# HordeContain melee parser: complete factory graph

At BFME 2 base66d9ca85287 and verified BFME 1 pointer96c88c73, the served
HordeContainParseMeleeBehavior.cpp owns the 221B parser4691B7 and its three
10B EH rows. The current census456ce161c5 reports six missing providers.

Target evidence, independently read from game.dat:

| Table VA | Slot0 | Slot1 | Slot2 |
| --- | --- | --- | --- |
| C44890 | 468A46 | purecall3B810 | empty RET4 47A69C |
| C4489C | 587752 | factory468A6C | empty RET4 47A69C |
| C448A8 | 587752 | factory468AAC | empty RET4 47A69C |

The parser's two inline allocations install the latter tables. Slot1 takes
one stack pointer and returns an allocated behavior: 468A6C allocates20B and
calls the existing Rva005838B5 constructor5838B5; 468AAC allocates24B and calls
HordeMeleeSwarm's constructor5843DA. The previous void()/void declaration
could not represent these methods. Existing source in Rva005838B5Ctor.cpp
and HordeContain/Rva00468AACCreate.cpp supplies the same semantic operations;
their address-derived owner views remain untouched. No additional original
application class or layout identity is inferred from these twins.

Deleting destructor587752 calls the seven-byte base-table reset468A3F before
conditionally deleting the object. An inline base destructor and out-of-line
derived destructors reproduce that graph naturally. Each derived destructor
is exactly seven bytes, both deleting destructors are28B, the base deleting
destructor is29B, and the empty buildFieldParse hook is3B. Complete ICF twin
rows carry every relocation; no callee pin or linker alias is introduced.
The noinline derived destructors preserve the actual out-of-line call proved
by587752. The earlier noinline-base trial produced an unwanted extra tail
wrapper and was not installed.

The native names table at VA DC9954 is exactly five pointers: C44880 (Swarm),
C44870 (WaitForLeader), C3C24C (HoldGround), C44868 (Amoeba), and zero. Its
existing global name is retained. The old data_ledger inferred844B region is
not the array extent; sizeof and complete relocation-aware verification must
prove the20B source definition. These are data bytes, not extra C++ coverage.

All additions are dependencies of the served whole file. The existing parser
must remain221B, its complete EH graph must remain exact, and every new body,
table relocation and shared COMDAT must pass normal admission before commit.

Validation completed: normal build passes12/12 function rows and the20B data
row, all3 EH graphs are EXACT, find_declared_unmatched is clean, and
place_bodies finds0 bodies/0 pins. link_check reports LINKS and0->230 bytes
under its frozen census accounting; new-variants passes. The queue's251B and
the link check's230B are different accounting views, not a new-coverage
claim. No new unique C++ bytes are credited for the ICF dependency rows.
