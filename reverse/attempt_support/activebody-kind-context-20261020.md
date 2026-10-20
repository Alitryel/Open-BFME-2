# ActiveBody damage: checked template-kind storage

No exact recovery; retain `reverse/attempts/0x004bfe07.cpp` unchanged. The whole
bank and its previous attempt records/handoff were read. The existing home,
`Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp`, still passes
find_declared_unmatched. No production source, pin or row was changed.

Identity remains the BodyModuleInterface vtable slot and named WB lead described
in `0x004bfe07-20261019-w1.md`. Native is the complete 2107-byte interval
0x004BFE07..0x004C0642, RET 4 before the next function. All existing providers
needed by the baseline now resolve; the old missing-onDie explanation is stale.

New hypothesis: the successful ElvenWood/shroud checked-container work might
also explain this function's register allocation. ThingTemplate kind storage
starts at +0x108 and has 218 bits; replace the oversized private 16-word view
with actual STLport bitset<218>, preserving every later member offset by
adjusting padding. This is target layout evidence carried from the existing
BitFlags transfer/table work, not a donor-only size assumption. Object's separate
isKindOf call and its large status mask are not the template container and were
left alone.

Across 38 normal mismatch diagnostics:

* Baseline reproduces 2113 bytes, frame 0x104 versus retail 0x100, with
  30 structural regions / 80 reported memory / 29 register differences.
* Checked bitset with default inlining outlines its test (2183 bytes,
  unresolved); no trial-only helper name was pinned.
* Ob1/d2inlS100..1000 gives the correct frame but 2129 bytes and 33/87/25.
  The changed global inline budget also inlines native's list constructor and
  insert, so frame agreement alone is not an improvement.
* Explicit noinline specializations of those two existing native list callees
  restore their boundaries and give 2115 bytes, still the original wrong frame.
  Const indexing, unchecked test, and forceinline wrapper controls either retain
  that result or leave an unresolved bitset helper with default budgets.
* All 16 combinations of checked versus raw tests at the four logical groups
  (containment; source-kind pair; death-kind pair; repulsor) give 2110..2115
  bytes. The shortest two are 2110 bytes, frame 0x104, and 31/88/34: worse
  structural and operand differences than the bank, despite being closer in
  total length. They are not banked as improvements.

The remaining static-mask address webs, outer/damage pointers and later boolean
lifetimes are the previously demonstrated allocation wall. Earlier independent
control-flow, lifetime, visibility, layout and compiler explanations were
reviewed rather than repeated. No further supported explanation arose here.

Replays are the adjacent `activebody-kind-{bitset,boundaries,sites}-20261020.py.txt`
drivers; copy them to the corresponding build/ filenames in that order. The
first freezes the bank from 886b6b1a5a. Scratch results and full diagnostics are
in build/activebody-kind-bitset-oct20/. All experiments use unique scratch
source/output paths; checks proved no output collision with tracked Code units.

Inputs: BFME2 886b6b1a5a, BFME1 verified 92f6bbe8e1dcdb46b5d27da0674313efc822b790;
O1/EHs/MD/SSE, static STLport and the bank's existing allocator/string shims.
No exact-byte gate passed. Approximately eight minutes from 13:49 UTC on
2026-10-20, model=gpt-6.1-sol. Remote claim released after verdict recording.
