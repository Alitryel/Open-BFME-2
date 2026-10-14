"""Root-run only after bounded --prepare-current on sources.txt and stable tree.
No compile, disk index refresh, or current receipt mutation. In-memory paired preview.
"""
import sys,json,hashlib,subprocess,shutil,csv
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_check,link_census,progress
out=Path('build/link-orchestrator/review/integrated');m=json.loads((out/'manifest.json').read_text());records=m['sources']
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
assert subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip()==m['head'],'HEAD changed: regenerate manifest'
assert sha(link_check.INDEX)==m['index_sha256'],'Index changed: regenerate manifest and proofs'
assert all(len(g['sources'])<=32 for g in m.get('preparation_groups',[]))
# Only strict preparation is bounded32; all explicit objects share one paired proof.
def receipt_matches_object(r):
 p=Path(r['current_object']);meta=json.loads(p.with_suffix('.deps.json').read_text())
 return meta.get('object')==hashlib.md5(p.read_bytes()).hexdigest()
def check_inputs():
 assert sha('reverse/functions.csv')==m['ledger_sha256'],'Ledger changed: regenerate manifest'
 for r in m.get('shared_header_inputs',[])+m.get('dependency_inputs',[])+m.get('verification_input_hashes',[]):
  assert sha(r['path'])==r['sha256'],r['path']+' input changed: regenerate manifest'
 for r in m.get('provenance_snapshots',[]):
  assert sha(r['snapshot'])==r['sha256'],'Provenance snapshot changed'
check_inputs()
for r in records:
 assert receipt_matches_object(r),r['source']+' actualobjectMD5 differs from compiler receipt'
 assert sha(r['source'])==r['source_current_sha256'],r['source']+' changed: regenerate manifest'
 assert sha(r['before_object'])==r['before_object_sha256'],r['source']+' before witness changed'
 command,env=build.compiler_command(Path(r['source']).resolve(),Path(r['current_object']))
 assert build._cmd_fingerprint(command,env)==r['compiler_command_fingerprint'],r['source']+' effective compile inputs changed'
 assert build.compile_is_current(Path(r['source']).resolve(),Path(r['current_object']),strict=True),r['source']+' needs root strict preparation'
object_hashes={r['current_object']:sha(r['current_object']) for r in records}
truth=link_census.RetailTruth(link_census.ledger());sources=[r['source'] for r in records];sizes=link_check.source_bytes(set(sources));objects={}
for label in ('before','after'):
 d=out/label;d.mkdir(exist_ok=True);objects[label]=[]
 for r in records:
  p=d/Path(r['current_object']).name
  shutil.copyfile(r['before_object'] if label=='before' else r['current_object'],p);objects[label].append(p)
result={'head':m['head'],'index_sha256':m['index_sha256'],'kind':'same-index bounded preview; no census or link.exe','sources':{s:{'bytes':sizes[s]} for s in sources}}
for label in ('before','after'):
 index=link_check.load_index();result['index_meta']=index['meta'];link_check.refresh(index,objects[label],truth)
 for s,p in zip(sources,objects[label]):result['sources'][s][label]=link_check.check_object(p,index,truth,s)
gained={s for s,r in result['sources'].items() if any(r['before'].values()) and not any(r['after'].values())}
expected={r['source'] for r in records if r['expected_gain']}
assert gained==expected,{'unexpected':sorted(gained-expected),'missing':sorted(expected-gained)}
start,size=progress.retail_text();image_start,image=progress._text_image();intervals=[]
matched={};notes={}
with open('reverse/functions.csv',newline='',encoding='utf-8') as f:
 for row in csv.DictReader(f):
  if row['status']=='matched' and row['source'] in gained:
   key=(row['name'],row['target_rva']);matched[key]=(int(row['target_size']),row['source']);notes[key]=row['notes']
naked=progress.naked_cpp_rows(matched,{s:Path(s).read_text(encoding='utf-8',errors='replace') for s in gained})
for key,(size_value,source) in matched.items():
 if progress.source_lane(source,notes[key],key in naked) not in progress.DECOMPILED_LANES:continue
 low=max(int(key[1],16),start);high=min(int(key[1],16)+size_value,start+size)
 if low<high:intervals.append((low,high))
result['sum_source_bytes']=sum(sizes[s] for s in gained)
result['unique_newly_clean_bytes']=sum(b-a-image[a-image_start:b-image_start].count(0xcc) for a,b in progress.merge_intervals(intervals))
assert result['unique_newly_clean_bytes']==m['expected_unique_union']
result['publication_threshold']=m.get('publication_threshold',40000)
result['threshold_met']=result['unique_newly_clean_bytes']>=result['publication_threshold']
if '--require-threshold' in sys.argv: assert result['threshold_met'],'Publication requires40,000 unique bytes'
assert sha(link_check.INDEX)==m['index_sha256']
for r in records:
 assert receipt_matches_object(r),r['source']+' actualobjectMD5 differs from compiler receipt'
 assert sha(r['source'])==r['source_current_sha256']
 assert build.compile_is_current(Path(r['source']).resolve(),Path(r['current_object']),strict=True),r['source']+' strict currency moved'
check_inputs()
assert all(sha(p)==h for p,h in object_hashes.items()),'Production objects moved during paired proof'
(out/'paired-proof.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({'sources':len(records),'gained_units':len(gained),'sum':result['sum_source_bytes'],'unique':result['unique_newly_clean_bytes']}))
# Intermediate preview allowed; --require-threshold enforces40,000 before publication.
