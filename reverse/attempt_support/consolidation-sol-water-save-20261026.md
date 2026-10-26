# WaterTracks save-view prerequisite, 2026-10-26 (codexb)

Allocated family B shard 0/2; runner --check-tu authorizes W3DWaterTracks.cpp.
Current Water/ naming planner and in-memory --plan were reviewed, including
original-path alternatives, mixed Common owners and declaration prerequisites.
Destination and WWMath/Rva000FF50DSaveTracks.cpp file scopes were claimed.
No merge, split, class identity decision or TU-map write was applied.

The ordinary merge dry-run rejects saveTracks because its private track view
uses m_initTimeOffset/m_initStart/m_initEnd/m_type/m_nextSystem, whereas the
seed's existing matched initializer uses initOffset/initStart/initEnd/type/next.
Both independently access type +0x30, endpoint pairs +0x58/+0x60, initialization
offset +0x68 and next +0xB0. The donor now uses the seed's existing spellings
in declarations and accesses. No new method/global identity is asserted; the
Rva000FF50D receiver and its surviving findings remain unchanged.

## Acceptance

- ./build.sh on W3DWaterTracks.cpp, WaterTracksRenderSystemCtor.cpp,
  WaterTracksRenderSystemInit.cpp and Rva000FF50DSaveTracks.cpp passes before
  and after: 11/11 functions, one data row, one parent-bound funclet, four
  literals plus two empty references, 27 floats and three named imports.
- find_declared_unmatched.py passes the destination and edited donor;
  class_gate.py passes. No frozen or nonmatching body is introduced.
- data_check.py reports zero findings; --converged reports ten addresses,
  zero second names and zero unjudged rows. No data key is retired.
- Scoped code_identity_gate.check is identical before/after: eleven rows,
  58 findings, one existing outside-baseline Vector3 copy-provider finding
  in the unchanged header closure. No code-identity key is retired.
- Scoped ms_header_audit scan reproduces the existing conflicting queue row:
  five local Microsoft declarations, same=2/source=2/abi=1. Its register is
  retained; this repair does not claim those declarations fixed.
- link_check.py --new-variants --staged-peers --shadow passes. After the
  composer finishes, --prepare-current on the same four explicit sources
  passes with four strict reusable receipts and the ordinary byte gates.
  An earlier preparation correctly refused temporary Code inventory movement
  during the composer trial; no witness from that refusal is used.

Baseline objects and source/object SHA256 are indexed in
build/sol-water-save-before.json. The standalone provider comparison
(build/sol-water-save-proof.py) preserves all 76/4/2/6 external providers,
undefined references, raw code/data bytes, relocation referents, section flags
and census COMDAT selections. Local labels are compared by containing provider
and exact offset; only the already established anonymous BoundsValue filename
hashes are normalized during temporary composition.

Ordinary tu_skeleton.py --merge W3DWaterTracks.cpp --dry-run improves from
three files/ten rows to four files/eleven rows, newly accepting the existing
217-byte saveTracks donor. The accepted composed object
build/tu_skeleton/e4a606df7dad4916.obj has no missing, added or changed provider,
no baseline multi-variant name and no undefined-reference addition/removal.
Both parent EH graphs verify EXACT; native funclet locations are retained.
Reproduce with build/sol-water-composition-proof.py
build/sol-water-save-before.json build/sol-water-save-after-trial.txt.
Receipts: build/sol-water-save-{before,after}-{build,trial}.txt,
-proof.txt, -composition-proof.txt, -receipts.txt and -msheaders.txt.
This is a demonstrated prerequisite for Luna, not a confirmed downstream merge.

## Remaining work and publication audit

Five ordinary donors still fail: Common release/resource and find declarations,
WaterTracksObjRender's RealRange collision, shutdown/destructor declarations
and flush declarations. Three mixed files remain separate supported split or
owner work. Their prerequisites are not inferred fixed by the save repair.

The complete pending outgoing batch is eb0e311873's Line3D blocked evidence
plus this in-place donor edit and handoff. origin/master has unrelated newer
work; merge-base..HEAD distinguishes the outgoing paths from that incoming
side. There are no source/header moves, additions/deletions, new includes or
compiler flags. Tools, hooks, workflows, includes, build inputs and registries
require no path repointing. Historical EA paths, all surviving debt and ledger
owners remain intact. No protected register was changed.

Files reduced: zero. Identity/data keys retired: zero. Recovered C++ bytes:
zero. Linked/census improvement: unmeasured. Keep the destination, save donor
and this handoff file claims until publication is confirmed, then release.
