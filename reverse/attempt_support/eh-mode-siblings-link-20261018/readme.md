# Exception-mode and private-view sibling link repairs

Same-index paired current-object legacy preview: **+669 existing C++ bytes linked** (399 -> 1068), no authored C++ growth. Four previously blocked units now link; the two already-linking providers remain unchanged. ModuleFactory.cpp still fails for its pre-existing unrelated providers and copies. These are legacy predictions from census c2c5ac8c27 (2026-10-18 11:36), not closed-strict or full-link results.

| Changed unit | Before | After |
|---|---:|---:|
| Rva001DA2D5Ctor.cpp | 0 | 311 |
| TransportAIUpdateModuleDataCtor.cpp | 0 | 176 |
| Rva00502c80Finish.cpp | 0 | 121 |
| Rva00414093Copy.cpp | 0 | 61 |

Both paired runs explicitly include the exact Rva001DA2D5Finish.cpp (206 B) and stlport_modulefactory_map_copyctor_00413EE6.cpp (193 B) providers and ModuleFactory.cpp. Before was measured from HEAD source contents at the same BFME 2 revision and reference pointer as after, restoring all four edits immediately afterwards. Full outputs are before.txt and after.txt; exit 1 in both is expected because unchanged ModuleFactory.cpp does not link.

## Supported changes

All four units inherit the proved /EHsc -> /EHs repair from ../eh-mode-link-20261018: preserve the exception-state store in referenced vector/tree destructor bodies. Every rowed caller remains byte-exact.

Rva001DA2D5Ctor's AudioInfoRefCountBase is an existing private view, not a newly established class identity. Its emitted base vtable pulled in an undefined destructor. Marking that base view novtable removes that unused construction table and its deleting-destructor reference; the complete native 311-byte constructor still verifies with all five floating literals. The independently rowed copy constructor in Rva004335BCFinish.cpp already uses a novtable base with the same virtual destructor and +4 scalar. The actual default-constructor body installs only the final 0x7DA270 table. No target base-class name or complete layout is newly asserted.

The two module-data holders incorrectly declared an empty ModuleFactory::ModuleTemplate with a nontrivial undefined destructor. The established three-word view has two procedure pointers and an interface mask and a trivial destructor. The existing reference/shims/modulefactory/Common/ModuleFactory.h describes that donor layout; independently rowed target pair construction/copy in ModuleFactory.cpp (0x41360E, 0x29B260, 0x413E0D) establishes the 12-byte payload and its trivial copy. Rva00414093Copy already used that view. Removing the false destructor and using the same three words makes both map _M_erase copies agree with the kept provider. No enclosing layout changes: map storage is still 12 bytes.

Rva00414093Copy additionally emitted a non-retail tree copy constructor. A declaration of its exact specialization binds the already-existing rowed 0x413EE6 provider instead. Its own native 61-byte caller and 10-byte handler are unchanged; the paired provider retains all 193 linked bytes. No instantiation identity, pin or alias is added.

## Acceptance and remaining scope

Strict reusable receipts and normal byte/reference gates pass 7/7 code rows across all four changed units, including the two module-data handlers and copy handler. Seven floating literals and one string verify. Exception tables are EXACT 3/3 (the default constructor has no EH frame). Frozen-source checks and hooks also run. No gate/baseline/header/reference input changes are involved. No runtime, census or closed-strict gain is claimed.

The private ModuleTemplate constructor/destructor pattern occurs in no remaining Code source after this pair is repaired. Other /EHsc siblings still have independent prerequisites (FileSystem set spelling/provider and private class destructors); a flag-only change would not link them and is not landed. The BFME 1 pointer remains the previously verified 64d369b90170b7e9ec917d646f020b11f13eb0d5; the upstream update is held by another live seat claim.
