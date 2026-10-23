from pathlib import Path
import csv,sys
sys.path.insert(0,'tools')
import data_ledger as dl
scratch=Path('build/banner-global-link-20261015')
current=dl.LEDGER.read_text(); (scratch/'data-ledger-before.csv').write_text(current)
generated=(scratch/'generated-data-ledger.csv').read_text().splitlines()
rows=[s for s in generated if s.startswith('0x009FE32C,')]
assert len(rows)==1
assert '?TheBannerUI@@3PAVBannerUI@@A' in rows[0]
old=[s for s in current.splitlines() if s.startswith('0x009FE32C,')]
assert len(old)==1
dl.LEDGER.write_text(current.replace(old[0],rows[0]))
print('Refreshed only the tool-generated 0x009FE32C row; unrelated generated changes omitted.')
