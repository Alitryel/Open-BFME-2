"""Materialize and compare a banked experiment; never changes Code or ledgers."""
import argparse
import os
from pathlib import Path
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("candidate", choices=("primary", "specialization"))
args = parser.parse_args()
name = {"primary": "primary-timing-in-class",
        "specialization": "exact-copy-Od-depth6"}[args.candidate]
out = ROOT / "build/string-copy-context-replay"
out.mkdir(parents=True, exist_ok=True)
source = out / (name + ".cpp")
source.write_text((HERE / (name + ".cpp.txt")).read_text(), newline="\n")
for symbol, rva, size, role in (
    ("?insertRange@Rva008314E0String@@QAEXPAD00ABUBfmeRangeTag@@@Z",
     "0x28820", 740, "insert"),
    ("?replaceRange@Rva008314E0String@@QAEAAV1@PAD000ABUBfmeRangeTag@@@Z",
     "0x2B050", 501, "replace"),
    ("??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z",
     "0x179B0", 41, "copy"),
):
    command = [sys.executable, "tools/explain_mismatch.py", symbol,
               "--rva", rva, "--size", str(size), "--source",
               source.relative_to(ROOT).as_posix(), "--context", "2"]
    result = subprocess.run(command, cwd=ROOT,
                            env=dict(os.environ, BFME_OBJSTORE="off"),
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                            text=True)
    log = out / (name + "." + role + ".log")
    log.write_text(result.stdout)
    print(role, "log=" + str(log.relative_to(ROOT)))
    for line in result.stdout.splitlines():
        if any(token in line for token in
               ("compiled symbol size:", "classification:", "first diff:",
                "unresolved:", "OK:")):
            print(line)
    if result.returncode:
        print(result.stdout[-2500:])
        raise SystemExit(result.returncode)
print("This is a diagnostic replay. The replacement mismatch is expected; "
      "successful execution is not acceptance of the candidate.")
