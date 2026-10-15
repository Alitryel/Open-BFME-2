Player-template getter emission repair, 2026-10-15

At BFME2 1fbd09924c, GameSpyStagingRoomSlotInit.cpp and
PalantirCommandInterfacePortrait.cpp emit Player::getPlayerTemplate COMDATs
that conflict with the first copy selected by the local census. Keep each
existing +0x34 view inline with dllimport/forceinline, suppressing its unused
external copy. No import is emitted. This changes no identity, layout, field,
compiler flag, pin, ledger row, shared header or baseline. Existing recovery
provenance and uncertainty remain unchanged; no donor body is imported.

The four census definers were reviewed: these two independent consumers,
Player.cpp and GameLogicDispatch.cpp. The latter uses a shared owner header;
its reconciliation with Player.cpp is separate work. Its exploratory file
claim was released without an edit. All retained bytes and relocations in
the two owned consumers independently establish this bounded repair.

Donor review: BFME1 c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 suppresses
surplus DamageInfo constructor copies using this same mechanism. The mechanism
applies; its layouts and bodies do not. Verified checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched to
61be6c32c. Another worker holds file:reference/open-bfme-1; the previously
documented old/new full-gate comparison remains outstanding. No reference
inputs, pointer or freshness-success stamp are changed.

context.json records the base commit and unchanged measurement artifact hash.
The fetched local index measures 825b86983f at 2026-10-15 12:37 and derives
from census 5986a99448 at 04:52. The committed status queue is discovery
evidence, not a substitute for this index. No census, index, status or history
is written by this repair.

Acceptance and limits:

- Strict preparation before and after and the ordinary byte gate pass all
  20 existing rows across the two consumers. After receipts are self-strict.
  String references: 32 literals and eight empty strings verified; one float
  reference verified; no skipped/baselined references or named imports.
- EH is 8/8 EXACT, with no missing objects or baseline entries. Class,
  declared-definition, COMDAT-variant, ledger and whitespace checks pass.
  Placement resweep finds zero bodies and zero pins.
- proof.py compares complete objects: exactly the getter COMDAT is removed
  from each. All 111 retained COMDATs and every retained nondebug section,
  extent, flags, definition, directive and normalized relocation are unchanged.
  Neither removed copy has an incoming nondebug relocation.
- Paired in-memory previews refresh the same two original objects and the
  same two strict-current replacements into separate copies of one frozen
  index. Staging findings fall 9 -> 8; portrait findings fall 6 -> 5. Exactly
  one getter conflict disappears per unit; every other finding is unchanged.
  Ordinary link_check agrees that both still have blockers. Existing LINKED
  bytes stay zero, and authored C++ growth is zero. No closed-strict or
  executable-placement improvement is claimed; external provider closure
  retains legacy index currency.
- Data facts are identical before/after. Enforced data checking exits 1 for
  seven pre-existing wrong-name findings outside its baseline: five portrait
  statics, MessageStreamSubsystem and g_currentAptOnlineCustomMatch. They are
  preserved, not repaired or excused. Converged-data admission passes eight
  protected addresses with zero second names/unjudged rows.
- Paired identity shadow findings fall 6 -> 5, removing the divergent getter
  definition; there are no new findings or baseline edits.

Remaining staging debt is five unresolved dependencies and three string
COMDATs. Portrait debt is one duplicate, three COMDAT conflicts and one
selected-provider finding. The data-name and reference-refresh work above
also remains. No maintainer-only verification runner was started.

Reproduce at the base revision: prepare-current both sources in sources.txt,
snapshot each source, strict object and dependency receipt into
build/player-template-inline-link-20261015/before, and save context.json.
Apply the two inline-emission annotations, prepare-current again, then run
proof.py, identity-proof.py and the commands in checks.json. Scratch snapshots
remain ignored; tracked JSON and logs preserve the paired evidence. The data
and local-link nonzero exits are explicitly recorded with their existing debt.
