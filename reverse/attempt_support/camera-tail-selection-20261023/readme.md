# PolygonTrigger camera tail, 2026-10-23

Target `?adjustCameraMovement@PolygonTrigger@@QAE_NPBUCoord3D@@0PAU2@_N@Z`,
native RVA 0x002E3AA8..0x002E3D7B, 723 bytes, RET 16. Input BFME2 revision
5d7bceb3dcbf19c2be6615c765da2d6974269033; BFME1 checkout/verified pointer
f890413e75e671748215ba2ef3304aa7953993e9. The other seat's fresh update lock
was respected. Source and dependency hashes are recorded in results.json.

The bank remains reverse/attempts/0x002e3aa8.cpp, 715 bytes. Its existing
0.9156293222683264 score is unchanged. This session found no better body and
made no Code, ledger, pin, header, baseline or verifier change.

## Prior exclusions and new hypothesis

Read the complete history with `/opt/runner/pick-hard --rva 0x2E3AA8`, the
20261021 planar-constructor handoff and the 20261022 selection-wall handoff.
Earlier work already excludes the ordinary product/add spellings, isolated
local lifetime changes, visible point/getter/intersection/math providers,
authenticated RTM/DDK/SP1 compiler changes, ordinary optimization switches,
and the volatile/barrier solution family. Do not repeat these on the same
inputs. Earlier parentheses controls preceded the current bank's planar
constructor repair, so interactions on this newer input were still open.

The first new hypothesis was that duplicated equivalent paths preserve
different allocation costs after merging, as established for 0x4404AC and
other recent recoveries. Follow-up families tested declaration numbering,
actual MathCoord3D base-type semantics, WB temporary scope interactions,
FP paren nodes, and aggregate value boundaries (motivated by the read-only
102F83 component-merging evidence). These are diagnostic source families,
not asserted reconstructions of retail's exact original spelling.

## Results

All compiles use the bank's /O1 /DNDEBUG /MD /arch:SSE settings and isolated
objects, eight workers per family. No direct shared-cache compiler call.

| Family | Generated variants | Result |
| --- | ---: | --- |
| Single duplicated operations/scopes, seven predicates | 98 | No exact; best retained-load alternative also retains a comparison |
| Eight duplicate sites, seven predicates, full factorial | 1792 | No exact; no improvement over the bank |
| 1..64 inert int/float declarations at eight boundaries | 1024 | One body, identical to bank |
| Flat versus Coord3DBase, ctor/assignment/dtor/formal/inline combinations | 192 | Five bodies; no improvement |
| Longer duplicated paths: slide, loop, function, candidate, output | 25 | No improvement |
| Ten WB lifetime/copy/mutator/helper-placement choices, full factorial | 1024 | Two bodies; no improvement |
| Integer-bit/pointer predicates at five tail sites, two source forms | 496 | No improvement |
| Eleven FP paren choices on the current bank, full factorial | 2048 | One body, identical to bank |
| Inline value/reference/pointer vector arguments and returned scaled values | 144 | One body, identical to bank |

Total: 6,843 generated variants plus nine baseline compiles, 6,852 valid
compiles, zero exact. The initial coarse generator hid candidate in a branch;
the initial staged-value generator accidentally used scaled in its own
initializer. Both bugs were corrected and those families rerun completely;
the final counts contain no compile errors. An early factorial harness also
tried resolving a body longer than the target; this was corrected before the
complete run. Invalid harness runs are not negative matching evidence.

The scorer masks branches, direct calls and relocated global addresses only
for instruction alignment. Its nd=13 on the baseline describes reordered
instructions/registers, not thirteen independent semantic defects. Exact
requires the full 723-byte extent and normal relocation resolution. These
diagnostic scores do not replace the byte gate and are not comparable with
the bank's older normalized-byte score. No family produced an exact candidate
for admission through the normal gates.

## Remaining residue and handoff

The WorldBuilder 0xABA7D0 twin was read again. Its local sequence supports
along.Scale(remaining), next(candidate), next.Add(along). Its Add/Sub calls
accept Coord3DBase; explicitly representing that base and formal relationship
did not change the baseline tail. The bank's visible math helpers still give
the retail 0x4C frame. Moving their definitions after the caller, copy/helper
forms and source scopes did not close the gap; earlier provider-visibility
and compiler-setting exclusions remain in force.

Retail tail begins +0x26C. It computes remaining*along.x into xmm2, reloads
candidate.x into xmm1 before the y product, computes z last, then adds x/y in
registers. The bank batches the products and folds candidate.x/y into addss
memory operands. Retail has 204 instructions, bank 202. Two missing 4-byte
movss loads explain the eight-byte extent deficit; resulting register roles,
schedule and outgoing jump displacements differ too. Every other normalized
region agrees. A single floating-condition duplicate retains an extra load
but also emits ucomiss/lahf, so it is not a better bank.

The tested source-cost, numbering, base-layout, lifetime, inline-boundary and
paren hypotheses do not explain the remaining instruction selection. A useful
next investigation is a read-only C2 trace of the scalar replacement and
operand-selection phases at this exact tail, comparing the current ordinary
bank with a load-retaining diagnostic. Do not repeat these families unchanged
or revive the old volatile/barrier bank. No missing callee currently blocks
the body. Claim released after recording this handoff. About 15 minutes,
model gpt-6.1-sol.

## Replay

Copy search.py.txt to build/camera-2e3aa8-20261023/search.py and restore
base.cpp from the recorded bank revision. Run one of single, factor, number,
layout, coarse, shape, bits, paren, value. Keep families sequential because
they share the baseline scratch filename. results.json preserves counts,
best diagnostics and input hashes. `diff <scratch.cpp>` prints aligned regions.
The script is evidence only, not a new production tool or verifier path.
