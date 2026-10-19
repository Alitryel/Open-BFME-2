# PolygonTrigger virtual-base cleanup

This cleanup is banked and has no matched ledger row. Its complete native
bytes and parent exception graph are exact, but the kept destructor is
not ordinarily certified until its virtual table has a verified data
home. The intentional tiny-fold rule does not admit this seven-byte
vptr-store body, and the data verifier cannot currently prove the size
of an implicit compiler vftable. See `identity-audit.md` for the exact
blocker, whole code/table evidence and future prerequisite.

Both existing clean C++ PolygonTrigger constructors install native handler
`0x00778B87` and FuncInfo `0x00920CA0`. The 158-byte two-argument constructor
at `0x002E3FAB` and the 166-byte one-argument constructor at `0x002E3EB8`
independently match their complete native bodies and complete EH graphs.
State 0 unwinds to -1 through the same native cleanup at `0x00778B4D`.
The admitted row uses only the two-argument constructor's actual `$L1318`
from `PolygonTriggerCtor.cpp`; the second parent is corroboration, not a
second alias row.

The cleanup tests construction flag bit 0 at `[ebp-0x10]`, clears it when
set, adjusts the saved receiver by 0x60, and tail-jumps to native RVA
`0x0057A243` through the existing fold-proven destructor spelling
`??1Rva00330C50Interface@@QAE@XZ`. That base's address-derived name and
layout view are inherited from existing verified sources; this recovery
does not establish an additional original base-class identity.

The whole native extent is **28 bytes**, not the first 27-byte COFF-label
slice. The conditional jump at +6 targets a genuinely emitted `RET` at
+27. The same associative `.text$x` section contains that byte under
`$L1319` (two-argument source) or `$L1360` (one-argument source), and each
parent's exact relocation graph places it at `0x00778B68`. The next cleanup
starts at +28. Ghidra independently inventories 28 bytes. No padding byte
or neighboring-parent inference supplies the return.

Complete raw COFF bytes:
`8b45f083e0010f840f0000008365f0fe8b4dec83c160e900000000c3`.
Complete native bytes:
`8b45f083e0010f840f0000008365f0fe8b4dec83c160e9db16e0ffc3`.
The sole relocation is REL32 at +23 to the existing destructor.

Verified at BFME2 revision `b4ea340f90e40557a97edd18d5f7e5a4e6fc1206`. `proof.json` records source/object hashes,
the source's last commit, actual local symbol, native state table and full
byte/relocation proof. Source and compiler settings are unchanged.

Recheck the current source with the normal repository entry points:

```text
python3 tools/explain_mismatch.py '$L1318' --rva 0x00778B4D --size 28 --source Code/GameEngine/Source/GameLogic/Map/PolygonTriggerCtor.cpp
./build.sh Code/GameEngine/Source/GameLogic/Map/PolygonTriggerCtor.cpp
python3 tools/eh_verify.py Code/GameEngine/Source/GameLogic/Map/PolygonTriggerCtor.cpp
```

The recorded source build verifies the existing constructor row.
Historical `add_match.py` byte admission passed at HEAD `36fa081545`: the complete
source verifies 2/2 matched rows with all reference checks green.
Use the actual `$L` name with `gen-funclet;parent=<real parent>` notes so the
existing local-label resolver proves its exact parent EH location. No
`object-symbol=` alias, new pin, hand-written assembly, synthetic emitter,
source edit or baseline change is involved. These are natural lifetimes of
existing real C++ parents, not generated harness output.
