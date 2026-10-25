"""README card and daily Discord post; no network requests."""
import html
import io
import re
import json
import sys
from pathlib import Path
from urllib.error import URLError

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import readme_progress as daily
import progress

UP = "▲"


def sample(authored=40, linked_authored=9, linked_game_code=90):
    # rebuilt 60 of 100; game's own code = 100 - 5 vendored - 5 library = 90;
    # represented game code 50 (40 authored + 10 generated); the census's
    # independent authored-only Linking figure remains 9/90.
    return {"total": 100, "linked": 12, "linked_authored": linked_authored, "linked_game_code": linked_game_code,
            "authored": authored, "vendored": 5, "generated": 10, "library": 5, "census": None,
            "cpp_rules": daily.progress.GAME_CPP_RULES}


def previous(**changes):
    """A saved post state: the figures the last post was drawn from."""
    return {**sample(), **changes, "message_id": "1", "run_id": "old"}


def setup_state(tmp_path, monkeypatch, state=None):
    (tmp_path / "docs").mkdir()
    monkeypatch.setattr(daily.progress, "ROOT", tmp_path)
    path = tmp_path / daily.STATE
    if state:
        path.write_text(json.dumps(state), encoding="utf-8")
    return path


def test_retry_does_not_duplicate_post(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "run-123")
    setup_state(tmp_path, monkeypatch, {"total": 100, "message_id": "123", "run_id": "run-123"})
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: pytest.fail("Unexpected post"))
    daily.notify(sample())


def test_success_posts_the_bars_and_saves_the_figures(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token\n")

    def send(request, timeout):
        assert request.full_url.endswith("token?wait=true")
        payload = json.loads(request.data)
        assert payload["allowed_mentions"] == {"parse": []}
        assert "**Rebuilt from source: 60.00%**" in payload["embeds"][0]["description"]
        return io.BytesIO(b'{"id":"123"}')
    monkeypatch.setattr(daily, "urlopen", send)
    daily.notify(sample())
    state = json.loads(path.read_text())
    assert state["message_id"] == "123"
    assert daily.measures(state) == daily.measures(sample())  # the next post's arrows start from these


def test_each_run_posts_new_message_even_if_unchanged(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "new-run")
    path = setup_state(tmp_path, monkeypatch, previous())
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda request, timeout: io.BytesIO(b'{"id":"456"}'))
    daily.notify(sample())
    assert json.loads(path.read_text())["message_id"] == "456"


def test_failed_post_does_not_advance_state_or_leak_url(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/secret")

    def fail(*args, **kwargs):
        raise URLError("secret")
    monkeypatch.setattr(daily, "urlopen", fail)
    with pytest.raises(SystemExit, match="^Discord update failed: connection error$"):
        daily.notify(sample())
    assert not path.exists()


def test_discord_posts_four_measures_and_links_the_readme():
    names = {"declared_names": 200, "readable_names": 142}
    embed = daily.announcement({**sample(), **names}, previous(authored=36, generated=10, declared_names=200,
                                                              readable_names=140))["embeds"][0]
    M, C, L, N = (daily.BLOCK[key] for key in ("matched", "cpp", "linked", "names"))
    R = daily.REST_BLOCK
    assert embed["description"].split("\n") == [
        f"**Rebuilt from source: 60.00%**  {UP} 4.00",
        f"{M * 6}{R * 4}",
        f"60 / 100 bytes rebuilt without copying {daily.EXE}",
        "",
        f"**Game code in C++*: 55.56%**  {UP} 4.44",
        f"{C * 6}{R * 4}",
        "50 / 90 bytes of executable game code (libraries and embedded data excluded)",
        "* Includes generated C++ and intentionally retained assembly.",
        "",
        "**Linking: 10.00%**",
        f"{L * 1}{R * 9}",
        "9 / 90 bytes of game code linked (legacy authored-only accounting) (not measured yet)",
        "",
        f"**Readable names: 71.00%**  {UP} 1.00",
        f"{N * 7}{R * 3}",
        "142 / 200 declared names (files, types, functions, members, globals, parameters, locals) "
        "that are not placeholders",
        "",
        f"[What each bar measures, with charts: README]({daily.README})"]
    assert "footer" not in embed and "Whole game" not in embed["description"]


def test_card_shows_the_same_three_measures():
    svg = daily.render(sample(), previous(authored=36, generated=10))
    for text in (">Rebuilt from source<", ">60.00%<", ">Game code in C++*<", ">55.56%<", ">Linking<", ">10.00%<",
                 f"60 / 100 bytes rebuilt without copying {daily.EXE}", f">{UP} 4.44<",
                 "60.00% rebuilt from source, 55.56% game code in C++*, 10.00% linking",
                 "* Includes generated C++ and intentionally retained assembly."):
        assert text in svg
    assert "prefers-color-scheme: light" in svg and "Whole game" not in svg


def test_completed_game_code_includes_reviewed_assembly_and_excludes_data():
    current = dict(sample(), total=7_978_500, authored=7_240_277,
                   generated=267_704, assembly=7_986, vendored=457_607,
                   library=822, data=4_104)
    assert daily.measures(current)['cpp'] == (7_515_967, 7_515_967)
    text = daily.announcement(current, None)['embeds'][0]['description']
    assert '**Game code in C++*: 100.00%**' in text
    assert daily.progress.GAME_CPP_ANNOTATION in text
    # Replacing a generated body with its parent's recovered code is useful
    # ownership work, but creates no newly represented executable bytes.
    reconciled = dict(current, authored=current['authored'] + 100,
                      generated=current['generated'] - 100)
    assert daily.measures(reconciled)['cpp'] == daily.measures(current)['cpp']
    assert daily.delta_since(current, 'cpp', *daily.measures(reconciled)['cpp'], reconciled) is None
    assert daily.measures(current)['linked'] == (9, 90)


def test_missing_coverage_cannot_be_rounded_or_clamped_to_complete():
    current = dict(sample(), assembly=5, data=5)
    assert daily.measures(current)['cpp'] == (55, 85)
    text = daily.announcement(current, None)['embeds'][0]['description']
    assert '**Game code in C++*: 64.71%**' in text


def test_blue_accounting_correction_does_not_claim_new_progress():
    current = sample()
    old = previous()
    del old['cpp_rules']
    assert daily.delta_since(old, 'cpp', *daily.measures(current)['cpp'], current) is None
    text = daily.announcement(current, old)['embeds'][0]['description']
    assert '**Game code in C++*: 55.56%**  (accounting changed)' in text
    assert 'accounting changed' in daily.render(current, old)
    assert 'rules changed' not in text and 'rules changed' not in daily.render(current, old)
    assert daily.UP not in text and daily.DOWN not in text


def test_linking_is_one_census_snapshot():
    # The census tree's game code (80) is the denominator, not today's (90).
    current = sample(linked_authored=8, linked_game_code=80)
    assert daily.measures(current)["linked"] == (8, 80)
    assert "8 / 80 bytes of game code linked (legacy authored-only accounting)" in daily.announcement(current, None)["embeds"][0]["description"]
    with pytest.raises(ValueError):
        daily.measures(sample(linked_game_code=None))  # bytes without their denominator
    with pytest.raises(ValueError):
        daily.measures(sample(linked_authored=91))  # more linked than there is code


def test_linking_without_a_census_figure_says_so():
    current = sample(linked_authored=None, linked_game_code=None)
    assert "**Linking:** not measured yet" in daily.announcement(current, None)["embeds"][0]["description"]
    assert ">not measured<" in daily.render(current)


def test_arrow_is_the_change_in_the_bars_percentage():
    # Linking went from 9/90 = 10.00% to 8/80 = 10.00%: same share, no arrow,
    # though the bytes and the denominator both moved.
    text = daily.announcement(sample(linked_authored=8, linked_game_code=80), previous())["embeds"][0]["description"]
    assert UP not in text and "▼" not in text
    # 9/90 -> 12/90: +3.33 points.
    assert f"**Linking: 13.33%**  {UP} 3.33" in daily.announcement(sample(linked_authored=12), previous())[
        "embeds"][0]["description"]
    # A move that rounds to 0.00 shows nothing.
    assert UP not in daily.announcement(sample(), previous(authored=39.999, generated=10.001))["embeds"][0][
        "description"]


def test_old_state_without_figures_gives_no_arrow():
    old = {"total": 100, "matched_total": 55, "message_id": "1", "run_id": "old"}  # before these figures existed
    assert UP not in daily.announcement(sample(), old)["embeds"][0]["description"]
    # A state from before the census stored Linking: the other bars still compare.
    text = daily.announcement(sample(), previous(authored=36, generated=10, linked_authored=None,
                                                 linked_game_code=None))["embeds"][0]["description"]
    assert f"55.56%**  {UP} 4.44" in text and "**Linking: 10.00%**\n" in text


def test_nothing_claims_the_game_is_100_percent_done():
    text = daily.announcement(sample(), previous())["embeds"][0]["description"] + daily.render(sample(), previous())
    assert "100%" not in text


@pytest.mark.parametrize("value", [0, 1, 4, 5, 49, 50, 95, 96, 100])
def test_blocks_always_fill_exactly_ten(value):
    text = daily.blocks(value, 100, daily.BLOCK["matched"])
    assert text.count(daily.BLOCK["matched"]) + text.count(daily.REST_BLOCK) == 10


@pytest.mark.parametrize("before, after, change", [
    (71.014, 71.016, "▲ 0.01"),
    (71.016, 71.014, "▼ 0.01"),
    (71.011, 71.014, "· 0.00"),
    (71.01, 71.01, "· 0.00"),
])
def test_names_always_compare_the_displayed_percentages(before, after, change):
    current = {**sample(), "declared_names": 100_000, "readable_names": round(after * 1000)}
    old = previous(declared_names=100_000, readable_names=round(before * 1000))
    text = daily.announcement(current, old)["embeds"][0]["description"]
    assert f"**Readable names: {after:.2f}%**  {change}" in text
    assert f">{change}<" in daily.render(current, old)
    if change.startswith("·"):
        assert f'class="muted" dx="10" font-size="13" font-weight="600">{change}<' in daily.render(current, old)


def test_names_compare_shares_not_counts():
    current = {**sample(), "declared_names": 400, "readable_names": 280}
    old = previous(declared_names=200, readable_names=142)
    assert "**Readable names: 70.00%**  ▼ 1.00" in daily.announcement(current, old)["embeds"][0]["description"]


def test_first_names_measurement_has_no_invented_delta():
    current = {**sample(), "declared_names": 200, "readable_names": 142}
    for old in (None, previous()):
        assert "**Readable names: 71.00%**\n" in daily.announcement(current, old)["embeds"][0]["description"]


@pytest.mark.parametrize("counts", [
    {"declared_names": 10}, {"readable_names": 5},
    {"declared_names": 10, "readable_names": 11},
    {"declared_names": 10, "readable_names": -1},
])
def test_invalid_names_counts_fail(counts):
    with pytest.raises(ValueError, match="Invalid readable-names count"):
        daily.measures({**sample(), **counts})


def test_main_measures_names_and_persists_them(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setattr(sys, "argv", ["readme_progress.py", "--discord"])
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: io.BytesIO(b'{"id":"123"}'))
    monkeypatch.setattr(daily.progress, "matched_at", lambda *a: [])
    monkeypatch.setattr(daily.progress, "notes_at", lambda *a: {})
    monkeypatch.setattr(daily.progress, "retail_text", lambda: (0, 100))
    monkeypatch.setattr(daily.progress, "naked_cpp_rows_at", lambda *a: [])
    monkeypatch.setattr(daily.progress, "real_split", lambda *a, **k: dict(sample(), data=7))
    monkeypatch.setattr(daily.progress, "census_at", lambda *a: None)
    monkeypatch.setattr(daily.progress, "real_code_denominator", lambda *a: (0, 100))
    monkeypatch.setattr(daily.name_metric, "readable", lambda: (200, 58))
    daily.main()
    state = json.loads(path.read_text())
    assert state['data'] == 7 and daily.measures(state)['matched'] == (67, 100)
    assert state["declared_names"] == 200 and state["readable_names"] == 142
    assert ">71.00%<" in (tmp_path / "docs/progress.svg").read_text()


def receipt(self_strict=2_000, closed=1_000, text=8_000, authoritative=True):
    return {"tool": "link_cycle", "commit": "9193fd824711fe616f8ac6ee2b9f8fad405f3e3f",
            "date_utc": "2026-10-09 07:57:15", "authoritative": authoritative,
            "series": {"retail_text_bytes": text, "credit_unique_bytes": closed,
                       "real": {"placed_self_strict": {"unique_bytes": self_strict}}}}


def test_strict_link_reads_the_committed_receipt(tmp_path):
    assert daily.strict_link(tmp_path) is None
    path = tmp_path / daily.RECEIPT
    path.parent.mkdir(parents=True)
    path.write_text(json.dumps(receipt()), encoding="utf-8")
    assert daily.strict_link(tmp_path) == {"date": "2026-10-09", "commit": "9193fd8247", "authoritative": True,
                                           "self_strict": 2_000, "closed_strict": 1_000, "text": 8_000}
    for bad in (receipt(self_strict=500, closed=1_000), {**receipt(), "series": {}}):
        path.write_text(json.dumps(bad), encoding="utf-8")
        assert "invalid" in daily.strict_link(tmp_path)
    path.write_text('{"series": {"retail_text_bytes": Infinity}}', encoding="utf-8")
    assert "invalid" in daily.strict_link(tmp_path)


def test_strict_line_sits_beside_linking_never_instead(tmp_path, monkeypatch):
    path = tmp_path / daily.RECEIPT
    path.parent.mkdir(parents=True)
    path.write_text(json.dumps(receipt()), encoding="utf-8")
    current = {**sample(), "strict": daily.strict_link(tmp_path)}
    line = ("Historical strict link check (2026-10-09 at 9193fd8247, no longer updated): 25.00% self-strict, "
            "12.50% fully linked, of all retail .text")
    lines = daily.announcement(current, None)["embeds"][0]["description"].split("\n")
    readme = f"[What each bar measures, with charts: README]({daily.README})"
    # until a bundle is published the card names no feed: one historical line
    assert daily.PUBLISHED is False
    assert "**Linking: 10.00%**" in lines and lines[-3:] == [line, "", readme]
    svg = daily.render(current)
    assert line in svg and daily.CURRENT_LINE not in svg and ">10.00%<" in svg and 'height="404"' in svg
    # from the first published bundle a second line says where the current measurement is
    monkeypatch.setattr(daily, "PUBLISHED", True)
    lines = daily.announcement(current, None)["embeds"][0]["description"].split("\n")
    assert lines[-4:] == [line, daily.CURRENT_LINE, "", readme]
    assert "published link-cycle bundle" in daily.CURRENT_LINE and "cycle_artifacts.py fetch --latest" in daily.CURRENT_LINE
    svg = daily.render(current)
    assert line in svg and daily.CURRENT_LINE in svg and ">10.00%<" in svg and 'height="422"' in svg
    assert 'height="382"' in daily.render(sample())


def test_strict_line_flags_a_receipt_that_is_not_authoritative(tmp_path):
    path = tmp_path / daily.RECEIPT
    path.parent.mkdir(parents=True)
    path.write_text(json.dumps(receipt(authoritative=False)), encoding="utf-8")
    assert daily.strict_line({"strict": daily.strict_link(tmp_path)}).endswith("(not authoritative)")


def test_unreadable_receipt_never_stops_the_daily_post(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    receipt_path = tmp_path / daily.RECEIPT
    receipt_path.parent.mkdir(parents=True)
    receipt_path.write_text(json.dumps(receipt(self_strict=500, closed=1_000)), encoding="utf-8")
    monkeypatch.setattr(sys, "argv", ["readme_progress.py", "--discord"])
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    posted = []
    monkeypatch.setattr(daily, "urlopen", lambda request, *a, **k: posted.append(request) or io.BytesIO(b'{"id":"9"}'))
    monkeypatch.setattr(daily.progress, "matched_at", lambda *a: [])
    monkeypatch.setattr(daily.progress, "notes_at", lambda *a: {})
    monkeypatch.setattr(daily.progress, "retail_text", lambda: (0, 100))
    monkeypatch.setattr(daily.progress, "naked_cpp_rows_at", lambda *a: [])
    monkeypatch.setattr(daily.progress, "real_split", lambda *a, **k: sample())
    monkeypatch.setattr(daily.progress, "census_at", lambda *a: None)
    monkeypatch.setattr(daily.progress, "real_code_denominator", lambda *a: (0, 100))
    monkeypatch.setattr(daily.name_metric, "readable", lambda: (200, 58))
    daily.main()
    assert posted and json.loads(path.read_text())["message_id"] == "9"
    assert "Strict link check unavailable" in (tmp_path / "docs/progress.svg").read_text()


def test_huge_or_unreachable_receipts_degrade(tmp_path, monkeypatch):
    path = tmp_path / daily.RECEIPT
    path.parent.mkdir(parents=True)
    path.write_text(json.dumps(receipt(self_strict=10, closed=5, text=10**400)), encoding="utf-8")
    strict = daily.strict_link(tmp_path)
    assert "invalid" in strict and daily.strict_line({"strict": strict}).startswith("Strict link check unavailable")

    def denied(self):
        raise PermissionError("denied")
    monkeypatch.setattr(type(path), "exists", denied)
    assert "invalid" in daily.strict_link(tmp_path)


@pytest.mark.parametrize("text", [
    "[" * 10000 + "0" + "]" * 10000,
    json.dumps({**receipt(), "date_utc": "\ud800"}),
    json.dumps({**receipt(), "commit": "\ud800"}),
    json.dumps({**receipt(), "series": {**receipt()["series"], "credit_unique_bytes": True}}),
    json.dumps({**receipt(), "series": {**receipt()["series"], "retail_text_bytes": "8000"}}),
])
def test_malformed_receipts_never_stop_main(tmp_path, monkeypatch, text):
    path = setup_state(tmp_path, monkeypatch)
    receipt_path = tmp_path / daily.RECEIPT
    receipt_path.parent.mkdir(parents=True)
    receipt_path.write_text(text, encoding="utf-8")
    monkeypatch.setattr(sys, "argv", ["readme_progress.py", "--discord"])
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: io.BytesIO(b'{"id":"7"}'))
    for name, value in (("matched_at", lambda *a: []), ("notes_at", lambda *a: {}), ("retail_text", lambda: (0, 100)),
                        ("naked_cpp_rows_at", lambda *a: []), ("real_split", lambda *a, **k: sample()),
                        ("census_at", lambda *a: None), ("real_code_denominator", lambda *a: (0, 100))):
        monkeypatch.setattr(daily.progress, name, value)
    monkeypatch.setattr(daily.name_metric, "readable", lambda: (200, 58))
    daily.main()
    assert json.loads(path.read_text())["message_id"] == "7"
    assert "Strict link check unavailable" in (tmp_path / "docs/progress.svg").read_text(encoding="utf-8")


def real_size(**changes):
    """A state with the tree's real magnitudes, so the card's longest lines are tested."""
    return {"total": 7_978_500, "authored": 7_240_075, "vendored": 457_218, "generated": 267_831, "library": 1_286,
            "data": 4_104, "assembly": 7_986, "linked": 7_355_718, "linked_authored": 6_898_514,
            "linked_game_code": 7_520_010, "declared_names": 558_118,
            "readable_names": 381_236, "census": {"date": "2026-10-24 06:00", "rules": "retail-truth-4"},
            "cpp_rules": progress.GAME_CPP_RULES,
            "strict": {"date": "2026-10-10", "commit": "d093315a52", "authoritative": True, "self_strict": 2_340_800,
                       "closed_strict": 1_129_757, "text": 8_096_994}, **changes}


# Advance widths, in font units (2048 an em), of the card's characters, read
# from the hmtx tables of Windows 11's segoeui.ttf, seguisb.ttf, segoeuib.ttf
# (Segoe UI 5.72) and arial.ttf, arialbd.ttf (Arial 7.06), sha256 as recorded
# beside progress.GLYPH_EM: a record separate from GLYPH_EM (the wrapper's own
# estimate), so the card is checked against the fonts it names.
MEASURED_CHARS = (" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
                  "abcdefghijklmnopqrstuvwxyz{|}~\u00b7\u25b2\u25bc\u2013\u2014\u2192\u00d7\u2248")
MEASURED = {face: dict(zip(MEASURED_CHARS, map(int, units.split()), strict=True)) for face, units in (
    ("Segoe UI", (
        "561 582 803 1210 1104 1676 1639 471 618 618 854 1401 444 819 444 798 1104 1104 1104 1104 1104 1104 "
        "1104 1104 1104 1104 444 444 1401 1401 1401 918 1956 1321 1174 1268 1436 1036 1000 1405 1454 545 731 "
        "1188 964 1839 1532 1544 1147 1544 1225 1088 1073 1407 1272 1913 1208 1132 1168 618 776 618 1401 850 "
        "549 1042 1204 946 1206 1071 641 1206 1159 496 496 1018 496 1764 1159 1200 1204 1206 712 869 694 1159 "
        "981 1480 940 991 926 618 490 618 1401 444 1764 1764 1024 2048 1767 1401 1403")),
    ("Arial", (
        "569 569 727 1139 1139 1821 1366 391 682 682 797 1196 569 682 569 569 1139 1139 1139 1139 1139 1139 "
        "1139 1139 1139 1139 569 569 1196 1196 1196 1139 2079 1366 1366 1479 1479 1366 1251 1593 1479 569 "
        "1024 1366 1139 1706 1479 1593 1366 1593 1479 1366 1251 1479 1366 1933 1366 1366 1251 569 569 569 961 "
        "1139 682 1139 1139 1024 1139 1139 569 1139 1139 455 455 1024 455 1706 1139 1139 1139 1139 682 1024 "
        "569 1139 1024 1479 1024 1024 1024 684 532 684 1196 682 2027 2027 1139 2048 2048 1196 1124")),
    ("Segoe UI Semibold", (
        "563 622 896 1211 1137 1721 1465 529 680 680 889 1422 494 823 494 847 1137 824 1137 1137 1180 1137 "
        "1143 1098 1137 1143 494 494 1422 1422 1422 909 1955 1375 1237 1272 1469 1060 1029 1428 1506 597 812 "
        "1251 1001 1893 1571 1548 1197 1548 1275 1115 1130 1440 1314 1978 1268 1182 1202 680 829 680 1422 850 "
        "591 1069 1234 963 1234 1088 706 1234 1192 535 535 1075 535 1814 1195 1223 1234 1234 758 883 740 1195 "
        "1039 1549 1026 1041 951 680 570 680 1422 494 1764 1764 1024 2048 1767 1422 1424")),
    ("Segoe UI Bold", (
        "565 670 1010 1213 1178 1776 1740 600 756 756 932 1448 555 828 555 908 1178 1178 1178 1178 1178 1178 "
        "1178 1178 1178 1178 555 555 1448 1448 1448 897 1954 1440 1313 1278 1510 1090 1065 1456 1569 649 912 "
        "1329 1047 1960 1618 1553 1258 1553 1337 1148 1200 1481 1366 2058 1342 1243 1243 756 893 756 1448 850 "
        "643 1102 1270 983 1268 1108 785 1268 1233 582 582 1145 582 1876 1239 1252 1270 1268 815 901 797 1239 "
        "1110 1633 1131 1102 981 756 668 756 1448 555 1764 1764 1024 2048 1767 1448 1450")),
    ("Arial Bold", (
        "569 682 971 1139 1139 1821 1479 487 682 682 797 1196 569 682 569 569 1139 1139 1139 1139 1139 1139 "
        "1139 1139 1139 1139 682 682 1196 1196 1196 1251 1997 1479 1479 1479 1479 1366 1251 1593 1479 569 "
        "1139 1479 1251 1706 1479 1593 1366 1593 1479 1366 1251 1479 1366 1933 1366 1366 1251 682 569 682 "
        "1196 1139 682 1139 1251 1139 1251 1139 682 1251 1251 569 569 1139 569 1821 1251 1251 1251 1251 797 "
        "1139 682 1251 1139 1593 1139 1139 1024 797 573 797 1196 682 2027 2027 1139 2048 2048 1196 1124")),
)}
REGULAR, SEMIBOLD, BOLD = ("Segoe UI", "Arial"), ("Segoe UI Semibold", "Arial Bold"), ("Segoe UI Bold", "Arial Bold")
# Positive kerning, in font units, of some pairs, from the same files: the
# larger of the kern table and GPOS PairPos under 'kern' (Segoe UI Regular's
# GPOS omits the bracket pairs its kern table widens; Arial kerns none of
# these). A record separate from progress.KERN_EM.
KERN_UNITS = {
    "(j": {"Segoe UI": 233, "Segoe UI Semibold": 214, "Segoe UI Bold": 190},
    "[j": {"Segoe UI": 233, "Segoe UI Semibold": 205, "Segoe UI Bold": 170},
    "{j": {"Segoe UI": 203, "Segoe UI Semibold": 184, "Segoe UI Bold": 160},
    "f)": {"Segoe UI": 141, "Segoe UI Semibold": 113, "Segoe UI Bold": 78},
    "qj": {"Segoe UI": 102, "Segoe UI Semibold": 97, "Segoe UI Bold": 90},
    "LJ": {"Segoe UI": 100, "Segoe UI Semibold": 81, "Segoe UI Bold": 57},
    "rv": {"Segoe UI": 82, "Segoe UI Semibold": 82, "Segoe UI Bold": 82},
}


def measured(text, size, faces):
    """The widest of `faces`' widths of the rendered `text` at `size` px,
    kerned where KERN_UNITS records the pair."""
    text = html.unescape(text)
    return max(size * (sum(MEASURED[face][char] for char in text)
                       + sum(KERN_UNITS.get(text[i:i + 2], {}).get(face, 0) for i in range(len(text) - 1))) / 2048
               for face in faces)


@pytest.mark.parametrize("pair", sorted(KERN_UNITS))
def test_text_width_bounds_kerned_pairs(pair):
    # A renderer that ignores font-kerning="none" widens these pairs; the
    # bound still holds in every face, alone and inside a longer run.
    for face in MEASURED:
        assert progress.text_width(pair, 2048) >= measured(pair, 2048, (face,)), (pair, face)
    assert progress.text_width(pair, 1000) == sum(progress.GLYPH_EM[c] for c in pair) + progress.KERN_EM[pair]
    run = f"x{pair}{pair}x"
    assert progress.text_width(run, 1000) == sum(progress.GLYPH_EM[c] for c in run) + 2 * progress.KERN_EM[pair]


def test_kerning_breaks_advances_alone_for_paren_j():
    # Segoe UI Bold kerns (j by +190 units (kern and GPOS): 0.746 em, past
    # the advances alone (0.655 em); Semibold (+214) is over too.
    advances = sum(progress.GLYPH_EM[c] for c in "(j") / 1000
    assert measured("(j", 1, ("Segoe UI Bold",)) > advances and measured("(j", 1, ("Segoe UI Semibold",)) > advances
    assert progress.text_width("(j", 1) >= measured("(j", 1, MEASURED)
    assert progress.text_width("j(", 1) == advances  # pairs are ordered
    assert all(value > 0 for value in progress.KERN_EM.values()) and set("".join(progress.KERN_EM)) <= set(MEASURED_CHARS)


def test_glyph_estimate_bounds_every_measured_advance():
    # The wrapper's estimate is at least every measured face's advance, at
    # every weight the SVGs use, for every character it knows, and covers
    # every character measured; text_width adds no allowance on top.
    assert set(progress.GLYPH_EM) == set(MEASURED_CHARS)
    for face in MEASURED:
        assert all(progress.GLYPH_EM[char] / 1000 >= units / 2048 for char, units in MEASURED[face].items()), face
    assert progress.text_width("I|*", 1000) == sum(progress.GLYPH_EM[char] for char in "I|*")
    assert measured("0123456789", 12.5, REGULAR) == pytest.approx(10 * 12.5 * 1139 / 2048)  # Arial digits, 0.556 em
    assert measured("W", 12.5, REGULAR) == pytest.approx(12.5 * 1933 / 2048)  # 0.94 em
    with pytest.raises(ValueError, match="No measured glyph advance"):
        progress.text_width("\u4e2d", 12.5)


# The measured faces of each family the SVGs may name.
FAMILIES = {"Segoe UI": ("Segoe UI", "Segoe UI Semibold", "Segoe UI Bold"), "Arial": ("Arial", "Arial Bold")}
# Noto Sans 2.008 Regular (notofonts/noto-fonts hinted/ttf, 1000 units an em),
# which an earlier stack named: wider than the bound it was given.
NOTO_SANS = {"I": 339, "*": 551, "|": 551}


def test_svgs_name_only_measured_faces():
    # Every family in the stack has a measured face at each weight, no generic
    # family closes it, and every SVG generator declares that stack and no other.
    families = [name.strip().strip("'\"") for name in progress.FONT_STACK.split(",")]
    assert families == list(FAMILIES) and set(MEASURED) == {face for faces in FAMILIES.values() for face in faces}
    tools = Path(progress.__file__).resolve().parent
    for name in ("readme_progress.py", "progress_v2.py", "progress_site.py"):
        source = (tools / name).read_text(encoding="utf-8")
        declared = re.findall(r'font-family="([^"]*)"', source)
        assert declared and set(declared) <= {"{progress.FONT_STACK}", "{FONT}"}, (name, declared)
        # ... and turns kerning off wherever it names the stack.
        assert source.count("{progress.NO_KERN}") == len(declared), name
    assert f'font-family="{progress.FONT_STACK}" {progress.NO_KERN}' in daily.render(real_size())
    assert 'style="font-kerning:none;' in progress.NO_KERN and 'text-rendering="optimizeSpeed"' in progress.NO_KERN
    # The stack dropped Noto Sans because its advances exceed what the old
    # table allowed; the new table still does not bound them, so it stays out.
    assert any(units / 1000 > progress.GLYPH_EM[char] / 1000 for char, units in NOTO_SANS.items())




def inclusive_size(**changes):
    return real_size(linked_game_executable=7_300_000, game_executable=7_515_906,
                     link_coverage_rules=progress.LINK_COVERAGE_RULES, **changes)


OTHER_RULES = {"census": {"date": "2026-10-23 06:00", "rules": "retail-truth-3"}}


@pytest.mark.parametrize("now,before,notes", [
    (real_size(), real_size(), ["legacy authored-only accounting"]),
    (inclusive_size(), inclusive_size(), ["of executable game code in link-clean units"]),
    (inclusive_size(), real_size(), ["generated linked code now counted"]),
    (real_size(), inclusive_size(), ["census accounting changed to authored-only"]),
    (real_size(), real_size(**OTHER_RULES), ["census accounting changed to retail-truth-4 (91.74% under retail-truth-3)"]),
    (inclusive_size(), inclusive_size(**OTHER_RULES), ["census accounting changed to retail-truth-4 (97.13% under retail-truth-3)"]),
    (inclusive_size(), {k: v for k, v in real_size(**OTHER_RULES).items() if k != "cpp_rules"},
     ["generated linked code now counted"]),
], ids=["legacy", "inclusive", "accounting", "reverse-accounting", "legacy-rules", "inclusive-rules", "both-bars"])
def test_card_lines_fit_the_card(now, before, notes):
    svg = daily.render(now, {**before, "message_id": "1"})
    lines = re.findall(r'<text x="28" y="(\d+)" class="muted" font-size="12.5">([^<]*)</text>', svg)
    assert lines and all(measured(text, 12.5, REGULAR) <= 824 for _, text in lines), [t for _, t in lines]
    ys = [int(y) for y, _ in lines]
    assert ys == sorted(ys) and len(set(ys)) == len(ys)
    assert ys[-1] < int(re.search(r'height="(\d+)"', svg).group(1)) - 6
    rows = re.findall(r'class="strong" font-size="15" font-weight="600">([^<]*)(?:<tspan[^>]*>([^<]*)</tspan>)?</text>'
                      r'\s*<text x="852" y="\d+" class="strong" font-size="20" font-weight="700" text-anchor="end">'
                      r'([^<]*)</text>', svg)
    assert [label for label, _, _ in rows] == [label for _, label, _ in daily.ROWS]
    for label, tag, number in rows:
        used = measured(label, 15, SEMIBOLD) + (10 + measured(tag, 13, SEMIBOLD) if tag else 0)
        assert used + 20 + measured(number, 20, BOLD) <= 824, (label, tag, number)
    joined = " ".join(text for _, text in lines)
    for note in notes:
        assert note in joined, (note, joined)
    assert f"* {progress.GAME_CPP_ANNOTATION}" in [text for _, text in lines]
    assert (("Game code in C++*", "accounting changed") in [row[:2] for row in rows]) == ("cpp_rules" not in before)


def test_rule_note_tells_an_absent_figure_from_invalid_saved_data():
    rules = {"census": {"date": "2026-10-24 06:00", "rules": "retail-truth-4"}}
    current = {**sample(), **rules}
    old_rules = {"census": {"date": "2026-10-23 06:00", "rules": "retail-truth-3"}}
    absent = previous(linked_authored=None, linked_game_code=None, **old_rules)
    text = daily.announcement(current, absent)["embeds"][0]["description"]
    assert ("census accounting changed to retail-truth-4 (was retail-truth-3; the last post saved no Linking figure)"
            in text)
    text = daily.announcement(current, previous(**old_rules))["embeds"][0]["description"]
    assert "census accounting changed to retail-truth-4 (10.00% under retail-truth-3)" in text
    for bad in ({"linked_authored": "9"}, {"linked_authored": 100}, {"linked_game_code": 5},
                {"linked_authored": None}, {"linked_game_code": None}):
        with pytest.raises(ValueError, match="saved"):
            daily.rule_note(previous(**old_rules, **bad), ("retail-truth-3", "retail-truth-4"))
        for draw in (daily.announcement, daily.render):
            with pytest.raises((ValueError, TypeError)):
                draw(current, previous(**old_rules, **bad))


@pytest.mark.parametrize("bad", [
    {"linked_game_executable": "9"}, {"game_executable": None}, {"linked_game_executable": None},
    {"linked_game_executable": -1}, {"linked_game_executable": 8_000_000}, {"game_executable": False},
    {"link_coverage_rules": ""}, {"game_executable": 8_000_000},
])
def test_invalid_inclusive_saved_linking_raises(bad):
    saved = inclusive_size()
    saved.update(bad)
    for change in (("retail-truth-3", "retail-truth-4"), ("authored-only", progress.LINK_COVERAGE_RULES)):
        with pytest.raises(ValueError, match="saved"):
            daily.rule_note(saved, change)
    with pytest.raises(ValueError, match="saved"):
        daily.saved_linking(saved)


def test_saved_linking_uses_upstream_inclusive_fields():
    assert daily.saved_linking(inclusive_size()) == (7_300_000, 7_515_906)
    assert daily.saved_linking(real_size()) == (6_898_514, 7_520_010)
    assert daily.saved_linking({}) is None
