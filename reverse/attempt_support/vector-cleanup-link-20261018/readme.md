# Empty-vector constructor link repair

`StlportRva003F610FDefaultCtor.cpp` gains **57 authored retail bytes in the
legacy link preview**. It formerly emitted a conflicting vector<unsigned int>
allocator constructor. Retain the inline wrapper but declare its base constructor
(the existing 29-byte owner at 00211E58) instead of instantiating another copy.
The compiler emits exactly the original parent, including the allocator temporary
and all three pointer stores performed by the existing callee. The existing
_Vector_base<uint> pin supplies that address; no pin or alias is added.

Paired five-unit previews use index 1a1c90e405 (2026-10-18 17:31): 0/5, 0 B
before; 1/5, 57 B after. Four nonmatching members were restored. No census,
index or link_status is changed. This is legacy evidence, not closed-strict
provider resolution or a runtime test. The bounded current-object preparer is
used only to create self-strict receipts for the changed unit.

The larger sweep also tested GeometryUpgradeModuleDataCtor,
stlport_list_create_node_vecuint, LightPointSystem and ProductionPrerequisiteCtor.
Imported-inline vector construction alone expands the base; declaring the rowed
base restores its call but changes EH states or allocator temporaries. Geometry
uses two distinct temporary bytes plus an extra state store; Production adds a
state store and its declaration-only copy dispatch initializes a formerly unused
tag; list insert moves its locals four bytes; LightPoint gains an EH frame.
All four original sources were restored after these two trials, and their
claims released. No checker exemption is warranted. Resume only with independent
compiler/EH evidence addressing these specific differences.

## Certified base provider

The first legacy-clean consumer exposed a shadow identity warning: its base
constructor name had a pin but no certified row, and the kept COMDAT differed.
Explicitly instantiate the unsigned base in the existing E16 owner unit and
register its complete 29-byte body as a gen-alias with fold-proof. Every byte
and owner relocation verifies, including allocator-proxy construction. This
certifies an existing ICF identity, adds zero coverage and is a required provider
for the 57-byte repair. `allowed_symbols.py --source` then reports two references
(one owner, one fold), zero rows with a wrong binding. No pin was added.

The provider unit still has pre-existing allocator/dispatch/assignment conflicts.
A trial restricting its whole-class instantiation to rowed members and declaring
the const uninitialized-copy helper changes the matched 52CE20 copy constructor:
the compiler initializes an otherwise unused tag and expands its frame. Restored
that trial; the committed provider unit differs only by the certified unsigned
base instantiation. Thus the consumer is self-strict and legacy-clean, while its
provider closure is still unmeasured/incomplete. No closed-strict gain is claimed.
