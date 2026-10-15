# Build-list link getter repair, 2026-10-15

Removed the competing, unused out-of-line `BuildListInfo::getNext() const`
COMDAT from four existing private views. Their loops now read the already
declared link field directly. No layout, pin, row, compiler flag, alias or
shared header changed.

| Consumer | Legacy findings before | After | Retained COMDATs unchanged |
| --- | ---: | ---: | ---: |
| AISkirmishPlayer.cpp | 3 | 2 | 107 |
| AIPlayerTeamBuild.cpp | 23 | 22 | 187 |
| SidesList_sidesInfo.cpp | 7 | 6 | 35 |
| Rva0032A186Finish.cpp | 9 | 8 | 5 |
| Total | 42 | 38 | 334 |

`object-proof.json` compares current, strictly receipted before/after objects
against the same census, refreshing all four objects together in each in-memory
trial. The only removed external COMDAT in each object is the four-byte getter
`8b412cc3`; no external COMDAT was added. Every retained body and relocation
digest, and the strong/undefined/weak symbol sets, are unchanged. Other census
copies are listed and were not modified. The on-disk index SHA256 is unchanged.
The baseline source revision, census commit and index hash are in
`measurement.json`; the census is dated 2026-10-15 09:31 at `28269d8e8d`.

This is a **legacy local link-preview improvement**, not a closed-strict census
measurement. Four reusable strict byte-verification receipts were refreshed;
no self-strict or closed-strict linkage gain is claimed. All four units remain
blocked, LINKED stays 0 -> 0 bytes, and authored C++ coverage grows by zero.
`all-link-after.txt` lists the remaining TeamInQueue/AIPlayer/Script/Snapshot
unresolved names and the independent STLport, Player, locomotor, SidesInfo and
BuildListInfo COMDAT/selected-definition conflicts.

## Target evidence and provenance

Retail directly loads the existing +0x2C link at the changed loop steps:

* `computeCenterAndRadiusOfBase`: 0x004F188E and 0x004F19A3.
* `adjustBuildList`: 0x004EF93F and 0x004EFAFD.
* `onStructureProduced`: 0x004F341F and 0x004F358D.
* `onUnitProduced`: 0x004F4AEB.
* `SidesInfo` copy constructor: 0x0032C73C.
* `BuildListInfo` destructor: 0x0032A1AC (initial link at 0x0032A19D).

`target-reads.json` records the existing ledger rows, complete retail row hashes
and disassembly candidates, including nearby stores; those stores are not
claimed as loop-link reads. Existing recovered class/function names remain
carried from the original recovery evidence; this repair establishes the target
field loads and unchanged bodies without making new identity/layout claims.

BFME 1 repair `d2e21369067f2f2c762c1c7ec2792c75f1ecf53d` was reviewed as a
lead for suppressing surplus incompatible COMDAT emission. Its constructor,
identity, pin, alias and layout changes do not apply here. No donor source was
imported. The verified BFME 1 checkout/pointer remains
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master was fetched at
`75ff0c1485a68eafb10344670711edbee8679b62`; pointer work is claimed by another
worker, so the inputs were preserved and no freshness success was stamped.

## Acceptance

* `./build.sh` on all four sources: 85/85 matched rows; 60 string literals,
  six empty-string references and 25 compiler floats verified.
* `link_check.py --prepare-current` on the four sources: strict reusable
  receipts refreshed. The existing SidesInfo EH funclet label renumbered from
  `$L943` to `$L937`; the verifier proves its unchanged 0x0077B70C placement from
  parent EH data, without a pin or ledger edit.
* EH verification: 25/25 exact, zero missing/not exact/baselined.
* `link_check.py` on the four sources: four fewer conflicts, no new findings.
* `link_check.py --new-variants`: accepted; frozen-file and class gates pass.
* Data shadow and converged checks explicitly cover all four sources: zero
  findings, zero second names at eight converged addresses.
* Placement rescans: no new bodies or pins. `check_csv.py`: passes.

The scoped file claims covered all edits. No full link cycle, census build,
nightly or boot runner was started. Broader linkage verification remains with
the maintainer/runner.
