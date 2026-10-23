# Terrain transfer height-data getter repair

W3DTerrainVisualXfer.cpp now marks its private WorldHeightMap::getDataPtr
imported and force-inline, as its width and height getters already were.
The matched transfer body already inlined the +0x24 field read; the ordinary
inline definition also emitted an unused, conflicting four-byte getter.
The change removes that COMDAT without introducing an import reference.

Base checkout: 46c93ac33370ef84d71bf5d2eac4ae6da88688b4.
The frozen local index measures a2839ea429, 2026-10-15 13:35 UTC, with census
5986a99448 at 04:52. This differs from the older committed link_status census
4b7e7091c4 at 12:36; the paired proof uses only the same frozen local index.
proof.json records index, source, object and receipt hashes. Before and after
objects have current strict reusable byte-verification receipts. Saved before
source/object/receipt and context remain under ignored
build/terrain-data-getter-link-20261015; proof.py consumes those snapshots.

The only removed nondebug section is the unused getter, 8b4124c3. All seven
retained COMDATs have identical bytes, extents and relocation digests. Every
other nondebug section, symbolic relocation target, external binding, weak
external and link directive is unchanged. No nondebug relocation targets the
removed getter. No class layout, compiler flag, pin, alias or ledger row changes.

Paired check_object checks independently refresh each object into copies of
the same index. The legacy local preview improves from two findings to one:
the getDataPtr COMDAT conflict disappears, while the unresolved
TerrainVisual::xfer remains. New authored bytes and predicted newly linked
bytes are both zero. Current strict compilation receipts establish the byte
gate; self-strict executable placement and closed-strict closure are unmeasured.
No census/index/link_status artifact was changed.

Target evidence is the unchanged complete 269-byte transfer at 0x000926EC,
its existing +0x24 height-data read, and the unchanged 68-byte shroud body at
0x00072988. ZH W3DTerrainVisual::xfer remains the established semantic donor.
This repair adds no identity or layout claim. The remaining base-transfer
reference targets 0x00306A9B, currently rowed under the neutral
Rva00306A9BDoXfer name; reconciling that provider requires separate evidence.

BFME 1 donor review: c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 suppresses
unused DamageInfo constructor copies, extending the imported-inline technique
in 53d32d6b4b377317a3397971629ca3ad20b870e9. The general repair is applicable;
its DamageInfo layout, addresses and ABI are not carried over. The related
66b19a8e95a4add525ef808fcea088e306798e2b Apt allocator repair supplies another
example. BFME 2's existing width/height getters supply the direct local pattern.
A search of local getDataPtr definitions found only a separate const,
unsigned-short getter in BaseHeightMapCellQueries.cpp; its different symbol
and ABI do not justify extending this exact repair.

BFME 1 master was fetched as 776c8123. The clean retained checkout/gitlink
remain a7c38d3b2597121f178ab5190b3062478823257d. Another live seat holds the
submodule update; comparative full verification remains outstanding. No
successful freshness stamp or reference pointer was changed here.

Acceptance:

- ./build.sh and before/after link_check --prepare-current: both matched
  bodies exact (337 bytes), strict reusable receipts, string/float/import
  checks pass.
- Paired object/link proof: one unused getter removed, all retained nondebug
  content unchanged, local legacy findings 2 -> 1, linked bytes 0 -> 0.
- Ordinary link_check reports only the unchanged unresolved base transfer;
  --new-variants passes.
- EH: zero EH-bearing rows, nonexact rows or missing objects. Enforced data
  check: zero findings. Converged data: eight addresses, no second names or
  unjudged rows.
- Frozen-file and class gates pass; check_csv and git diff --check pass.
  place_bodies reports zero additional bodies or pins.

No full link cycle, census build/measure/history, nightly or boot runner ran.
