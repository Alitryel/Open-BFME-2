"""Compile and score only the bank, without writing the shared match cache.

Clean room: 001c5e30.md and retail. Optional --oracle uses the existing
dispatch-only Unicorn oracle; it does not verify the pixel-producing callees.
"""
from contextlib import redirect_stdout
import difflib
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'AGENTS.md').is_file())
sys.path.insert(0, str(ROOT / 'tools'))
import build
import capstone
from permute import fitness

SYMBOL = '?Rva009B5530Prepare@@YAXPAURva009B5830State@@PAXH@Z'
RVA, SIZE = 0x1C5E30, 768
ADDRESSES = {
    '?g_bfmeVp6SelectorMap@@3PAEA': 0xBD8D00,
    '?g_bfmeSlotB54@@3PAXA': 0xE22D1C,
    '?g_bfmeSlotB50@@3PAXA': 0xE22D18,
    '_VP6_PredictFiltered': 0x5D8DD0,
    '_Var16Point': 0x5D8A30,
}


def main():
    source = ROOT / 'reverse/attempts/0x001c5e30.cpp'
    scratch = ROOT / 'build/predict-filtered-weight-repro'
    scratch.mkdir(exist_ok=True)
    obj = scratch / 'bank.obj'
    command, env = build.compiler_command(source, obj)
    result = subprocess.run(command, cwd=ROOT, env=env, capture_output=True)
    if result.returncode:
        sys.stderr.write(result.stdout.decode('latin1') + result.stderr.decode('latin1'))
        return result.returncode
    raw, relocs = build.read_object_symbol_bytes(obj, SYMBOL, code_only=True)
    compiled = bytearray(raw)
    for off, kind, name in relocs:
        value = struct.unpack_from('<I', compiled, off)[0] + ADDRESSES[name]
        if kind == 20:
            value -= 0x400000 + RVA + off + 4
        elif kind != 6:
            raise ValueError((off, kind, name))
        struct.pack_into('<I', compiled, off, value & 0xFFFFFFFF)
    compiled = bytes(compiled)
    retail = build.read_target_bytes(RVA, SIZE)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    own = [(i.mnemonic, i.op_str) for i in md.disasm(compiled, 0)]
    target = [(i.mnemonic, i.op_str) for i in md.disasm(retail, 0)]
    align = difflib.SequenceMatcher(None, [x[0] for x in own],
                                  [x[0] for x in target], autojunk=False)
    differing = structural = 0
    for tag, a, b, c, d in align.get_opcodes():
        if tag == 'equal':
            differing += sum(x != y for x, y in zip(own[a:b], target[c:d]))
        else:
            structural += 1
            differing += max(b - a, d - c)
    report = dict(source=str(source.relative_to(ROOT)), size=len(compiled),
                  target_size=SIZE, exact=compiled == retail,
                  differing_instructions=differing, structural_regions=structural,
                  fitness=fitness(compiled, retail),
                  byte_ratio=difflib.SequenceMatcher(None, compiled, retail,
                                                    autojunk=False).ratio(),
                  source_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),
                  compiled_sha256=hashlib.sha256(compiled).hexdigest(),
                  retail_sha256=hashlib.sha256(retail).hexdigest())
    if '--oracle' in sys.argv:
        path = ROOT / 'reverse/attempt_support/predict-filtered-bank-repair-20261018/oracle.py'
        spec = importlib.util.spec_from_file_location('prediction_oracle', path)
        oracle = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(oracle)
        oracle.compiled = lambda _source: compiled
        saved = sys.argv
        sys.argv = [str(path), str(source)]
        capture = io.StringIO()
        try:
            with redirect_stdout(capture):
                status = oracle.main()
        finally:
            sys.argv = saved
        report['oracle'] = json.loads(capture.getvalue())
        if status:
            print(json.dumps(report, indent=2))
            return status
    print(json.dumps(report, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
