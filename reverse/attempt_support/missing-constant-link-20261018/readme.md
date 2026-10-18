# Missing constant definitions, 2026-10-18

The frozen published index at c2c5ac8c27 reports one undefined data name in each
of two otherwise linkable units. Define those existing names in their consumers
and row their complete retail data in `reverse/data_rows.csv`:

* `Rva0053805DBaseCtor.cpp`: external float at RVA 0x008691E8, four native
  bytes `90 C2 75 3D`, exactly 0.060000002384185791 (one ULP above `0.06f`).
  Define it after the constructor so the existing external load is preserved.
* `INI_Rva0033940FParse.cpp`: ThingTemplate diagnostic at RVA 0x0080EA88,
  29 bytes including the newline and NUL, already passed to Debug::Format.

These are target data and existing address-derived names. Original global
names and the float field's semantic meaning remain unknown. No donor layout
or new code identity is claimed. First verification caught the rounded float
and a diagnostic extent excluding the NUL; the exact values above pass.

The paired frozen-index prediction goes from 0/2 to 2/2 clean, **+385 B**
(149 + 236; the first includes its 10-byte EH handler and excludes padding /
funclet scoring). `proof.py` checks strict reusable object receipts and proves
that every retained nondebug section, COMDAT, section flag, external definition,
and symbolic relocation is unchanged. The only new sections are the two data
symbols. Byte verification passes all four existing code rows and both data
rows, including sizeof-based extents and all initialization bytes.

This is a legacy link prediction with self-strict input currency. No full link
or closed-strict gain was measured. `data_check` debt is compared before/after;
existing address-identity findings remain separately recorded by the proof.
No verification runner or census was launched. Baseline snapshots and the
frozen-index digest are under `build/missing-constant-link-20261018/`.

The commit hook reports existing code-identity shadow debt in the constructor
cleanup funclet `rva00797832`: its `VBase00C6EE28` destructor binding at
0x0057A243 is wrong. The retained-object proof includes the complete funclet
and its symbolic relocation, so this change preserves that finding. This is
another reason the legacy prediction does not establish closed-strict closure.
