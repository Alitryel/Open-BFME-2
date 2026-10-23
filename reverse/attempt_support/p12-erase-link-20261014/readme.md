# Twelve-byte vector range-erase selection repair

Base checkout: 90129c098500168b94bb88b1ec44dcb73bd90be2 (full revision in object-proof.json). Local census
index: 147cfae2cb, 2026-10-14 07:27; its hash is recorded in the proof.
The committed repair queue at 67e1365aa9 is discovery evidence only. Neither
census/index nor committed link status is changed.

Four units emitted a non-retail vector<Gen_p12pod>::erase(first,last) that the
index selected ahead of existing verified copies: pathfinder.cpp,
Rva0029B1C2.cpp, LivingWorldLogicRva002B83E5.cpp and
LivingWorldLogicRva002B98AD.cpp. Add an explicit specialization declaration in
each unit so its existing calls use the verified provider. The row at
0x002A133B is 38 bytes and remains owned by Rva007D85C0FilterShutdown.cpp.
The other retail copies in AIStateMachineCtor.cpp,
ScreenHilightFilterShutdown.cpp and Rva0055A7DBTess.cpp are unchanged.

Target evidence is the existing verified erase row and exact compiled callers,
including their existing relocations to this same symbol. Gen_p12pod remains
the existing twelve-byte carrier; this repair adds no new identity or layout
claim. No algorithm, type layout, ABI, compiler setting, row, pin, alias,
marker, global, shared header or baseline is changed.

Reference linking review used verified BFME 1 gitlink
23b143233b5a8664a3bdf8572df6d905c310a5a1. Donor repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d removes non-retail local constructor
bodies in favor of existing providers. The same cause applies here; no donor
code is imported. Official master fetched as
a7c38d3b2597121f178ab5190b3062478823257d. Another worker holds the reference
file claim; its comparative verification and gitlink update remain pending.
The verified checkout was preserved and no freshness success was recorded.

Acceptance:

- Bounded link_check.py --prepare-current --paths-from cohort.txt before and
  after: 168/168 rows across eleven explicitly listed units, strict reusable
  receipts. The ordinary four-source build also passes 84/84 rows. After:
  103 literals plus three empty-string references, 57 float constants, ten
  imports, one data row and two full STLport constructor folds verified;
  zero baselined or skipped literal checks. The pathfinder funclet's local
  label renumber is verified against parent EH data.
- Object comparison removes seven COMDATs per edited unit (range erase and
  six helpers it alone emitted), adds none and retains 384 identical COMDAT
  bodies across the eleven units. Raw bytes, sizes and byte/relocation digests
  agree; COFF indices/sections are normalized for relocation comparison.
  External strong definitions and weak directives retain the same sets.
  Source/object/strict receipt hashes and complete findings are in
  object-proof.json; original objects and receipts are preserved under
  build/p12-erase-link-20261014, with the read-only comparison scripts.
- Same-index, same-cohort legacy local preview with historical strict baseline
  objects: total findings 50 -> 35, clean units 0 -> 7. The CLI after report
  shows 4,899 existing LINKED bytes: filter provider 143; AIStateMachineCtor
  3,800; PhysicsBehavior 134; ScreenHilightFilterShutdown 121;
  ScreenFilterRva007DCA80Shutdown 121; Rva000C18E3Chain 186;
  W3DShaderGaussianVector 394. Erase is no longer a COMDAT or selected-body
  finding anywhere in this cohort. Remaining findings in the four edited
  units are unchanged. Historical object witnesses are not presented as
  current source objects.
- EH: 9/9 EXACT, zero baseline or missing objects. check_csv,
  find_declared_unmatched, class gate, new-variants admission and whitespace
  checks pass. Affected-unit placement resweep: zero new bodies or pins.
- Enforced converged data check: eleven sources, eight protected addresses,
  zero second names and zero unjudged rows. Shadow data check has two existing
  pathfinder wrong-name findings at 0x009FF0E4 and 0x009FEFF0. Reading the
  historical baseline objects proves the same two findings before the edit;
  no data binding changes. Their exact keys are in the proof and data logs.

New authored C++ bytes: zero. Self-strict object currency is established for
this eleven-unit cohort. This is a legacy local selection improvement;
closed-strict dependency closure, actual link placement and a fresh census
were not measured. No census build/measure/history, full link cycle, nightly,
boot or publisher verification runner was started.

Remaining blockers: pathfinder has sixteen missing providers, two duplicate
helpers and sin/cos copies; Rva0029B1C2 lacks its formation-preview provider;
LivingWorldLogicRva002B83E5 has string teardown copies;
LivingWorldLogicRva002B98AD lacks rva002B29BD and has separate void-pointer
vector and TreeHintRef copies. These require independent repairs.

Preparation recovery (2026-10-14): upstream commit
8d49474a47d0b0bdd08ecff705507722efb90971 already implements the identical
four-consumer specialization repair and records its own acceptance evidence.
The replay retains upstream source verbatim, removes the redundant insertion
in LivingWorldLogicRva002B83E5, and preserves this independent historical
evidence and attempt verdict. This evidence-only replay claims no additional
linking improvement. Original objects remain in build/p12-erase-link-20261014;
the original commit and untracked-input stash remain in the preparation
backup refs.

Recovery acceptance at preparation upstream 4b00574221c81599a69834add41b3d1540f10d72:
- Rebase complete; no unmerged index entries. Stash apply --index succeeded.
  All 31 saved untracked files match their original stash blobs; the stash
  contains no staged or unstaged tracked edits. All backups remain intact.
- check_csv and whitespace checks pass. Four-consumer build: 84/84 rows.
  Bounded eleven-unit --prepare-current: 168/168 strict byte rows, current
  reusable receipts. EH: 9/9 EXACT. Converged data: eleven sources, eight
  addresses, zero second names or unjudged rows. Declared-function check passes.
- All eleven cohort sources are verbatim preparation-upstream source.
  Bounded local link_check (without a global --refresh): seven of eleven clean,
  4,899 existing bytes in legacy preview, exactly the same 35 independent
  findings and no Gen_p12pod range-erase finding. Its exit 1 reflects those
  preserved blockers, not an unresolved recovery conflict. No closure or
  placement gain is claimed. Fresh check logs remain under
  build/preparation-recovery-20261014. Census index SHA256: 690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
