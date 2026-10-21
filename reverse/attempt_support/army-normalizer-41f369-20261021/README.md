# 0x0041F369 ArmyDefinition weight normalizer: TU-context wall (2026-10-21)

Session model claude-opus-5-5. The bank `reverse/attempts/0x0041f369.cpp` is unchanged.
Its residue is 9 bytes: totals[0] gets xmm2 instead of retail's xmm3, and the
block-1 scale gets xmm3 instead of xmm2.

## New target facts

- WB `getInterpolatedPercentageOfArmy` (WB 0x1332840) is in
  `...\SkirmishAI\ArmyDefinitionManager.cpp`, so the accessor 0x41F28C,
  getInterpolated 0x41F2A8, this normalizer and parseArmyDefinition 0x41F871
  all come from one original TU.
- WB getInterpolated calls the accessor four times (0/1, 1/2, default 2) and
  returns `a * t + (1.0f - t) * b` with a and b zero-initialised. That
  accessor-based source compiles to retail's 104 bytes under
  `/O1 /G7 /arch:SSE`. Both operand orders give 0 differing bytes.
- The accessor in direct-return switch form matches retail under the same
  flags, so all three bodies can share one TU (`insitu-context.cpp.txt`).

## Why it does not land

The normalizer's colouring depends on TU state that earlier functions leave behind:

- A batched TU with 800 variants had 44 exact bodies. In every case the
  preceding function had inlined a member helper:
  `normalize2(int i, const Real &total) { if (total > 0) { scale = 100/total; for (...) *acc(i) *= scale; } }`.
- A single preceding `normalize2(0, 1.0f);` is enough. So is
  `volatile Real a; normalize(0, a);`.
- `normalize(0, 1.0f)` by value (folded away) does not trigger it, and
  neither does a plain `*acc(0) *= 2.0f` loop.
- Inert preceding context: dummy functions with 0..68 live locals,
  preceding uses of 100.0f, and the real neighbours (accessor and
  getInterpolated in WB form).
- The same body replicated 64 times is never exact.

In the real-file context (accessor plus getInterpolated plus the normalizer), every
spelling stays at 9 bytes:

- 216 uniform condition/scale forms;
- 96 WB per-loop-iterator, shared-iterator, pre/post-increment, array/scalar forms;
- 148 random forms.

## Next lever

Find a real function of the original ArmyDefinitionManager.cpp that precedes the
normalizer and inlines an accessor loop through a non-folded helper. One candidate
is an ArmyDefinition or ArmyMemberDefinition method whose COMDAT the linker
placed elsewhere. Alternatively, explain what c2 state the inlined helper leaves
behind (inline-IL cache of the accessor?).
