# Separate intermediate and root virtual lifetimes

The three button constructors at 5F589E, 5F5C77 and 5F5F2B install C7A630,
while their base destruction restores BC6F20. Giving both stores the root's
vtable name passed masked function matching but failed DIR32 consistency.

The existing Rva00567960BaseMid view names the intermediate table. Its first
slot points to the complete 28-byte deleting wrapper at 5FAA31; the native
REL32 at operand offset four calls the complete seven-byte 4E84A4 body, which
restores BC6F20. That wrapper's existing C++ provider also passes its own full
byte check. The three constructors now use this intermediate view. Its existing
destructor provider and the older 567CCD constructor adopt the same generated
header. The claimed root header and its provider's root definition are unchanged.

This is a minimum lifetime model for the consumed eight-byte prefix and one
evidenced destructor slot. The address-derived class names come from existing
source; original names, unused slots and the complete original hierarchy remain
unknown. The inherited word's pointer-versus-integer meaning is not asserted.

The class-contract tool compiled two eight-byte views but found an inherited
offset-four type tie. The saved automatic contract records that uncertainty.
The final contract inherits the registered root's storage once and adds no
second field. The standard header-adoption generator preserves the out-of-line
virtual destructor declaration. All five files pass header acceptance and their
whole-unit byte checks; all four parent exception graphs are EXACT. The scoped
DIR32 check passes 194 symbols, with root references only at BC6F20 and
intermediate references only at C7A630. An emitted-body rescan finds no further
bodies or pins.

Link prediction refreshed stale providers and predicts 0 -> 135 linked bytes
for the older constructor. The other four files retain unrelated callback,
holder, destructor and global blockers; there is no root/intermediate vtable
finding. This is prediction against the recorded census, not a whole-game link
or runtime result. No new unique C++ bytes, pins, aliases, baseline entries or
verifier-code changes are claimed.
