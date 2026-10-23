"""Run from the repo root. Isolated diagnostics, not branch/callee admission.

Example: python3 <this-file> --family 18b --name w18b_01 w18b_17
Use --list to inspect a family without compiling; baseline is the default.
"""
import argparse
import concurrent.futures
import hashlib
import importlib.util
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = Path.cwd()
BANK = ROOT / "reverse/attempts/0x0043003c.cpp"
EXPECTED = "f89827eee85c9f65e8ee21cb57f5d2979398ad831755d9af6ea3f453a1a90750"


def generate(family):
    base = BANK.read_text()
    if family == "baseline":
        return [("retained-bank", base)]
    # Recreate this session's input after the better w22_01 body is banked.
    # Only that equality-proven argument and re_log's two-line prefix differ.
    if hashlib.sha256(base.encode()).hexdigest() != EXPECTED:
        start = base.index("    if ( now - m_lastGroupSelTime", base.index("   Int group = t - ((GameMessage::Type)62);"))
        end = base.index("    else", start)
        branch = base[start:end].replace("rva002AA176(m_lastGroupSelGroup)", "rva002AA176(group)", 1)
        base = base[:start] + branch + base[end:]
        for _ in range(16):
            if hashlib.sha256(base.encode()).hexdigest() == EXPECTED:
                break
            lines = base.splitlines(keepends=True)
            assert lines[1].startswith("// partial score="), "Bank changed; reassess these trials."
            base = "".join(lines[2:])
    assert hashlib.sha256(base.encode()).hexdigest() == EXPECTED, "Bank changed; reassess these trials."
    a = base.index("   Int group = t - ((GameMessage::Type)62);")
    b = base.index("  case ((GameMessage::Type)72):", a)
    fn = base[a:b]
    old = fn[fn.index("    if (m_lastGroupSelGroup >= 0)"):
             fn.index("    // check for double-press to jump view")]
    direct = old.replace("     Bool valid = TRUE;\n", "")
    direct = direct.replace("valid = FALSE;", "m_lastGroupSelGroup = -1;")
    direct = direct.replace("     if (!valid)\n      m_lastGroupSelGroup = -1;\n", "")
    scope = dict(BASE=base, a=a, b=b, fn=fn, old=old, direct=direct)
    path = HERE / ("wave" + family + ".py")
    exec(compile(path.read_text(), str(path), "exec"), scope)
    return scope["variants"]


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--family", default="baseline",
                        choices=["baseline", "15", "16", "17", "18b", "19", "20", "21", "22", "23", "24"])
    parser.add_argument("--name", nargs="*")
    parser.add_argument("--list", action="store_true")
    args = parser.parse_args()
    variants = generate(args.family)
    if args.name:
        variants = [(n, s) for n, s in variants if n in args.name]
        assert len(variants) == len(args.name), "Unknown variant name"
    if args.list:
        print(json.dumps([name for name, _ in variants]))
    else:
        previous = HERE.parent / "0043003c-20261020-codex7/reproduce.py"
        spec = importlib.util.spec_from_file_location("selection_diagnostic", previous)
        diagnostic = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(diagnostic)
        diagnostic.OUT = ROOT / "build/selection43003c-codex7-resume-reproduce"
        diagnostic.OUT.mkdir(parents=True, exist_ok=True)

        def measure(item):
            result = diagnostic.measure(item)
            name, _ = item
            obj = diagnostic.OUT / (name + ".obj")
            body, relocs = next((b, r) for n, b, r in diagnostic.object_functions(obj)
                                if n == diagnostic.NAME)
            holes = {i for off, _, _ in relocs for i in range(off, off + 4)}
            differences = [dict(offset=hex(i), ours=hex(x), retail=hex(y))
                           for i, (x, y) in enumerate(zip(body, diagnostic.TARGET))
                           if i not in holes and x != y]
            raw = dict(ours_size=len(body), retail_size=len(diagnostic.TARGET),
                       relocations=len(relocs), unmasked_differences=differences)
            (diagnostic.OUT / (name + ".raw-diff.json")).write_text(json.dumps(raw, indent=2) + "\n")
            if len(body) == len(diagnostic.TARGET):
                row = dict(name=diagnostic.NAME, rva="0x0043003C", size="4054", notes="")
                patch = dict(target_rva=0x43003C, target=diagnostic.TARGET)
                problems = diagnostic.build.body_extent_problems(
                    row, patch, {}, obj, [0x43003C, 0x431012])
                report = dict(check="build.body_extent_problems", problems=problems,
                              rva="0x0043003C", size=4054)
                (diagnostic.OUT / (name + ".extent.json")).write_text(json.dumps(report, indent=2) + "\n")
            return result

        with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
            for result in pool.map(measure, variants):
                print(json.dumps(result), flush=True)
