# Bezier basis consumer type repair

BFME2 b7baa1eca9, published census ce1b975697 (2026-10-25 03:51,
retail-truth-4). Rva005C76C0Ctor used DX9's struct D3DXMATRIX while the
existing, data-rowed definition in Rva0055A0DDEvaluate used DX8's
_D3DXMATRIX. The different COFF names left the consumer unresolved.
Use the provider's existing d3dx8math.h include and its 64-byte matrix type.
There is still one global definition, at the already proven VA DD2398.
The three consumer rows and the provider's code/data pass normal gates;
no source arithmetic, data initialization, row, pin or alias changes.

Paired refreshed legacy link_check over the same consumer/provider set:
360 -> 938 B, **+578 B linked** (consumer's unique attributed bytes).
The consumer's three row extents sum to 579 B; the checker attributes 578 B.
The provider stays at 360 B. This is scoped legacy availability, not a
self-strict, closed-strict, or new whole-image census measurement. Logs
retain both results and the normal code/data/literal/import checks.
Frozen-definition and whitespace checks pass.

Reference review: clean committed BFME1 0bf534ea7, within the existing
2026-10-23 freshness window. Its BezierSegmentEvaluation source also uses
_D3DXMATRIX; original donor identity and layout qualifications in the target
sources are retained. Its latest reverb/import repair does not apply here.
The target global's existing data row and matched DIR32 references establish
the basis relationship independently; no donor address is imported.
