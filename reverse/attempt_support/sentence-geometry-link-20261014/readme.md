# Sentence geometry record linkage repair

Base checkout 00008ddf5d. Paired runner index: 147cfae2cb,
2026-10-14 07:27; exact source/object/index hashes and findings are in
object-proof.json. The newer committed link_status.csv measurement de7bb30890
is discovery only. No index, status, history or data-back ranking changed.

Render2DSentenceClassRva00156540.cpp used TextureStatisticsStructWide for a
36-byte local geometry record: W3DRadarResetSurface (COM ownership) followed
by eight floats. Its emitted destructor delegates to W3DRadarResetSurface.
TextureStatisticsVectorWide.cpp and its Extras unit use that same placeholder
name for a texture-owning record with RefCountPtrWide<TextureClassWide>.
Their destructor delegates to that wrapper instead. The index selects the
first texture-record copy, causing this surface-record copy to lose.

Rename only the local geometry view to RenderSentenceGeometryView. Keep the
append provider's existing opaque TextureStatisticsStructWide spelling and
cast the local view at that call, as the matched Record_Sentence_Chunk sibling
already does for its 36-byte surface/geometry record. This separates two
existing implementation views; it asserts no new original retail type name.
Target stores, the matched surface destructor and the existing append call
establish the local layout and ownership. The sibling supplies corroborating
surface/geometry interpretation; texture-view field labels are not evidence
for geometry semantics. No ABI, flags, headers, globals, pins or ledger rows change.

Acceptance:

- Bounded link_check.py --prepare-current verifies four explicit source units,
  11/11 rows, with strict reusable receipts before editing. Afterward the
  touched unit passes the independent ./build.sh gate and strict preparation,
  1/1 row (256 bytes), with zero skipped literal/import references.
- Its renamed constructor and destructor have identical extents, bytes and
  normalized relocations. All retained external COMDAT digests agree; every
  nondebug section and relocation compares equal after normalizing the two
  local helper names. Strong, undefined and weak binding sets agree.
- The same index and same three byte-verified witnesses are refreshed in memory
  on both sides. The consumer changes from one COMDAT finding to none;
  paired LEGACY existing linked bytes rise 0 -> 256. All findings and object
  bytes of the three witnesses stay unchanged. No other old-name destructor
  losing copy is present in this index; its two texture copies agree.
- EH 1/1 EXACT, zero baseline/missing objects. Frozen definitions, class gate,
  shadow new-variant admission, CSV and whitespace checks pass. Converged data
  checks protect eight addresses, with zero second names/unjudged rows;
  shadow data checks find zero issues. Placement resweep: zero bodies/pins.

This is self-strict byte verification plus bounded paired LEGACY link closure,
with zero new authored C++ bytes. No closed-strict, fresh full census, actual
placement or runtime gain is claimed. The texture witnesses still need their
Release_Ref provider and assignment reconciliation. The adjacent sentence
chunk witness retains duplicate/selected-body and other COMDAT findings;
these are separate dependencies, unchanged by this repair. No maintainer-only
runner was started.

Reproduction: proof.py consumes the preserved build/sentence-geometry-link-20261014
snapshots and receipts, refreshes only these four units against the recorded
index, and asserts the comparisons. Scratch snapshots remain untracked there.

Donor review: verified BFME1 gitlink a7c38d3b2597121f178ab5190b3062478823257d;
reviewed de59a7e9f891b3ed2d4221d151ca881f4b75a583 (Apt incidental predicate
ownership). The ownership principle applies; no Apt code/layout is imported.
BFME1 official master was fetched but the verified pointer is retained:
the previously documented comparative full-gate prerequisite needs thousands
of stale units and encountered compiler stalls. That unchanged multi-hour
blocker was not repeated in this bounded seat, and no freshness success stamp
was written. The published census download separately failed with proxy HTTP
403; the present runner index was used without a rebuild.
