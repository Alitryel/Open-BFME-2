Publication reconciliation: upstream ecdbfc26d3 independently repaired this
unit with native cosf/sinf expressions before this seat published. The upstream
source passes the ordinary byte gate (6/6 current rows) and link_check.py
predicts LINKS, 1,879 nonpadding bytes. The additional wrapper-localization
edit is redundant and has been removed. This rebased evidence-only commit
claims zero additional linked bytes. Historical paired proof follows; its
original source variant is no longer the checked-in implementation.

MetaImpactNugget CRT-wrapper linkage repair (2026-10-21)

The published census at 2b4d1fb42a predicts MetaImpactNugget.cpp cannot link
because its unproven float cos/sin COMDATs differ from the selected retail
copies. Restricting math.h's inline wrappers to this translation unit preserves
their inline expansions and removes the competing external definitions. This
uses the established math.h inclusion pattern in TextureMapperApply and other
matched BFME 2 units; it does not change a shared header or the retail providers.
The other two units with this blocker also have unrelated blockers, so this
change alone would not link them and they are left for their larger repairs.

Before and after: link_check.py on the consumer predicts 0 -> 1,879 linked
nonpadding bytes (4 rows, including an unwind funclet). Both consumer and
AptMathCallbacksBFME2.cpp provider passed --prepare-current strict byte checks
(4 and 20 rows respectively); ./build.sh consumer also passes all rows, data,
strings and floats. find_declared_unmatched.py passes; --new-variants reports
no new variants. This is a legacy preview with self-strict current objects,
not a measured closed-strict link result.

proof.json records the unchanged census hash and paired before/after provider
and consumer checks. proof.py compares objects saved before the edit under
build/meta-link/before against the current object. All retained COMDAT hashes
and sizes agree; after excluding the eight CRT wrappers, every non-debug
section's bytes, flags, definitions and normalized relocations agree. The same
eight wrappers now have static linkage, and retained sections have no incoming
references to them. The proof refreshes only an in-memory copy of the index.
To reproduce, build the parent source, save its object under that directory,
restore/build the repaired source, prepare the provider, then run proof.py.

Donor review: verified BFME 1 5987fd1b859e86801d093256eadc6fb63d87785f,
including its native wrapper/base-class linkage patterns. The repair and byte
claims above are established from BFME 2's own objects and retail checks.
