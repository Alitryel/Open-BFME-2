# BridgeScaffoldBehavior composition prerequisite, 2026-10-25

Allocated family A shard 1/2 target:
`Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehavior.cpp`.
Reviewed the current Behavior planner packet, original-path evidence,
alternatives and prerequisites; its currency check passed before editing.
Current routing is rebuilt in memory by the TU tool; no map is committed.

The baseline ordinary merge trial accepted no composition. The getter failed
bytes; update conflicted with reference Coord3D/GameLogic; Xfer conflicted with
the reference Xfer and lacked IsLightCRC. Individual baseline sources were
already 6/6 byte exact. This was a composition prerequisite, not a lost row.

BridgeScaffoldBehaviorView.h now shares the accessed Object and module prefixes.
The matched getter proves the secondary BehaviorModule interface at +0x0C and
slot 14; the matched constructor independently establishes module subobjects at
+0, +0x0C, +0x10 and scaffold interface +0x20, with fields starting +0x24.
Existing opaque slot names are retained without inferring new identities.
The update's canonical inline Coord3D is reused; Xfer's existing Coord3DBase
operand is accessed by a cast rather than a competing coordinate definition.
BridgeScaffoldXferPrefix.h keeps the existing operand declarations with the
BfmeXfer include when the composition engine hoists includes. Shared headers,
compiler flags and the protected constructor/pool-key sources are unchanged.
The seed's preexisting loadPostProcess marker/body is retained.

Verification:

- `./build.sh` on seed/getter/update/Xfer: 6/6 exact, 812 retail bytes retained;
  string (0), float (3), import (0) checks pass. Baseline and final receipts:
  build/codex4-scaffold-baseline-build.txt, codex4-scaffold-shared-build.txt.
- `find_declared_unmatched.py` passes all four; the existing seed note remains.
- `data_check.py --converged`: four sources, ten addresses, zero second names
  and unjudged rows. `eh_verify.py`: no EH rows or missing objects.
- Normal `tu_skeleton.py --merge TU --dry-run` now accepts seed plus all three
  eligible donors / six rows, no rejections. Before/after receipts:
  build/codex4-scaffold-before.txt, codex4-scaffold-shared-dryrun.txt.
  This demonstrates an unblock; no downstream Luna merge is claimed.
- No identity/header-queue keys belong to the four edited sources. The protected
  pool-key data finding remains owned by its unchanged source. No register key,
  hatch, row, address, provider name or source path is added or removed.

Publication audit: the complete pending batch (ClickReaction, AIGuardRetaliate,
LivingWorldCampaign handoff, this prerequisite) contains no source moves or
absorptions. Active tools, hooks, workflows, build inputs, include consumers,
registries and ledgers have no obsolete path needing repointing. New private
header consumers verify together and the normal composition preserves their
relative includes; historical EA paths stay intact. File reduction, identity
retirement and recovered C++ bytes each remain zero.

Keep the destination, three donors and two new header file claims plus RVAs
0x00458279, 0x0045829E, 0x004582CB, 0x004582F3, 0x00458422, 0x00458638
until publication is confirmed. Earlier retained claims are listed in the
ClickReaction and AIGuardRetaliate handoffs. Two mixed sources and protected
ctor/pool-key sources remain outside the demonstrated merge.
