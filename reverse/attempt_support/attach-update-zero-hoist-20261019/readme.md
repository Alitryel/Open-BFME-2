# AttachUpdate 0x00491AD0: constant-zero hoist (seat7, 2026-10-19)

Target `0x00491AD0..0x00491C84`, 436 bytes. Bank `reverse/attempts/0x00491ad0.cpp`
unchanged (it still has the uninitialised `where` and the int-argument EVA view).

Clean semantic body (real `reportEvaEvent(EvaEventID, const Coord3D *, const Coord3D *)`,
every branch reporting at `parent->getPosition()`, no volatile) compiles to 417 B with
113 differing rows. Residue: cl hoists the constant 0 into EDI at entry
(`xor edi,edi; cmp [ecx+0x20],edi`), spills `this` to [ebp-0x10] and keeps the
parent in EDI. Native keeps this=EBX, data=ESI, obj=EDI, the parent in [ebp-0x10],
compares `[ebx+0x20]` with an immediate and only materialises 0 in EDI after the
FX call, once obj is dead.

Tried (scripts beside this file), no change from 417 B / 113 rows:

- inline `getObject()` / `getTemplate()` / `m_274` accessors, the module-data
  accessor at every use instead of a local (438 B), no obj local (416/436 B, worse),
  inline vs local `ThePlayerList->getLocalPlayer()`;
- parent made address-taken through an inline `Object *&` / `Object **` redirect
  helper and through a local reference: cl sees through all of them.

The inline-accessor lever that closed 0x005A9F70 (same constant-hoist/this-spill
shape) does not move this one. The earlier volatile-reference diagnostic (436 B, this
and obj swapped) remains the closest structural result but is not landable.
