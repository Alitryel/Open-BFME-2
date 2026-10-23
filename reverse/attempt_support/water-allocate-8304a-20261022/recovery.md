# Standing-water buffer allocation, 0x0008304A

Recovered on 2026-10-22 with gpt-6-astra. Native extent is
0x0008304A..0x000834CE (1156 bytes). The final C++ is in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp`.
The old bank is removed by `add_match`; its pre-recovery revision remains
available at BFME2 3e7fd99380. BFME1 inputs: 37c3022de1ab944c7ffe536440d637dc8199091c.

## Identity and layout evidence

The named WorldBuilder method at 0x0073F580 establishes the identity and
algorithm: select grid cells with a byte mask, reserve a cache, emit six
indices per selected cell, then copy its 44-byte vertex records. The native
body independently proves the target calls, loop operations, resource
lifetimes, target offsets and complete 1156-byte boundary.

WB's getBoundaryPoint at 0x007401A0 reads vector begin/end at +0x14/+0x18,
divides their difference by 12, and returns begin + index * 12. This supports
a vector of three-float boundary points, rather than the bank's raw float
pointer. Native origin construction reads its first point's Z. The resource
vectors are at +0x70/+0x7C/+0x88/+0x94. The cache constructor's existing neutral
name Rva00082A53 is retained: its row establishes cells +4, dimensions +0x10
and +0x14, records +0x18, origin +0x24, and spacing +0x30. No new identity pin,
class rename, or data-address alias is introduced. Existing neutral template
names and pointer-sized resource element spellings retain their uncertainty.

## The interacting fixes

1. The bank emitted 1152 bytes, score 0.9394287. Its byte-vector deallocation
   called C free; using the already established C++ free owner at 0x00030830
   restores the throwing-call EH state store near +0x45D: 1156 bytes,
   score 0.945147. This is the cache/vector allocator convention already used
   by the matched destructor; no synthetic throw specification was added.
2. A named `cell = y * nx + x` in the second mask pass and WB's named
   `numCells`, `indexCount = numCells * 2 * 3`, and
   `capacity = numCells * 2 + nx + 1` must be tested together. Their interaction
   fixes the count/y stack-home swap, keeps nx in its retail register, and
   produces retail's advancing mask cursor. Either isolated change had been
   misleading. Score 0.9884088; the whole parent EH graph is now exact.
3. Restore the actual boundary-vector accessor:
   `getBoundaryPoint(i) { return boundary.begin() + i; }`.
   Reading `getBoundaryPoint(0)->Z` for the origin resolves the remaining
   constructor-argument load order and EAX/ECX exchange. All 1156 bytes and
   relocations match. An explicit Vector3 copy constructor is unnecessary.

The allocator and cache constructor bodies must remain visible to MSVC 7.1;
declaration-only trials regress the frame. The two byte-vector helper copies
that conflict at link time use the existing inline-only dllimport/forceinline
pattern: their operations remain compiled inline and no import references are
emitted. uninitialized_fill_n uses the existing out-of-line provider. The cache
constructor and cached vertex lookup are rehomed with their two companion
rows (four rows total) from Rva00082A53Ctor.cpp; that split file is retired.
This removes the strong-definition collision without new symbol aliases.

## Controls and rejected explanations

The session began from the bank and read the served history. It did not repeat
the disproven inert-local k=1..48 scan. Factorial families covered loop entry,
latch/continue forms, index temporaries, scope of x/y, count and capacity
expressions, conditional count accumulation, long versus int dimensions,
visible helper bodies, temporary versus named center/origin objects, capacity
references and constness, and declaration/assignment permutations. A four-minute
permute run on the 0.9884 body made 266 trials with no improvement. Those
register/slot permutations did not replace the missing boundary-vector context.
A second-loop index axis in one early generator was accidentally a no-op;
it is not negative evidence. Later factorials tested that axis correctly.
Const/reference variants that failed compilation are not negative evidence.

The winning source uses the bank's /O1 /G7 /arch:SSE /MD /EHsc flags, static
STLport, and the existing bfmealloc shim, with _STLP_NO_EXCEPTIONS for the
native vector growth shape. No decoder reference source or decompiler output
was used as byte proof. WorldBuilder supplied source-shape/layout evidence;
retail bytes, relocations and EH metadata supplied acceptance proof.

## Acceptance

- The pre-edit full gate passed all 98,039 functions and all other checks.
- The recovered home unit passes 36/36 rows, including the four rehomed
  helper rows, plus literal and import checks; all existing water rows remain exact.
- eh_verify reports all six EH-bearing parents EXACT, including this method
  and the rehomed cache constructor, with no baseline allowances.
- Placement rescan: zero bodies, zero pins. Ledger and class checks pass.
- Code identity ran in shadow mode and reported eight findings; full output
  is preserved in identity-shadow.txt. This includes a binding finding on the
  existing WaterRenderObjClass constructor and seven divergent emitted helper
  definitions. No identity baseline was changed.
- The strict --current-ledger link preview refused 10,992 cached objects
  lacking its required compiler receipts. This is a validation limitation,
  not a link result. The ordinary preview uses the locally refreshed index
  so the retired split file is removed from provider accounting.
- Refreshed-index link_check: all three checked units LINKS: W3DWater.cpp
  (2784 bytes), PathfinderSidewaysAttack.cpp (2459), and the by-value byte
  vector resize provider (68). The original snapshot's Pathfinder report was
  stale; no change was needed in that unit. Full output is in link-preview.txt.
  This is a local preview, not a newly published census or executable link.

The BFME1 freshness fetch saw upstream 08d8bf51712d1662cb60929dcf38a2ea1ac324e9,
but another seat held file:reference/open-bfme-1. The verified committed
37c3022 inputs were retained, the update lock was released, and no successful
freshness receipt was written. This did not block the assigned recovery.

## Resume verification

The following session found this recovery already committed and rebased it onto
BFME2 ab9b90af8c. The water gate still passes 36/36 rows, all six EH graphs
remain EXACT, check_csv passes, and find_declared_unmatched reports no missing
rows. `progress.py origin/master` reports +1149 game-code C++ bytes (padding
excluded) and +1156 exact .text C++ bytes.
The refreshed link preview rebuilt 25 stale ledger objects and replaced one
additional cached object's definitions; the same three checked units still
report LINKS (5311 bytes total). This remains a preview, not a census update.

The fresh BFME1 fetch reached 4500af95a9d9a4b68c6398d5b82a1783f19c0a6f;
file:reference/open-bfme-1 remains claimed by codex-bce2-01a11b23-root.
The verified 37c3022 inputs were retained, the temporary update lock released,
and the stale freshness receipt was not renewed. The assigned body is complete;
no further reconstruction trials or unrelated body were started.
