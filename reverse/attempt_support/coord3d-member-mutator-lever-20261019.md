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

## Round 2 screen (seat12, same day)

Note: WB's callee map labels the in-place MathCoord3D thunks wrongly (0x420D30
Sub shows as "atan2 0x422CD", 0x420830 Add as "Rva002E7964"); read the WB
call's `ecx`/push pattern, not the label. Separately, retail really does call
the C++ float overload `?atan2@@YAMMM@Z` (0x000422CD) in several bodies that
banks spell `_atan2f`; check the reloc.

- 0x004DFCE6 (sphere merge, 361 B): rebuilt in WB 0x0129CFF0 member order
  (copy ctors, `-=`, `*=`, `edge(old += dir)`, `center = (edge += opp)`):
  90 positional bytes -> 3 lines; then coord3d.cpp's Coord3D length and
  normalize visible as `__declspec(noinline) inline` copies (lever 1) made it
  exact. LANDED (Rva004DFCE6SphereMerge.cpp).
- 0x0037609C computeAerialPath (2148 B): the same visible length/normalize
  fixed both cos arms (14 -> 3 lines); the last line was the repair-loop
  tail, closed by reading the time step into a local before the add
  (`float spacing = ...; time = spacing + middle;`). LANDED
  (AerialPathfinderComputePath.cpp).
- So pair the member-mutator rewrite with visible Coord3D length/normalize:
  either alone left both bodies short. A blind sweep that only injects the
  visible bodies into banks (0x001E6007, 0x00451B92, 0x00561564, 0x0046525F,
  0x0034E5B5, 0x0047AC8F, 0x00457737) was inert or near-inert; a blind
  atan2f -> float-overload swap helped only 0x000471AD (10 -> 9).
- 0x001E6B8B (Locomotor, 919 B): getMaxSpeed respelling + float atan2
  overload: 9 -> 7 lines (cmp scheduled inside the goal copy). Banked.
- Inert or worse: 0x002E3AA8 (volatile-free member slide grows the frame,
  735 B), 0x005AA2D9 (members = existing forceinline helpers), 0x0041D60B
  (frame residue untouched), 0x00365309 (cos-cast trick inert at Rotate_Z),
  0x0045569D (bank baseline 1185 B), 0x00473B36 (bank 520 vs 543 B),
  0x0045AF14 (needs the home unit's region flags).
- Not attempted (large, low-score or home-unit): 0x00470DC1, 0x00345393,
  0x0026C4EB, 0x0027FD2A, 0x00272FB6, 0x00475F61, 0x001E6007 (no atan2/member
  site in its residue).
