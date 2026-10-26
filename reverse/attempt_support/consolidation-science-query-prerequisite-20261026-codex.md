# Science query prerequisite, 2026-10-26

Seat codex, allocated family A shard 0/2 destination:
`Code/GameEngine/Source/Common/RTS/Science.cpp`. Read the prior Common handoff;
its earlier 11-row merge is inherited work, not progress from this session.
The fresh Common/RTS planner gives Science.cpp placement hints and same-name
reference leads, with no stronger target-identity claim. The official current-map
trial approves these donors; the planner does not approve their merge.

## Repair and evidence

The baseline full dry-run accepts nothing. NameDescription fails because the
composed ScienceStore declaration precedes ScienceInfo, and the internal-name
query is absent from the seed's receiver declaration. A TU-scoped
`ScienceStoreQueryView.h` shares the existing query declarations among the seed,
NameDescription and getScienceFromInternalName consumers. ScienceInfo retains
string accesses at +0x14/+0x18 and the grantable byte at +0x30; opaque intervening
bytes do not assert a complete retail layout. The inverse query consumers also share the existing NameKeyGenerator method
declarations, preserving keyToName/nameToKey signatures and the same global
receiver type. No function body, symbol name, compiler flag, global or ledger
row changes. The first after-trial accepted the seed plus NameDescription (12 rows), then
exposed the seed's missing NameKeyGenerator::nameToKey declaration. That
compile diagnostic justified the final shared method union; the first result
is preserved in build/codex-science-first-after-dry-run.txt.
The purchase-cost donor remains
outside this repair because its canonical GameLogic adoption is separate.

`./build.sh` on the three sources passes 13/13 rows before and after, with
string, float and import checks clean. Frozen-file and class checks pass.
Saved before and freshly verified after objects have identical external
code/data definitions, undefined symbols, alternatenames and every non-debug
section's bytes, relocation targets, flags and COMDAT selection policy.
External code-definition counts are 42/1/2; non-debug sections are 47/2/3.
The upstream Identity/scan comparison retains all 24 reference facts, with
zero added or removed facts. The complete scoped allowed_symbols scan reports
22 owner references, one fold, one EH reference and zero wrong bindings.
Data checking reports zero findings, and
`link_check.py --new-variants --paths-from` the three-source list exits zero.
These scoped checks do not claim a new LINKED census result.

Local evidence: `build/codex-science-query-*`,
`build/codex-science-{before,after}-dry-run.txt`,
`build/codex-science-build-{before,after}.txt`, and the scoped identity/data/link
logs. Object proof uses upstream allowed_symbols object readers,
`_object_defs`, `_comdat_selections`, and link_check alternatename parsing;
reference proof uses Identity/scan backed by saved verified before objects.
No hand compilation or maintainer-only link cycle was used.

The final official dry-run exits zero and accepts Science.cpp,
ScienceStoreNameDescription.cpp and ScienceStore_getScienceFromInternalName.cpp
as one 13-row unit. Two existing donor rows (52 and 30 bytes) are newly
compatible. The intermediate 12-row result is superseded by this verified
13-row result, not represented as a separate recovery. No merge was applied.
Remaining prerequisites: purchase-cost fields plus canonical GameLogic adoption;
STL vector/template declaration conflicts; parser/Overridable receiver methods;
protected debt keys and mixed donors. StlSweepW4Rva001FF743 still differs in bytes.
Evidence: build/codex-science-final-dry-run.txt and the final build/object/reference,
identity/data/link logs (build/codex-science-*-final.txt).

## Registers and handoff

No source paths move and no merge is applied: file reduction, recovered C++
bytes and debt retirement are all zero. One declaration header is added.
No code/data identity or class-header keys exist for these three sources.
The existing two ms-header queue entries (Science.cpp and NameDescription)
remain owned at their current paths, including their NULL/include findings.
Protected donors, mixed rows, template providers and their debt keys remain
untouched. The compatible query donors are intended for Luna; dry-run acceptance
will establish an unblock, not a later confirmed Luna landing.

Luna must verify selected providers and bindings for the eventual composed TU;
identical objects here prove the declaration prerequisite preserves the existing
consumers, not that an unapplied merge has landed safely.

## Reproduction and batch audit

```
./build.sh Code/GameEngine/Source/Common/RTS/Science.cpp Code/GameEngine/Source/Common/RTS/ScienceStoreNameDescription.cpp Code/GameEngine/Source/Common/ScienceStore_getScienceFromInternalName.cpp
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/Common/RTS/Science.cpp Code/GameEngine/Source/Common/RTS/ScienceStoreNameDescription.cpp Code/GameEngine/Source/Common/ScienceStore_getScienceFromInternalName.cpp
python3 tools/allowed_symbols.py --source Code/GameEngine/Source/Common/RTS/Science.cpp Code/GameEngine/Source/Common/RTS/ScienceStoreNameDescription.cpp Code/GameEngine/Source/Common/ScienceStore_getScienceFromInternalName.cpp
python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/RTS/Science.cpp --dry-run
```

Audited the complete pending batch, commit 7455ffcee1 plus this prerequisite,
after fetching origin at 9e1ca7f93f. Incoming commits do not touch the repaired
consumers or current instructions. The two-dot range also contains reversed
incoming changes because the runner has deferred publication; those are not our
moves. Our outgoing changes introduce two scoped headers, with no source move.
Searched combined paths/basenames in active tools, hooks, workflows, Code,
build.sh, root/documentation configuration and 10,331 configuration/register
files. The six intended includes are the only new path consumers; existing
TU routing, link-status, naming provenance, pending-donor comments and the two
MS-header rows retain their current meaning. Historical references remain.
No active consumer or mutable register needs a path repoint, and no map or
debt baseline is regenerated. Evidence: build/codex-science-path-audit*.txt.

The four Science file claims remain held until publication is confirmed:

- file:Code/GameEngine/Source/Common/RTS/Science.cpp
- file:Code/GameEngine/Source/Common/RTS/ScienceStoreNameDescription.cpp
- file:Code/GameEngine/Source/Common/ScienceStore_getScienceFromInternalName.cpp
- file:Code/GameEngine/Source/Common/RTS/ScienceStoreQueryView.h

The four TunnelTracker file claims also remain held for pending 7455ffcee1,
as listed in its handoff. No RVA claims were created. If the runner retains
this batch, the next session must confirm publication before releasing the
eight scopes; no source work remains in those scopes after verification.

Session progress check `python3 tools/progress.py origin/master` exits zero:
BYTE-MATCHED 7,978,500 bytes (100%), LINKING 7,267,914 (96.74%), LINKED 7,518,133
(97.51%), all deltas zero. Linking figures are the 2026-10-25 21:36 census at
f995f30157, not trial predictions. Across both prerequisite repairs, three
existing donor rows totaling 179 retail bytes are newly compatible with their
TUs. Recovered/authored C++ growth, file reduction and debt retirement are zero;
two scoped headers are added. Neither subsequent Luna merge is confirmed here.

## Recovery receipt, 2026-10-26 01:36 UTC

Fresh session recovered this two-commit batch and pulled/rebased onto
`e5c5a1787c` without source conflicts. Pending repairs are now `c7dff2abdc`
(TunnelTracker) and this Science commit. The complete six-consumer build passes
19/19 rows; frozen-file checking passes. Repeated upstream object-reader proof
against the saved verified before objects retains every non-debug section,
relocation, COMDAT policy, code/data definition, undefined symbol and alias in
all six consumers. Recovery logs: build/codex-recovery-build-20261026.txt and
the refreshed codex-scoped-object-proof outputs.

Refreshed the outgoing-range audit against `origin/master=e5c5a1787c`: eleven
changed paths, no source moves or deleted donors. Combined active tool, hook,
workflow, include, configuration and register search finds only the same six
intended new includes, existing pending-donor provenance comments and the
unchanged NameDescription ms-header row. No further path consumer needs repair.
Evidence: build/codex-recovery-path-audit-20261026.txt. Existing debt ownership
and the prior dry-run scope remain unchanged. Publication retry accompanies
this amended handoff; keep all eight inherited file claims if the shared
publisher defers it, or release them after confirmed landing. This is recovery
verification, not a new prerequisite or recovered-byte claim.
