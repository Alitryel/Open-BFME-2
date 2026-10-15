# Object team accessor emission repair, 2026-10-15

Four current objects emitted an unused competing non-const `Object::getTeam`
COMDAT. Marking those existing inline definitions `dllimport` and `__forceinline`
keeps each caller's established access and suppresses the out-of-line definition.
No import references are introduced. No fields, identities, boundaries, compiler
flags, pins, globals, headers or ledger extents change.

Affected consumers:

- `Code/GameEngine/Source/GameLogic/AI/AIStatesDerivedOnExit.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp`
- `Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/PalantirCommandInterfacePortrait.cpp`
- `Code/GameEngine/Source/GameClient/MessageStream/SelectionXlatTranslateGameMessage.cpp`

## Measurement and acceptance

The target checkout was `27e1d4cc31a643909b0f74961950c5722f158f95`.
The unchanged runner index has SHA256
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`,
receipt commit `a2839ea429` (2026-10-15 13:35), census origin `5986a99448`
(2026-10-15 04:52). The committed link-status measurement is older; it has not
been rewritten. No census build, full link cycle or closed-strict measurement
was run.

`link_check.py --prepare-current` prepared each original and repaired object.
The paired proof refreshes each version separately into a copy of that same
index and compares `check_object` findings. It removes exactly one getter
COMDAT conflict per consumer, four total. All other unresolved, duplicate,
COMDAT, address and selected-provider findings are identical. All four units
still have other blockers, so local legacy LINKED bytes remain zero. New authored
C++ bytes are zero. No placement/self-strict or closed-strict gain is claimed.

`proof.json` records source, object and dependency-receipt hashes, strict-current
receipt results, removed definitions and the complete paired findings. Across
all four objects, all 860 retained COMDATs preserve bytes and relocation digests.
All other nondebug sections, external bindings and linker directives agree.
The comparison normalizes local-section relocation identities by content and
EH symbol indices rather than object symbol-table numbering. Each removed
section is seven bytes; no retained section refers to the removed name.

Acceptance checks:

- `./build.sh` on all four sources: 58/58 matched rows exact; literal, floating
  constant and import checks pass. Both prepare-current passes also verify them.
- EH verification before and after: nine EXACT, zero baseline and zero missing;
  see `eh-before.json` and `eh-after.json`.
- `find_declared_unmatched.py`, `class_gate.py`, `check_csv.py` and
  `link_check.py --new-variants`: pass for the affected scope.
- Shadow data checks: six identical pre-existing findings before and after,
  including five outside the shadow baseline; `data-proof.json` records the
  complete paired findings. No baseline was changed. Converged-data check:
  eight addresses, zero second definitions, zero unjudged.
- `place_bodies.py` on the four sources: zero new bodies and zero pins.
- `git diff --check`: pass.

## Provenance and remaining work

The existing target source and retail-matched callers establish the retained
access behavior; this repair makes no new standalone getter identity or layout
claim. BFME 1 donor commit `66b19a8e95a4add525ef808fcea088e306798e2b` was
reviewed for the inline-emission suppression mechanism only. Its types and
layouts are not imported. `peer-inventory.json` records the 17 indexed getter
copies. The fifth indexed wrong emitter, AIGuardInnerTargetRva00369FDF.cpp,
was already repaired in current source and was not changed again.

AIStatesDerivedOnExit still has seven unresolved helpers; AIGuardStates has
five unresolved state methods. Palantir still has a duplicate helper and
ThingTemplate/Drawable conflicts. Selection still has unresolved helpers and
other COMDAT/selected-provider conflicts. Exact lists are in `proof.json`.
These require separate evidence and repairs; no closure is inferred from this
local improvement. Shadow data-name debt also remains as recorded above.

BFME 1 freshness was checked against official master
`e082760734795655f086939df77b393f4b728375`. The verified checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`: another seat holds the reference-file
claim. Its update was therefore left to that owner, and no freshness-success
stamp was written. No moved headers or newer donor inputs were substituted.
