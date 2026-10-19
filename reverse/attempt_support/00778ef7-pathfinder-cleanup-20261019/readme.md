# GetHordeUnitPath allocation cleanup

The existing clean C++ `Pathfinder::GetHordeUnitPath` emits the actual local
label `$L17187` at native RVA `0x00778EF7`. The WorldBuilder-backed parent
identity and its complete 1128-byte body were already matched. Its full EH
graph now proves this previously unrowed 10-byte cleanup, independently of
neighboring function addresses or byte-uniqueness guesses.

Native FuncInfo `0x009211F8` has one state: state 0 unwinds to -1 through
`0x00778EF7`. The parent allocates 0x28 bytes at VA `0x006F64A4`, saves the
pointer at `[ebp+8]`, activates state 0, calls the existing constructor at
VA `0x00763DC8`, and clears the state afterward. This matches the source's
`new Path` allocation lifetime. The cleanup passes that saved pointer to
scalar operator delete, native RVA `0x0002FD60`.

Complete raw COFF bytes: `ff7508e80000000059c3`.
Complete native bytes: `ff7508e8616e8bff59c3`.
The sole relocation is REL32 at +4 to `??3@YAXPAX@Z`.
Ghidra independently inventories a complete 10-byte unwind body at this RVA.
The following EH-handler stub is another COFF symbol, outside these 10 bytes.

Verified at BFME2 revision `b4ea340f90e40557a97edd18d5f7e5a4e6fc1206`. `proof.json` records source/object hashes,
the source's last commit, actual local symbol, native state table and full
byte/relocation proof. Source and compiler settings are unchanged.

Recheck the current source with the normal repository entry points:

```text
python3 tools/explain_mismatch.py '$L17187' --rva 0x00778EF7 --size 10 --source Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
./build.sh Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
python3 tools/eh_verify.py Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
```

The recorded source build verifies 89 existing rows.
Normal `add_match.py` admission passed at HEAD `6291db2de9`: the complete
source verifies 90/90 matched rows, with all string/float/import references green.
The new row awaits normal commit hooks.
Use the actual `$L` name with `gen-funclet;parent=<real parent>` notes so the
existing local-label resolver proves its exact parent EH location. No
`object-symbol=` alias, new pin, hand-written assembly, synthetic emitter,
source edit or baseline change is involved. These are natural lifetimes of
existing real C++ parents, not generated harness output.
