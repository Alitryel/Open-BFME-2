Pointer-set cleanup link repair, 2026-10-22
=========================================

Baseline HEAD 73df4683fb; published census e20daa4e78 (retail-truth-3).
No census, full link cycle or status regeneration was run.

Paired legacy previews of the current objects, with the same explicit paths:

* Code/Libraries/Source/assetmanager/Rva0061FFA0.cpp: 0 -> 1,365 B.
* Code/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorRva00398E9A.cpp:
  0 -> 723 B (unique nonpadding bytes).

The worker's sole live blocker was allocator<tree-node<pointer>>::deallocate.
The castle also emitted competing tree/base destructor copies. Preserve stock
inline bodies with imported forceinline specializations; the base destructor
must instead be an ordinary external declaration. Importing that destructor
left an unresolved __imp_ reference despite exact row bytes; that trial was
replaced, not accepted. Allocation, element identity and tree layout are unchanged.

Acceptance: build.sh verifies all 9 rows, literals and imports; frozen-file
checks pass. link_check.py --prepare-current on the two explicit units verifies
9/9 with strict reusable receipts. The paired ordinary link_check.py preview
then links both (2,088 B total). This is a legacy-preview gain with self-strict
objects, not a closed-strict link measurement.

Sweep of the same deallocator name: assetmanager_impl.cpp and
AssetManagerImplRefresh.cpp retain 10 and 10+ other live helper blockers.
They were not modified for an unmeasurable gain. Castle's three live blockers
were all removed. Unreferenced diagnostics were left alone.

Donor review reused the current BFME1 37c3022d checkout and the tracked
20261021-bfme1-freshness-link-review.md; recent applyPacket/false-loser donor
repairs do not supply these allocator specializations. Source semantics come
from the existing STLport allocator/tree headers and target-byte verification.
No new naming, folding, address or data-layout claim is made.
