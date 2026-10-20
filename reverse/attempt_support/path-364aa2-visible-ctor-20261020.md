# Path::rva00364AA2 (0x00364AA2, 2029 B): visible LineSeg ctor bank, 2026-10-20

Bank `reverse/attempts/0x00364aa2.cpp` replaces the 0.85 bank (`path-364aa2-20261020.md` describes it and what it ruled out). Toolchain and flags are unchanged (the bank's `// cl:` line, /O1 /G7 /arch:SSE, WWMath/WWLib from the BFME 1 reference). Model: claude-opus-5-5.

## Result

Measured with `tools/align_diff.py` on fresh objects:

| Source | Size | Structural regions | Memory | Register | Frame |
|---|---:|---:|---:|---:|---:|
| previous bank (0.85) | 2029/2029 | 6 | 114 | 33 | 0x14c |
| this bank | 2029/2029 | 2 | 30 | 7 | 0x138 (retail 0x138) |

Every stack slot now matches retail. Of the 30 memory lines, 9 are DIR32 constant addresses the gate fills; the other 21 and all 7 register lines lie in the two constant-angle `Rotate_Z(-PI/2)` sites (retail +0x2be..+0x38a), which are the only remaining mismatch.

## The two source changes

1. The two-Vector3 `LineSegClass` constructor is defined in the unit as `inline __declspec(noinline)` with the header body (`P0(p0), P1(p1) { recalculate(); }`, `recalculate` declared protected and out of line). Its emitted copy byte-matches retail 0x000927F9 (align_diff: 0 regions, 0 memory, 0 register, 1 reloc). With the body visible, cl 7.1 sees that the constructor does not leak its arguments, so the named endpoints p0/p1 and the argument temporaries are packed by liveness: p0 shares +0x38 with n2 and q, p1 shares +0x1c with a, and the seg-construction temporaries take retail's homes. This alone moved 6/114/33 to 2/43/21 and the frame to 0x134. Making `LineSegClass::Set` visible as well is inert (byte-identical), so the bank leaves it declared only.
2. `float fraction;` is declared at function scope beside `center`/`other` instead of in the tail block. Inside the tail block it was packed into p1/a's home (+0x24); at function scope it gets its own slot at +0xc as in retail, which shifts every lower slot by 4 and gives the 0x138 frame. Declaring it at function top is equivalent.

Link note for a future landing: the constructor's home `Code/Libraries/Source/WWVegas/WWMath/LineSegVectorCtor.cpp` already defines it `inline` (select-any), so the visible copy does not collide. The bank still carries the earlier visible copies (`rva002655E3` for appendNode, the PathNode ctor and `rva00363B4BAngle`), whose names and linkage need the same review before landing.

## Remaining mismatch: constant-site Rotate_Z colouring

Retail colours both inlined `Vector3::Rotate_Z(-PI/2)` expansions tmp_x=xmm0, tmp_y=xmm1, cos=xmm2; ours gives xmm2/xmm0/xmm1. The instruction order after scheduling is the same at the first site, so the difference is the allocation order (first-free over retail's pre-schedule order gives retail's registers; ours behaves as if y and cos are loaded before x). At the second site the colouring also lets retail delay the X' `subss` to +0x385 and store Y' first, interleaved with the p0/p1 sums; ours computes X' at +0x34d. That is the one structural pair.

Ruled out this round (each measured on the full body, all identical to the bank unless noted):

- Explicit `Rotate_Z(sinf(a), cosf(a))` calls (struct 4) and named s/c locals per site (2027 B, struct 8).
- A file-local copy of Rotate_Z with tmp_y declared before tmp_x, with operands swapped in either product, with Y's terms swapped, with X written as `-s*y + c*x`, with plain `inline` on the inner helper: all byte-identical; plain `inline` on both levels stops the inlining (1889 B). `(float)sin((double)a)` instead of sinf: struct 11.
- `Vector3 v1(radius * Dir)` direct-init, `Dir * radius` operand order: identical. Explicit `radius * Dir.X` components: memory 32. Declaring v1/v2 first and assigning: frame 0x150, struct 6.
- WB-faithful clamp locals (`len2`, `maxRadius` from WB local_fc/local_130) and the WB dead `Vector2` set from prevPos (local_60): identical.
- /O1 without /G7: identical. /Os: 1867 B.
- Removing the whole tail (diagnostic): site 1 colouring unchanged, so the cause is not in the tail.
- A minimal unit with only `v = radius * d; v.Rotate_Z(-PI/2)` twice and non-escaping v gives our colouring; with v escaping to an external call x takes xmm0 but y is then folded from memory twice, which retail does not do. WB shows no address of v1/v2 (local_108/local_12c) ever taken.

## Lead: the angle helper's visibility decides the colouring

Replacing the visible `rva00363B4BAngle` copy with a plain declaration (bank otherwise unchanged) gives **0 structural regions**: both Rotate_Z sites colour x/y/cos = xmm0/1/2 and the X' `subss` lands at +0x385 as in retail, frame still 0x138. But n1/n2 then escape and pack lexically, and the high stack zone is permuted: memory 194, register 19 (all instruction mnemonics align). By the bank rule that is not closer than 2/30/7, so it is not banked; the change replaces the helper's definition with the declaration `float rva00363B4BAngle(const Rva00363B4BVector *a, const Rva00363B4BVector *b);`.

Retail's grouping (12-byte slots from the top): +0x5c {nextPos, v1}, +0x50 {seg temp p0, n1, pt, d}, +0x44 {prevPos, v2}, +0x38 {seg temp p1, p0, n2, q}, +0x34 this, +0x28 curPos, +0x1c {p1, a}. With the helper declared only, ours is +0x5c {prevPos, seg temp p0, n2, pt, d}, +0x50 {nextPos, v2}, +0x44 {v1}, +0x40 this, +0x34 {seg temp p1, p0}, +0x28 {p1, a, n1}, +0x1c curPos. With the helper visible, the grouping is retail's exactly.

Measured on top of the declared-only helper, none of which restores the grouping: n1/n2 without a block (frame 0x150, 0/158/25), fraction back in the tail block (frame 0x134), center/other/fraction in the tail block (frame 0x130), one block for normals and tail (frame 0x144), n2 declared first, n-block before center/other, Vector2 a..d or center/other at function top (all identical to 0/194/19), LineSeg ctor not visible (frame 0x150, struct 4), Set visible as well (identical), n1 and n2 in nested blocks in either order (identical), appendNode declared only (struct 10: the curPos.z store no longer hoists, so appendNode stays visible). With the helper defined, a plain or `__declspec(noinline)` definition is identical to the bank and a `static` one gives 2025 B, struct 9.

Splitting the two helper calls between the visible copy and a declared-only twin (diagnostic only) shows the cause: with only the first call (seg1/seg2 directions) declared-only the body equals the bank, with only the second call (n1/n2) declared-only it equals the 0/194/19 result. So the colouring follows whether n1/n2 escape, and retail's colouring says they do.

Next: find the shape that, with n1/n2 escaping to the out-of-line 0x00363B4B, reproduces retail's grouping above. Declaration order and block nesting of the normals were inert, so vary what else changes when n1/n2 escape. Note that 0x00363B4B sits inside the Path cluster (between 0x00363B24 and 0x003641AE), so retail may define it in the same unit; a definition before the caller would make it visible, which these measurements contradict unless something else makes n1/n2 escape in retail.

Scratch trials and logs: `build/w1_364aa2/` (t1..t33, u1..u19, d1/d2, min1/min2 minimal units).
