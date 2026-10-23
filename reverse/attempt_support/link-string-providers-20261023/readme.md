# Record and tree shared providers

Base 2da4a2f1b3, published census b711de3634 (2026-10-23 14:28).
These are current-object legacy link previews, not self-strict or closed-strict
gain measurements. No census or full link runner was used.

NarrowStringRecordCopyBFME2.cpp: 0 -> 850 linked bytes. Declare the shared
string copy constructor and copy assignment helper instead of emitting their
private helper graph. Preserve the unit's rowed allocator cleanup at 46264A
with explicit instantiation. All 30 rows pass the byte gate. The copy and
assignment providers remain 81 and 41 linked bytes in the paired preview.
The first trial omitted that allocator body; explicit instantiation repairs
the missing symbol without changing any other row.

stlport_rb_tree_hint_0038d58c.cpp: 0 -> 1282 linked bytes. Declare the same
string copy constructor. Its rowed comparator388F39 directly calls the ledger
owner bfmeDoPW at24FC0 instead of instantiating a second _M_compare identity.
Retail's complete42-byte comparator passes four begin/end pointers to24FC0
and tests the result against zero. STLport4.5.3 supplies the comparison
semantics; the target instructions independently establish the ABI and callee.
Move the existing allocator specialization ahead of that explicit string use;
otherwise MSVC instantiates allocator before its specialization. All19 rows
pass, including both cleanup rows resolved through exact parent EH data.
Paired copy-constructor and comparison providers remain81 and191 linked bytes.
No new pins, aliases, flags, shared headers or allocator behavior were added.

The combined new gain is2132 bytes. The same-cause survey included narrow
ostringstream, VersionBlockParser, narrow num_put and wide money facets.
Their independent remaining blockers prevent extending this batch safely.
The donor review for this session is recorded with link-scene-getters-20261023.md;
this repair uses the existing vendored STLport4.5.3 declarations and target
calls, not an unverified donor pointer or transplanted layout.

## Ostringstream handoff

stlport_narrow_ostringstream_dtor.cpp, parent1F66C6/70, remains0/1195 linked.
The saved patch is the best byte-exact declaration trial, not a production fix.
It removes mutable-range-initializer and imbue conflicts. The emitted
uninitialized_copy<char*,char*> and private _M_assign_dispatch<char*> still
conflict with the kept copies. The imbue provider also retains its own public
_M_assign_dispatch conflict; it gains nothing in the paired preview.

Suppressing string copy/assign and imbue renumbers cleanup $L14561 to$L14475.
The existing row lacks gen-funclet; adding that token lets the current verifier
use its existing parent annotation. EH verification is2/2 EXACT and the full
unit is14/14 byte exact with this metadata. That trial still does not link.
Adding declaration-only assign<char*>(char*,char*) plus uninitialized_copy
then triggers MSVC7.1 C1001 at vendor/stlport/stl/_string.h:306
(compiler P2/main.c:148). Do not repeat that combination unchanged.
The declarations and ledger annotation were reverted; the original unit passes
14/14 again. No nonmatching source remains in Code/. The diagnostic patch
preserves the successful intermediate shape; the existing landed log entry
from metadata verification is superseded by the blocked follow-up.
