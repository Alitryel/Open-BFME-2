"""Materialize five hash-bound frame controls; optionally run normal diagnostics.

Default execution only prepares sources under build/. --run compiles with
explain_mismatch and verifies the recorded exact matches AND expected failures.
A successful replay is not a successful linking repair.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
OUT = ROOT / "build/string-copy-provider-frame-replay"
INSERT = "?insertRange@Rva008314E0String@@QAEXPAD00ABUBfmeRangeTag@@@Z"
COPY = "??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z"
ROWS = {
    "owner": [("insert", INSERT, "0x28820", 740, 740, "exact match", None),
              ("replace", "?replaceRange@Rva008314E0String@@QAEAAV1@PAD000ABUBfmeRangeTag@@@Z",
               "0x2B050", 501, 501, "instruction/register encoding mismatch", "+0x5")],
    "v21": [("caller", "?bfmeInsertV21@BfmeStrV21@@QAEPAV1@IPADI@Z",
             "0x2AB40", 149, 116, "size mismatch", "+0x3"),
            ("insert", INSERT, "0x28820", 740, 740, "exact match", None)],
    "v22": [("caller", "?bfmeInsertV22@BfmeStrV22@@QAEPAV1@IPAD@Z",
             "0x2ABE0", 170, 134, "size mismatch", "+0x5"),
            ("insert", INSERT, "0x28820", 740, 740, "exact match", None)],
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def apply_patch(original, patch):
    """Strict local unified diff: no shell, offsets, fuzzy matches or fallback."""
    lines = original.splitlines(keepends=True)
    edits = patch.splitlines(keepends=True)
    assert edits[0].startswith("--- ") and edits[1].startswith("+++ ")
    cursor, i, output = 0, 2, []
    while i < len(edits):
        match = re.fullmatch(r"@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@\n", edits[i])
        assert match, edits[i]
        start = int(match.group(1)) - 1
        old_count, new_count = int(match.group(2) or "1"), int(match.group(4) or "1")
        assert cursor <= start <= len(lines)
        output.extend(lines[cursor:start])
        cursor, old_seen, new_seen = start, 0, 0
        i += 1
        while i < len(edits) and not edits[i].startswith("@@ "):
            op, body = edits[i][0], edits[i][1:]
            assert op in " +-"
            if op in " -":
                assert cursor < len(lines) and lines[cursor] == body
                cursor += 1
                old_seen += 1
            if op in " +":
                output.append(body)
                new_seen += 1
            i += 1
        assert (old_seen, new_seen) == (old_count, new_count)
    output.extend(lines[cursor:])
    return "".join(output)


def materialize(case, primary):
    if case["kind"] == "primary":
        return primary
    if case["kind"] == "patch":
        return apply_patch(primary, (HERE / case["patch"]).read_text())
    assert case["kind"] == "wrapper"
    production = ROOT / case["production"]["path"]
    assert sha(production.read_bytes()) == case["production"]["sha256"], (
        "Production wrapper changed; review this recorded context before replaying.", production)
    text = production.read_text()
    marker = "// Compatibility spelling for the pre-existing neutral caller ABI."
    assert text.count(marker) == 1
    split = "\nRva008314E0String &Rva008314E0String::replaceRange("
    assert primary.count(split) == 1
    class_only = primary.split(split, 1)[0]
    assert class_only.count("#pragma inline_depth(6)\n") == 1
    class_only = class_only.replace("#pragma inline_depth(6)\n", "")
    extra = ""
    if case["context"] == "v22":
        declaration = "int bfmeMakeOX(void *);"
        assert text.count(declaration) == 1
        extra = declaration + "\n\n"
    return class_only + extra + marker + text.split(marker, 1)[1] + '\n#pragma optimize("gty", on)\n'


def main():
    receipt = json.loads((HERE / "selected.json").read_text())
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run", action="store_true", help="Run normal explain_mismatch after preparation.")
    parser.add_argument("--case", action="append", choices=[c["case"] for c in receipt["cases"]])
    args = parser.parse_args()
    primary_bytes = (HERE / "primary01.cpp.txt").read_bytes()
    assert sha(primary_bytes) == receipt["primary_sha256"]
    primary = primary_bytes.decode("utf-8")
    inputs = json.loads((HERE / "inputs.json").read_text())
    for relative, expected in inputs["compiled_dependency_md5"].items():
        assert hashlib.md5((ROOT / relative).read_bytes()).hexdigest() == expected, (
            "Recorded compiler input changed; review before replaying.", relative)
    OUT.mkdir(parents=True, exist_ok=True)
    temp = OUT / "temp"
    temp.mkdir(exist_ok=True)
    env = dict(os.environ, BFME_OBJSTORE="off", TEMP=str(temp), TMP=str(temp))
    results = []
    for case in receipt["cases"]:
        if args.case and case["case"] not in args.case:
            continue
        text = materialize(case, primary)
        assert sha(text.encode("utf-8")) == case["source_sha256"], case["case"]
        source = OUT / (case["case"] + ".cpp")
        source.write_text(text, encoding="utf-8", newline="\n")
        assert sha(source.read_bytes()) == case["source_sha256"]
        print("Prepared " + source.relative_to(ROOT).as_posix(), flush=True)
        if not args.run:
            continue
        rows = ROWS[case["context"]] + [("copy", COPY, "0x179B0", 41, 41, "exact match", None)]
        for role, symbol, rva, target_size, compiled_size, classification, first in rows:
            command = [sys.executable, "tools/explain_mismatch.py", symbol, "--rva", rva,
                       "--size", str(target_size), "--source", source.relative_to(ROOT).as_posix(),
                       "--context", "3"]
            done = subprocess.run(command, cwd=ROOT, env=env, stdout=subprocess.PIPE,
                                  stderr=subprocess.STDOUT, text=True)
            log = OUT / (case["case"] + "." + role + ".txt")
            log.write_text(done.stdout)
            assert done.returncode == 0, (command, done.stdout)
            assert re.search(r"^classification: " + re.escape(classification) + r"$", done.stdout, re.M), done.stdout
            assert f"compiled symbol size: {compiled_size} bytes" in done.stdout, done.stdout
            if first:
                assert "first diff: " + first + " at RVA " in done.stdout, done.stdout
            assert not re.search(r"^unresolved:", done.stdout, re.M), done.stdout
            results.append(dict(case=case["case"], row=role, classification=classification,
                                compiled_size=compiled_size, log=log.relative_to(ROOT).as_posix()))
            print(f"{case['case']} {role}: reproduced {classification}, {compiled_size} bytes", flush=True)
    if args.run:
        (OUT / "results.json").write_text(json.dumps(results, indent=2) + "\n")
        print("Recorded outcomes reproduced, including expected caller failures. Shared-copy scope remains blocked.")
    else:
        print("Preparation only: source hashes verified; no compiler was run.")


if __name__ == "__main__":
    main()
