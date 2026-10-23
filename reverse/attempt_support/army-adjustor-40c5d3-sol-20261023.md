# ArmySummaryEntry secondary deleting-destructor adjustor

Inputs: BFME2 b51a8e3e03; pinned BFME1
138757e9b74645fbcbb7724a7af2764e34931e11; ordinary MSVC 7.1 /O1 /MD.

## Native evidence and prior blocker

The complete native entry at RVA 0040C5D3 is 11 bytes:
`81 e9 ac 00 00 00 e9 00 00 00 00`. Its jump reaches 0040C5DE.
The generated five-byte owner at 0040C5D9 covers only that jump.
The four-slot primary table at VA 00C3944C points to deleting destructor
0040C5DE, empty load-postprocess 000B3FD0, name getter 0040C586 and xfer
0040C4FE. The one-slot secondary table at VA 00C3945C points to 0040C5D3.
The adjacent literal is `ArmySummaryEntry`; the established constructor,
destructor and xfer owners use that class independently of this attempt.

The native destructor at 0040C39E installs those two derived tables, restores
the secondary base table BC6F20 at offset AC, and tail-jumps to CarryoverUnit's
destructor. The constructor initializes the secondary word at B0 to zero.
Those accesses agree with the registered Rva0007DF07 partial base layout and
its BC6F20 table; the original secondary-base name remains unknown.

Prior attempts at 40C5D3 correctly rejected an ordinary wrapper and the
nonvirtual synthetic Rva0040C39E deleting-destructor declaration. The real
ArmySummaryEntry destructor is already rowed and virtual. Retract the old
synthetic wrapper separately rather than silently replacing its identity.

## Isolated reconstruction

Using the canonical Snapshot header for the four primary slots, CarryoverUnit
as the AC-byte primary base, and canonical Rva0007DF07 as the secondary base
emits the real compiler adjustor `??_EArmySummaryEntry@@WKM@AEPAXI@Z`.
The compiler also emits the 28-byte virtual scalar deleting destructor,
29-byte parent destructor, one-byte loadPostProcess and six-byte name getter.
The parent reproduces all 29 bytes with the existing CarryoverUnit relocation;
the adjustor's real weak default resolves to the scalar deleting destructor.
These are isolated trial results, not yet ledger admission or progress.

An incomplete one-slot primary view also emits the code, but its generated
vtable is not the complete native table and must not land. Integrate the
complete Snapshot surface and reconcile the raw table providers/consumers
before admitting the new adjustor. The secondary offset is established;
this partial destructor view does not establish the full class size.

## Production integration and limits

The incorrect scalar owner and its destructor pin were retracted in
d54e386715. The raw primary-table data row was retracted with its definition:
its first entry depended on the removed false scalar identity. The normal
commit hooks verified the remaining 20 functions and two data rows.

The production destructor now uses the canonical four-slot Snapshot surface
and Rva0007DF07 secondary base. The constructors reference the compiler's two
actual vftable symbols instead of separate address-named globals. The const
name getter is admitted as an exact six-byte ICF twin of the existing opaque
returner, with no unique-byte gain. The three-source byte gate is required
before committing this integration.

Independent private-object inspection of the protected-slot model confirms
complete emitted extents of 29 bytes for the parent, 28 for the virtual scalar
deleting destructor, and 11 for the secondary adjustor. Every REL32 matches
the existing parent/base destructor or operator delete, or the adjustor's
genuine weak default to the scalar. The parent has three DIR32 relocations;
their native words are copied by the byte comparison, not independently
resolved by that private diagnostic. The generated primary table has exactly
four relocations at offsets 0/4/8/12; the secondary has one at offset 0.

The shared empty body at 000B3FD0 is held by another worker (link seat w3).
Do not add its ArmySummaryEntry::loadPostProcess ICF implementation or force
the claim. The current class intentionally leaves that method declared, not
defined. This preserves the complete slot surface without touching the claimed
body, but leaves an explicit link prerequisite. A generated table and exact
destructor/adjustor bytes are not a claim that this unit already links.
