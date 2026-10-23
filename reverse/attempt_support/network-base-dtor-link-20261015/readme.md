# Network base-destructor ownership repair

Source base: 3366f331c9. Runner index: 19a2565407, 2026-10-15 09:33;
original census 5986a99448, 2026-10-15 04:52. Index SHA256 and source,
object and strict-receipt hashes are recorded in object-proof.json.
Committed link_status.csv is queue evidence, not this measurement.

Rva00552C0FBase.cpp emitted a strong empty virtual destructor at 0x00552C08.
Rva00557CCCDtor.cpp already emitted an identical inline copy needed by its
matched derived cleanup. Make the standalone definition inline (it no longer
emits that body) and rehome the existing seven-byte row to the unchanged
consumer with add_match --replace-existing. The standalone constructor and
scalar deleting destructor remain unchanged. No class header, pin, flags,
baseline, census index, status/history or other escape hatch changes.

Target facts: native552C08..552C0F restores vtable VA00C6B090 and returns;
scalar deleting destructor552C0F and constructor552C56 use that same vtable;
derived cleanup557CCC uses the base. Both old copies independently pass
retail byte and relocation verdicts, including the vtable relocation. Existing
address-derived class names are retained; no original semantic class name
or additional layout is claimed. No donor code or layout is imported.

Acceptance:

- Both explicit claimed units pass link_check --prepare-current before and
  after, all16 rows with strict reusable receipts. add_match independently
  verifies all14 rows now owned by the consumer; normal build.sh passes16/16.
- EH: EXACT1, no missing objects. Frozen definitions, canonical classes,
  new COMDAT variants, converged data (eight addresses), shadow data,
  check_csv and whitespace checks pass. Placement: zero bodies, zero pins.
- Snapshot/proof refreshes only these two current objects into the same index
  in memory before each local prediction. Exactly one redundant7B section
  disappears. Every retained nondebug section, code byte, relocation, external
  binding, EH reference and directive is unchanged. The provider object is
  unchanged. The asserting scratch proof is build/network-base-dtor-link-20261015/proof.py.
- Paired legacy preview:0/2 ->2/2 clean; duplicate findings2 ->0; no findings
  added. LINKED existing nonpadding retail bytes0 ->249 (38 standalone,
  211 consumer after ownership transfer). Authored C++ and total matched bytes
  grow by zero. Both units are self-strict current. External providers retain
  the census's legacy evidence; closed-strict closure, link.exe placement and
  fresh census gain are not measured. No full link cycle or census ran.

Reference review: retained clean verified BFME1 gitlink/checkout
 a7c38d3b2597121f178ab5190b3062478823257d. Inspected repair
4966496c5ae401ec877a044e1ae6dd04f9d9f65c directly: avoiding surplus emission
while preserving matched callers is applicable as an ownership principle;
its AsciiString changes are not imported. The earlier shared-library donor
review is recorded in vector12-assign-home-link-20261015 and adjacent repair
evidence. Official master was fetched by the initial pull to a2f54add8;
freshness update remains blocked by another worker's reference/open-bfme-1
file claim and outstanding old/new full-byte comparison. Verified inputs and
old stamp are preserved; no successful freshness update is claimed.

Selection: repair_queue.py link; link_rank.py help/top/near and duplicate
rank. GameSlotApparent and PlayerList getter trials are already blocked;
Rva00358076AudioComplete remains foreign-claimed. Debug-hash and vector
ownership fixes already landed; their stale census findings are not repeated.
The independent callback destructor attempt is restored and recorded at
../callback-dtor-link-blocked-20261015/readme.md. No per-row data-back artifact
was available or used for ranking. No full link cycle, census build/measure/
history, nightly, boot, shadow publisher or maintainer-only runner ran.
