"""marker_screen clears a destination's marker to measure a donor, so the one
thing it must never do is leave that marker cleared. A destination missing its
marker makes the NEXT build report a stale-annotation pass that never compared
a byte -- the trap docs/lessons.md records -- so an interrupted screen is worse
than a failed one."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import marker_screen  # noqa: E402


def _dest(tmp_path, donor, symbol):
    """screen() resolves its destination as ROOT / dest, and pathlib lets an
    ABSOLUTE dest win, which is how these tests point it at tmp_path without
    patching anything."""
    path = tmp_path / "Dest.cpp"
    marker = "// byte-exact reconstruction: %s\n// %s present-unmatched\n" % (donor, symbol)
    path.write_bytes(("above\n" + marker + "below\n").encode("utf-8"))
    return path, marker


def test_an_exception_mid_screen_restores_the_marker(tmp_path, monkeypatch):
    donor, symbol = "d.cpp", "?f@C@@QAEXXZ"
    path, marker = _dest(tmp_path, donor, symbol)
    before = path.read_bytes()

    def boom(*a, **k):
        raise RuntimeError("build died")
    monkeypatch.setattr(marker_screen, "_screen_cleared", boom)
    with pytest.raises(RuntimeError):
        marker_screen.screen(donor, str(path), symbol)

    assert path.read_bytes() == before, "marker not restored after an exception"
    assert marker in path.read_bytes().decode("utf-8")


def test_a_keyboardinterrupt_also_restores(tmp_path, monkeypatch):
    """BaseException, not Exception -- a Ctrl-C mid-build must restore too."""
    donor, symbol = "d.cpp", "?f@C@@QAEXXZ"
    path, marker = _dest(tmp_path, donor, symbol)
    before = path.read_bytes()

    def interrupted(*a, **k):
        raise KeyboardInterrupt
    monkeypatch.setattr(marker_screen, "_screen_cleared", interrupted)
    with pytest.raises(KeyboardInterrupt):
        marker_screen.screen(donor, str(path), symbol)

    assert path.read_bytes() == before, "marker not restored after Ctrl-C"


def test_a_missing_marker_pair_is_reported_and_nothing_is_written(tmp_path, monkeypatch):
    path = tmp_path / "Dest.cpp"
    path.write_bytes(b"no marker here\n")
    before = path.read_bytes()
    assert marker_screen.screen("d.cpp", str(path), "?f@C@@QAEXXZ") == "no-marker-pair"
    assert path.read_bytes() == before


def test_an_absent_destination_is_a_verdict_not_a_traceback(tmp_path):
    """Six of the queue's nineteen pairs name a destination that does not exist.

    The subsystem was never consolidated -- VideoPlayer.cpp is absent beside
    VideoPlayerDeletingDtor.cpp and VideoPlayerGetVideo.cpp -- so there is
    nothing to repoint into. screen() used to die in read_bytes with a
    FileNotFoundError traceback, which reads as a broken checkout rather than as
    the free dead end it is, and made looping over the queue impossible.
    """
    verdict = marker_screen.screen(
        "donor.cpp", str(tmp_path / "NeverAuthored.cpp"), "?f@C@@QAEXXZ")
    assert verdict.startswith("NO-DESTINATION"), verdict
    assert "NeverAuthored.cpp" in verdict


def test_an_absent_destination_is_decided_before_any_file_is_touched(tmp_path,
                                                                    monkeypatch):
    """It must be one of the free verdicts: no compile, no write, no restore."""
    def boom(*a, **k):
        raise AssertionError("screen() went on to compile an absent destination")
    monkeypatch.setattr(marker_screen, "_screen_cleared", boom)
    assert marker_screen.screen(
        "donor.cpp", str(tmp_path / "Nope.cpp"), "?f@C@@QAEXXZ"
    ).startswith("NO-DESTINATION")


CRLF_CASES = {
    "paired LF": "// byte-exact reconstruction: {donor}\n// {sym} present-unmatched\n",
    "paired CRLF": "// byte-exact reconstruction: {donor}\r\n// {sym} present-unmatched\r\n",
    "bare LF": "// {sym} present-unmatched\n",
    "bare CRLF": "// {sym} present-unmatched\r\n",
}


@pytest.mark.parametrize("case", sorted(CRLF_CASES))
def test_a_marker_is_found_under_either_terminator_paired_or_bare(case):
    """All thirteen screenable pairs in the queue reported no-marker-pair.

    Not because they lacked a marker: these destinations hold CRLF blocks inside
    otherwise-LF files, so their markers end "\r\n" and a literal match built
    with "\n" found nothing. The lane read as exhausted when nothing had been
    measured. Pairing was the second half -- crosslink.py writes the two-line
    form and has not been run over most of the tree, while the donor's own
    "readable body of" line already establishes the relationship.
    """
    donor, sym = "d.cpp", "?f@C@@QAEXXZ"
    block = CRLF_CASES[case].format(donor=donor, sym=sym)
    found = marker_screen._marker_in("above\n" + block + "below\n", donor, sym)
    assert found == block, (case, repr(found))


def test_the_paired_form_wins_so_no_orphan_link_is_left_behind():
    """Clearing only the marker line would strand the reconstruction pointer."""
    donor, sym = "d.cpp", "?f@C@@QAEXXZ"
    paired = CRLF_CASES["paired CRLF"].format(donor=donor, sym=sym)
    assert marker_screen._marker_in("x\r\n" + paired, donor, sym) == paired


def test_no_marker_at_all_is_still_no_marker_pair():
    assert marker_screen._marker_in("nothing here\n", "d.cpp", "?f@C@@QAEXXZ") is None


def test_a_marker_appearing_twice_is_refused_rather_than_guessed():
    donor, sym = "d.cpp", "?f@C@@QAEXXZ"
    bare = CRLF_CASES["bare LF"].format(donor=donor, sym=sym)
    assert marker_screen._marker_in(bare + bare, donor, sym) is None
