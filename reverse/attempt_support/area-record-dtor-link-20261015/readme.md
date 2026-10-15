Area-record destructor ownership repair

BFME2 base: 83f8781be4 (full SHA in context.json). Frozen runner index:
ac77c85054, 2026-10-15 14:25 UTC; context.json records its SHA256.
The committed census supplied discovery, not a new measurement. No matching
per-row data-back artifact was available or used for ranking.

Rva0027EA49Dtor.cpp emitted an exclusive 13-byte destructor beside the
identical implicit destructor in Rva00282135Clear.cpp. Both units failed
solely on that duplicate. Move the existing row through add_match
--replace-existing into the vector consumer and delete the standalone unit.
The surviving destructor retains the complete native 13 bytes and its
REL32 fastcall ReleaseTreeHintRef00217D4C relocation. No new name, type,
layout, flag, pin, alias, allowance or reference-header change is introduced.
The identity remains the existing address-derived retained-record name.
Target evidence remains the pointer at +4, native boundary and release call;
the vector unit already represented the same retained-pointer ownership.

Proof and local acceptance

Before repair, bounded strict preparation passes 71/71 rows across the four
sources. After repair it passes the same 71/71 rows in three sources. All
surviving sources have self-strict reusable receipts. proof.json records
object/receipt hashes and exact paired findings. Each surviving object is
identical in its entirety except the COFF timestamp, including all bytes,
sections, external/weak/undefined names, relocations and directives. Both
unchanged vector-destruction and tree-erasure consumers are byte-for-byte
identical even including their timestamps.

build/area-record-dtor-link-20261015/proof.py compares saved-before objects
with current objects. It refreshes the same bounded objects into independent
copies of the frozen index. Afterward it uses link_check.forget to retire the
removed ledger owner's definitions, exactly as --update-index handles
removed units. The shared index and committed census/status remain unchanged.
The ordinary local link_check main/CLI runs against that isolated preview
index and reports all three surviving sources LINKS. The vector consumer
moves 0 -> 139 existing matched bytes; the two peers stay at 98 and 2435.
Paired legacy predicted LINKED total: 2533 -> 2672 (+139). The destructor
has one provider and both consumers retain all their original findings
(none). This is a legacy local prediction with self-strict object currency,
not a closed-strict, census, executable-placement or runtime gain. New
authored C++ coverage is zero.

Acceptance: add_match's normal byte gate 2/2; strict three-source preparation
71/71; frozen definitions, class gate, no-new-variants, CSV and whitespace
checks pass. Enforced data has zero findings; converged data checks eight
addresses with zero second names or unjudged rows. EH: one EXACT, zero
missing/nonexact objects or baseline entries. No literals, compiler floats
or imports require verification in this cohort. Affected-unit placement
resweep finds zero bodies and zero pins. Hooks repeat required checks.

Reference review and remaining boundaries

Reviewed BFME1 repair b66f793f3d886b07b8698ff04aa5ce9707eb896a (duplicate
provider ownership) and 66b19a8e95a4add525ef808fcea088e306798e2b (suppress
incidental emitted copies), including their byte/link evidence. Ownership
convergence applies; no donor source or ABI is imported. Here deletion
preserves every surviving object, so no substitute emitter is necessary.
Verified donor checkout/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
Official master was fetched as 8fd28602 (full upstream history available).
The overdue reference update still needs the controlled old/new full-byte
comparison and layout reconciliation; this bounded repair preserves verified
inputs and writes no freshness success stamp. An earlier foreign claim is
not asserted to remain live at this session's claim check.

No full census, link cycle, nightly, boot, scheduler or shadow-publisher
runner was invoked. Broad reference freshness and full link closure remain
outstanding; the repaired local dependency has no remaining finding.
Model: gpt-6.1-sol.
