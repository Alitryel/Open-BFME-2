# Consolidation handoff: FireWeaponWhenDeadBehavior.cpp

Shard 0/5 allocation check and scoped planner/check passed. The destination has 7 approved rows, 3 clean donor files and 2 mixed files. The unchanged merge dry run accepted no clean donor: `FireWeaponWhenDeadBehaviorOnDie.cpp` failed with `C2504: 'UpgradeMux' : base class undefined`; `FireWeaponWhenDeadBehaviorPoolKey.cpp` failed with `C2039: 'getModuleNameKey' is not a member of 'FireWeaponWhenDeadBehavior'`. Do not retry unchanged; the class declaration prerequisites belong to Sol.

The mixed `Rva00589079Derived.cpp` split for rows 0x00482BDB and 0x00482C39 was refused by hatch counter rule 3 because a copied helper or datum carries a hatch. The mixed `ConstIntGetters4.cpp` split for 0x00482E4B was accepted unchanged and applied; its 266 residual rows remain in the shared source, so this split produced no source-file reduction.

`./build.sh FireWeaponWhenDeadBehavior.cpp ConstIntGetters4.cpp` passed (269/269 matched rows); `find_declared_unmatched.py` and `check_csv.py` passed. Staged code identity and data identity reported zero findings. `tu_map.py --check-fresh` remains stale due to concurrent inputs; no full map regeneration was committed. No clean TU merge was available; net source-file reduction for this task is 0.
