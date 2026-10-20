# AssetManagerImpl::LoadAsset: verified integration of the 2780-byte bank

Target: `?LoadAsset@AssetManagerImpl@@QAEXPAVRva009EF0D0Element@@@Z`,
RVA `0x00623600..0x006240DC`, including the seven-entry phase table at
`0x006240C0`. Source: `Code/Libraries/Source/assetmanager/Rva00622290CollectKeys.cpp`.
Starting BFME 2 revision: `a684fce91d9820129a7e2c4f765ff8a2b6699d9f`;
reference checkout matches the pinned BFME 1 revision `4483e88da1c2f3b9a273f779baac7458bd8bb891`.

## Prior work used

Read the attempt-log history and the bank before editing. The key handoffs are
`0x00623600-loadasset-20261020-w3.md` and
`0x00623600-loadasset-20261020-w5.md` in this directory. They already establish
the frame layout and compiler-visible field qualifiers needed for the exact
body. This integration does not claim those compiler discoveries as new work.

The WorldBuilder lead at `0x0167B5C0` supplies the method name. The BFME 1
`0x009F0FA0` donor supplies the phase-machine lead; BFME 2 retail supplies the
target layout, DX8 waiting, demand-load logging, profiling and call targets.
The asset element retains its existing opaque name rather than inventing a
retail class identity. Donor naming is not treated as independent target proof.

## Last blocker and its proof

The bank's only unresolved calls were to
`??A?$deque@HV?$allocator@H@_STL@@@_STL@@QAEAAHI@Z` at `0x00620F10`.
The address is already owned by the non-const deque iterator's `operator[]`.
The deque's start iterator is at offset zero, explaining the identical bodies.

First verified every existing row of
`Code/Libraries/Source/WWVegas/WWLib/stlport_deque_int.cpp` (23/23). That matched
provider also emits the deque operator, so the fold proof can use an existing
owner rather than depending on the new unit having landed first.
`pin_admission.py --add` accepted the new binding with that source as
`fold-proof=`: the whole 76-byte body and resolved relocation graph satisfy
the normal admission check, including the call to `_M_advance` at `0x006202E0`.
`pin_consistency.py --symbol` independently reports the binding consistent.
No alias row, alternate-name directive or verification exception was added.

## Integration and validation

- Initially verified the bank in a standalone unit. `flag_defaults.py propose`
  independently confirmed that the region default loses the row. A new override
  would trigger a full repository gate, so the final placement shares the existing
  key-collection unit and its established `/O2 /G6 /arch:SSE` override. The
  temporary standalone source and override are removed; no flag table changes.
- Kept the bank's imported CRT declarations before the shared headers. The
  opposite order lets the shim/header include guards retain earlier non-import
  declarations, producing a 2800-byte LoadAsset instead of retail's 2780. With
  the import context preserved, both complete functions and all existing EH
  cleanup rows remain exact. This is a translation-unit visibility finding,
  not a claim about the retail source's original file organization.
- Replaced three stale bank global spellings with the data ledger's
  `g_00E09B08`, `g_00E09A00` and `Debug *theDebug`; the private debug interface is
  a view cast at the call sites. The function remains byte-exact.
- Normal scoped byte build: 6/6, including all 2780 LoadAsset bytes and its table;
  18 nonempty strings plus one empty reference, five floating-point literals
  and 20 named imports verified for the combined unit.
- Final shared-unit `eh_verify.py`: EXACT 2 (both parents), zero missing
  objects or baselined mismatches.
- Three key-collection cleanup labels renumber after integration: `$L10281`,
  `$L10282`, `$L10283` become `$L13117`, `$L13118`, `$L13119`. The normal byte
  verifier proves their placements from the unchanged parent EH graph at
  `0x007A75C0`, `0x007A75C8`, `0x007A75D0`; it reports these renumberings rather
  than treating a label's spelling as independent placement evidence.
- `data_check.py --enforce`: zero findings; enforced converged-data check:
  zero second names and zero unjudged rows.
- `find_declared_unmatched.py` and `class_gate.py` pass.
- Published-index COMDAT admission is checked against census `3f413ed3ff`
  (2026-10-20 18:52 UTC). This is admission against existing providers, not a
  new census or a claim that this unit is fully linked.

`add_match.py` records the verified landing and removes the old bank. The
earlier handoffs stay tracked so future work retains the failed experiments
and the explanation of the successful compiler shape.
