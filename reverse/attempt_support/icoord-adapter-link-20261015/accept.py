"""Run bounded acceptance checks; full verification runners are not invoked."""
import json
import subprocess
from pathlib import Path

OUT = Path('build/icoord-adapter-link-20261015')
SOURCES = ['Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeMeleeAmoeba.cpp', 'Code/GameEngine/Source/Common/Rva00366AE3Add.cpp']
commands = [
    ('byte', ['./build.sh', *SOURCES]),
    ('definitions', ['python3', 'tools/find_declared_unmatched.py', *SOURCES]),
    ('classes', ['python3', 'tools/class_gate.py', *SOURCES]),
    ('variants', ['python3', 'tools/link_check.py', '--new-variants', *SOURCES]),
    ('data', ['python3', 'tools/data_check.py', '--enforce', *SOURCES]),
    ('converged', ['python3', 'tools/data_check.py', '--converged', *SOURCES]),
    ('eh', ['python3', 'tools/eh_verify.py', *SOURCES]),
    ('placements', ['python3', 'tools/place_bodies.py', *SOURCES]),
    ('ledger', ['python3', 'tools/check_csv.py']),
    ('link', ['python3', 'tools/link_check.py', *SOURCES]),
    ('proof', ['python3', 'reverse/attempt_support/icoord-adapter-link-20261015/proof.py']),
    ('whitespace', ['git', 'diff', '--check']),
]
results = []
for label, command in commands:
    completed = subprocess.run(command, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    (OUT / (label + '.txt')).write_text(completed.stdout)
    results.append({'check': label, 'command': command, 'exit': completed.returncode,
                    'output': completed.stdout})
    print(label, completed.returncode, flush=True)
    if completed.returncode:
        print(completed.stdout)
        raise SystemExit(completed.returncode)
(OUT / 'checks.json').write_text(json.dumps(results, indent=2) + '\n')
