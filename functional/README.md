# `functional` branch — 100% behaviour, not 100% bytes

master measures **byte exactness**: a function counts when its C++ rebuilds retail's exact
bytes. This branch measures **behaviour**: a function counts when it does exactly what
retail does, proven by differential execution, even if MSVC lays it out differently
(register allocation, stack-slot order, instruction scheduling, length). The goal is a
complete `game.dat` that links, boots and plays like retail, with every function either
byte-exact (from master) or behaviour-verified (here).

master stays authoritative and byte-exact. Nothing here is merged into master; master is
merged into here regularly. Anything that is byte-neutral and passes master's gates (link
repairs, ledger fixes, real names) goes to **master**, not here.

## The counter (this branch only)

    python3 functional/tools/fn_progress.py          # needs the census index: tools/link_check.py --fetch-index

| Figure | Meaning |
|---|---|
| BEHAVIOUR-VERIFIED | byte-exact rows ∪ `functional/ledger.csv` rows with a passing verdict, over real code (.text minus 0xCC, the same 7,978,500-byte denominator as `tools/progress.py`) |
| BYTE-EXACT | master's ledger alone |
| FUNCTIONAL-ONLY | verified here, not byte-exact |
| CLAIMED | ledger rows without a passing verdict — shown, never counted |
| FUNCTIONAL LINKING | matched code in units that link once byte-only link blockers are waived (a kept COMDAT copy differing from retail's bytes, S, or from the first copy, L, still links and behaves the same); only unresolved names (U), duplicate definitions (D) and hard-coded addresses (A) block a unit here |

Baseline at creation (2026-10-18, master 1d0a25b6db+): BEHAVIOUR-VERIFIED 93.87%
(7,489,332 B, all byte-exact), remaining 489,168 B; FUNCTIONAL LINKING 79.17% of matched
code vs 72.95% under master's rules (+459 KB from the rule alone).

First F1 survey (same day, `fn_verify.py --all-banks --record` over 359 unmatched banks, 256
completed): 127 `regalloc-only` + 1 `none` (149.7 KB), plus SegLineRenderer `tested` →
**BEHAVIOUR-VERIFIED 95.94%** (7,654,579 B; 165,247 B functional-only, 129 rows), remaining
323,921 B. Not passing: 46 `binding` (45 KB), 20 `logic` (43 KB), 62 `inconclusive` (58 KB:
emulator limit cuts, symbol missing from the object, compile errors, no symbol in the log).
**These passes are provisional until F0 lands**: three synthetic input vectors and stubbed
callees are weak evidence for large functions; F0's fuzzing and coverage receipts will
re-verify every row, and rows that then fail drop out of the count.

## What counts as verified

`functional/ledger.csv`: `name,target_rva,target_size,source,verdict,evidence,date`.
A row passes with verdict:

- `none` / `regalloc-only` from `functional/tools/fn_verify.py`, which compiles the body and
  runs it beside retail's bytes in `tools/diffexec.py`'s x86 emulator (Unicorn) on identical
  inputs with callees stubbed: equal return values, memory writes, call sequence and call
  arguments on every input vector. Bodies may differ in length (compared over the longer
  extent, the shorter padded with int3).
- `tested`: a dedicated differential harness with receipts under `functional/receipts/`
  (example: SegLineRenderer 0x191C10, contributor package, 83/83 full-renderer scenarios,
  66/66 x87 boundary cases).

`logic`, `binding`, `build_env`, `inconclusive` never pass. One receipt per row in
`functional/receipts/<rva>.json`.

## Workstreams (in priority order)

**F0 — verifier hardening** (before trusting large numbers)
1. Inlining-aware call comparison: run a callee that is a matched ledger row *for real*
   (its retail bytes) instead of stubbing it, so "retail inlined X, we call X" stops reading
   as `binding` (first seen on SegLine: `WWMath::Inv_Sqrt`).
2. More input vectors: seeded fuzzing of `this`/argument objects and field values beyond
   diffexec's three fixed vectors; x87 edge values (NaN, denormals, ±0, large) for float code.
3. A coverage receipt per row (basic blocks of retail reached by the vectors) so a pass on
   2% of the paths is visibly weak.
4. Spot-audit: re-run `fn_verify` on a sample of byte-exact master rows (must all pass) and on
   deliberately broken bodies (must all fail) — `tools/tests` style regression cases.

**F1 — promote banked attempts** (363 unmatched functions with a bank, 463 KB)
`fn_verify.py --all-banks --record` verifies every `reverse/attempts/<rva>.cpp` whose RVA has
no matched row. Passing rows count at once. `logic`/`binding` rows go to agents: today's
closers found most farm "near misses" are semantically wrong (wrong argument, inverted
condition, swapped compare operands); fixing the semantics is enough on this branch — no
register-allocation work.

**F2 — farm bests** (`wave10/closer/dossiers/<rva>/best.cpp`, 350 functions)
Same as F1 for the farm's best non-exact bodies where they beat the bank.

**F3 — missing functions** (unclaimed functions with no usable bank; 595 callees that
held units out of linking as U-match; 180 small unbanked functions, 5.4 KB)
Write clean C++ from the WorldBuilder debug build (`tools/wb_show.py --gd`, same source
unoptimised), Zero Hour / BFME1 donors and the retail disassembly; verify; record. Largest
link payoff first: AptLinker::Load (0x6D1F80), AptActionInterpreter::_createObject
(0x706A40) and rva007092F0 (one unit holds 35 KB), Pathfinder::moveAllies (0x2F3C09),
consume (0x3909FA), BuildAssistant::getPortTransform (0x392802), rva005AF12F.

**F4 — functional linking to 100%**
1. FUNCTIONAL LINKING counts S/L as fine already.
2. U blockers: U-twin / U-data are byte-neutral → fix on **master** (the DeepSeek and Opus link
   seats are doing this). U-match → F3. U-unknown (2,742 names) → classify (CRT/lib, data,
   template) with `wave10/tools/link_triage.py`.
3. D (280 units, 350 KB): keep one definition (byte-neutral → master when the gates allow,
   else here).
4. A functional census mode: `link_census` with the S/L waiver as a rule, and functional
   bodies from `functional/src/` substituted for missing rows, producing a real link plan.

**F5 — data** (2.5 MB of .rdata/.data, none byte-verified yet)
Use `reverse/data_rows.csv` / `tools/data_check.py`; behaviour needs initialised data equal
in value (vtables, tables, strings, float constants), not in layout where nothing addresses it.

**F6 — the executable**
Full link of a functional `game.dat` (link.exe under Wine, master's link_cycle tooling) and
`tools/boot_smoke.py` — a verification runner: **ask the maintainer before running it**. Then
scripted in-game scenarios (skirmish start, save/load, a campaign map) compared with retail.

## How work happens here

- Workspace: a titan checkout on branch `functional` (`ws/fn`). Bodies that are not byte-exact
  live under `functional/src/` (never under `Code/`, which master's gates own).
- Every row lands with its receipt; `fn_progress.py` is re-run and its headline goes in the
  commit message.
- Merge master in regularly: `git merge origin/master` (this branch only adds `functional/`,
  so merges are conflict-free).
- Agents follow AGENTS.md; on this branch the byte gate is replaced by `fn_verify.py`, never
  by nothing.

## Where 100% stands

| Gap | Size | Path |
|---|---|---|
| Unmatched code with a bank | ~463 KB | F1 (mechanical once F0 lands) + agents for semantic fixes |
| Unmatched code without a bank | ~26 KB | F3 |
| Units not linking (functional rules) | ~1.54 MB of matched code | F4 (mostly U: names and missing functions) |
| Data | 2.5 MB unverified | F5 |
| Whole program | — | F6 |
