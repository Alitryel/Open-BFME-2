# Vector3 consumer link repair, 2026-10-18

Measured against the published retail-truth-2 census at c2c5ac8c27
(2026-10-18 11:36), with current objects for the edited sources and the
matrix3d_inverse.cpp assignment provider. Current-source checks before editing
reported 0 linked bytes in each of the three consumers. After the repair:

| Unit | Before | After |
| --- | ---: | ---: |
| RTS3DSceneRva0007054F.cpp | 0 | 754 |
| W3DShrubBufferRva000E8365.cpp | 0 | 752 |
| layer.cpp | 0 | 199 |
| matrix3d_inverse.cpp, unchanged provider | 572 | 572 |

Net improvement: **1,705 legacy LINKED bytes**. The shrub ledger extent is
753 bytes, including a trailing INT3 excluded by the link-byte measurement.
This is a link_check preview, not a new census or closed-strict link result.

## Evidence and implementation

The scene's private Vector3 assignment keeps its component-store body but uses
the established dllimport/forceinline declaration pattern to avoid an external
non-retail copy. The owner remains matrix3d_inverse.cpp at RVA 0x00169FB0.
The scene mode-7 infantry override reads a single byte at VA 0x00DE1EB8:
retail instruction 0x0047072A is cmp byte ptr [0x00DE1EB8],0. The byte is within
virtual .data and beyond its raw data, hence loader-zero initialized. No
symbol, data row or converged-data owner covered it. The existing neutral
SceneModeOverride name now has one bool definition and a one-byte data row;
no original target identifier is inferred.

The shrub and layer consumers reuse the existing bfme_part_emt_inline and
bfme_vector3_ctor_link header views, respectively. Those headers retain the
float constructor's arithmetic while suppressing the competing external copy.
The shrub's local transform is the pinned donor Matrix3D::Transform_Vector
algorithm, retaining its alias branch and expression order but using Set(in)
for the temporary component copy. Set copies exactly X/Y/Z just as assignment
does. This avoids emitting the wrong external assignment copy. A trial that
removed the alias branch changed register allocation and was discarded.

## Acceptance

- Normal build.sh gates: seven matched bodies exact across three units.
- link_check --prepare-current: all three providers pass normal byte gates
  with strict reusable compilation receipts; one data row byte-verified.
  Compilation receipts do not establish a closed-strict link closure.
- Final link_check on all three consumers plus matrix3d_inverse.cpp: four of
  four link cleanly, 572 -> 2,277 bytes. Unreferenced helper-copy diagnostics
  remain non-blocking under retail-truth-2 and were not edited.
- check_csv, class_gate, find_declared_unmatched, data_check --enforce,
  data_check --converged and git diff --check pass for touched sources.
- No shared header edits, census rebuild, link cycle or protected baseline edits.

## Other attempts recorded with this batch

The attempt log records the GameSpy options unit and eight narrow-string
cleanup consumers. Declaration-only cleanup bindings replace retail inlined
frees with calls; importing the original inline template bodies still changes
cleanup/register scheduling. Those attempts were discarded, their restored
sources passed normal byte gates, and all their claims were released. The
shared narrow-string cleanup/codegen prerequisite remains unresolved; the log
records the native boundaries and the tested alternatives so later seats can
avoid unchanged retries. These attempts contribute no linked-byte credit.

## Preparation recovery

Upstream fe5d4a4cdc already binds the shrub and layer header inlines to their
existing owners (+951 B). Preserve both upstream units in full, including
the original Matrix3D transform call; do not reintroduce the private transform
or substitute shim includes. The original +1,705 B measurement above is
historical. The scene's 754-byte repair remains the independent contribution
of this patch relative to that upstream.
