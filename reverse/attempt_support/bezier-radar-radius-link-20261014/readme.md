# Projectile and radar radius-helper linkage repair

Base checkout a2db31d873625dcdfbcc5c6b60e57125e4f4a28c. Runner measurement
index: 147cfae2cb, 2026-10-14 07:27; its SHA256 is in object-proof.json.
The newer committed link_status.csv queue measures de7bb30890 and serves
as discovery evidence only. Index, status and history remain unchanged;
no per-row data-back artifact or ranking was used.

The private GeometryInfo views in BezierProjectileBehaviorUpdate.cpp and
W3DRadarRenderObjectList.cpp emit getBoundingCircleRadius as `d94110c3`,
reading +0x10. Nine indexed copies, including the first PartitionManager copy and the
strict-current StickyBombUpdate.cpp witness, read
+0x18 (`d94118c3`). These two consumers are the only indexed divergent
copies. Neither helper body has a retail address, ledger row or pin.

Retain the +0x10 operation proved by the matched callers, and rename these
implementation helpers to projectileCollisionRadius and radarCircleRadius.
The matched callers are Bezier update at 0x0045C226..0x0045C812 and radar
render at 0x00050125..0x0005053E; the radar EH handler is also retained.
The Bezier ledger's independent WB debug twin and native object-access
proof establish the caller identity; the existing radar row establishes
its retained rendering implementation. Whole-body gates establish the
unchanged compiled operations. The new helper spellings assert neither a
retail method name nor a canonical GeometryInfo layout. No flags, ABI,
layout, globals, headers, pins or ledger rows change.

Acceptance:

- Before/after bounded link_check.py --prepare-current prepares both
  consumers with strict reusable receipts. Independent ./build.sh passes
  all three rows (1516B, 1049B, 10B ledger extents), ten float literals and
  one named import. No string baseline or skipped reference is used.
- All 601 retained external COMDAT bodies have identical bytes, extents,
  digests and normalized relocations; both renamed four-byte helper bodies
  also remain identical. All 622 nondebug sections match after normalizing
  just the helper names, including local code/data and relocation targets.
  Strong, undefined and weak bindings and row-level data facts are unchanged.
  Complete retained digests, strict-currency flags and source/object hashes
  are recorded in object-proof.json. Historical objects were checked under
  their actual cache basenames, preserving the index's ownership mapping.
- StickyBombUpdate.cpp passes its two-row byte gate and strict receipt
  preparation. Refreshing only this provider witness and the before/after
  consumers in memory against the SAME index reduces legacy findings from
  2 to 1 in Bezier and from 7 to 6 in radar. Provider findings are unchanged.
  The stock link_check.py independently confirms both radius conflicts are
  gone. Legacy LINKED bytes remain 0 -> 0; both consumers still fail closure.
- EH is EXACT 2/2, with no baseline or missing object. Frozen definitions,
  class gate, new-variant admission (shadow), CSV and whitespace checks pass.
  Enforced converged-data checks cover eight addresses with zero second
  names or unjudged rows. Shadow data checks have zero findings; before/after
  data facts and findings compare equal. Placement resweep finds zero bodies
  or pins. See checks.txt for bounded check output.

Remaining Bezier blocker: unresolved WeaponTemplate::getAimPosition.
Radar retains four unresolved data names, a divergent RadarObject::getColor
COMDAT and a nonretail std::max<int> COMDAT. The provider witness retains its
independent blockers; it is not edited. No broader closure or placement is
inferred from removing these two conflicts.

This is self-strict byte verification and a paired LEGACY conflict reduction,
with zero new authored C++ bytes and zero legacy linked-byte gain. Closed-strict
closure and fresh census gains remain unmeasured. No maintainer-only full
link cycle, census, nightly or boot runner was started. Scratch snapshots,
objects, receipts and comparison scripts remain under
build/bezier-radar-radius-link-20261014.

Donor review: verified BFME 1 gitlink a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (incidental constructor
ownership) and b955ec4852b51ec7190f1a4542a9f2864abda988 (keep the exact
geometry helper in its caller TU). Preserving the verified caller and
separating incompatible helper ownership is applicable. Donor addresses,
layouts, alias scaffolding and body rehoming are inapplicable here. No donor
code is imported; target byte and object evidence independently establish
the unchanged operation and conflict reduction.

Official BFME 1 master was fetched and is now
4b2a6f64aa83cd66e01cd83574cc64cc366a440e. Freshness remains due: the
previously recorded old-input full gate needs thousands of stale TUs and
encountered compiler stalls. That unchanged multi-hour prerequisite was not
repeated in this bounded link seat. The verified checkout/gitlink and
successful-check timestamp are preserved; the fetched pointer is not
claimed verified or advanced.
