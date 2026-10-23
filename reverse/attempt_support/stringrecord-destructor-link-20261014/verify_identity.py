import sys,json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3];sys.path.insert(0,str(ROOT/'tools'))
import allowed_symbols as a,dup_defs as d,build
OUT=ROOT/'build/stringrecord-destructor-link-20261014'
sources=(OUT/'sources.txt').read_text().splitlines();rows=a.census.ledger();truth=a.census.RetailTruth(rows)
objs=a.link_order(rows);changed={str(build.obj_path(ROOT/s)):OUT/'before'/build.obj_path(ROOT/s).name for s in sources[1:3]}
reports={}
for phase in ('before','after'):
 cohort=[Path(changed.get(str(o),o)) if phase=='before' else Path(o) for o in objs]
 defs=a.definitions(cohort);scoped=set(changed.values()) if phase=='before' else set(changed)
 names={n for n,copies in defs.items() if any(str(c[0]) in {str(x) for x in scoped} for c in copies)}
 sub={n:defs[n] for n in names};debt=d.debt(d.analyse(rows,sub,truth));new=debt-d.read_baseline()
 reports[phase]={'outside_baseline_definition_keys':sorted(new),'all_definition_debt_keys':sorted(debt)}
assert set(reports['after']['outside_baseline_definition_keys'])<=set(reports['before']['outside_baseline_definition_keys'])
(OUT/'identity-proof.json').write_text(json.dumps(reports,indent=2)+'\n')
print('No added shadow definition finding keys; before',len(reports['before']['outside_baseline_definition_keys']),'after',len(reports['after']['outside_baseline_definition_keys']))
