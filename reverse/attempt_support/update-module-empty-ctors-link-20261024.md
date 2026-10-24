# Empty UpdateModuleData constructor emitters

At BFME2 49f2095c11, both BridgeBehaviorModuleDataCtor.cpp and
LargeGroupBonusUpdateModuleDataCtor.cpp emit a conflicting empty
UpdateModuleData constructor. Same-index current-object link_check before
reports 0/212 B; after marking only those empty constructors dllimport and
forceinline, both link, 99 + 113 = 212 B. Index: 268f876e3b,
2026-10-24 02:54, retail-truth-4. This is a scoped legacy prediction;
no self-strict, closed-strict or full-image gain is claimed.

Retail parent bodies already expand the empty base construction. The change
retains that expansion and removes the conflicting standalone copy, using the
existing BfmeModuleData.h and AutoDepositUpdateModuleDataCtor.cpp precedent.
No class layout, member, destructor, vtable, pin or row changes. The scan of
remaining explicit UpdateModuleData constructors found no other unsuppressed
empty definition to sweep. The pre-existing destructor/interface reconciliation
in bridge-moduledata-link-20261023.md is not counted again.

Acceptance: build.sh passes all 6/6 rows and string/float/import checks;
eh_verify.py EXACT 2/2; find_declared_unmatched.py and git diff --check pass.
Both before/after link checks use the same two current objects and index.

Reference review: official BFME1 master 32774ab0, committed input f5140c1c.
Its recent string-accessor/link changes do not alter this empty-constructor
cause; the applicable inline-only precedent is already inherited locally.
The reference pointer is foreign-claimed and remains unchanged, without a
freshness success stamp. No maintainer-only runner or census build ran.
