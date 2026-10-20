# Shared STLport node allocator binding

At BFME2 6f04adc45b07f2f7a8f718111c06847ca9f9ced3, the four units in
proof.json fail only their extra __node_alloc<true,0>::allocate copy. An explicit
specialization declaration after the STL includes suppresses that copy and its
unused __stl_new helper. The external allocator resolves to the indexed shared
STLport definition (stlport_vector_int.cpp); this helper has no independent
retail address, so this is shared-definition binding, not a new identity claim.

Paired link_check evaluation replaces the same four objects in memory against
unchanged index 5366c4f808 (SHA256 in proof.json): 0 -> 2,797 nonpadding matched
bytes; AnimateWindowManager 1,724, BridgeBehaviorParseFX 190,
BridgeBehaviorParseOCL 170, FloodUpdate 713. All five blocking fields are empty
afterwards. Strict reusable receipts cover all four units; this is a legacy
index preview with self-strict objects, not closed-strict LINK evidence.
No census, link status, index or published object bundle was rewritten.

COFF comparison removes only allocate and __stl_new. Strong definitions and weak
externals do not change; the sole added undefined name is allocate, resolved by
the shared provider. All retained instruction bytes are unchanged. One helper,
BFMEAnimateWindowListPush::bfmePushBack, changes its sole relocation from
_M_allocate to allocate; its unchanged `push 12` always follows allocate's
small-node branch to that same _M_allocate. The exact bytes/relocations are in
proof.json. The preview has no wrong-selected definition or new COMDAT variant.
The existing helper fold pin is unchanged and is not asserted as new proof of
its identity. Every ledger body and its references still pass the byte gate.

Checks: ./build.sh on the four units (37/37 rows, literals/imports pass),
link_check.py --prepare-current on the same units, link_check.py before/after,
link_check.py --new-variants, class_gate.py, data_check.py --converged,
find_declared_unmatched.py. The paired facts include the original strict
objects saved before editing; no hand compilation or cache override was used.

## BFME1 freshness and donor review

Advance verified pointer 92f6bbe8e1dcdb46b5d27da0674313efc822b790 to official
master 01b84526fc8a43c9dea1cfe6abd0a6859b34eee5. Both full gates ran at the same
unchanged BFME2 revision above, before this repair: all 97,396 rows and 1,119
data entries passed at each pointer; no pre-existing failure or update regression.
The input/layout report verifies existing migrated game/ and inputs/ resolution
and the donor include directories. No headers/toolchain settings changed.

Refreshed bfme1_sweep scan/ranked/near: 5,513 independently matched boundaries,
zero free exact placements, zero ranked donor files; one 25-byte near lead is
outside this dedicated linking lane. lift_lane.py --limit 1000 ran. Compiled the
three changed clean donor TUs with place_bodies.py: zero body/pin placements;
none are silently imported or treated as target identity proof.

Reviewed BFME1 linking repair 3313189ad1571cb1612568ff84fc2c483b0ee9af
(PathfinderInternalFindPath constructor ownership): declaration-only reuse of
an existing shared definition applies here; its addresses and layouts do not.
Reviewed a411b334c and c54305633 as other name-ownership leads, with no additional
applicable change in these units. New donor commits change Money/Ghost transfer
bodies and census metadata rather than this allocator; none is copied here.

Recovery reconciliation (2026-10-20): upstream 30d4f04a9c independently repaired these same four units using visible forceinline allocator bodies. Kept all four upstream implementations unchanged when the publication rebase encountered the overlap. This recovered commit now retains the verified BFME1 pointer update and independent comparative evidence; the historical +2,797 B is not an additional gain over 30d4f04a9c. No allocator declaration from the old trial is added on top of the upstream implementation.
