"""tools/name_lane.py on a miniature tree: a temporary git repository with
small ledgers and one source, so serving, blind hashed voting, agreement
(two sessions agreeing, disagreeing, ties), landing through tools/rename.py
and disputes all run without the real ledger or a compiler (verification is
injected). A real-tree `next --list-only` smoke closes the file."""
import csv
import io
import json
import os
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import name_agreement  # noqa: E402
import name_lane  # noqa: E402
import rename  # noqa: E402

SOURCE = "Code/Game/Box.cpp"
FN = "?rva00401000@@YAHPAURva00401000Box@@H@Z"
BOX = """// cl: /O2
struct Rva00401000Box {
    int m_x2C;
    int m_count;
};
int g_00A01000;
int rva00401000(Rva00401000Box *param_1, int a2)
{
    int iVar3 = param_1->m_x2C + a2;
    g_00A01000 = iVar3;
    return iVar3;
}
"""
SLOW = """// cl: /Od
struct Rva00402000Slow { int m_x10; int m_y; };
int rva00402000(Rva00402000Slow *param_1)
{
    int iVar1 = param_1->m_x10;
    return iVar1 + param_1->m_x10;
}
"""
FILES = {
    "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n"
                             f"{FN},,0x00401000,20,{SOURCE},matched,\n"
                             "?rva00402000@@YAHPAURva00402000Slow@@@Z,,0x00402000,12,Code/Game/Slow.cpp,matched,\n",
    "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n"
                             f"?g_00A01000@@3HA,0x00A01000,rva,4,.data,{SOURCE},matched,ev,m\n",
    "reverse/symbols.csv": "name,address,notes\n",
    "reverse/deleted_rows.csv": "name,target_rva,reason\n",
    SOURCE: BOX,
    "Code/Game/Slow.cpp": SLOW,
}


def _git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True, text=True).stdout


@pytest.fixture
def tree(tmp_path):
    for rel, text in FILES.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    return tmp_path


@pytest.fixture(autouse=True)
def seat(monkeypatch):
    """Each test sets its seats' worker identity through BFME_CLAIM_OWNER."""
    monkeypatch.setenv("BFME_CLAIM_OWNER", "seat-default")


def be(worker):
    os.environ["BFME_CLAIM_OWNER"] = worker


def lane_of(root):
    return name_lane.Lane(root, rename.Context(root, object_scan=False))


def rows(root, rel):
    path = root / rel
    return list(csv.DictReader(io.StringIO(path.read_text(encoding="utf-8")))) if path.exists() else []


def serve(root, session, model="claude-opus-5-5", worker=None, **kw):
    be(worker or f"seat-{session}")
    args = SimpleNamespace(session=session, model=model, count=1, file=kw.get("file", SOURCE), list_only=False)
    assert name_lane.cmd_next(lane_of(root), args) == 0
    return json.loads((root / f"build/name_lane/sessions/{session}.json").read_text())


def vote(root, tmp_path, session, answers, model="claude-opus-5-5", lead=2, min_models=1, worker=None):
    serve(root, session, model, worker)
    answer = tmp_path / f"answer-{session}.json"
    answer.write_text(json.dumps(answers))
    args = SimpleNamespace(answer=str(answer), session=session, model=model)
    return name_lane.cmd_submit(lane_of(root), args, lead=lead, min_models=min_models)


def ok_verify(ctx, sources):
    return True


def no_checks(ctx, plan):
    return []


def apply(root, **kw):
    args = SimpleNamespace(retry_blocked=kw.get("retry_blocked", False), lead=2, min_models=1, claim=False)
    return name_lane.cmd_apply(lane_of(root), args, verify=kw.get("verify", ok_verify), checks=no_checks)


FN_KEY = name_lane.key_of(SOURCE, "function", "0x00401000", "rva00401000")
MEMBER_KEY = name_lane.key_of(SOURCE, "member", "Rva00401000Box", "m_x2C")
PARAM_KEY = name_lane.key_of(SOURCE, "param", "rva00401000", "param_1")


# ---------------------------------------------------------------- pure rules

def test_canon_folds_order_plurals_synonyms():
    assert name_lane.canon("m_ladderComboBox") == name_lane.canon("m_comboBoxLadder")
    assert name_lane.canon("numItems") == name_lane.canon("itemCount")
    assert name_lane.digest("k", "boxIndex") == name_lane.digest("k", "idxBox")
    assert name_lane.digest("k", "boxIndex") != name_lane.digest("other", "boxIndex")


def test_wins_rules():
    two = {"s1": "a", "s2": "a"}
    assert name_lane.wins(two, [])
    assert not name_lane.wins({"s1": "a"}, [])
    assert not name_lane.wins(two, [{"s3": "a"}])                  # tie-ish: lead 1
    assert name_lane.wins(two, [{"s3": "a"}], lead=1)
    assert not name_lane.wins(two, [], min_models=2)
    assert name_lane.wins({"s1": "a", "s2": "b"}, [], min_models=2)


def test_owned_kinds(tree):
    items = lane_of(tree).owned(SOURCE)
    got = {(k, s, i) for k, s, i, _ in items}
    assert ("class", "", "Rva00401000Box") in got
    assert ("member", "Rva00401000Box", "m_x2C") in got
    assert ("member", "Rva00401000Box", "m_count") not in got        # real name
    assert ("function", "0x00401000", "rva00401000") in got
    assert ("param", "rva00401000", "param_1") in got and ("param", "rva00401000", "a2") in got
    assert ("local", "rva00401000", "iVar3") in got
    assert ("global", "", "g_00A01000") in got


def test_owned_skips_locals_under_od(tree):
    got = {(k, i) for k, _, i, _ in lane_of(tree).owned("Code/Game/Slow.cpp")}
    assert ("param", "param_1") in got and ("local", "iVar1") not in got


def test_owned_keeps_donor_spelled_weak_params(tree):
    """WWMath's own Dot_Product(const Vector3 &a, const Vector3 &b): a weak
    spelling the donor wrote is not served; a placeholder always is."""
    donor = tree / "reference/open-bfme-1/game/Libraries/vector3.h"
    donor.parent.mkdir(parents=True)
    donor.write_text("inline float Dot_Product(const Vector3 &a, const Vector3 &b) { return 0; }\n"
                     "x = Dot_Product(v, w);\n")
    src = tree / SOURCE
    src.write_text(BOX + "static inline int Dot_Product(const int &a, const int &w, int param_3)"
                         " { return a + w + param_3; }\n")
    got = {i for _, s, i, _ in lane_of(tree).owned(SOURCE) if s == "Dot_Product"}
    assert got == {"w", "param_3"}      # w appears only in a call, param_3 is a placeholder


def test_owned_ignores_macros_in_class_bodies(tree):
    """A #define/#undef inside a class body (DrawablePhysicsXformTreads.cpp's
    BFME_AI_SLOT(n) slot table) is not a member declaration."""
    src = tree / SOURCE
    src.write_text(BOX + "class Rva00402000View\n{\npublic:\n#define BFME_SLOT(n) virtual void slot##n();\n"
                         "\tBFME_SLOT(00) BFME_SLOT(01)\n\tvirtual int slot02();\n\tint m_x10;\n#undef BFME_SLOT\n};\n"
                         "int use(Rva00402000View *v) { return v->m_x10 + v->m_x10; }\n")
    got = {(k, s, i) for k, s, i, _ in lane_of(tree).owned(SOURCE)}
    assert ("member", "Rva00402000View", "m_x10") in got
    assert not any(i == "BFME_SLOT" for _, _, i in got)


def test_owned_skips_members_of_classes_other_files_view(tree):
    """A placeholder member of a class another file also defines (Object's many
    private views) is renamed across every view: not this file's to decide."""
    other = tree / "Code/Game/Other.cpp"
    other.write_text("struct Rva00401000Box { int m_x2C; int m_count; };\n")
    _git(tree, "add", "-A")
    got = {(k, i) for k, _, i, _ in lane_of(tree).owned(SOURCE)}
    assert ("member", "m_x2C") not in got
    assert ("param", "param_1") in got


def test_problem_rules(tree):
    lane = lane_of(tree)
    words = {"m_count", "rva00401000"}
    assert lane.problem("member", "m_x2C", "health", words) == "members are m_camelCase"
    assert lane.problem("member", "m_x2C", "m_count", words) == "collides with a name already in the file"
    assert lane.problem("class", "X", "boxThing", words) == "types are CamelCase"
    assert lane.problem("param", "a2", "Delta", words) == "params and locals are camelCase"
    assert lane.problem("param", "a2", "tmp", words) == "still a placeholder"
    assert lane.problem("function", "f", "data", words) == "too generic to help a reader"
    assert lane.problem("function", "f", "Rva00401000", words) == "still a placeholder"
    assert lane.problem("function", "f", "int", words) == "not a C++ identifier"
    assert lane.problem("member", "m_x2C", "m_width", words) is None


# ---------------------------------------------------------------- next

def test_next_writes_brief_and_list_only_writes_nothing(tree, capsys):
    args = SimpleNamespace(session="s1", model="claude-opus-5-5", count=1, file=None, list_only=True)
    name_lane.cmd_next(lane_of(tree), args)
    listed = json.loads(capsys.readouterr().out)
    assert {e["file"] for e in listed} <= {SOURCE, "Code/Game/Slow.cpp"} and listed
    assert not (tree / "build/name_lane").exists()
    served = serve(tree, "s1")
    brief = (tree / "build/name_lane/briefs/s1.txt").read_text()
    assert "types CamelCase, members m_camelCase" in brief and "Rva00401000Box::m_x2C" in brief
    assert "int rva00401000(Rva00401000Box *param_1, int a2)" in brief
    assert SOURCE in served["files"]


# ---------------------------------------------------------------- submit

def test_two_sessions_agree(tree, tmp_path):
    assert vote(tree, tmp_path, "s1", {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "sumBox"}) == 0
    votes = (tree / name_lane.VOTES).read_text()
    assert "m_boxWidth" not in votes and "sumBox" not in votes            # hashes only
    assert not rows(tree, name_lane.AGREED)
    vote(tree, tmp_path, "s2", {"Rva00401000Box::m_x2C": "m_widthBox", "rva00401000": "skip"},
         model="gpt-6.1-sol")
    agreed = rows(tree, name_lane.AGREED)
    assert [(r["key"], r["new"], r["status"]) for r in agreed] == [(MEMBER_KEY, "m_widthBox", "agreed")]
    be("seat-s1")
    w1 = name_agreement.worker_identity()
    be("seat-s2")
    w2 = name_agreement.worker_identity()
    assert set(agreed[0]["agents"].split(";")) == {f"{w1}@claude-opus-5-5", f"{w2}@gpt-6.1-sol"}
    assert agreed[0]["id"].startswith("nl-")
    assert all(name_agreement.WORKER.fullmatch(r["worker"]) for r in rows(tree, name_lane.VOTES))
    assert agreed[0]["old"] == "m_x2C" and agreed[0]["kind"] == "member"


def test_disagreement_and_tie(tree, tmp_path):
    vote(tree, tmp_path, "s1", {"rva00401000": "sumBox"})
    vote(tree, tmp_path, "s2", {"rva00401000": "addBoxWidth"})
    vote(tree, tmp_path, "s3", {"rva00401000": "sumBox"})                 # 2 vs 1: lead 1, not enough
    assert not rows(tree, name_lane.AGREED)
    vote(tree, tmp_path, "s4", {"rva00401000": "boxSum"})                 # 3 vs 1
    agreed = rows(tree, name_lane.AGREED)
    assert [(r["key"], r["new"]) for r in agreed] == [(FN_KEY, "boxSum")]
    assert agreed[0]["rva"] == "0x00401000"


def test_session_votes_once_and_bad_names_rejected(tree, tmp_path, capsys):
    vote(tree, tmp_path, "s1", {"rva00401000": "sumBox", "rva00401000:a2": "Delta"})
    out = capsys.readouterr().out
    assert "params and locals are camelCase" in out
    serve_twice = SimpleNamespace(session="s1", model="claude-opus-5-5", count=1, file=SOURCE, list_only=False)
    name_lane.cmd_next(lane_of(tree), serve_twice)
    assert "no file is left" in capsys.readouterr().out
    with pytest.raises(SystemExit):
        vote(tree, tmp_path, "s2", {"nonexistent": "x"})


# ---------------------------------------------------------------- apply

def agree_on(tree, tmp_path, answers):
    vote(tree, tmp_path, "s1", answers)
    vote(tree, tmp_path, "s2", answers, model="gpt-6.1-sol")


def test_apply_lands_through_rename(tree, tmp_path):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width", "rva00401000": "sumBox",
                              "rva00401000:param_1": "box"})
    assert apply(tree) == 0
    text = (tree / SOURCE).read_text()
    assert "int m_width;" in text and "int sumBox(Rva00401000Box *box, int a2)" in text
    assert "box->m_width + a2" in text
    states = name_lane.Lane(tree).state()
    assert {states[k]["status"] for k in (FN_KEY, MEMBER_KEY, PARAM_KEY)} == {"landed"}
    basis = [b for b in rows(tree, "reverse/name_basis.csv") if b["kind"] != "carry"]
    assert {b["basis"] for b in basis} == {"inferred"} and len(basis) == 3
    assert {b["evidence"] for b in basis} == {f"agree:{states[k]['id']}" for k in (FN_KEY, MEMBER_KEY, PARAM_KEY)}
    assert any(r["name"] == "?sumBox@@YAHPAURva00401000Box@@H@Z" for r in rows(tree, "reverse/functions.csv"))
    assert any(r["name"] == FN for r in rows(tree, "reverse/deleted_rows.csv"))


def test_apply_blocked_restores(tree, tmp_path):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width"})
    before = (tree / SOURCE).read_bytes()
    apply(tree, verify=lambda ctx, sources: False)
    assert (tree / SOURCE).read_bytes() == before
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["status"] == "blocked"
    apply(tree, retry_blocked=True)
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["status"] == "landed"


def test_apply_stale_when_placeholder_gone(tree, tmp_path):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width"})
    path = tree / SOURCE
    path.write_text(path.read_text().replace("m_x2C", "m_height"))
    apply(tree)
    row = name_lane.Lane(tree).state()[MEMBER_KEY]
    assert row["status"] == "stale" and row["agents"] == ""


def test_rename_refuses_without_lane_record(tree):
    with pytest.raises(rename.Refusal):
        rename.plan_rename("member", ctx=rename.Context(tree, object_scan=False), cls="Rva00401000Box",
                           member="m_x2C", new="m_width", basis="inferred", evidence="agree:nl-000000000000")


# ---------------------------------------------------------------- dispute

def test_dispute_reverts_and_refuses_spelling(tree, tmp_path, capsys):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width", "rva00401000": "sumBox"})
    apply(tree)
    args = SimpleNamespace(keys=[MEMBER_KEY, FN_KEY], reason="offset 0x2C is the box height", claim=False)
    assert name_lane.cmd_dispute(lane_of(tree), args, verify=ok_verify, checks=no_checks) == 0
    text = (tree / SOURCE).read_text()
    assert "int m_x2C;" in text and "int rva00401000(" in text
    lane = name_lane.Lane(tree)
    state = lane.state()
    assert state[MEMBER_KEY]["status"] == "disputed" and state[MEMBER_KEY]["agents"] == ""
    assert "offset 0x2C" in state[MEMBER_KEY]["detail"]
    assert any(r["name"] == FN for r in rows(tree, "reverse/functions.csv"))
    # the record no longer authorises a rename, and the spelling is refused for the key
    with pytest.raises(rename.Refusal):
        rename.plan_rename("member", ctx=rename.Context(tree, object_scan=False), cls="Rva00401000Box",
                           member="m_x2C", new="m_width", basis="inferred",
                           evidence=f"agree:{state[MEMBER_KEY]['id']}")
    capsys.readouterr()
    vote(tree, tmp_path, "s3", {"Rva00401000Box::m_x2C": "m_width"})
    assert "disputed for this key" in capsys.readouterr().out
    # a different name can still be agreed and landed for the key
    vote(tree, tmp_path, "s4", {"Rva00401000Box::m_x2C": "m_height"})
    vote(tree, tmp_path, "s5", {"Rva00401000Box::m_x2C": "m_height"}, model="gpt-6.1-sol")
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["status"] == "agreed"
    apply(tree)
    assert "int m_height;" in (tree / SOURCE).read_text()
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["new"] == "m_height"
    # the reverting override is gone again
    with pytest.raises(rename.Refusal):
        rename.check_new_identifier("m_x2C", "member")


def test_dispute_needs_landed(tree):
    args = SimpleNamespace(keys=[MEMBER_KEY], reason="x", claim=False)
    with pytest.raises(SystemExit):
        name_lane.cmd_dispute(lane_of(tree), args)


# ---------------------------------------------------------------- review fix-2: one worker, one vote

def test_one_worker_under_two_session_labels_is_one_vote(tree, tmp_path, capsys):
    """Finding 1: `--session` is a label; the worker identity decides who voted."""
    vote(tree, tmp_path, "s1", {"rva00401000": "sumBox"}, worker="seat-same")
    capsys.readouterr()
    args = SimpleNamespace(session="s2", model="gpt-6.1-sol", count=1, file=SOURCE, list_only=False)
    be("seat-same")
    name_lane.cmd_next(lane_of(tree), args)
    assert "no file is left" in capsys.readouterr().out          # never served again, any label
    assert not rows(tree, name_lane.AGREED)


def test_one_worker_cannot_vote_twice_through_two_served_sessions(tree, tmp_path, capsys):
    serve(tree, "s1", worker="seat-same")
    serve(tree, "s2", worker="seat-same")                         # served before either voted
    for session in ("s1", "s2"):
        answer = tmp_path / f"a-{session}.json"
        answer.write_text(json.dumps({"rva00401000": "sumBox"}))
        be("seat-same")
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(answer=str(answer), session=session,
                                                            model="claude-opus-5-5"))
    assert "this worker already voted" in capsys.readouterr().out
    assert len(rows(tree, name_lane.VOTES)) == 1 and not rows(tree, name_lane.AGREED)


def test_submit_from_another_worker_is_refused(tree, tmp_path):
    serve(tree, "s1", worker="seat-a")
    answer = tmp_path / "a.json"
    answer.write_text(json.dumps({"rva00401000": "sumBox"}))
    be("seat-b")
    with pytest.raises(SystemExit, match="another worker"):
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(answer=str(answer), session="s1",
                                                            model="claude-opus-5-5"))
    be("seat-b")
    with pytest.raises(SystemExit, match="another worker"):
        name_lane.cmd_next(lane_of(tree), SimpleNamespace(session="s1", model="claude-opus-5-5", count=1,
                                                          file=SOURCE, list_only=False))


def test_worker_identity_sources(monkeypatch):
    monkeypatch.delenv("BFME_CLAIM_OWNER", raising=False)
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.setenv("CLAUDE_CODE_SESSION_ID", "abc")
    a = name_agreement.worker_identity()
    monkeypatch.setenv("CLAUDE_CODE_SESSION_ID", "abd")
    assert name_agreement.worker_identity() != a
    monkeypatch.setenv("BFME_CLAIM_OWNER", "seat-1")           # an orchestrator's seat wins
    b = name_agreement.worker_identity()
    monkeypatch.setenv("CLAUDE_CODE_SESSION_ID", "abc")
    assert name_agreement.worker_identity() == b and name_agreement.WORKER.fullmatch(b)
    assert "seat-1" not in b


def forge_agreement(tree, rid="nl-forged00000", agents="a@m;b@m"):
    with (tree / name_lane.AGREED).open("a") as handle:
        if handle.tell() == 0:
            handle.write(",".join(name_lane.AGREED_COLUMNS) + "\n")
        handle.write(f"{rid},member,m_x2C,m_width,,{agents},{MEMBER_KEY},agreed,forged\n")
    return f"agree:{rid}"


def plan_member(tree, evidence):
    return rename.plan_rename("member", ctx=rename.Context(tree, object_scan=False), cls="Rva00401000Box",
                              member="m_x2C", new="m_width", basis="inferred", evidence=evidence)


def add_vote(tree, name, worker, model="m"):
    with (tree / name_lane.VOTES).open("a") as handle:
        handle.write(f"{MEMBER_KEY},{name_agreement.digest(MEMBER_KEY, name)},{model},x,{worker},2026-10-21\n")


def test_rename_recomputes_agreement_from_votes(tree, tmp_path):
    """Finding 1: a hand-written agreed row with two agent strings authorises nothing."""
    with pytest.raises(rename.Refusal, match="0 distinct worker"):
        plan_member(tree, forge_agreement(tree, "nl-forged00001"))


def test_rename_counts_only_workers_with_an_identity(tree, tmp_path):
    vote(tree, tmp_path, "s1", {"Rva00401000Box::m_x2C": "m_width"})
    add_vote(tree, "m_width", "")                    # no worker id: counts for nothing
    add_vote(tree, "m_width", "bogus")
    with pytest.raises(rename.Refusal, match="1 distinct worker"):
        plan_member(tree, forge_agreement(tree))
    add_vote(tree, "m_width", "w-0123456789ab")      # a second worker's vote carries it
    assert plan_member(tree, forge_agreement(tree)).basis == "inferred"


def test_rename_refuses_a_tied_rival(tree, tmp_path):
    vote(tree, tmp_path, "s1", {"Rva00401000Box::m_x2C": "m_width"})
    vote(tree, tmp_path, "s2", {"Rva00401000Box::m_x2C": "m_width"})
    rid = name_lane.Lane(tree).state()[MEMBER_KEY]["id"]
    assert plan_member(tree, f"agree:{rid}").basis == "inferred"
    add_vote(tree, "m_height", "w-00000000000a")
    add_vote(tree, "m_height", "w-00000000000b")
    with pytest.raises(rename.Refusal, match="rival spelling has 2"):
        plan_member(tree, f"agree:{rid}")


# ---------------------------------------------------------------- review fix-2: dispute through the engine

def test_dispute_uses_the_engine_and_is_append_only(tree, tmp_path):
    """Finding 2: the dispute is rename.revert's exact inverse, recorded as
    basis `restored`; nothing monkeypatches rename.py."""
    agree_on(tree, tmp_path, {"rva00401000": "sumBox"})
    apply(tree)
    checks = (rename.check_new_identifier, rename.check_basis)
    before = rows(tree, "reverse/name_basis.csv")
    args = SimpleNamespace(keys=[FN_KEY], reason="it subtracts", claim=False)
    assert name_lane.cmd_dispute(lane_of(tree), args, verify=ok_verify, checks=no_checks) == 0
    assert (rename.check_new_identifier, rename.check_basis) == checks
    after = rows(tree, "reverse/name_basis.csv")
    assert after[:len(before)] == before                          # append-only
    restored = after[-1]
    assert (restored["kind"], restored["basis"]) == ("function", "restored")
    assert restored["old"] == "?sumBox@@YAHPAURva00401000Box@@H@Z" and restored["new"] == FN
    assert restored["evidence"].startswith("revert:nl-") and "it subtracts" in restored["evidence"]
    deleted = rows(tree, "reverse/deleted_rows.csv")
    assert not any(r["name"] == FN for r in deleted)               # the landing's tombstone is lifted
    assert any(r["name"] == "?sumBox@@YAHPAURva00401000Box@@H@Z" and "(restored)" in r["reason"]
               for r in deleted)
    ctx = rename.Context(tree, object_scan=False)
    assert rename.check_renames(ctx, rename.name_basis_rows(ctx)) == []
    # a union merge that brings the lifted line back is honoured by rename.py and reported by check
    with (tree / "reverse/deleted_rows.csv").open("a") as handle:
        handle.write(f'{FN},0x00401000,"Renamed to ?sumBox@@YAHPAURva00401000Box@@H@Z by tools/rename.py '
                     f'(inferred)"\n')
    ctx = rename.Context(tree, object_scan=False)
    assert (FN, 0x00401000) not in rename._tombstones(ctx)
    assert any("again" in p for p in rename.check_renames(ctx, rename.name_basis_rows(ctx)))


def test_revert_refuses_anything_but_the_exact_inverse(tree, tmp_path):
    agree_on(tree, tmp_path, {"rva00401000": "sumBox", "Rva00401000Box::m_x2C": "m_width"})
    apply(tree)
    rid = name_lane.Lane(tree).state()[FN_KEY]["id"]
    ctx = rename.Context(tree, object_scan=False)
    with pytest.raises(rename.Refusal, match="not the exact inverse"):
        rename.plan_rename("function", ctx=ctx, rva=0x00401000, new="rva00401999", basis="restored",
                           evidence=f"revert:{rid} wrong")
    with pytest.raises(rename.Refusal, match="reason"):
        rename.plan_rename("function", ctx=ctx, rva=0x00401000, new="rva00401000", basis="restored",
                           evidence=f"revert:{rid}")
    with pytest.raises(rename.Refusal, match="no inferred rename"):
        rename.revert(ctx, "nl-nothing", "because", claim=False, dry_run=True)
    with pytest.raises(rename.Refusal, match="placeholder"):     # restoring is not a back door
        rename.plan_rename("function", ctx=ctx, rva=0x00401000, new="rva00401000", basis="inferred",
                           evidence=f"agree:{rid}")
    rename.revert(ctx, rid, "because", claim=False, verify=ok_verify, checks=no_checks)
    with pytest.raises(rename.Refusal, match="already reverted"):
        rename.revert(rename.Context(tree, object_scan=False), rid, "again", claim=False, dry_run=True)


def test_revert_cli_dry_run(tree, tmp_path, capsys):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width"})
    apply(tree)
    rid = name_lane.Lane(tree).state()[MEMBER_KEY]["id"]
    before = (tree / SOURCE).read_bytes()
    assert rename.main(["revert", "--record", f"agree:{rid}", "--reason", "it is the height", "--dry-run",
                        "--no-claim", "--root", str(tree)]) == 0
    assert "Rename Rva00401000Box::m_width to m_x2C (restored)" in capsys.readouterr().out
    assert (tree / SOURCE).read_bytes() == before


# ---------------------------------------------------------------- real tree

def test_real_tree_list_only(capsys):
    lane = name_lane.Lane()
    if not (lane.root / "reverse/functions.csv").exists():
        pytest.skip("no real ledger")
    args = SimpleNamespace(session="pytest-smoke", model="claude-opus-5-5", count=2, file=None, list_only=True)
    assert name_lane.cmd_next(lane, args) == 0
    listed = json.loads(capsys.readouterr().out)
    assert len(listed) == 2
    for entry in listed:
        assert entry["file"].startswith("Code/") and not entry["file"].startswith(rename.GENERATED)
        assert entry["chars"] <= name_lane.MAX_CHARS and sum(entry["kinds"].values()) >= 1
    assert not (lane.root / "build/name_lane/sessions/pytest-smoke.json").exists()
