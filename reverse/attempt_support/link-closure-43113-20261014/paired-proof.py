"""Root-run readonly paired proof AFTER ordinary native gates (and strict prep for final mode).
--ordinary-preview is explicitly non-final. --require-threshold enforces40000.
"""
import sys,json,csv,hashlib,shutil,subprocess
from pathlib import Path
sys.path.insert(0,'tools');import build,link_check as ck,link_census as lc,progress
evidence=Path(__file__).resolve().parent
out=Path('build/link-orchestrator/review/final-reproduction');out.mkdir(parents=True,exist_ok=True)
plan=json.loads((evidence/'manifest.json').read_text());app=json.loads((evidence/'expected-sources.json').read_text());rows=plan['sources']
# COFF binaries are intentionally not committed. Supply the genuine archived pre-edit objects.
if '--object-archive' in sys.argv:
 archive=Path(sys.argv[sys.argv.index('--object-archive')+1])
 for r in rows:r['before_object']=str(archive/(r['before_sha256']+'.obj'))
ordinary='--ordinary-preview' in sys.argv;require='--require-threshold' in sys.argv;assert not(ordinary and require),'Finalthresholdproof requiresstrictreceipts'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest();head=subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip();actions={r['source']:r for r in app['write_actions']};inventory={};index_hash=sha(ck.INDEX)
before_revision=plan['planning_head']
if '--before-revision' in sys.argv:before_revision=sys.argv[sys.argv.index('--before-revision')+1]
before_revision=subprocess.check_output(['git','rev-parse','--verify',before_revision+'^{commit}'],text=True).strip()
inputs=['reverse/functions.csv','reverse/symbols.csv','reverse/flag_overrides.csv','reverse/data_converged.csv','tools/build.py','tools/link_check.py','tools/link_census.py','tools/progress.py','reference/shims/bfme_vertexmaterial_link/dx8wrapper.h'];input_hashes={p:sha(p) for p in inputs};assert all(sha(p)==h for p,h in plan['header_inputs'].items()),'Header changed after manifest freeze'
# Snapshot every actual receipt dependency without compiling or modifying receipts.
for r in rows:
 meta=json.loads(Path(r['current_object']).with_suffix('.deps.json').read_text())
 for dep in meta.get('deps',{}):
  if Path(dep).is_file():input_hashes.setdefault(dep,sha(dep))
objects_hash={r['current_object']:sha(r['current_object']) for r in rows}
def validate_sources_and_receipts():
 for r in rows:
  expected=actions[r['source']]['after_sha256'] if r['source'] in actions else r['source_before_sha256'];assert sha(r['source'])==expected,r['source']+' unreviewedsourcechange'
  # Check the explicit historical parent even when HEAD already contains the committed candidate.
  parent=subprocess.check_output(['git','show',before_revision+':'+r['source']]);assert hashlib.sha256(parent).hexdigest()==r['source_before_sha256'],r['source']+' incomingparentchanged; refreshbeforewitness'
  assert sha(r['before_object'])==r['before_sha256'],r['source']+' beforewitnessmoved'
  obj=Path(r['current_object']);meta=json.loads(obj.with_suffix('.deps.json').read_text());assert meta.get('object')==hashlib.md5(obj.read_bytes()).hexdigest(),r['source']+' actualOBJMD5!=receipt'
  cmd,env=build.compiler_command(Path(r['source']).resolve(),obj);assert build._cmd_fingerprint(cmd,env)==r['compiler_fingerprint'],r['source']+' flag/inputcommandchanged'
  assert build.compile_is_current(Path(r['source']).resolve(),obj,strict=not ordinary,inventory_cache=inventory),r['source']+' staleordinary/strictreceipt'
validate_sources_and_receipts();truth=lc.RetailTruth(lc.ledger());result={'HEAD':head,'before_revision':before_revision,'kind':'ordinaryreadonlypreviewNOTstrictfinal' if ordinary else 'strict-currentboundedpairedproofnotcensus/link.exe','index_sha256':index_hash,'sources':{r['source']:{} for r in rows},'inputs':input_hashes}
for label in ['before','after']:
 d=out/('proof-'+label);d.mkdir(exist_ok=True);objects=[]
 for r in rows:
  p=d/Path(r['current_object']).name;shutil.copyfile(r['before_object'] if label=='before' else r['current_object'],p);objects.append(p)
 idx=ck.load_index();assert all(p.name in idx['objects'] for p in objects),'Unseenprovider requiresofficialindexedproof, no injection';result['index_meta']=idx['meta'];ck.refresh(idx,objects,truth)
 for r,p in zip(rows,objects):result['sources'][r['source']][label]=ck.check_object(p,idx,truth,r['source'])
gained={s for s,r in result['sources'].items() if any(r['before'].values()) and not any(r['after'].values())};expected={r['source'] for r in rows if r['expected_gain']};result['missing_expected']=sorted(expected-gained);result['unexpected']=sorted(gained-expected);assert gained==expected,result['missing_expected']
matched={};notes={}
with open('reverse/functions.csv',newline='',encoding='utf8') as f:
 for r in csv.DictReader(f):
  if r['status']=='matched' and r['source'] in gained:k=(r['name'],r['target_rva']);matched[k]=(int(r['target_size']),r['source']);notes[k]=r['notes']
naked=progress.naked_cpp_rows(matched,{s:Path(s).read_text(encoding='utf8',errors='replace') for s in gained});start,size=progress.retail_text();ib,image=progress._text_image();intervals=[]
for k,(z,s) in matched.items():
 if progress.source_lane(s,notes[k],k in naked) not in progress.DECOMPILED_LANES:continue
 a=max(int(k[1],16),start);b=min(int(k[1],16)+z,start+size)
 if a<b:intervals.append((a,b))
result['unique_newly_clean_bytes']=sum(b-a-image[a-ib:b-ib].count(0xcc) for a,b in progress.merge_intervals(intervals));assert result['unique_newly_clean_bytes']==plan['independent_projected_union'];result['gained_units']=len(gained);result['threshold_met']=result['unique_newly_clean_bytes']>=40000
validate_sources_and_receipts();assert ordinary or build._inventory_cache_still_current(inventory),'Includeinventorychanged';assert sha(ck.INDEX)==index_hash and all(sha(p)==h for p,h in input_hashes.items());assert all(sha(p)==h for p,h in objects_hash.items());assert subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip()==head
(out/('ordinary-paired-proof.json' if ordinary else 'strict-paired-proof.json')).write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'gains':len(gained),'unique':result['unique_newly_clean_bytes'],'strict':not ordinary,'threshold_met':result['threshold_met']}));assert not require or result['threshold_met'],'Below40000: preparationonly'
