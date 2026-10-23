# Dispatcher PlayerList getter emission repair

The LogicDispatch private PlayerList header marks its existing local-player and
player-count getters imported forceinline. GameLogicDispatch.cpp already inlines
both accesses. Suppressing the two unused four-byte standalone copies removes
two losing COMDAT findings while preserving every retained nondebug section,
byte, relocation, definition, directive and external binding. No new import
reference, alias, pin, layout or standalone retail identity is introduced.

The complete 14,202-byte dispatcher at 0x00377613 independently verifies the
+0x10 local-player and +0x14 player-count accesses. The first generic indexed
copies in PartitionManager.cpp use +0x0C and +0x10, respectively. Neither generic
getter has a proven retail address. This change does not reconcile the class
or change that provider. The target dispatcher evidence remains its existing
WorldBuilder identity and complete native body; donor layouts are not proof.

## Measurement and checks

Base checkout: 3b6a471a1c30e3d86e386e1c4af106c558dcefdd. The runner's frozen
index measures ac77c85054, 2026-10-15 14:25 UTC. The published index fetch kept
this same index and added reusable compiled objects; its SHA-256 is recorded
in proof.json. No census, index, status or history is rewritten.

The paired local preview substitutes the original and repaired strict-current
consumer into separate in-memory copies of that index. Exactly two losing
getter findings disappear (18 -> 16 findings); every other finding is identical.
Legacy LINKED stays 0 -> 0 bytes. No new authored C++ bytes, self-strict placement
gain or closed-strict gain is claimed. Generic providers remain legacy index
entries, not strict-current closure witnesses.

proof.py verifies all retained nondebug COFF sections and all retained COMDATs,
checks that no retained relocation refers to either removed getter, and proves
identical strong, undefined and weak symbol sets. Version-2 original and repaired
receipts have the same compiler command, source, include inventory, dependency
keys, retry directories and search roots; only the claimed header's content hash
changes. Original receipts were refreshed after creating the evidence filenames
so the include inventory agrees. Ignored replay inputs live under
build/logicdispatch-playerlist-link-20261015/.

Normal and bounded strict byte gates pass both matched rows; EH is EXACT.
The local link check retains the other 16 blockers and exits 1 as expected.
Four pre-existing shadow data wrong-name findings (static guard, static sound,
TheStatsCollector and TheVictoryConditions) are identical before and after;
--enforce reports them, while the enforced converged-data check passes. No data
baseline is changed. Frozen-definition, class, new-variant and ledger checks
pass. The placement resweep finds zero bodies and zero pins.

## Scope, donor review and handoff

Both the header and its consumer were file-claimed before edits. Cached
receipt scanning finds only GameLogicDispatch.cpp using this header; the
hook's independent staged include-graph check determines the gate scope.
index-family.json records the frozen getter family. The prior update and
selection consumers were already repaired in 3b6a471a1c and were not retried.
This closes that evidence record's remaining PlayerList getter emission handoff.

Remaining dispatcher blockers include the rva00085124 duplicate, allocation
and list COMDAT conflicts, Object/Player getter conflicts, wrong-selected
NAMEKEY, and unresolved StatsCollector/VictoryConditions globals. These need
separate evidence-backed repairs; no whole-game linkage claim is made and no
maintainer-only runner was started.

Reviewed BFME 1 repair c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 (DamageInfo
constructor emission) and 66b19a8e95a4add525ef808fcea088e306798e2b (Apt allocation
emission). The imported-forceinline technique applies; names, layouts and donor
link gains do not transfer. No donor inputs changed. The checkout and committed
pointer remain a7c38d3b2597121f178ab5190b3062478823257d. Official upstream was
fetched to 579a8169e; the overdue pointer update/full comparison remains under
another worker's live file:reference/open-bfme-1 claim. The old freshness stamp
was preserved and this session does not claim that update verified.
