"""tools/name_evidence.py on a miniature tree: which evidence counts as proof,
which is only a hint, and that no protected or real name is ever proposed."""
import csv
import io
import json
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import name_evidence as ne  # noqa: E402

BASE = ne.IMAGE_BASE
ZH_CPP = ne.ZH_ROOT + "/GeneralsMD/Code/GameEngine/Source/Widget.cpp"

FUNCTIONS = """name,export_rva,target_rva,target_size,source,status,notes
?rva00401000@Widget@@QAEXXZ,,0x00401000,40,Code/Game/Widget.cpp,matched,
?rva00402000@Widget@@QAEXXZ,,0x00402000,40,Code/Game/Widget.cpp,matched,
?Rva00403000@@YAXXZ,,0x00403000,40,Code/Game/Free.cpp,matched,
?draw@Widget@@QAEXXZ,,0x00404000,40,Code/Game/Widget.cpp,matched,
?Rva00405000@@YAXXZ,,0x00405000,40,Code/Game/Free.cpp,matched,
?get@Rva00406000Box@@QAEHXZ,,0x00406000,8,Code/Game/Box.cpp,matched,
?set@Rva00406000Box@@QAEXH@Z,,0x00407000,8,Code/Game/Box.cpp,matched,
?size@Rva00406000Box@@QAEHXZ,,0x00408000,8,Code/Game/Box.cpp,matched,
?rva00409000@Gadget@@QAEXXZ,,0x00409000,60,Code/Game/Gadget.cpp,matched,
?Rva0040A000@@YAXXZ,,0x0040A000,60,Code/Game/Free.cpp,matched,
?rva0040B000@Spawner@@SA?AW4NameKeyType@@XZ,,0x0040B000,69,Code/Game/SpawnerPoolKey.cpp,matched,
?Rva0040C000@@YAXXZ,,0x0040C000,60,Code/Game/Free.cpp,matched,
?Rva0040D000@@YAXXZ,,0x0040D000,60,Code/Game/Free.cpp,matched,
?rva0040E000@Panel@@QAEXXZ,,0x0040E000,60,Code/Game/Panel.cpp,matched,
?rva0040F000@Panel@@QAEXXZ,,0x0040F000,60,Code/Game/Panel.cpp,matched,
?Rva00410000@@YAXXZ,,0x00410000,60,Code/Game/Free.cpp,matched,
?flushQueue@@YAXXZ,,0x00411000,60,Code/Game/Free.cpp,matched,
?Rva00412000@@YAXXZ,,0x00412000,60,Code/gen_asm/Gen.asm,matched,
?get@Rva00413000Pad@@QAEHXZ,,0x00413000,8,Code/Game/Pad.cpp,matched,
?get@Rva00414000Pad@@QAEHXZ,,0x00414000,8,Code/Game/Pad.cpp,matched,
?pushobject@@YAXXZ,,0x00415000,6,Code/Libraries/Source/Lua/lapi.c,matched,vendored=lua-5.0
?rva00423000@Panel@@QAEXXZ,,0x00423000,60,Code/Game/Panel.cpp,matched,
"""
# 0x401000/0x402000 Widget: two placeholder methods; WB proves one (score 5)
# and only hints the other (score 2).
# 0x403000 free: name carried by two WB bodies -> hint.
# 0x404000 Widget::draw is real: never proposed.
# 0x405000 free: export at the address -> protected.
# 0x406000-0x408000 Rva00406000Box: class proven at two addresses -> canonical class.
# 0x409000 Gadget (real) vs WB class Gizmo -> function hint.
# 0x40A000 / 0x40C000 / 0x40D000 free: zh specific, zh trivial, bfme1.
# 0x40E000/0x40F000 Panel: one body, one name collision and a conflict.
WB_FUNCTIONS = [
    {"va": 0x1000, "names": ["Widget::resize"], "name_files": [["Widget::resize", "c:\\x\\Widget.cpp"]]},
    {"va": 0x1100, "names": ["Widget::paint"], "name_files": [["Widget::paint", "c:\\x\\Widget.cpp"]]},
    {"va": 0x1200, "names": ["flushAll"], "name_files": []},
    {"va": 0x1210, "names": ["flushAll"], "name_files": []},
    {"va": 0x1300, "names": ["TrayBox::get"], "name_files": []},
    {"va": 0x1310, "names": ["TrayBox::set"], "name_files": []},
    {"va": 0x1320, "names": ["TrayBox::size"], "name_files": []},
    {"va": 0x1400, "names": ["Gizmo::spin"], "name_files": []},
    {"va": 0x1500, "names": ["Panel::layout"], "name_files": []},
    {"va": 0x1600, "names": ["Panel::refresh"], "name_files": []},
    {"va": 0x1610, "names": ["Panel::redraw"], "name_files": []},
    {"va": 0x1700, "names": ["exportedThing"], "name_files": []},
    {"va": 0x1800, "names": ["PadView::get"], "name_files": []},
    {"va": 0x1810, "names": ["PadView::other"], "name_files": []},
]
PAIRS = [  # (rva, wb_va, wb_name, score)
    (0x401000, 0x1000, "Widget::resize", 5), (0x402000, 0x1100, "Widget::paint", 2),
    (0x403000, 0x1200, "flushAll", 9), (0x405000, 0x1700, "exportedThing", 9),
    (0x406000, 0x1300, "TrayBox::get", 6), (0x407000, 0x1310, "TrayBox::set", 6),
    (0x408000, 0x1320, "TrayBox::size", 1), (0x409000, 0x1400, "Gizmo::spin", 8),
    (0x40E000, 0x1500, "Panel::layout", 7), (0x40F000, 0x1600, "Panel::refresh", 7),
    (0x40F000, 0x1610, "Panel::redraw", 7), (0x404000, 0x1100, "Widget::paint", 1),
    (0x413000, 0x1800, "PadView::get", 9),
]


def write(root, rel, text):
    path = root / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def leads_csv(pairs):
    out = io.StringIO()
    w = csv.writer(out, lineterminator="\n")
    w.writerow(["target_rva", "current_name", "current_kind", "wb_name", "wb_file", "score", "evidence"])
    for rva, _, name, score in pairs:
        w.writerow([f"0x{rva:08X}", "", "PLACEHOLDER", name, "C:\\x\\Widget.cpp", f"{score:.4f}", "callgraph"])
    return out.getvalue()


@pytest.fixture
def tree(tmp_path):
    root = tmp_path
    write(root, "reverse/functions.csv", FUNCTIONS)
    write(root, "reverse/exports.csv", "ordinal,rva,target_rva,section,kind,name\n"
                                       "1,0x00405000,,.text,code,?Rva00405000@@YAXXZ\n")
    write(root, "reverse/name_tiers.csv", "name,target_rva,name_tier,evidence\n")
    write(root, "reverse/data_converged.csv", "address,name,evidence\n")
    write(root, "reverse/module_factory_registrations.csv", "index,name\n0,SpawnerModule\n")
    write(root, "reverse/canonical_classes.csv", "class,header,notes\n")
    write(root, "reverse/name_basis.csv", "kind,old,new,basis,evidence,source,rva\n")
    write(root, "reverse/wb_name_leads.csv", leads_csv(PAIRS))
    write(root, "build/wb/wb_functions.jsonl", "".join(json.dumps(f) + "\n" for f in WB_FUNCTIONS))
    write(root, "build/wb/matches_full.jsonl", "".join(json.dumps(
        {"gd_va": rva + BASE, "wb_va": wb, "wb_name": name, "score": score}) + "\n"
        for rva, wb, name, score in PAIRS))
    write(root, "reverse/string_xrefs.tsv", "\n".join([
        "Widget::rva, bad",                              # not a placeholder target
        "Gadget::rva00409111 nope\t0x409000",            # placeholder donor word: dropped
        "SpecialAbilityGiveUpgrade\t0x40c000",           # identifier string, one placeholder ref
        "SharedIdentifierString\t0x40c000,0x40d000",     # two refs: no hint
        "Spawner\t0x40b000",                             # pool string
        "Panel::flush, queue overflow\t0x423000",        # message prefix, class agrees
        "Panel::Label\t0x40f000",                        # bare label
    ]) + "\n")
    write(root, ZH_CPP, "#include \"Widget.h\"\n\nvoid Widget::nothing() {}\nvoid Cleaner::sweepAll()\n{\n}\n")
    write(root, "build/zh_sweep/match.json", json.dumps([
        {"sym": "?sweepAll@@YAXXZ", "source": ZH_CPP, "size": 60, "relocs": 3, "rva": 0x40A000,
         "bucket": "exact-unique-claimed"},
        {"sym": "?tidy@@YAXXZ", "source": ZH_CPP, "size": 12, "relocs": 0, "rva": 0x40C000,
         "bucket": "exact-unique-claimed"},
        {"sym": "?Widget@@YAXXZ", "source": ZH_CPP, "size": 60, "relocs": 1, "bucket": "no-placement"},
    ]))
    write(root, "build/bfme1_sweep/match.json", json.dumps({"records": [
        {"name": "?drainQueue@@YAXXZ", "source": "game/X.cpp", "bfme1_rva": 0x7000, "bfme2_rva": 0x40D000,
         "size": 60, "icf_twins": [], "calls": [1], "strings": [], "imports": []},
        {"name": "?pumpEvents@@YAXXZ", "source": "game/X.cpp", "bfme1_rva": 0x7100, "bfme2_rva": 0x410000,
         "size": 60, "icf_twins": [], "calls": [1], "strings": [], "imports": []},
    ]}))
    write(root, ne.BFME1_EA, "rva,kind,value,route,basis\n0x00007000,name,drainQueue,wb2-run,strong\n")
    return root


def run(root, **kw):
    candidates, notes, skips = ne.generate(root, sweep_dirs=("build",), **kw)
    return candidates, notes, skips


def find(candidates, **match):
    return [c for c in candidates if all(getattr(c, k) == v for k, v in match.items())]


def test_wb_assert_with_score_is_canonical(tree):
    cands, _, _ = run(tree)
    [c] = find(cands, key="?rva00401000@Widget@@QAEXXZ")
    assert (c.kind, c.current, c.candidate, c.evidence_kind, c.strength) == \
        ("function", "rva00401000", "resize", "wb-assert", "canonical")
    assert c.detail["basis"] == "canonical:wb"
    assert "0x00401000" in c.detail["evidence"] and c.detail["score"] == "5"


def test_wb_low_score_is_hint(tree):
    cands, _, _ = run(tree)
    [c] = find(cands, key="?rva00402000@Widget@@QAEXXZ")
    assert c.strength == "hint" and "score 2 < 4" in c.detail["weak"] and "basis" not in c.detail


def test_wb_name_carried_by_two_bodies_is_hint(tree):
    cands, _, _ = run(tree)
    [c] = find(cands, key="?Rva00403000@@YAXXZ")
    assert c.strength == "hint" and "2 WB bodies carry the name" in c.detail["weak"]


def test_real_and_protected_names_never_proposed(tree):
    cands, _, skips = run(tree)
    assert not find(cands, key="?draw@Widget@@QAEXXZ")          # real name
    assert not find(cands, key="?Rva00405000@@YAXXZ")           # retail export
    assert not find(cands, current="flushQueue")
    assert not [c for c in cands if c.key.startswith("?pushobject")]
    assert skips["wb-assert: function protected name"] == 1
    assert skips["wb-assert: function real name"] == 1


def test_name_basis_canonical_is_protected(tree):
    write(tree, "reverse/name_basis.csv", "kind,old,new,basis,evidence,source,rva\n"
                                          "function,x,rva00401000,canonical:wb,e,s,0x00401000\n")
    cands, _, _ = run(tree)
    assert not find(cands, current="rva00401000")


def test_inferred_name_takes_canonical_but_not_hint(tree):
    write(tree, "reverse/functions.csv", FUNCTIONS.replace("?rva00401000@Widget", "?grow@Widget")
          .replace("?rva00402000@Widget", "?shrink@Widget"))
    write(tree, "reverse/name_basis.csv", "kind,old,new,basis,evidence,source,rva\n"
                                          "function,a,grow,inferred,agree:1,s,0x00401000\n"
                                          "function,b,shrink,inferred,agree:2,s,0x00402000\n")
    cands, _, skips = run(tree)
    assert [c.strength for c in find(cands, current="grow")] == ["canonical"]
    assert not find(cands, current="shrink")
    assert skips["wb-assert: hint over an inferred name"] == 1


def test_class_needs_two_proven_addresses(tree):
    cands, _, _ = run(tree)
    [c] = find(cands, kind="class", key="Rva00406000Box")
    assert (c.candidate, c.strength, c.detail["basis"]) == ("TrayBox", "canonical", "canonical:wb")
    [pad] = find(cands, kind="class", key="Rva00413000Pad")
    assert pad.strength == "hint" and "proven address" in pad.detail["weak"]


def test_class_that_already_exists_is_a_merge_not_a_rename(tree):
    write(tree, "reverse/functions.csv", FUNCTIONS + "?other@TrayBox@@QAEXXZ,,0x00420000,8,Code/Game/T.cpp,matched,\n")
    cands, _, _ = run(tree)
    [c] = find(cands, kind="class", key="Rva00406000Box")
    assert c.strength == "hint" and "already exists" in c.detail["weak"]


def test_real_class_disagreeing_with_donor_demotes(tree):
    cands, _, _ = run(tree)
    [c] = find(cands, key="?rva00409000@Gadget@@QAEXXZ")
    assert c.strength == "hint" and "Gadget differs from donor class Gizmo" in c.detail["caution"]
    assert not find(cands, kind="class", key="Gadget")


def test_conflicting_sources_demote_and_one_body_one_name(tree):
    cands, _, _ = run(tree)
    panel = find(cands, key="?rva0040F000@Panel@@QAEXXZ")
    assert {c.candidate for c in panel} >= {"refresh", "redraw"}
    assert all(c.strength == "hint" for c in panel)
    assert all("conflict" in c.detail for c in panel if c.evidence_kind == "wb-assert")
    write(tree, "reverse/functions.csv", FUNCTIONS + "?layout@Panel@@QAEXXZ,,0x00421000,8,Code/Game/Panel.cpp,matched,\n")
    cands, _, _ = run(tree)
    [c] = find(cands, key="?rva0040E000@Panel@@QAEXXZ", evidence_kind="wb-assert")
    assert c.strength == "hint" and "one body, one name" in c.detail["caution"]


def test_zh_specific_body_cites_a_zero_hour_line(tree):
    cands, notes, _ = run(tree)
    [c] = find(cands, key="?Rva0040A000@@YAXXZ")
    assert (c.candidate, c.evidence_kind, c.strength) == ("sweepAll", "zh-body", "hint")  # free fn: no Class:: line
    assert any("zh:" in n for n in notes)


def test_zh_member_body_canonical_and_trivial_hint(tree):
    write(tree, "reverse/functions.csv", FUNCTIONS + "?rva00422000@Cleaner@@QAEXXZ,,0x00422000,60,Code/G/C.cpp,matched,\n")
    data = json.loads((tree / "build/zh_sweep/match.json").read_text())
    data.append({"sym": "?sweepAll@Cleaner@@QAEXXZ", "source": ZH_CPP, "size": 60, "relocs": 2, "rva": 0x422000,
                 "bucket": "exact-unique-claimed"})
    write(tree, "build/zh_sweep/match.json", json.dumps(data))
    cands, _, _ = run(tree)
    [c] = find(cands, key="?rva00422000@Cleaner@@QAEXXZ")
    assert c.strength == "canonical" and c.detail["basis"] == "canonical:zh"
    assert c.detail["evidence"].startswith(ZH_CPP + ":4 ")
    [t] = find(cands, key="?Rva0040C000@@YAXXZ", evidence_kind="zh-body")
    assert t.strength == "hint" and "trivial body" in t.detail["weak"]


def test_bfme1_needs_ea_or_zero_hour_support(tree):
    cands, _, _ = run(tree)
    [c] = find(cands, key="?Rva0040D000@@YAXXZ", evidence_kind="bfme1-body")
    assert c.strength == "canonical" and c.detail["evidence"].startswith(ne.BFME1_EA + ":2 ")
    [h] = find(cands, key="?Rva00410000@@YAXXZ")
    assert h.strength == "hint" and "without EA evidence or a Zero Hour same-body record" in h.detail["weak"]


def bfme1_cleaner(tree, with_zh_body):
    """A BFME 1 same-body record ?sweepAll@Cleaner at 0x424000, whose name
    Zero Hour spells (ZH_CPP line 4); optionally a Zero Hour same-body record
    at the address naming the same donor."""
    write(tree, "reverse/functions.csv", FUNCTIONS + "?rva00424000@Cleaner@@QAEXXZ,,0x00424000,60,Code/G/C.cpp,matched,\n")
    data = json.loads((tree / "build/bfme1_sweep/match.json").read_text())
    data["records"].append({"name": "?sweepAll@Cleaner@@QAEXXZ", "source": "game/C.cpp", "bfme1_rva": 0x7200,
                            "bfme2_rva": 0x424000, "size": 60, "icf_twins": [], "calls": [1], "strings": [],
                            "imports": []})
    write(tree, "build/bfme1_sweep/match.json", json.dumps(data))
    if with_zh_body:
        zh = json.loads((tree / "build/zh_sweep/match.json").read_text())
        zh.append({"sym": "?sweepAll@Cleaner@@QAEXXZ", "source": ZH_CPP, "size": 60, "relocs": 2,
                   "rva": 0x424000, "bucket": "exact-unique-claimed"})
        write(tree, "build/zh_sweep/match.json", json.dumps(zh))


def test_bfme1_zero_hour_spelling_alone_is_a_hint(tree):
    """Review fix-2 finding 4: a Zero Hour line spelling BFME 1's ledger name
    shows the name exists, not that this body is that function."""
    bfme1_cleaner(tree, with_zh_body=False)
    cands, _, _ = run(tree)
    [c] = find(cands, key="?rva00424000@Cleaner@@QAEXXZ", evidence_kind="bfme1-body")
    assert c.strength == "hint" and "basis" not in c.detail and not c.detail.get("evidence")
    assert c.detail["zh_spelling"] == ZH_CPP + ":4"
    assert ne.proof(tree, "bfme1", "function", "rva00424000", "sweepAll", 0x424000)


def test_bfme1_with_an_agreeing_zero_hour_body_is_canonical(tree):
    bfme1_cleaner(tree, with_zh_body=True)
    cands, _, _ = run(tree, kinds=("bfme1",))                  # zh lane off: its records still count
    [c] = find(cands, key="?rva00424000@Cleaner@@QAEXXZ", evidence_kind="bfme1-body")
    assert c.strength == "canonical" and c.detail["evidence"].startswith(ZH_CPP + ":4 same-body BFME 1")
    assert ne.proof(tree, "bfme1", "function", "rva00424000", "sweepAll", 0x424000) == []


def test_proof_is_the_lane_grading(tree):
    """Review fix-2 finding 3: rename.py's canonical check asks this grading."""
    assert ne.proof(tree, "wb", "function", "rva00401000", "resize", 0x00401000) == []
    weak = ne.proof(tree, "wb", "function", "rva00402000", "paint", 0x00402000)
    assert weak and "score 2 < 4" in weak[0]
    assert ne.proof(tree, "wb", "function", "rva00401000", "resize", 0x00402000)      # another address
    assert ne.proof(tree, "wb", "class", "Rva00406000Box", "TrayBox") == []
    assert ne.proof(tree, "wb", "class", "Rva00413000Pad", "PadView")
    assert ne.proof(tree, "string", "function", "x", "y", 1)                        # not graded here


def test_bfme1_folded_twins_are_hint(tree):
    data = json.loads((tree / "build/bfme1_sweep/match.json").read_text())
    data["records"][0]["icf_twins"] = ["?drainQueue@@YAXXZ", "?emptyBuffer@@YAXXZ"]
    write(tree, "build/bfme1_sweep/match.json", json.dumps(data))
    cands, _, _ = run(tree)
    [c] = find(cands, key="?Rva0040D000@@YAXXZ", evidence_kind="bfme1-body")
    assert c.strength == "hint" and "folded" in c.detail["weak"]


def test_missing_sweep_cache_is_a_note(tree):
    (tree / "build/zh_sweep/match.json").unlink()
    (tree / "build/bfme1_sweep/match.json").unlink()
    cands, notes, _ = run(tree)
    assert any(n.startswith("zh: no zh_sweep") for n in notes)
    assert any(n.startswith("bfme1: no bfme1_sweep") for n in notes)
    assert not find(cands, evidence_kind="zh-body")


def test_strings(tree):
    cands, _, _ = run(tree)
    [s] = find(cands, evidence_kind="string-self", key="?rva00423000@Panel@@QAEXXZ")
    assert (s.candidate, s.strength, s.detail["basis"]) == ("flush", "canonical", "canonical:string")
    assert "0x00423000" in s.detail["evidence"]
    [label] = find(cands, evidence_kind="string-self", key="?rva0040F000@Panel@@QAEXXZ")
    assert label.strength == "hint" and "bare label" in label.detail["weak"]
    hints = find(cands, evidence_kind="string-hint")
    assert [(h.key, h.candidate) for h in hints] == [("?Rva0040C000@@YAXXZ", "SpecialAbilityGiveUpgrade")]
    assert not find(cands, candidate="rva00409111")


def test_poolkey_is_hint_with_class_confirmation(tree):
    cands, _, _ = run(tree)
    [p] = find(cands, evidence_kind="poolkey")
    assert (p.candidate, p.strength, p.detail["class_confirmed"]) == ("getModuleNameKey", "hint", "string_xrefs")


def test_hint_only_kinds_never_canonical_and_generated_ignored(tree):
    cands, _, _ = run(tree)
    for c in cands:
        if c.evidence_kind in ne.HINT_ONLY:
            assert c.strength == "hint"
        if c.strength == "canonical":
            assert c.detail["basis"] == ne.PROOF_BASIS[c.evidence_kind] and c.detail["evidence"]
    assert not find(cands, key="?Rva00412000@@YAXXZ")


def test_main_writes_tsv(tree, capsys):
    assert ne.main(["--root", str(tree), "--out", "build/out.tsv"]) == 0
    lines = (tree / "build/out.tsv").read_text().splitlines()
    assert lines[0].split("\t") == list(ne.COLUMNS)
    assert all(len(line.split("\t")) == len(ne.COLUMNS) for line in lines)
    first = lines[1].split("\t")
    assert first[6] == "canonical"
    assert "candidate(s)" in capsys.readouterr().out


def test_unknown_kind_is_an_error(tree):
    with pytest.raises(SystemExit):
        ne.main(["--root", str(tree), "--kinds", "wb,psychic"])


@pytest.mark.skipif(not (ne.ROOT / "reverse/wb_name_leads.csv").exists(), reason="no real tree")
def test_real_tree_smoke():
    tree = ne.Tree(ne.ROOT)
    cands, _, _ = ne.generate(ne.ROOT, kinds=("wb", "string", "poolkey"), sweep_dirs=("build",))
    assert cands
    for c in cands:
        assert c.current not in tree.protected_words
        if c.strength == "canonical":
            assert c.evidence_kind in ne.PROOF_BASIS
            assert ne.rename.is_placeholder(c.current, c.kind) or c.current in tree.inferred


# ---------------------------------------------------------------- vtable slots
VT_ROWS = """??_GShape@@UAEPAXI@Z,,0x00429000,20,Code/Game/Shape.cpp,matched,
??_GCircle@@UAEPAXI@Z,,0x0042A000,20,Code/Game/Circle.cpp,matched,
?draw@Shape@@UAEXXZ,,0x00430000,40,Code/Game/Shape.cpp,matched,
?area@Shape@@UAEHXZ,,0x00431000,40,Code/Game/Shape.cpp,matched,
?rva00432000@Circle@@UAEHXZ,,0x00432000,40,Code/Game/Circle.cpp,matched,
?rva00433000@Rva00433000Sq@@UAEHXZ,,0x00433000,40,Code/Game/Sq.cpp,matched,
?rva00434000@Circle@@UAEXXZ,,0x00434000,40,Code/Game/Circle.cpp,matched,
?rva00435000@Lonely@@UAEXXZ,,0x00435000,40,Code/Game/Lonely.cpp,matched,
?rva00436000@Tri@@UAEHXZ,,0x00436000,40,Code/Game/Tri.cpp,matched,
?spin@Circle@@UAEXXZ,,0x00437000,40,Code/Game/Circle.cpp,matched,
?rva00438000@Folded@@UAEHXZ,,0x00438000,40,Code/Game/Folded.cpp,matched,
__purecall,,0x00440000,6,Code/Libraries/crt.lib,matched,
"""
VT_LEDGER = """address,size,section,kind,name,source,status,names,defs,refs
0x007C0000,16,.rdata,vtable,??_7Shape@@6B@,,literal,,0,1
0x007C0010,16,.rdata,vtable,??_7Circle@@6B@,,literal,,0,1
0x007C0020,12,.rdata,vtable,??_7Rva00433000Sq@@6B@,,literal,,0,1
0x007C0030,8,.rdata,vtable,??_7Lonely@@6B@,,literal,,0,1
0x007C0040,12,.rdata,vtable,??_7Tri@@6B@,,literal,,0,1
0x007C0050,12,.rdata,vtable,??_7Folded@@6B@,,literal,??_7Folded@@6B@;??_7Other@@6B@,0,1
"""
VT_SLOTS = {
    "Shape": [0x429000, 0x430000, 0x431000, 0x440000],
    "Circle": [0x42A000, 0x437000, 0x432000, 0x434000],
    "Rva00433000Sq": [0x429000, 0x430000, 0x433000],
    "Lonely": [0x429000, 0x435000],
    "Tri": [0x429000, 0x429000, 0x436000],
    "Folded": [0x429000, 0x430000, 0x438000],
}
ZH_SHAPE_H = ne.ZH_ROOT + "/GeneralsMD/Code/GameEngine/Include/Shape.h"


@pytest.fixture
def vtree(tree):
    with (tree / "reverse/functions.csv").open("a", encoding="utf-8") as handle:
        handle.write(VT_ROWS)
    write(tree, "reverse/data_ledger.csv", VT_LEDGER)
    write(tree, ZH_SHAPE_H, "// class Circle : public Lonely {\n"
                            "class Shape\n{\npublic:\n\tvirtual void draw(); // virtual int bogus(\n"
                            "\tvirtual int area() { return 0; }\n\tvirtual void pure() = 0;\n};\n"
                            "class Circle : public Shape\n{\n\tvirtual void spin();\n};\n")
    write(tree, "Code/Game/Tri.h", "class Tri : public Shape\n{\n};\n")
    write(tree, "Code/gen_asm/Lonely.h", "class Lonely : public Shape\n{\n};\n")
    return tree


def vrun(root):
    return ne.generate(root, kinds=("vtable",), slots=VT_SLOTS)


def test_vtable_override_from_zero_hour_hierarchy(vtree):
    cands, notes, _ = vrun(vtree)
    [c] = find(cands, key="?rva00432000@Circle@@UAEHXZ")
    assert (c.current, c.candidate, c.evidence_kind, c.strength) == ("rva00432000", "area", "vtable-slot", "hint")
    assert c.detail["slot"] == 2 and c.detail["base"] == "Shape::area" and c.detail["base_via"] == "Zero Hour header"
    assert c.detail["zh_virtual"] == ZH_SHAPE_H + ":6" and "basis" not in c.detail
    assert any("vtable: 5 named vftables" in n for n in notes)


def test_vtable_base_from_inherited_body_and_own_declaration(vtree):
    cands, _, _ = vrun(vtree)
    [sq] = find(cands, key="?rva00433000@Rva00433000Sq@@UAEHXZ")
    assert sq.candidate == "area" and sq.detail["base_via"] == "slot 1 ?draw@Shape@@UAEXXZ"
    [tri] = find(cands, key="?rva00436000@Tri@@UAEHXZ")
    assert tri.candidate == "area" and tri.detail["base_via"] == "BFME 2 source declaration"


def test_vtable_skips(vtree):
    cands, _, skips = vrun(vtree)
    assert not find(cands, key="?rva00434000@Circle@@UAEXXZ")      # base slot is __purecall
    assert not find(cands, key="?rva00435000@Lonely@@UAEXXZ")      # gen_ declaration ignored
    assert not find(cands, key="?rva00438000@Folded@@UAEHXZ")      # folded table
    assert not find(cands, candidate="draw") and not find(cands, key="?spin@Circle@@UAEXXZ")
    assert skips["vtable-slot: base slot is a pure-virtual stub"] == 1
    assert skips["vtable-slot: no known base class"] == 1
    assert len(cands) == 3


def test_vtable_slots_need_this_trees_image(vtree):
    cands, notes, _ = ne.generate(vtree, kinds=("vtable",))
    assert not cands and any("game.dat is not this tree's" in n for n in notes)


def test_zh_class_parse_ignores_comments(vtree):
    bases, virtuals = ne.zh_classes(ne.Tree(vtree))
    assert bases == {"Circle": "Shape"}
    assert set(virtuals["Shape"]) == {"draw", "area", "pure"} and set(virtuals["Circle"]) == {"spin"}


# ------------------------------------------- pure base slots: Zero Hour order
# Unit's slot 2 is pure in retail; Zero Hour declares ~, update, kind, kill, so
# Tank's placeholder there is `kind` (anchored by update and kill, 2 apart in
# both). Ship's retail table has a BFME virtual between its anchors -> refused.
# Crate has nothing named above the pure slot -> refused.
OR_ROWS = """??_GUnit@@UAEPAXI@Z,,0x00450000,20,Code/Game/Unit.cpp,matched,
?update@Unit@@UAEXXZ,,0x00451000,40,Code/Game/Unit.cpp,matched,
?kill@Unit@@UAEXXZ,,0x00452000,40,Code/Game/Unit.cpp,matched,
??_GTank@@UAEPAXI@Z,,0x00453000,20,Code/Game/Tank.cpp,matched,
?rva00454000@Tank@@UAEHXZ,,0x00454000,40,Code/Game/Tank.cpp,matched,
??_GShip@@UAEPAXI@Z,,0x00455000,20,Code/Game/Ship.cpp,matched,
?sail@Ship@@UAEXXZ,,0x00456000,40,Code/Game/Ship.cpp,matched,
?dock@Ship@@UAEXXZ,,0x00457000,40,Code/Game/Ship.cpp,matched,
?rva00458000@Raft@@UAEXXZ,,0x00458000,40,Code/Game/Raft.cpp,matched,
?open@Crate@@UAEXXZ,,0x00459000,40,Code/Game/Crate.cpp,matched,
?rva0045A000@Box@@UAEXXZ,,0x0045A000,40,Code/Game/Box.cpp,matched,
__purecall,,0x00460000,6,Code/Libraries/crt.lib,matched,
"""
OR_LEDGER = """address,size,section,kind,name,source,status,names,defs,refs
0x007D0000,16,.rdata,vtable,??_7Unit@@6B@,,literal,,0,1
0x007D0010,16,.rdata,vtable,??_7Tank@@6B@,,literal,,0,1
0x007D0020,20,.rdata,vtable,??_7Ship@@6B@,,literal,,0,1
0x007D0040,20,.rdata,vtable,??_7Raft@@6B@,,literal,,0,1
0x007D0060,12,.rdata,vtable,??_7Crate@@6B@,,literal,,0,1
0x007D0070,12,.rdata,vtable,??_7Box@@6B@,,literal,,0,1
"""
PURE = 0x460000
OR_SLOTS = {
    "Unit": [0x450000, 0x451000, PURE, 0x452000],
    "Tank": [0x453000, 0x451000, 0x454000, 0x452000],
    "Ship": [0x455000, 0x456000, PURE, PURE, 0x457000],
    "Raft": [0x455000, 0x456000, 0x458000, PURE, 0x457000],
    "Crate": [PURE, 0x459000, PURE],
    "Box": [PURE, 0x459000, 0x45A000],
}
ZH_UNIT_H = ne.ZH_ROOT + "/GeneralsMD/Code/GameEngine/Include/Unit.h"
ZH_UNIT_OLD_H = ne.ZH_ROOT + "/Generals/Code/GameEngine/Include/Unit.h"


@pytest.fixture
def otree(tree):
    with (tree / "reverse/functions.csv").open("a", encoding="utf-8") as handle:
        handle.write(OR_ROWS)
    write(tree, "reverse/data_ledger.csv", OR_LEDGER)
    write(tree, ZH_UNIT_H,
          "class Unit\n{\npublic:\n\tvirtual ~Unit();\n\tvirtual void update();\n"
          "\tvirtual int kind() = 0;\n\tvirtual void kill();\n};\n"
          "class Tank : public Unit\n{\n\tvirtual int kind();\n};\n"
          "class Ship\n{\n\tvirtual ~Ship();\n\tvirtual void sail();\n\tvirtual void steer() = 0;\n"
          "\tvirtual void dock();\n};\n"
          "class Raft : public Ship\n{\n\tvirtual void steer();\n};\n"
          "class Crate\n{\n\tvirtual void open();\n\tvirtual void close() = 0;\n};\n"
          "class Box : public Crate\n{\n};\n")
    # the older game's copy differs; GeneralsMD's definition wins
    write(tree, ZH_UNIT_OLD_H, "class Unit\n{\n\tvirtual void other();\n};\n")
    return tree


def test_pure_base_slot_named_from_zero_hour_order(otree):
    cands, _, skips = ne.generate(otree, kinds=("vtable",), slots=OR_SLOTS)
    [c] = find(cands, key="?rva00454000@Tank@@UAEHXZ")
    assert (c.current, c.candidate, c.evidence_kind, c.strength) == ("rva00454000", "kind", "vtable-order", "hint")
    assert c.detail["base"] == "Unit::kind" and c.detail["zh_virtual"] == ZH_UNIT_H + ":6"
    assert "slot 1 update and slot 3 kill" in c.detail["zh_order"] and "basis" not in c.detail
    assert "vtable-order" in ne.HINT_ONLY and "vtable-order" not in ne.PROOF_BASIS
    assert not find(cands, key="?rva00458000@Raft@@UAEXXZ")
    assert not find(cands, key="?rva0045A000@Box@@UAEXXZ")
    assert skips["vtable-order: a virtual was inserted or dropped between the anchors"] == 1
    assert skips["vtable-order: no named slot above it to anchor the Zero Hour order"] == 1
    assert len(cands) == 1


def test_zh_slot_order_layout(tree):
    write(tree, ZH_UNIT_H,
          "class A\n{\n\tvirtual ~A();\n\tvirtual void f(int);\n\tvirtual void g();\n\tvirtual void f();\n};\n"
          "class B : public A\n{\n\tvirtual void g();\n\tvirtual void h();\n\tvirtual ~B();\n};\n"
          "class C : public Missing\n{\n\tvirtual void k();\n};\n")
    write(tree, ZH_UNIT_OLD_H, "class A\n{\n\tvirtual void z();\n};\n")
    t = ne.Tree(tree)
    ne.zh_classes(t)
    # overloads grouped at the first declaration; overrides keep the base slot
    assert ne.zh_slot_order(t, "A") == ["~", "f", "f", "g"]
    assert ne.zh_slot_order(t, "B") == ["~", "f", "f", "g", "h"]
    assert ne.zh_slot_order(t, "C") is None
