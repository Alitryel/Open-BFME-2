"""Bounded copy-definition/instantiation experiments; normal diagnostic CLI only."""
from pathlib import Path
import json
import hashlib
import os
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / "build/string-copy-context-replay/root"
OUT.mkdir(parents=True, exist_ok=True)
BASE = ROOT / "Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp"
COPY = "??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z"
INSERT = "?insertRange@Rva008314E0String@@QAEXPAD00ABUBfmeRangeTag@@@Z"
REPLACE = "?replaceRange@Rva008314E0String@@QAEAAV1@PAD000ABUBfmeRangeTag@@@Z"
text = BASE.read_text()
decl = "void *__copy_trivial(const void *__first, const void *__last, void *__result);"
definition = """inline void *__copy_trivial(const void *__first, const void *__last, void *__result)
{
    return (__last == __first) ? __result :
        ((char *)memmove(__result, __first, ((const char *)__last - (const char *)__first))) +
        ((const char *)__last - (const char *)__first);
}"""
boundary = "\n}\n\nextern \"C\" void free"
instantiation = "\ntemplate char *Rva000179B0UninitializedCopy<char *, char *>(char *, char *, char *);\n"
cases = {}
for optimization in ("Od", "O2"):
    for timing in ("definition", "instantiate"):
        s = text.replace("/Od", "/" + optimization, 1).replace(decl, definition)
        s = s.replace("namespace _STL\n{", '#pragma optimize("gty", on)\nnamespace _STL\n{', 1)
        addition = instantiation if timing == "instantiate" else ""
        s = s.replace(boundary, addition + '\n}\n#pragma optimize("", off)\n\nextern "C" void free', 1)
        cases[optimization + "-" + timing] = s
# Unlike the old scoped-gty trial, keep the actual copy definition visible under
# each policy, and record the emitted helper independently of caller size.
for timing in ("instantiate", "late"):
    s = text.replace(decl, definition)
    if timing == "instantiate":
        s = s.replace(boundary, instantiation + boundary, 1)
    cases["Od-visible-" + timing] = s
for body_name, body in (
    ("dispatch", "return __uninitialized_copy(__first, __last, __result, __true_type());"),
    ("direct", """return (__last == __first) ? __result :
        ((char *)memmove(__result, __first, __last - __first)) + (__last - __first);"""),
):
    for inline in ("inline", "__declspec(noinline)", ""):
        specialization = """
#pragma optimize("gty", on)
template <> %s char *Rva000179B0UninitializedCopy<char *, char *>(
    char *__first, char *__last, char *__result)
{
    %s
}
#pragma optimize("", off)
""" % (inline, body)
        s = text.replace("/Od", "/O2", 1).replace(decl, definition)
        s = s.replace("namespace _STL\n{", '#pragma optimize("", off)\nnamespace _STL\n{', 1)
        s = s.replace(boundary, specialization + boundary, 1)
        cases["spec-" + body_name + "-" + (inline or "ordinary").replace("__declspec(noinline)", "noinline")] = s
for label in ("O2-definition", "O2-instantiate"):
    cases[label + "-eof-on"] = cases[label] + '\n#pragma optimize("gty", on)\n'
for label in ("spec-direct-inline", "spec-direct-noinline", "spec-direct-ordinary"):
    cases[label + "-extern-worker"] = cases[label].replace(definition, decl, 1)
for label in ("spec-dispatch-inline", "spec-dispatch-noinline", "spec-dispatch-ordinary"):
    s = cases[label].replace(definition, decl, 1)
    s = s.replace("return (_OutputIter)__copy_trivial(__first, __last, __result);", """return (__last == __first) ? __result :
        (_OutputIter)(((char *)memmove(__result, __first, ((const char *)__last - (const char *)__first))) +
        ((const char *)__last - (const char *)__first));""", 1)
    cases[label + "-inline-worker"] = s
for mode in ("force", "force-ctors"):
    s = cases["spec-dispatch-inline-inline-worker"]
    for signature in ("inline _OutputIter", "inline _ForwardIter __uninitialized_copy"):
        s = s.replace(signature, signature.replace("inline", "__forceinline", 1))
    if mode == "force-ctors":
        s = s.replace("inline _OKToMemCpy", "__forceinline _OKToMemCpy")
        s = s.replace("static __true_type _Ret()", "static __forceinline __true_type _Ret()")
        s = s.replace("static _Type _Ret()", "static __forceinline _Type _Ret()")
    cases["spec-dispatch-" + mode] = s
for mode in ("base", "force"):
    s = text.replace("struct __true_type\n{\n};", "struct __true_type\n{\n    __true_type() {}\n};", 1)
    if mode == "force":
        for signature in ("inline _OutputIter", "inline _ForwardIter"):
            s = s.replace(signature, signature.replace("inline", "__forceinline", 1))
    cases["diagnostic-empty-ctor-" + mode] = s
for depth in (7, 8, 9):
    cases["exact-copy-depth" + str(depth)] = cases["spec-dispatch-force-ctors"].replace(
        "#pragma inline_depth(6)", "#pragma inline_depth(%d)" % depth, 1)
for depth in (4, 5, 6, 8):
    s = cases["spec-dispatch-force-ctors"].replace("/O2", "/Od", 1)
    s = s.replace("#pragma inline_depth(6)", "#pragma inline_depth(%d)" % depth, 1)
    cases["exact-copy-Od-depth" + str(depth)] = s

selected = sys.argv[1:] or list(cases)
records = []
env = dict(os.environ, BFME_OBJSTORE="off")
for label in selected:
    source = OUT / (label + ".cpp")
    source.write_text(cases[label], newline="\n")
    rows = []
    for name, rva, size, short in (
        (INSERT, "0x28820", 740, "insert"),
        (REPLACE, "0x2B050", 501, "replace"),
        (COPY, "0x179B0", 41, "copy"),
    ):
        cmd = [sys.executable, "tools/explain_mismatch.py", name,
               "--rva", rva, "--size", str(size), "--source",
               source.relative_to(ROOT).as_posix(), "--context", "2"]
        result = subprocess.run(cmd, cwd=ROOT, env=env, text=True,
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        log = OUT / (label + "." + short + ".log")
        log.write_text(result.stdout)
        row = {"target": short, "exit": result.returncode, "log": log.name,
               "summary": [l for l in result.stdout.splitlines() if any(t in l for t in
                           ("compiled symbol size:", "classification:", "first diff:", "unresolved:", "OK:"))]}
        rows.append(row)
        print(json.dumps({"case": label, **row}), flush=True)
        if any(t in result.stdout for t in ("PermissionError", "WinError", "Access is denied")):
            raise SystemExit(result.stdout[-2000:])
    records.append({"case": label, "checks": rows})
(OUT / ("results-" + hashlib.sha256("\n".join(selected).encode()).hexdigest()[:12] + ".json")).write_text(json.dumps(records, indent=2))
