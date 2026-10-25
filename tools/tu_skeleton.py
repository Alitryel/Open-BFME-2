#!/usr/bin/env python3
"""Turn an approved TU from tu_map.csv into the one source file retail built it from.

The skeleton of a TU is every function tu_map.csv approves for it, in retail
address order. Matched bodies are pulled in from the one-function files that
hold them today; everything else is an explicit placeholder comment:

    // tu-skeleton: 0x004A1230 88B ?foo@Bar@@QAEXXZ -- unmatched, no code, never credited
    // tu-skeleton: 0x004A1290 40B ?baz@Bar@@QAEXXZ -- matched in Die/Baz.cpp (not merged yet)

A placeholder is a comment, so it compiles to nothing and no gate or progress
figure can count it. Retail-byte stubs (`__emit`) are deliberately not emitted:
conversion_gate refuses them outside Code/gen_small/ and they would be the one
kind of placeholder a progress figure could mistake for a match.

Merging is verified, never assumed. Each donor file is compiled alone first and
the rows that match there are the baseline. Donors are then accreted in three
deterministic orders (address, row count, text size); a donor is accepted only
if the TU still compiles and NO baseline row is lost, and the best order wins.
Duplicate declarations are emitted once; a type that two donors spell
differently gets one spelling (first, else longest) and the byte check decides
whether that was safe. A donor that also holds rows of another TU is never
split here ("mixed"): it stays a satellite and is reported.

Applying a merge writes the TU file (`// cl:` line chosen from the donors' own
flag sets by the same verification), repoints every ledger row of each absorbed
donor at it, deletes the absorbed donors and stages the result. The commit hook
then byte-verifies it again; this tool never commits.

The map is the one tu_map.py builds from the current inputs: when the committed
tu_map.csv is stale (tu_map.py --check-fresh) it is rebuilt in memory, never
written, so a merge never carries a regenerated map and two merges never
conflict over it.

A donor is refused, not absorbed, when deleting it is not mechanical: it is
untracked, vendored, keyed in a protected path-keyed register (a
Verifier-Change commit re-keys those), #included by another file, or expands
__FILE__ (its path reaches its bytes). These are tools/rename_files.py's
refusals, read from the same tree.

Applying a merge claims `file:` for the TU and every donor plus each moved
row's RVA first (BFME_CLAIM_OWNER; nothing is written when another worker
holds one), and repoints every path-keyed column tools/rename.py repoints
(functions.csv, data_rows.csv, tu_map.csv and body_owners.csv `source`, the
docs/doxygen/sources.cfg INPUT lines).

The queue (--queue) is the consolidation lane's picker: approved TUs ranked by
how many files a merge would remove, skipping TUs another worker holds.

Usage:
  python3 tools/tu_skeleton.py --queue [--under PREFIX] [--limit N] [--json FILE]
  python3 tools/tu_skeleton.py --list PREFIX       approved TUs under PREFIX
  python3 tools/tu_skeleton.py --plan TU           the skeleton, row by row
  python3 tools/tu_skeleton.py --merge TU [--dry-run] [--no-claim]
"""
import argparse
import collections
import contextlib
import csv
import hashlib
import io
import json
import posixpath
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_map  # noqa: E402
import claims  # noqa: E402
import rename  # noqa: E402
import rename_files  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
LAYOUT = tu_map.Layout(ROOT)
LEDGER = LAYOUT.path("functions.csv")
MARK = "// tu-skeleton:"


# ---------------------------------------------------------------- chunking
def chunks(text):
    """Top-level items as (kind, text); comments stay with the item after them.

    kind is 'pp' (a preprocessor line), 'def' (a function body), 'decl'
    (anything ending in ';', class bodies included) or 'tail' (trailing
    comments). Braces inside comments, strings and character literals are
    skipped, which is what the earlier comment-stripping chunker could not do.
    """
    out, n, i, start, depth, code = [], len(text), 0, 0, 0, False
    while i < n:
        c = text[i]
        if text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
            continue
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            i = n if j < 0 else j + 2
            continue
        if c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i, code = j + 1, True
            continue
        if c == "#" and depth == 0 and not code and text[text.rfind("\n", 0, i) + 1:i].strip() == "":
            j = i
            while True:
                k = text.find("\n", j)
                if k < 0:
                    k = n
                    break
                if text[k - 1:k] != "\\" and not text[j:k].rstrip("\r").endswith("\\"):
                    break
                j = k + 1
            lead = text[start:text.rfind("\n", 0, i) + 1]
            if lead.strip():
                out.append(("tail", lead))
            out.append(("pp", text[i:k].rstrip()))
            i = start = min(k + 1, n)
            continue
        if not c.isspace():
            code = True
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                body = strip(text[start:i + 1]).strip()
                head = body.split("{")[0]
                aggregate = re.match(r"^(template\s*<[^>]*>\s*)?(typedef\s+)?(class|struct|enum|union)\b", body) \
                    and not re.search(r"\)\s*(const)?\s*$", head.strip())
                if not aggregate:
                    out.append(("def" if not re.match(r"^(namespace|extern\s+\"C\")", body) else "decl",
                                text[start:i + 1]))
                    start, code = i + 1, False
        elif c == ";" and depth == 0:
            out.append(("decl", text[start:i + 1]))
            start, code = i + 1, False
        i += 1
    if text[start:].strip():
        out.append(("tail" if not strip(text[start:]).strip() else "decl", text[start:]))
    return out


def strip(t):
    t = re.sub(r"/\*.*?\*/", " ", t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


def norm(t):
    return re.sub(r"\s+", " ", strip(t)).strip()


def key_of(kind, text):
    s = norm(text)
    m = re.match(r"^(?:template\s*<[^>]*>\s*)?(class|struct|enum|union)\s+(?:__declspec\([^)]*\)\s*)?"
                 r"([A-Za-z_]\w*)\s*(?::[^{]*)?\{", s)
    if m:
        return ("type", m.group(2))
    m = re.match(r"^typedef\b.*?\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;$", s)
    if m:
        return ("typedef", m.group(1))
    if kind == "def":
        return ("func", s.split("{")[0].strip())
    return ("decl", s)


ACCESS = re.compile(r"^\s*(public|protected|private)\s*:(?!:)")


def members(text):
    """(head, [(access, member text)], tail) of one class body; comments stripped."""
    text = strip(text)
    i, j = text.index("{"), text.rindex("}")
    head, body, tail = text[:i + 1], text[i + 1:j], text[j:]
    acc = "public" if re.match(r"^\s*(template\s*<[^>]*>\s*)?(struct|union)\b", head) else "private"
    out, buf, depth, par = [], "", 0, 0
    for ch in body:
        buf += ch
        m = ACCESS.match(buf)
        if m and depth == 0 and par == 0:
            acc, buf = m.group(1), buf[m.end():]
            continue
        if ch == "(":
            par += 1
        elif ch == ")":
            par -= 1
        elif ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0 and par == 0 and "(" in buf.split("{")[0] \
                    and not re.match(r"^\s*(enum|struct|class|union)\b", buf):
                out.append((acc, buf.strip()))
                buf = ""
        elif ch == ";" and depth == 0 and par == 0:
            out.append((acc, buf.strip()))
            buf = ""
    return head, [(a, m) for a, m in out if m and m != ";"], tail


def member_key(m):
    """(key, 'safe'|'layout'): safe members cannot change size, offsets or vtable."""
    s = re.sub(r"\s+", " ", re.sub(r"\{.*\}$", "", m, flags=re.S)).strip().rstrip(";")
    if re.match(r"^(enum|struct|class|union|typedef)\b", s):
        names = re.findall(r"[A-Za-z_]\w*", s)
        return ("type", names[-1] if s.startswith("typedef") else names[1] if len(names) > 1 else s), "safe"
    f = re.search(r"(~?[A-Za-z_]\w*|operator\s*\S+)\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*(const)?", s)
    if f and not re.search(r"\(\s*\*", s[:f.start() + 3]):
        return ("fn", f.group(1), bool(f.group(3))), ("layout" if re.search(r"\bvirtual\b", s) else "safe")
    names = re.findall(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*$", s)
    return ("data", names[0] if names else s), ("safe" if s.startswith("static ") else "layout")


def union_view(base, others):
    """`base` plus the layout-safe members only the others declare (access kept:
    MSVC mangles it). Virtual functions and data members are never added."""
    try:
        head, mem, tail = members(base)
    except ValueError:
        return base
    have = {member_key(m)[0] for _, m in mem}
    add = []
    for v in others:
        try:
            _, vm, _ = members(v)
        except ValueError:
            continue
        for a, m in vm:
            k, kind = member_key(m)
            if kind == "safe" and k not in have:
                have.add(k)
                add.append((a, m))
    if not add:
        return base
    extra = "".join(f"\n{a}:\n\t{m}{'' if m.endswith(('}', ';')) else ';'}" for a, m in add)
    return head + "".join(f"\n{a}:\n\t{m};" if not m.endswith(("}", ";")) else f"\n{a}:\n\t{m}"
                          for a, m in mem) + extra + "\n" + tail


# ---------------------------------------------------------------- inputs
_CACHE = {}


def ledger_rows():
    if "ledger" not in _CACHE:
        _CACHE["ledger"] = list(csv.DictReader(io.StringIO(
            LEDGER.read_text(encoding="utf-8", errors="replace"), newline="")))
    return _CACHE["ledger"]


def map_rows():
    """tu_map rows from the current inputs: the committed map when it is fresh,
    else a rebuild in memory (tu_map.build is a pure function of the inputs)."""
    if "map" not in _CACHE:
        stale = tu_map.check_fresh(LAYOUT)
        rows = tu_map.build(LAYOUT) if stale else tu_map.read_csv(LAYOUT.out)
        _CACHE["map"] = [{k: str(v) for k, v in r.items()} for r in rows]
        _CACHE["stale"] = stale
    return _CACHE["map"]


def tree():
    """rename_files' refusal reader (tracked files, protected keys, includes)."""
    if "tree" not in _CACHE:
        _CACHE["tree"] = rename_files.Tree(rename.Context(ROOT, object_scan=False))
    return _CACHE["tree"]


# rename_files.Tree reasons that do not apply to absorbing a donor: its name is
# not kept either way, and its rows keep theirs.
NOT_REFUSALS = ("an approved retail TU path", "recorded canonical")


def refusal(f, rows):
    why = tree().refusal(f, rows)
    return None if why is None or why.startswith(NOT_REFUSALS) else why


def skeleton(tu):
    """Approved rows of `tu` in retail order, each with its ledger row (or None)."""
    m = map_rows()
    want = [r for r in m if r["tu"].lower() == tu.lower() and r["confidence"] == "approved"
            and r["kind"].startswith("code")]
    led = {}
    for r in ledger_rows():
        if "gen-alias" not in (r["notes"] or "") and r["target_rva"].startswith("0x"):
            led.setdefault(int(r["target_rva"], 16), r)
    return [(r, led.get(int(r["rva"], 16))) for r in sorted(want, key=lambda r: int(r["rva"], 16))]


def donors(tu, sk):
    """(donor file -> its rows, mixed file -> foreign row count, refused file -> why).

    A candidate is the file of an approved row, or the TU path itself. It may be
    absorbed only when every matched row it owns is assigned to this TU (any
    confidence); anything else would move a row the map does not put here. A
    donor other than the TU path is refused when deleting it is not mechanical
    (see refusal()).
    """
    rows = ledger_rows()
    if "assigned" not in _CACHE:
        _CACHE["assigned"] = {int(r["rva"], 16): r["tu"].lower() for r in map_rows()
                              if r["kind"].startswith("code") and r["tu"]}
    assigned = _CACHE["assigned"]
    if "by_file" not in _CACHE:
        _CACHE["by_file"] = collections.defaultdict(list)
        for r in rows:
            _CACHE["by_file"][r["source"]].append(r)
    by_file = _CACHE["by_file"]
    # Unconverted rows are approved too now; a generated or dump file (gen_uw.py owns
    # gen_small end to end) is a placeholder for the address, never a donor to absorb.
    cands = {led["source"] for t, led in sk
             if led and led["status"] == "matched" and led["source"].endswith(".cpp")
             and not re.search(r"/(gen_small|gen_asm|masm_dumps)/", led["source"])}
    if by_file.get(tu):
        cands.add(tu)
    out, mixed, refused = {}, {}, {}
    for f in sorted(cands):
        own = [r for r in by_file[f] if r["status"] == "matched" and "gen-alias" not in (r["notes"] or "")]
        foreign = [r for r in own if assigned.get(int(r["target_rva"], 16)) != tu.lower()]
        if foreign:
            mixed[f] = len(foreign)
        elif own:
            why = refusal(f, by_file[f]) if f != tu else None
            if why:
                refused[f] = why
            else:
                out[f] = own
    return out, mixed, refused


def flags_of(text):
    for line in text.splitlines():
        if line.startswith("// cl:"):
            return line[len("// cl:"):].split()
    return []


# ---------------------------------------------------------------- compose
# Redefinitions cl reports when two donors (or a donor and a header another
# donor includes) both declare one type: the later, donor-local copy is dropped
# and the byte check decides whether the surviving spelling was safe.
REDEFINED = re.compile(r"error C2011: '([A-Za-z_]\w*)' : '(?:struct|class|enum|union)' type redefinition"
                       r"|error C2371: '([A-Za-z_]\w*)' : redefinition; different basic types"
                       r"|error C2365: '([A-Za-z_]\w*)' : redefinition; previous definition was")


def redefined(errors):
    return {next(g for g in m.groups() if g) for e in errors for m in [REDEFINED.search(e)] if m}


def compose(tu, sk, files, texts, flags, strategy, drop=frozenset(), drop_all=frozenset()):
    """Declarations first (donor order, one spelling each), then bodies in retail order.

    `files` is in donor order with the seed first. A type two donors spell
    differently is emitted once, from the donor whose spelling is chosen and at
    that donor's own position, so whatever it depends on is already declared.
    """
    parsed = {f: chunks("\n".join(l for l in texts[f].lstrip("\ufeff").splitlines()
                                  if not l.startswith("// cl:") and l.strip() != "// stlport") + "\n")
              for f in files}
    variants = collections.defaultdict(list)
    for f in files:
        for kind, c in parsed[f]:
            if kind == "decl":
                k = key_of(kind, c)
                if k[0] in ("type", "typedef") and norm(c) not in [norm(v) for v, _ in variants[k]]:
                    variants[k].append((c, f))
    chosen = {}
    for k, v in variants.items():
        if len(v) > 1:
            pick = v[0] if strategy.endswith("first") else max(v, key=lambda x: len(norm(x[0])))
            if strategy.startswith("union") and k[0] == "type":
                # emitted where the LAST donor declares it: members added from
                # other donors may name types those donors declare first
                pick = (union_view(pick[0], [x[0] for x in v if x is not pick]), v[-1][1])
            chosen[k] = pick
    pps, decls, seen = [], [], set()
    for f in files:
        for kind, c in parsed[f]:
            if kind == "pp":
                if c.strip() not in pps:
                    pps.append(c.strip())
            elif kind == "decl":
                k = key_of(kind, c)
                if k[0] in ("type", "typedef") and (k[1] in drop_all or (k[1] in drop and f != files[0])):
                    continue   # cl saw it defined earlier: the seed's copy, else a header (includes come first)
                if k[0] in ("type", "typedef") and k[1] in drop and k not in seen:
                    seen.add(k)    # the seed's own spelling, whichever spelling the strategy chose
                    decls.append(c.strip("\n"))
                    continue
                if k in seen or (k in chosen and chosen[k][1] != f):
                    continue
                seen.add(k)
                decls.append((chosen[k][0] if k in chosen else c).strip("\n"))
    body, done, bodies = [], set(), set()
    for t, led in sk:
        f = led["source"] if led else None
        if f in files:
            if f in done:
                continue
            done.add(f)
            body.append(f"// ---- from {f}")
            for kind, c in parsed[f]:
                if kind == "def" and norm(c) not in bodies:
                    bodies.add(norm(c))
                    body.append(c.strip("\n"))
                elif kind == "tail":
                    body.append(c.strip("\n"))
            continue
        name = (led or {}).get("name") or "(unledgered)"
        why = (f"matched in {f} (not merged yet)" if led and led["status"] == "matched"
               else "unmatched, no code, never credited")
        body.append(f"{MARK} {t['rva']} {t['size']}B {name} -- {why}")
    for f in files:   # a donor none of whose rows is approved here (cannot happen today)
        if f not in done:
            body.extend(c.strip("\n") for kind, c in parsed[f] if kind == "def")
    head = [f"// cl: {' '.join(flags)}"] if flags else []
    if any("// stlport" in texts[f] for f in files):
        head.append("// stlport")
    head.append(f"// TU {tu}: generated by tools/tu_skeleton.py from tu_map.csv (approved rows, retail order)")
    return "\n".join(head + pps) + "\n\n" + "\n\n".join(decls + body) + "\n"


# ---------------------------------------------------------------- verify
class Verifier:
    """Compiles candidate TU texts beside the TU and judges rows as build.sh does.

    The candidate is a temporary file, which tools/flag_defaults.py knows no
    region for, so it would compile with its raw `// cl:` codegen flags while the
    real file gets its region's. The verifier therefore writes the flags the
    build will use: the region holding most bytes of the rows being judged
    (flag_defaults' own rule for a TU), or the TU's own flags when the TU path
    is in flag_overrides.csv, and compiles with region defaults off."""

    def __init__(self, tu):
        import build as B
        self.B = B
        self.fd = B.flag_defaults
        self.tu_rel = tu
        self.sm = B.load_symbol_map()
        self.tu = ROOT / tu
        self.tmp = ROOT / "build" / "tu_skeleton"   # build.py wants objects inside the tree
        self.tmp.mkdir(parents=True, exist_ok=True)
        self.cache = {}
        self.errors = []
        self.all_errors = []

    def effective(self, text, rows):
        """`text` with the `// cl:` line the build would use for these rows."""
        fd = self.fd
        if self.tu_rel in fd.overrides():
            return text
        weights = {}
        for r in rows:
            try:
                region = fd.region_at(int(r["target_rva"], 16))
                size = int(r["target_size"])
            except (ValueError, KeyError):
                continue
            if region is None or region.get("vote") != "1":
                continue
            entry = weights.setdefault(fd._flag_set(region), [0, region])
            entry[0] += size
        if not weights:
            return text
        region = max(sorted(weights.items()), key=lambda item: item[1][0])[1][1]
        lines = text.split("\n")
        at = next((i for i, l in enumerate(lines) if l.startswith("// cl:")), None)
        own = lines[at][len("// cl:"):].split() if at is not None else []
        keep = [t for t in own if not fd.MANAGED.match(t.replace("/", "-", 1) if t.startswith("/") else t)]
        line = "// cl: " + " ".join(["/" + t[1:] for t in fd.region_tokens(region)] + keep)
        if at is None:
            lines.insert(0, line)
        else:
            lines[at] = line
        return "\n".join(lines)

    def matched(self, text, rows):
        text = self.effective(text, rows)
        key = hashlib.sha1(text.encode()).hexdigest()[:16]
        if key not in self.cache:
            src = self.tu.parent / f".{self.tu.stem}.{key}.tu_skeleton.cpp"
            obj = self.tmp / f"{key}.obj"
            src.write_text(text, encoding="utf-8", newline="")
            try:
                with contextlib.redirect_stdout(io.StringIO()), self.fd.forced_mode("current"):
                    ok, msg, _ = self.B.try_compile_source(src, obj)
            finally:
                src.unlink()
            self.cache[key] = obj if ok else None
            if not ok:
                self.all_errors = [l.strip() for l in (msg or "").splitlines() if " error " in l]
                self.errors = self.all_errors[:3]
        obj, out = self.cache[key], set()
        if obj is None:
            return None
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
            for r in rows:
                try:
                    res = self.B.compile_function(r, self.sm, obj)
                    if res["bytes"] == res["target"]:
                        out.add(r["target_rva"])
                except BaseException:   # build.py reports misses by SystemExit
                    pass
        return out


def merge(tu, dry_run=False, log=print, claim=True):
    sk = skeleton(tu)
    don, mixed, refused = donors(tu, sk)
    report = {"tu": tu, "approved": len(sk), "mixed": mixed, "refused": refused, "accepted": [], "rejected": {}}
    if tu in mixed or ((ROOT / tu).exists() and tu not in don):
        report["blocked"] = "TU path exists and holds rows of another TU (split it first)"
        return report
    if len(don) < 2 and not (len(don) == 1 and tu not in don):
        report["blocked"] = "fewer than two donors"
        return report
    if claim and not dry_run:
        held = claim_scope(tu, don)
        if held:
            report["blocked"] = "held by another worker: " + ", ".join(held[:5])
            return report
    v = Verifier(tu)
    texts = {f: (ROOT / f).read_text(encoding="utf-8-sig", errors="replace") for f in don}
    base = {}
    for f in don:
        got = v.matched(texts[f], don[f])
        base[f] = got or set()
    good = [f for f in don if base[f]]
    if tu in don and tu not in good:
        report["rejected"] = {f: "no baseline match" for f in don if f not in good}
        report["blocked"] = "the TU file's own rows do not match under the verifier"
        return report
    weight = collections.Counter()
    cands = {}
    for f in good:
        fl = flags_of(texts[f])
        # region-managed codegen tokens are inert (Verifier.effective writes the
        # region's), so flag sets that differ only in them are one candidate
        k = tuple(x for x in fl if not x.lower().startswith(("/i", "-i"))
                  and not v.fd.MANAGED.match(x.replace("/", "-", 1) if x.startswith("/") else x))
        weight[k] += len(base[f])
        cands.setdefault(k, None)
    incs = []
    for f in good:
        for x in flags_of(texts[f]):
            if x.lower().startswith(("/i", "-i")) and x not in incs:
                incs.append(x)
    flag_sets = [list(k) + incs for k, _ in weight.most_common()]

    def attempt(files, flags):
        best = None
        need = set().union(*(base[f] for f in files))
        rows = [r for f in files for r in don[f]]
        for st in ("union-first", "union-longest", "first", "longest"):
            drop, drop_all = set(), set()
            for _ in range(16):
                text = compose(tu, sk, files, texts, flags, st, frozenset(drop), frozenset(drop_all))
                got = v.matched(text, rows)
                again = redefined(v.all_errors) if got is None else set()
                if not again - drop_all:
                    break
                drop_all |= again & drop   # still redefined with only the seed's copy: a header owns it
                drop |= again
            if got is not None and need <= got:
                return text
            best = best or ("compile" if got is None else "bytes")
        return best

    def greedy(order, flags):
        acc, rej = [], {}
        for f in order:
            res = attempt(acc + [f], flags)
            if res in ("compile", "bytes"):
                rej[f] = res + ("" if res == "bytes" else ": " + " | ".join(v.errors)[:300])
            else:
                acc.append(f)
        return acc, rej

    first = {f: min(int(r["target_rva"], 16) for r in don[f]) for f in good}
    orders = [sorted(good, key=first.get), sorted(good, key=lambda f: (-len(base[f]), first[f])),
              sorted(good, key=lambda f: (-len(texts[f]), first[f]))]
    if tu in good:   # an existing file at the TU path is always the seed
        orders = [[tu] + [f for f in o if f != tu] for o in orders]
    best = None
    for flags in flag_sets[:3]:
        for o in orders:
            acc, rej = greedy(o, flags)
            score = sum(len(base[f]) for f in acc)
            if (tu in good and tu not in acc):
                continue
            if best is None or score > best[0]:
                best = (score, acc, rej, flags)
    report["rejected"].update({f: "no baseline match" for f in don if f not in good})
    if not best or len(best[1]) < 2 and not (len(best[1]) == 1 and best[1][0] != tu):
        report["rejected"].update(best[2] if best else {})
        report["blocked"] = "no verified merge of two or more donors"
        return report
    score, acc, rej, flags = best
    text = attempt(acc, flags)
    report.update(accepted=acc, flags=flags, rows=score)
    report["rejected"].update(rej)
    if dry_run:
        report["text"] = text
        return report
    moved = apply(tu, acc, text)
    report["repointed"] = moved
    report["stage"] = "staged: " + " ".join([tu] + sorted(moved) + [f for f in acc if f != tu])
    report["subject"] = (f"Merge {len(acc)} files into {posixpath.basename(tu)} "
                         f"({score} rows, tu_map approved TU, retail order)")
    return report


# ---------------------------------------------------------------- apply
def claim_keys(tu, don):
    keys = [f"file:{tu}"] + [f"file:{f}" for f in sorted(don) if f != tu]
    return keys + sorted({r["target_rva"] for rows in don.values() for r in rows})


def claim_scope(tu, don, root=ROOT):
    """Claim the TU, its donors and their rows; [] or the keys another worker holds."""
    keys = claim_keys(tu, don)
    try:
        res = claims.claim(keys, note=f"tu_skeleton merge {tu}", root=root)
    except claims.ClaimsUnavailable as e:
        return [f"(claims unavailable: {e})"]
    if res.refused:
        names = {claims.key_of(k): k for k in keys}
        return [str(names.get(k, k)) for k in res.refused]
    return []


def repoint_sources_cfg(raw, gone, tu):
    """INPUT lines of absorbed donors become one line for the TU."""
    lines = raw.decode("utf-8").splitlines(keepends=True)
    entry = re.compile(r"INPUT\s*\+=\s*(\S+)\s*")
    have = any((m := entry.fullmatch(l)) and m.group(1) == tu for l in lines)
    out, count = [], 0
    for line in lines:
        m = entry.fullmatch(line)
        if m and m.group(1) in gone:
            count += 1
            if not have:
                out.append(line.replace(m.group(1), tu))
                have = True
            continue
        out.append(line)
    return "".join(out).encode("utf-8"), count


def repoint_all(root, gone, tu):
    """Point every path-keyed column (rename.PATH_COLUMNS) and the doxygen
    INPUT list from the absorbed donors at the TU. Returns {file: records}."""
    moved = {}
    for rel, column in rename.PATH_COLUMNS:
        path = Path(root) / rel
        if not path.exists():
            continue
        raw = path.read_bytes()
        total = 0
        for f in sorted(gone):
            raw, n = rename.repoint_column(raw, rel, column, f, tu)
            total += n
        if total:
            path.write_bytes(raw)
            moved[rel] = total
    cfg = Path(root) / rename.SOURCES_CFG
    if cfg.exists():
        raw, n = repoint_sources_cfg(cfg.read_bytes(), set(gone), tu)
        if n:
            cfg.write_bytes(raw)
            moved[rename.SOURCES_CFG] = n
    return moved


def apply(tu, accepted, text, root=ROOT):
    gone = [f for f in accepted if f != tu]
    moved = repoint_all(root, gone, tu)
    (Path(root) / tu).write_text(text, encoding="utf-8", newline="\n")
    if gone:
        subprocess.run(["git", "rm", "-q", "--", *gone], cwd=root, check=True)
    subprocess.run(["git", "add", "--", tu, *moved], cwd=root, check=True)
    _CACHE.clear()
    return moved


def plan(tu):
    sk = skeleton(tu)
    don, mixed, refused = donors(tu, sk)
    for t, led in sk:
        state = ("pull " + led["source"] if led and led["source"] in don else
                 "mixed " + led["source"] if led and led["source"] in mixed else
                 "refused " + led["source"] + " (" + refused[led["source"]] + ")"
                 if led and led["source"] in refused else
                 "placeholder (" + (led["status"] if led else "unledgered") + ")")
        print(f"{t['rva']} {int(t['size']):6d} {t['by']} {(led or {}).get('name', '')[:60]:60s} {state}")
    print(f"{len(sk)} approved rows, {len(don)} donor files, {len(mixed)} mixed files, "
          f"{len(refused)} refused files")


def queue(under="", limit=None, root=ROOT):
    """Approved TUs a merge can shrink, most files removed first.

    `removes` is an upper bound: the merge verifies every donor and keeps only
    those that compile together without losing a matched row."""
    by_tu = collections.defaultdict(list)
    for r in map_rows():
        if r["confidence"] == "approved" and r["kind"].startswith("code") and r["tu"]:
            by_tu[r["tu"]].append(r)
    try:
        held = set().union(*(set(rec) for rec in claims._blocking_records(root)))
    except Exception:   # no origin: nothing is known to be held
        held = set()
    out = []
    for tu in sorted(by_tu):
        if under and not tu.startswith(under):
            continue
        sk = skeleton(tu)
        don, mixed, refused = donors(tu, sk)
        removes = len(don) - 1
        if removes < 1 or tu in mixed or ((Path(root) / tu).exists() and tu not in don):
            continue   # nothing to remove, or the TU path itself must be split first
        keys = {claims.key_of(k) for k in claim_keys(tu, don)}
        out.append({"tu": tu, "removes": removes, "rows": sum(len(v) for v in don.values()),
                    "mixed": len(mixed), "refused": len(refused), "held": bool(keys & held)})
    out.sort(key=lambda d: (d["held"], -d["removes"], -d["rows"], d["tu"]))
    return out[:limit] if limit else out


def list_tus(prefix):
    c = collections.defaultdict(set)
    for r in map_rows():
        if r["confidence"] == "approved" and r["tu"].startswith(prefix) and r["kind"].startswith("code"):
            c[r["tu"]].add(r["source"])
    for tu, files in sorted(c.items()):
        print(f"{len(files - {''}):3d} files  {tu}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--queue", action="store_true")
    g.add_argument("--list", metavar="PREFIX")
    g.add_argument("--plan", metavar="TU")
    g.add_argument("--merge", metavar="TU")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--no-claim", action="store_true", help="merge without claiming (fixtures, private trees)")
    ap.add_argument("--under", default="")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--json")
    a = ap.parse_args(argv)
    if a.queue:
        q = queue(a.under, a.limit)
        if a.json:
            Path(a.json).write_text(json.dumps(q, indent=2) + "\n")
        if _CACHE.get("stale"):
            print("(tu_map.csv is stale; the queue uses a map rebuilt in memory)")
        for d in q:
            print(f"{d['removes']:4d} files {d['rows']:5d} rows  mixed {d['mixed']:3d}  refused {d['refused']:3d}"
                  f"{'  HELD' if d['held'] else ''}  {d['tu']}")
        return 0
    if a.list is not None:
        list_tus(a.list)
    elif a.plan:
        plan(a.plan)
    else:
        rep = merge(a.merge, a.dry_run, claim=not a.no_claim)
        text = rep.pop("text", None)
        for k, val in rep.items():
            print(f"{k}: {val}")
        if text and a.dry_run:
            print(text)
        return 0 if rep.get("accepted") else 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
