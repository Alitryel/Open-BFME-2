# Mechanical consolidation batch audit

Date: 2026-10-26
Upstream base: `377ffd172491b071702f9fbec0dd42c0a7c1d7e3`

Four allocated, approved destinations were merged in separate verified
commits: `SwayClientUpdate.cpp`, `ExperienceScalarUpgrade.cpp`,
`LocomotorSetUpgrade.cpp`, and `W3DDefaultDraw.cpp`. The 14 moved rows remain
matched. Net tracked source-file count fell by four. Each destination passed
`./build.sh <TU>` and `python3 tools/find_declared_unmatched.py <TU>`.

For the full outgoing range, `link_check.py --update-index` refreshed the index
to the base above; `link_check.py --prepare-current` produced strict receipts
for all four destination objects and verified 14/14 matched rows. The
`link_batch_audit.py` comparison reported no selected-provider change and no
changed-unit unresolved blocker. The exact combined search for absorbed paths
across `tools/`, hooks, workflows, `Code/`, `docs/`, and `reverse/` found only
the expected retained source comments in merged translation units. Historical
name-basis, link-status and consolidation evidence was left intact.

The merge tools carried existing data-identity and hatch keys. Experience
Scalar still has the shadow identity finding and two shadow data-name findings
recorded in its destination register; no identity or data debt is claimed
retired. Header queues were refreshed during the pass; outstanding header and
identity work remains with Sol. No `tu_map.csv` regeneration was committed.

Other allocated dry runs were left unchanged when mechanical verification
found prerequisites: Matrix4's approved destination directory is absent;
DeletionUpdate and RadarUpgrade have class/header declaration errors; and
GiantBirdAIUpdate has the compile errors listed in its blocker note. See the
per-destination notes for exact diagnostics. No path-consumer change requiring
manual repair was found in this batch.
