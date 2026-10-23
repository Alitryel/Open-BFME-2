# Scene-list direct-base linking repair

`BfmeRefSceneListDtor.cpp` previously constructed an empty
`RefMultiListClass<RenderObjClass>` intermediate base. That emitted three
conflicting template special members (constructor, destructor and scalar
deleting destructor), preventing all 124 matched bytes in the unit from linking.

The owner now derives directly from `GenericMultiListClass`, as the existing
view in `RTS3DSceneCtor.cpp` already does. Its drain loop calls the existing
rowed `RefMultiListClass<RenderObjClass>::Release_Head` through a pointer view;
that view retains its real GenericMultiList inheritance but is never constructed
as a separate subobject. No template code is suppressed with compiler attributes.

Native evidence:

- Constructor `0x0006E518`, 18 bytes, calls GenericMultiList constructor
  `0x00065815`, then installs vtable `0x00BC6260`.
- Destructor `0x0006F29B`, 68 bytes, drains through Release_Head
  `0x0006EF8C` while `[this+8] != this+4`, then calls GenericMultiList
  destructor `0x00610640`.
- Its FuncInfo at VA `0x00D01134` has one unwind state. The sole action
  `0x0075EB10` loads the saved receiver and jumps directly to the same
  GenericMultiList destructor. The exceptional base lifetime is therefore
  direct as well.
- Vtable `0x00BC6260` points to the 28-byte deleting destructor
  `0x0006F7A1`, which calls `0x0006F29B` and conditionally deletes.
- The reference `RefMultiListClass` destructor drains its own list; an
  extra empty instance of that template is a local reconstruction artifact.
  The original concrete class name remains unproven, so the existing neutral
  `BfmeRefSceneList` name is retained.

Validation at BFME2 `413ecd9e74b1c122e930f26a1f9d3099f4ad6d20`, pinned BFME1
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`:

- Fresh baseline `link_check.py`: three COMDAT blockers, 0 linked bytes.
- Repaired `./build.sh`: all four existing rows exact (18 + 68 + 28 + 10-byte
  EH handler).
- Repaired `link_check.py`: 124 linked bytes, no blockers or diagnostics,
  against published census `5366c4f808` from 2026-10-20 12:21.
- `place_bodies.py`: no new bodies or pins.
- Consumer checks: RTS3DSceneDtor's 49 bytes and SimpleSceneClass_dtor's
  290 bytes remain link-clean. RTS3DSceneCtor retains independent existing
  unresolved material-setter, duplicate-constructor, lighting and vtable
  blockers; no gain is claimed for it.

This is a 124-byte linking repair, not newly recovered retail coverage.
