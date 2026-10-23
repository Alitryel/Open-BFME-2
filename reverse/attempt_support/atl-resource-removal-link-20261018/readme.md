ATL resource-removal constructor ownership

Target: RemoveResourceInstance at RVA 0x628D36, 89 bytes. The ATL 7.1 constructor is owned by atlcomcritseclock.cpp at RVA 0x628CBE. The consumer already uses the same layout and constructor semantics, but emitted an optimized conflicting copy. An imported forceinline specialization retains the constant-false construction inline without supplying an external definition; unlike the nearby AddResourceInstance specialization, the throwing failure path is preserved.

Same-index legacy preview: 1/2 units, 120 bytes before; 2/2 units, 209 bytes after: +89 existing matched bytes linked. Canonical provider unchanged. Both current sources have strict reusable receipts and all 7 rows plus 6 named imports pass. This is self-strict byte evidence and a legacy index prediction, not a closed-strict link-cycle measurement. No authored byte growth.

Donor linking repairs reviewed at BFME1 8619c4c56d73; c42f040f demonstrates the same inline-visibility/external-ownership principle for ShareBuffer. This ATL repair uses existing BFME2 source and the neighboring AddResourceInstance approach; donor layout is not transferred.
