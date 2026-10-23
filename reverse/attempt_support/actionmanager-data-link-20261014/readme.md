# ActionManager global link repair

Base commit: 77c7d45bd04471a9c6441953b2afef035cb1f169. The local census
index measures 147cfae2cb at 2026-10-14 07:27; its SHA256 is
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
The older committed link_status.csv is discovery evidence only. Neither
index, census/status/history, ledger, pins, headers nor compiler flags change.

Two AI state units declared TheActionManager as BFMEActionManager *, leaving
an unresolved global with no provider. GameClient.cpp already defines the
real ActionManager * global. Declare that global in both consumers and cast
to the existing BFMEActionManager view at canEnterObject calls. Existing
getCanAttackObject calls retain ActionManager's method identity. This changes
no layout, method definition, control flow, global storage or call target.
Both file scopes were claimed before editing; no other consumer still declares
the private BFMEActionManager * global.

Target evidence: seven matched DIR32 operands address retail VA 0x00E030E8
(RVA 0x00A030E8), each preserved in object-proof.json. The data ledger names
?TheActionManager@@3PAVActionManager@@A there, with GameClient.cpp as owner.
That entry remains PROVISIONAL: retail references prove the native address,
and the existing object proves the real global definition, but this pass does
not prove its final placement in a linked image. BFMEActionManager::canEnterObject
retains its existing identity and 806-byte body at 0x0041C2D0 in
ActionManagerSpecialPowerChecks.cpp. The consumer rows' established identity,
ABI, layout and donor evidence are unchanged; this is a name-binding repair,
not new C++ recovery or a new class contract.

Dedicated donor review reuses the verified BFME 1 revision
23b143233b5a8664a3bdf8572df6d905c310a5a1 and reviews repairs
0835ab92bef30e3303e729a0ce09cf591368d0cd (real global ownership with
view casts) and 92a8d854746f059994f8ab370c133f3ba71eec24 (real debug data
owner with view casts). That binding principle applies; donor addresses,
layouts and data placement are not imported. No donor source is changed.

Acceptance and limits:

- Ordinary ./build.sh on the two consumers and two providers passes 60/60
  matched rows. Bounded link_check --prepare-current passes 60/60 with all
  four explicit units self-strict current: two data rows, ten string literals
  (zero baselined/skipped), 22 float literals and zero named imports verified.
- Object proof compares saved before objects against the final objects:
  every nondebug section's bytes, flags and extent, defined external, and
  relocation coordinate/type/value agrees. Only the private global relocation
  name changes. Compiler-local $L/$T names are normalized for comparison.
  All four receipt inventories are self-strict current; the two provider
  objects and emitted method/global definitions are unchanged.
- Paired same-index local preview (saved before/current after, identical four
  object refresh scope) removes exactly that unresolved name from each
  consumer. AIStatesBfmeOnExit findings drop 13 -> 12 (nine -> eight unresolved,
  four losing COMDATs unchanged). AIEnterStateOnEnter drops three -> two
  (unresolved -> zero, two losing COMDATs unchanged). All other findings and
  provider results agree exactly. Local LINKED remains 6,010 -> 6,010 bytes,
  one of four units clean; zero new authored bytes. This is a legacy census
  preview with self-strict explicit objects, not a closed-strict result.
- EH passes 5/5 EXACT with zero missing objects/baseline debt. Converged-data
  enforcement checks four sources and eight addresses: zero second names or
  unjudged rows. Paired shadow data checks remove the two global wrong-name
  findings (five -> three total); the unchanged special-power provider retains
  two outside-baseline static-data wrong-name findings at 0x00A03110 and
  0x00A03118, plus one existing baseline finding. No baseline was edited.
- New-variants admission, frozen-definition check, class gate, CSV and diff
  whitespace checks pass. Placement resweep of both changed units finds zero
  bodies and zero pins.
- link_check --refresh --current-ledger refuses because 416 current-ledger
  objects are missing. No closed-strict gain, final data-back placement or
  actual link.exe result is claimed. No maintainer-only full link cycle,
  census build/measure/history, nightly or boot runner was started.

Remaining AIStates blockers: eight unresolved Pathfinder/report/Object/charge/
WeaponTemplate callees and four existing Locomotor/AIUpdateInterface/Coord3D
COMDAT variants. AIEnter retains Locomotor::setAllowInvalidPosition and
AIInternalMoveToState::setAdjustsDestination COMDAT variants. Provider GameClient
has unrelated unresolved/COMDAT/selected-definition debt; the canEnterObject
provider remains locally link-clean. Exact names appear in link-after.txt.
Those blockers were not retried as part of this global repair.

BFME 1 freshness remains incomplete. Official master was fetched at
a7c38d3b2597121f178ab5190b3062478823257d; the checkout/gitlink stays at
23b14323, the retained verified inputs. The prior full old/new comparison
stopped during the old-input 2982-TU refresh with 2806 remaining, as recorded
in ../unicode-comparator-link-20261014/readme.md. This seat preserves that
handoff and the old success stamp: no pointer advance or freshness success
is claimed. A dedicated comparison is still needed before updating it.

Scratch before sources, objects/receipts, proof.py and delta.py remain under
build/actionmanager-data-link-20261014. The latter uses the normal local
check_object/refresh APIs with separate in-memory index copies; the on-disk
index hash is unchanged. Neither scratch script is new gate code.
