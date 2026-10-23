"""Regenerate the executed reference controls from tracked source; cache independent.

Default: validate inputs and generate scratch sources only.
--run: also invoke the normal explain_mismatch CLI, recording fresh diagnostics.
No direct compiler calls, ledger writes, pin changes or production edits.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
SOURCES = {
    "owner": "Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp",
    "v21": "Code/GameEngine/Source/Common/BfmeConv1461.cpp",
    "v22": "Code/GameEngine/Source/Common/BfmeConv1462.cpp",
}
INSERT = "?insertRange@Rva008314E0String@@QAEXPAD00ABUBfmeRangeTag@@@Z"
REPLACE = "?replaceRange@Rva008314E0String@@QAEAAV1@PAD000ABUBfmeRangeTag@@@Z"
COPY = "??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z"
ROWS = {
    "owner": [("insert", INSERT, "0x28820", 740),
              ("replace", REPLACE, "0x2B050", 501)],
    "v21": [("caller", "?bfmeInsertV21@BfmeStrV21@@QAEPAV1@IPADI@Z", "0x2AB40", 149),
            ("insert", INSERT, "0x28820", 740)],
    "v22": [("caller", "?bfmeInsertV22@BfmeStrV22@@QAEPAV1@IPAD@Z", "0x2ABE0", 170),
            ("insert", INSERT, "0x28820", 740)],
}
ITERATION = [
    ("inline int __distance(", "__forceinline int __distance("),
    ("inline int distance(", "__forceinline int distance("),
    ("inline void __advance(", "__forceinline void __advance("),
    ("inline void advance(", "__forceinline void advance("),
    ("static void copyIter(", "static __forceinline void copyIter("),
]


def once(text, old, new):
    assert text.count(old) == 1, old
    return text.replace(old, new, 1)


def actual_header(text, extern):
    begin = text.index("namespace _STL\n{")
    end = text.index('\nextern "C" void free(void *);', begin)
    declarations = text[begin:text.index("void *__copy_trivial(", begin)]
    declarations += "void Rva0069E440Destroy(char *, char *);\n}\n"
    header = ("#define _STLP_BFME_COPY_TRIVIAL_EXTERN\n" if extern else "")
    header += (
        "#define uninitialized_copy Rva000179B0UninitializedCopy\n"
        "#include <stl/_uninitialized.h>\n"
        "#undef uninitialized_copy\n"
    )
    return text[:begin] + header + declarations + text[end:]


def primary_timing(text):
    text = once(text, "/Od", "/O2")
    text = once(text, "namespace _STL\n{",
                '#pragma optimize("", off)\nnamespace _STL\n{')
    text = once(
        text, "return (_OutputIter)__copy_trivial(__first, __last, __result);",
        """return (__last == __first) ? __result :
        (_OutputIter)(((char *)memmove(__result, __first, ((const char *)__last - (const char *)__first))) +
        ((const char *)__last - (const char *)__first));""",
    )
    for old in (
        "inline _OutputIter __copy_ptrs(",
        "inline _OutputIter __copy_aux(",
        "inline _ForwardIter __uninitialized_copy(",
        "inline _OKToMemCpy", "static __true_type _Ret()",
        "static _Type _Ret()",
    ):
        new = (old.replace("static ", "static __forceinline ", 1)
               if old.startswith("static ") else old.replace("inline", "__forceinline", 1))
        text = once(text, old, new)
    # Preserve the blank line left by removal of the diagnostic specialization.
    text = once(text, "\n}\n}\n\nextern \"C\" void free",
                "\n}\n\n}\n\nextern \"C\" void free")
    return text + '\n#pragma optimize("gty", on)\n'


def out_of_class(text):
    signature = "\tvoid insertRange(char *__position, char *__first, char *__last, const BfmeRangeTag &)"
    start = text.index(signature)
    opening = text.index("{", start)
    level, end = 1, opening + 1
    while level:
        level += (text[end] == "{") - (text[end] == "}")
        end += 1
    body = text[opening:end]
    text = text[:start] + signature + ";" + text[end:]
    definition = (
        "void Rva008314E0String::insertRange"
        "(char *__position, char *__first, char *__last, const BfmeRangeTag &)\n"
        + body + "\n\n"
    )
    position = text.index("Rva008314E0String &Rva008314E0String::replaceRange(")
    return text[:position] + definition + text[position:]


def force_iteration(text):
    for old, new in ITERATION:
        text = once(text, old, new)
    return text


def cases():
    result = {}
    for context, source in SOURCES.items():
        text = (ROOT / source).read_text()
        for label, extern in (("01-header-extern", True), ("02-header-visible", False)):
            result[f"{label}-{context}"] = (context, actual_header(text, extern))
    primary = primary_timing((ROOT / SOURCES["owner"]).read_text())
    for ob in (1, 2):
        timing = once(out_of_class(primary), "/Ob1", f"/Ob{ob}")
        result[f"timing-ob{ob}"] = ("owner", timing)
        result[f"timing-force-iter-ob{ob}"] = ("owner", force_iteration(timing))
    result["primary-timing-in-class"] = ("owner", force_iteration(primary))
    return result


def check_inputs():
    inputs = json.loads((HERE / "inputs.json").read_text())
    for relative, expected in inputs["sha256"].items():
        path = ROOT / relative
        if not path.exists():
            raise SystemExit(f"Missing recorded input: {relative}")
        if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
            raise SystemExit(f"Changed recorded input: {relative}; reassess before replay.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run", action="store_true")
    parser.add_argument("--case", action="append", default=[])
    args = parser.parse_args()
    check_inputs()
    output = ROOT / "build/string-copy-context-reference-replay"
    output.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, BFME_OBJSTORE="off")
    records = []
    for label, (context, source) in cases().items():
        if args.case and label not in args.case:
            continue
        path = output / (label + ".cpp")
        path.write_text(source, newline="\n")
        row = {"case": label, "source": path.relative_to(ROOT).as_posix(), "checks": []}
        if args.run:
            for short, name, rva, size in ROWS[context] + [("copy", COPY, "0x179B0", 41)]:
                command = [
                    sys.executable, "tools/explain_mismatch.py", name,
                    "--source", row["source"], "--rva", rva, "--size", str(size),
                    "--context", "2",
                ]
                done = subprocess.run(command, cwd=ROOT, env=env, text=True,
                                      stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                log = output / f"{label}.{short}.log"
                log.write_text(done.stdout)
                check = {
                    "row": short, "exit": done.returncode, "log": log.name,
                    "summary": [line for line in done.stdout.splitlines()
                                if any(token in line for token in
                                       ("compiled symbol size:", "classification:",
                                        "first diff:", "unresolved:", "OK:"))],
                }
                row["checks"].append(check)
                print(json.dumps({"case": label, **check}), flush=True)
                if any(token in done.stdout for token in
                       ("PermissionError", "WinError", "Access is denied", "OSError:")):
                    raise SystemExit(done.stdout[-2200:])
        records.append(row)
    (output / "results.json").write_text(json.dumps(records, indent=2) + "\n")
    print(f"Prepared {len(records)} cases in {output.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
