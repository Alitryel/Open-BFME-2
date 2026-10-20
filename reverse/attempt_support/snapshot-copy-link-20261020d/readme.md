# Snapshot record copy provider

Parent: `8ab73492f5`; BFME 1 reference: `4483e88da1c2f3b9a273f779baac7458bd8bb891`.

`GameLogicInit.cpp` implicitly emitted `Rva0024076D`'s copy constructor.
That COMDAT did not match retail and competed with the already-rowed strong
copy in `Rva0024314ARecordCopy.cpp` (RVA `0x002419E2`, 188 bytes). The rowed
`_Construct` at `0x0024314A` (45 bytes) also selected the wrong copy. Declaring
the existing copy constructor in the caller's class view binds both units to
the verified provider. No class layout, compiler flags, pins or headers change.

The provider's existing reconstruction identifies a 0x50-byte record: AsciiString
at +0, Matrix3D at +4, words +0x34 through +0x40, list at +0x44, and words +0x48
and +0x4c. This repair uses that established target view; it adds no donor-derived
identity claim. The declaration-only single-provider approach is consistent
with the reviewed BFME 1 linking repairs (including `51b97cd79`).

## Acceptance

- Before/after `link_check.py` on all three units: legacy prediction 0 -> 233
  nonpadding bytes, comprising the 188-byte copy and 45-byte forwarding helper.
- `./build.sh Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp`: 174/174
  rows exact. Strict `link_check.py --prepare-current` receipts cover all 176
  rows in the caller, provider and forwarding helper.
- `proof.py` refreshes the same immutable published index with the same current
  provider cohort on each side. Only the caller's old/current object changes.
  It confirms that all 576 retained COMDAT hashes, and all retained nondebug
  section bytes, flags, definitions and relocations, are identical. Eight
  removed COMDATs are the implicit copy and helpers reachable only through it.
  Associative sections and symbolic SafeSEH membership are accounted for.
- `proof.json` records the index revision/hash, object hashes, removed names,
  paired blocker lists and measured gain. No closed-strict gain is claimed.

Run from the repository root:

```sh
python3 tools/link_check.py --prepare-current Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp Code/GameEngine/Source/Common/Rva0024314ARecordCopy.cpp Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0024314A.cpp
python3 reverse/attempt_support/snapshot-copy-link-20261020d/proof.py
```

The proof expects the pre-edit caller object at
`build/link-seat-20261020d/logic-before.obj`. The baseline source is available
with `git show 8ab73492f5:Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp`;
compile it through the normal gate with its unchanged source flags to regenerate
that object, then restore the repaired source and gate it again.

`GameLogicInit.cpp` itself still has independent unresolved methods, duplicated
definitions and other losing class/STL copies. Its bytes are excluded from the
gain. A whole-current-ledger check was attempted but refused a provider input
moving during enumeration; the paired legacy and self-strict results above are
the acceptance evidence. No full link cycle or census was run.
