# Archive-directory destructor ownership repair

At source commit `884f993895bf02a2e9427477c4f5b7d5b81c1192`, ArchiveFile.cpp
emitted an implicit 89-byte `DetailedArchivedDirectoryInfo` destructor. Retail
has the existing 68-byte definition at RVA `0x00224252`, compiled by
ArchiveDirInfoO1.cpp. The competing copy caused one wrong-retail COMDAT finding
and wrong-selected findings in ArchiveFile.cpp, ArchiveDirInfoO1.cpp and
AptPlayerDtor.cpp. Those three units are the index's entire affected cohort.

The repair gives ArchiveFile.cpp a scoped ArchiveFileSystem.h with an explicit
destructor declaration. Apart from provenance comments and that declaration,
the header equals the ZH header (trailing whitespace normalized) at BFME1 revision
`64d369b90170b7e9ec917d646f020b11f13eb0d5`. The existing fields and inline
definitions are preserved. The native owner and consumer are unchanged.
Target evidence establishes the native teardown and member access; the donor
provides the retained header structure. This repair adds no identity or layout
claim for the consumer's existing opaque payload.

## Paired local evidence

The frozen census index is from measurement commit `2967eab33e`, dated
2026-10-18 08:17, SHA256
`ab684114e7a11cbc2fe38e3296716a21ef91eadcb39f4b83588ac58c1a5232ec`.
All three baseline objects were refreshed and strictly byte-verified at the
source commit above before saving them. The same cohort was strictly verified
after the change: 26/26 rows, no string, float or import findings.

| Unit | Before core findings | After core findings |
| --- | --- | --- |
| ArchiveFile.cpp | 4 COMDAT, 1 selected | 3 COMDAT |
| ArchiveDirInfoO1.cpp | 4 COMDAT, 1 selected | 4 COMDAT |
| AptPlayerDtor.cpp | 1 selected | none |

The paired local legacy prediction changes from zero clean units/bytes to one
clean unit and 246 nonpadding matched bytes. Four core findings disappear and
none are added. Self-strict receipts are current. Closed-strict gains and actual
executable linking are unmeasured; no census, full link cycle or measurement
history was run or changed.

`object-proof.json` records the paired findings and object hashes. `proof.py`
checks the removed destructor, 766 retained ArchiveFile COMDATs, unchanged
provider/consumer objects, nondebug section bytes/flags/definitions and symbolic
relocations, unchanged data bindings, consumed scoped-header hash, and no new
COMDAT variants. Associative sections of the removed destructor are excluded;
the SafeSEH inventory is compared by symbolic entry with multiplicity because
the compiler reorders it when the destructor disappears.

Remaining independent blockers are ArchiveFile's AsciiString construct, less
and allocator copies, and ArchiveDirInfoO1's directory-tree destructor, clear,
erase and pair-destructor copies. They are unchanged by this repair.

## Checks and reproduction

Successful checks: ArchiveFile's byte gate (1/1), the three-unit
`link_check.py --prepare-current` (26/26), the object proof, new-variant check,
class gate, declared-unmatched check, enforcing and converged data checks,
ledger and path-case checks, and `git diff --check`. `place_bodies.py` found no
incidental placements. The ordinary three-unit link check exits 1 because the
two archive units retain the independent blockers listed above.

Local scratch is `build/archivefile-directory-link-20261018/`: baseline source,
`before/` object and dependency snapshots, context and generated report. Run
`python3 reverse/attempt_support/archivefile-directory-link-20261018/proof.py`
while those snapshots and the recorded index remain available. To reproduce
from scratch, strictly prepare the three sources listed in context.json at the
recorded source commit against that index, save their objects/dependencies and
baseline context there, apply this repair, strictly prepare the same cohort,
then run the proof. Baseline object binaries are intentionally not committed.

The BFME1 freshness check fetched upstream `d348fca17814`; advancing the verified
pointer is blocked by another seat's live `file:reference/open-bfme-1` claim.
The existing verified pointer was preserved and no freshness-success stamp was
written. A separate MapUtil constructor-ownership trial was restored after
removing its old addMap body suppressed twelve rowed emissions; its blocked
evidence is recorded in re_attempts.log and its claims were released.
