"""Reproduce bank diagnostics in isolated objects; this does not verify a row."""
import difflib
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import build
import capstone
import permute

SYM = "?rva0051DE3D@AptScoreScreen@@QAEXXZ"
WORK = ROOT / "build/apt51de3d-oct22-reproduce"
WORK.mkdir(parents=True, exist_ok=True)
TARGET = build.read_target_bytes(0x51DE3D, 1061)
SYMBOLS = build.load_symbol_map()


def insns(blob):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return list(md.disasm(blob, 0))


def measure(label, source):
    src = WORK / (label + ".cpp")
    obj = src.with_suffix(".obj")
    src.write_text(source)
    command, env = build.compiler_command(src, obj)
    process = subprocess.run(command, cwd=ROOT, env=env,
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             text=True)
    src.with_suffix(".compile.txt").write_text(process.stdout)
    process.check_returncode()
    raw, relocations = build.read_object_symbol_bytes(obj, SYM, code_only=True)
    raw = raw.rstrip(b"\xcc")
    # Diagnostic window only. The actual ledger extent is always 1061.
    row = dict(name=SYM, target_rva="0x0051DE3D",
               target_size=str(max(len(raw), 1061)),
               source=src.relative_to(ROOT).as_posix(), notes="")
    result = build.compile_function(row, SYMBOLS, obj)
    a, b = insns(raw), insns(TARGET)
    sequence = difflib.SequenceMatcher(None, [i.mnemonic for i in a],
                                      [i.mnemonic for i in b], autojunk=False)
    regions = []
    memory = registers = different = 0
    for tag, a1, a2, b1, b2 in sequence.get_opcodes():
        if tag != "equal":
            regions.append([hex(b[b1].address) if b1 < len(b) else "end",
                            a2-a1, b2-b1])
            different += max(a2-a1, b2-b1)
            continue
        for x, y in zip(a[a1:a2], b[b1:b2]):
            if x.op_str == y.op_str or x.mnemonic.startswith("j"):
                continue
            if any(x.address <= r[0] < x.address+x.size for r in relocations):
                continue
            different += 1
            if "[" in x.op_str or "[" in y.op_str:
                memory += 1
            else:
                registers += 1
    return dict(case=label, size=len(raw),
                fitness=permute.fitness(result["bytes"], TARGET),
                nd=different, mem=memory, reg=registers, regions=regions,
                unresolved=result["unresolved"],
                exact=result["bytes"] == TARGET and not result["unresolved"])


bank = (ROOT / "reverse/attempts/0x0051de3d.cpp").read_text()
before = bank.replace("   typedef bool (AptScoreScreen::*Populate51)();\n", "", 1)
before = before.replace("   const Populate51 populate51 = "
                        "&AptScoreScreen::PopulatePersistentUnitsListbox;\n", "", 1)
before = before.replace("(this->*populate51)();", "PopulatePersistentUnitsListbox();", 1)
if before == bank or "populate51" in before:
    raise SystemExit("Bank changed: review the control transformation first")
results = [measure("bank", bank), measure("direct-call-control", before)]
(WORK / "results.json").write_text(json.dumps(results, indent=2) + "\n")
print(json.dumps(results, indent=2))
