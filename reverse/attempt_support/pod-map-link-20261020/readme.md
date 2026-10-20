# POD map provider reconciliation

The malloc-configured stlport_pod_map_bodies.cpp emitted an allocator-base
constructor unlike the bfmealloc copies in three siblings. Its existing pin
names native 0x0023E863, the 36-byte bfmealloc body; the pin evidence identifies
that native callee from the complete tree copy constructor at 0x003A299C.
Declare that base specialization in the malloc unit so callers use the
existing provider. No pin, type-layout or ledger changes are needed.

The same unit and TeamFactoryClear.cpp emitted competing tree destructors.
Declare the shared destructor specialization in these two callers. The
remaining generic definition remains visible in the constructor provider;
no new identity or retail address is asserted for the unrowed destructor.
Existing source comments retain target identity evidence and the limits of
the placeholder BfmePod8 semantic/key inference. No donor input changes.

Paired legacy link previews at census b73720bed9 (2026-10-20 05:34):
- map bodies: 0 -> 661 bytes;
- TeamFactoryClear: 0 -> 136 bytes;
- unchanged bfmealloc copy-constructor unit: 0 -> 404 bytes.
Together: 0/3 -> 3/3 units and 0 -> 1,201 bytes. The TeamFactory constructor
still has a separate primary-vtable conflict; it is not counted.

All 11 changed rows byte-match. Strict self preparation also passes all
17 rows across the three measured units. No new variants, undeclared
functions or CSV errors. These are legacy preview and self-strict results;
closure/full link/census have not been run or updated.

Shadow identity follow-up: removing the competing 33-byte base copy changes
the kept 36-byte copy's binding from divergent to wrong/unknown, not a proven
byte mismatch. Its alloc-proxy callee at 0x0014F3C4 has no known address; see
the constructor follow-up evidence. Shadow divergent iterator/allocator
helper findings remain. No closed-strict gain is claimed.
