# Structural reconciliation — the manual-RE workflow

For drift rows classed `structural`/`register-swap` the source exists but
compiles to a different shape. Expect 30-60 minutes per function.

**Check the class before you budget that.** Measured 2026-09-29, the two classes
in that sentence are not where the bytes are:

| class | rows | what it actually is |
|---|---|---|
| `structural` | 3,782 | 99.3% are not function starts; best genuine alignment 35% |
| `register-swap` | **0** | no rows exist in this class at all |
| `exact-ambiguous` | 31 | compiles **byte-exactly**, but ties across instantiations at one address |

`exact-ambiguous` is the profitable one and it is not in this doc's title. Its
rows are usually blocked only on unresolved REL32 callees, which
`tools/decode_calls.py` decodes straight out of the target bytes — run it, paste
the pins it prints, re-verify. Worked in one pass: nine candidates, six reached
exact (766 bytes), three did not. That is a far better rate than the structural
loop below, so take the folds first.

## The loop for ONE function

1. `python3 tools/next_work.py --tier structural` draws one candidate from the
   highest-quality band. If it prints a `stash:` line, start from that body — a
   previous attempt already reached the score shown.
2. `python3 tools/explain_mismatch.py '<sym>' --rva <candidate_rva> --size <size> --source <src>`
   Read the classification line first, then the side-by-side disasm.
3. Fix in dependency order; earlier classes mask later ones:
   a. **unresolved REL32 call** — resolve callees FIRST:
      `python3 tools/decode_calls.py <src> --rva <candidate_rva>` prints the
      symbols.csv pins. Add them, re-explain; the real diff often shrinks or
      vanishes.
   b. **misplaced candidate** — target bytes opening like another function's
      tail (`ret`/`int3` within a few bytes) mean the drift vote shifted. Find
      the true start in `reverse/ghidra_functions.csv`; trust a `ret` boundary
      plus export evidence where Ghidra merged functions.

      Do this BEFORE anything else, because it is the usual case rather than
      the exception. Measured 2026-09-29: of the 3,782 `structural` rows in
      `reverse/zh_sweep/drift_report.csv`, only **28** have a `candidate_rva`
      that appears as a function start in the inventory -- 99.3% do not. Mean
      alignment is ~20% either way, so a low score does not tell you which kind
      you have. Confirming the boundary costs one query; not confirming it costs
      the 30-60 minutes this loop warns about. `0x00758338` is the worked
      example: it is mid-instruction inside a function at `0x00758310`, decodes
      as `or al,0x98`, and reached `next_work --tier structural` as a served
      candidate carrying the correct byte count -- which is why the count alone
      is not evidence.

      Then check the inventory ENTRY, not just its presence. Two of those 28
      point at `Unwind@` records -- 11-byte unwind tables that sit inside real
      functions and look like small bodies -- which leaves 26 genuine starts.
      That mattered here: the best-looking row in the whole tier, a 117B
      destructor at 54% alignment, is `0x007690E1,11,Unwind@00b690e1`. Once
      unwind records are excluded the best genuine alignment in the tier is
      35%, on `??0FileSystem@@QAE@XZ` at `0x007398D0`, so nothing in this tier
      is close enough to be worth the loop's budget before the reference lanes
      have been tried.
   c. **field-offset diffs** (`[reg+0xNN]` vs `[reg+0xMM]`, same shape): BFME
      relaid a struct, or retail has a real bug. Change the member access — the
      header only when verified siblings permit — then byte-verify the file.
   d. **literal diffs** (immediates, string addresses): fix the constant.
   e. **shape diffs** (branch layout, register choice, inlining): the hard
      class. Try early-return versus nesting, inverted arms, hoist/sink,
      declaration order, temp versus re-read, split/merge conditions. Do not
      chase x87 operand order or register renames past two attempts; see
      `docs/matching.md`.
4. If exact, `python3 tools/add_match.py '<sym>' <rva> <size> <src>` validates,
   appends, strips the marker and re-verifies; then bank the unit.
5. If it did not land, bank it before reverting:
   `re_log.py record '<sym>' <rva> <size> partial '<diff>' --stash <src>
   --score <0..1>` — both flags required, else `blocked`. Then revert; keep no
   nonmatching body in `Code/`.

An interior-only body is probably inlined; identical already-claimed bytes are
probably ICF-folded. Compiler-only machinery (SEH array-constructor,
`_initterm` stubs) may need the naked-assembly precedent. Each time: verify the
evidence, revert the experiment, take another candidate.

## Escalation beyond drift rows

When this queue thins, `python3 tools/next_work.py --tier ghidra` serves
string-anchored absent functions under the same rules.

## Jump-encoding residuals are a wall, not a puzzle

A body can match byte for byte except for one byte, where retail encodes a
branch short and the build encodes it near, to the same target at the same
distance:

```
retail   eb 20        jmp +0x20      2 bytes
build    e9 xx xx xx  jmp +0x20      3 bytes
```

Measured on `__adjust_heap<int*,int,int,greater<int>>` at `0x5E48C2` (retail 94,
build 95): the body is byte-identical from the function entry through the branch
and again from the byte after it to the `ret`. Five codegen variants were tried
on that exact build — `/O1 /G7`, `/O1 /G6`, `/O1`, `/O1 /EHs` all give 95, `/O2`
gives 114 — so it is not a flag.

This is the same residual the `_M_fill_insert<vector<void*>>` stash records
alongside its frame difference ("homes ... plus jump encodings"), which suggests
it is not specific to one body. Treat it as a layout-pass decision the source
cannot reach: bank the body, record the one-byte residue, and move on. Do not
spend rounds on operand order, driver shape or flag sweeps — all were tried here.

**A related trap that cost a round:** a flag sweep is only valid for the build it
was run on. One run earlier in this work was invalidated by a source change made
afterwards, and answering the question again took one command against reasoning
about whether the old result still applied.

## Attempts: reassess, record, bank (moved from AGENTS.md, 2026-10)

Ghidra boundaries, xrefs and vtables are identity evidence; decompiled C is not
byte-match proof.

After ~120 minutes without meaningful progress, reassess; it is a review point,
not an automatic stopping time. Continue while testing a new evidence-backed
hypothesis; identity, layout, dependency and compiler discoveries count as
progress. Bank and switch when viable hypotheses are exhausted or a concrete
prerequisite blocks further work. Before declaring a function blocked, reassess
independent explanations: control flow, variable lifetime, types/layout, callee
visibility and compiler settings. Exhausting one family of source variations is
insufficient. Do not repeat disproven trials.

Record the verdict with `python3 tools/re_log.py record <symbol> <rva> <size>
<status> <evidence>`, citing the real boundary, `t=<minutes>` and your model.
Walled only by a missing function? Add `blocked-on=0x<rva>`: the queue re-serves
you as untried once it lands. `add_match` records `landed` and lists deferrals
citing the body it landed; stage the log with your row.

**Preserve substantial failed work.** Before retrying any function, read its
attempt-log entries and linked evidence, regardless of how you selected it. For
substantive attempts ending `blocked` or `partial`, commit a concise handoff under
`reverse/attempt_support/` and cite its tracked path in the `re_log.py` evidence.
Include hypotheses tested and ruled out, the exact remaining mismatch or
prerequisite, the best candidate and useful diagnostic diffs, and relevant input
revisions/compiler settings. Preserve better existing banks; retain only artifacts
needed to resume (diagnostic source as patches or `.cpp.txt`). A simple blocker
needs only a concise log entry.

**Close, not exact? Bank the body:** `partial '<what is wrong>' --stash <your
.cpp> --score <0..1>` keeps the candidate servable and starts the next agent from
your body. Both flags are required (a `partial` without a banked body landed 5.1%
against 7.5% for silence). No body, no `partial`: record `blocked`. Prefer
batching smaller banked attempts and blocker notes into a single push.

Banked attempts (`reverse/attempts/<rva>.cpp`) are evidence, never progress:
nothing compiles them, `add_match` deletes one on landing, and `check_csv` flags
leftovers.
