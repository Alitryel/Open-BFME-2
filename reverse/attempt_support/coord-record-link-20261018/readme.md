# Coordinate record inline constructor

The published c2c5ac8c27 census and current-object preview both reject this unit solely for its ICoord2D default-constructor COMDAT. The class already force-inlines its two zero stores, which the retail record constructor overwrites from the supplied coordinate. Applying the existing imported-forceinline pattern suppresses only the out-of-line offering; all four matched rows remain strict-byte exact. Local legacy link prediction rises from 0 to 258 unique matched bytes. No closed-strict or runtime claim.

The normal string, float and import checks pass, and code identity reports no new findings. No new pin, alias, address global or layout change. The entire blocker index was searched for this constructor: this is the only losing consumer, so there is no same-cause batch to extend. The BFME 1 pointer and donor scan remain those reviewed for the preceding repairs; this repair follows the target-owned record and existing compiler pattern.

## Preserved session evidence

Upstream 865c54fdb5 already holds the identical constructor change. Recovery
retains that source and its comment; no additional 258-byte gain is claimed.
The independently saved report follows for provenance.

### Earlier trial report

StlportCoordVectorRecordInsert.cpp's private ICoord2D constructor initializes
its two integer components to zero. Its external copy differed from the
selected copy, holding the complete 258-byte unit out of linking. Apply the
existing dllimport/forceinline pattern to keep the real initialization in the
record constructor without emitting this competing copy. No layout, helper
semantics, compiler settings, pins or ledger rows change.

Explicit current-object link_check.py before: 0 -> 0 B, sole ICoord2D constructor
COMDAT blocker. After: LINKS, 0 -> 258 B. Published index c2c5ac8c27,
2026-10-18 11:36. This is a legacy same-index projection, not a closed-strict
measurement. The current-ledger check remains blocked on 46 missing objects
as recorded in layer-vector3-link-20261018. No census or full link cycle run.

build.sh and link_check.py --prepare-current pass 4/4 existing rows with
strict reusable receipts and zero string/float/import references. The
unclaimed-definition check passes. The available index reports no other
unit blocked by this constructor; the full Code search finds no second
private forceinline copy with this shape. This change makes no new identity
or original-type claim beyond the record unit's existing structural view.

The accompanying attempt log records a separate pointer-deque allocator
repair stopped and restored after two failed byte trials; no deque edit is
included.
