# AIWall 0x004EACF5: coordinate carriers and observed register costs

2026-10-20 Arizona, gpt-6. No new match or stronger bank. The complete helper
is 197 bytes at `[0x004EACF5, 0x004EADBA)`; its 227-byte caller remains dependent
on it. The joint canonical bank `reverse/attempts/0x004eadba.cpp` is unchanged.
Read `aiwall-distsq-4eacf5-r54-20261020.md` and
`0x004eadba_20261020_w1.md` before this continuation.

## Result and remaining mismatch

Official `align_diff` reproduces 197 bytes, 52 instructions, zero structural
regions and four differing instructions, also in the complete current AIWall
translation unit. Those four instructions encode 15 differing bytes: the bank
issues the point's y subtraction before x; retail issues x before y. Every
subsequent instruction matches. This is four instructions, not four bytes.

The coordinate form fixes that order but changes the direction/length XMM
assignments. It is not a better bank. No Code, ledger, pin, compiler profile,
shared header or verifier was changed.

## New observation: the unfinished cost trace is now reproducible

`trace_color.py.txt` observes the pinned 32-bit RTM backend using the Windows
debugger API. It checks c2.dll SHA256 before installing temporary breakpoints
in that compiler process. Marker offsets are recorded in its `offsets` map;
they are observation points, not assertions identifying every internal routine.
Sequence 4 is this helper for the archived input generators. Costs are the
candidate record's DWORD at +0x0C; physical register records are read after
allocation. Candidate-to-value associations below follow the source forms and
emitted register uses.

| Ordinary source form | dx/dy candidate costs | length-y candidate cost |
| --- | --- | --- |
| scalar bank | 35 / 35 | 44 |
| point difference as Coord2D | 55 / 55 | 44 |
| point and direction as Coord2D | 70 / 70 | 44 |

Thus the carrier changes more than candidate numbering. In the two coordinate
forms the direction candidates obtain xmm2/xmm3 and the length-y candidate
obtains xmm4; retail needs direction xmm3/xmm4 and length-y xmm2. This replaces
the previous uncompleted trace with observed records. It does not establish a
source transformation that produces retail.

Observation-only debugger controls preserved **every emitted function's bytes
and relocations** against ordinary compiles for all three forms. Two explicitly
diagnostic interventions were also measured: raising the point-coordinate
length-y cost 44 to 56 did not fix it; lowering the paired-coordinate direction
costs 70 to 35 introduced another copy and grew the body to 200 bytes. Neither
instrumented output is a valid reconstruction, and neither is exact. Cost alone
is insufficient; copy/coalescing and interference decisions still matter.

## Source hypotheses tested

329 isolated compiles, summarized by outcome in `observations.json`:

- Partial carriers: one-field records, separate coordinate records and shared
  x/y records. The narrow forms disappear into the original scalar code.
- Inline field accessors, setters, reference accessors and difference methods,
  following the documented struct-piece numbering recipe.
- Explicit length-difference scalars, arrays and coordinate records, both store
  orders and product/sqr forms; point-copy construction and split assignments.
- Const-reference value bindings and temporary storage for either point
  difference; local scopes ending at the dot product; initialized dot locals.
- Four controls in the entire real AIWall unit, preserving its actual view
  types, vector iterator and established compiler flags. Same mismatch families.

No flags, barriers, artificial uses, assumptions or source padding were added
to a production candidate. Previous independent control-flow, callee-visibility
and compiler-profile investigations were read rather than repeated.

## Reproduce or continue

Inputs: BFME2 `c985deb9ff`, committed BFME1 pointer
`68c5ce2789e974f36b6c742d57437d157bc159e9`, default RTM backend; standalone flags
`/O1 /G7 /arch:SSE /MD /DNDEBUG`. Full-home controls use the home's own flags.
The freshness fetch saw newer donor `d02802ce29`; that update was not adopted
or marked verified, and no freshness-success stamp was written. No new donor
repair was used. Exact input-bank hash and output controls are in the JSON.

Restore the `.py.txt` generators as `.py` under `build/aiwall4eacf5/`. Run
carriers, partial_coords, accessors, length_carriers, ap_construction,
reference_values, home_context and scopes in that order. Each uses fresh scratch
source/object paths and the existing scorer. The original bank must agree with
the recorded hash when reproducing these observations.

For the observer, run `trace_color.py build/aiwall4eacf5/carriers/c1.cpp
build/aiwall4eacf5/trace/scalar.json`; use `partial-coords/c18.cpp` for point
coordinates and `partial-coords/c30.cpp` for paired coordinates. Omit its third
argument for observation-only mode. The optional priority intervention is
diagnostic only; never feed that object to a recovery or normal build cache.

Next useful investigation: observe copy/coalescing and interference changes
between the three forms, rather than replaying carrier/parenthesis spellings
or assuming candidate numbering is the whole cause. No missing retail provider
has been established for this helper. `remaining-diff.txt` preserves the actual
best mismatch; `paired-coordinates.patch` preserves the contrasting source form.
