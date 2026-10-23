#!/usr/bin/env python3
"""Fast unit tests for fleet partitioning and dead-end memory."""

import tempfile
import json
import subprocess
from pathlib import Path

import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import list_naked_candidates as queue


def candidate(index):
    return {
        "symbol": f"?candidate{index}@@YAXXZ",
        "path": f"Code/candidate{index}.cpp",
        "line": index,
        "signature": f"void candidate{index}()",
    }


def main():
    candidates = [candidate(index) for index in range(100)]
    shards = [queue.apply_shard(candidates, (index, 6)) for index in range(6)]
    identities = [{item["symbol"] for item in shard} for shard in shards]
    assert sum(len(shard) for shard in shards) == len(candidates)
    assert set().union(*identities) == {item["symbol"] for item in candidates}
    for left in range(6):
        for right in range(left + 1, 6):
            assert identities[left].isdisjoint(identities[right])

    with tempfile.TemporaryDirectory() as temporary:
        log = Path(temporary) / "dead.tsv"
        log.write_text("?candidate7@@YAXXZ\tno-match\tverified dead end\n"
                       "?candidate8@@YAXXZ\tother\tnot terminal\n",
                       encoding="utf-8")
        assert queue.logged_no_match([log]) == {"?candidate7@@YAXXZ"}
    proc = subprocess.run(
        [sys.executable, str(Path(__file__).resolve().parents[1] /
                             "list_naked_candidates.py"),
         "Code/GameEngine/Source/Common/FireWeaponUpdateDestructorThunk.cpp", "--json"],
        cwd=Path(__file__).resolve().parents[2], capture_output=True, text=True,
        timeout=60, check=True,
    )
    payload = json.loads(proc.stdout)
    assert isinstance(payload["candidates"], list)
    assert all("bytes" not in item and "bytes_hex" in item for item in payload["candidates"])
    print("PASS naked queue: stable shards and no-match filtering")


if __name__ == "__main__":
    main()


# --- collectable tests -----------------------------------------------------
# Everything above runs only under `python3 tools/tests/test_list_naked_candidates.py`:
# with no test_-prefixed function and no conftest.py, pytest collects NOTHING
# from this file, so a suite run would go green while the code below is broken.

import re  # noqa: E402
import pytest  # noqa: E402
import re_log  # noqa: E402


def test_partial_survives_the_legacy_three_field_filter(tmp_path, monkeypatch):
    """The silent blocking path: logged_no_match reads only the 3-field shape
    and has no latest-wins, so before the fix a stale `no-match` out-voted the
    `partial` that released the candidate and it was never served again."""
    log = tmp_path / "reverse" / "re_attempts.log"
    log.parent.mkdir(parents=True, exist_ok=True)
    log.write_text("?Sym@@QAEXXZ\tno-match\told 3-field row\n"
                   "?Sym@@QAEXXZ\t0x00401000\t16\tpartial\t92%, banked\r\n",
                   encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    re_log._reset()
    try:
        # The queue's own filter must release it...
        kept, dropped = queue.drop_logged(
            [{"symbol": "?Sym@@QAEXXZ", "rva": "0x00401000"}])
        assert dropped == 0 and len(kept) == 1, (kept, dropped)
        # ...and the legacy reader must no longer be fed re_attempts.log at all,
        # or it would retire the symbol on the 3-field row regardless.
        assert queue.logged_no_match([log]) == {"?Sym@@QAEXXZ"}, \
            "3-field reader still parses the file; it must not receive it"
    finally:
        re_log._reset()

    # Lock the wiring, not just the parts: the reader above still retires on a
    # 3-field row, so the fix is precisely that main() stops handing it the log.
    import inspect
    source = inspect.getsource(queue.main)
    call = re.search(r"logged_no_match\(([^)]*)\)", source)
    assert call and "RE_ATTEMPTS" not in call.group(1), (
        "main() feeds re_attempts.log to the 3-field reader again — a stale "
        f"no-match will silently out-vote a later partial: {call and call.group(0)}")


def test_stash_is_offered_with_a_served_candidate(tmp_path, monkeypatch):
    log = tmp_path / "reverse" / "re_attempts.log"
    log.parent.mkdir(parents=True, exist_ok=True)
    log.write_text("", encoding="utf-8")
    stash = tmp_path / "reverse" / "attempts" / "0x00401000.cpp"
    stash.parent.mkdir(parents=True, exist_ok=True)
    stash.write_text("// ?Sym@@QAEXXZ\n// partial score=0.5 date=2026-08-24\nvoid f(){}\n",
                     encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    monkeypatch.setattr(queue.build, "ROOT", tmp_path)
    re_log._reset()
    try:
        found = queue.stash_for_item({"symbol": "?Sym@@QAEXXZ", "rva": "0x00401000"})
        assert found == ("reverse/attempts/0x00401000.cpp", 0.5), found
        assert queue.stash_for_item({"symbol": "?X@@QAEXXZ", "rva": "0x00999000"}) is None
    finally:
        re_log._reset()


def test_add_match_clears_the_stash_only_on_success(tmp_path):
    """Landing removes the head start it consumed; a revert must not."""
    import add_match

    stash = tmp_path / "reverse" / "attempts" / "0x000c8220.cpp"
    stash.parent.mkdir(parents=True, exist_ok=True)
    stash.write_text("// sym\n// partial score=0.9 date=2026-08-24\nvoid f(){}\n",
                     encoding="utf-8")

    add_match.remove_stash(0x000C8220, tmp_path)
    assert not stash.exists(), "landing left its stash behind"

    add_match.remove_stash(0x000C8220, tmp_path)  # absent -> no-op, no raise

    other = tmp_path / "reverse" / "attempts" / "0x00401000.cpp"
    other.write_text("// other\n// partial score=0.1 date=2026-08-24\nvoid g(){}\n",
                     encoding="utf-8")
    add_match.remove_stash(0x000C8220, tmp_path)
    assert other.exists(), "removed a stash belonging to a different address"


def test_gen_asm_procs_skip_landed_owner_bodies(tmp_path, monkeypatch):
    """Before the fix the .asm branch lacked the .cpp branch's already-matched
    tripwire, so gen-asm PROCs whose exact bytes live in a matched row's body
    (or whose name owns a matched row) were served again as candidates."""
    index = {b"\x90\x90\x90\x90": {"name": "row", "source": "home.cpp"}}
    own = [{"status": "matched"}]
    other_files = [{"status": "matched"}]
    unmatched = [{"status": "queued"}]

    # landed: same-file matched row
    assert queue.asm_already_matched(own, [], b"\x90\x90\x90\x90", index)
    # landed: name matched under another source
    assert queue.asm_already_matched([], other_files, b"\x90\x90\x90\x90", index)
    # landed: exact bytes in the matched body index
    assert queue.asm_already_matched([], [], b"\x90\x90\x90\x90", index)
    # still a candidate: unrowed body with no matched owner
    assert not queue.asm_already_matched(unmatched, unmatched,
                                         b"\x90\x90\x90\x90", {b"\xAA": None})


def test_gen_asm_procs_skip_bodies_inside_matched_ranges():
    """A dump PROC that is only a prefix of a matched row at its own RVA --
    the common EH-prologue stub of a rowed parent -- shares no exact-bytes
    index entry, so the range index must catch it."""
    ranges = queue.matched_row_ranges({"home.cpp": [
        {"status": "matched", "target_rva": "0x00006B09", "target_size": "285"},
        {"status": "queued", "target_rva": "0x00008000", "target_size": "40"},
    ]})
    assert ranges == [(0x6B09, 0x6B09 + 285)]  # the queued row is excluded

    # the 10-byte prologue stub of the rowed 285-byte parent
    assert queue.asm_rva_contained(ranges, 0x6B09, 10)
    assert queue.asm_rva_contained(ranges, 0x6B09, 285)
    # a body overhanging the parent's end is not owned
    assert not queue.asm_rva_contained(ranges, 0x6C1E, 10)
    # no ghidra comment -> no rva -> undecidable, kept as a candidate
    assert not queue.asm_rva_contained(ranges, None, 10)


def test_ghidra_rva_comment_is_read_above_the_proc():
    """The PROC's retail rva comes from the ghidra comment above it, across
    the `public` line between them."""
    lines = [
        "; ghidra: FUN_00406b09  retail @ 0x00006B09 size 10",
        "public ?d_00006b09@@YAXXZ",
        "?d_00006b09@@YAXXZ PROC",
        "    db 0B8h, 0DCh",
        "?d_00006b09@@YAXXZ ENDP",
    ]
    assert queue.asm_proc_blocks(lines) == [
        ("?d_00006b09@@YAXXZ", b"\xb8\xdc", 2, 4, 0x6B09)]


def test_gen_asm_branch_uses_the_tripwire():
    """Lock the wiring: main()'s .asm branch must consult asm_already_matched,
    not just the pytest above, or a refedit could drop the call again."""
    import inspect

    source = inspect.getsource(queue.main)
    assert "asm_already_matched(own" in source, (
        "main()'s .asm branch stopped consulting the already-matched filter; "
        "landed gen-asm PROCs will be served as fresh candidates again")
    assert "asm_rva_contained(body_ranges" in source, (
        "main()'s .asm branch stopped consulting the matched-range filter; "
        "prologue stubs of rowed parents will be served as fresh candidates")


def recovery_row(name, rva, source, notes=""):
    return {"name": name, "target_rva": f"0x{rva:08X}",
            "target_size": "2", "source": source,
            "status": "matched", "notes": notes}


def queue_indexes(tmp_path, monkeypatch, rows):
    # Two identical literal bodies, one per fixture RVA. The PE plumbing is
    # irrelevant to ownership, so keep the real index builders and stub it.
    exe = tmp_path / "game.dat"
    exe.write_bytes(b"\x90\xc3" * 2)
    monkeypatch.setattr(queue.build, "EXE", exe)
    monkeypatch.setattr(queue.build, "pe_sections", lambda data: [])
    monkeypatch.setattr(queue.build, "rva_to_file_offset",
                        lambda sections, rva: rva - 0x1000)
    by_source = {}
    for row in rows:
        by_source.setdefault(row["source"], []).append(row)
    return (queue.matched_body_index(by_source, 2),
            queue.matched_row_ranges(by_source))


@pytest.mark.parametrize("notes", ["gen-dump", "gen-dump;bounds=inventory",
                                  "  gen-dump;ghidra=FUN_00401000"])
def test_own_dump_remains_open_in_all_recovery_filters(tmp_path, monkeypatch, notes):
    dump = recovery_row("?d_00001000@@YAXXZ", 0x1000,
                        "Code/gen_asm/d_00001000.asm", notes)
    body_index, ranges = queue_indexes(tmp_path, monkeypatch, [dump])
    assert not queue.asm_already_matched([dump], [dump], b"\x90\xc3", body_index)
    assert not queue.asm_rva_contained(ranges, 0x1000, 2)
    assert body_index == {} and ranges == []


def test_another_dump_is_not_an_exact_byte_recovery(tmp_path, monkeypatch):
    # The rule is keyed by the scaffold note, including historical dump rows
    # outside gen_asm. An identical dump elsewhere is not recovered C++.
    other = recovery_row("?other_dump@@YAXXZ", 0x1002,
                         "Code/old_dump.cpp", "gen-dump")
    body_index, ranges = queue_indexes(tmp_path, monkeypatch, [other])
    assert not queue.asm_already_matched([], [], b"\x90\xc3", body_index)
    assert not queue.asm_rva_contained(ranges, 0x1002, 2)


def test_real_source_still_retires_a_matching_dump(tmp_path, monkeypatch):
    dump = recovery_row("?d_00001000@@YAXXZ", 0x1000,
                        "Code/gen_asm/d_00001000.asm", "gen-dump")
    recovered = recovery_row("?real@@YAXXZ", 0x1002, "Code/real.cpp")
    body_index, ranges = queue_indexes(tmp_path, monkeypatch, [dump, recovered])
    assert queue.asm_already_matched([dump], [], b"\x90\xc3", body_index)
    assert queue.asm_already_matched([], [recovered], b"different", {})
    assert queue.asm_rva_contained(ranges, 0x1002, 2)
    assert not queue.asm_rva_contained(ranges, 0x1000, 2)
    assert list(body_index.values()) == [recovered]
