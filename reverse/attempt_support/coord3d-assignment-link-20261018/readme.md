# Coord3D vector assignment provider binding

FlightDeckBehavior, ParkingPlaceBehavior and OpenContain instantiated three
non-retail copies of vector<Coord3D>::operator=. The first two emit 273-byte
const-storage-pointer versions; OpenContain emits a 211-byte version. The
rowed 209-byte provider at 0x002CD098 uses the target-proven mutable storage
pointers and the independently rowed copy/allocate helpers. The object layout
is three pointers with 12-byte Coord3D elements; all consumers request the
same assignment operation. A declaration-only specialization before the
engine headers selects this existing real provider. No pin, alias, layout
change, compiler setting or shared-header edit is needed.

OpenContain no longer incidentally emits its rowed capacity helper when the
assignment becomes external. Its explicit instantiation retains the exact
existing body. All 12 matched rows across the three consumers and the provider
pass ./build.sh and paired strict preparation. Data enforce has zero findings,
converged data checks have zero second names at nine checked addresses;
new-variants, frozen-source and class checks pass. No EH rows apply.

Same-index paired local preview, census c2c5ac8c27 (2026-10-18 11:36),
index SHA256 90bd1bed6c06692963e0e6e96411614d502ca33f48b3e26d5338daaae99cf761:
StlportVectorAssignCoord3D.cpp 0 -> 209 legacy linked bytes. The three consumers
remain independently blocked (0 -> 0). This is not a self-strict or
closed-strict link gain. The index/status artifacts remain unchanged.

proof.json records every changed/removed COMDAT and object hash. The provider
and all retained FlightDeck/ParkingPlace COMDAT digests are unchanged. In
OpenContain, two unrowed bodies change: scatterToNearbyPosition assertion line
numbers move with the source; exitObjectViaDoor retains its instructions and
relocations with a larger local frame and corresponding stack offsets. It is
still independently non-retail and blocked, as before. No recovery is claimed
for either. The three wrong assignment copies and their unused copy helpers
are removed; no new COMDAT is introduced.

Baseline and final logs/objects are in build/coord3d-assign-link-20261018/.
The initial declaration after engine headers was rejected as already
instantiated; early includes briefly hit a missing then duplicate Coord3D
header. PreRTS already supplies the existing Coord3D view. The final early
specialization needs only <vector> and preserves the current class definition.
