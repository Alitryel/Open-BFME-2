import subprocess,sys
from pathlib import Path
out=Path('build/refcount-link-seat');source='Code/Libraries/Source/WWVegas/WW3D2/MeshGeometryCopy.cpp'
commands=[('byte-final',['./build.sh',source]),('definitions',['python3','tools/find_declared_unmatched.py',source]),('classes',['python3','tools/class_gate.py',source]),('variants',['python3','tools/link_check.py','--new-variants',source]),('data',['python3','tools/data_check.py','--enforce',source]),('converged',['python3','tools/data_check.py','--converged',source]),('eh',['python3','tools/eh_verify.py',source,'--json',str(out/'eh.json')]),('placements',['python3','tools/place_bodies.py',source]),('ledger',['python3','tools/check_csv.py']),('whitespace',['git','diff','--check'])]
for label,cmd in commands:
 with (out/(label+'.txt')).open('w') as f:r=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
 print(label,r.returncode,flush=True)
 if r.returncode:print((out/(label+'.txt')).read_text());sys.exit(r.returncode)
with (out/'link-after.txt').open('w') as f:r=subprocess.run(['python3','tools/link_check.py',source],stdout=f,stderr=subprocess.STDOUT)
assert r.returncode==1
print('local link: five residual findings expected; paired proof checks exact delta',flush=True)
