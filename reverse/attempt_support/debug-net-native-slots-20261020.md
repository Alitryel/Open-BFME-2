# Native debug net interface prerequisite

Read-only follow-up to the ODS linking repair; no source or ledger rename was
attempted. The named DebugIONet destructor currently has no pin or row. The
existing owner is Rva0088FB30NetIO at 0x3F4F0, with its deleting wrapper at
0x3F810. Its comment about another named FreeConsole owner is stale.

Retail evidence independently ties that owner to the named net constructor and
factory: 0x3F4A0 (70 B), 0x3F7B0 (96 B), and 0x3F4F0 (87 B) all store VA
0xBC09C8. The destructor closes the handle at this+4 unless it equals -1.
The constructor/factory first store the base VA 0xBC0990. At VA 0xBC09C8 the
seven native vtable entries, expressed as RVAs, are:

| Slot | Native target | Existing identity |
| --- | --- | --- |
| 0 | 0x3F810 | deleting destructor |
| 1 | 0x3F550 | DebugIONet::Read |
| 2 | 0x73B660 | byte-false stub; method identity unresolved |
| 3 | 0x3F5D0 | DebugIONet::Write |
| 4 | 0x69E440 | empty body; donor EmergencyFlush position |
| 5 | 0x3F690 | DebugIONet::Execute |
| 6 | 0x386C0 | shared DebugIOFlat::Delete body |

The BFME1 donor at 4483e88da1c2f3b9a273f779baac7458bd8bb891,
inputs/reference/.../debug/debug_io.h and internal_io.h, declares six slots,
without the native slot 2. BFME2 debug_io_net.cpp already uses BFMENetABI to
call Write through slot 3. Thus the donor declaration is not the complete
native virtual contract. The existing ODS improvement measures legacy link
prediction with self-strict code objects, not native vtable-data or closed-strict
convergence; its evidence states that scope.

Next repair needs to establish the native extra-slot contract and reconcile
its providers and consumers coherently before renaming the net destructor.
A rename plus the previously successful base/derived frame split would clear
some legacy findings while leaving this known ABI discrepancy. No such edit
was retained. All four net-unit claims and their requested RVAs were released.

Other session fallback probes: name_globals.py dry run found zero rewrites;
rehome_rows.py found two exact homes, but only 29 B and 17 B split rows, below
this seat's independent-repair threshold. The ranked/census queues include
many already-landed repairs; the expanded current-object probe and attempt log
remain necessary to avoid repeating the known allocator/Apt EH-copy blockers.
