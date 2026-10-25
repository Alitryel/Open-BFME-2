# ProjectileStreamUpdate GameLogic adoption prerequisite, 2026-10-25

Allocated family A shard 1/2 destination:
Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdate.cpp.
Scoped Update planner original-path evidence, alternatives and prerequisites
reviewed; currency check passed before edit. Placement has a same-spelling ZH
hint, not independent target identity proof; current --plan approves the row.
No move or merge is applied by this prerequisite.

The ordinary trial marks ProjectileStreamUpdateGetAllPoints.cpp as adopt_first
GameLogic. Its header queue row reports the private ObjectID redefinition.
Removed that unused private enum (its INVALID_ID enumerator is never read by
this body) and the private GameLogic declaration, including the registered
GameLogicObjectLookupView.h instead. ObjectID remains the same enum ABI; no
object ID value is rewritten. No canonical header or compiler flags changed.
`header_adopt_lane.py accept --class GameLogic SOURCE` passes and retires one
header queue row. No identity, data or gate baseline debt is retired.

Verification:
- ./build.sh SOURCE: 1/1 exact, 143 bytes; string, float and import checks pass.
  find_declared_unmatched.py passes; EH has zero missing objects or mismatches.
- allowed_symbols reports three references (two owner, one fold), zero wrong
  bindings; before/final refs.tsv is identical. External code definition digest
  c1bfd070deb8, extent 143 and exclusive COMDAT flag are unchanged. Undefined
  external symbol sets are identical (iteration order is immaterial).
- data_check.object_facts is identical, with no unread objects. Full
  data_check.py --converged passes: one source, ten addresses, zero second
  names, zero unjudged rows. link_check.py --new-variants exits zero.
  Scoped receipts are in ignored build/codex4-projectile-*.
  link_check.py SOURCE predicts LINKS 143 -> 143 bytes against census
  2026-10-25 21:36 at f995f30157; this is no census improvement claim.

Fresh ordinary dry-run removes adopt_first and repeats the seed/name-ref
accepted diagnostic (five rows), but its final text is the literal `compile`,
not a generated translation unit. The earlier trial also ends in `compile`.
Thus this diagnostic does not certify a complete composed object: do not apply
or count a merge from these reports. No merge trial is published. This commit
contains only the independently verified adoption; its definitions, COMDATs,
data facts and consumer bindings are unchanged as checked above. A later
composition needs a fresh successful trial and provider evidence.

Remaining composition blockers are independent: GameLogic and Coord3D are supplied both by
reference headers and the native header, MAX_PROJECTILE_STREAM/private class
views conflict, and Xfer/Thing definitions collide with the seed's reference
include environment. The seed intentionally exposes inline findObjectByID for
its already matched cullFrontOfList; do not replace that environment without
checking all consumers and COMDAT providers. Ctor/pool-key protected register
owners and two mixed donors remain. This is a demonstrated header-adoption
unblock, not a confirmed Luna merge or additional linked bytes.

Another allocated TU inspected without edits or claims: UnpauseSpecialPowerUpgrade.
Current --plan/ordinary --merge --dry-run accepts implementation plus name-ref,
four rows; ctor fails with base UpgradeModule undefined under composition and
has a different private multi-interface view. Reconcile the real ctor/vtable
provider before extending its merge. Receipts: build/codex4-unpause-*.

Compatibility audit before commit/publish: reviewed origin/master..HEAD and
isolated actual outgoing changes using origin/master...HEAD, plus the staged
adoption. The four earlier pending prerequisites and this adoption contain no
moves/deletions/absorptions. Active tools, hooks, workflows, includes, build
inputs and registries need no path repointing; historical EA paths are retained.
All debt keys survive except the two header rows removed through their accept
commands (OCLUpdate in the earlier commit, ProjectileStreamUpdate here).
File reduction, identity debt retirement and recovered C++ bytes: all zero.
Header debt retirement in the complete five-commit batch: two entries.

Keep file:Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdateGetAllPoints.cpp
and 0x0033F090 until publication, together with the earlier handoffs' claims.
OCLUpdate's remaining destination/donors are now held by codex2; do not race
those claims. Its two speculative new-header claims were released without edits.
