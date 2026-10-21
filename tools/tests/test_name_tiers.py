"""reverse/name_tiers.csv's name_basis.csv tiers (tools/allowed_symbols.py --tiers).

A name tools/rename.py recorded canonical stays in the evidence tier with its
evidence kind; one recorded inferred gets the `inferred` tier; nothing a
record says overrides the placeholder, vendored, lib-member or export verdict.
"""
import csv
import io
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import allowed_symbols as allowed  # noqa: E402

HEADER = "kind,old,new,basis,evidence,source,rva\n"
WALL = "?ClassifyWall@Pathfinder@@QAEXPAVObject@@_N@Z"
SPAN = "?spanOf@Widget@@QAEHXZ"


def bases(tmp_path, *lines):
    path = tmp_path / "name_basis.csv"
    path.write_text(HEADER + "".join(line + "\n" for line in lines), encoding="utf-8")
    return allowed.Bases(path)


def tier(name, b=None, rva=0x1000, notes="", source="Code/x.cpp", exports=None):
    row = {"name": name, "notes": notes, "source": source, "target_rva": f"0x{rva:08X}"}
    return allowed.name_tier(row, exports or {}, b)


def test_canonical_record_is_evidence_with_its_kind(tmp_path):
    b = bases(tmp_path, f"function,?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z,{WALL},canonical:wb,"
                        f"\"WB 0x12DB220 asserts Pathfinder::ClassifyWall\",Code/a.cpp,0x0052F63F")
    assert tier(WALL, b, rva=0x0052F63F) == ("evidence", "wb")


def test_inferred_record_is_inferred_tier_with_evidence_kind(tmp_path):
    b = bases(tmp_path, f"function,?rva00001000@Widget@@QAEHXZ,{SPAN},inferred,agree:a1b2,Code/w.cpp,0x00001000")
    assert tier(SPAN, b) == ("inferred", "agree")


def test_global_record_counts_like_a_function(tmp_path):
    b = bases(tmp_path, "global,?g_00DFE9E0@@3HA,?g_count@@3HA,inferred,agree:x,Code/g.cpp,0x00001000")
    assert tier("?g_count@@3HA", b) == ("inferred", "agree")


def test_record_at_another_address_does_not_apply(tmp_path):
    b = bases(tmp_path, f"function,?rva00002000@Widget@@QAEHXZ,{SPAN},inferred,agree:a,Code/w.cpp,0x00002000")
    assert tier(SPAN, b, rva=0x1000) == ("unverified", "")
    assert tier(SPAN, b, rva=0x2000) == ("inferred", "agree")


def test_unrecorded_name_stays_unverified(tmp_path):
    b = bases(tmp_path)
    assert tier("?update@Foo@@UAEXXZ", b) == ("unverified", "")
    assert tier("?update@Foo@@UAEXXZ") == ("unverified", "")     # no bases at all: old behaviour


def test_missing_ledger_is_empty(tmp_path):
    b = allowed.Bases(tmp_path / "absent.csv")
    assert (b.spellings, b.classes) == ({}, {})


def test_restored_record_drops_the_inferred_spelling(tmp_path):
    b = bases(tmp_path,
              f"function,?rva00001000@Widget@@QAEHXZ,{SPAN},inferred,agree:a,Code/w.cpp,0x00001000",
              f"function,{SPAN},?rva00001000@Widget@@QAEHXZ,restored,revert:a wrong,Code/w.cpp,0x00001000")
    assert tier(SPAN, b) == ("unverified", "")
    assert tier("?rva00001000@Widget@@QAEHXZ", b) == ("address", "placeholder")


def test_carry_row_keeps_the_carried_tier(tmp_path):
    moved = "?ClassifyWall@PathPlanner@@QAEXPAVObject@@_N@Z"
    b = bases(tmp_path,
              f"function,?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z,{WALL},canonical:wb,wb,Code/a.cpp,0x0052F63F",
              f"carry,{WALL},{moved},canonical:wb,scope renamed by x,Code/a.cpp,0x0052F63F")
    assert tier(moved, b, rva=0x0052F63F) == ("evidence", "wb")


def test_inferred_class_marks_rows_spelling_the_class_token(tmp_path):
    b = bases(tmp_path, "class,Rva0040ADDD,AwardRecordView,inferred,agree:c1,Code/aw.cpp,")
    assert tier("?count@AwardRecordView@@QBEHXZ", b) == ("inferred", "class-agree")
    assert tier("?add@List@@QAEXPAVAwardRecordView@@@Z", b) == ("inferred", "class-agree")
    # a longer token that only contains the word is another class
    assert tier("?count@AwardRecordViewer@@QBEHXZ", b) == ("unverified", "")


def test_exact_record_wins_over_class_taint(tmp_path):
    name = "?get@AwardRecordView@@QBEHXZ"
    b = bases(tmp_path, "class,Rva0040ADDD,AwardRecordView,inferred,agree:c1,Code/aw.cpp,",
              f"function,?rva00001000@AwardRecordView@@QBEHXZ,{name},canonical:string,0x1000,Code/aw.cpp,0x00001000")
    assert tier(name, b) == ("evidence", "string")


def test_later_canonical_class_record_clears_the_inferred_word(tmp_path):
    b = bases(tmp_path, "class,Rva0040ADDD,AwardRecordView,inferred,agree:c1,Code/aw.cpp,",
              "class,AwardRecordView,AwardRecord,canonical:module,module,Code/aw.cpp,")
    assert b.classes == {}
    assert tier("?count@AwardRecord@@QBEHXZ", b) == ("unverified", "")


def test_path_and_member_records_never_name_rows(tmp_path):
    b = bases(tmp_path, "file,Code/Rva1.cpp,Code/Widget_spanOf.cpp,inferred,mechanical:x,Code/Widget_spanOf.cpp,",
              "member,Widget::m_0C,Widget::m_span,inferred,agree:m,Code/w.cpp,")
    assert b.spellings == {} and b.classes == {}


def test_records_never_override_the_checkable_verdicts(tmp_path):
    b = bases(tmp_path,
              "function,a,?Rva00401000Get@@YAXXZ,inferred,agree:a,Code/x.cpp,0x00001000",
              "function,b,_compress,inferred,agree:b,Code/x.cpp,0x00001000",
              "function,c,?Exported@@YAXXZ,inferred,agree:c,Code/x.cpp,0x00001000")
    assert tier("?Rva00401000Get@@YAXXZ", b) == ("address", "placeholder")
    assert tier("_compress", b, notes="vendored=zlib-1.1.4") == ("evidence", "vendored")
    assert tier("?Exported@@YAXXZ", b, exports={0x1000: {"?Exported@@YAXXZ"}}) == ("evidence", "export")


def test_tiers_text_lists_inferred_rows(tmp_path):
    b = bases(tmp_path, f"function,?rva00001000@Widget@@QAEHXZ,{SPAN},inferred,agree:a1,Code/w.cpp,0x00001000")
    rows = [{"name": SPAN, "notes": "", "source": "Code/w.cpp", "target_rva": "0x00001000"},
            {"name": "?other@Widget@@QAEHXZ", "notes": "", "source": "Code/w.cpp", "target_rva": "0x00001010"}]
    got = list(csv.reader(io.StringIO(allowed.tiers_text(rows, b))))
    assert got == [["name", "target_rva", "name_tier", "evidence"], [SPAN, "0x00001000", "inferred", "agree"]]
