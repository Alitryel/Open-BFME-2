# LivingWorldCampaign prerequisite trial, 2026-10-25

Allocated family A shard 1/2 target:
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaign.cpp.
Reviewed the scoped planner packet, original-path evidence and alternatives;
its currency check passed. Frozen seed check passes. Normal current-routing
`tu_skeleton.py --plan` reports 97 approved rows, 24 donor files, 24 mixed and
11 protected sources. No map was regenerated or committed.

Ordinary `--merge TU --dry-run` exits 2: no verified merge; the seed itself
fails under every merged flag set. C2950 at
reference/shims/bfmealloc/stl/_alloc.h:446 says allocator<char> cannot explicitly
instantiate an explicit specialization. Several Libraries donors additionally
redefine _STL::__false_type. FindRecord also lacks rva0052C7A2 in the stride
receiver view, but fixing this secondary declaration conflict cannot demonstrate
a working merge while the seed compile environment is blocked. Local evidence:
build/codex4-campaign-before.txt, build/codex4-campaign-plan.txt,
build/codex4-campaign-planner.txt. No source edits or shared-shim changes made;
no normal standalone byte regression is asserted. The cross-family Libraries
compile environment needs an owner-coordinated prerequisite investigation.

Read-only split inventory for Rva0052C119CurrentEntry.cpp finds two rows approved
for this TU and one unapproved row (the shared name getter). No split trial or
split applied. Identity/header registers have no key on FindRecord/StrideSearch/
CurrentEntry, but the other protected and mixed sources remain prerequisites.
Blocked seed recorded through re_log.py; destination claim released. No bytes,
file reduction, debt retirement or demonstrated unblock claimed.
