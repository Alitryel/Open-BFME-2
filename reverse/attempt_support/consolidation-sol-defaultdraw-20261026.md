# W3DDefaultDraw class composition prerequisite, 2026-10-26

Seat codexb, family B shard 0/2. The refreshed runner queue lists this unheld
destination. The Drawable/ planner's original-path, alternatives and blockers
were reviewed, then regenerated after the upstream rebase and declaration
changes. Its currency check passes before each actual trial. The supported
current in-memory plan approves the ctor and name-key donor; the Common
W3DDrawNameGetters.cpp source is mixed and remains untouched. The displaced
friend-new row is not pulled into this TU. No TU-map file is regenerated.

The ordinary baseline dry-run accepts only W3DDefaultDrawPoolKey.cpp and its
two rows; the ctor fails C2511 because the chosen private class has no matching
constructor declaration. Both ordinary views now declare that existing ctor
and virtual getModuleNameKey, using a common DrawModule base declaration.
The base's protected virtual destructor preserves its vfptr at +0, avoiding
the empty-base relocation seen in the previously verified W3DTreeDraw repair.
Target evidence is the existing matched DrawModule constructor at 0x000B19A1
and protected virtual destructor row/fold at 0x000CEB6F. No new destructor
body or vtable is emitted. No source identity, function name, field, layout
from an external donor, pin or escape hatch is added.

## Verified improvement

- `./build.sh` on W3DDefaultDrawCtor.cpp and W3DDefaultDrawPoolKey.cpp passes
  before and after: 3/3 existing functions, one literal, zero float or import
  references. Both declared-unmatched scans and class_gate pass.
- The repaired ordinary `tu_skeleton.py --merge
  Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDefaultDraw.cpp
  --dry-run` accepts both ordinary donors, all three rows, no rejected donor.
  The 28-byte ctor is newly compatible. The compatible merge is left for Luna;
  a later Luna landing is not claimed here.
- Saved baseline objects indexed by build/sol-defaultdraw-before.json have
  two external providers each. Supported Obj/COMDAT comparison proves every
  standalone provider body, size, relocation, data value, section flag,
  COMDAT selection and undefined reference unchanged.
- The composed object build/tu_skeleton/8c4672320944309f.obj preserves the
  complete union of those providers and references: missing/added/changed
  providers 0/0/0, added/removed undefined references 0/0, no baseline
  multi-variant names. The TU-local static guard and name-key storage keep
  their exact names, bytes and relocation bindings. The supported
  eh_verify.verify_row API verifies the composed name-key EH graph EXACT,
  including the handler at 0x00761504 and cleanup at 0x007614F7.
- Scoped code identity is unchanged: three rows, five findings and no
  outside-baseline finding. data_check has the same two pre-existing
  wrong-name findings at 0x009EA304/0x009EA308; the older registered guard
  key and both data-ledger owners are preserved. No identity or data key is
  retired. link_check --new-variants --staged-peers --shadow exits zero
  without variant findings. This preview is not a census or full-link result.

Receipts: build/sol-defaultdraw-{before,after}-build.txt,
build/sol-defaultdraw-{before,after}-trial.txt,
build/sol-defaultdraw-{before,after}-identity.json,
build/sol-defaultdraw-{before,after}-data.txt,
build/sol-defaultdraw-proof.txt, build/sol-defaultdraw-composition-proof.txt,
and build/sol-defaultdraw-link.txt. `python3 build/sol-defaultdraw-proof.py`
and `python3 build/sol-water-composition-proof.py
build/sol-defaultdraw-before.json build/sol-defaultdraw-after-trial.txt`
reproduce the object-level comparisons through the supported readers.

## Batch audit and handoff

Audit at local HEAD 8bb231f7a6 covers origin/master..HEAD and the pending
ctor/pool-key source edits: font global repair, NetPacket evidence,
WaterTracks declarations and these two in-place edits. There are no outgoing
source path moves/deletions or absorbed donors. No include or compiler-profile
change is made here. Active tools, hooks, workflows, includes, build inputs
and registries need no repointing; historical EA paths and debt ownership
are retained. No protected register or ledger is changed in this prerequisite.
File reduction 0, recovered C++ bytes 0, identity/data debt retired 0.
Keep the destination, both donor and this handoff file scopes until confirmed
publication; then release them. Mixed Common rows still need their assigned
owner and the supported split lane.

Converged-data check passes: zero second names and zero unjudged rows.
Scoped Microsoft-header scan completes with zero local Microsoft declarations,
zero conflicts and zero failed scans. Neither file owns a header/MS-header
queue key, so there is no queue row to transfer or refresh in this in-place
prerequisite. Receipt: build/sol-defaultdraw-msheaders.txt.
