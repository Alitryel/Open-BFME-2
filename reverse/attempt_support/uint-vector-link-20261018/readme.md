# Unsigned-vector lifetime link repair, 2026-10-18

HeroTransfer.cpp previously emitted a competing vector<unsigned int> allocator constructor. The census kept the rowed /Od provider at RVA 0x25100. Retail SelectRandomHero instead inlines the vector wrapper and calls the existing base constructor at 0x211E58.

Keep the STLport constructor body visible as a dllimport forceinline specialization and declare the already-pinned base constructor. This suppresses the competing wrapper without changing the native call, stack frame, random-selection behavior or exception cleanup. No pins or identities changed.

Acceptance: both HeroTransfer rows pass strict byte verification with reusable receipts, including the EH handler; the source literal also passes. Legacy link preview against census c2c5ac8c27 changes from 0 to 280 existing matched bytes. This is self-strict provider evidence plus a legacy index prediction, not a closed-strict result or a full link cycle. Unique authored coverage does not grow.

The same blocking name was swept through other eligible sole/near siblings: list_create_node_vecuint, GeometryUpgradeModuleDataCtor and LightPointSystem. Their attempts alter stack or exception-state shape and were restored, recorded and released. Remaining multi-blocker siblings need distinct prerequisite repairs. Sources already owned by other workers were left alone.

Donor review and the BFME1 freshness blocker remain as recorded in ../coord-record-link-20261018/readme.md. This target repair uses the checked-in STLport header and existing target callees; no donor address or layout was imported.
