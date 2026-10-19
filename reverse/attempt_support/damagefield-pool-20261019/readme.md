# DamageField pooled ObjectID list recovery

The new recovery is `DamageFieldUpdate::update`, native RVA `0x00491316`,
615 bytes. The previously verified 126-byte fire helper at `0x004911AE`
stays in its existing census-measured source unit and remains exact. Its
view is reconciled with the update's module layout. It adds no coverage.

## Identity and target evidence

The banked work identified the WorldBuilder twin at VA `0x011DF5A0` and the
native update interface at primary-object offset `0x10`. Native calls establish
the upgrade check, partition-filter chain, range iteration, fire helper,
retained-ID list operations and final FireWeaponUpdate update call. Native
accesses establish module data at `+0x04`, object at `+0x08`, retained list at
`+0x2C`, Object position at `+0x38`, and ObjectID at `+0x74`. The filter
temporaries die after the range-query full expression, before the two local
lists are constructed.

The fire helper's native accesses establish weapon `+0x20`, damage list
`+0x24`, entry weapon/frame/flag `+0/+4/+8`, and GameLogic frame `+0x40`.
The canonical `TheGameLogic` global is declared once; a local access view
expresses the frame offset. The fire helper's original name remains unknown.

## Source provenance and structural inference

The algorithm follows the prior WB-guided bank with real STLport 4.5.3 list
and find implementations. The missing distinction was the allocator parameter,
not the ObjectID or iterator type. Retail allocation calls the existing pool
at `0x00DA60E8` through `FreelistPool::pop`; teardown returns nodes to the
existing free list at `0x00DA60F0`. `BfmeObjectIdPoolAllocator` names this
structural allocator view; it does not claim a recovered original typedef.
Neither datum is newly defined.

VC7.1's configured STLport allocator adapter requires local rebind/create and
allocator-traits support. The allocation proxy constructor remains out of line,
as its native caller requires. The erase specialization performs the native
prev-first unlink and free-list return; the ObjectID enum has no nontrivial
destructor. These are real C++ lifetime/allocation operations. No assembly,
volatile scheduling device, optimizer pragma or alternate symbol was added.

The nine template helper names are folds onto existing matched providers.
`pin_admission.py --add` independently admitted their complete emitted extents,
bytes, callee identities and every owner's relocation bindings. They recover
zero additional bytes. `pin_consistency.py --symbol` established that none
already had a pin, and `--check` passed after admission. The existing
`find<_List_iterator<ObjectID>,ObjectID>` identity remains unchanged.

| Dependency | Native RVA | Whole size |
| --- | --- | ---: |
| allocator proxy constructor | `0x0014F3C4` | 11 |
| create node | `0x0029FB80` | 28 |
| clear | `0x0026549E` | 42 |
| erase | `0x002ABB20` | 36 |
| insert | `0x002A1316` | 37 |
| push_back | `0x002A1B6F` | 26 |
| remove | `0x002ABFC3` | 58 |
| list base constructor | `0x0029FB3B` | 40 |
| list base destructor | `0x00268902` | 29 |

The initial diagnostic proof is retained as `diagnostic-proof.json`. It binds
callees only after their own complete comparison, in dependency order. It is
exploratory evidence; normal pin admission and the normal source byte gate are
the landing proof. The normal source gate passed both rows (741 bytes).

`production-proof.json` separately records all eleven complete extents from
the production source object, using the actual symbol map after admission:
zero unresolved bindings, zero masked bytes, and no diagnostic overlay or
extent trimming. The normal EH verifier passed the update's complete graph
(`EXACT 1`, no baseline). Declaration and canonical-class checks passed. The
post-import placement rescan reported zero further bodies or pins.

The refreshed link preview first exposed three unprovided private filter
names and truncated filter vtables inherited from the bank, plus a losing
iterator comparison COMDAT. The native vtable addresses independently map
the filters to existing Rva002614ECFilter, Rva002611BFFilter and
Rva00260EB1Filter providers. Restoring the native third getPlayerMask slot
and using those established names preserves every update byte and its EH
graph. The existing TU-local iterator comparison pattern avoids emitting
the differently optimized shared iterator-base member. No new linker alias
or provider identity was invented.

Final `link_check.py <source> --refresh` passed: `1 of 1 link cleanly`,
`LINKED 125 -> 739 bytes`, against the published 2026-10-19 19:24 census
at `d5ae1ce9c2`, after replacing 957 rebuilt providers' definitions. These
are the link tool's authored-byte figures; the new whole retail body is 615
bytes. The broader current-ledger preview was unavailable because 10,659
older providers lacked its strict compiler receipts; no such preview result
is claimed. The ordinary refreshed census prediction is the link evidence.
