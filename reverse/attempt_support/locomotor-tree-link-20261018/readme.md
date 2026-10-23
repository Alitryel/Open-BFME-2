Locomotor tree provider reconciliation, 2026-10-18

Baseline: 0f98e122cd; published census c2c5ac8c27 (retail-truth-2).
The before and after legacy predictions include the same four current providers:
LocomotorSetMapSubscript.cpp, LocomotorSetMapInstantiation.cpp,
LocomotorSetMapThunks.cpp, and stlport_locomotor_map_copy.cpp.
Before: 0/4 clean, 0 bytes. After: 2/4 clean, 390 bytes (275-byte thunk unit
and 115-byte copy unit). The two instantiation units retain independent blockers.
No authored C++ coverage increase, no closed-strict or full link-cycle claim.

Target evidence: assignment RVA 0x004FFDA5 is 115 bytes. Its relocation at
+0x0D calls clear RVA 0x004FF49F, while the existing typed clear ledger row
owns 0x0026DEE4. Its +0x38 call reaches _M_copy at 0x004FFD09. The existing
Rva004FF3DB::rva004FF49F owner supplies the actual clear address. The explicit
assignment keeps STLport's established algorithm, changing only that named call.
The two map-instantiation units no longer emit competing _M_copy definitions;
the subscript unit also reuses the assignment provider. No pins or aliases added.
Original application/container identities remain as uncertain as in prior rows.

Acceptance: self-strict preparation of all four providers passes 33/33 function
rows, with no string, float or import-reference failures. The two edited sources
pass find_declared_unmatched; check_csv passes (96663 function, 15993 symbol,
961 data rows). Both helpers already have complete ledger rows. The assignment
annotation names its actual existing row through its source typedef.
