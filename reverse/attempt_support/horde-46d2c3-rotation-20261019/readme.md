# HordeContain 0x0046D2C3: three-register rotation (seat7, 2026-10-19)

Target `0x0046D2C3..0x0046D372`, 175 bytes. Bank `reverse/attempts/0x0046d2c3.cpp`
unchanged. The scripts beside this file apply the bank's listed home-unit edits
(slot 69 declaration, `KindOfType`, pinned `ThingTemplate::isKindOf`, inline
`Object::getTemplate/isKindOf`) to a scratch copy of the current
`HordeContainIface11CSlots.cpp` and compile candidates through `explain_mismatch.py`.

Current result: 175 B size-exact, 20 differing rows, a pure rotation of the three
saved registers (ours this=EBX / end=EDI / cursor=ESI; native this=EDI / end=ESI /
cursor and later obj=EBX).

Inert this session (all 175 B / 20 rows):
- 32 scope shapes: blocks around the list half and the set half, `obj` and the set
  iterator declared at function top (iterator reused for the final lookup),
  iterator declared before `end`;
- an `items` local, a forceinline slot-70 wrapper returning the list, an inline
  `ids()` accessor for the +0x170 set (the accessor lever that closed 0x005A9F70
  and 0x005B59FD). A non-forceinline wrapper (161 B) and `containedItems()`
  (172 B, different call) are worse; binding `*it` to an `Object *` local gives 181 B.
