ScreenMapper helper ownership repair, 2026-10-21

BFME2 base 5b28dde673; retained BFME1 a80da2e3be84ebdb3b6bc280faca3f99a44788af.
The current published index measures d08db10acb, 2026-10-21 18:42.
The normal current-object preview before this change reported 0/821 authored
nonpadding bytes and four blockers: the array constructor iterator, Matrix4
rows constructor, Matrix4::Transpose, and wrong-selected WWMath::Floor.
The paired preview after this change reports LINKS 821/821. This is a legacy
preview gain of 821 B, not a census, link.exe placement, or closed-strict gain.
No new unique C++ bytes are claimed.

Combine three existing, independently supported repairs in this caller:
- The quat_BuildMatrix4 unemitted /O1 iterator anchor emits retail's 34-byte
  iterator, without changing the parent (the prior 20261021 survey proved
  this unit byte-safe but left its other blockers unresolved).
- Include the existing BFME1 rows-link Matrix4 view before mapper.h, after
  the existing Vector4 view. It preserves visible matrix operations and
  binds outlined bodies to the independently rowed native owners 6A34E and
  6A3D1. No new shared header or layout is introduced.
- Use the identical file-static floorf wrapper from the color-picker repair
  instead of emitting another public WWMath::Floor body. The vendor definition
  itself is return floorf(val), and every parent byte/import still verifies.

The complete 823-byte parent passes its byte gate, one float literal and two
named imports. Strict reusable current receipt preparation also passes; that
is self verification, not closed-strict link closure. Declared-definition and
converged-data checks pass, and shadow data has zero findings. The remaining
unreferenced Get_Transform copy is diagnostic only under retail-truth-2.
Existing target identity and layout evidence and donor uncertainty are retained.

Related leads were read before editing: grid-math-link-20261020-batch2,
color-picker-floor-link-20261019 and the iterator survey at re_attempts.log.
GridWSEnv has already been rehomed and repaired in mapper.cpp. SortingRenderer
and MeshClassRenderWithFXMaterial retain recorded parent-byte failures with
this iterator anchor. MeshGeometry has independent collision-helper providers;
htree/HLod have separate class/vector/weight helpers. No speculative edits to
those units are retained. The global --refresh was interrupted during stale
input discovery; the explicit current object was already rebuilt by build.sh,
and both paired previews use the same published index. No census runner ran.

A simplification trial removing the iterator anchor fails the parent byte gate:
Transpose again outlines the array iterator and changes parent scheduling and
frame. The verified anchor is therefore necessary; the exact version was
restored and reverified before commit.

Restoring and rebuilding the original source reproduces the four before
blockers and three identity-shadow findings (Matrix4 assignment, subscript
and Init). Rebuilding the final source reduces these to the two existing
assignment/subscript findings; no identity finding is introduced.
