# Scoped inline emitter repairs

Five sources stop emitting competing, unused helper copies while retaining
their byte-exact retail callers. No shared header, ledger, pin or alias changes.

| Source basename | Removed local findings | Current local linked gain |
| --- | ---: | ---: |
| AptTimeLineStats.cpp | 3 | 4057 bytes |
| W3DViewSetCameraTransformBfme.cpp | 2 | 954 bytes |
| Rva003093F6BasesSamplers.cpp | 5 | 968 bytes |
| W3DModelDrawDoDrawModule.cpp | 1 | 0 |
| ParticleSystemDebugDisplayBody.cpp | 2 | 0 |

The three newly clean units total 5979 existing retail bytes. This is a bounded
same-index prediction, not a new census or link.exe measurement. The index is
de7bb30890, 2026-10-14 15:43; its SHA256 and independently checked old/current
object findings are in paired-vector-proof.json. No new authored bytes claimed.

The integer-vector units use existing imported-inline specializations to keep
allocator/proxy helpers inline. Timeline retains its throwing game allocator
and exact out-of-line allocator implementation; no exception policy changes.
The sampler's TU-scoped Vector4 view retains donor component assignments and
arithmetic. Its layout and return ABI are independently supported by the four
exact target bodies. Vector4 has no canonical registry entry; no exemption is
added. Every use inlines, with zero new undefined symbols or import references.

ModelDraw reads its existing +0x1C0 orientation member directly instead of
emitting an unused getter. Particle debug uses typed, local node comparisons
with the same donor semantics. Its remaining smart-pointer destruction blocker
and ModelDraw's three missing callees remain unresolved.

Donor reviewed: a7c38d3b2597121f178ab5190b3062478823257d. Relevant techniques:
564215e0 preserves allocator declarations; d003077f removes duplicate forwarding
copies; d3f9000f/d2e21369 suppress unnecessary inline copies. Their addresses or
layouts are not transplanted. Existing BFME 2 stlport_vector_int.cpp,
vector4scale-constructor-link-20261013 and rb-node-link-20261014 provide the
target-specific precedents. BFME 1 tree exception-flag repairs are inapplicable
where these consumers already disable exceptions.

Before/current COFF comparisons preserve every retained body and relocation.
Independent review also checks local-label destination sections/offsets, data,
EH, and undefined-symbol sets. The final campaign gate covers these five units,
two binding repairs and INI: 174/174 rows, 70 strings plus 7 empty references,
18 float literals and 50 named imports, with strict reusable receipts for all
eight sources. EH: 29 exact, one unchanged existing INI baseline discrepancy.
Converged-data enforcement: eight sources, zero second names or unjudged rows.
Shadow data retains only two pre-existing PlaceEventTranslator static-data
name findings; those unchanged bytes and referents are outside these five units.

All ten requested GPT-6.1-sol agents ran in this same checkout, with at most
five workers concurrent. Roles included donor selection and independent review.
The broader voice-class reconciliation and one iterator trial were not retained.
No full census, link cycle, boot runner, shared index or verification rule changed.
