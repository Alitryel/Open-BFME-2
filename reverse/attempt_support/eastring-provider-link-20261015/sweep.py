"""Read-only assignment-consumer sweep; run from the repository root."""
import hashlib
import json
import subprocess
import sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_census as lc
import link_check as ck

BASE = Path('build/eastring-provider-link-20261015')
EVIDENCE = Path('reverse/attempt_support/eastring-provider-link-20261015')
PROVIDER = 'Code/Libraries/Source/EA/Apt/AptString/EAStringCConcat.cpp'
CALLER = 'Code/Libraries/Source/Apt/string/EAString.cpp'
ASSIGN = '??4EAStringC@@QAEAAV0@ABV0@@Z'
index_meta = json.loads((BASE / 'index-meta.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == index_meta['sha256']
sources = subprocess.check_output(['rg', '-l', r'operator\s*=\s*\(const EAStringC',
                                   'Code/Libraries/Source'], text=True).splitlines()
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
eligible, skipped = [], []
for source in sources:
    obj = build.obj_path(build.ROOT / source)
    if ck.in_census(index, obj.name) and lc.object_current(build.ROOT / source, obj, allow_fresh=False):
        eligible.append((source, obj))
    else:
        skipped.append(source)
paired, copies = {}, {}
for phase in ('before', 'after'):
    current = ck.load_index()
    cohort = {source: BASE / 'before' / obj.name
              if phase == 'before' and source in (PROVIDER, CALLER) else obj
              for source, obj in eligible}
    ck.refresh(current, list(cohort.values()), truth)
    paired[phase] = {source: ck.check_object(obj, current, truth, source=source)
                     for source, obj in cohort.items()}
    copies[phase] = {source: [body for body in lc.comdat_bodies(obj) if body[0] == ASSIGN]
                     for source, obj in cohort.items()}
new = [(source, kind, name) for source, result in paired['after'].items()
       for kind, names in result.items() for name in names
       if name not in paired['before'][source][kind]]
assert not new
counts = ck.source_bytes(set(paired['after']))
linked = {phase: sum(counts.get(source, 0) for source, result in findings.items() if not any(result.values()))
          for phase, findings in paired.items()}
report = {
 'scope': 'strict-current assignment-declaring consumers only; in-memory legacy-index preview',
 'index': index_meta,
 'current_object_sha256': {source: hashlib.sha256(obj.read_bytes()).hexdigest() for source, obj in eligible},
 'skipped_missing_stale_or_outside_index': skipped,
 'assignment_copies': copies, 'paired_findings': paired,
 'local_linked_bytes': linked, 'new_findings': new, 'closed_strict_gain_claimed': False,
}
(EVIDENCE / 'sweep.json').write_text(json.dumps(report, indent=2) + '\n')
print(f'{len(eligible)} strict-current units, {len(skipped)} skipped; local linked bytes {linked}; no added findings')
