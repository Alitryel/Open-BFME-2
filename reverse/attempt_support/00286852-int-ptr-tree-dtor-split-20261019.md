# 0x00286852 `_Rb_tree<int, pair<const int, void*>>` dtor: two retail families, one name

Link regression handoff (seat4, 2026-10-19, census 8eecc93d07 refreshed in memory at 432f23f7f5).

## Symptom

After cb80994bb0 retired `?dup_004ABCFE@@YAXXZ` (its `object-symbol=` annotation gave the
int/void* tree dtor name a second home at 0x004ABCFE), every COMDAT copy of
`??1?$_Rb_tree@HU?$pair@$$CBHPAX@...@QAE@XZ` is judged `wrong` by RetailTruth: the
name's only ledger home is 0x00286852, which calls clear at 0x00286656, while the
copies call `?clear@...<int,void*>`, whose ledger home is 0x004ABC5C (pins on the
0x00286656/0x00286183 twins are ignored because a ledger row wins). All 21 definer
units now fail link_check (`comdat`/`selected`), 7,370 census-linked bytes -> 0
(AptPalantirConstructor 3,896, AITeamBuilder 1,818, OpenContainCtor 452, ...), and
referencers such as PathDoXfer.cpp (1,501) gain a `selected` blocker.

## Target facts

- Family X: dtor 0x00286852 -> clear 0x00286656 -> _M_erase 0x00286183. Callers that
  name it int/void*: SiegeEngineContain/HordeSiegeEngineContain/HordeContain/OpenContain
  dtors (and HordeContainDtor funclets $L7168/$L7172), `map<int,void*>::~map` in
  ConnectionManagerCtor.cpp, StrategicConflictResultsImplCtor's unwind funclet.
  clear/erase are rowed only under address-derived placeholder elements
  (StlSweepW5Rva00286656.cpp `Rva00286656Element`, StlSweepW5Rva00286183.cpp
  `Rva00286183Element`); map clear forwarder 0x0046AAD9 calls 0x00286656.
- Family Y: dtor 0x004ABCFE (now `??1Rva004ABCFETree`, ModuleDataKeyMapDestructor.cpp)
  -> clear 0x004ABC5C -> _M_erase 0x004ABAD6; the 0x004ABxxx cluster in
  stlport_map_int_ptr_o1.cpp rows the whole int/void* tree (erase, find, count,
  equal_range, ...) under the int/void* names.
- The two families are byte-and-relocation twins, so they are two different template
  instantiations; only one can be int/void*.

## Tried (reverted)

Renaming row 0x00286852 (+ handler 0x00773EDF) to the `Rva00286656Element` tree dtor
(explicit instantiation, clear declared only) byte-matches the 56+10 bytes, but leaves
the int/void* dtor name without an address, and build.sh then fails 7 rowed callers
(the four Contain dtors, two HordeContainDtor funclets, ConnectionManagerCtor's
`~map<int,void*>`), whose calls to 0x00286852 are spelled with the int/void* name.

## What a fix needs (identity work, not a census-rule change)

Either (a) give family X its real type (ZH OpenContain's
`map<ObjectID, ObjectEnterExitType>` is a structural lead for the Contain users, not
proven) and respell the X callers listed above, or (b) rename X clear/erase to the
int/void* names and move family Y (0x004ABC5C/0x004ABAD6 plus the Y cluster and
ModuleDataKeyMapDestructor's declared clear) to another instantiation. Both touch
every caller listed; verify all 41 units that reference the dtor name
(`./build.sh` and `link_check.py`).
