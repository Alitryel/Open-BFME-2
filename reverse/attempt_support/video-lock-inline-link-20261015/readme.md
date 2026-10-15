# Video-buffer device-lock constructor emission repair

Base: 0616cac0df20fe9322912e52a75f12ab7e8c995e. The current
W3DDisplayCreate_W3DDisplay_createVideoBuffer.cpp emitted an unused 12-byte
BFMEDX8DeviceLock constructor COMDAT (digest 5e4f5b69cb40). It differed from
the census's first copy, digest 07867f503b83. All 56 other indexed copies
use that first digest; the video-buffer unit is the sole different emitter.
No retail constructor identity or standalone constructor recovery is claimed.

Mark this local constructor imported forceinline. Its existing call to
W3DRadarResetLock remains inlined in createVideoBuffer. This is the emission
strategy reviewed in BFME 1 c1315665a1b22beb7e6d9279548fe5b1c26ed1f9
(DamageInfo), applied using BFME 2 object and byte evidence. No donor class
layout, address or ABI is imported. No shared header, pin, row, flag, baseline
or data declaration changes.

The paired proof loads the same frozen ac77c85054 index (2026-10-15 14:25;
SHA256 in object-proof.json), refreshing only this unit in memory before and
after. One losing-COMDAT finding disappears and this unit becomes clean in
the local legacy preview: 0 -> 258 existing nonpadding matched bytes.
Authored C++ byte growth is zero. Self-strict current receipt checks cover
the edited object. External dependency closure remains legacy; closed-strict,
full-link placement and runtime gains remain unmeasured. Neither index,
link_status nor census history was changed. No maintainer-only runner ran.

proof.py proves that only the unused constructor section disappears. No
nondebug relocation references it. Every retained nondebug section, flag,
definition, byte and symbolic relocation is identical, including the two
retained COMDATs and EH data. The compiler renumbers a local cleanup label;
the ordinary gate resolves the existing funclet through the exact parent EH
graph. No label, row or ownership workaround is added. Data-reference facts
are identical before and after.

Acceptance: strict prepare-current before and after, and ./build.sh, pass
3/3 rows. EH: 1/1 EXACT, zero missing objects. String/float/import checks have
zero skipped references. Local link_check passes 1/1. Data enforcement has
one unchanged baselined wrong-name finding (TheW3DRadarFormatCaps at RVA
0x009EDA7C), zero outside baseline; converged-data checking has zero second
names or unjudged rows. Frozen definitions, class gate, CSV and whitespace
checks pass. New-variant comparison adds no variant. Placement resweep:
zero bodies, zero pins. Normal commit hooks remain required.

Reproduction needs ignored build/video-lock-inline-link-20261015/before
(source/object/receipt snapshots) and its context.json. The committed JSON
preserves the original/current object hashes, measurement receipt, paired
findings and scoped byte total. Run proof.py against those snapshots and
unchanged index after strict preparation of the source.

BFME 1 freshness remains outstanding: official master was fetched at
49d66824; the verified gitlink/checkout remains a7c38d3b. Another worker holds
file:reference/open-bfme-1. Controlled old/new-input verification and pointer
update remain with that scope; no success stamp or pointer advance is made.
Discovery checked repair_queue.py link, link_rank.py (general, near, A and L),
and current local previews. Several top-ranked items are already repaired
since the census; unrelated deferred bodies were not retried.
