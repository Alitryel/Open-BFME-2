# Carryover insertion unsigned max link repair

BFME 2 base: c01c35ac0d0bacdea7aac9a4cda334edb4083cf5.
Unchanged runner census index: 147cfae2cb, 2026-10-14 07:27;
SHA256 690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a. The older committed
link_status.csv is discovery evidence only.

LinearCampaignCarryoverInsert.cpp emitted an incidental nonretail standalone
_STL::max<unsigned int> COMDAT. Add the established internal unsigned overload
before vector headers. Its comparison and reference-return semantics agree
with STLport; this unit already inlined every use. Flags, class layouts,
ledger rows, pins, globals and external providers are unchanged.

Target identity, ABI and layout evidence remain the existing 349-byte
0x001EC1B4..0x001EC311 RET16 body and its callers, 172-byte stride and existing
copy/assignment providers. STLport supplies the comparison semantics; no new
application name or layout fact is inferred. Source donor provenance remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 as recorded in the source.

Acceptance:

- Strict receipt preparation passes the touched row before and after. The
  preparation logs also include an exploratory online-room unit, which already
  had declaration-only max suppression; its trial edit was fully restored and
  both of its claims released. Final source/object proofs concern only campaign.
- Ordinary byte gate: campaign 1/1 exact. Campaign plus canonical max-provider
  stlport_basic_ios_init.cpp pass 22/22, with two named imports checked, zero string/float references,
  and no baseline or skip. The provider is unchanged.
- All 16 retained COMDATs have identical bytes, extents and relocation digests.
  The only removed external binding is max. Other nondebug sections and exact
  linker directives are equal after normalizing local COFF indices. One private
  eight-byte comparison helper replaces it; it has no relocations or nondebug
  callers. Source/object/index hashes are in object-proof.json. Proof scripts,
  originals and receipts remain in build/carryover-chat-max-link-20261014.
- Same-index, same-cohort local legacy preview refreshes only the explicit
  consumer in memory. Findings decrease 3 -> 2, with only max removed; LINKED
  remains 0 -> 0. link-proof.json compares saved-before and current objects
  under their canonical filenames. The removed copy is index position 5123,
  wrong digest 733af3e58f87; the first retail copy at position 66 has digest
  4e112da03a19. Canonical owner stlport_basic_ios_init.cpp stays unchanged.
- Declared-function, class, new-variant and CSV checks pass. Enforced data check:
  eight protected addresses, zero second names or unjudged rows. Shadow data
  check: zero findings. EH verifier: no applicable rows or missing objects.
  Placement resweep: zero bodies and zero pins. Whitespace check preserves
  the file's existing CRLF format.

This verifies one fewer local link finding, with zero authored C++ growth.
The two remaining findings are selected nonretail BfmePod172 _Construct and
Rva001EB831Element __copy_backward providers. They are independent unchanged
blockers and were not retried. Strict compiler currency is proven; no
self-strict LINK closure, closed-strict gain, fresh census placement or runtime
result is claimed. The closed-strict current-ledger check refuses judgment
because 418 objects are missing. Maintainer-only runners and census
build/measure/history were not invoked.

Donor review: retained clean verified BFME 1 revision
23b143233b5a8664a3bdf8572df6d905c310a5a1. Reviewed linking repair
d3f9000fe08615a100e844adfff57fa4a39cd615 (suppress incidental nonretail emission).
Its principle applies; TileData identities/layouts do not. The preceding BFME 2
vector-growth, armies-page and fog repairs establish the concrete local overload
pattern. Whole-object target proof establishes this application; no donor code
is imported.

Official BFME 1 master was fetched as bc990782485c4111aa72d4fb8f8d00bb82e12f5b.
Compared with the verified gitlink, only one Apt source, attempt records and
donor conversion-gate/tests changed; no headers changed. Comparative full
verification remains outstanding from previous sessions, whose old-input gate
required thousands of stale TUs and was interrupted. The clean verified pointer
is preserved and no freshness-success stamp is written.
