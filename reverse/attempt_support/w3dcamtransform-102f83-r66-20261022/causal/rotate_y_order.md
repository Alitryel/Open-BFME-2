# Shaker versus final Rotate_Y canonical keys

Read-only FactCanonSort traces of existing value_reference and full donor math
header candidates. Both traced target bodies and relocation lists are identical
to their ordinary objects:4286B and4261B respectively. No source variant was
created in this investigation. The final-only two-argument overload remains
deferred: the current trace does not predict that it alone changes operand order.

The C2 stage is FactCanonSort at RVA0x5CC68. Source-relative line111 is shaker
Rotate_Y; line136 is finalRotation. The exact target name is filtered so the
local AnimatedTransform constructor cannot contaminate results. Full before/after
nodes, source symbol IDs and decoded names are in *.canon.json; selected products
are in product-comparison.json.

| Context | s ID/key | c ID/key | oldX ID/key | oldZ ID/key |
|---|---|---|---|---|
| Reduced, shaker |1892/1EC80|1893/1ECA0|1894/1ECC0|1895/1ECE0|
| Reduced, final |1909/1EEA0|1910/1EEC0|1911/1EEE0|1912/1EF00|
| Full donor, shaker |1967/1F5E0|1968/1F600|1969/1F620|1970/1F640|
| Full donor, final |2247/118E1|2251/11961|2252/11981|2253/119A1|
| Donor row assignment, shaker |1833/1E520|1834/1E540|1835/1E560|1836/1E580|
| Donor row assignment, final |1855/1E7E0|2176/11001|2177/11021|2178/11041|

In the reduced and full-header contexts, each MUL sorts the old coordinate before the trig
value. This gives the already matching shaker sequence, but the retail final
sequence instead keeps c/s as the first multiplicands. Whole-function normalized
diff identifies final Rotate_Y at+F67..1015; nearAdjust starts+1030 and already
matches.

The exact named-variable key is0x10000|ROL16(Fold16(F),5), where Fold16 XORs the
high and low16 bits of F. C2 RVA5DF41..5DF72 reads the ID at symbol+1C, performs
that XOR, then rotates the16-bit result left5. RVA5D3A8..5D3BB masks the low16
and adds the leaf-class high bit. Thus for these IDs below65536 the low bit after
F2048 is the rotated-out bit, not a type flag. The principal key wraps at F2048.
A real inline context
that put reduced-view final s/c at2046/2047 and oldX/Z at2048/2049 would give
1FFC0/1FFE0 versus10000/10020, reversing the product operand preference while
leaving the earlier shaker context below the boundary. This is a numeric
hypothesis, not proof of retail symbol IDs or permission for filler locals.

The full donor comparison shows real context matters: shaker IDs rise75, but
final IDs rise338..341. It passes entirely beyond the useful wrap, so old fields
still rank above c/s. The additional growth between the two calls lies across
real matrix-copy/listener source, motivating the parent's targeted donor
Matrix3D::operator= / Vector4::operator= restoration. That probe belongs to the
parent; no duplicate source probe or production edits were performed here.

The parent then restored actual donor row assignment and Vector4 assignment.
Its traced body and relocation list equal the ordinary4306B object. This context
straddles a symbol-allocation pool: final sine1855 (last slot of a32-symbol pool)
keeps the high key, while cosine2176 starts another pool. Consequently both sine
products sort trig first, while cosine products still sort old-coordinate first.
The final region improves32 to30 normalized changed instructions. This is not a
uniform symbol-number shift. All four final scalars have identical kind/type,
self origin, and consecutive local ordinals229,230,231,232. C2 SymAllocPool
RVA603DB allocates32 records of96bytes and preassigns their IDs at offset1C.
The completed pool trace (`pool-proof.json`, full `row_assignment-pools.json`)
shows that IDs1856..2175 belong to ten32-record temporary-register pools. Every
allocation there is kind3; the pools are replenished from RVA60869. They are
unnamed register temporaries, not late scalar pieces or canonical hash variables.
The local pool is replenished from RVA3B30F. Both trigs and the two row values are
ordinary kind4 locals mapped by the same source-symbol path at return RVA6F08C.

Immediately before the final call, the named-local free list supplies `this`
ID1845 and `theta`1854. Sine takes the last unused record1855; cosine requests the
next local pool and receives2176, then the old coordinates2177/2178. There is no
different type or ancestry explaining cosine. The current three source lines
simply cross the pool boundary. Consecutive local ordinals229..232 were assigned
later and are independent of the pool IDs used by FactCanonSort.

This supports one bounded source hypothesis: the actual donor two-argument
Rotate_Y overload removes the theta formal and could move both trigs before
the boundary, leaving the old coordinates after it. This is a prediction about
local pool demand, subject to actual lowering of caller argument expressions.
