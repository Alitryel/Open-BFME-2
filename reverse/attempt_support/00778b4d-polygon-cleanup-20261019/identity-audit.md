# Polygon cleanup: unsupported tiny-fold certificate

Inspected HEAD `84c1bbd6731f8ddaad2a62791bc8f551cf37812f`; BFME1 gitlink `cf0a80c228583af789772b794ab27abcab2debbf`. Read-only audit; no tracked edits or compiles.

Native cleanup `$L1318` at RVA `0x00778B4D`, 28 bytes, calls `??1Rva00330C50Interface@@QAE@XZ` at `0x0057A243`. Its parent code/EH graph and all 28 bytes verify; the unresolved admission question is the callee identity certificate.

## Kept code and data evidence

`allowed_symbols.Identity.kept` selects the `Rva00330C50Ctor.cpp` object, exactly the existing pin's `fold-proof=` source. All three copies listed below have identical seven-byte raw code `c70100000000c3`, one zero-addend DIR32 at +2 to `??_7Rva00330C50Interface@@6B@`, and digest `a7b0ed983123`. Native code is `c70128eec600c3`. No divergent emitted destructor was found.

Each emitted vftable is a 28-byte read-only COMDAT (section flags `0x40301040`, value 0), with seven zero-addend DIR32 relocations to `__purecall` at offsets 0/4/8/12/16/20/24. No RTTI pointer is present. Native table RVA `0x0086EE28` contains seven `0x0043B810` pointers. `__purecall` is independently matched at RVA `0x0003B810`, 62 bytes, in `Code/Libraries/Source/debug/debug_purecall.cpp`. Full code and table contents therefore agree when those specific relocations are resolved.

- Source `Code/GameEngine/Source/Common/Rva00330C50Ctor.cpp`
  - Source SHA256 `a63bc7d50062b62b63f517edde55339d39422f1beb6aeb345e3f3dc46d393636`
  - Object `build/match/^code_^game^engine_^source_^common_^rva00330^c50^ctor.obj`
  - Object SHA256 `481b8d5d9f3be06a6243de8ae7a78e752ba8681efa4d0c4a5b7f6f0de401408b`
- Source `Code/GameEngine/Source/Common/Rva002E3EB8Permuted.cpp`
  - Source SHA256 `7580d7edd98de9ddd554e3126ac44a51fe3a94feb38697fce7fd0d7eaae59eb5`
  - Object `build/match/^code_^game^engine_^source_^common_^rva002^e3^e^b8^permuted.obj`
  - Object SHA256 `9d5804a2866e7161a090e4dc579fdea5526d587c9c09f77b4eb6a6f609dbd801`
- Source `Code/GameEngine/Source/GameLogic/Map/PolygonTriggerCtor.cpp`
  - Source SHA256 `9d0eeb14904ee1da32b0dd49012588e53d2ac3b6b08846d097c0d994f2fc399f`
  - Object `build/match/^code_^game^engine_^source_^game^logic_^map_^polygon^trigger^ctor.obj`
  - Object SHA256 `af5870fd7580ec8ea4152dd1dd98b0957de013642c8ba451d4e026267dcc4c57`

## Current policy blocker

Ordinary `RetailTruth._judge` returns `unknown` for all three copies because the external vftable has no admitted data binding. `allowed_symbols.py:383..425` tries ordinary truth before the fold receipt. The historical pin then fails the current intentional rule in `pin_admission.fold_proof_problems`: the seven-byte body has only three concrete bytes, below `build.MIN_LIB_CONCRETE = 8`; the tiny exception accepts only a five-byte zero-addend direct tail jump. This destructor is not that exception. The resulting shadow finding is `wrong / unknown`, not a proven machine-code mismatch. Do not weaken this rule.

There is no `data_rows.csv`, `dir32_addresses.csv`, or converged data owner for RVA `0x0086EE28`. The source-less `data_ledger.csv` inventory calls it `??_7VBase00C6EE28@@6B@`, with status `literal`, guessed size 208 and the interface table among aliases. That is not a verified owner or size receipt.

A formal implicit-vftable data recovery is currently unsupported by the ordinary data gate. Exact read-only calls returned:

```
data_rows._cpp_data_access("??_7Rva00330C50Interface@@6B@", allow_private=True)
    -> (None, None, False)
data_rows.compiled_size(Rva00330C50Ctor.cpp, "??_7Rva00330C50Interface@@6B@")
    -> (None, "??_7Rva00330C50Interface@@6B@ cannot be named from its TU")
```

`data_rows.py:355..367` requires a nameable C++ `sizeof` probe. `symbol_size` explicitly refuses using allocation extent as size. The 28-byte COMDAT extent cannot be forced into a data row, and introducing another data symbol/global would not certify this emitted vftable.

Recommendation: bank/remove the new cleanup row before publication, preserving its complete source and this code/data proof. A future dedicated verifier/data-recovery lane may address compiler-emitted vftable size/ownership with regression tests and the required Verifier-Change trailer. No new pin, class rename, alias, baseline addition, or tiny-rule workaround is justified.
