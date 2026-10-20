"""Materialize hash-checked controls; optionally run normal byte diagnostics."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
parser = argparse.ArgumentParser()
parser.add_argument('--run', action='store_true', help='compile with explain_mismatch')
parser.add_argument('--case', action='append', default=[])
args = parser.parse_args()
manifest = json.loads((HERE / 'inputs.json').read_text())
out = ROOT / 'build/string-copy-providers-replay/root'
out.mkdir(parents=True, exist_ok=True)
bases = {}
for name, spec in manifest['bases'].items():
    if 'git' in spec:
        text = subprocess.check_output(['git', 'show', spec['git'] + ':' + spec['path']], cwd=ROOT).decode()
    else:
        text = (HERE / spec['file']).read_text()
    text = text.replace('\r\n', '\n')
    assert hashlib.sha256(text.encode()).hexdigest() == spec['sha256'], name
    bases[name] = text
insert = ('insert', '?insertRange@Rva008314E0String@@QAEXPAD00ABUBfmeRangeTag@@@Z', '0x28820', 740)
copy = ('copy', '??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z', '0x179B0', 41)
parents = {
    'owner': ('replace', '?replaceRange@Rva008314E0String@@QAEAAV1@PAD000ABUBfmeRangeTag@@@Z', '0x2B050', 501),
    'v21': ('caller', '?bfmeInsertV21@BfmeStrV21@@QAEPAV1@IPADI@Z', '0x2AB40', 149),
    'v22': ('caller', '?bfmeInsertV22@BfmeStrV22@@QAEPAV1@IPAD@Z', '0x2ABE0', 170),
}
for case in manifest['cases']:
    if args.case and case['case'] not in args.case:
        continue
    lines = bases[case['base']].splitlines(True)
    for edit in reversed(case['edits']):
        lines[edit['start']:edit['end']] = edit['insert'].splitlines(True)
    text = ''.join(lines)
    assert hashlib.sha256(text.encode()).hexdigest() == case['sha256'], case['case']
    source = out / (case['case'] + '.cpp')
    source.write_text(text, newline='\n')
    print('materialized ' + case['case'], flush=True)
    if not args.run:
        continue
    rows = [insert, parents[case['context']], copy]
    if 'worker' in case['case']:
        rows.append(('worker', '?__copy_trivial@_STL@@YAPAXPBX0PAX@Z', '0x179B0', 41))
    for role, symbol, rva, size in rows:
        done = subprocess.run([sys.executable, 'tools/explain_mismatch.py', symbol,
                               '--rva', rva, '--size', str(size), '--source',
                               source.relative_to(ROOT).as_posix(), '--context', '2'],
                              cwd=ROOT, env=dict(os.environ, BFME_OBJSTORE='off'),
                              text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        (out / (case['case'] + '.' + role + '.log')).write_text(done.stdout)
        print(done.stdout, flush=True)
        if done.returncode:
            raise SystemExit(done.returncode)
