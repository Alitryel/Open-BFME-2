# River virtual-base aggregate-return thunk

Inputs: BFME2 ac8df80501; retained verified BFME1
138757e9b74645fbcbb7724a7af2764e34931e11; MSVC 13.10.3077;
/O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB.

## Target facts

Native secondary table VA C088E0 has seven slots:
30C4BE, 30C4C6, 30C4A6, 30C4CE, 30C4AE, 30C4B6, 30C4D6.
The complete eight-byte slot-1 entry at 30C4C6 is
`2b 49 fc e9 d4 f9 ff ff`: subtract [ECX-4] then jump to 30BEA2.
The existing complete 68-byte aggregate-return body at 30BEA2 reads the
16-byte-element vector 0x28 bytes before its receiver. The current row's
nonvirtual class is an opaque layout view, not an established original name.
The exact river ctor 30C4DE and dtor 30C40A independently place the
virtual interface at +90 and the vector-containing quad strip at +68.

## New compiler evidence

Earlier explicit C++ forwarding failed because it repushed the hidden result
and index arguments. Genuine virtual inheritance solves the instruction-shape
problem: an aggregate-return virtual override emits the native eight-byte
vtordisp thunk without repushing either stack argument.

The diagnostic .cpp.txt is not game source. Copy it to
build/local-vm/river-vtordisp-probe.cpp, then use explain_mismatch with the
virtual method symbol, --source, --rva 0x0030BEA2 --size 68. Its real member
vector at +68 and virtual base at +90 reproduce the existing parent exactly,
including both operator[] relocations to the existing provider. Its emitted
`?rva0030BEA2@Rva0030BEA2Base@@$4PPPPPPPM@A@AE?AURva0030BEA2Point@@H@Z`
is eight bytes `2b49fce900000000`, with one REL32 to that virtual method.
A smaller inheritance model using the old this-minus-28 expression instead
produced the wrong -30/-2C displacements because MSVC also adjusts virtual
receiver accesses. That is why layout, not extra casts, fixes the parent.

## Remaining prerequisite

Do not land the diagnostic constructor or its invented partial vtable. Removing
the constructor correctly leaves no emitted vtordisp thunk. An authentic
existing constructor/destructor must emit the complete native hierarchy.
The current Rva0030C1FCOwnerDtor view has only one virtual-interface slot,
and its `s0` forwarder does not represent native seven-slot C088E0. Its
primary table is also incomplete. Reconcile that owning class and the existing
opaque provider rows before admitting the thunk; do not add alias pins,
invent a wrapper, rename just the parent, or force emission with a dummy ctor.
No Code or ledger implementation was changed for this target.

## Startup limitation

The BFME1 upstream fetch reached 11e07d5c02bf0ee6e6fbecdbebeaa9f45189b72c.
The old-input full gate required 2,114 compiles of 23,425 TUs despite importing
22,653 published objects; it was interrupted before a verdict. The missing ZH
cache rebuild's first animatedsoundmgr.cpp compile ran over 17 minutes in the
VM and was interrupted too. Existing 12 ZH cache objects gave no free packets.
BFME1 was not advanced, no full baseline or update success is claimed, and no
freshness receipt was written. Future work still owes the reference refresh.
