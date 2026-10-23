#!/usr/bin/env python3
"""Two-agent agreement on an inferred name: one definition for the lane that
records votes (tools/name_lane.py) and the engine that lands names
(tools/rename.py).

The owner rule is that a name nobody can prove lands only when two
independent agents proposed it blind and agreed. Two things make that rule
checkable instead of asserted:

  workers   every vote carries the identity of the worker that cast it, taken
            from the environment, not from a flag the caller types. A session
            label (`--session`) is a free string, so one agent could serve
            itself twice under two labels and outvote nobody but itself; the
            worker identity is BFME_CLAIM_OWNER or BFME_RUN_ID (the identity
            tools/claims.py claims under -- an orchestrator gives each seat its
            own), else the harness's CLAUDE_CODE_SESSION_ID, else
            tools/claims.py's default owner. It is stored hashed (w-<12 hex>),
            so no user, host or session id enters the repository. Agreement
            counts distinct workers, never distinct session labels.
  votes     reverse/name_votes.csv (append-only, union-merged) holds each vote
            as sha256(key|canon(name))[:24]. The agreement record in
            reverse/name_agreed.csv is only an index into those votes: the
            engine recomputes the agreement from them (two or more distinct
            workers voted the landed spelling's hash, no rival spelling has as
            many, the record and the spelling are not disputed), so a
            hand-written agreement row authorises nothing.

canon() folds word order, plurals and common abbreviations, so
m_ladderComboBox and m_comboBoxLadder are one vote.

    python3 tools/name_agreement.py whoami      # this environment's worker id
"""
import argparse
import collections
import hashlib
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

VOTES = "reverse/name_votes.csv"
AGREED = "reverse/name_agreed.csv"
VOTE_COLUMNS = ["key", "hash", "model", "session", "worker", "date"]
AGREED_COLUMNS = ["id", "kind", "old", "new", "rva", "agents", "key", "status", "detail"]
SYNONYMS = {"num": "count", "number": "count", "cnt": "count", "idx": "index", "len": "length", "pos": "position",
            "str": "string", "msg": "message", "btn": "button", "wnd": "window", "tex": "texture", "obj": "object"}
WORKER = re.compile(r"w-[0-9a-f]{12}")


def canon(name):
    """Word order, plurals and common abbreviations are style, not meaning."""
    words = re.findall(r"[A-Z]+(?![a-z])|[A-Z]?[a-z]+|\d+", re.sub(r"^[msg]_", "", name or ""))
    words = [SYNONYMS.get(w.lower(), w.lower()) for w in words]
    return " ".join(sorted(w[:-1] if len(w) > 3 and w.endswith("s") else w for w in words))


def digest(key, name):
    return hash_canon(key, canon(name))


def hash_canon(key, canonical):
    return hashlib.sha256(f"{key}|{canonical}".encode()).hexdigest()[:24]


def worker_identity(root=None):
    """This environment's worker id, `w-<12 hex>`. The raw identity is
    BFME_CLAIM_OWNER / BFME_RUN_ID through tools/claims.py's owner(), else
    CLAUDE_CODE_SESSION_ID, else claims.owner()'s default (branch or
    user@host/checkout): never a value the voter passes on the command line."""
    env = os.environ
    if env.get("BFME_CLAIM_OWNER") or env.get("BFME_RUN_ID") or not env.get("CLAUDE_CODE_SESSION_ID"):
        import claims
        raw = "owner:" + claims.owner(root)
    else:
        raw = "session:" + env["CLAUDE_CODE_SESSION_ID"]
    return "w-" + hashlib.sha256(raw.encode("utf-8")).hexdigest()[:12]


def tally(votes):
    """key -> hash -> {worker: model}. A vote without a well-formed worker id
    counts for nothing: it cannot be told apart from its voter's other votes."""
    out = collections.defaultdict(lambda: collections.defaultdict(dict))
    for v in votes:
        worker = (v.get("worker") or "").strip()
        if WORKER.fullmatch(worker):
            out[v.get("key", "")][v.get("hash", "")][worker] = v.get("model", "")
    return out


def disputed(agreed_rows):
    """key -> canon spellings a dispute refused for it."""
    out = collections.defaultdict(set)
    for row in agreed_rows:
        if row.get("status") == "disputed":
            out[row.get("key", "")].add(canon(row.get("new", "")))
    return out


def wins(mine, rivals, *, lead=2, min_models=1):
    """`mine` and each rival are {worker: model} for one spelling. Two
    distinct workers agree, from at least `min_models` models, and the name
    leads every rival spelling by `lead` workers: when another worker named
    the thing differently, two workers sharing a guess is not enough."""
    return (len(mine) >= 2 and len(set(mine.values())) >= min_models
            and len(mine) - max((len(r) for r in rivals), default=0) >= lead)


def standing(votes, agreed_rows, key, name):
    """(mine, rivals) for spelling `name` of `key`: the workers that voted its
    hash, and the voter sets of every other spelling not refused by a dispute."""
    counts = tally(votes)[key]
    gone = {hash_canon(key, c) for c in disputed(agreed_rows).get(key, ())}
    h = digest(key, name)
    return dict(counts.get(h, {})), [v for h2, v in counts.items() if h2 != h and h2 not in gone]


def verify(votes, agreed_rows, key, name, *, lead=1):
    """Problems (empty when the votes carry `name` for `key`): the floor the
    engine enforces whatever --lead the lane ran with -- two distinct workers
    and no rival spelling with as many (`lead` 1) -- and the spelling and
    the record not disputed."""
    problems = []
    if canon(name) in disputed(agreed_rows).get(key, ()):
        problems.append(f"{name} was disputed for {key}")
    mine, rivals = standing(votes, agreed_rows, key, name)
    if len(mine) < 2:
        problems.append(f"{len(mine)} distinct worker(s) voted it in {VOTES} (two are needed)")
    top = max((len(r) for r in rivals), default=0)
    if mine and len(mine) - top < lead:
        problems.append(f"a rival spelling has {top} worker(s) against its {len(mine)}")
    return problems


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("whoami", help="print this environment's worker id")
    args = ap.parse_args(argv)
    if args.cmd == "whoami":
        print(worker_identity())
    return 0


if __name__ == "__main__":
    sys.exit(main())
