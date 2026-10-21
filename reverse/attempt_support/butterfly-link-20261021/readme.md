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
