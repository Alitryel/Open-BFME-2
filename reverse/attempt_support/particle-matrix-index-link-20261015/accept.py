"""Run bounded acceptance checks; full verification runners are not invoked."""
import json
import subprocess
from pathlib import Path

OUT = Path('build/particle-matrix-index-link-20261015')
SOURCE = 'Code/GameEngine/Source/GameClient/System/FXParticleSystem/RenderObjectDrawModuleDoParticles.cpp'
commands = [
    ('byte', ['./build.sh', SOURCE]),
    ('definitions', ['python3', 'tools/find_declared_unmatched.py', SOURCE]),
    ('classes', ['python3', 'tools/class_gate.py', SOURCE]),
    ('variants', ['python3', 'tools/link_check.py', '--new-variants', SOURCE]),
    ('data', ['python3', 'tools/data_check.py', '--enforce', SOURCE]),
    ('converged', ['python3', 'tools/data_check.py', '--converged', SOURCE]),
    ('eh', ['python3', 'tools/eh_verify.py', SOURCE]),
    ('placements', ['python3', 'tools/place_bodies.py', SOURCE]),
    ('ledger', ['python3', 'tools/check_csv.py']),
    ('link', ['python3', 'tools/link_check.py', SOURCE]),
    ('proof', ['python3', 'reverse/attempt_support/particle-matrix-index-link-20261015/proof.py']),
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
