# Separate the two false map families before reconciliation

Read with map_int_asciistring_fake_family.md. Inputs: BFME2 51c500ec7c,
BFME1 32774ab0, MSVC7.1. No production source, row, pin or metadata changed.

The prior handoff's blanket AsciiString -> Rva0050055D plan is too broad.
Native 50116B allocates a 44-byte node and calls Construct 500CFE, pair copy
500839 and the existing 24-byte holder copy 50055D. Those establish family A,
pair<const int, Rva0050055D>, independently of the old fake type spelling.

Native clone 5041D8 instead calls node factory 5041B6. That factory's Construct
copies the seven dwords of Rva00064640Record28 (constructor 64640). This is a
different family B. Clear 2B70B3 already has a genuine record-set owner in
Rva00064640Insert.cpp, alongside its fake int/AsciiString spelling in
WOLBuddyOverlay.cpp. Classify remaining functions by native element operations
and relationships; do not propagate A's holder type through B merely because
the current template names agree. Full allocator/comparator identities remain
unresolved.

Two isolated A helpers compile exactly with production /O1 /arch:SSE /G7:

* _M_create_node<HolderPair>: 34 bytes, native 50116B, every relocation exact.
* _Construct<HolderPair,HolderPair>: 45 bytes, native 500CFE, every relocation
  exact when the proper pair copy specialization is declared out of line.

The trial uses a 24-byte Rva0050055D declaration with its existing copy ctor,
an opaque HolderPair _Construct declaration in the factory unit, and an opaque
HolderPair copy constructor declaration in the Construct unit. The source
contexts are stlport_rb_tree_copy_0052D25D.cpp and Rva00566695Assign.cpp.
The sibling .py.txt preserves the exact isolated experiment. Scratch compilation
must retain the production path's flag defaults; copying only // cl: loses them.

These are diagnostic byte results under a temporary symbol map, not admission
proof, completed identities or linking gain. A coherent repair must reconcile
the existing false rows and pins with tombstones, preserve B separately, prove
the genuine four-byte AsciiString chain, and gate every provider and consumer.
No blind rename, second name at an occupied address or shared-tool edit is
authorized by these results. All claims from this investigation were released.
