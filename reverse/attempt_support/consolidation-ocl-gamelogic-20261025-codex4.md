# OCLUpdate GameLogic adoption prerequisite, 2026-10-25

Allocated family A shard 1/2 TU:
Code/GameEngine/Source/GameLogic/Object/Update/OCLUpdate.cpp.
Scoped Update planner original-path evidence, alternatives and prerequisites
reviewed; currency check passed before edit. Current tu_skeleton --plan and
ordinary --merge TU --dry-run receipts are in build/codex4-ocl-*.

Concrete prerequisite: the ordinary trial marks
Common/OCLUpdate_getRemainingFrames.cpp as adopt_first GameLogic. Its header
queue row reports private m_frame access. Replaced the private GameLogic body
with its registered GameLogicObjectLookupView.h and the existing getFrame()
accessor. No canonical header changes. This retires one header queue row via
`header_adopt_lane.py accept --class GameLogic SOURCE` (PASS, retired 1).
No code-identity, data or gate-baseline key was retired.

Verification:
- ./build.sh SOURCE: 1/1 exact, 13 bytes; string/float/import checks pass.
  find_declared_unmatched.py and EH pass; no missing object.
- link_check.py SOURCE: LINKS, LINKED 13 -> 13 bytes against census
  2026-10-25 21:36 at f995f30157. Predictor only, no census improvement claim.
  --new-variants exits 0. --fetch-index refreshed the supported index.
- allowed_symbols: zero code references in this getter, no wrong binding.
  Existing code definition, undefined names and data bindings/definitions are
  identical. The accessor additionally emits a four-byte getFrame COMDAT,
  digest 84449fef877c: identical to all 395 census copies. This verifies the
  changed provider rather than inferring it from matching getter bytes.
- data_check.py --converged: one source, ten addresses, zero second names,
  zero unjudged rows. Baseline/final object snapshots are in ignored
  build/codex4-ocl-adopt-{defs,data,refs}-*.
- Ordinary merge trial still accepts seed and getter, four rows in total,
  and now has no adopt_first entry. Its composed object's external code
  definitions equal the union of original objects, including the certified
  getFrame copy; data_check.object_facts also agrees with no unread rows.
  Its four code references classify as two owner, one EH and one alias;
  zero wrong bindings. No merge was applied. Demonstrated adoption unblock,
  not a confirmed Luna landing.

Remaining independent blockers: getCountdownPercent needs a compatible
OCLUpdate declaration; BehaviorCtor has a conflicting explicit-vtable base
and undeclared ctor; Rva0049B2A2Xfer still hoists BfmeXfer above its operand
forwards. Two mixed sources remain. Do not equate the identity of that
address-named view with a donor name without target evidence.

Compatibility audit immediately before commit/publish: all actual outgoing
paths from base 2538d83cfd, pending Upgrade/Rain commits and staged adoption
have no moves/absorptions. origin/master..HEAD includes independently advanced
upstream work; triple-dot diff isolates our pending paths. Active tools, hooks,
workflows, includes, build inputs and registries need no path repointing.
Protected debt keys remain accounted for; only header queue acceptance removed
its proven-fixed row. Historical EA paths are retained.

File reduction and recovered C++ bytes: zero. Header debt retired: one entry.
Keep file:Common/OCLUpdate_getRemainingFrames.cpp and 0x0049B303 claims until
publication, along with the claims listed in earlier pending handoffs.
