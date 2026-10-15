# Debug output factories: remove unused placement-new copies

Base: 05ce90b4759cbe0249cee7262d953dc9b0f3b636. Sources:
Code/Libraries/Source/WWVegas/WWDebug/DebugIONet_Create.cpp and
Code/Libraries/Source/WWVegas/WWDebug/DebugIOOds_Create.cpp.

Both factories emit the same unused 8-byte placement-new COMDAT
`??2@YAPAXIPAX@Z` (`558bec8b450c5dc3`, digest `6df3a864d1e4`).
The index rejects that body against retail. Apply the already verified
WWDebug factory spelling from DebugPreStaticInit.cpp: keep standard placement
construction and delete visible, but suppress the unused external new body
with dllimport/forceinline. No import reference, alias, pin, global, compiler
flag, class layout, ledger extent or identity changes.

## Paired measurement

Index SHA256 a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3:
runner index receipt 19a2565407, 2026-10-15 09:33;
underlying census 5986a99448, 2026-10-15 04:52.
Committed reverse/link_status.csv names another measurement (28269d8e8d),
so it is only discovery evidence, not a paired measurement here. The fetch
kept the newer local index and populated reusable objects from the published
archive. No per-row data-back artifact was ranked.

The strict-current pre-edit objects and strict-current post-edit objects were
refreshed together into independent in-memory copies of this same index.
Each file's legacy local findings fall 4 -> 3, total 8 -> 6. Both remain
unlinked: existing nonpadding authored LINKED bytes 0 -> 0 (106 network,
111 ODS). New authored C++ bytes: zero. This is self-strict byte acceptance,
verified object-emission repair and a legacy local preview, not a closed-strict
census gain or executable placement result. Index/status/history are unchanged.

object-proof.json records source/object/receipt hashes and both results.
Exactly one unused COMDAT and its external binding disappear per object.
No external binding is added. All 22 retained COMDATs (9 network, 13 ODS)
and all 34 retained nondebug sections (14 network, 20 ODS) have identical
bytes, extents and normalized relocations. Nondebug relocations never refer
to the removed symbol; directives are unchanged. Local label targets and
.sxdata symbol indices are normalized. Scratch proof script, saved source,
objects and dependency receipts remain under ignored
build/debug-output-placement-link-20261015/.

## Acceptance and remaining work

- Before/after `link_check.py --prepare-current` on both files: 9/9 exact,
  strict reusable current receipts, no skipped string or import references.
- Ordinary `./build.sh` on both files: 9/9 exact, references pass.
- `eh_verify.py` before/after: 2/2 EXACT. Generated unwind rows retain their
  existing object-symbol identities and exact bodies.
- Ordinary `link_check.py` on both current files agrees: 3 findings each
  (expected exit 1), no placement-new finding.
- `link_check.py --new-variants`: passes with no findings.
- Enforced data check: zero findings; converged check: 8 addresses, zero
  second names or unjudged rows. Class, declared-definition and whitespace
  checks pass. Placement resweep: zero bodies/pins.

Network still needs the DebugIONet destructor provider and consistent
DebugIOInterface vtable/deleting destructor. ODS still has its duplicate
constructor, competing DebugIOOds vtable and DebugIOInterface deleting
destructor. These are independent class/provider work; this change neither
retries them nor claims a consumer gain. The remaining same-helper cohort
was recorded by the preceding debug-placement-link-20261015 repair; only
these two additional WWDebug consumers are changed here.

## Reference and identity evidence

The BFME1 incidental-constructor repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d
supports the same emission principle, not these class layouts or addresses.
The existing dedicated-pass donor review is reused; no broad unchanged donor
scan was repeated. Original verbatim-import ledger provenance and target
identities remain unchanged. Whole target bodies are 0x0003F7B0..0x0003F810
and 0x0003F3D0..0x0003F430, both 96 bytes.

Clean donor checkout/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
A read-only official-master fetch found 8ccabba86ebc7cf7961a1a483b3b344fdfeea5a0.
Another worker holds file:reference/open-bfme-1. The overdue old/new full
verification and pointer update stay under that claim; no inputs or pointer
were changed and no successful freshness stamp was written. No maintainer-only
census, link cycle, nightly, boot or publication runner was started.
