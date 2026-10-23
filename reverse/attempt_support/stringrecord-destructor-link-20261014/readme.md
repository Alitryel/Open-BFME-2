# Shared string-record destructor link repair, 2026-10-14

Declare `~BfmeStringRecord000B9534()` in the allocator and vector-base shards.
The allocation/copy unit already emits the kept five-byte cleanup COMDAT, which
tail-jumps to `StringBase<char>::releaseBuffer`. The two edited shards emitted a
competing five-byte tail jump to `AsciiString::~AsciiString`. The latter retail
body, rowed at RVA 0x0048BA39, itself tail-jumps to the same releaseBuffer owner
at RVA 0x00036410. This repair changes ownership of emitted cleanup, not layout.
The record's address-derived name remains a structural inference; no original
application identity, retail address for this record destructor, or pin is added.

## Paired evidence

The actual local index is measurement 147cfae2cb, 2026-10-14 07:27, SHA256
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
`base-head.txt` identifies the working source revision. The committed status
artifact describes a different measurement and was used for discovery only.
Both previews refresh the same index **in memory**, with the same five explicit
objects, before or after the edit; neither changes the census/index/status.

| Source | Before legacy local preview | After |
| --- | --- | --- |
| allocate_copy | clean, 260 matched bytes | clean, 260 |
| vector_base | 13 losing COMDATs, 0 bytes | 12 losing COMDATs, 0 bytes |
| allocator | 1 losing COMDAT, 0 bytes | clean, 28 bytes |
| SubObjectVisibility | 1 losing COMDAT, 0 bytes | unchanged |
| ScriptedModelDrawXfer | 8 losing COMDATs, 2 wrong selections, 0 bytes | unchanged |

Total clean files: 1/5 -> 2/5. Existing LINKED bytes in this paired legacy
preview: 260 -> 288. New authored retail bytes: zero. Strict-current receipts
are proven for all five inputs; this is not closed-strict closure or a full
link measurement. No published census or closed-strict gain is claimed.
The normal local link check exits 1 because three consumers remain blocked;
its two clean files and detailed residual findings agree with the paired proof.

## Object and gate checks

`object-proof.json` records object hashes, removed COMDATs, every allowed
cleanup-call retarget, and complete paired findings. The allocator retains all
other COMDAT bytes, extents and relocations. Two sections reorder without
changing contents. Vector-base retains all body bytes and extents, but six
already-unmatched vector helper calls switch from the AsciiString destructor
to the shared record destructor. Both destinations perform the same release,
as established above. Their COMDATs were losing before and remain losing after;
no new variant is introduced to a census-agreed name. All other retained
nondebug sections, relocations, external definitions, EH and data are unchanged
under section-order and these six cleanup-target normalizations. The edited
units' new undefined record destructor is provided by the unchanged current
allocation/copy unit; there is no new unresolved reference in the local check.
The drawing consumers remain unchanged because hiding their cleanup body would
change inlining needed by matched parent bodies.

Before and after `link_check.py --prepare-current --paths-from sources.txt`:
12/12 matched rows, exact bytes and relocations; string/float/import checks pass.
The separate edited-source byte gate passes 4/4 rows. EH: 2/2 EXACT, no baseline
or missing objects. Enforced data check: zero findings across five sources.
Class gate and link new-variants pass. Frozen-source checks pass in both edited
units. Placement resweep yields zero additional bodies or pins. `check_csv.py`
and normal commit hooks validate the final change. The shadow code-identity
hook reports seven divergent definition keys outside its baseline. A paired
comparison using its own `dup_defs.analyse`/`debt` rules and all cached tree
objects finds **8 before -> 7 after**, with no added key: the record destructor
key disappears and all seven remaining keys are pre-existing. This is a shadow
finding comparison, not receipt-current tree closure. `identity-proof.json`
and `verify_identity.py` preserve that distinction. No baseline is edited.

Run `python3 reverse/attempt_support/stringrecord-destructor-link-20261014/verify.py`
to repeat the paired object proof when the saved snapshots in
`build/stringrecord-destructor-link-20261014/` and this measurement index remain
available. The script uses saved before objects and current strict receipts,
not a new census build. Acceptance commands and output are included beside it.

## Donor review and remaining work

The retained verified BFME 1 checkout/gitlink is
23b143233b5a8664a3bdf8572df6d905c310a5a1; fetched official master is
a7c38d3b2597121f178ab5190b3062478823257d. Prior review and the current review
of donor repair de59a7e9f891b3ed2d4221d151ca881f4b75a583 support reconciling
incidental differing inline COMDATs instead of importing extra wrappers. This
principle is applied locally; no donor code or layout is imported. Target
byte/EH gates and current object evidence establish the present acceptance.

The pre-existing freshness comparison still requires thousands of stale donor
objects; its interrupted full-gate evidence is in the unicode-comparator repair
record. Last verified inputs are preserved; no pointer or success stamp changes.
The vector helpers and drawing consumers retain the blockers listed above.
Broader closed-strict verification and a full link cycle remain outstanding;
maintainer-only runners were not started.
