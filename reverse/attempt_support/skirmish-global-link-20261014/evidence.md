# LivingWorld battle options: existing skirmish global binding

The consumer is `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBattleGetResolutionOptions.cpp`,
`?GetResolutionOptions@LivingWorldBattle@@QAEHXZ`, RVA `0x003F4FD4`, extent 446.
Its `extern GameInfo *TheSkirmishGameInfo` declaration named an unresolved
datum. Forward-declaring `SkirmishGameInfo` and declaring the actual pointer
type binds to the existing strong definition in
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp:108`.
The existing cast to the target's prefix view remains the access mechanism.

Target evidence: the proven body ends at `0x003F5192`; its DIR32 operand at
offset 105 reaches VA `0x00E02EF0` (data RVA `0x00A02EF0`). The existing provider
defines `?TheSkirmishGameInfo@@3PAVSkirmishGameInfo@@A`. Before/after objects
have identical complete 446-byte bodies; exactly that relocation changes from
`?TheSkirmishGameInfo@@3PAVGameInfo@@A` to the provider's symbol. All five other
external COMDAT bodies, relocation targets, digests and extents are identical.
Exclusive definitions and weak externals are identical. The undefined-symbol
set changes only that binding. The provider object is byte-for-byte unchanged.
`proof.json` records object hashes and strict current-receipt checks for both
units. No class layout or additional body identity is asserted by this repair.

The donor linking pass reviewed BFME1 commit
`92a8d854746f059994f8ab370c133f3ba71eec24`: declaring the existing global's
real type and casting at use sites is applicable here. This is an independently
verified BFME2 declaration repair; donor addresses, layouts and function bodies
were not imported. Reviewed BFME1 checkout/pointer:
`23b143233b5a8664a3bdf8572df6d905c310a5a1`. The freshness fetch found upstream
`a7c38d3b2597121f178ab5190b3062478823257d`; another worker holds the reference
file claim, so the last verified pointer was preserved and no successful
freshness stamp was written.

Verification HEAD: `87697e262aa67b5a475a8205e2295e4e707b907e`.
Measurement index: `147cfae2cb`, `2026-10-14 07:27`; SHA256 is in `proof.json`.
Both units passed `link_check.py --prepare-current` before and after the edit
(6/6 matched), and `./build.sh` on both passed 6/6 with string, float and import
checks. The known provider funclet renumbering passed parent-EH verification.
`link_check.py --new-variants` reported no new variants; the consumer passed
`find_declared_unmatched.py`.

The same-index paired local `link_check.py` preview changes the consumer from
not linking (sole unresolved old global name) to LINKS, 0 -> 446 bytes. The
provider remains unlinked with existing unresolved, duplicate, losing-COMDAT
and wrong-selected blockers. This is a **legacy local preview** improvement,
not a new self-strict or closed-strict measurement. Strict compile receipts
prove input currency, not placement or provider closure. Full link cycles and
census measurements were not run; authored C++ byte growth is zero.

Enforced converged-data check: 2 sources, 8 addresses, zero second names and
zero unjudged rows. Shadow data check: before zero findings, after one
`wrong-name` at `0x00A02EF0`. The provisional, tool-written discovery ledger
still chooses the old `GameInfo*` name and lists both names; even its named
Recorder consumer already declares the correct `SkirmishGameInfo*` type.
That stale ownership choice is recorded as an outstanding shadow warning.
No baseline, data ownership row, pin or verifier was changed to suppress it.
The raw before/after commands and results are included alongside this note.
