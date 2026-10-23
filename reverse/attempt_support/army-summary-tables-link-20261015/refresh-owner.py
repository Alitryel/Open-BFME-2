"""Copy exact generated rows after data_ledger.py --out build/.../data-ledger-current.csv."""
from pathlib import Path
base = Path('build/army-summary-tables-link-20261015')
generated = (base / 'data-ledger-current.csv').read_text().splitlines(keepends=True)
keys = ['0x007E6A64,', '0x007E6A68,']
rows = {key: next(line for line in generated if line.startswith(key)) for key in keys}
assert all(row.split(',')[1] == '4' and ',owned,,1,1' in row for row in rows.values())
p = Path('reverse/data_ledger.csv')
old = p.read_text().splitlines(keepends=True)
assert all(sum(line.startswith(key) for line in old) == 1 for key in keys)
p.write_text(''.join(next((rows[key] for key in keys if line.startswith(key)), line) for line in old))
