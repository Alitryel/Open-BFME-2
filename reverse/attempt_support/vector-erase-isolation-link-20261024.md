# STLport erase provider isolation

BFME 2 parent 50dc98bcdd; published census 11b3872700, 2026-10-23
23:06, retail-truth-4. Before editing, StlportVectorEraseRangeFamily.cpp
has 54 unresolved helper references and one wrong-selected _Destroy copy
(BfmeAssignRecord104). Its current-object legacy preview excludes all
3,346 matched bytes. These dependencies belong to 36 distinct element views.

Move those views' explicit template instantiations unchanged into
StlportVectorEraseRangeDeferred.cpp and repoint their 67 ledger rows
(2,630 B). Keep the ten independent erase/helper instantiations and the
W3D helper bodies in the original unit: fifteen rows, 716 B. Both units
retain the original generic definitions, declaration-only element views,
compiler flags and native evidence table. No type equivalence, callee
identity, element layout or new pin is inferred from matching bytes.

After: original unit LINKS 0 -> 716 B. This is a legacy per-file preview,
not self-strict or closed-strict closure or an executable link. The new
unit is absent from the published census and receives zero link credit;
its unresolved and wrong-selected providers remain repair prerequisites.
The chain-pool isolation note documents the same selection rule.

Acceptance: 82/82 bodies byte-exact with strict reusable receipts;
string/float/import, CSV and declared-definition checks pass. EH EXACT 1/1
for the W3DHordeModelDraw helper. Variant admission passes; normal hooks
also check class, identity and data. Scratch outputs and the exact selected
type list are in build/link-vector-erase-isolation/. New authored C++ bytes:
zero. No verifier, baseline, shared header or donor inputs changed.

The preceding chain-pool commit's shadow reports re-key seven existing
present-unmatched markers and seven known wrong-binding findings to the
new deferred path. The definitions and findings themselves were already
present; they remain explicit repair debt, and no admission baseline was
expanded. Its scoped byte, data, identity-admission and link checks passed.
The reference review/freshness prerequisite remains as recorded in
opaque-sibling-isolation-link-20261024.md.

Recovery at 8847b96bb5: preserve upstream native-provider rehomes for
eight moved rows (0x4CD7C, 0x4CD20, 0x2B4410, 0x565A94..0x565AC0),
rather than restoring their older deferred claims. Eight duplicate keys
caused the previous push failure. The current indexed original admits
614 B, with zero baseline linked bytes, in the legacy preview; the earlier
716 B figure belongs to the original ledger. No strict closure is measured.
