# Bezier basis provider type, 2026-10-25

At BFME2 9f275d0298, published retail-truth-4 index ce1b975697,
Rva005C76C0Ctor.cpp references the D3DX9 `D3DXMATRIX` tag, while the only
provider Rva0055A0DDEvaluate.cpp and the verified 64-byte data row at
VA 00DD2398 use D3DX8 `_D3DXMATRIX`. The ABI layout is the same, but their
C++ data names differ. Include the provider's d3dx8math.h in the consumer.
No alias, global definition, pin, source flags or data-row change is needed.

Paired current-object legacy preview: consumer 0 -> 578 current authored
bytes; provider remains 360 -> 360. Rank's historical 579 is not credited.
Both units pass bounded strict reusable receipt preparation and normal byte
gates (3 consumer bodies, 1 provider body, and the 64-byte data row); this
is not a self-strict or closed-strict LINK measurement. New-variants and
frozen-definition checks pass. Cause sweep finds only this consumer of the
basis global. Prior donor provenance and target-vs-donor uncertainty remain
as recorded in each source and bezier-donor-tessellation-link-20261023.md.
