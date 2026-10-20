"""Materialize measured controls; --run opts into normal compiler diagnostics.

No raw compiler API, ledger edit, pin, claim, or network operation is used.
The input commit is read with git show, independently of current source edits.
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
OUT = ROOT / "build/copy-provider-replay"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def apply_patch(original, patch):
    lines = original.splitlines(True)
    result, pos = [], 0
    records = patch.splitlines(True)
    i = 2
    while i < len(records):
        header = re.match(r"@@ -(\d+)(?:,\d+)? \+\d+(?:,\d+)? @@", records[i])
        if not header:
            raise ValueError("Malformed patch hunk: " + records[i])
        start = int(header.group(1)) - 1
        if start < pos:
            raise ValueError("Overlapping patch hunks")
        result.extend(lines[pos:start])
        pos = start
        i += 1
        while i < len(records) and not records[i].startswith("@@ "):
            tag, value = records[i][0], records[i][1:]
            if tag in " -":
                if pos >= len(lines) or lines[pos] != value:
                    raise ValueError("Patch context differs at original line " + str(pos + 1))
                pos += 1
            if tag in " +":
                result.append(value)
            if tag not in " +-":
                raise ValueError("Unsupported patch record")
            i += 1
    result.extend(lines[pos:])
    return "".join(result)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--case", action="append", help="Choose an inputs.json case; repeat to select several")
    parser.add_argument("--run", action="store_true", help="After preparation, invoke normal explain_mismatch diagnostics")
    args = parser.parse_args()
    inputs = json.loads((HERE / "inputs.json").read_text())
    selected = [case for case in inputs["cases"] if not args.case or case["case"] in args.case]
    if args.case and set(args.case) != {case["case"] for case in selected}:
        parser.error("Unknown case")
    OUT.mkdir(parents=True, exist_ok=True)
    for case in selected:
        original = subprocess.check_output(
            ["git", "show", case["base_revision"] + ":" + case["base_source"]], cwd=ROOT)
        if sha(original) != case["base_git_blob_sha256"]:
            raise SystemExit("Original Git blob hash differs")
        original_text = original.decode("utf-8-sig").replace("\r\n", "\n")
        if sha(original_text.encode()) != case["base_text_sha256"]:
            raise SystemExit("Original normalized source hash differs")
        original_label = "fill-original" if case["base_source"].endswith("stlport_string_insert_fill.cpp") else "older-original"
        (OUT / (original_label + ".cpp")).write_text(original_text, newline="\n")
        candidate = apply_patch(original_text, (HERE / case["patch"]).read_text())
        if sha(candidate.encode()) != case["candidate_sha256"]:
            raise SystemExit("Reconstructed candidate hash differs: " + case["case"])
        path = OUT / (case["case"] + ".cpp")
        path.write_text(candidate, newline="\n")
        print(case["case"] + ": prepared exact measured source " + case["candidate_sha256"], flush=True)
        if not args.run:
            continue
        temp = OUT / "temp"
        temp.mkdir(exist_ok=True)
        env = dict(os.environ, BFME_OBJSTORE="off", TEMP=str(temp), TMP=str(temp))
        for label, name, rva, size in case["rows"]:
            command = [sys.executable, "tools/explain_mismatch.py", name,
                       "--rva", rva, "--size", str(size), "--source",
                       path.relative_to(ROOT).as_posix(), "--context", "2"]
            done = subprocess.run(command, cwd=ROOT, env=env, text=True,
                                  stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            (OUT / (case["case"] + "." + label + ".log")).write_text(done.stdout)
            print(done.stdout, flush=True)
            if done.returncode:
                raise SystemExit(done.returncode)
    if not args.run:
        print("Preparation only; no compiler was invoked.")


if __name__ == "__main__":
    main()
