# Button base vtable identity repair

The full gate at 0ec78c128 and 475287431 found one unbaselined DIR32 identity conflict: `??_7Rva005F5C77Base0@@6B@` resolved both to 0xBC6F20 and 0xC7A630.

The Rva005E91A9 constructor at 0x5E91ED installs the shared intermediate base table 0xC7A630. Its destructor at 0x5E91A9 restores the lower base table 0xBC6F20 at operand +46. Marking that lower base `novtable` suppressed its own teardown vptr and attributed the final store to the intermediate base. Removing the annotation preserves every ordinary instruction byte while making this operand name the actual lower base table. No class rename, new address pin, alias, gate allowance or baseline change is needed.

The complete lifetime unit already emits the scalar deleting wrapper at 0x5E9279 (28 bytes) and adjustment thunk at 0x5E91E5 (8 bytes), identical in bytes and relocations to the partial view in OpaqueScalarDeletingDtorsB17.cpp. Rehome those existing rows to the complete lifetime unit and remove that obsolete view. The three peer constructors at 0x5F5C77, 0x5F5F2B and 0x5F589E declare the shared base destructor instead of emitting competing empty copies; its complete provider remains in Rva005E91A9Dtor.cpp.

`proof.json` records a controlled comparison against the pre-edit objects using the published 2026-10-18 08:17 census refreshed with current objects. All seven peer units introduce no new unresolved, duplicate, COMDAT, selection or address findings. Whole matched ordinary bytes are unchanged; all five parent EH graphs remain independently EXACT. The meaningful relocation change is precisely the destructor operand +46. The normal scoped byte gate passes 36/36 rows across seven units. Remaining unreferenced table diagnostics are outside this repaired DIR32 conflict; no full executable linkage or runtime result is inferred.

Prior family identity evidence: reverse/identity_evidence/button-single-state-constructor.md, reverse/identity_evidence/button-record-base-constructor.md and reverse/attempt_support/button-base-link-20261015/readme.md. BFME 1 donor pointer reviewed: 64d369b90170b7e9ec917d646f020b11f13eb0d5; existing family ownership limitations still apply. No unchanged donor search is repeated.

