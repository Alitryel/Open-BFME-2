# Relation-map provider repair

Base b4a4af5524; published census 08160bc2c9 (2026-10-22 17:08).
Current unchanged RelationMapXfer.cpp preview: 0/577 linked bytes; unresolved
PlayerRelationHashMap::clear and int/Relationship hashtable resize/new-node.
The authored int subscript copy introduced the latter two dependencies.

Call the existing neutral Rva004DFC20::clear owner (1DBCDC) and the existing
ObjectLookupMap::findSlot owner (41F4E5) directly. This uses the same opaque
four-byte value carrier already established by this unit's copy helper.
The existing target rows and caller relocations prove these addresses and
receiver contracts; no new donor identity or payload type is asserted.

After: ./build.sh reports 4/4 exact rows, literals/imports pass; scoped
link_check reports 577/577 linked. Gain +577 bytes is a legacy census preview,
not closed-strict evidence. No pins or aliases added. The saved blocker map
has no other consumers of these three unresolved names; the related
PlayerCloneFrom iterator visibility blocker remains a separate cause.
