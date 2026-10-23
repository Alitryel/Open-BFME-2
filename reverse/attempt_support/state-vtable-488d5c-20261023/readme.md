# Complete the existing Rva00488D5C state view

Model gpt-6-astra, seat s5. Input local 5669476dd2 over published b8613df467. BFME1 pinned 138757e9b74645fbcbb7724a7af2764e34931e11; donor tree unchanged.

The source already owns the full 117-byte constructor at488883, its complete EH graph, the 54-byte state-entry callback488906, and deleting wrapper488D40. The constructor writes native primary vtable VA C4B5C8. This class view originally declared only five slots: its destructor, three undefined placeholders, and the entry callback. The undefined placeholders alone prevent the entire source from linking.

Native C4B5C8 contains seventeen code pointers (68 bytes), then the DozerActionState string atC4B60C. That string is the exact value returned by its slot2 code at488900. The class name is deliberately not renamed: the existing address-derived owner and neutral slot labels remain, and original method names/signatures beyond the recovered ABI remain uncertain. Primitive argument/return views follow the native RET cleanup and existing independently recovered bodies; no claim is made that body equality alone proves a new real name.

| Slots | Native RVA | Existing independent source evidence |
| --- | --- | --- |
| 0 | 488D40 | Rowed deleting destructor and its488D5C callee |
| 1, 7, 16 | B3FD0 | Complete one-byte void return |
| 2 | 488900 | ModuleNameGetters3 literal getter DozerActionState |
| 3 | 4894CA | Rva004894CAXfer_muse-4f8a: Version1, raw word at20, child Snapshot pointer at24 |
| 4 | 488906 | Existing full entry callback in this same source |
| 5 | 48893C | GapBodiesGE04 state-exit body; owner18->14->258, interface93, result10(-1), result24 |
| 6 | 4888F8 | VslotSmallBodiesAI: child pointer24, tail virtual call at slot4 |
| 8 through 15 | 47A699 | Complete three-byte false return |

The Xfer declaration is copied from the existing verified43-byte owner; its Version1 direct call and virtual raw-byte/Snapshot slots are retained. The existing OpaqueCallResult declaration is extended through slot24 for the exit body, without adding definitions. The native class fields remain unchanged, including volatile value20 and child24; the transfer takes the address of the former and passes the latter without pointer adjustment, as native does. No flag, header, baseline, pin, alias pragma, inline assembly, new volatile field or unrowed anchor is introduced.

The first normal build preserves all33 existing rows, including six EH-resolved funclet references and all existing literal references. A COFF diagnostic finds exactly68 bytes/17 relocations in the completed vtable. Every newly emitted body equals native after resolving the one Version1 call and the actual literal pointer; normal add_match --icf-owner subsequently verifies each against every existing owner. Final gates and scoped link accounting will be appended after admission completes.

## Coordinator budget stop

Stopped after slot13 admission (45/45 whole-unit checks). Slots14-16 and final link accounting were not completed. No new build or function started after stop. Production source and partial ledger entries restored; candidate.cpp.txt and in-progress.patch preserve the complete attempt. No link gain claimed. model=gpt-6-astra seat=s5.
