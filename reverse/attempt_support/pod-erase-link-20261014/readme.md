# POD vector erase provider repair

At BFME 2 base `9d1861bd0f`, four units emitted a 41-byte non-retail copy of
`_STL::vector<Gen_p12pod>::erase`. Declaration-only explicit specializations
now select the existing byte-verified 38-byte owner at `0x002A133B` in
`Code/GameEngine/Source/Common/Rva007D85C0FilterShutdown.cpp`.
No function identities, layouts, ABI, ledger rows, pins or compiler flags change.
This is a link repair with zero added authored C++ retail bytes.

## Target evidence and acceptance

- `cohort.txt` identifies all eleven checked units: four edited callers, the
  unchanged owner and six unchanged affected consumers.
- Strict `./build.sh` preparation passed all 168 matched rows (`prepare-after.txt`).
  All eleven strict verification receipts are current.
- Object comparison (`object-proof.json`) finds four wrong erase copies and
  24 now-unused helper copies removed, no new COMDATs, unchanged retained
  code/data bytes and relocation targets. SafeSEH symbol-table indices and order
  are normalized to the same handler names, bodies and offsets. The owner and
  six witness objects are byte-identical to their before objects.
- Six matched retail caller edges independently target `0x002A133B`.
  These target edges and the owner's exact bytes establish provider selection;
  no donor layout or function name is promoted to a new target claim.
- EH verification: nine EXACT graphs, zero nonexact/baseline/missing (`eh.txt`).
- Converged-data check: eleven sources, eight addresses, zero second names or
  unjudged names (`converged.txt`). Class gate, declared-function gate and
  `git diff --check` pass. `place_bodies.py` on the four changed units finds no
  additional bodies or pins.

## Local link result and limits

Commands: `python3 tools/link_check.py --refresh --paths-from COHORT` before
and after, using the runner's index measured at `147cfae2cb`,
2026-10-14 07:27. Index SHA256:
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
Strictly verified current objects replace the cohort's indexed objects.

The legacy-index preview improves from zero to seven clean units, and from
zero to 4,899 linked existing bytes. Fifteen findings disappear with none added
(`finding-delta.json`; before/after logs). The four edited units retain unrelated
blockers: pathfinder unresolved/duplicate/trigonometric definitions, formation
preview's missing provider, and LivingWorld string/vector/tree-hint COMDATs.
Their complete remaining findings are in `cohort-after.txt`.

`python3 tools/link_check.py --refresh --current-ledger --paths-from COHORT`
refuses before a closure judgment because 365 current-ledger objects are missing
(`closed-after.txt`). This is not a closed-strict gain or a measured placement
result. No full census, link cycle, nightly or boot runner was started.

## Reference review and handoff

Reviewed BFME 1 donor repair `d003077f0b7ce97622adb7a53f1fe76653433c5c`:
its declaration-only provider reconciliation is applicable in principle, with
BFME 2 provider and call edges independently verified above. Also reviewed
`de59a7e9f` (isUndefined COMDAT reconciliation) and
`5f05cce4e52a5f69608af60cc2bfa2a8e78d9187` (StringBase reconciliation);
no donor source imported and no unrelated repair attempted in this batch.

The reference checkout and committed pointer remain at
`23b143233b5a8664a3bdf8572df6d905c310a5a1`. Freshness fetch found upstream
`a7c38d3b2597121f178ab5190b3062478823257d`, but another seat holds
`file:reference/open-bfme-1` (`yasinschroeder-claude2`); the verified pointer and
freshness stamp were left intact. That seat must finish the pointer update and
its required full byte comparison. The next runner census can measure this
repair's closure and placement; the local preview alone does not establish them.
