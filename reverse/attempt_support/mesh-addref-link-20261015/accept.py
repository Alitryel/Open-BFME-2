import json, subprocess, sys
from pathlib import Path
OUT = Path('build/mesh-addref-link-20261015')
sources = json.loads((OUT / 'before.json').read_text())['sources']
changed = sources
commands = [
    ('byte-after', ['./build.sh', *changed]),
    ('definitions-after', ['python3', 'tools/find_declared_unmatched.py', *changed]),
    ('classes-after', ['python3', 'tools/class_gate.py', *changed]),
    ('variants-after', ['python3', 'tools/link_check.py', '--new-variants', *changed]),
    ('data-after', ['python3', 'tools/data_check.py', '--enforce', *changed]),
    ('converged-after', ['python3', 'tools/data_check.py', '--converged', *changed]),
    ('eh-after', ['python3', 'tools/eh_verify.py', *changed, '--json', str(OUT / 'eh-after.json')]),
    ('placements-after', ['python3', 'tools/place_bodies.py', *changed]),
    ('ledger-after', ['python3', 'tools/check_csv.py']),
    ('whitespace-after', ['git', 'diff', '--check']),
]
for label, command in commands:
    with (OUT / (label + '.txt')).open('w') as log:
        done = subprocess.run(command, stdout=log, stderr=subprocess.STDOUT)
    print(label, done.returncode, flush=True)
    if done.returncode:
        print((OUT / (label + '.txt')).read_text())
        sys.exit(done.returncode)
with (OUT / 'link-after.txt').open('w') as log:
    done = subprocess.run(['python3','tools/link_check.py',*sources],stdout=log,stderr=subprocess.STDOUT)
assert done.returncode == 1  # Background and sibling blockers remain; paired proof checks exact differences.
print('local-link preview: expected background/sibling blockers remain; inspect paired proof',flush=True)
