import ast,hashlib,json,shlex,struct,sys
from collections import Counter
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_census as lc,link_check as ck
base=Path('build/audio-list-bind-20261025')
source='Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp'
old=base/'before.obj';new=build.obj_path(build.ROOT/source)
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
index_hash=sha(ck.INDEX)
truth=lc.RetailTruth(lc.ledger())
a={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
b={n:(d,z) for n,d,z in lc.comdat_bodies(new)}
assert a.keys()==b.keys()
changed=[n for n in a if a[n]!=b[n]]
assert len(changed)==1 and '_M_create_node@?$list@VPlayingAudioRef@@' in changed[0],changed
name=changed[0]
def entries(p):return {s['name']:(s,body,relocs,d,z) for s,body,relocs,d,z in lc._comdat_sections(p.read_bytes())}
def simple(e):return e[1].hex(),[(at,k,r['name']) for at,k,r in e[2]],e[4]
old_node=entries(old)[name];new_node=entries(new)[name]
owner_source='Code/Libraries/Source/WWVegas/WWLib/stlport_list_create_nodes.cpp'
owner=build.obj_path(build.ROOT/owner_source)
native=next(e for n,e in entries(owner).items() if '_M_create_node@?$list@VRva0036CA00Str@@' in n)
assert simple(new_node)==simple(native)
assert old_node[1]==new_node[1] and old_node[4]==new_node[4]==34
assert len(new_node[2])==2
for (at,k,r),(nat,nk,nr) in zip(old_node[2],new_node[2]):
 assert (at,k)==(nat,nk)
 if r['name']!=nr['name']:
  assert '_Construct@VPlayingAudioRef@@' in r['name'] and '_Construct@VRva0036CA00Str@@' in nr['name']
# Normalize symbol indexes and EH labels when comparing ordinary sections.
tree=ast.parse(Path('reverse/attempt_support/audio-ref-setter-link-20261015/proof.py').read_text())
functions=[x for x in tree.body if isinstance(x,ast.FunctionDef) and x.name in ('sha','normalized')]
code=ast.unparse(ast.Module(body=functions,type_ignores=[]))
code=code.replace("assert n not in omitted, 'removed helper has an incoming nondebug relocation'",'')
# The deleted declaration-only fallback alias is the sole directive change.
code=code.replace("if section['name'].startswith('.debug') or n in omitted:","if section['name'].startswith('.debug') or section['name']=='.drectve' or n in omitted:")
ns=dict(hashlib=hashlib,struct=struct,build=build,Counter=Counter);exec(code,ns)
left=ns['normalized'](old,{name});right=ns['normalized'](new,{name})
assert left==right

def directives(p):
 d,secs,_=build._object_layout(str(p),p.stat().st_mtime_ns,p.stat().st_size)
 return set(shlex.split(''.join(d[s['raw_pointer']:s['raw_pointer']+s['raw_size']].decode('ascii') for s in secs if s['name']=='.drectve')))
x,y=directives(old),directives(new)
removed=x-y
assert not y-x and removed=={'/alternatename:??$_Construct@VPlayingAudioRef@@V1@@_STL@@YAXPAVPlayingAudioRef@@ABV1@@Z=?_Construct@_STL@@YAXPAVPlayingAudioRef@@ABV2@@Z'}
import data_check as dc
rows=dc.source_rows([source]);data_ledger=dc.dl.load();row_object=build.row_object;data_findings={}
for label,obj in [('before',old),('after',new)]:
 build.row_object=lambda r:obj
 unread=[];data_findings[label]=dc.findings(dc.object_facts(rows,unread),data_ledger)
 assert not unread,unread
build.row_object=row_object
assert data_findings['before']==data_findings['after']
paired={}
for label,obj in [('before',old),('after',new)]:
 idx=ck.load_index()
 # Keep original object basename so each phase replaces the same census slot.
 dest=base/label/new.name;dest.parent.mkdir(exist_ok=True);dest.write_bytes(obj.read_bytes())
 ck.refresh(idx,[dest],truth)
 paired[label]=ck.check_object(dest,idx,truth,source)
assert paired['before']['unresolved']==['??$_Construct@VPlayingAudioRef@@V1@@_STL@@YAXPAVPlayingAudioRef@@ABV1@@Z']
assert not any(v for k,v in paired['after'].items() if k!='unreferenced_differs'),paired
expected=dict(paired['before']);expected['unresolved']=[]
assert paired['after']==expected
for label in paired: paired[label].pop('unreferenced_differs')
amount=ck.source_bytes({source})[source]
assert amount==41647,amount
assert sha(ck.INDEX)==index_hash
result=dict(source=source,base_commit='8d4b145924',index_sha256=index_hash,index_commit='ce1b975697',index_rules='retail-truth-4',before_object_sha256=sha(old),after_object_sha256=sha(new),retained_external_comdats=len(a),changed_comdats=changed,node_size=34,node_bytes_identical=True,unchanged_other_nondebug_sections=sum(left.values()),removed_directives=sorted(removed),data_findings=data_findings,node_relocation_retarget='owning Rva0036CA00Str _Construct at 0x2393AA',native_node_owner=owner_source,native_node_byte_and_relocation_twin=True,paired=paired,legacy_predicted_gain=amount,closed_strict_gain_unmeasured=True)
(base/'object-proof.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result,indent=2))
