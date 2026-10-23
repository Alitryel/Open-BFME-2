# Collision axis-list merge sort, 0x007586F0

Not matched. Native extent is 460 bytes (007586F0..007588BC); WorldBuilder
01802EC0 corroborates the four head/tail/count records, alternating prepend,
width-doubling stable merge, and final backlink repair. Neither image supplies
a recovered method name. The existing home declaration rva007586F0 is retained.
Its matched 1,244-byte UpdateSort caller establishes the receiver and list layout.

Inputs: BFME2 d8961f14c218725a3dc0890fe1dcc313d533d469; verified BFME1
f52d3a5cb41976aafa760e8db12c4bfdb2be91e8. The BFME1 collision donor units
produced no new placements. Its banked 009A2750 merge is a reconstruction, not
original source or independent proof. Flags: /O2 /G6 /DNDEBUG /MD; default VC7.1.

`clean-home.patch` adds a barrier-free diagnostic to the actual home TU. Apply
only in scratch; do not install as production code. It emits 454 bytes with an
0x50-byte frame; retail uses 0x4C. The unhoisted destination variant emits 462
bytes. The existing bank is unchanged, including its historical provenance;
its artificial barriers and redundant source-index condition are not solutions.

Tested and refuted in this pass:

- Actual receiver layout versus the old oversized heads array does not fix it.
- Signed counters, left/right declaration order, reference aliases and guarded
  do/while retain the spill. A remaining-count struct grows the frame to 0x54.
- Hoisting the destination gives 454 bytes, but retains the extra stack slot.
- Explicit old-count append, prepend accessors, and separate head/tail stores
  do not reproduce retail register allocation.
- Deferred next phase, early output, separate phase assignment and pair cursor
  emit 470, 456, 470 and 456 bytes respectively; no exact body.
- VC7.1 DDK4035 and SP1, /Ob1, /Op, /Os and /Og- do not fix the native shape.
- Reversing comparison operands, overloaded comparison and inline value/reference
  comparison helpers do not reproduce the native ordered-greater branch.
  Negating <= also fails and is not accepted as equivalent for NaN inputs.

Remaining concrete residue: retail keeps source-offset computation in EAX across
its merge-loop backedge without the clean candidate's spill; native head cursor
uses EBX, left chain EDI and right chain EBX in the merge. Retail loads left float
then compares right with TEST AH,41 / JE; the candidate loads right first and
uses TEST AH,05 / JNP. Retail append increments the loaded count and writes head
before tail for the empty list. There are no native calls, relocations or EH.
No new evidence-backed hypothesis remained after the list/compare trials.

Reproduce after applying the diagnostic to a scratch copy:
`python3 tools/explain_mismatch.py '?rva007586F0@CollisionManagerImpl@@QAEXXZ'
 --rva 0x007586F0 --size 460 --source <scratch.cpp>`.
Use the reported compiled symbol size: compile_function's row-sized byte result
clips overlong output and is not a valid emitted-size metric. No progress claimed.
