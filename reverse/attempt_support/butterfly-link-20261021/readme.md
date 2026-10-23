# Butterfly particle linking

The previous shader repair deferred this unit solely because frozen index
03035cf02c did not include it (../particle-shader-link-20261021/readme.md).
The runner-published index 2b4d1fb42a now includes it: current-object baseline
0/2153 real bytes, missing g_00DB6250 and DX8Wrapper::render_state_world plus
a non-retail Vector4(float,float,float,float) COMDAT.

Bind type-2 shader reads to BfmeParticleType2ShaderBits (complete matched
4-byte data row RVA009B6250), casting to the existing ShaderClass view, as
Streak/Lightning already do. Bind world-matrix reads to BFME2World (complete
matched64-byte cache RVA009EE7C4), retaining transpose/identity behavior.
Keep Vector4's existing inline float constructor and suppress its outline
copy with imported forceinline, as the proven particle/math siblings do.
No new globals, pins, layouts or donor identity assertions.

At 894111481c: ./build.sh passes4/4, two string refs, five float refs and zero
named imports, none skipped. Parent EH graph EXACT; the existing cleanup
label is renumbered and independently resolved by that graph. Strict provider
preparation repeats the gates with a reusable receipt. Declared definitions,
class gate, enforced converged data (10 addresses, zero second/unjudged) and
whitespace pass. Same-index current-object prediction LINKS0->2153B. This is
self-strict byte proof and a legacy preview, not closed-strict placement.

Sweep: no old shader name remains in Code C++ sources. Other indexed Vector4
float-ctor losers all have multiple independent blockers; no partial fixes
or additional gains claimed. Existing BFME1 emitter provenance is documented
in ../particle-shader-link-20261021/readme.md and this session's MetaImpact
record; no donor source imported or pointer advanced. No maintainer-only
runner or census build/measure/history was started.


Independent seat corroboration follows. Upstream a51b86bb29 already landed this source repair during publication; this rebased evidence commit claims zero additional linked bytes.

Butterfly particle link repair, 2026-10-21

The previous attempt deferred this unit because the published census did not
contain it. Index 2b4d1fb42a (2026-10-21 06:00) now measures it: three blockers,
0 -> 2,153 nonpadding matched bytes after this repair. This is a paired legacy
preview with self-strict consumer/provider receipts. Closed-strict closure and
executable placement are unmeasured.

Bind the four-byte type-2 shader view at native RVA 009B6250 to existing storage
owner BfmeParticleType2ShaderBits (StreakDrawModuleDoParticles.cpp). Bind the world
matrix cache at 009EE7C4 to existing 64-byte BFME2World storage
(Rva00785FD0RendererReset.cpp). Their complete data rows verify. No new storage,
pin, original shader name or class-layout fact is asserted. Target address/data
rows establish these relationships; the source's private views remain views.

Keep Vector4's component constructor operations visible as imported forceinline,
following the established BFME2 particle siblings and bfme_vp_math header. The
SSE external copy differs from retail's integer-move owner. It disappears with
no import reference or retained incoming relocation. Every retained nondebug
section, byte, flag, definition and symbolic relocation is identical after the
two known global rebindings. The unreferenced Get_Transform diagnostic remains.

Ordinary byte gate 4/4; strict consumer plus two providers 12/12, two data rows,
two strings plus two empty references, 17 float references, zero imports.
Full parent EH verification passes despite a compiler-local label renumbering.
Undeclared-definition and new-COMDAT-variant checks pass. proof.py reproduces the
paired check with the original object basename; index/status are unchanged.

Cause sweep finds no remaining old shader/world name in the particle family;
other Vector4 consumers have independent unresolved blockers. Prior donor review
at BFME1 68c5ce2789e9 and c1315665a1b22 is retained in
../quad-vector4-link-20261021/readme.md. Current verified donor pointer 5987fd1b
was reviewed for this session; target byte/data evidence decides the adaptation.
t=10 model=gpt-6.1-sol.
