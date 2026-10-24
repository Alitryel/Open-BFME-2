"""The requested reference packet lane must not require other queue reports."""
import json
import sys
from pathlib import Path
import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import next_work
import build


@pytest.fixture
def packet_environment(tmp_path, monkeypatch):
    """Real packet/log readers; no retail files, shared claims or cache writes."""
    import repair_queue
    from types import SimpleNamespace

    packets = tmp_path / "reverse" / "zh_sweep" / "packets"
    packets.mkdir(parents=True)
    for rva, name, size in [(0x0F000100, "Ready", 64),
                            (0x0F000200, "Unproven", 48),
                            (0x0F000300, "Busy", 80),
                            (0x0F000400, "Retired", 96),
                            (0x0F000500, "Landed", 112)]:
        (packets / f"0x{rva:08X}.md").write_text(
            f"- {size} bytes, unclaimed by any ledger row\n"
            "- best Zero Hour candidate agrees on 90.0% of the bytes outside relocation sites\n"
            f"- `{name}`\n  in `GeneralsMD/{name}.cpp`\n\n"
            "## Callee pins\n\n```\n(no relative calls in this body)\n```\n",
            encoding="utf-8")
    log = tmp_path / "reverse" / "re_attempts.log"
    log.write_text("Retired\t0x0F000400\t96\tno-boundary\tmeasured inside another body\n",
                   encoding="utf-8")
    monkeypatch.setattr(next_work, "ROOT", tmp_path)
    monkeypatch.setattr(next_work, "PACKETS", packets)
    monkeypatch.setattr(next_work.re_log, "RE_ATTEMPTS", log)
    monkeypatch.setattr(next_work, "check_ledger", lambda: "ledger healthy")
    monkeypatch.setattr(build, "load_claim_rows", lambda **kwargs: [
        {"target_rva": "0x0F000500", "target_size": "112", "name": "Landed"}])
    monkeypatch.setattr(next_work.claims, "busy_rvas", lambda: {0x0F000300})

    def unexpected_claim(*args, **kwargs):
        raise AssertionError("a ranked view must not take or settle shared claims")

    monkeypatch.setattr(next_work.claims, "claim", unexpected_claim)
    monkeypatch.setattr(next_work.claims, "settle", unexpected_claim)
    monkeypatch.setattr(next_work, "structural_validator", lambda: SimpleNamespace(
        check_start=lambda rva: (None if rva == 0x0F000200 else True, "fixture")))
    monkeypatch.setattr(next_work.wb_context, "lead", lambda rva: None)
    monkeypatch.setattr(next_work, "wpo_detect", None)
    monkeypatch.setattr(repair_queue, "dest_tu",
                        lambda rva: {"dest": "Code/PacketHome.cpp", "basis": "fixture"})
    for name in ("drift_quick_wins", "structural_candidates"):
        monkeypatch.setattr(next_work, name, lambda *args, **kwargs: [])
    for name in ("reloc_named_candidates", "anchored_candidates", "ghidra_absent_candidates"):
        monkeypatch.setattr(next_work, name, lambda *args, **kwargs: ([], "empty fixture"))
    monkeypatch.setattr(repair_queue, "all_repair_items", lambda: [])
    monkeypatch.setattr(repair_queue, "link_items", lambda: ([], ""))
    monkeypatch.setattr(repair_queue, "repair_turn", lambda every: False)
    next_work.re_log._reset()
    try:
        yield packets
    finally:
        next_work.re_log._reset()


def run_queue(monkeypatch, capsys, *args):
    monkeypatch.setattr(sys, "argv", ["next_work.py", *args])
    next_work.main()
    return capsys.readouterr().out


@pytest.mark.parametrize("tier", [(), ("--tier", "packet")])
def test_ranked_json_contains_filtered_packets(packet_environment, monkeypatch, capsys, tier):
    output = json.loads(run_queue(monkeypatch, capsys, *tier, "--ranked", "--json"))
    packets = output["packets"]
    assert [item["function"] for item in packets] == ["Ready", "Unproven"]
    assert [item["landability"]["label"] for item in packets] == [
        "landable", "unproven-boundary"]
    assert all(item["dest"] == "Code/PacketHome.cpp" for item in packets)
    assert output["suppressed_logged"] == 1
    assert {"ledger", "reloc_named", "drift_quick_wins", "structural",
            "ghidra_absent", "wb_leads", "repair", "link", "shard"} <= output.keys()


def test_ranked_packets_can_include_prior_boundary_findings(packet_environment, monkeypatch, capsys):
    output = json.loads(run_queue(monkeypatch, capsys, "--tier", "packet",
                                  "--ranked", "--json", "--include-logged"))
    packets = {item["function"]: item for item in output["packets"]}
    assert set(packets) == {"Ready", "Unproven", "Retired"}
    assert packets["Retired"]["prior_attempt"]["evidence"] == "measured inside another body"
    assert output["suppressed_logged"] == 0


@pytest.mark.parametrize("tier", [(), ("--tier", "packet")])
@pytest.mark.parametrize("limit", [1, 10])
def test_ranked_text_shows_packet_instructions(packet_environment, monkeypatch, capsys, tier, limit):
    output = run_queue(monkeypatch, capsys, *tier, "--ranked", "--limit", str(limit))
    assert "Zero Hour work packets (2)" in output
    assert "Ready" in output
    assert "reverse/zh_sweep/packets/0x0F000100.md" in output
    assert "port GeneralsMD/Ready.cpp" in output
    assert ("Unproven" in output) == (limit > 1)
    assert "Busy" not in output and "Retired" not in output and "Landed" not in output
    assert "selected work" not in output
    if tier:
        assert "drift quick wins" not in output and "structural reconciliation" not in output


def test_packet_selection_still_uses_the_best_band(packet_environment, monkeypatch, capsys):
    output = json.loads(run_queue(monkeypatch, capsys, "--tier", "packet", "--json"))
    assert output["selection"]["function"] == "Ready"
    assert output["selection_meta"]["pool"] == 1
    assert output["selection_meta"]["packets_set_aside"] == 1
    assert output["selection_meta"]["suppressed_logged"] == 1


def test_unproven_packets_remain_visible_but_do_not_preempt_by_default(
        packet_environment, monkeypatch, capsys):
    (packet_environment / "0x0F000100.md").unlink()
    ranked = json.loads(run_queue(monkeypatch, capsys, "--ranked", "--json"))
    assert [item["function"] for item in ranked["packets"]] == ["Unproven"]
    selected = json.loads(run_queue(monkeypatch, capsys, "--json"))
    assert selected["selection"] is None
    assert selected["selection_meta"]["packets_withheld"] == 1
    explicit = json.loads(run_queue(monkeypatch, capsys, "--tier", "packet", "--json"))
    assert explicit["selection"]["function"] == "Unproven"


def test_packet_lane_is_independent_of_drift_reports(monkeypatch, capsys):
    def unrelated(*args, **kwargs):
        raise AssertionError("packet selection loaded an unrelated report")

    monkeypatch.setattr(sys, "argv", ["next_work.py", "--tier", "packet", "--json"])
    monkeypatch.setattr(next_work, "check_ledger", lambda: "ledger healthy")
    monkeypatch.setattr(build, "load_claim_rows", lambda **kwargs: [])
    monkeypatch.setattr(next_work.claims, "busy_rvas", lambda: set())
    for name in ["drift_quick_wins", "structural_candidates", "ghidra_absent_candidates",
                 "reloc_named_candidates", "anchored_candidates"]:
        monkeypatch.setattr(next_work, name, unrelated)
    seen = []
    def packets(claimed):
        seen.append(claimed)
        return []
    monkeypatch.setattr(next_work, "packet_candidates", packets)

    next_work.main()
    output = json.loads(capsys.readouterr().out)
    assert output["ledger"] == "ledger healthy"
    assert output["tier"] == "Zero Hour work packet"
    assert output["selection"] is None
    assert seen == [set()]


@pytest.mark.parametrize("options", [[], ["--ranked"], ["--ranked", "--json"]])
def test_packet_lane_still_refuses_an_invalid_ledger(monkeypatch, options):
    monkeypatch.setattr(sys, "argv", ["next_work.py", "--tier", "packet", *options])
    def invalid():
        raise SystemExit(2)
    def premature(*args, **kwargs):
        raise AssertionError("invalid ledger reached packet selection")
    monkeypatch.setattr(next_work, "check_ledger", invalid)
    monkeypatch.setattr(next_work, "packet_candidates", premature)
    with pytest.raises(SystemExit) as error:
        next_work.main()
    assert error.value.code == 2
