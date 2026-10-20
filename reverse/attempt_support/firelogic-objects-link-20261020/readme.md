# FireLogicSystemObjects.cpp link repair: handoff (2026-10-20)

Unit: `Code/GameEngine/Source/GameLogic/Map/FireLogicSystemObjects.cpp` (37/37 rows
matched, 5,805 B). `tools/link_check.py` at 7e32ef28ce reports 9 unresolved names
and one duplicate. Nothing was edited. Model: claude-opus-5-5, t=40.

## Wall: FireLogicSystemUpdate.cpp must link first

Retail's primary vftable 0x00BFB7BC (stored by ctor 0x00286EC8) has
`?update@FireLogicSystem@@UAEXXZ` (0x00287FAD) in slot 10. Only
FireLogicSystemUpdate.cpp defines that name, and that unit does not link:
- 6 STLport COMDAT copies: ObjectID map tree, vector erase, `_M_insert_overflow`,
  `_Construct`, `max`.
- `??0DamageInfo` selected.
- The same `rva00286E33`/`rva00287B2A` pair as below.

Once Objects models its vftable correctly, it references `update`, so it cannot
link before Update does.

## Retail facts established (target evidence)

### Vftables

| Address | Slot | RVA | Identity | Current row |
|---|---|---|---|---|
| 0x00BFB7BC | 1 init | 0x0028576D | `?init@FireLogicSystem@@UAEXXZ` | `?apply@Rva0028576DDwordImmSetter`, DispDwordImmSettersAddr.cpp |
| 0x00BFB7BC | 9 reset | 0x00287010 | `?reset@FireLogicSystem@@UAEXXZ` | `?rva00287010@Rva00287010`, VslotSmallBodiesAJ_Rva00034D00.cpp |
| 0x00BFB7BC | 10 update | 0x00287FAD | update (FireLogicSystemUpdate.cpp) | |
| 0x00BFB7AC (Snapshot) | 1 | 0x000B3FD0 | empty `loadPostProcess`, inline `{}` | |
| 0x00BFB7AC (Snapshot) | 2 | 0x00286F81 | `GetSnapshotName() const` returning "FireLogicSystem" | `?name@Rva00286F81Named`, SubsystemNameGetters.cpp |
| 0x00BFB7AC (Snapshot) | 3 | 0x00287C51 | xfer | |

- **Slot 1 init** (0x0028576D) stores `&0x002D7B50` into +0x9C. So +0x9C is
  `void (__cdecl *)(Int, Int)`, as FireLogicSystemUpdate.cpp already declares.
- The other slots of 0x00BFB7BC are SubsystemInterface defaults. Use
  `reference/shims/subsystem_bfme2/subsystem_interface.h` with
  `/Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2`, then
  `#define BFME_SNAPSHOT_NAME_SLOT` and Snapshot.h, as in
  SkirmishAIManagerCtor.cpp.
- There is no `crc` virtual. Drop the class's `crc` declaration.
- The deleting dtors 0x00287C05 and 0x00286F87 (rowed `??_GRva00286F8F` and
  `??_ERva00286F8F@@WM@` in OpaqueScalarDeletingDtorsB05.cpp) are this class's
  `??_G` and `??_E` vbase thunk.

### Registration global at VA 0x00DBB750

It is static data: {vftable 0x00BFB730, use count 0}. No code writes it
except FireLogicSystem's ctor and dtor.

The vftable 0x00BFB730 has one slot, 0x00286356. That is rowed
`?rva00286356@Rva00286356@@QAE?AVRva003ED658@@XZ` in VslotSmallBodiesAJ.cpp.
It returns a copy of the 0x002862C9 static through the copy ctor 0x003ED658.

Scratch `build/flsd/reg1.cpp` (this TU's flags) shows:

```cpp
struct FireLogicSystemParseRegistration { FireLogicSystemParseRegistration() : m_useCount(0) {}
  virtual Rva003ED658 rva00286356(); unsigned int m_useCount; };
FireLogicSystemParseRegistration theFireLogicSystemParseRegistration;
```

- MSVC 7.1 initializes this statically (no `.CRT$XCU`).
- It still emits `??0FireLogicSystemParseRegistration@@QAE@XZ`, an EXACT 13 B
  match for 0x00285D27. That row is now `??0Rva00285D27@@QAE@XZ` in
  RvaSmallVtableCtors.cpp ("vftable 0x00BFB730, owner unrecovered").
- So the ctor 0x00285D27 and the slot 0x00286356 belong to this TU's
  registration struct. Keep the `struct` keyword so the data name stays
  `?theFireLogicSystemParseRegistration@@3UFireLogicSystemParseRegistration@@A`.

### m_cellsOnFire (+0x84)

The node value is a 20-byte Rva00285BEC (polymorphic; FireLogicSystemUpdate.cpp
uses `_Rb_tree_node<Rva00285BEC>`), so the member is an STLport
set<Rva00285BEC> (node 0x24).

**Ctor.** 0x00286EC8 calls 0x00242F01 (a folded map/set default ctor). That
calls 0x0046AB53 (`_Rb_tree` ctor), which calls 0x0033B758 (`_Rb_tree_base`
ctor). That in turn calls 0x0014F3C4 (alloc proxy) and 0x000307F0 (allocate 0x24).
- Scratch `build/flsd/set1.cpp` shows a real `_STL::set<Rva00285BEC, Less>`
  ctor matches 0x00242F01 apart from its callee.
- But the instantiation drags about 25 COMDATs. Each needs a fold-proof pin or
  must stay unemitted, and no linked unit defines them.
- The cheap alternative is a gen-alias `??0Rva00286214@@QAE@XZ` row at
  0x00242F01. Its body would call the rowed LadderPref `_Rb_tree` ctor
  (0x0046AB53) through MSVC's explicit-ctor-call syntax, which is an identity
  stretch: see ArmorSetFinderView in ThingTemplateConstructor.cpp and
  Rva00171024Ctor.cpp for precedent.

**Dtor.**
- 0x00286F8F calls 0x0028681A, the tree dtor rowed in
  StlSweepR3Rva0028681A.cpp, which links.
- The funclets 0x00773F36 and 0x00773F80 `jmp 0x0028691C` instead. That is the
  out-of-line set dtor COMDAT, now rowed
  `?cleanup@Rva0028691CTreeCleanupForward@@QAEXXZ`.
- The symbols.csv pin `??1Rva00286214@@QAE@XZ -> 0x0028681A` is therefore
  wrong; it should be 0x0028691C.
- Fix: an inline `~Rva00286214()` calling `Rva0028681ATree::~_Rb_tree`
  (decl-only specialization). Rename the 0x0028691C row to
  `??1Rva00286214@@QAE@XZ` (this TU emits it), drop the pin, and drop the
  StlSweepR3 `cleanup` definition.

### Insert and duplicate

- **Insert:** call `?rva00286E33@Rva0028688A@@QAE?AURva00286E33Result@@ABURva0028688AKey@@@Z`
  (Rva00286E33InsertUnique.cpp, which links) through a view. This replaces the
  unresolved `?rva00286E33@Rva00286214`.
- **Duplicate:** define `rva00287B2A` inline (noinline) in both FireLogic units.
  Today Objects defines it strongly and Update emits a COMDAT.

## Order for the next seat

1. Link FireLogicSystemUpdate.cpp (its own blockers).
2. Apply the shim, vftable, registration, insert and dtor steps above here.
3. Resolve the 0x00242F01 ctor.
