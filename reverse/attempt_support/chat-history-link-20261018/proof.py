"""Reproduce paired legacy preview using strict-current objects and saved baseline."""
import hashlib, json, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_check as ck, link_census as lc
BASE = Path('build/seat8-chat')
OUT = Path(__file__).parent
paths = [
 'Code/Libraries/Source/WWVegas/WWLib/stlport_vector_stringrecord_5ddd40_clear.cpp',
 'Code/GameEngine/Source/Common/LANChatHistory.cpp',
 'Code/GameEngine/Source/Common/Rva00381C82AddChatText.cpp',
 'Code/GameEngine/Source/Common/Rva007AEA2CArrayInits.cpp',
]
def sha(path): return hashlib.sha256(path.read_bytes()).hexdigest()
renames = {
 '?g_00E022F8@@3PAV?$vector@UBfmeStringRecord005DDD40@@V?$allocator@UBfmeStringRecord005DDD40@@@_STL@@@_STL@@A': '?g_chatHistoryVectors@@3PAIA',
 '?g_00E02310@@3VRva0038188BList@@A': '?g_00E02310@@3VRva003818B0List@@A',
}
objects = {s: build.obj_path(build.ROOT/s) for s in paths}
index_hash = sha(ck.INDEX)
proofs = {}
for source, obj in objects.items():
    old = BASE/'before'/obj.name
    assert lc.object_current(build.ROOT/source, obj, allow_fresh=False)
    before = {n:(d,z) for n,d,z in lc.comdat_bodies(old)}
    after = {n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
    assert not after.keys()-before.keys()
    changed=[]
    for name in after:
        a, ar = build.read_object_symbol_bytes(old, name)
        b, br = build.read_object_symbol_bytes(obj, name)
        assert a == b, (source,name,'body changed')
        ar = [(at,kind,renames.get(target,target)) for at,kind,target in ar]
        assert ar == br, (source,name,'unexpected relocation change',ar,br)
        if before[name] != after[name]: changed.append(name)
    removed = before.keys()-after.keys()
    expected = 22 if 'AddChatText' in source else 1 if 'LANChatHistory' in source else 0
    assert len(removed) == expected, (source,removed)
    proofs[source] = dict(before_sha256=sha(old),after_sha256=sha(obj),
        retained_comdats=len(after), removed_comdats={n:before[n] for n in sorted(removed)},
        retained_bytes_identical=True, relocations_identical_after_explicit_renames=True,
        renamed_relocations_in=changed)
truth = lc.RetailTruth(lc.ledger())
paired = {}
for phase in ('before','after'):
    objs = {s:BASE/'before'/o.name if phase=='before' else o for s,o in objects.items()}
    index = ck.load_index()
    ck.refresh(index,list(objs.values()),truth)
    paired[phase] = {s:ck.check_object(o,index,truth,source=s) for s,o in objs.items()}
core = ('unresolved','duplicates','comdat','addresses','selected')
def clean(row): return all(not row[k] for k in core)
sizes = ck.source_bytes(set(paths))
for s in paths: assert not clean(paired['before'][s])
assert [clean(paired['after'][s]) for s in paths] == [True,True,True,False]
assert len(paired['after'][paths[-1]]['unresolved']) == 10
before_bytes = sum(sizes[s] for s in paths if clean(paired['before'][s]))
after_bytes = sum(sizes[s] for s in paths if clean(paired['after'][s]))
assert (before_bytes,after_bytes)==(0,269)
assert sha(ck.INDEX)==index_hash
report = dict(measurement=index['meta'], index_sha256=index_hash, object_proofs=proofs,
    explicit_global_renames=renames, paired_link=paired,
    legacy_predicted_linked_nonpadding_bytes=dict(before=before_bytes,after=after_bytes,gain=after_bytes-before_bytes),
    source_bytes=sizes,self_strict_current=True,closed_strict_gain_unmeasured=True)
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: 14 strict-current rows; retained COMDAT bytes and normalized relocations unchanged; paired legacy +269 B, three units newly clean; initializer still blocked.')
