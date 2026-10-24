# Apt value allocator breakpoint intrinsics, 2026-10-24

Owner: Code/GameEngine/Source/Common/Rva006D29E0Cluster.cpp. Four existing
AptValueGCAllocator methods remain at the same addresses and complete extents.
Existing bitfield layout, mode byte, source assertions, method identities and
callee relationships are unchanged. No flags, ABI, pins or data definitions change.

Each completed row below is converted in its own commit. Genuine VC7.1
__debugbreak replaces the existing opaque INT3; no artificial volatile, register
constraint or instruction emitter is introduced. All four complete row bodies,
the owner data row and all14 string references are reverified after every step.
Normal add_match retains each row's existing notes and queues its landing receipt.

| RVA | Method | Complete bytes | Result |
|---|---|---:|---|
|0x6D2880|isAllocated|69|Bare breakpoint intrinsic; whole-file4/4 plusdata1/string14 exact.|
|0x6D28D0|allocator bitfield setter|92|Bare intrinsic at 1 existing breakpoint site(s); whole-file4/4/data1/string14 exact.|

The helper is also inlined into the171B reader; that reader retains its own
assembly until its separate conversion. Published-index link preview against
7e43384268 remains LINKS for the whole unit; the existing census metric is
reported in private build/gc-allocator/link69.log. No linked-byte gain is claimed.
These bodies already count as C++ coverage, so classification delta is zero.
