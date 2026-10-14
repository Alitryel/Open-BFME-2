# LivingWorld unsigned vector-growth emitter repair

Base BFME 2 revision: 6323365ee1406126e6d18dca1015f06e1c33dc21.
Runner index: commit 147cfae2cb, 2026-10-14 07:27; unchanged SHA256 in both
object-proof JSON records. The newer committed link status is discovery
information only and is not used as before/after measurement.

LivingWorldAIArmyMover.cpp and LivingWorldScoreKeeper.cpp each emit an
incidental external `_STL::max<unsigned int>` COMDAT that differs from retail.
Add the established TU-local unsigned overload before vector/map headers,
retaining comparison and reference-return semantics. Every use already inlines;
there are no nondebug incoming relocations to either removed external helper
or its replacement. No external provider or consumer binding changes, except
removing these unused external definitions. No layouts, ABI, algorithms,
compiler flags, dependencies, rows, pins, aliases, markers or globals change.

## Target evidence and acceptance

Existing matched rows retain their identities and target extents. Ordinary
byte gates and strict reusable preparation receipts pass 5/5 ArmyMover rows
and 35/35 ScoreKeeper rows, including ten ScoreKeeper funclets recovered through
verified parent EH maps despite compiler label renumbering. String, float and
import checks pass. Two ArmyMover and three ScoreKeeper EH parent rows are
EXACT; the archived EH outputs state the actual counts. No baseline is changed.

The archived object-proof.py compares the complete objects. All 154 ArmyMover
and 177 ScoreKeeper retained external COMDATs have identical bytes, extents and
relocation digests. Every other nondebug section and relocation remains equal
after normalizing COFF indices, including vtables, EH data and linker directives.
Strong, undefined and weak bindings remain equal. The sole removed COMDAT is
the 16-byte max template, `8b4424048b108b4c24083b110f42c1c3`; the eight-byte
private helper is `8b113b100f43c1c3`. Neither has outgoing relocations. This
whole-object equality independently proves the repair is applicable here.
Before/after source, object and receipt snapshots remain under ignored
build/army-mover-max-link-20261014. The proof records include the before/after object hashes.

Declared-function, canonical-class and new-variant admission checks pass.
ArmyMover passes the enforced data check with zero findings. The paired shadow
data check reports three existing ScoreKeeper wrong-name findings; comparison
against the archived before objects proves all three are unchanged, with no
unread row or new finding (data-proof.json). The optional paired enforced check
refuses those same existing findings outside its baseline. No baseline is
changed. Converged-data check finds no second names or unjudged rows across
eight protected addresses. Both placement sweeps
find zero additional bodies or pins. CSV and normal commit hooks also apply.

## Result and remaining blockers

| Consumer | Legacy local findings before -> after | Existing unique own bytes | Legacy local LINKED before -> after |
| --- | ---: | ---: | ---: |
| LivingWorldAIArmyMover.cpp | 19 -> 18 | 3,901 | 0 -> 0 |
| LivingWorldScoreKeeper.cpp | 19 -> 18 | 2,388 | 0 -> 0 |

Each removed finding is exactly the unsigned max COMDAT; every other finding
is unchanged (link-delta.json). Other consumers of max receive no claimed gain.
ArmyMover retains vector/allocator/tree iterator conflicts. ScoreKeeper retains
its unresolved Xfer wrapper and listener append calls, vector/tree/iterator
COMDAT conflicts and wrong-selected integer-vector providers; the complete
remaining names are archived. New authored C++ coverage is zero.

Strict preparation proves current byte-verified objects, not self-strict LINK
closure. The bounded `link_check.py --refresh --current-ledger` pair request
refuses judgment because 152 current-ledger objects are missing. No self-strict
or closed-strict LINK gain, fresh census result or runtime gain is claimed.
No full census build/measure/history, link cycle, nightly or boot runner ran.

## Donor review and reference freshness

Reviewed BFME 1 repair de59a7e9f891b3ed2d4221d151ca881f4b75a583 at retained
verified gitlink a7c38d3b2597121f178ab5190b3062478823257d. Its reconciliation
of Apt predicates whose inline code agrees but external COMDATs differ applies
as a repair principle; its code, layouts and link gains are not transferred.
BFME 2's verified local-max repair in GameLogicLoadPostProcess.cpp and
HordeContainModuleDataParse.cpp supplies this concrete pattern. Existing
ArmyDetails evidence was reused as the whole-object comparison method.
The same-index forty-two-consumer max cohort was searched; previously repaired
or currently claimed units were excluded before selecting these two consumers.
The p12 erase cohort is already repaired and was not retried from stale index
findings. Owner-binding dry-run leads were inspected without edits.

Official BFME 1 master was fetched at
58ab850fd1f734e310048b2e19c1ecb7ba112a3f. The clean verified checkout/gitlink is retained.
Comparative full verification remains outstanding after the prior interrupted
baseline with 2,806 stale units; no freshness-success stamp is written. Bounded
checks here use retained verified inputs. That update needs a complete valid-cache
baseline and comparison; no silent header substitution or weakened gate occurred.
