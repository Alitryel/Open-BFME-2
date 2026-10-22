# Linking pass 2026-10-22 (second seat): findings and dead ends

Model: claude-opus-5-5. Index: the local link index brought to HEAD with
`link_check.py --update-index` (census 2026-10-21 21:42 at e20daa4e78 plus
reread objects). Landed fixes are in the commit log ("Link ..." by
Gleb302596555 on 2026-10-22). This file records what was tried and not landed,
so the next linking seat does not repeat it.

## Read this first

- Units added since the census are "not previewable". Several blockers that
  still show in `link_rank.py` are already fixed by such units and resolve at
  the next census: `Locomotor::rva001E7ECA` (LocomotorRva001E7ECA.cpp),
  `~vector<Rva002BBB96Element>` (StlportVectorDtorDeferred.cpp),
  `~_List_base<Object*, Rva001EB984PoolAllocator>` (HordeContainRva00475F61.cpp),
  `NetPacket::getCommandList`. Check `git log` for the name before working it.
- A stale `build/match` object can show old manglings: LivingWorldArmy.cpp's
  cached object still exported `PAV` names after the source moved to
  `struct` (fixed upstream in 5bd9ec9e4c). Rebuild a unit before reasoning from
  its object.

## Declaration-only suppression: where it does not work

The pattern (`namespace _STL { template <> ... ; }` before use) only helps
where the unit calls the member out of line. Measured failures:

- `__uninitialized_copy<char*,char*>` (14 units, 3,126 shared bytes): eight
  wrong copies precede the first retail copy in link order (rope_char,
  narrow_string, narrow_num_put, basic_ios_init, narrow_money_put_string,
  wide_ifstream, narrow_string_substring_ctor, narrow_string_substr). The
  suppression is byte-safe in rope_char, narrow_string, narrow_num_put,
  basic_ios_init, narrow_money_put_string, wide_money_get_string and
  float_format, but changes rows in wide_ifstream (`_M_underflow_aux`),
  narrow_string_substring_ctor and narrow_string_substr (they inline it).
  Until those three keep a retail-identical copy, suppressing the others
  links nothing; nothing was committed.
- `vector<Rva0007BB16Record>::_M_allocate_and_copy` in fxshadersetup.cpp:
  the `template <> template <>` member-template declaration ICEs cl 7.1
  (C1001 at _vector.c:50) wherever it is placed; the single `template <>`
  form is rejected (C2768).
- `vector<BfmePod52>::_M_insert_overflow` in stlport_pod_vector_bodies.cpp:
  suppressing it changes the push_back row's call (REL32 past its 55-byte
  extent).
- `_List_base<Drawable*>(const allocator&)` (SelectionXlatTranslateGameMessage,
  4,145 B), `_Construct<const ModuleData*>` (Rva00506A52),
  `__uninitialized_copy<BfmeRecord0040B61A>`, `_M_put_num<char,long>`
  (Rva0055C0E1), `_Hashtable_iterator::_M_skip_to_next` (PlayerCloneFrom),
  `_M_create_node` (ScriptEngineDoXfer: shifts $L funclet numbering): all
  inlined, so their rows change.
- `vector<unsigned>(const allocator&)` (stlport_list_create_node_vecuint,
  AptStrategicPlayerStatus): the copy is emitted unreferenced; retail's default
  insert reaches the ICF'd `_Vector_base` at 0x00211E58, so declaring the
  vector ctor turns the inline into a call.

## Vtables emitted from two views

Moving an opaque batch file's `??_G` row into the class's real unit (done
for Rva002CCD56 and Rva003EF36E) only pays when the receiving unit then links.
AutoAbilityBehaviorModuleData (FamilyDeletingDtors_muse-206f) was tried and
reverted: its constructor unit still has unresolved slot names. Rva001E72B4 was
reverted: its constructor and destructor units use different
SubsystemInterface views, so removing B03's copy unlinked the destructor unit.

Classes whose views all disagree with the retail table (need a canonical
module/state header, not a local edit): Rva00340BDC (retail 0x00812150:
AIAttackMeleeEngageState slots), CreateCrateDieModuleData (retail 0x00BF40A8:
ModuleData slots 1-3 are the shared 0x000B3FD0 / name getter / 0x0047A69C),
MonitorConditionUpdate (0x0084DAD8), Rva00421242 (alternatename hatch in the
constructor unit), Rva0020479E (DoXfer's view declares unrowed
LoadPostProcess/crc/DoXfer).

## Other leads

- `g_lastJoinedGroupRoomID` (AptMessengerOnlineResponse.cpp, extern only): no
  definition and no data row; retail .data 0x009D3938 holds -1. The unit also
  needs `~GameSpyGroupRoom` fixed.
- `~GameSpyGroupRoom` (pin 0x0038240F): PeerDefs.cpp (no /O flag) emits a
  5-byte tail jump. The 53-byte retail body is reproduced exactly by
  `AsciiUnicodePair::~AsciiUnicodePair() {}` with AsciiUnicodePairCopyCtor.cpp's
  view under /O1; adding /O1 to that file breaks its copy constructor row, so it
  needs its own /O1 unit and an identity decision (the pin names
  GameSpyGroupRoom; PeerDefs.cpp says retail spells it AsciiUnicodePair).
- `Set@Matrix3D(Matrix3x3)` in colmathsphere.cpp: `#define Matrix3x3 Matrix3`
  resolves the name, but the unit (no /O flag) then emits its own
  `Matrix3D(Matrix3,Vector3)` constructor with a Vector4 constructor iterator,
  unlike retail 0x00174C20, so it still fails.
- `?rva0006F039@Object` style address pins of matched bodies: calling the
  ledger name instead (as done for LocomotorMoveTowardsPositionHorde) is the
  cheapest repair; `tools` has no finder, a scan of unresolved names against
  symbols.csv pin addresses with a matched row there lists them.
