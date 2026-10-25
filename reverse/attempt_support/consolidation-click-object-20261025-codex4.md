# ClickReactionBehavior Object/AI prerequisite, 2026-10-25

Allocated Sol family A, shard 1/2; destination
`Code/GameEngine/Source/GameLogic/Object/Behavior/ClickReactionBehavior.cpp`.
The scoped planner packet, alternatives and current in-memory approved routing
were reviewed. The planner currency check passed before editing. No TU map was
regenerated on disk. The two mixed and three protected donors remain untouched.

The normal before trial accepted only the update donor (one row); adding the
reaction donor failed because its Object methods and model-condition view were
missing from the update donor's shorter Object declaration. Both consumers now
include ClickReactionObjectView.h. It carries the reaction donor's existing
Object, ModelConditionFlags and AIUpdateInterface declarations unchanged, along
with their existing inline helpers and operand declarations. The update donor
uses that same AI interface at Object+0x258, whose slot 110 is isIdle. Its unused
short Object/AI views were removed. No layout, ledger name, external call,
compiler flag or retail string was changed; no class is newly registered.

Verification:

- Before and after `./build.sh` on ClickReactionBehaviorRva004596F9.cpp and
  Update/AIUpdate/Rva0045969F.cpp: 2/2 exact (363 + 90 retail bytes), with the
  string, float and import checks passing.
- Both frozen-file checks pass. Converged-data check: two sources, ten addresses,
  zero second names and zero unjudged rows. EH verification: no EH-bearing rows
  and no missing objects. No affected source owns a code/data identity baseline
  or canonical-header/Microsoft-header queue key; none was retired or dropped.
- Normal `tu_skeleton.py --merge ... --dry-run` now accepts both update and
  reaction donors, two rows. Receipts: build/codex4-click-before.txt and
  build/codex4-click-object-after.txt. Leave the compatible pair for Luna;
  this is a demonstrated dry-run unblock, not a confirmed downstream landing.
- The Xfer donor still fails because BfmeXfer.h is hoisted ahead of Snapshot and
  coordinate declarations. Its separate class hierarchy also needs review after
  include repair. The protected constructors/pool key and mixed sources remain.

Publication compatibility audit: origin/master..HEAD has no unpublished path
moves. This prerequisite adds one private header and changes its two consumers;
no existing source path is moved or deleted. The relative include from AIUpdate
resolves to the same header beside the approved Behavior destination (the normal
trial verifies this). Both consumers were built together. No active tool, hook,
workflow, build input, ledger, registry or fold-proof path needs repointing.
Original EA paths and historical evidence remain intact. No debt retirement,
file reduction or recovered C++ bytes is claimed.

Additional allocated read-only trial: PlayerTemplate accepts eight donors / 19
rows, but rejects fourteen others on private class/template conflicts. Its
Libraries donors are cross-family work and were not edited. Receipt:
build/codex4-playertemplate-before.txt. Destination investigation claim released.
The transient source files produced by that running trial caused two planner
scans to refuse; a fresh scoped scan and currency check succeeded after it ended.

## Xfer and hierarchy follow-up

The Xfer include is now wrapped by the private ClickReactionXferPrefix.h, which
keeps its existing operand class-keys before BfmeXfer.h when the composer hoists
includes. This first removed the include error but exposed competing
ClickReactionBehavior declarations (receipt: build/codex4-click-xfer-after.txt).

ClickReactionBehaviorView.h now supplies one declaration to Xfer and reaction.
It retains the reaction donor's PB base hierarchy, secondary interface and
fields at +0x24/+0x28. The existing rowed constructor 0x0045961D independently
uses the three-base UpdateModule layout followed by that secondary interface;
its UpdateModule spelling and out-of-line declarations replace the reaction's
private UpdateModuleView spelling. Xfer consumes the same existing fields and
keeps its existing nonvirtual qualified base call. No ledger symbol, global,
string, virtual implementation or protected constructor source was renamed or
changed. These are local declaration reconciliations, not new source-name or
canonical-layout claims.

- `./build.sh` on Xfer, reaction and update: 3/3 exact, 503 retail bytes kept;
  string, float and import checks pass (build/codex4-click-shared-build.txt).
- Frozen-file checks pass for all three; converged data: 3 sources, 10 addresses,
  zero second names/unjudged rows. EH: zero EH-bearing rows or missing objects.
- Normal dry-run now accepts all three eligible donors / three rows and rejects
  none (build/codex4-click-shared-after.txt). This is a demonstrated prerequisite
  unblock for Luna, not an applied merge. The two mixed and three protected
  donors remain untouched. No rows, debt keys or files were removed.
- No affected source owns a code-identity, header, or Microsoft-header queue key.
  No protected register was edited. The prior Object header's trailing blank
  line was also removed.

The outgoing range plus this change adds private headers but moves/deletes no
source path. Active tools, hooks, workflows, includes, build inputs and the
canonical-class registry have no references requiring repointing. The new
headers' consumers were verified together, including their eventual composed
location; historical paths remain unchanged. The previous path audit therefore
still applies to the entire pending batch. Claims remain held while the runner
queues publication; release the ClickReactionBehavior destination, all three
donors, three private headers and RVAs 0x00459579/0x0045969F/0x004596F9 after
confirmed publication. First prerequisite commit: 44a9537bc7.
