# Natural XferException throws in container loaders

Five existing `Code/GameEngine/Source/Common/` units replace their manual
formatter/runtime-throw bridges with `throw XferException(4, message)`:

| File | Existing retail rows | Bytes |
| --- | --- | ---: |
| `Rva00390911Xfer.cpp` | 0x00390911 | 205 |
| `Rva0046EFDBXfer.cpp` | 0x0046EFDB | 202 |
| `Rva00426F17Xfer.cpp` | 0x00426F17 and EH 0x00787332 | 258 |
| `Rva00473FD4Xfer.cpp` | 0x00473FD4 | 217 |
| `XferSTLObjectIDList.cpp` | 0x00331F2D | 196 |

The nonempty-on-load conditions, tag 4, vector/map/list messages, loops,
container declarations, compiler flags and STL settings are unchanged.
The two unused C++ runtime-throw aliases are removed along with their
declarations. No shared header, symbol pin, data owner or ledger row changes.
The shared legacy ThrowInfo owner in `Rva00470222Xfer.cpp` is outside this
consumer-local repair.

Native calls independently identify constructor RVA 0x0060C36E, runtime
throw RVA 0x00629094 and ThrowInfo VA 0x00CFFD18 in all five parents.
The 8-byte `.?AVXferException@@` class and its existing providers are
established by retail metadata, not inferred from the donor names.
The pinned BFME1 revision `92f6bbe8` independently supplies ordinary throws
for the same error conditions in:

- `game/GameEngine/Source/Common/System/XferCoord3DVector.cpp:112`
- `game/GameEngine/Source/Common/System/XferObjectIDVector.cpp:108`
- `game/GameEngine/Source/Common/System/XferMapAsciiStringReal.cpp:124`
- `game/GameEngine/Source/GameLogic/ScriptEngine/XferListInt.cpp:92`

`throw-evidence.json` records source hashes, unchanged effective flags,
all six exact retail rows and their 15 exception-related relocations.
`metadata-graph.json` follows the four emitted exception metadata sections
per object. Every masked section is exact, with external references checked
against destructor VA 0x0042BD30, copy constructor VA 0x004588C5 and type-info
vtable VA 0x00C7C730. `independent-review.json` records a separate inspection
that resolved all metadata relocations and compared the full 20 sections.
`eh.json` reports the existing parent exception graph EXACT.

The initial ordinary gate passed all six candidate files before editing.
After excluding the snapshot-vector outlier below, the final ordinary gate
passed all eight original rows, including a fresh compile of the restored
outlier, and all 12 string references. The accepted five files account for
six rows and 1,078 bytes. `paired-link.json` compares the preserved original
objects with the repaired objects under the same census and compiler
command/environment: all five link both before and after, with every blocker
category empty. This is source repair with zero new coverage or link gain.

## Rejected snapshot-vector candidate

`Rva004EE9E9XferVector.cpp` owns parent 0x004EE9E9 (245 bytes) and handler
0x0079298F (10 bytes). The plain natural-throw replacement produces six
differing bytes: frame allocation changes from 0x10 to 0x18, and five
references to the later 12-byte record move down eight bytes. Native code
shares the 8-byte exception temporary at EBP-0x18 with the upper part of
the record at EBP-0x1C; the compiler keeps the natural throw temporary
separate from that record.

`snapshot-slot-rejected.patch` preserves the exact rejected source change;
`initial-gate-failure.txt` preserves the ordinary gate's byte comparison.
One bounded private-object trial removed the redundant `else` after the
nonreturning throw and placed the record in its own following block.
This preserves disjoint natural lifetimes without storage overlays.
It compiled in 3.37 seconds and retained exactly the same six differences,
with no unresolved calls and an exact 10-byte handler; see
`snapshot-scope-trial.json`. The remaining prerequisite is a source-supported
lifetime or object-ownership explanation for native slot sharing. No union,
forced stack placement, helper or broader allocator search was introduced.
Production source was restored byte-for-byte and the normal gate passed.

Agent: Codex (runtime model not exposed).
