# Malloc copy-family follow-up

Starting at b5d28bada3, the same two-unit legacy preview reports the
no-exception unit linking 1,162 real bytes and the malloc unit linking zero.
The malloc blocker list is the remaining copy/assignment families recorded
in readme.md, not the repaired 44-byte overflow.

Bind the 40-byte __copy call to its existing ledger owner at 0x00540082,
__copy<Rva00540082Element*, Rva00540082Element*, int>, using a visible
import-inline specialization of the old placeholder spelling. The retail
0x0054014D forwarder proves this callee; the named worker's source and bytes
supply its nontrivial assignment algorithm. The adaptation makes no further
claim about the element's underlying identity or fields. The forwarder's
29 bytes and both 40-byte erase bodies remain exact, with no new alias or pin.

Move only the three matched assignment/fill bodies (583 bytes) whose
8/16-byte typed-copy families remain inconsistent into the deferred malloc
unit, together with the associated unrowed 8-byte erase instantiations.
Keep the independent 8-byte const-copy forwarder, 16-byte erase, all 40-byte
members, and 12/44-byte operations in the original unit. Their compiler flags
and algorithms remain unchanged apart from the verified 40-byte helper bind.

An initial broader partition also moved the 40-byte erase provider, making
the already repaired no-exception unit unresolved in the legacy preview.
That partition was not counted or committed: the final change keeps the
provider and repairs its actual copy callee. This is why the paired preview
includes the no-exception consumer even though its source is unchanged.

Paired command before and after on these same two indexed units:
`python3 tools/link_check.py Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_bodies.cpp Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_malloc_bodies.cpp`
changes 1/2 linking, 1,162 bytes, to 2/2 linking, 1,599 bytes: +437 real bytes
(excluding 0xCC as progress.py does). The new deferred unit has no census
position and contributes no claimed linked bytes. This is legacy scope;
closed-strict closure and a fresh census were not measured.

Strict input preparation and full scoped byte gates pass for the two
providers and new deferred unit: 25/25 rows (13 + 9 + 3). The declaration and
CSV gates also pass. No shared headers, flags, data, pins or existing aliases
change. Donor input revision remains the verified pointer in readme.md.

The deferred 0x000B02B6 fill-insert calls 0x004C3121, while the size-only
Pod8 instantiation emits a different helper. The assignment bodies at
0x001D9BEE and 0x00538782 reach non-retail EH-enabled generic allocate/copy
and const-copy helpers instead of their target-specific no-EH copies.
They need their actual record copy contracts, not further stride-only aliases.
