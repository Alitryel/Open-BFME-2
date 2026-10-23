# CopyBlockMMX whole-file intrinsic repair attempt

Assembly-hatch removal only, zero additional matched-row coverage. No external
decoder source consulted. The original matched 110-byte implementation is
retained unchanged in Code. The saved complete C++ TU is diagnostic evidence,
not a replacement match or a pin.

## Selection and identity

After reassessing the independent width-domain and copy-topology hypotheses
for LastVerticalBand_1_2_Scale_MMX, selected the fixed-size four-row-snapshot
copy topology, which has no width countdown. Checked origin/master
0393df10e2db815e1651eb89083a39ad6e11faf8, prior attempt log and banks: no
earlier CopyBlockMMX attempt was found. Claimed the whole CopyBlockMmx.cpp
file and RVA 001D7630 under sol-team-vp6-20261023 before editing. The normal
declared-definition check confirmed its sole definition is already matched.

Spec: reverse/vp6_cleanroom/specs/001d7630.md. Native cdecl ABI with two
pointers and a stride (three arguments), and the complete 110-byte extent
through RET at 001D769D, independently
checked against retail. The first group loads rows 0..3 before any stores;
the second group loads rows 4..7 after those stores. This snapshot ordering
matters with overlapping buffers. The body has no calls, tables or EMMS.

## Inputs and measured trials

- BFME2 starting commit: 64eae8eac4 (evidence-only last-band continuation).
- BFME1 pin: 138757e9b74645fbcbb7724a7af2764e34931e11, untouched.
- Retail SHA256: f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640.
- Parent-granted t3-b3925755 OrbStack environment, BUILD_POOL=1,
  BFME_OBJSTORE=off. Only normal scoped build.sh compilation; object readback
  with build.read_object_symbol_bytes and existing Capstone, no raw compiler.
- Four ordinary __m64 local snapshots: 92 bytes, EBP frame and AND ESP,-8.
  Second-group vector allocation rotates MM3/MM0/MM1/MM2.
- Packed four-__m64 snapshot aggregate: also 92 bytes and the same alignment
  frame, but both groups now use MM0..MM3. Grouped lifetime/representation
  therefore affects allocation independently of mathematical expressions.
- Four unsigned-64-bit aggregate fields accessed by __m64 references: 85
  bytes, no EBP frame, no stack realignment, both groups use MM0..MM3.
  Removing packing leaves the same 85 bytes; the saved version has no
  packing directive. No artificial dead storage, padding or volatile used.
- Admitted /Og- on the scalar-backed snapshot: 262 bytes with stack spills
  for all row snapshots. It does not recover the isolated retail argument
  homing while preserving register-only MMX processing. No flag bypass.
- Two-iteration group loop, four-row snapshot per iteration, advance pointers
  only between groups: 75 bytes with a real runtime loop and three saved
  integer registers. The optimizer does not unroll it into the retail body.
- Restored explicit two-group scalar snapshot without packing: 85 bytes,
  identical to the earlier scalar-backed result. This is the saved candidate.

## Exact remaining mismatch

Retail bytes (110, no relocations):

    518b4424088b4c240c8b5424105389442404894c240c895424108b4c24108b4424048b5c240c8d14490f6f000f6f0c080f6f14480f6f1c108d04880f7f030f7f0c0b0f7f144b0f7f1c138d1c8b0f6f000f6f0c080f6f14480f6f1c100f7f030f7f0c0b0f7f144b0f7f1c135b59c3

Saved candidate bytes (85, no relocations):

    8b44240c8b4c24040f6f010f6f0c010f6f14418d14400f6f1c0a568b74240c0f7f060f7f0c060f7f14460f7f1c320f6f04818d0c810f6f0c010f6f14410f6f1c0a8d34860f7f060f7f0c060f7f14460f7f1c325ec3

Both have eight MOVQ loads and eight MOVQ stores with the same two four-row
snapshot groups and no EMMS. Retail homes three argument values into stack
slots and reloads them at 001D763E..001D7652, keeps source EAX, stride ECX,
destination EBX, and advances source before the first four stores. Candidate
keeps stride EAX, source ECX, destination ESI; argument homing disappears,
3*stride LEA is interleaved with loads, and the second-group first load folds
the 4*stride offset before advancing source. The scalar-backed representation
solves the alignment problem, not the remaining home-slot/register schedule.

These findings narrow concrete codegen blockers; they do not prove all C++
forms impossible. There is no hidden callee-visibility dependency: both
retail and compiled candidate are leaves. Retaining the retail stack copies
by forcing artificial address escapes/volatile would not be genuine recovery
and was not attempted. No wrapper, pin, naked body, emits, or EMMS was added.
No native/emulated function execution or full-tree gate was performed; the
semantic grouping is checked from spec and disassembly, not a runtime proof.

Resume by putting the saved whole-file candidate at its original path under
a fresh parent grant and using normal build.sh. Recheck live claims first.
The next useful hypothesis must explain the real argument-home mechanism
without manufacturing dead storage, or demonstrate a different admissible
register/lifetime topology. Repeating the packed/unpacked frame experiments
or lowering /Og with unchanged source does not address the remaining gap.
