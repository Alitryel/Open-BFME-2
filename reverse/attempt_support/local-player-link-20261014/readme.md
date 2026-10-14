# Local PlayerList accessor link repair

Base checkout: 47b28d4111. Paired runner census index: 147cfae2cb,
2026-10-14 07:27; its SHA256 is recorded in object-proof.json. The committed
link_status.csv queue measures 67e1365aa9 and was used for discovery only.
No census index, status, history, baseline, pin or per-row data-back artifact
was changed. No ranking was manufactured from missing per-row artifacts.

Four units independently inline a +0x10 PlayerList view, emitting a surplus
getLocalPlayer COMDAT (8b4110c3). The first indexed copy belongs to
PartitionManager.cpp and reads +0x0C (8b410cc3, digest 96acfa69671b).
The census has no retail address for this generic accessor. These copies
cannot safely share one out-of-line implementation. This repair names each
local implementation helper for its use: announceLocalPlayer,
portraitLocalPlayer, garrisonLocalPlayer and disguiseLocalPlayer.

Every renamed helper's full four-byte body and relocation facts remain
identical. All 34 retained COMDATs are identical in full raw bytes, extents,
digests and relocation facts. External undefined/strong/weak bindings,
ordinary nondebug sections (including symbolic EH targets), and hatch counts
are unchanged. Both paired previews select the unchanged generic keeper.
The helpers are implementation names, not newly claimed retail identities.
Target +0x10 access evidence is the existing callers' complete byte gates;
this repair establishes no shared PlayerList layout or new global binding.

| Consumer | Existing authored bytes | Legacy findings before | After |
| --- | ---: | ---: | ---: |
| Object/Create/EvaAnnounceClientCreateSlots.cpp | 243 | 1 | 0 |
| Object/ObjectRva00294759.cpp | 298 | 2 | 1 |
| Object/Contain/GarrisonContainRecalcApparentControllingPlayer.cpp | 529 | 2 | 1 |
| Object/Update/SpecialDisguiseUpdateTriggerAbilityEffect.cpp | 764 | 1 | 0 |

Same-index legacy local preview: four losing COMDAT findings removed;
0/4 to 2/4 clean, LINKED 0 -> 1007 existing bytes. Strict reusable compiler
receipts are established for the four owned consumers before and after.
These are self-strict object witnesses, not closed-strict provider closure
or self-strict placement gains. The full provider closure, actual link.exe
placement and a fresh census remain unmeasured. New authored C++ bytes: zero.

Acceptance checks:

- Bounded link_check.py --prepare-current before and after: 9/9 exact rows,
  strict reusable receipts, explicit four-source scope.
- Final ./build.sh: 9/9 exact; one string and three compiler float references;
  zero baselined, skipped or unverified literal/import references.
- Full-object paired proof described above; before/after previews and hashes
  are in object-proof.json and paired-link-{before,after}.txt. Source/object
  backups and reproducible proof remain in build/local-player-link-20261014.
- EH verifier: 1 EXACT, none nonexact or missing. Class, frozen-definition,
  new-variants admission, converged-data and shadow-data checks pass.
  Converged-data: 4 sources, 8 addresses, no second names or unjudged rows.
- Affected-unit placement resweep: no bodies or pins. CSV and whitespace
  checks pass; normal commit hooks remain required.

Independent remaining legacy blockers: ObjectRva00294759.cpp references
unresolved CreateAHeroManager::rva002197A6; the selected
GarrisonContain::loadGarrisonPoints definition is proven not retail's.
Neither was retried, renamed or concealed by this repair.

The same-cause sweep inspected all 18 indexed losing getLocalPlayer units.
TerrainResourceClaimFeedback.cpp was already repaired. Thirteen further
units have the same +0x10 local view and pass frozen-definition checks;
they are listed in sweep-discovery.txt. Their bounded strict preparation
queued behind another full build's compiler lock. That still-waiting process
was cancelled before any of their sources changed; all 13 claims were
released. They remain eligible handoff work, not byte failures or exhausted
queues. No compiler lock, hook or verification was bypassed.

Reference review: verified BFME 1 pointer
23b143233b5a8664a3bdf8572df6d905c310a5a1. Reviewed linking repair
 de59a7e9f891b3ed2d4221d151ca881f4b75a583 (surplus inline Apt predicates),
 d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (non-retail local wrappers), and
 b955ec4852b51ec7190f1a4542a9f2864abda988 (geometry provider reconciliation).
Their conflicting local emission cause is applicable; their donor-specific
layouts, identities, aliases and pins are inapplicable. No donor code was
imported. The implementation uses the existing BFME 2 local-helper pattern
from TerrainResourceClaimFeedback.cpp and HordeContainMovementPosition.cpp.

Official BFME 1 master was fetched: a7c38d3b2597121f178ab5190b3062478823257d,
ahead of the verified pointer. Another worker owns file:reference/open-bfme-1;
the clean checkout and verified gitlink were preserved. The pointer update
and comparative full verification remain with that owner. No freshness
success stamp was written. No full link cycle, census build/measure/history,
nightly or boot/scheduler runner was started.
