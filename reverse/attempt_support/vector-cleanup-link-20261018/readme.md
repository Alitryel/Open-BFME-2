# Outlined STL vector cleanup ownership

At BFME 2 ca289991a6 with census c2c5ac8c27 (2026-10-18 11:36),
three callers emitted non-retail vector/base destructor copies and allocator
cleanup. Explicit specialization declarations bind their existing outlined
calls to the ledger's providers instead of emitting those copies. The retained
COMDAT bodies and relocations are unchanged; no aliases, pins or definitions
were added. Native caller bytes, target call relocations and EH establish the
required ownership, independently of donor names/layouts.

The same six current objects were checked before and after (three consumers,
StlportVectorDtorFamily.cpp, StlportVectorDtorChains.cpp, and
FamilyVectorDtors_CodexSep26.cpp):

| Consumer | Before | After |
| --- | ---: | ---: |
| Made002CC5E1Ctor.cpp | 0 | 463 |
| AttributeModifierPoolUpdateCtor.cpp | 0 | 278 |
| FlammableUpdateModuleDataCtor.cpp | 0 | 212 |
| Unchanged provider subtotal | 950 | 950 |
| Total local LINKED preview | 950 | 1,903 |

This is **+953 B in the local legacy preview**, with clean units increasing
from 2/6 to 5/6. It is not a self-strict or closed-strict LINK measurement.
StlportVectorDtorFamily.cpp retains independent blockers; the two other provider
units link before and after. The published census/status were not rewritten.
The 212 B Flammable count is the checker's unique byte count, not a sum of
possibly overlapping row extents.

Acceptance:

- `./build.sh` for all three consumers: all 14 rows exact.
- `python3 tools/link_check.py --prepare-current` on all six explicit units:
  83/83 rows pass strict reusable receipt verification, seven float literals
  verified, no string/import findings. This prepares providers; it does not
  establish LINK closure.
- Paired `python3 tools/link_check.py` on the six-unit cohort: logs attached.
- `python3 tools/link_check.py --new-variants` on the consumers: no new variants.
- `python3 tools/eh_verify.py` on the consumers: 5/5 EXACT.
- `data_check.py --enforce`: one existing baselined finding, zero new findings.
  `--converged`: nine addresses, no second names or unjudged rows.
- `class_gate.py`, `find_declared_unmatched.py`, `check_csv.py`, and
  `git diff --check`: pass.
- COMDAT proof attached: 49 retained copies unchanged, 32 removed, none added.

Donor review: official BFME 1 master 67f4eab2437e8a7ab3f22d3b3f9bf1eac91e081b
was reviewed for linking repairs (including 67f4eab2, 81dc7af4, c42f040f,
97a7c973, 95ca17f1, 06a23066 and 4b285d7b). Declaration-only cleanup ownership
is applicable where BFME 2's own bytes and relocations support it. No donor
layout was imported. The verified BFME 1 pointer remains 64d369b90170 because
its documented DIR32 vtable freshness blocker remains unresolved.

A separate three-caller Locomotor pair-destructor declaration trial passed all
three byte rows but removed no COMDAT copies and freed no bytes. It was fully
reverted and recorded with `re_log.py`; its claims were released. The next
repair needs evidence for the pair/vector cleanup ownership, rather than a
repeat of the ineffective declaration.

The shadow code-identity hook reports two findings (CameraMarker base-ctor
binding and duplicate Flammable ctor). A read-only comparison using the saved
pre-edit objects establishes both were already present; three divergent
cleanup-copy findings disappear. `identity-comparison.json` records 5 -> 2.
No shared cache object was replaced to perform this comparison.

Follow-up inline-cleanup sweep: Rva003F6A91Dtor.cpp (146 B in the legacy
preview) and Rva00148B84ReverseIndexDtor.cpp (62 B) each inline guarded free
in their matched destructor. The current void-pointer provider itself links
3,902 B; both callers remain blocked on incompatible emitted cleanup copies.
An extern-template vector/base destructor trial uninlined that cleanup and
failed two of six byte rows. A visible dllimport/forceinline specialization
trial also changed those two rows, including EH state/cleanup placement. After
these two attempts both files were restored, the full six-row gate passed,
blockers were recorded, and all eight claims were released. Attached logs
preserve the findings; no gain is claimed for this follow-up. Do not repeat the
same suppression trials without new compiler/EH evidence.

Rebase verification: upstream advanced to 327ed4930f0ae568c5f2f9d4c08833da54deff28 during this session.
The three consumers were rebuilt from that exact parent for a fresh before
measurement, then restored and byte-verified with all three current providers.
The paired result remains 950 -> 1,903 B and 2/6 -> 5/6 clean; all 14 baseline
consumer rows and all 83 final cohort rows pass. The changed upstream
StlportVectorDtorFamily provider retains independent blockers. Rebased logs
are attached.
