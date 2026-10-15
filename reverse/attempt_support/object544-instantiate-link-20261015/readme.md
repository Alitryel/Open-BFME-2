Object544 vector instantiation link repair

Whole-class vector<BfmeObject544> instantiation emitted an unrelated destructor
copy that disagreed with the indexed family. Instantiate the recovered
push_back, _M_clear and _M_insert_overflow operations and the const-pointer
uninitialized-copy helper explicitly. All ten ledger rows remain emitted.
The existing StlportVectorDtorFamily.cpp retains the destructor owner at
0x004CAE89; no identity or layout assertion is added.

Base checkout: 03c02784ee4e48d4984941660a7b9667692a2dc2. Measurement:
ac77c85054, 2026-10-15 14:25 UTC. Exact index hash, object hashes and paired
findings are in object-proof.json. Against the same unchanged index with the
same current destructor provider on both sides, the consumer changes from
one COMDAT blocker to zero: LEGACY local linked bytes 0 -> 473.
The provider retains exactly its previous 9 unresolved, 33 COMDAT and
18 wrong-selected findings. No provider closure improvement is claimed.

All 21 retained COMDAT bodies have identical bytes, extents and digests.
The paired full-object proof compares retained nondebug sections, flags,
bytes and symbolic relocations, normalizing local references and SafeSEH
entries. Only 68 removed COMDATs and their associative sections are excluded;
no retained section refers to a removed body. The five removed shared
families preserve the first selected digest and introduce no new losers.
The 63 removed sole-provider names have no undefined external consumer in
68,933 available unique object variants. This covers 22,830 measurement
hashes; 238 measurement hashes are unavailable. This bounded scan does not
establish global closure for missing objects. Data bindings are unchanged.

Acceptance:
- Consumer build and strict reusable receipt: 10/10 matched rows.
- Current destructor-provider strict reusable receipt: 44/44 matched rows.
- Paired local link preview: consumer LINKS; provider findings unchanged.
- EH verification over both units: 32 EXACT, no missing object or debt.
- Data enforcement, converged-data enforcement, frozen-file, class, CSV,
  new-COMDAT-variant and whitespace checks pass.
- place_bodies.py on the consumer finds zero bodies and zero pins.

Receipts are self-strict. New authored C++ bytes: zero. The 473-byte result
is an existing-code LEGACY local preview gain, not a closed-strict census,
full-link, placement or runtime measurement. No census/status/baseline,
flags, header, pin, ledger row or verifier rule changes. No maintainer-only
runner was started. proof.py and scan.py are saved here; their baseline
source/object/receipt snapshots remain in ignored build/object544-instantiate-link-20261015.

Donor review: retained verified BFME 1 pointer
 a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor suppression repair
66b19a8e95a4add525ef808fcea088e306798e2b and earlier c1315665 linking work;
the actual successful adaptation follows BFME 2's already verified
image-map-link-20261015 selective-instantiation repair. No donor ABI or
layout is imported. Official master was fetched to 9f335a9e, but another
worker owns file:reference/open-bfme-1; the overdue verified pointer update
remains pending. No freshness success stamp was written.

Independent triage: MeshMatDescUniqueArrays.cpp's dllimport/forceinline
RefPtr-destructor suppression preserved the parent and handler but changed
its unwind cleanup 0x0076730F from 18 to 19 bytes. Recorded blocked via
re_log.py and restored the source; all three rows pass after restoration.
SpawnBehavior_update's lookup suppression was already blocked by recorded
register changes; no repeated edit or trial was made. All trial claims are
released. Investigation model: gpt-6.1-sol; mesh trial t=4 minutes.
