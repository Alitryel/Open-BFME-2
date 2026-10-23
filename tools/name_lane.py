#!/usr/bin/env python3
"""The inferred-name lane: a name nobody can prove lands only when two agents
proposed it blind and agreed.

Most placeholders (Rva..., bfme..., m_2C, param_1, iVar3) sit where no export,
WorldBuilder lead, Zero Hour twin or retail string says what the thing is
called; tools/name_evidence.py serves the few that do. For the rest the owner
rule is BFME 1's: a descriptive name that is not proven canonical still gets a
clean readable identifier, but only on blind agreement of two independent
agents, and the ledger -- reverse/name_basis.csv, written by tools/rename.py --
records it as `inferred`, revocable through `dispute`. BFME 1's 2026-09-29
spike measured why: one model alone named about 60% of placeholders right and
2-9% misleadingly; two independent proposals that agreed were about 80% right
and never misleading.

    python3 tools/name_lane.py next --session S --model M [--count N] [--file F] [--list-only]
    python3 tools/name_lane.py submit ANSWER.json --session S --model M
    python3 tools/name_lane.py apply [--retry-blocked] [--lead 2] [--min-models 1]
    python3 tools/name_lane.py dispute KEY... --reason TEXT
    python3 tools/name_lane.py status

`next` serves one matched, non-generated Code/ source with the identifiers
that file alone decides -- functions it owns rows for, classes only it
defines, their used members, parameters and locals (locals only where the unit
compiles optimised: under /Od a local's name can reorder the frame), and file
globals it owns data rows for -- that are placeholder or weak
(tools/name_metric.py's definition, which tools/rename.py shares), except a
weak parameter spelling (a, b, tmp) that the donor trees' own declaration of
that function uses -- the original programmer's, not a converter's. It writes a
brief to build/name_lane/briefs/<session>.txt: the fixed style rules, the keys
to answer, the file's text, callers spelling its functions, the retail strings
its rows reference and tools/name_evidence.py hints. A skip costs nothing; a
wrong name misleads readers.

`submit` stores each vote only as sha256(key|canon(name))[:24] in
reverse/name_votes.csv (append-only). canon() folds word order, plurals and
common abbreviations, so m_ladderComboBox and m_comboBoxLadder are one vote,
and no name text enters the repo until a second worker matches it -- a
worker cannot copy what it cannot read. Every vote and every served session
record carries the voter's worker identity (tools/name_agreement.py: hashed
BFME_CLAIM_OWNER / BFME_RUN_ID, else CLAUDE_CODE_SESSION_ID, else
tools/claims.py's owner), read from the environment rather than from
`--session`, which is only a label: `submit` refuses a session `next` served
to another worker, a worker votes once per key whatever label it uses, and
agreement counts distinct workers. An orchestrator running blind seats gives
each its own BFME_CLAIM_OWNER, as it already does for claims. When a vote
makes a name win (two distinct workers, a lead of `--lead` votes over every
rival spelling, optionally `--min-models` distinct models; files another
model voted on are served first), the name is written to
reverse/name_agreed.csv as `agreed`.

`apply` lands each agreed key through tools/rename.py's library API with
basis `inferred` and evidence `agree:<id>`; rename.py's check_agreement uses
that row only as an index (id,kind,old,new,rva,key) and recomputes the
agreement from the votes, then claims, rewrites every reference,
byte-verifies every touched unit and restores everything on any failure.
Outcomes are appended to name_agreed.csv: landed, blocked (the refusal or
failure), stale (the file changed or the placeholder is gone). `dispute`
puts landed names back through rename.py's own reversal entry point
(rename.revert: the exact inverse of the recorded inferred rename, recorded
append-only as basis `restored`), records the reason, and refuses that
spelling for the key from then on.

name_agreed.csv columns: id,kind,old,new,rva,agents,key,status,detail -- the
first six are rename.py's agreement record, `new` is the agreed name, `key`
is the lane key (source|kind|scope|placeholder). Both lane files are
append-only and union-merged; the latest row of a key is its state.
"""
import argparse
import collections
import csv
import datetime
import hashlib
import io
import json
import random
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import name_agreement  # noqa: E402
import name_metric  # noqa: E402
import rename  # noqa: E402

VOTES = name_agreement.VOTES
AGREED = name_agreement.AGREED
VOTE_COLUMNS = name_agreement.VOTE_COLUMNS
AGREED_COLUMNS = name_agreement.AGREED_COLUMNS
LANE_DIR = "build/name_lane"
EVIDENCE_TSV = "build/name_evidence.tsv"
MAX_CHARS = 15000
KINDS = ("function", "class", "member", "param", "local", "global")
NAMED = ("class", "member", "function", "global")
# rename order inside one file: a member's key names its class and a param's
# key names its function, so those land before the class or function moves
LAND_ORDER = {"member": 0, "param": 1, "local": 1, "global": 2, "function": 3, "class": 4}
FAMILY = re.compile(r"(?:a|d|dup|sub|uw|eh|tg|fun|nullsub|loc|j)_[0-9A-Fa-f]+")
GENERIC = {"data", "info", "value", "temp", "tmp", "helper", "thing", "stuff", "foo", "bar", "obj", "var", "func",
           "method", "unknown", "misc", "item", "object", "result", "ret", "field", "member", "param", "arg", "local"}
DIRECTIVE = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)
MACRO = re.compile(r"^[ \t]*#[ \t]*(?:define|undef)[ \t]+([A-Za-z_]\w*)", re.M)
STATUS_RANK = {"agreed": 0, "stale": 1, "blocked": 2, "landed": 3, "disputed": 4}


def fail(message):
    sys.exit(f"name_lane: {message}")


# ---------------------------------------------------------------- votes

canon = name_agreement.canon
digest = name_agreement.digest
wins = name_agreement.wins


def refuted(key, canons):
    """The vote hashes of a key's disputed spellings: they no longer count as rivals."""
    return {name_agreement.hash_canon(key, c) for c in canons}


def record_id(key, name):
    return "nl-" + hashlib.sha256(f"{key}|{name}".encode()).hexdigest()[:12]


def model_id(text):
    """A normalised model label: lower case, no spaces."""
    model = re.sub(r"\s+", "-", (text or "").strip().lower())
    if not re.fullmatch(r"[a-z0-9][a-z0-9._-]*", model):
        fail(f"--model {text!r}: pass the label you vote under, e.g. seat-a")
    return model


def session_id(text):
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9._-]{0,63}", text or ""):
        fail(f"--session {text!r}: letters, digits, '.', '_' or '-' (at most 64)")
    return text


# ---------------------------------------------------------------- the lane

class Lane:
    """The lane's view of one tree; tests point it at a miniature repository."""

    def __init__(self, root=ROOT, ctx=None):
        self.root = Path(root).resolve()
        self.ctx = ctx or rename.Context(self.root, object_scan=self.root == ROOT.resolve())
        self._types = {}
        self._donor = {}

    def path(self, rel):
        return self.root / rel

    def text(self, rel):
        data = self.ctx.read(rel)
        return data.decode("utf-8", errors="surrogateescape") if data is not None else None

    def git(self, *args):
        return subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True,
                              encoding="utf-8", errors="replace").stdout

    # ------------------------------------------------------------ tables

    def table(self, rel, columns):
        raw = self.path(rel).read_text(encoding="utf-8") if self.path(rel).exists() else ""
        rows = list(csv.DictReader(io.StringIO(raw)))
        if raw and next(csv.reader(io.StringIO(raw)), []) != columns:
            fail(f"{rel} has columns {next(csv.reader(io.StringIO(raw)))}, expected {columns}")
        return rows

    def append(self, rel, columns, rows):
        """Append under build/name_lane/.lock; the files are append-only."""
        from portable_lock import lock, unlock
        if not rows:
            return
        self.path(LANE_DIR).mkdir(parents=True, exist_ok=True)
        with self.path(f"{LANE_DIR}/.lock").open("a") as handle:
            lock(handle, exclusive=True, wait_notice="name_lane: waiting for the lane lock...")
            try:
                path = self.path(rel)
                raw = path.read_bytes() if path.exists() else b""
                out = io.StringIO()
                writer = csv.DictWriter(out, columns, lineterminator="\n")
                if not raw:
                    writer.writeheader()
                elif not raw.endswith(b"\n"):
                    out.write("\n")
                writer.writerows({c: r.get(c, "") for c in columns} for r in rows)
                with path.open("ab") as f:
                    f.write(out.getvalue().encode("utf-8"))
            finally:
                unlock(handle)
        self.ctx._cache.pop(rel, None)

    def votes(self):
        return self.table(VOTES, VOTE_COLUMNS)

    def agreed_rows(self):
        return self.table(AGREED, AGREED_COLUMNS)

    def state(self):
        """key -> its state row. A key's current record is its latest agreement
        id (a dispute refuses its spelling, so a re-agreement is a new id);
        within one id the highest status wins -- disputed, landed, blocked,
        stale, agreed -- because union merges may interleave concurrent rows.
        A later blocked row of the same rank (--retry-blocked) wins too."""
        by_key = collections.defaultdict(dict)
        for row in self.agreed_rows():
            by_key[row["key"]].setdefault(row["id"], []).append(row)
        out = {}
        for key, ids in by_key.items():
            rows = list(ids.values())[-1]
            best = rows[0]
            for row in rows[1:]:
                if STATUS_RANK.get(row["status"], -1) >= STATUS_RANK.get(best["status"], -1):
                    best = row
            out[key] = best
        return out

    def disputed(self):
        """key -> canon spellings refused for it."""
        return name_agreement.disputed(self.agreed_rows())

    def tally(self):
        """key -> hash -> {worker: model}: distinct workers, not session labels."""
        return name_agreement.tally(self.votes())

    def worker(self):
        """This environment's worker id (tools/name_agreement.py)."""
        return name_agreement.worker_identity(self.root)

    # ------------------------------------------------------------ evidence

    def ledger(self):
        if "_by_source" not in self.ctx._cache:
            by = collections.defaultdict(list)
            for r in self.ctx.rows():
                if r.get("status") == "matched":
                    by[r.get("source", "")].append(r)
            self.ctx._cache["_by_source"] = by
        return self.ctx._cache["_by_source"]

    def data_rows(self, rel):
        return [r for r in self.ctx.dicts(rename.DATA_ROWS) if r.get("source") == rel and r.get("status") == "matched"]

    def named_rvas(self):
        """RVAs another lane names: a WorldBuilder lead, an evidence-tier name or a
        canonical name_evidence candidate (rename.py refuses an inferred name there)."""
        if "_named_rvas" not in self.ctx._cache:
            out = {rename._rva(r.get("rva") or r.get("target_rva")) for r in self.ctx.dicts(rename.WB_LEADS)}
            out |= {rename._rva(r.get("target_rva")) for r in self.ctx.dicts(rename.NAME_TIERS)
                    if r.get("name_tier") == "evidence"}
            out |= {rename._rva(r.get("rva")) for r in self.evidence() if r.get("strength") == "canonical"}
            out.discard(None)
            self.ctx._cache["_named_rvas"] = out
        return self.ctx._cache["_named_rvas"]

    def evidence(self):
        if "_evidence" not in self.ctx._cache:
            raw = self.text(EVIDENCE_TSV) or ""
            self.ctx._cache["_evidence"] = list(csv.DictReader(io.StringIO(raw), delimiter="\t"))
        return self.ctx._cache["_evidence"]

    def strings(self):
        """rva -> retail strings it references (reverse/string_xrefs.tsv)."""
        if "_strings" not in self.ctx._cache:
            out = collections.defaultdict(list)
            for line in (self.text(rename.STRING_XREFS) or "").splitlines():
                if "\t" not in line:
                    continue
                text, refs = line.rsplit("\t", 1)
                for ref in refs.split(","):
                    rva = rename._rva(ref.strip())
                    if rva is not None:
                        out[rva].append(text)
            self.ctx._cache["_strings"] = out
        return self.ctx._cache["_strings"]

    def type_definers(self, word):
        """Files under Code/ and reference/shims/ that define `word` as a class or struct."""
        if word not in self._types:
            hits = self.git("grep", "-l", "-I", "-w", "-E", rf"(class|struct)[[:space:]]+{word}", "--",
                            *rename.SEARCH_ROOTS).split()
            self._types[word] = sorted(f for f in hits if not rename.is_generated(f)
                                       and word in name_metric.DECL.findall(name_metric.strip(self.text(f) or "")))
        return self._types[word]

    def header_type(self, word):
        """Some header (game or Zero Hour) declares `word`: a real class a stand-in may take."""
        if any(f.endswith(rename.HEADER_SUFFIXES) for f in self.type_definers(word)):
            return True
        zh = self.path(rename.BFME1) / rename.ZH_TREE
        if not zh.exists():
            return False
        result = subprocess.run(["grep", "-rlwE", "--include=*.h", rf"(class|struct)[[:space:]]+{word}", str(zh)],
                                capture_output=True, text=True)
        return bool(result.stdout.strip())

    def donor_params(self, functions):
        """{function word: parameter words} as the donor trees (Open-BFME-1's
        game/ and its Zero Hour reference) spell them in declarations. A weak
        spelling the donor wrote itself -- WWMath's Dot_Product(const Vector3 &a,
        const Vector3 &b) -- is the original programmer's, not a converter's
        invention, so the lane does not ask for a new one."""
        todo = sorted(w for w in set(functions) - set(self._donor) if re.fullmatch(r"[A-Za-z_]\w*", w))
        roots = [str(self.path(rename.BFME1) / d) for d in ("game", rename.ZH_TREE)]
        roots = [r for r in roots if Path(r).is_dir()]
        for w in todo:
            self._donor[w] = set()
        for i in range(0, len(todo) if roots else 0, 200):
            chunk = todo[i:i + 200]
            out = subprocess.run(["grep", "-rhoE", "--include=*.h", "--include=*.inl", "--include=*.cpp",
                                  rf"\b({'|'.join(chunk)})[[:space:]]*\([^()]*\)", *roots],
                                 capture_output=True, text=True, errors="replace").stdout
            for line in out.splitlines():
                m = re.match(r"(\w+)\s*\((.*)\)", line)
                if not m or m.group(1) not in self._donor:
                    continue
                for piece in m.group(2).split(","):
                    words = re.findall(r"[A-Za-z_]\w*", piece.split("=")[0])
                    if len(words) >= 2:         # a type and a name: a declaration, not a call
                        self._donor[m.group(1)].add(words[-1])
        return {w: self._donor.get(w, set()) for w in functions}

    # ------------------------------------------------------------ what a file decides

    def servable(self, rel):
        """A matched, hand-written Code/ C/C++ unit with no vendored, export or .lib row."""
        rows = self.ledger().get(rel, [])
        if not rows or not rel.startswith("Code/") or not rel.endswith((".cpp", ".c")):
            return False
        if rename.is_generated(rel) or "stlport" in rel.lower() or rename.is_vendored_path(self.ctx, rel):
            return False
        return not any("vendored=" in (r.get("notes") or "") or r.get("export_rva") for r in rows)

    def owned(self, rel, text=None):
        """[(kind, scope, ident, rva)] the file alone decides, in reading order.
        scope: a function's RVA (0x...), a member's class, a param's or
        local's function (name_metric.functions_in spelling, #N for overloads)."""
        text = self.text(rel) if text is None else text
        code = name_metric.strip(text)
        rows = self.ledger().get(rel, [])
        items = []
        decls = list(name_metric.DECL.finditer(code))
        for t in dict.fromkeys(m.group(1) for m in decls):
            if name_metric.placeholder(t) and self.type_definers(t) in ([], [rel]):
                items.append(("class", "", t, None))
        holders = collections.defaultdict(set)
        macros = set(MACRO.findall(code))
        for m in decls:
            # a #define/#undef inside a class body is not a declaration (BFME_AI_SLOT(n) slot tables)
            body = DIRECTIVE.sub("", code[m.end():name_metric.close(code, m.end() - 1)])
            for name in name_metric.members(body):
                if name not in macros:
                    holders[name].add(m.group(1))
        for name, classes in holders.items():
            # only a class this file alone defines: a member of a class with other views
            # (Object's 13 private copies) is renamed across all of them, not decided here
            if (len(classes) == 1 and name_metric.placeholder(name) and not name_metric.PAD.match(name)
                    and len(re.findall(rf"\b{re.escape(name)}\b", code)) > 1     # used, so not padding
                    and self.type_definers(next(iter(classes))) in ([], [rel])):
                items.append(("member", next(iter(classes)), name, None))
        scopes = collections.defaultdict(set)
        parsed = []
        for r in rows:
            name = r.get("name", "")
            if name.startswith(rename.FUNCLET_PREFIXES + ("$L",)) or "parent=" in (r.get("notes") or ""):
                continue
            try:
                _, word, _ = rename.split_function_name(name)
            except rename.Refusal:
                continue
            scope = rename.scope_of(name) or ""
            scopes[word].add(scope)
            parsed.append((word, rename._rva(r.get("target_rva")), name))
        named = self.named_rvas()
        seen_rvas = collections.Counter(rva for _, rva, _ in parsed)
        for word, rva, name in parsed:
            # one RVA per word in the file: a word shared by several scopes or rows is not this row's alone
            if (rva is not None and rva not in named and seen_rvas[rva] == 1 and len(scopes[word]) == 1
                    and sum(1 for w, _, _ in parsed if w == word) == 1 and name_metric.placeholder(word)
                    and not FAMILY.fullmatch(word) and re.search(rf"\b{re.escape(word)}\b", code)):
                items.append(("function", f"0x{rva:08X}", word, rva))
        optimised = None
        spans = list(name_metric.functions_in(code))
        # weak but not placeholder (a, b, tmp): the donor's own spelling stays
        donor = self.donor_params({base(scope) for scope, _, _, params in spans
                                   if any(name_metric.weak("param", n) and not name_metric.placeholder(n)
                                          for n in rename.parameters(params))})
        for scope, start, end, params in spans:
            items += [("param", scope, n, None) for n in rename.parameters(params) if name_metric.weak("param", n)
                      and (name_metric.placeholder(n) or n not in donor.get(base(scope), ()))]
            if optimised is None:
                optimised = rename.optimized(rename.compile_flags(self.ctx, rel)) and not re.search(
                    r'^[ \t]*#[ \t]*pragma[ \t]+optimize[ \t]*\([^)]*\boff\b', text, re.M)
            if optimised:       # /Od orders frame slots by identifier text: renaming a local moves bytes
                body = code[code.find("{", start):end]
                items += [("local", scope, n, None) for n in name_metric.local_names(body)
                          if name_metric.weak("local", n)]
        file_globals = set(name_metric.global_names(code))
        for r in self.data_rows(rel):
            word = rename._identifier(r.get("name", ""))
            if word and word in file_globals and name_metric.placeholder(word):
                items.append(("global", "", word, rename.data_rva(r)))
        seen, out = set(), []
        for kind, scope, ident, rva in items:
            slot = (scope, ident) if kind in ("param", "local") else ident
            if slot not in seen:
                seen.add(slot)
                out.append((kind, scope, ident, rva))
        return out

    # ------------------------------------------------------------ refusals

    def problem(self, kind, old, new, file_words):
        """Why `new` may not be voted for `old`, or None (BFME 1's problem())."""
        if not re.fullmatch(r"[A-Za-z_]\w*", new or "") or new in name_metric.KEYWORDS:
            return "not a C++ identifier"
        if new == old or name_metric.weak(kind if kind in ("param", "local") else "function", new):
            return "still a placeholder"
        if canon(new).replace(" ", "") in GENERIC:
            return "too generic to help a reader"
        if kind == "class" and not new[0].isupper():
            return "types are CamelCase"
        if kind == "member" and not re.fullmatch(r"m_[a-z]\w*", new):
            return "members are m_camelCase"
        if kind in ("param", "local") and not new[0].islower():
            return "params and locals are camelCase"
        if kind == "class" and self.type_definers(new) and not self.header_type(new):
            return f"{new} is another file's stand-in, not a class any header declares"
        if kind in NAMED and new in file_words:
            return "collides with a name already in the file"
        return None


def base(scope):
    """The function word of a param's or local's scope (Class::method#2 -> method)."""
    return scope.split("#")[0].split("::")[-1]


def key_of(rel, kind, scope, ident):
    return f"{rel}|{kind}|{scope}|{ident}"


def split_key(key):
    rel, kind, scope, ident = key.split("|")
    return rel, kind, scope, ident


def answer_key(kind, scope, ident):
    if kind in ("param", "local"):
        return f"{scope}:{ident}"
    if kind == "member":
        return f"{scope}::{ident}"
    return ident


# ---------------------------------------------------------------- next

def queue(lane, worker, model, only=None):
    """Files to serve, best first: one another model voted on (this vote can
    land names), then one another worker voted on, then the rest, shuffled.
    A file this worker already voted on is never served to it again, under
    any session label."""
    voted_sessions, voted_models = collections.defaultdict(set), collections.defaultdict(set)
    for v in lane.votes():
        rel = v["key"].split("|")[0]
        voted_sessions[rel].add(v.get("worker") or "")
        voted_models[rel].add(v["model"])
    files = [only] if only else [f for f in lane.ledger() if f.endswith((".cpp", ".c"))]
    files = [f for f in files if worker not in voted_sessions[f]]
    random.shuffle(files)
    files.sort(key=lambda f: (not (voted_models[f] - {model}), not voted_sessions[f]))
    return files, voted_sessions


def callers(lane, rel, word, limit=6):
    lines = []
    for f in lane.git("grep", "-l", "-I", "-w", "-F", "-e", word, "--", "Code").split():
        if f == rel or rename.is_generated(f):
            continue
        hit = next((l.strip() for l in (lane.text(f) or "").splitlines() if re.search(rf"\b{word}\b", l)), "")
        lines.append(f"  {f}: {hit[:110]}")
        if len(lines) == limit:
            break
    return lines


def brief_text(lane, rel, text, items, session, model):
    rows = lane.ledger().get(rel, [])
    lines = text.splitlines()

    code = name_metric.strip(text)
    spans = {scope: text[start:end].splitlines() for scope, start, end, _ in name_metric.functions_in(code)}

    def declared_at(ident, scope=None):
        uses = [l.strip() for l in spans.get(scope, lines) if re.search(rf"\b{re.escape(ident)}\b", l)]
        decl = re.compile(rf"(?:class|struct)\s+{re.escape(ident)}\b|[\w>*&]\s*[*&]?\s*\b{re.escape(ident)}\s*"
                          r"(?:\[[^\]]*\]\s*)*[;,=)(]")
        return next((l for l in uses if decl.search(l)), uses[0] if uses else "")[:90]

    listing = "\n".join(f"  {answer_key(k, s, i):44} {k:8} {declared_at(i, s if k in ('param', 'local') else None)}"
                        for k, s, i, _ in items)
    evidence = []
    for kind, scope, ident, rva in items:
        if kind == "function":
            found = callers(lane, rel, ident)
            if found:
                evidence.append(f"callers spelling {ident}:")
                evidence += found
    rvas = {rename._rva(r.get("target_rva")) for r in rows}
    for rva in sorted(r for r in rvas if r is not None):
        for s in lane.strings().get(rva, [])[:6]:
            evidence.append(f"  0x{rva:08X} references string {json.dumps(s[:100])}")
    hints = [e for e in lane.evidence() if rename._rva(e.get("rva")) in rvas]
    for e in hints[:10]:
        evidence.append(f"  hint 0x{rename._rva(e['rva']):08X} {e.get('current')} ~ {e.get('candidate')} "
                        f"({e.get('evidence_kind')}, {e.get('strength')}): {(e.get('detail') or '')[:140]}")
    return f"""NAME THE PLACEHOLDERS IN {rel}  (session {session}, model {model})

This is decompiled BFME 2 (SAGE engine) C++. A converter invented the names
below from addresses, offsets or decompiler slots. Give each the name its
original EA programmer most likely used, judging from what the code does and
the evidence. Style (fixed): types CamelCase, members m_camelCase, params and
locals camelCase, functions and methods camelCase unless the class already
uses CamelCase. Answer "skip" when you cannot justify a name: a skip costs
nothing, a wrong name misleads readers. A name lands only when another
session independently proposes the same one, so your proposal must be your
own: do not take names from, or show yours to, another model or session.
Write your answer with a file-writing tool, never inline in a shell command
(other sessions can read command lines). If a stand-in type IS a real class
that a game or Zero Hour header declares, answer that class's name.

Write a JSON object mapping each key below to a name or "skip", then run:
  python3 tools/name_lane.py submit <that file> --session {session} --model {model}

{listing}

--- {rel}
{text}
--- evidence (callers, retail strings, tools/name_evidence.py hints)
""" + ("\n".join(evidence) or "  (none)") + "\n"


def cmd_next(lane, args):
    session, model = session_id(args.session), model_id(args.model)
    worker = lane.worker()
    state = lane.state()
    files, voted = queue(lane, worker, model, args.file)
    served, metadata = [], []
    record = lane.path(f"{LANE_DIR}/sessions/{session}.json")
    current = json.loads(record.read_text()) if record.exists() else {"model": model, "worker": worker, "files": {}}
    if current.get("worker") != worker and not args.list_only:
        fail(f"session {session} belongs to another worker; pick a session label of your own")
    for rel in files:
        if rel in current["files"] or not lane.servable(rel):
            continue
        text = lane.text(rel)
        if text is None or len(text) > MAX_CHARS:
            continue
        items = [i for i in lane.owned(rel, text) if key_of(rel, *i[:3]) not in state
                 or state[key_of(rel, *i[:3])]["status"] == "disputed"]
        if len(items) < (1 if voted[rel] or args.file else 3):      # an asked-for file needs one key
            continue
        if args.list_only:
            metadata.append({"file": rel, "chars": len(text), "kinds": dict(collections.Counter(i[0] for i in items))})
        else:
            current["files"][rel] = {"sha": hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest(),
                                     "items": [list(i) for i in items]}
            served.append((rel, text, items))
        if len(served) + len(metadata) >= args.count:
            break
    if args.list_only:
        print(json.dumps(metadata, indent=1))
        return 0
    if not served:
        print(f"name_lane: no file is left for session {session} to name.")
        return 0
    record.parent.mkdir(parents=True, exist_ok=True)
    record.write_text(json.dumps(current, indent=1))
    briefs = lane.path(f"{LANE_DIR}/briefs")
    briefs.mkdir(parents=True, exist_ok=True)
    out = briefs / f"{session}.txt"
    out.write_text("\n\n".join(brief_text(lane, rel, text, items, session, model) for rel, text, items in served),
                   encoding="utf-8", errors="surrogateescape")
    print(f"name_lane: brief for {len(served)} file(s) ({sum(len(i) for _, _, i in served)} keys): {out}")
    if len(served) > 1:
        print("name_lane: answer {\"<file>\": {<key>: <name>|\"skip\"}, ...} for several files")
    return 0


# ---------------------------------------------------------------- submit

def cmd_submit(lane, args, *, lead=2, min_models=1):
    session, model = session_id(args.session), model_id(args.model)
    record = lane.path(f"{LANE_DIR}/sessions/{session}.json")
    if not record.exists():
        fail(f"unknown session {session}: run `next --session {session}` in this checkout first")
    served = json.loads(record.read_text())
    if served.get("model") != model:
        fail(f"session {session} was served to {served.get('model')}, not {model}")
    worker = lane.worker()
    if served.get("worker") != worker:
        fail(f"session {session} was served to another worker; a vote counts only from the worker that "
             "`next` served (BFME_CLAIM_OWNER, BFME_RUN_ID or CLAUDE_CODE_SESSION_ID decide who you are)")
    answers = json.loads(Path(args.answer).read_text(encoding="utf-8"))
    files = served["files"]
    if len(files) == 1 and not any(k in files for k in answers):
        answers = {next(iter(files)): answers}
    unknown = set(answers) - set(files)
    if unknown:
        fail(f"files not served to session {session}: {', '.join(sorted(unknown)[:4])}")
    tally, state, refused = lane.tally(), lane.state(), lane.disputed()
    now = datetime.date.today().isoformat()
    votes, agreed, rejected = [], [], []
    for rel, mapping in answers.items():
        entry = files[rel]
        text = lane.text(rel) or ""
        if hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest() != entry["sha"]:
            rejected.append(f"{rel}: changed since `next` served it; run `next` again")
            continue
        items = [tuple(i) for i in entry["items"]]
        unknown = set(mapping) - {answer_key(k, s, i) for k, s, i, _ in items}
        if unknown:
            fail(f"keys not served for {rel}: {', '.join(sorted(unknown)[:8])}")
        file_words, taken = set(name_metric.WORD.findall(name_metric.strip(text))), set()
        for kind, scope, ident, rva in items:
            answer = str(mapping.get(answer_key(kind, scope, ident), "skip")).strip()
            if answer.lower() == "skip":
                continue
            key = key_of(rel, kind, scope, ident)
            why = lane.problem(kind, ident, answer, file_words)
            if not why and kind in NAMED and canon(answer) in taken:
                why = "the same name as another placeholder in this file"
            if not why and canon(answer) in refused.get(key, ()):
                why = "disputed for this key"
            if not why and worker in {w for h in tally[key].values() for w in h}:
                why = "this worker already voted on it (under some session label)"
            if why:
                rejected.append(f"{answer_key(kind, scope, ident)} -> {answer}: {why}")
                continue
            if kind in NAMED:
                taken.add(canon(answer))
            h = digest(key, answer)
            votes.append({"key": key, "hash": h, "model": model, "session": session, "worker": worker,
                          "date": now})
            tally[key][h][worker] = model
            open_key = key not in state or state[key]["status"] == "disputed"
            gone = refuted(key, refused.get(key, ()))
            rivals = [v for h2, v in tally[key].items() if h2 != h and h2 not in gone]
            if open_key and wins(tally[key][h], rivals, lead=lead, min_models=min_models):
                agents = ";".join(f"{w}@{m}" for w, m in sorted(tally[key][h].items()))
                name = lane_spelling(lane, answer, kind)
                row = {"id": record_id(key, name), "kind": kind, "old": ident, "new": name,
                       "rva": f"0x{rva:08X}" if rva is not None else "", "agents": agents, "key": key,
                       "status": "agreed", "detail": f"two-agent agreement: {agents}"}
                agreed.append(row)
                state[key] = row
    lane.append(VOTES, VOTE_COLUMNS, votes)
    lane.append(AGREED, AGREED_COLUMNS, agreed)
    for rel in answers:
        files.pop(rel, None)
    if files:
        record.write_text(json.dumps(served, indent=1))
    else:
        record.unlink()
    for r in rejected:
        print("  rejected:", r)
    for a in agreed:
        print(f"  AGREED: {a['key']} -> {a['new']} ({a['agents']})")
    print(f"name_lane: {len(votes)} vote(s) recorded as hashes, {len(rejected)} rejected, {len(agreed)} newly agreed"
          + ("; run `python3 tools/name_lane.py apply` to land them" if agreed else ""))
    return 0


def lane_spelling(lane, name, kind):
    """Zero Hour's or WorldBuilder's own spelling of an agreed name when exactly
    one fits: votes match case- and order-blind, so otherwise the last voter's
    casing would land."""
    words = set()
    for row in lane.ctx.dicts(rename.WB_LEADS):
        words |= set(name_metric.WORD.findall(row.get("wb_name", "")))
    zh = lane.path(rename.BFME1) / rename.ZH_TREE
    if zh.exists():
        target = canon(name)
        pattern = "|".join(re.escape(w) for w in re.findall(r"[A-Za-z]{3,}", name)[:1]) or re.escape(name)
        result = subprocess.run(["grep", "-rhoiwE", "--include=*.h", rf"[A-Za-z_]*({pattern})[A-Za-z_0-9]*", str(zh)],
                                capture_output=True, text=True)
        words |= {w for w in result.stdout.split() if canon(w) == target}
    fits = {w for w in words if canon(w) == canon(name) and lane.problem(kind, "", w, set()) is None}
    return fits.pop() if len(fits) == 1 else name


# ---------------------------------------------------------------- apply / dispute

def rename_kwargs(kind, scope, old, new, rva, rel):
    if kind == "function":
        return {"rva": int(scope, 16), "new": new}
    if kind == "class":
        return {"name": old, "new": new}
    if kind == "member":
        return {"cls": scope, "member": old, "new": new}
    if kind in ("param", "local"):
        return {"source": rel, "name": old, "new": new, "function": scope}
    if kind == "global":
        return {"name": old, "new": new}
    raise rename.Refusal(f"unknown lane kind {kind}")


def cmd_apply(lane, args, *, verify=rename.build_verify, checks=rename.ledger_checks):
    state, tally, refused = lane.state(), lane.tally(), lane.disputed()
    todo = collections.defaultdict(list)
    for key, row in state.items():
        if row["status"] == "agreed" or (args.retry_blocked and row["status"] == "blocked"):
            todo[split_key(key)[0]].append(row)
    if not todo:
        print("name_lane: nothing agreed is waiting to land.")
        return 0
    landed = blocked = stale = 0
    for rel, rows in sorted(todo.items()):
        live = {key_of(rel, k, s, i) for k, s, i, _ in lane.owned(rel)} if lane.text(rel) is not None \
            and lane.servable(rel) else set()
        for row in sorted(rows, key=lambda r: LAND_ORDER[r["kind"]]):
            key = row["key"]
            _, kind, scope, ident = split_key(key)
            mine = tally[key].get(digest(key, row["new"]), {})
            gone = refuted(key, refused.get(key, ()))
            rivals = [v for h, v in tally[key].items() if h != digest(key, row["new"]) and h not in gone]
            outcome = dict(row, detail="")
            if key not in live:
                outcome.update(status="stale", agents="", detail="the file changed or the placeholder is gone")
                stale += 1
            elif not wins(mine, rivals, lead=args.lead, min_models=args.min_models):
                print(f"{key}: votes no longer agree under --lead {args.lead} --min-models {args.min_models}; left")
                continue
            else:
                try:
                    rename.run(kind, lane.ctx, claim=args.claim, verify=verify, checks=checks,
                               basis="inferred", evidence=f"agree:{row['id']}",
                               **rename_kwargs(kind, scope, ident, row["new"], row["rva"], rel))
                    outcome.update(status="landed", detail=f"two-agent agreement: {row['agents']}")
                    landed += 1
                except (rename.Refusal, rename.VerifyFailed) as exc:
                    outcome.update(status="blocked", detail=" ".join(str(exc).split())[:300])
                    blocked += 1
                    print(f"{key}: blocked: {outcome['detail']}")
                lane.ctx._cache.clear()
            lane.append(AGREED, AGREED_COLUMNS, [outcome])
    print(f"name_lane: landed {landed}, blocked {blocked}, stale {stale}. Stage the files rename.py listed "
          f"and {AGREED}; the lander commits.")
    return 0


def cmd_dispute(lane, args, *, verify=rename.build_verify, checks=rename.ledger_checks):
    """Put landed names back through rename.revert -- the engine's own exact
    inverse of the recorded inferred rename -- then record the dispute, which
    refuses the spelling for the key from then on."""
    state = lane.state()
    for key in args.keys:
        if key not in state or state[key]["status"] != "landed":
            fail(f"{key}: no landed name to dispute")
    reason = " ".join(args.reason.split())
    if not reason:
        fail("--reason must say what the code shows against the landed name")
    failed = 0
    for key in sorted(args.keys, key=lambda k: -LAND_ORDER[split_key(k)[1]]):
        row = state[key]
        _, kind, scope, ident = split_key(key)
        try:
            rename.revert(lane.ctx, row["id"], reason, claim=args.claim, verify=verify, checks=checks,
                          function=scope if kind in ("param", "local") else None)
        except (rename.Refusal, rename.VerifyFailed) as exc:
            print(f"{key}: could not put {ident} back: {' '.join(str(exc).split())[:300]}")
            failed += 1
            continue
        finally:
            lane.ctx._cache.clear()
        lane.append(AGREED, AGREED_COLUMNS, [dict(row, agents="", status="disputed",
                                                  detail=f"{reason} (was agreed by {row['agents']})")])
        print(f"{key}: {row['new']} put back to {ident}; {row['new']} is refused for it from now on")
    return 1 if failed else 0


# ---------------------------------------------------------------- status

def cmd_status(lane, args):
    votes, state = lane.votes(), lane.state()
    count = collections.Counter(r["status"] for r in state.values())
    sessions = {v.get("worker") for v in votes}
    models = collections.Counter(v["model"] for v in votes)
    print(f"votes: {len(votes):,} from {len(sessions)} worker(s) ({', '.join(f'{m} {n}' for m, n in models.most_common())})")
    print(f"keys voted: {len({v['key'] for v in votes}):,}; agreed: {len(state)} (landed {count['landed']}, "
          f"waiting {count['agreed']}, blocked {count['blocked']}, stale {count['stale']}, "
          f"disputed {count['disputed']})")
    if args.metric:
        names, bad = name_metric.readable()
        print(f"Readable names: {100 * (1 - bad / names):.2f}% ({names - bad:,} of {names:,}); placeholders {bad:,}")
    return 0


def main(argv=None, lane=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    n = sub.add_parser("next", help="serve one file's placeholders as a brief")
    n.add_argument("--session", required=True, help="a label for this brief; who votes is the worker identity, not this")
    n.add_argument("--model", required=True, help="the label you vote under, e.g. seat-a")
    n.add_argument("--count", type=int, default=1, help="serve this many files")
    n.add_argument("--file", help="serve this file instead of the next in the queue")
    n.add_argument("--list-only", action="store_true",
                   help="print the queue's file/size/kind metadata as JSON; no session, no brief")
    s = sub.add_parser("submit", help="record a session's answers as hashed votes")
    s.add_argument("answer")
    s.add_argument("--session", required=True)
    s.add_argument("--model", required=True)
    for p in (s,):
        p.add_argument("--lead", type=int, default=2, help="votes the name must lead every rival by")
        p.add_argument("--min-models", type=int, default=1, help="distinct models among the agreeing workers")
    a = sub.add_parser("apply", help="land agreed names through tools/rename.py")
    a.add_argument("--retry-blocked", action="store_true", help="try blocked names again, e.g. after a fix")
    a.add_argument("--lead", type=int, default=2)
    a.add_argument("--min-models", type=int, default=1)
    a.add_argument("--no-claim", dest="claim", action="store_false", help="do not take tools/claims.py claims")
    d = sub.add_parser("dispute", help="put landed names back and refuse them for their keys")
    d.add_argument("keys", nargs="+", help="as name_agreed.csv spells them (source|kind|scope|placeholder)")
    d.add_argument("--reason", required=True, help="what the code shows against the landed name")
    d.add_argument("--no-claim", dest="claim", action="store_false")
    st = sub.add_parser("status", help="votes and agreement counts")
    st.add_argument("--metric", action="store_true", help="also the tree-wide readable-name metric (slow)")
    args = ap.parse_args(argv)
    lane = lane or Lane()
    if args.cmd == "next":
        return cmd_next(lane, args)
    if args.cmd == "submit":
        return cmd_submit(lane, args, lead=args.lead, min_models=args.min_models)
    if args.cmd == "apply":
        return cmd_apply(lane, args)
    if args.cmd == "dispute":
        return cmd_dispute(lane, args)
    return cmd_status(lane, args)


if __name__ == "__main__":
    sys.exit(main())
