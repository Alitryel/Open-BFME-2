# SpecialPower consolidation binding blocked (2026-10-25)

Allocated destination: `Code/GameEngine/Source/Common/RTS/SpecialPower.cpp` (shard 0/5, unheld). The scoped planner snapshot was current. Dry run accepted `Code/GameEngine/Source/Common/Rva003B1101Dtor.cpp` unchanged (9 rows). Three other donors failed with `StringBase` redefinition errors; three protected donors were refused because their paths are keyed in protected registers. The accepted donor's existing `free:abi` Microsoft-header queue finding was refreshed and preserved at the destination.

The merge build passed (`./build.sh Code/GameEngine/Source/Common/RTS/SpecialPower.cpp`: 9/9 functions, exact funclet pins) and `find_declared_unmatched.py` passed. The staged checks passed for `link_check.py --staged --new-variants --shadow` (0 of 1 TUs compiled), `tu_ownership.py --staged --shadow`, `data_check.py --staged --converged` (10 addresses, no second names), `eh_verify.py` (one exact row), and case-collision checks.

The commit hook's shadow identity check found one new binding:

```
code identity: binding: Code/GameEngine/Source/Common/RTS/SpecialPower.cpp | Unwind@00b8202e | ??1?$StringBase@D@@QAE@XZ | 0x0048BA39 | wrong
```

Because this changes the selected provider for unwind metadata and needs manual provider investigation, the merge commit was not published. I reset only that unpushed trial commit, restoring the donor and original path-keyed rows, and released the destination, donor and moved-row claims. No source, ledger or register change from the trial remains. Sol should compare the prior and composed unwind/provider bindings before considering this TU again.
