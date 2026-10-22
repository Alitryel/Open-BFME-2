# Queued-icon range cleanup linking repair

At BFME2 3de7cd797f, using the published census at 08160bc2c9
(2026-10-22 17:08), paired current-source previews of
`StrategicInGameUIBuildQueueUnitQueued.cpp` and
`StrategicInGameUIBuildQueueIconSelect.cpp` give **0 -> 975 linked bytes**.
This is a legacy preview gain, not a closed-strict measurement.

The queued observer emitted incompatible `_Destroy<Rva005E71C6Ref *>` and
`__destroy_aux<Rva005E71C6Ref *>` copies. The icon-selection unit already owns
the native 24-byte false-type range dispatch at 0x005E7FB0. A declaration-only
specialization makes vector exception cleanup call that existing provider.
The queued observer's copy/assignment code and intrusive-reference semantics
stay byte-exact. This uses the existing target-established type and provider;
it adds no identity claim. The other indexed consumer of this cleanup family,
`StlportVectorInsertOverflowFamily.cpp`, has 43 independent blockers, so it is
not a useful extension of this repair. Unreferenced single-object cleanup
copies are left alone under retail-truth-2.

The specialization renumbers compiler-local `$L` labels. Five existing rows
had only raw labels and prose identifying their parent. Their notes now record
`gen-funclet;parent=...` for that same parent, without renaming the rows or
adding object-symbol aliases. All three parent EH graphs are EXACT; the normal
byte gate locates all six renumbered cleanups through the native EH graph.

Acceptance:

- Queued observer: 15/15 complete byte rows; strings, floats and imports pass.
- Unchanged icon-selection provider: 72/72 rows and literal/import gates pass.
- EH verification: 3/3 EXACT in the changed unit.
- Declared-definition, class and CSV checks pass.
- `link_check.py --prepare-current` refuses the changed unit because its include
  inventory has unknown macro/parent-traversing search roots. No self-strict
  receipt or closed-strict closure gain is claimed.

Local diagnostics: `build/seat-ui-destroy-{before,after,byte,provider,eh,strict}.log`.
The original source is preserved in `build/seat-ui-queued-original.cpp`.

Other trials recorded alongside this repair were restored: opaque narrow-string
construction in money_put changes the native stack frame, and imported tree
constructors in AssetManager refresh expose unresolved inline dependencies.
Their concise attempt records describe the failures; no nonmatching source is
left in Code.
