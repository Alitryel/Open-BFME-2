# Empty-map constructor cleanup link repair

At baseline 6ddf0b5863, Rva00359290Dtor.cpp emits a non-retail NamedTimerInfo
tree destructor through its empty-map constructor view. Declare that member
so the rowed member views keep their own teardown and incidental EH code uses
the existing InGameUI tree provider. This does not identify the three actual
member map types: their key and value identities remain unknown.

Paired current objects on published census c2c5ac8c27 improve legacy predicted
linked nonpadding retail bytes 0->165, one unit clean. The 79-byte constructor,
86-byte destructor and two 11-byte unwind rows retain exact sections and
relocations. No added/changed COMDAT; nine incidental members disappear.
Every referenced removed name retains the same kept provider. No shared
header, pin, alias, layout or global change. proof.py uses saved before objects
in build/map-dtor-link-seat-20261018; proof.json records hashes and paired results.

All four rows pass, both parent EH graphs EXACT with verified label remaps.
Canonical InGameUICtor/InGameUIDtor providers pass 129/129 rows, six complete
STLport constructor folds, nine strings and nine floats, no skipped imports.
Strict receipts establish self-strict currency; closed-strict gain and full
link cycle remain unmeasured. Declared-unmatched, enforced data and diff
checks pass. The initial map destructor declaration was a no-op and discarded.

Dedicated donor review is recorded in ../template-helper-link-20261018/;
this repair relies on target row ownership and paired objects, not inferred
BFME1 application identity. A separate unsigned-byte vector declaration trial
changed its matched caller and was restored, recorded blocked and released.
