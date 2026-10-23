# Tree insertion provider repair, 2026-10-21

Parent bb1c2a5869; published census e20daa4e78, 2026-10-21 21:42.
StlSweepW4Rva0029FBC9.cpp held 136 matched bytes out of the legacy link
preview because its private element copy constructor had no provider.

Retail's insertion calls node creator 0029E11A twice. That creator allocates
32 bytes (16 link bytes, four key bytes, 12 value bytes), and its construction
call reaches 0041360E. Both workers already have rowed formation-preview
specializations in StlSweepW5Rva002A147E.cpp. The existing preview insertion
also shares this complete 136-byte retail body. This is provider repair, with
no new identity, symbol pin, ledger range or unique byte-coverage claim.

Correct the opaque value extent to 12 bytes and bind its node creation to the
existing preview tree worker. A declaration-only derived view exposes the
protected member; it adds no implementation or data. Preserve the opaque
application identity: native allocation and copy relationships establish the
compatible operation and layout, not an application class name.

The first trial forwarded pair construction instead. Its parent matched and
the legacy preview linked, but it emitted a 37-byte node helper where retail
has 34 bytes under these flags. That trial was discarded. The final direct
node-provider binding emits no such private helper. An intermediate converting
pair cast was rejected by MSVC; the final reinterpret_cast selects the exact
existing value layout.

Acceptance:
- link_check before: 0/136 B; after: 136/136 B, legacy preview.
- ./build.sh: full 136-byte row exact, literals and imports pass.
- Independently checked all three REL32 edges: offsets 41 and 66 reach
  0029E11A; offset 115 reaches tree rebalance 00025490.
- --prepare-current produced a strict reusable receipt; this does not prove
  closed-strict dependency closure.
- find_declared_unmatched and staged-peers new-variants shadow checks pass.
- Closed-strict gains and full-link runtime behavior remain unmeasured.
