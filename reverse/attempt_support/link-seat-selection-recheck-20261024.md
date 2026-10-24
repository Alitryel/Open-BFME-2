# Link selection reassessment, 2026-10-24

Inputs: BFME 2 `dc2d68f1bf`, verified BFME 1 `f5140c1c`, published census
`11b3872700` (2026-10-23 23:06). No production source was changed and no
new linking or coverage gain is claimed. These are legacy previews, not
self-strict or closed-strict measurements.

## Prerequisite-copy worker: current selection blocker

The current three-provider preview of ProductionPrerequisiteRecVectorCopy.cpp,
ProductionPrerequisiteCopyCtor.cpp and
stlport_vector_stringrecord_2cf5b1_allocate_copy.cpp reports only the middle
unit linking: **145 -> 145 B**. The constructor and helper units retain
172 B and 120 B respectively behind the same wrong-selected const-copy worker.
This supersedes the earlier successful preview for these particular inputs;
see prereq-copy-provider-20261023-bce2/typed-reconciliation.md for the established
native identity, exact parent/EH evidence and prior failed declaration trials.

For the existing typed `__uninitialized_copy` owner at 0x004F5097, the new
index has these COMDAT copies, in link order:

| Position | Source | Retail verdict |
| --- | --- | --- |
| 6403 | ProductionPrerequisiteRecVectorCopy.cpp | wrong |
| 9499 | stlport_vector_stringrecord_2cf5b1_allocate_copy.cpp | retail |
| 9529 | ProductionPrerequisiteAssign.cpp | retail |

There is no selection exception. Consequently the later correct copies do
not rescue the first copy under retail-truth-4. The constructor's comment
saying that the link keeps the no-EH worker is no longer true for this index.

The prior declaration-only/extern-template trials changed the 96 B parent
to 105 B; do not repeat them. An untested hypothesis is a TU-local explicit
worker specialization using the existing no-EH STL construction loop while
retaining the parent's EH-enabled compilation. It must preserve the whole
38 B worker, its construction callee, the 96 B parent and its EH graph, and
must pass normal identity/byte/link checks. It is only a hypothesis, not banked
code or a proven fix. Claiming 0x004F5097 was refused: StarkillerHDX@fleet
holds it for link seat w5. Released both acquired file claims and 0x002CFE45;
no compiler trial or source edit was made across that claim.

## Other checks

Fetched the current published index and objects; checked link_rank --top 30,
--near 2, --owner-gaps --near 2, class_views --blockers and repair_queue link.
The read-only current-object probe retained 25 failing previews / 6,465
census-sized bytes. This is triage, not proof of repository-wide exhaustion.
The largest remaining causes are documented helper-codegen, unrecovered
callees and native class/vtable contracts; many broad families are claimed.

Current BuildListInfo xfer/destructor providers already link together, 454 B.
The icon-unit constructor already links, 156 B, while its base constructor
still needs seven independently identified virtual providers. Neither is a
new gain. FiringTracker ctor/dtor/Xfer preview retains only the Xfer unit's
1,543 B: the first two have three conflicting private FiringTracker tables.
Their tiny private interface declarations need native class reconciliation;
no table suppression trial was made.

name_globals --dry-run proposes zero changes. A rehome read-only rescan again
finds the known 100 split units and the previously known EntryCtor placement;
stopped the redundant scan after checking the leading pairs. Its previously
claimed home is now available, but the current paired preview already links
both the 29 B split unit and the 2,441 B battle home. Rehoming would add no
linked bytes. Other known exact pairs also already link.
No matching data-back measurement artifact is available. No maintainer-only
verification runner was started.

Fetched BFME 1 official master `8964e30d91f3e69642b0455abff1fd2a79496a64`;
reviewed the latest inherited StringBase length-getter repair. This census has
no AsciiString/UnicodeString getLength blockers to transfer it to. Retained
the verified f5140c1c checkout and wrote no freshness-success stamp; the donor
scope remains foreign-claimed. Earlier reviewed donor leads remain applicable
only after their recorded prerequisites change.

check_csv passes; progress.py origin/master reports +0 coverage and linking
deltas. Existing source and banked attempts are preserved. Resume the worker
repair with its claim owner, or reassess after new class/provider evidence.
