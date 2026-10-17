#!/usr/bin/env python3
"""tools/variant_search.py: round loop, parallel scoring, regalloc-only blind phase."""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import variant_search as vs  # noqa: E402

RETAIL = bytes.fromhex("8b442404" "8b4808" "03c8" "c3")     # mov eax,[esp+4]; mov ecx,[eax+8]; add ecx,eax
REGALLOC = bytes.fromhex("8b542404" "8b4a08" "03ca" "c3")   # same with edx
STRUCTURAL = bytes.fromhex("33c0" "c3")


def test_classify():
    assert vs.classify(RETAIL, RETAIL) == "exact"
    assert vs.classify(REGALLOC, RETAIL) == "regalloc"
    assert vs.classify(STRUCTURAL, RETAIL) == "structural"


def test_parse_variants_drops_asm_and_duplicates():
    answer = ("```cpp\nint f(){return 1;}\n```\n```cpp\nint f(){return 1;}\n```\n"
              "```cpp\nint f(){__asm nop}\n```\n```c++\nint f(){return 2;}\n```")
    assert vs.parse_variants(answer, 16) == ["int f(){return 1;}\n", "int f(){return 2;}\n"]


def fake_scorer(table):
    """Scores by lookup: text -> compiled bytes (None = does not compile)."""
    def make(_slot):
        def score(text):
            compiled = table.get(text.strip())
            if compiled is None:
                return {"fitness": -1.0, "exact": False, "class": "compile-error"}
            exact = compiled == RETAIL
            return {"fitness": 1.0 if exact else vs.fitness(compiled, RETAIL), "exact": exact,
                    "class": vs.classify(compiled, RETAIL), "compiled": compiled, "target": RETAIL}
        return score
    return make


def run(tmp_path, table, answers, **kw):
    draft = tmp_path / "draft.cpp"
    draft.write_text("draft", encoding="latin-1")
    prompts = []

    def propose(prompt):
        prompts.append(prompt)
        return answers[min(len(prompts) - 1, len(answers) - 1)]
    result = vs.search(draft, "?f@@YAXXZ", 0x1000, len(RETAIL), model="m", propose=propose,
                       make_scorer=fake_scorer(table), out=tmp_path / "out", jobs=4, **kw)
    return result, prompts


def fenced(*texts):
    return "\n".join(f"```cpp\n{t}\n```" for t in texts)


def test_model_round_reaches_exact(tmp_path):
    table = {"draft": STRUCTURAL, "good": RETAIL, "meh": STRUCTURAL + b"\x90"}
    result, prompts = run(tmp_path, table, [fenced("meh", "broken", "good")], n=8)
    assert result["exact"] and result["stop"] == "exact"
    assert len(prompts) == 1 and "xor eax, eax" in prompts[0]  # the diff reached the model
    assert (tmp_path / "out" / "win.cpp").read_text(encoding="latin-1").strip() == "good"
    assert result["runner_model"] == "m"


def test_round_cap(tmp_path):
    table = {"draft": STRUCTURAL}
    result, prompts = run(tmp_path, table, [fenced("nope")], n=8, rounds=3)
    assert len(prompts) == 3 and not result["exact"] and result["stop"] == "round cap"


def test_regalloc_only_goes_blind_under_a_cap(tmp_path):
    table = {"draft": REGALLOC}
    result, prompts = run(tmp_path, table, [fenced("x")], n=8, permute_trials=10)
    assert prompts == []  # no model round is spent on register choice
    assert result["blind_trials"] <= 10 and result["stop"] == "regalloc: blind trial cap"


def test_n_band_enforced(tmp_path):
    with pytest.raises(ValueError):
        run(tmp_path, {"draft": STRUCTURAL}, [""], n=4)


# ----------------------------------------------------------------- exactness before fitness

def table_scorer(results):
    """Scores by lookup: text -> a full result dict (unknown text does not compile)."""
    def make(_slot):
        def score(text):
            return dict(results.get(text.strip(), {"fitness": -1.0, "exact": False,
                                                  "class": "compile-error"}))
        return score
    return make


def test_rank_puts_verified_exact_above_any_fitness():
    exact = {"fitness": 1.0, "exact": True}
    unresolved = {"fitness": 1.0, "exact": False}       # bytes equal, references unresolved
    assert vs.rank(exact) > vs.rank(unresolved)
    assert vs.better(exact, unresolved) and not vs.better(unresolved, exact)
    assert vs.rank({"fitness": 0.2, "exact": True}) > vs.rank({"fitness": 0.99, "exact": False})


def test_model_round_picks_exact_over_a_tied_non_exact(tmp_path):
    # a non-exact candidate that rounds to fitness 1.0 comes first in the reply
    results = {"draft": {"fitness": 0.5, "exact": False, "class": "structural",
                         "compiled": STRUCTURAL, "target": RETAIL},
               "tie": {"fitness": 1.0, "exact": False, "class": "structural",
                       "compiled": RETAIL, "target": RETAIL},
               "good": {"fitness": 1.0, "exact": True, "class": "exact",
                        "compiled": RETAIL, "target": RETAIL}}
    draft = tmp_path / "draft.cpp"
    draft.write_text("draft", encoding="latin-1")
    result = vs.search(draft, "?f@@YAXXZ", 0x1000, len(RETAIL), model="m",
                       propose=lambda prompt: fenced("tie", "good"),
                       make_scorer=table_scorer(results), out=tmp_path / "out", jobs=2, n=8)
    assert result["exact"] and result["stop"] == "exact"
    assert (tmp_path / "out" / "win.cpp").read_text(encoding="latin-1").strip() == "good"


def test_exact_replaces_an_incumbent_with_equal_fitness(tmp_path):
    results = {"draft": {"fitness": 1.0, "exact": False, "class": "structural",
                         "compiled": RETAIL, "target": RETAIL},
               "good": {"fitness": 1.0, "exact": True, "class": "exact",
                        "compiled": RETAIL, "target": RETAIL}}
    draft = tmp_path / "draft.cpp"
    draft.write_text("draft", encoding="latin-1")
    result = vs.search(draft, "?f@@YAXXZ", 0x1000, len(RETAIL), model="m",
                       propose=lambda prompt: fenced("good"),
                       make_scorer=table_scorer(results), out=tmp_path / "out", jobs=2, n=8)
    assert result["exact"]


def test_blind_phase_keeps_exact_over_equal_fitness(monkeypatch):
    calls = iter(["a", "b"])
    monkeypatch.setattr(vs, "blind_mutate", lambda text, rng: next(calls, text))
    results = {"a": {"fitness": 0.9, "exact": False, "class": "regalloc"},
               "b": {"fitness": 0.9, "exact": True, "class": "exact"}}
    incumbent = {"fitness": 0.9, "exact": False, "class": "regalloc"}
    text, best, spent = vs.blind_phase("start", incumbent, table_scorer(results), 2, 1, 0)
    assert best["exact"] and text == "b"


def test_non_exact_fitness_stays_below_one():
    # identical bytes with unresolved references must not score as a perfect 1.0
    assert vs.non_exact_fitness(RETAIL, RETAIL) < 1.0


# ----------------------------------------------------------------- busy scorers

def test_score_all_never_shares_a_busy_scorer():
    import threading
    import time as _time
    busy, overlaps, lock = set(), [], threading.Lock()

    def make(slot):
        def score(text):
            with lock:
                if slot in busy:
                    overlaps.append(slot)
                busy.add(slot)
            _time.sleep(0.02 if int(text) % 3 else 0.001)   # uneven durations
            with lock:
                busy.discard(slot)
            return {"fitness": 0.1, "exact": False, "class": "structural"}
        return score
    results = vs.score_all([str(i) for i in range(40)], make, 4)
    assert len(results) == 40 and all(r is not None for r in results)
    assert overlaps == []
