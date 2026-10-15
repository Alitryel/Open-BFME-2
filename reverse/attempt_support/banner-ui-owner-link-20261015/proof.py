"""Bounded COFF and legacy-link comparison; snapshots remain under build/."""
import collections, copy, hashlib, json, shutil, struct, sys
from pathlib import Path
ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import build, link_check as ck, link_census as lc
OUT = ROOT / 'build/banner-ui-owner-link-20261015'
OLD = '?g_00DFE32C@@3PAVBannerUI@@A'
OLD_VIEW = '?g_00DFE32C@@3PAVRva00217194BannerUI@@A'
NEW = '?TheBannerUI@@3PAVBannerUI@@A'
PROVIDER = 'Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/BannerUI.cpp'
def rename(name):
    return NEW if name in (OLD, OLD_VIEW) else name

def sections(data):
    symbols = {s['index']: s for s in lc._coff_symbols(data)}
    count = struct.unpack_from('<H', data, 2)[0]
    optional = struct.unpack_from('<H', data, 16)[0]
    raw = []
    for i in range(count):
        h = 20 + optional + 40 * i
        name = data[h:h + 8].rstrip(b'\0').decode('latin1')
        size, pointer, reloc = struct.unpack_from('<III', data, h + 16)
        nr = struct.unpack_from('<H', data, h + 32)[0]
        flags = struct.unpack_from('<I', data, h + 36)[0]
        body = data[pointer:pointer + size] if pointer else None
        raw.append((name, flags, size, body, reloc, nr))
    result = collections.Counter()
    for name, flags, size, body, reloc, nr in raw:
        if name.startswith('.debug') or name == '.drectve':
            continue
        if name == '.sxdata':
            # COFF symbol indices change when the unused wrapper disappears.
            body = tuple(rename(symbols[t[0]]['name']) for t in struct.iter_unpack('<I', body))
        else:
            body = body.hex() if body is not None else None
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            if s['storage'] in (2, 105):
                label = ('external', rename(s['name']))
            else:
                # Compare the actual local target section and offset, rather
                # than MSVC's automatically renumbered $L/$T label.
                assert s['section'] > 0
                target_name, target_flags, target_size, target_body, _, _ = raw[s['section'] - 1]
                label = ('local', target_name, target_flags, target_size,
                         target_body.hex() if target_body is not None else None, s['value'])
            refs.append((where, kind, label))
        result[(name, flags, size, body, tuple(refs))] += 1
    return result

def bindings(data):
    return {(rename(s['name']),s['storage'],s['section']>0,s['value'] if s['section']<=0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2,105)}

def directives(data):
    result=[]
    for i in range(struct.unpack_from('<H',data,2)[0]):
        h=20+struct.unpack_from('<H',data,16)[0]+40*i
        if data[h:h+8].rstrip(b'\0')==b'.drectve':
            n,at=struct.unpack_from('<II',data,h+16);result.append(data[at:at+n])
    return result

paths = json.loads((OUT/'sources.json').read_text())
ctx = json.loads((OUT/'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
rank = ck.link_rank(lc.ledger())
objects, proof = {}, {}
for source in paths:
    obj = build.obj_path(ROOT/source)
    before = OUT/'before'/obj.name
    assert lc.object_current(ROOT/source, obj, allow_fresh=False), source
    a, b = before.read_bytes(), obj.read_bytes()
    sa,sb=sections(a),sections(b)
    ba,bb=bindings(a),bindings(b)
    if source == PROVIDER:
        # The only extra allocation is the new zero-initialized singleton slot.
        extra=sb-sa
        assert not sa-sb, (source, list((sa-sb).elements()))
        assert sum(extra.values()) == 1, list(extra.elements())
        sec=list(extra.elements())[0]
        assert sec[0]=='.bss' and sec[2]==4 and sec[3] in (None, '00000000') and sec[4]==(),sec
        assert bb-ba == {(NEW,2,True,0)} and ba-bb == {(NEW,2,False,0)},(ba-bb,bb-ba)
    else:
        assert sa == sb, (source, list((sa-sb).elements())[:2],list((sb-sa).elements())[:2])
        assert ba == bb, (source,ba-bb,bb-ba)
    assert directives(a) == directives(b), source
    syma, symb = list(lc._coff_symbols(a)), list(lc._coff_symbols(b))
    assert any(s['name'] in (OLD,OLD_VIEW) for s in syma),source
    assert not any(s['name'] in (OLD,OLD_VIEW) for s in symb),source
    assert any(s['name']==NEW for s in symb),source
    previous = {}
    for name, digest, _, verdict in lc.object_facts(before, truth)[0]:
        previous.setdefault(name, set()).add(digest)
    assert not ck.new_variants(obj,index,truth,previous,rank), source
    proof[source] = {'strict_receipt_current':True,
        'source_sha256':hashlib.sha256((ROOT/source).read_bytes()).hexdigest(),
        'object_before_sha256':hashlib.sha256(a).hexdigest(),
        'object_after_sha256':hashlib.sha256(b).hexdigest(),
        'nondebug_content_equal_after_singleton_binding_repair':True,
        'directives_unchanged':True,'new_four_byte_zero_owner':source==PROVIDER}
    objects[source] = (before,obj)
    after = OUT/'after';after.mkdir(exist_ok=True)
    shutil.copy2(obj,after/obj.name)
    shutil.copy2(obj.with_suffix('.deps.json'),after/obj.with_suffix('.deps.json').name)
results = {}
for phase,n in [('before',0),('after',1)]:
    local=copy.deepcopy(index)
    ck.refresh(local,[objects[s][n] for s in paths],truth)
    results[phase]={s:ck.check_object(objects[s][n],local,truth,s) for s in paths}
gain=0
sizes=ck.source_bytes(set(paths))
for source in paths:
    before,after=results['before'][source],results['after'][source]
    expected=copy.deepcopy(before)
    old=OLD_VIEW if source==PROVIDER else OLD
    assert old in expected['unresolved'],(source,before)
    expected['unresolved'].remove(old)
    assert expected==after,(source,before,after)
    if any(before.values()) and not any(after.values()):gain+=sizes.get(source,0)
    print(source, sum(map(len,before.values())), '->',sum(map(len,after.values())), 'findings')
report={'context':ctx,'index_meta':index['meta'],'objects':proof,'paired_results':results,
        'removed_unresolved_findings':len(paths),'legacy_linked_bytes_gain':gain,
        'new_authored_cpp_bytes':0,'closed_strict_gain_claimed':False,
        'existing_bytes_affected':sizes}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: ten undefined singleton bindings removed; legacy linked byte gain',gain)
