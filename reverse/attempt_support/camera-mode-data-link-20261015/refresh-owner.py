"""Copy one exact tool-generated inventory row; preserve unrelated snapshot rows.
First run: python3 tools/data_ledger.py --out build/camera-mode-data-link-20261015/data-ledger-current.csv
"""
from pathlib import Path
import csv
base=Path('build/camera-mode-data-link-20261015')
current=(base/'data-ledger-current.csv').read_text().splitlines(keepends=True)
rows=[line for line in current if line.startswith('0x009EC290,')]
assert len(rows)==1
r=next(csv.DictReader([current[0],rows[0]]))
assert r['name']=='?BfmeLiveCameraModeNameStorage@@3IA' and r['status']=='owned'
assert r['source']=='Code/GameEngine/Source/Common/Rva007AB85CAtexitInits.cpp'
assert r['defs']=='1' and r['refs']=='3' and r['size']=='4'
p=Path('reverse/data_ledger.csv'); old=p.read_text().splitlines(keepends=True)
assert sum(line.startswith('0x009EC290,') for line in old)==1
p.write_text(''.join(rows[0] if line.startswith('0x009EC290,') else line for line in old))
(base/'generated-owner-row.csv').write_text(current[0]+rows[0])
