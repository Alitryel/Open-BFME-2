# Army entry-added unsigned max ownership repair

BFME 2 base bb0c3d7fab. The runner index measures 147cfae2cb at
2026-10-14 07:27; its complete metadata and unchanged SHA256 are in
object-proof.json. The committed link_status.csv measures de7bb30890 and
is used only for discovery. No per-row data-back artifact or ranking is used.

StrategicInGameUIArmyDetailsEntryAdded.cpp emits an incidental sixteen-byte
unsigned _STL::max COMDAT that differs from retail's seventeen-byte provider
in stlport_basic_ios_init.cpp. The established TU-local overload before the
container headers retains the original comparison and reference-return
semantics. Its uses were already inlined. No flags, shared headers, layouts,
external calls, globals, rows, pins, aliases or baselines change.

The existing native 0x005E4E55..0x005E4F6D callback, WorldBuilder twin and
ledger establish the caller identity. The preexisting storage-view uncertainty
about integer entry IDs and ScienceType providers remains unchanged. This
repair makes no new identity or layout claim.

## Verification and result

- Independent build.sh passes the unit's complete 280-byte row, all literal
  checks and imports. Bounded prepare-current passes 22/22 rows across the
  consumer and unchanged max provider with strict reusable compiler receipts.
- All 46 retained external COMDATs have identical whole bytes, extents and
  normalized relocation digests. All 50 other nondebug sections, including
  directives and EH data, are identical after normalization of COFF indices
  and local compiler labels by their target section bytes and offsets.
- The only removed external definition is max. Its replacement is an
  eight-byte static helper; neither has incoming or outgoing nondebug
  relocations. Exclusive, undefined and weak bindings remain equal. The
  provider's seventeen-byte copy is independently judged retail and its
  findings are unchanged in both paired comparisons.
- Same-index paired legacy findings fall 6 -> 5, removing exactly max.
  Remaining findings: ScienceType allocator deallocate, int and ScienceType
  proxy deallocate, ScienceType vector _M_clear, and selected-wrong int vector
  base destructor. The exact names and unchanged provider blockers are in
  object-proof.json and link-after.txt. Legacy LINKED stays 0 -> 0 bytes.
- EH graph is EXACT 1/1, with no baseline or missing object. Enforced data
  check has zero findings; converged-data covers eight addresses with zero
  second names or unjudged rows. Before/after row data facts and findings are
  identical. Frozen-definition, class gate, new-COMDAT admission, CSV and
  whitespace checks pass. Placement resweep finds zero bodies or pins.

Strict receipts establish the explicit objects' currency and byte acceptance.
The link improvement is a paired LEGACY preview, with zero authored C++ growth
and zero linked-byte gain. No self-strict LINK closure, closed-strict gain,
fresh census placement or runtime result is claimed. No census build/measure/
history, full link cycle, nightly, boot or scheduler operation ran. Other
allocator/vector blockers require separate supported repairs.

Snapshots, receipts and original source/object backups remain in ignored
build/army-entry-max-link-20261014. Archived snapshot.py and compare.py reproduce
the strict-currency snapshots and complete-object/paired-index comparison.

## Donor review and prerequisites

Reviewed BFME 1 d3f9000fe08615a100e844adfff57fa4a39cd615 and
de59a7e9f891b3ed2d4221d151ca881f4b75a583 at verified gitlink
 a7c38d3b2597121f178ab5190b3062478823257d. Suppressing or reconciling incidental
emitters while retaining verified callers is applicable as a principle.
The donor bodies, layouts and addresses are inapplicable here; no donor code
is imported. Prior verified BFME 2 unsigned-max repairs supply the concrete
local overload; independent target comparisons establish this application.

Official BFME 1 master was fetched at
46dddb7d562a0c4d66f2618c13f134f2710257ba. The clean verified checkout/gitlink
is retained. Its update is still blocked by the previously documented
valid-cache comparative full-gate prerequisite (thousands of stale TUs and
compiler stalls). No pointer advancement or freshness-success stamp is made.
Fetching the published BFME 2 index failed with HTTP 403 Filtered; the existing
runner index is present and remains unchanged, so the paired repair is locally
verifiable without rebuilding a census.

The bounded BuildQueueUnitQueued preparation probe refused an unknown include
inventory / uncacheable strict receipt. That unit has a declaration-only max
specialization already and was not modified or claimed. Previously deferred
PeerDefsGameOptions and SidesListTeamsInfoRecAddTeam max changes were not retried:
the former changes the matched caller's schedule, and the latter has a recorded
EH-symbol false reject. Existing preparation and unrelated untracked dumps and
zh_sweep data are preserved.
