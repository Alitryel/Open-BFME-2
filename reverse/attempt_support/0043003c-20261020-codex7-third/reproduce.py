"""From the repo root: --family 30 --name w30_001. Baseline is the default.

Isolated compiler diagnostics, never build.compile_source or a production gate.
--list emits source names without compiling. Prior generations are not rerun
unless explicitly requested. Diagnostic-only unused locals and assumptions are
not proposed bank source.
"""
import argparse
import concurrent.futures
import hashlib
import importlib.util
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = Path.cwd()
EXPECTED = '9a4702f3c6fc22a564c3d7e800f8b6545051faf779eb5e64755074a77f363eb1'
FAMILIES = ['baseline', '25b', '26', '27', '28', '29', '30', '31', '32', '33', '34']


def generate(family):
    base = (ROOT / 'reverse/attempts/0x0043003c.cpp').read_text()
    if family == 'baseline':
        return [('retained-bank', base)]
    # re_log prefixes a score and symbol while preserving the prior best body.
    for _ in range(20):
        if hashlib.sha256(base.encode()).hexdigest() == EXPECTED:
            break
        lines = base.splitlines(keepends=True)
        assert lines[1].startswith('// partial score='), 'Changed bank: reassess inputs.'
        base = ''.join(lines[2:])
    assert hashlib.sha256(base.encode()).hexdigest() == EXPECTED, 'Changed bank: reassess inputs.'
    a = base.index('   Int group = t - ((GameMessage::Type)62);')
    b = base.index('  case ((GameMessage::Type)72):', a)
    scope = dict(Path=Path, BASE=base, a=a, b=b, fn=base[a:b])
    path = HERE / ('wave'+family+'.py')
    exec(compile(path.read_text(),str(path),'exec'),scope)
    return scope['variants']


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--family', choices=FAMILIES, default='baseline')
    ap.add_argument('--name', nargs='*')
    ap.add_argument('--list', action='store_true')
    args = ap.parse_args()
    variants = generate(args.family)
    if args.name:
        variants = [(name, src) for name, src in variants if name in args.name]
        assert len(variants) == len(args.name), 'Unknown variant name'
    if args.list:
        print(json.dumps([name for name, _ in variants]))
    else:
        path = HERE.parent/'0043003c-20261020-codex7/reproduce.py'
        spec = importlib.util.spec_from_file_location('selection_diagnostic',path)
        diagnostic = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(diagnostic)
        diagnostic.OUT = ROOT/'build/selection43003c-codex7-third-reproduce'
        diagnostic.OUT.mkdir(parents=True, exist_ok=True)

        def measure(item):
            report = diagnostic.measure(item)
            name, _ = item
            obj = diagnostic.OUT/(name+'.obj')
            body, relocs = next((b,r) for n,b,r in diagnostic.object_functions(obj)
                                if n == diagnostic.NAME)
            holes = {i for off,_,_ in relocs for i in range(off,off+4)}
            raw = dict(ours_size=len(body), retail_size=len(diagnostic.TARGET),
                       relocations=len(relocs),
                       differences=[dict(offset=hex(i),ours=hex(x),retail=hex(y))
                                    for i,(x,y) in enumerate(zip(body,diagnostic.TARGET))
                                    if i not in holes and x!=y])
            (diagnostic.OUT/(name+'.raw-diff.json')).write_text(json.dumps(raw,indent=2)+'\n')
            if len(body)==len(diagnostic.TARGET):
                row=dict(name=diagnostic.NAME,rva='0x0043003C',size='4054',notes='')
                patch=dict(target_rva=0x43003C,target=diagnostic.TARGET)
                problems=diagnostic.build.body_extent_problems(row,patch,{},obj,[0x43003C,0x431012])
                (diagnostic.OUT/(name+'.extent.json')).write_text(json.dumps(dict(problems=problems),indent=2)+'\n')
            return report

        with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
            for result in pool.map(measure,variants):
                print(json.dumps(result),flush=True)
