# Local-player getter emission repair

PlayerUpdate.cpp and Rva0030F14CSelect.cpp mark their existing local getter
imported forceinline. Both callers already inline the +0x10 field access.
This removes two unused four-byte standalone COMDAT copies without changing
any retained code, data, relocation, external binding or linker directive.
No import reference, alias, pin or retail identity is introduced.

Target evidence is the complete existing 351-byte Player::update body at
0x002AE770 and 351-byte selection callback at 0x0030F14C. Their byte gates
independently preserve each caller's target accesses. The generic getter has
no proven retail address: the indexed first copy in PartitionManager.cpp reads
+0x0C, whereas the removed copies read +0x10. This repair neither changes that
provider nor asserts a canonical PlayerList layout or standalone getter name.

## Paired evidence

Base checkout 37e9a9166c60a933d320c49d17d669123ade034d; frozen runner index
ac77c85054, 2026-10-15 14:25. Its SHA-256 is in proof.json. No census, status,
index or history is rewritten. Original and repaired objects have version-2
strict receipts, with identical commands, dependency hashes, include inventory,
search roots and retry directories. Both sources were file-claimed before edits.
The original update receipt was refreshed after adding the evidence filenames,
then the edited source was restored and both current consumers prepared again.

Each paired preview substitutes only these two current consumer objects into
separate copies of the same frozen index. PartitionManager's provider remains
legacy and its object is not a strict-current witness.

| Consumer | Before findings | After findings | Legacy linked bytes |
| --- | ---: | ---: | ---: |
| PlayerUpdate.cpp | 9 | 8 | 0 -> 0 |
| Rva0030F14CSelect.cpp | 6 | 5 | 0 -> 0 |

Exactly one losing getter finding disappears per consumer; every other finding
is identical. Zero new authored C++ bytes, self-strict placement gains or
closed-strict gains are claimed. Neither unit links yet. The update still has
an iterator duplicate, vector/list COMDAT conflicts and wrong-selected list
helpers; selection retains list/allocation COMDAT and wrong-selected allocation
helpers. The normal local link check exits 1 for these retained blockers.

proof.py compares all retained nondebug COFF sections, flags, bytes, definitions,
directives and symbolic relocation targets, and requires identical strong,
undefined and weak-name sets. It also proves no retained relocation points at
either removed helper. proof.json records object/source/receipt hashes and all
paired findings. Replay uses ignored snapshots under
build/player-update-accessor-link-20261015 and the same frozen index.

## Acceptance and handoff

Both normal per-source builds and the final bounded strict preparation pass:
2/2 matched rows, zero baselined or skipped literal/import references. EH:
1 EXACT, no nonexact, baseline or missing-object cases. New-variant admission,
frozen-definition, canonical-class, enforced data, converged-data, ledger and
whitespace checks pass. Placement resweep: zero bodies and zero pins.
checks.txt records commands; link-after.txt retains the remaining findings.

The ranked family sweep found one further conflicting consumer,
GameLogicDispatch.cpp, whose getter is defined in the shared LogicDispatch
playerlist.h shim. It needs a separate shared-header/provider-consumer repair;
no claim or edit was made. sweep.json records that handoff. Previously repaired
list comparisons were not retried. No maintainer-only runner was used.

## Donor provenance and freshness

Reviewed BFME 1 repair commits c1315665a1b22beb7e6d9279548fe5b1c26ed1f9
(DamageInfo emission) and 66b19a8e95a4add525ef808fcea088e306798e2b
(Apt allocation emission). Only their imported-forceinline emission technique
is reused; donor names, layouts, identities and link gains are not target facts.
No donor source or headers changed.

The clean verified donor pointer remains a7c38d3b2597121f178ab5190b3062478823257d.
Official upstream master was fetched to 9f335a9ec; the overdue pointer comparison
and full verification remain under another worker's live
file:reference/open-bfme-1 claim. The pointer and old freshness stamp were kept;
this session does not claim the update verified.
