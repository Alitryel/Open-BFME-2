# Path 0x00365309: rotation and inline context trials

Base: 8bfb5231fb1a7766a8cc96d3dd86988b913e5e81. Model: gpt-6.
Donor pointer: a18d9ed50607e9175de4d6568798d7d73119de09 (official master fetched, unchanged).
Elapsed body work: 3.9 minutes; lane R, budget 30m.

Native boundary remains 0x00365309..0x00365B8A, 2177 bytes, RET28.
Identity/layout basis is unchanged from the bank: native accesses and calls,
WB F1FC60 curve construction, ZH Vector3 as a semantic guide, no original
method name asserted. This attempt does not add new identity/layout claims.
The prior bank reverse/attempts/0x00365309.cpp remains the best source.

## Measurements

71 isolated trials including baseline, serialized BUILD_POOL=1.
MSVC 7.1 under Wine 11; bank flags /ICode/Libraries/Include /O1 /DNDEBUG
/MD /arch:SSE /G7 /EHsc /Oy-, FLAG_DEFAULTS=off only in scratch trials.
Baseline fitness 0.97907, 126 differing bytes in the scorer's normalized
comparison. Independently inspected COFF extent is 2177, unresolved list empty.
This is not a match, a successful link-cycle measurement, or credited progress.

## Hypotheses tested

- Donor Vector3::Rotate_Z uses nested sinf/cosf arguments. The actual CRT form
  emits float-call sites instead of native double sin/cos and worsens the body
  to 2170 bytes; /Ob2 does not fix it. Nested casts reverse call evaluation;
  forceinline float wrappers or reversing the helper's two argument positions
  restore sin-before-cos but reproduce the bank's scheduling.
- Float/double/const return temporaries, references, named versus nested
  arguments, explicit XY/product temporaries and operation order do not improve.
- RTM, DDK-4035 and SP1 profiles produce the same best body. G5/G6, Ob2 and Os
  variants are unchanged; Op/Oi/Og- regress. Ot fails scorer extraction, not a
  successful candidate. Result lengths are scorer slices, not extent proofs.
- Scalar, reversed, reference and by-value Coord3D addition do not close the
  final x-term operand ordering. Reference += is unchanged.
- Before/after angle helper definitions (plain, noinline, inline), visible
  noinline Coord3D::length, and scratch composition with actual Path teardown,
  pool definition and free helper all reproduce the same best body.

## Remaining work

Cos-result FSTP and independent SSE loads still schedule differently; there
are also zero/load, loop-tail load and final add operand-order differences.
No evidence establishes compiler impossibility. Avoid repeating these exact
trials; a new source/context explanation is needed. The bank's statement that
0x00365E98 must land together is stale: that caller is already rowed in
Code/GameEngine/Source/GameLogic/Pathfinder/rva00365E98Rva00365E98Farm.cpp.

inspection.txt includes exact relocations and the diff. The scorer substitutes
DIR32 operands using retail offsets; shifted sites can show nonsensical absolute
operands in that diagnostic, which are not new address claims. trials.py.txt
preserves the exact scratch transformations; run its sections from the repo
root after copying the existing bank to build/lane-r-path/banked.cpp.
No Code file, pin, header, extent or existing bank was modified.
