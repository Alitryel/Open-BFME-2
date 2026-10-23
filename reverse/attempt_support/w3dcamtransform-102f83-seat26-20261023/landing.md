# Camera 0x00102F83: exact landing, 23 October 2026

Continued only the previous session's camera task. The incoming bank (blob
`8f049066a3dd5397919c5a50d471cc2e01dfd991`, score 0.9807022095501403)
becomes an exact **4299-byte** body with **57 resolved relocations**. The
existing 1024-byte `transitionLiveMode` in the home unit remains exact.

Production uses the already pinned name
`?rva00102F83@Rva00102F83Owner@@QAEXPAVRva0010274F@@@Z` in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DCamTransform.cpp`.
The `Rva0010274F` descriptor and neutral owner are preserved; no new symbol pin,
original-method-name claim, address alias, compiler modification or assembly was
introduced. The old bank is deleted by `add_match.py`.

## Evidence and provenance

Retail establishes the whole boundary `0x00102F83..0x0010404E`, RET4, the E0
input record and every accessed offset/callee. The established W3DView caller
passes its camera state at receiver+0xC0. Earlier evidence maps the WorldBuilder
twin `0x007E3040..0x007E7303`, including its locals and expression lifetimes:
`../w3dcamtransform-102f83-r66-20261022/readme.md`. GeneralsMD supplies the
vector/matrix formulas; target bytes independently validate their application.
The scalar aggregate introduced here is an equivalent compiler-shape adaptation,
not an assertion about the original source type.

The canonical Coord3D contract gains the already matched `lengthSqr()`
declaration: owner 0x00065A1A, 31 bytes, called twice on input+0x64. Its layout is
unchanged. Production includes the canonical Coord3D and ICoord2D headers.
The BFME 2 AsciiString shim must precede the BFME 1 WWLib include directory.
The incoming bank had the opposite order: it silently selected the donor string
class and emitted a non-retail five-byte AsciiString::compare forwarding COMDAT.
Putting the BFME 2 shim first removes that link blocker while preserving every
camera byte. The real existing BfmeLiveCameraModeNameStorage global is retained.

## What closed the mismatch

The earlier bank already had the WB control flow, real WWMath sqrt and the
seat24 Rotate_X parenthesization. The previous session ruled out further
statement-order changes as the cause of delayed XY stores. This session used a
small translation probe before returning to the whole body:

1. A one-float aggregate result, consumed immediately into each field, produces
   the required immediate XY stores and XMM0 reuse. Ordinary scalar locals and
   by-value three-float helpers do not produce the same ownership/lifetime.
2. The initial source/target translations use that result. In the live arm,
   retain by-value source XY translation, then store source Z **before** target
   XY, as the WB flow shows. Target XY and source Z consume scalar results.
3. The real-zoom pitch helper takes its source vector by reference and wraps the
   division result in that same scalar type. This leaves only three scheduled
   instructions (17 differing bytes), with the correct 4299-byte extent.
4. Wrapping the existing `float(1.0-groundFraction)` result in the scalar type
   closes those last instructions. No arithmetic, padding, fake use, volatile
   access, global, barrier or extra emitted instruction is added.

The factorial families totaled **10136 full-body variants**, plus 15 small
translation probes. `results.json` records counts, best scores, unresolved
extents, immutable inputs and compiler hash. Families covered internal helper
lifetimes; scalar-result ownership; region combinations; nested arithmetic;
live translation order; pitch stages; constructor-result ownership; axis
product groupings; constructor-local lifetime/Set forms; trig ABI/types; ground
factor ownership; and local axis values. Two constructor-local variants exceed
the target extent and are not matches. Exhausted families need not be repeated.

## Stock compiler finding

A read-only Wine debugger trace of stock MSVC 7.1 c2.dll (13.10.3077) explains
why a seemingly unrelated earlier result changes the last pitch scheduling.
The scheduler region builder at RVA B4E2F advances its tuple cursor and counter;
at VA 107B4E6A it compares the counter with 0x50, then exits on greater-than.
The resulting region holds at most **81 tuples**. Before the final change,
graph 20 has 81 tuples and ends with the sine-times-zero multiply; the live
camera compare is in graph 21. The earlier sine copy has higher scheduling
priority and issues before the pop and other multiply. The cap prevents the
next graph's compare from interleaving as retail does.

The used ground-factor aggregate changes that region boundary: graph 20 still
has 81 tuples, graph 21 grows from 72 to 73, and the resulting machine order is
exact. This is a source-level solution to the fixed tuple cap. The interpretation
of intermediate tuples is compiler RE; exact ordinary output is separately
proven. Both traced objects equal their ordinary counterparts in complete raw
camera bytes **and every relocation**, recorded in `results.json`.
`schedule-tail.json` retains graph sizes and the relevant ready-queue tails.
An attempted data watchpoint on stale heap addresses failed with Bad address;
it supplied no evidence and played no part in the result.

## Shared-header prerequisite

The first normal commit gate caught a genuine dependency regression in
`TeamTemplateInfo::loadFromDict` (0x0039FEBB, 3606 bytes). Adding the canonical
lengthSqr declaration reversed two independent ESI/EDI restores after the
waypoint's three MOVSDs: four bytes at +0x8BC differed, with unchanged extent.
Moving the declaration to the header's end alone did not resolve it.

A 64-way assignment/accessor/loop-scope family did not improve the four bytes.
A 144-way inline-copy family tested reference/pointer/value arguments, helper
placement, link access and loop scope: 48 were exact. The minimal chosen form
copies the home member through a used inline reference helper placed before
Waypoint's definition. Its argument names are descriptive in production; the
ordinary gate confirms the result there. No extra runtime call or instruction
is emitted. This is an equivalent source adaptation, not a claim about donor
spelling. Both the 3606-byte parent and all its existing children pass: the
normal build verifies 33/33 rows across this unit and the camera unit, including
29 funclets resolved through the parent's EH data after label renumbering.
`dependency-results.json` and `dependency-search.py.txt` preserve the search.

A separate 39-variant header-position probe pasted the header into private
sources and appeared exact everywhere; an unchanged-source real-include
control reproduced the four-byte mismatch. Thus that probe changed compilation
context and does not establish that declaration placement fixes the problem.

The next dependency batch exposed MapCache::writeCacheINI (0x00303409,
1503 bytes): 11 bytes at +0x20C..+0x210, +0x228..+0x22C and +0x244 reversed
which yes/no constant occupies ESI. A private compilation with the actual old
header was exact; the same source with the new header reproduced those 11
bytes. Earlier failed iterator changes and 1..16 declaration scans were read
and not repeated. 352 label lifetime/helper/ownership variants and 1680 real
include-order variants left at least those 11 bytes. The new conditional-call
family found an exact minimal form: initialize the final isScenarioMP label to
no, conditionally assign yes, then pass the label to fprintf. The first two
selections remain unchanged. Its scoped local affects the shared constant's
register choice without adding any emitted instruction. The production form
with a descriptive local name passes all gates on the three edited units:
**41/41 rows**, 35 relocated funclets, 44 string literals plus 9 empty strings,
21 floating literals and 3 imports. No new EH rows were required for either
already-matched dependency.

The conditional-call family stopped after 162 compiled objects because an
unrelated longer variant raised the verifier's extent exception at offset1501;
it was not treated as a candidate. Seven exact results had already been
reported, including 0_0_5, the minimal chosen change. The search is preserved
with its original base revision and an exception capture so its full family
can be replayed without that diagnostic stopping it. `map-dependency.json`
records the controls and successful ordinary verification; the rejected
families need not be repeated.

The sixth dependency batch exposed an existing stale EH parent annotation:
Unwind@00b88227 (0x00788227, 8 bytes) still named the old rva00439E0C method
although commit 21640a6100 renamed its already-matched parent to detected.
The header recompile renumbered $L8352 to $L8353, revealing the broken parent
lookup. Correcting only parent= to the current ledger name lets the existing
verifier locate the child through the byte-exact parent's EH graph. The unit
passes 7/7 ordinary rows, and eh_verify reports all three graphs EXACT. No
code, identity, object-symbol pin, baseline or gate rule changed. See
`invisibility-eh.json` and `invisibility-eh-build.txt`.

The code-identity shadow detector reports an unaddressed Vector3 copy-constructor
COMDAT as divergent. It has no ledger/pin identity and no callers in this unit;
the link predictor accepts the camera and caller under its retail-truth rules.
An explicit forceinline trial still emitted that copy and was not adopted.
No verifier or baseline was changed.

## Reproduction and checks

Input BFME 2 revision: `27f85d806d271727d1fae17cbd3123343ec1e354`.
BFME 1 pointer: `f36a4db066aa61edeee90085a31d628eb829001d`.
Flags: `/O1 /G7 /arch:SSE /DNDEBUG /MD`, normal repository compiler command.
The fresh BFME 1 update lock belongs to codex8; this seat preserved its pointer
and did not run a concurrent update.

Run `python3 reverse/attempt_support/w3dcamtransform-102f83-seat26-20261023/replay.py.txt`
to reconstruct the final diagnostic candidates from the immutable bank and
patches into ignored build/ and verify full resolved bytes. Diagnostic names
remain only in that replay; production uses the existing neutral symbol.
The replay also restores the optional probe and read-only debugger scripts.
The trace command is `python3 build/camera-102f83-seat26-replay/schedule.py
build/camera-102f83-seat26-replay/trials/winner.cpp
build/camera-102f83-seat26-replay/traced.obj`.

Completed checks before commit:

- `add_match.py`: complete camera body verified and row recorded; bank removed.
- `./build.sh .../W3DCamTransform.cpp`: 2/2 bodies, strings (2), float literals
  (21), imports and source claims pass using the BFME 2 string shim first.
- `find_declared_unmatched.py`: all definitions matched; class gate passes.
- `place_bodies.py`: zero additional bodies or pins. The repaired dependency placement scans also report zero bodies/pins.
  Production emits no EH
  handlers, unwind funclets or catch bodies, so no child rows are pending.
- Published census index fetched (2026-10-23 03:12, 491a8b3d87).
  `link_check.py` predicts the camera home, its W3DView caller and the repaired
  TeamTemplateInfo and MapCache units LINKS;
  its interval accounting increases from 1024 to 6471 linked bytes across the
  pair. This is a predictor, not a new census or link-cycle run.
- `./build.sh` on both edited units: 41/41 rows, strings, float literals and
  imports pass; all definitions are declared.
- The remaining 415 shared-header dependents pass 2804/2804 rows after
  399 recompiles, with all strings, floats and imports verified. Earlier
  batches verified 5002 rows; the next batch exposed only the corrected
  EH parent annotation above.
- The ordinary commit hooks provide the required shared-header dependency gate.

No unresolved camera mismatch or known link blocker remains. The latest user
instruction limits this session to this unfinished task; the only additional
claims are the two dependency files and one EH child repaired for the same landing.
