# Debug realloc trailer follow-up

Target: ?rva006C4730@GeneralAllocatorDebug@@QAEPAXPAXIH@Z, native
0x006C4730..0x006C4A4E, complete 798 bytes including RET12. The served
GeneralAllocatorDebugLockGuard 28-byte lead at this address is not the native
identity. WorldBuilder 0x0070BE40 corroborates debug reallocation, locking,
delayed-free retry, saved debug data and block-table/metrics relationships;
its layout, virtual dispatch and backup allocation differ from retail. No clean
GeneralAllocatorDebug donor was found in the committed BFME 1 game/reference
trees; the previous reference search remains applicable.

Read all seven prior boundary-specific attempt entries, the complete current
home Rva006C1F60Finish.cpp, the new complete home-TU bank, the WB decompilation,
and both matched siblings Rva006C4300Malloc.cpp and Rva006C3D30Debug.cpp before
trials. The newer bank incorporates the actual (void*, bool) metrics ABI and
the native conditional usable-size expression. Under the normal compiler it
emits 798 bytes with no unresolved calls and 18 differing fixed bytes, starting
at +0x9B. These differences are confined to the backup trailer calculation:
retail joins the integer capacity before LEA(base+capacity-10) and a word store;
the bank performs base additions in the two arms and retains -10 in the store.
Everything following this short region rejoins at the same native address.

The target/header relationship and the matched siblings support clearing the
two-byte trailer, not an extra lifetime or a volatile access. Test nine genuine
representations through explain_mismatch.py, with unchanged /MD source flags:

| Representation | Whole emitted extent | First difference | Fixed byte differences |
| --- | ---: | ---: | ---: |
| Forward pointer fill | 846 | 23 | 726 |
| Reverse pointer fill | 828 | 23 | 550 |
| Copy a zero ushort to trailer | 784 | 80 | 605 |
| Chunk-header-derived trailer store | 784 | 80 | 605 |
| Chunk-header-derived counted byte fill | 814 | 23 | 665 |
| Header plus generic inline byte fill | 798 | 80 | 235 |
| Integer-address phi | 798 | 155 | 18 |
| Integer-address plus size phi | 784 | 80 | 605 |
| Integer-address plus counted byte fill | 814 | 23 | 665 |

All calls resolve. Raw COFF extents are measured independently of the 798-byte
row-prefix patch. The generic fill produces two byte stores and repurposes EBX
for the backup request; it does not reproduce the native word store. Counted
fills disturb allocation/frame shape. The integer-address phi is equivalent to
the existing pointer phi and gives the identical remaining mismatch. The normal
explanation's x87 classification of one branch displacement byte is incidental;
the relevant native instructions are integer address calculations.

No better or exact candidate resulted. Preserve the stronger existing 0.99
bank unchanged; no Code, ledger, pin, header or compiler-setting edit is made.
The body claim is released. This follow-up contributes zero recovered bytes.

Input tree: ed842b1346cb91b2f29a60789b7909fdc3acf5d2; verified BFME 1 pointer
6b9d92bf92debd03e4357462bab41f701651e67c. results.json records measurements;
baseline.txt and generic-byte-fill.txt preserve useful instruction diagnostics.
For reproduction, copy replay.py.txt to build/NAME/trials.py and run it with
no argument, then header, then address. It obtains the unchanged seed from the
input commit when baseline.cpp is absent. Model: gpt-6.1-sol, about eight minutes.
