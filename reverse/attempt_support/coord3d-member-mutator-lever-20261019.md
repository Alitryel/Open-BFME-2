# Coord3D member-mutator lever (seat12, 2026-10-19)

Landed 0x0053EDF4 (`?rva0053EDF4@Rva0053ED1A@@UAE?AUICoord2D@@XZ`, 286 B, commit
"Land Rva0053ED1A's slot-4 screen-position override") after a 0.865 bank had
stalled at 294 B: the offset arm scheduled a fourth XMM register.

## What closed it (target facts vs inference)

- Target: the WorldBuilder twin 0x01116650 calls MathCoord3D.h's in-place
  operators (WB 0x41F630 `operator-=`, 0x41F3B0 `operator+=`, both `ret 4`
  returning `*this`) and constructs its Coord3Ds (debug sentinel 0x1DD08E0 and
  EH states).
- Measured in isolation on 0x0053EDF4 with `/O1 /Op /MD /EHsc /arch:SSE`:
  - exact: member `-=`/`+=` (or member `sub`/`add`) **and** the zeroed
    contact initialised through a member (`Coord3D(0,0,0)` from
    `Lib/Coord3DCtorView.h`, or `set(0,0,0)` from `Lib/Coord3DInline.h`);
  - exact: canonical POD `Lib/Coord3D.h` plus a TU-local derived view
    (`struct C3 : Coord3D { set; operator-=; operator+= }`) reached by
    `static_cast<C3 &>(c)` for the init and both mutations;
  - 294 B: the same member operators with aggregate init `= {0,0,0}`;
    explicit component arithmetic (any of 72 order/operand permutations);
    free `operator-=`/`+=` taking references; free pointer or reference
    helpers; `/O2`, `/G5-/G7`, `/arch:SSE2`, `/Oi-`.
  So the lever is "write every mutation of the Coord3D, its initialisation
  included, through inline member functions as the twin does".

## Tried elsewhere, not closing

- 0x0028F326 (`Rva0028F326Owner`, 294 B): WB copy-constructed delta,
  `delta -= source`, inline dot (WB 0x41FB90) under Coord3DCtorView.h takes the
  bank from 8 to 3 differing lines (banked 0.97). Left: retail loads
  visionAngle (movss [eax+0x53C]) after the first dot fmul, ours before.
  Inert: local before/after the dot, `*3.141f/360.0f`, Bool result, dot operand
  orders, /G flags; worse: 3-arg/set() facing, re-reading `data`.
- 0x002FD344 FindPath (781 B, 2 diffs): bank re-applied to current
  pathfinder.cpp (LocomotorSet `m_nameBuffer`/`name()`, FindPath declaration,
  block after InternalFindPath). A derived member view for adjusted/delta
  (`set`, `-=`, `*=` or `sub`/`scale`) leaves the loop-latch reload order
  (retail y,x,z; ours x,y,z). Bank unchanged.
- 0x00392802 getPortTransform (725 B volatile bank): volatile-free member
  `/=` (inv*x), `-=`, `+=`, `*=` in WB order gives 735 B (dir copy becomes
  movs) or 712 B with a member/ctor copy; not closer. Bank unchanged.

- 0x0037609C computeAerialPath (2148 B): the stored bank compiled to 2144 B
  (setup-z add folded into a memory operand). Initialising `center` with a
  member `set(const Coord3D *)` and writing `p += center` as a member
  `operator+=` (WB 0x41F3B0) makes it 2148 B size-exact; calling the C++
  float overload `atan2(float, float)` (`?atan2@@YAMMM@Z`, 0x000422CD, the
  retail call target) instead of `_atan2f` fixes that call. 22 differing
  lines left, all in the two cos arms (retail loads target.z right after
  `call cos`, then fmul/fadd between the pushes). Banked 0.97.

## Candidates still unscreened with this lever

Banks whose WB twin calls 0x41F630/0x41F3B0/0x41F8B0/0x41FA20/0x420830/0x420D30:
0x001E6007, 0x005AA2D9, 0x0046525F, 0x00470DC1, 0x00345393, 0x00473B36,
0x006BEF80, 0x002E3AA8, 0x0026C4EB, 0x0027FD2A, 0x001E6B8B, 0x00272FB6,
0x0041D60B, 0x004DFCE6, 0x00365309, 0x00475F61 (0x420830 and
0x420D30 are the by-value Add/Sub forms, untested).
