# 0x102F83 W3DCamTransform::rva00102F83, round r66 (2026-10-22)

Bank: `reverse/attempts/0x00102f83.cpp` = scratch `b6`, fitness **0.95707**
(4303 B vs 4299, 57 relocations, 77 changed instructions in 8 regions).
It is the earlier codex seat's combined candidate (0.9479) plus one change:
the translation helper reads the descriptor itself,
`translated(Vector3 p, const CameraTransformInput *v) {p.X+=v->pos.x;p.Y+=v->pos.y;return p;}`,
which addresses `pos.y` as `[ebx+0x50]` like retail. The bank still relies on
compensating helpers (see "Faithful base" below); it is the score-best, not the
source-faithful body.

`causal/` holds the codex seat's 2026-10-21 trace write-ups (FactCanonSort keys,
symbol pools, glob costs, SubsumePseudos). Read `causal/current-progress.md` and
`causal/rotate_y_order.md` first.

## Faithful base (`faithful-kf.cpp.txt`, 0.88426, hack-free)

Built by reading the WB twin 0x7E3040 and matching its /Od structure. Compiled
`/Od /Ob1` (x87) our body aligns with WB at 0.979 after register/offset
normalisation; the remaining WB-only lines are debug sentinels and assert
conditions. All 272 WB stack locals map 1:1 onto ours. WB-proven shapes the bank
replaces with helpers:

- translation: direct `sourcePos.X+=v->pos.x; ... targetPos.Y+=v->pos.y;`
  (live arm: sX,sY,sZ then tX,tY, tZ += pos.z+targetZAdjustment);
- constraint: four `v->pos.x=maxf(v->minX,v->pos.x);` style statements;
- live test: `!live || (live && obj && !obj->getTemplate()->isKindOf(12))` ->
  ground arm, else live arm;
- realZoom pitch: direct `(s-t)/fxPitch+t` statements;
- live height `tanf(v->fxPitch)*distance` (one-formal wrapper, return temp);
- hold `targetPos += delta`; distance `v->distance = delta.Length()`;
- `mulVector3(Vector3&)` donor one-arg forwarder to the WWINLINE two-arg form
  (WB calls it out of line: sub_7e7310, 4 sites);
- matrices: donor `Matrix3D(axis,angle)` -> `Set(axis,angle)` -> `Set(axis,s,c)`;
- empty member hook `if(v->liveCamera) hook(&sourcePos,v)` before
  transitionLiveMode (WB sub_7e8450, 13 B, auto-inlined in retail);
- slaved: `Matrix3D tm;`, `Get_Translation()`, struct copy to previousPos;
- final: plain `v->transform->Rotate_Y(v->finalRotation)`; near adjust uses a
  named local 90.0f.

## Rotation mechanism (solved structurally)

FactCanonSort key of a named symbol = `0x10000 | ROL16(ID,5)`; a MUL node hash
is `0x1030000 + ((k_first + 2*k_second + 0x30) & 0xFFFF)`; ADD sorts products
by descending hash. Named locals come from 32-record pools (LIFO free list,
`@SymFree@4` mapped at 3077 RVA 0x5a8b6). Only *kept* records advance the fresh
counter; transient (freed) ones do not.

- Shaker Rotate_X needs `tmp1` on the last slot of a pool (A).
- Final Rotate_Y needs c on a pool end with tmp1 in a pool >= 2048 (B), and
  `F_s + 2(T-2048) mod 2048` outside {2045,2046,2047} (16-bit hash wrap).

`cond.py.txt`/`pools.py.txt` check A/B from a `@SymAlloc/@SymFree` trace in ~7 s.
Diagnostic padding (never landable) proved both: +1 kept record before the
shaker and +3 between shaker and final solve those regions.

Natural source that satisfies A and B on the faithful base: donor WWINLINE
(`__forceinline`) markings on Vector3 ctor/copy/operator=/Set/operator[],
Vector4 ctor/operator[], Matrix3D ctor, plus the ZH kind-of chain
`isKindOf -> TEST_KINDOFMASK -> BitFlags::test -> bitset::test` (reduced
inline structs; the real STLport `<bitset>` include drops to 0.835). With it
the shaker region is gone; the final still differs (26 insns) because
F_s=1854, T=2144 hit the hash-wrap window.

## Open: the X/Y register wall (~180 insns, cost-driven, not ID-driven)

Retail keeps sourcePos/targetPos X/Y in memory; the faithful base gives them
registers. Spillcosts (copied tracer `costs_trace.py`): faithful sX 20 refs
+19, tX 14 refs +10; bank sX/tX -7/-6. Per statement each translation adds +6
(load temp coalesced into the component), realZoom lerp +8 to sX.
Ruled out on the faithful base: end-of-function padding up to 48 (component
IDs), interior padding, transitionLiveMode/hook definition order,
transitionLiveMode invisible, escaping X/Y via an extern at the end, kind-of
layer variants, real STLport bitset.

t=600 model=claude-opus-5-5
