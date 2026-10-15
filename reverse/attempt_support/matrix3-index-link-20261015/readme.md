# Matrix3 indexing emission link repair

Seat model: `gpt-6.1-sol`; elapsed repair effort approximately 16 minutes.

Base BFME2: `260b6195f3` (full SHA in proof.json). Frozen local index:
`ac77c85054`, 2026-10-15 14:25; its SHA256 is in index-meta.json.
Committed link_status.csv is discovery evidence, not a new measurement.

RenderObjectDrawModuleDoParticles.cpp and texproject.cpp now select the existing
bfme_matrix3_owner_link/matrix3.h at their original Matrix3 include positions.
Compared with the verified BFME1 header, this view changes only provenance
comments and the two indexing helpers' dllimport/forceinline declarations.
The layout and Row[i] expressions remain identical. No shared header, pin,
alias, row, optimization setting, import reference or allowance is added.

The removed const indexing copies are 12 bytes, digest 748fa195f6c9. The
indexed first definition in matrix3d.cpp has digest 961e263a2091. This helper
has no retail address: the finding uses the upstream first-copy rule, not a
claim that the selected helper has independently established retail identity.
The complete matched particle body remains 1820 bytes at 0x00562DDB; the
existing ledger's boundary, virtual-slot evidence and provenance are unchanged.

## Paired proof

All three sources have strict reusable receipts before and after. The witness
matrix3d.cpp object is byte-for-byte unchanged. Each edited object removes only
the unused const indexing section. Every retained nondebug section's bytes,
flags, external definitions and symbolic relocations is identical, including
local target sections. No retained relocation points at the removed helper;
strong, undefined and weak-name sets are unchanged. Retained COMDATs:
particle 20, texture projection 119, witness 16.

proof.py refreshes the same three positions into separate in-memory copies of
the frozen index. The particle unit loses its only finding and becomes LINKS:
0 -> 1816 existing nonpadding bytes. The witness remains LINKS at 286 bytes.
Texture projection loses one finding, 19 -> 18, without changing any other
finding. Combined local legacy prediction: 1/3 -> 2/3 clean, 286 -> 2102 bytes.
The ordinary three-source link_check confirms this and exits 1 because texture
projection retains unrelated blockers. There is no new authored C++ coverage,
closed-strict placement claim or full-link measurement.

The index contains eight copies of this helper: these are its only two losing
copies, so the supported family is drained. Other copies already agree with
the selected witness. Texture projection still has 11 unresolved Projector,
MatrixMapper and WW3D methods, five COMDAT losers and two selected-provider
findings. Those are separate dependencies, preserved in proof.json.

## Acceptance and reproduction

- Bounded --prepare-current: 12/12 rows before and after, strict receipts.
- Explicit ./build.sh on both edited units: 3/3 rows, two compiler floats.
- EH: no applicable rows, no missing objects or baseline entries.
- Enforced data: zero findings. Converged data: eight addresses, no second
  names and no unjudged rows. Class gate, declared-definition check,
  no-new-variants, CSV and whitespace checks pass.
- Both affected placement rescans: zero bodies and zero pins.

acceptance.txt records commands' outputs. proof.py uses ignored snapshots in
build/matrix3-index-link-20261015/before with the original object basenames,
the saved source backups, source list and index metadata. It compares the
complete objects and exact finding sets; it never writes the index or census.
An initial texture-projection trial moved the include before rendobj.h and
changed unrowed emitted helpers, despite passing its matched-row gates. That
trial was discarded; final selection preserves the original include position
and all retained sections. All three file scopes were claimed before editing.

## Reference review

Verified BFME1 checkout/gitlink: a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed donor repair 66b19a8e95a4add525ef808fcea088e306798e2b: suppress an
incidental external inline copy while preserving the native enclosing body.
That principle and the existing BFME2 Matrix3 view apply here; no donor code,
layout, address or recovered identity is imported. The header comparison and
whole-object verification establish applicability to these target units.

Official BFME1 master was fetched at 95eeb3bef370a7cd730b0ad5f228c317c8756e72.
The overdue reference update remains foreign-claimed, with comparative old/new
verification previously incomplete. Verified inputs and the stale success stamp
are retained. No unchanged multi-hour verification retry or maintainer-only
census, link cycle, nightly, boot or publication runner was started.
