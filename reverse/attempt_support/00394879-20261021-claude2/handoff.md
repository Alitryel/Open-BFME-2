# 0x394879 BuildAssistant::isLocationClearOfObjects - 2026-10-21 02:24-03:20 UTC (yasinschroeder-claude2, claude-opus-5-5)

Bank = reverse/attempts/0x00394879.cpp, fit 0.88748 (previous bank 0.8824). The whole TU, built at
Code/GameEngine/Source/Common/System. It starts from the earlier bank plus the in-TU noinline
Coord2D::length / Coord3D::GetLength copies. The one change that raised the score: `Coord3D pt; pt.x=pt.y=pt.z=0.0f;`
(chained zero) replaces three separate stores.

Remaining residue, frame 0x12c vs retail 0x11c:
- (a) Retail puts one 12-byte slot (top -0xc) above the four bools, shared by `this` (entry spill), Coord2D dir,
  Coord3D pt and the Rva00261353Filter temp. Ours has bools at -d/-e, then this -14, dir -18, pt -1c, and the
  filter temp in its own 12-byte slot (this is the +16 frame).
- Finding: the filter temp never shares a slot that holds `this`. Probes that kept `this` live later, or moved
  it out of that slot (w8, x5, x6), let the filter join pt's slot, but `this` then lands elsewhere and the
  score drops. dir and the filter are compatible. The open question is how retail makes `this` and the filter
  compatible: its `this` spill dies before the door tail.
- (b) Length2 load order: ours is z*z+y*y+x*x, retail x*x+y*y+z*z.
- (c) Transform_Vector output scheduling and center-store order.
- (d) builderObject register: retail edx, ours eax, in the dozer QuickDoesPathExist block.

Disproven this session (do not repeat):
- Exit-branch forms
  - s4/s5 grow the body past 1838 (REL32 at 1836 needs 1840).
  - WB-faithful dir-first forms all 0.850-0.862: wb1 (Vector3 dir from m_offset fields, pt=dir fields), wb2 (const ref off), wb3 (pt=*(Coord3D*)&dir).
  - s1g/s2g/s3g: an out-of-TU GetLength still packs pt with this/dir.
- Slot-weight probes
  - y1-y3: dummy self-assignments pt.x=pt.x etc. are completely inert.
  - n3-n5, w4-w8, x4-x8: `this` kept live, self=this, qualified call.
- Scratch TUs e0/e1/f0/f1: the filter-temp kind; not faithful enough to transfer.
- z1/z2: a named filter local (before doorRange / before iter2) still gets its own slot at -0x3c, 0.873/0.882.
- Permuter: 30 min, 2236 trials from the 0.886 base, no gain.
- Flag sweep (earlier session): no gain.
- Earlier ids: p1 p2 p4 r1 r4 r6-r9 q2-q4 g1 g3-g11 n1 n2 s1-s3 a2-a10 c2-c9 d1.

Explanations covered:
- control flow: exit/door loop shapes, early-return forms.
- variable lifetime: pt/dir scoping, `this` liveness probes.
- types/layout: Vector3 vs Coord3D dir, Coord2D dir.
- callee visibility: in-TU vs out-of-TU GetLength/length.
- compiler settings: flag sweep.

Untried:
- An inner block that ends `this`'s last use together with the filter (a named filter alone is disproven: z1/z2).
- Retail's `this` might come from a non-virtual helper split: the door tail as a separate inline member function
  taking builderObject.
