# Remove an unrelated donor initializer from the topple unit

At parent e1add84209 (plus three independent link repairs), the current
Object_Object_topple.cpp failed the published d08db10acb link preview with
`__imp_?__stl_throw_out_of_range@_STL@@YAXPBD@Z` unresolved and a competing
`_STL::bitset<117>::set(unsigned)` body. Its own matched coverage is 133 bytes.

The only occurrence of s_allWeaponFireFlags in Code/ is its definition in this
unit. It came from the larger donor Object.cpp, but Object::topple does not use
it. Its three MAKE_MODELCONDITION_MASK5 initializers emit the bitset setter and
range-error dependency. Remove this unused private table from the dedicated TU;
retain the donor provenance, includes and matched topple implementation.
No call, global, template alias, symbol pin or ledger entry was substituted.

Acceptance: ./build.sh on the unit passes both rows (123-byte topple and its
10-byte EH handler), including string/import checks. link_check.py
--prepare-current on the explicit unit passes 2/2 with strict reusable receipts.
Current-source link_check before: 0/1, 0 B; after: 1/1, 133 B. This is a
self-strict current-source preview against the published index, not a
closed-strict link cycle. +133 matched bytes link, +0 authored C++ bytes.

The indexed copies with the related bitset<117> specialization belong to
WeaponSet, GarrisonContain, W3DTerrainVisual, W3DModelDraw and
MobMemberSlavedUpdate. Their blockers and usages differ; no other occurrence of
the unused firing-mask table exists, so this removal is not spread to them.
