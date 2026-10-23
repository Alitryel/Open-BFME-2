# Armor rts constructor isolation

Base c5f98f213e; published census 456ce161c5, 2026-10-23 06:28,
retail-truth-4. Before editing, ArmorHashtableRtsCtor.cpp has 161 matched
bytes and a legacy current-object preview of 0 linked bytes. Its sole live
cause is the nonretail insert_unique_noresize provider pinned at 5472F8.

Keep the existing three constructor/EH rows in the original unit, explicitly
instantiating only the map default constructor. Move the 5474C3 (36 B) and
547547 (20 B) insertion wrappers to ArmorHashtableRtsInsertDeferred.cpp,
with unchanged compiler flags, declarations, view and original provenance.
The latter instantiates only insert. It remains deferred and earns no link
credit; the published index does not contain that new path.

The existing Armor identity is inherited, not newly established by this
repair. Native constructor facts and donor Armor.h provenance remain in the
original source. Existing MoveToGroupOrder banks at 5476C8 independently
warn that the insertion address is shared with an ObjectID/Coord3D spelling;
5472F8 still needs its real table layout/identity. Merely matching the two
outer wrappers does not establish the provisional Armor element there.
No alias, pin, name, layout or helper-body repair is claimed.

After: constructor unit LINKS 0 -> 105 B (64 + 31 + 10). This is a legacy
per-file preview, not self-strict/closed-strict closure or an executable link.
Both units pass 5/5 byte rows, literal/float/import checks, strict reusable
receipt preparation, class gate, declared-definition and new-variant checks.
EH verification reports zero applicable EH-data rows and zero unavailable
objects. Placement rescan finds zero additional bodies/pins. No shared
header, compiler flags, verifier or baseline changed. New authored bytes: 0.
Scratch receipts: build/link-seat-20261023c/armor-*.log.

This repeats the accepted BFME2 bucket-resize/camera isolation pattern.
BFME1 reviewed input remains 138757e9; upstream 21ef97bd is unchanged, with
pointer verification blocked as documented in link-reference-freshness-20261023.md.
