"""Run from the repository root; all generated files stay under build/."""
import concurrent.futures
import difflib
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / "tools"))
import build
import capstone
from locate import object_functions

NAME = "?translateGameMessage@SelectionTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z"
OUT = ROOT / "build/selection43003c-codex7-reproduce"
TARGET = build.read_target_bytes(0x43003C, 4054)


def measure(item):
    label, source = item
    path = OUT / (label + ".cpp")
    path.write_text(source)
    obj = path.with_suffix(".obj")
    cmd, env = build.compiler_command(path, obj)
    env["WINEDEBUG"] = "-all"
    result = subprocess.run(cmd, cwd=ROOT, env=env, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT)
    path.with_suffix(".compile.log").write_bytes(result.stdout)
    if result.returncode:
        raise RuntimeError(str(path.with_suffix(".compile.log")))
    ours, relocations = next((b, r) for n, b, r in object_functions(obj)
                             if n == NAME)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    a, b = list(md.disasm(ours, 0)), list(md.disasm(TARGET, 0))
    assert a[-1].address + a[-1].size == len(ours)
    assert b[-1].address + b[-1].size == len(TARGET)
    holes = {x for off, _, _ in relocations for x in range(off, off + 4)}
    alignment = difflib.SequenceMatcher(a=[i.mnemonic for i in a],
                                       b=[i.mnemonic for i in b], autojunk=False)
    structural, differences = [], []
    for tag, i, j, k, l in alignment.get_opcodes():
        if tag != "equal":
            structural.append([tag, hex(b[k].address) if k < len(b) else "end",
                               [[hex(z.address), z.mnemonic, z.op_str] for z in a[i:j]],
                               [[hex(z.address), z.mnemonic, z.op_str] for z in b[k:l]]])
            continue
        for x, y in zip(a[i:j], b[k:l]):
            if x.mnemonic.startswith("j"):
                continue
            xb, yb = bytearray(x.bytes), bytearray(y.bytes)
            for pos in range(x.size):
                if x.address + pos in holes and pos < len(yb):
                    xb[pos] = yb[pos] = 0
            if xb != yb:
                differences.append([hex(y.address), y.mnemonic, y.op_str,
                                    hex(x.address), x.op_str])
    report = dict(label=label, size=len(ours), regions=len(structural),
                  defects=len(differences), structural=structural, differences=differences)
    path.with_suffix(".json").write_text(json.dumps(report, indent=2) + "\n")
    return {k: report[k] for k in ("label", "size", "regions", "defects")}


if __name__ == "__main__":
    OUT.mkdir(parents=True, exist_ok=True)
    bank = (ROOT / "reverse/attempts/0x0043003c.cpp").read_text()
    condition = "!(((const unsigned long *)((const char *)nativeTemplate43003C(obj)+0x108))[1] & (1u << 23))"
    assert condition in bank, "Bank changed: inspect the new source before reconstructing this baseline."
    baseline = bank.replace(condition, "!(((const unsigned char *)nativeTemplate43003C(obj))[0x10E] & 0x80)")
    baseline = baseline.replace("     if (nativeContained43003C(obj) &&",
                                "     Object *containedBy = nativeContained43003C(obj);\n     if (containedBy &&")
    baseline = baseline.replace("      obj = nativeContained43003C(obj);", "      obj = containedBy;")
    subtraction = bank.replace("group == m_lastGroupSelGroup",
                               "!((UnsignedInt)group - (UnsignedInt)m_lastGroupSelGroup)", 1)
    # These are diagnostics, not full gates: branch destinations and callee
    # identities still need the normal verifier. No shared build cache is written.
    with concurrent.futures.ThreadPoolExecutor(max_workers=3) as executor:
        for result in executor.map(measure, [("baseline", baseline), ("best", bank),
                                             ("subtraction-diagnostic", subtraction)]):
            print(json.dumps(result), flush=True)
