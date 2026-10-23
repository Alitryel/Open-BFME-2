# Win32BIGFileSystem constructor link prerequisite

At BFME 2 4f08dcdb9e7, with verified BFME 1 pointer 96c88c73a5cd1a58fc2f8db691beea50acd996db,
the served 55B constructor in Rva0060453BCtor.cpp fails link_check only on
`??1Rva00602635VTableInstall@@UAE@XZ` and `??1Win32BIGFileSystem@@UAE@XZ`.
The file is not frozen. No production source or ledger was changed in this pass.

This is the class prerequisite already identified in
`reverse/attempt_support/filesystem-604465-vtable-20261019.md`, not two missing
destructor implementations. Read-only target inspection confirms:

- C7A94C has ten slots: 604572,603944,603D02,603C5F,603CA3,6046B0,
  47A69C,B3FD0,6042B6,603FF8. Slot zero calls the existing 59B
  Rva00604465 destructor at 604465, which tears down the tree at +4 and
  calls the base reset 60263E.
- C7A84C has ten slots: deleting destructor602645 and nine purecalls3B810.
  Constructor602635 installs that table in nine bytes; the seven-byte
  reset60263E is already rowed under Rva00060263EDwordImmSetter.
- The served constructor emits only one virtual slot and declares an empty
  fake map of NameKeyType to ModuleFactory::ModuleTemplate. Native6045A2 and
  its actual nested-map implementation in Win32BIGFileSystemRva006046B0.cpp
  establish the real 12B directory index, with a C-string comparator and
  file/offset/size member records. Copying the BFME 1 class layout directly
  would be wrong: its archive map and virtual signatures differ.

class_contract reports six Win32BIGFileSystem views, a majority 16B extent,
and unresolved names, field types and virtual slots; its majority result is
not a sufficient contract. Slots2/4 are supplied by Rva00603C0F, slot3 and the
destructor by Rva00604465. All must be reconciled with the named views.

The normal rename dry run for Rva00604465 -> Win32BIGFileSystem using
canonical:wb and the slot9 lead603FF8 refuses because name_evidence has no
wb-assert proof for that class rename. This is not recorded as a false reject:
the table proves shared class ownership, while the WorldBuilder lead alone
does not satisfy the tool's canonical-name standard. An inferred-name path
requires the documented independent agreement; rename.py also deliberately
rejects merging into a class token already present, so this needs a supported
class reconciliation rather than a cosmetic rename or extra alias pin.

Resume with the complete ten-slot/base contract and all existing providers.
Do not add destructor pins, remove virtual slots, or use novtable to hide the
missing graph. The existing one-slot destructor's successful byte/EH check
does not prove that its emitted class table is complete. No compiler variant
can supply the missing identity reconciliation.
