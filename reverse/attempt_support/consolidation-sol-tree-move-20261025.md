# Tree movement consolidation blocker, 2026-10-25

Seat codexb, device pool. Current routing approves W3DTreeBuffer.cpp and the
whole W3DTreeBufferRva000EA327.cpp donor. The prior normal trial
build/sol-tree-removal-final-after.txt rejects movement with C2039 for its
missing method declaration and C2065 for its count member. The matched
358-byte body spans 0x000EA327..0x000EA48D; it is already real C++.

Tested prerequisite hypotheses, all reverted:

- Add the destination declaration, align count/dirty/array member names and
  cast its existing canonical arrays to the donor views. A local array pointer
  changes record addressing from a this-relative +0x5c0 displacement to an
  array-relative base; many instructions differ.
- Preserve the complete original layout as a separate whole-object view.
  This preserves nearly all instructions, but scalar radius multiplication
  loads radius before scale instead of retail's scale before radius. Changing
  the C++ multiplication expression order does not repair this compiler choice.
- Adopt the canonical record/type headers and view only the existing sphere
  padding at record +0x48 and type +0x10. This changes SSE register allocation
  and reuse through the Center/Radius operations. It is not byte exact.

All trials used ./build.sh on the seed and donor. The seed's 17 rows stay
exact; the movement row fails. No altered body remains in Code and no ledger,
contract, compiler setting or protected register changed. Restored sources
are checked again before this handoff is committed. This is consolidation
prerequisite failure, not lost byte coverage; do not repeat these unchanged
view strategies. A future repair needs evidence that preserves the compiler's
this/member alias assumptions, or a properly accepted canonical layout change.
Scratch final receipt: build/sol-tree-move-build.txt (last failed variant).
The successful removal prerequisite a957cd3f2a remains for Luna to merge.
No source paths change in this outgoing batch; no consumer repointing is needed.
Source files removed 0; identity keys retired 0; recovered C++ bytes 0.
