# Debug placement-new link repair, 2026-10-15

Base: `14987909b64803985c38dd43295c37ab39a07a1a`.

The two touched WWDebug factories emitted an unused eight-byte placement-new
COMDAT, `??2@YAPAXIPAX@Z`, with digest `6df3a864d1e4`. The current local link
index rejects that copy against retail. It was the only local finding in each
unit. Suppress its external emission using the already established
`dllimport` plus `__forceinline` technique. Retain `<new>` and equivalent inline
placement delete: the first singleton trial omitted placement delete and lost
its EH shape, so that trial was corrected before acceptance. Compiler flags,
class layouts, data bindings, pins and ledger identities are unchanged.

## Paired evidence and limits

Index SHA-256: `a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3`.
Its refreshed index receipt is `19a2565407`, 2026-10-15 09:33; its underlying
census measurement is `5986a99448`, 2026-10-15 04:52. The committed link-status
measurement is different and is not used for a before/after claim here.

Each object-proof JSON pairs the saved strict-current pre-edit object with the
strict-current post-edit object against that same index. The only removed
external binding/COMDAT is placement new; no external binding is added, no
nondebug relocation references the removed name, and directives are unchanged.
All retained COMDAT bytes and normalized relocations are identical, as are all
other retained nondebug sections (local-label targets and `.sxdata` symbol
indices are normalized). Source, object and receipt hashes are recorded.

- `DebugPreStaticInit.cpp`: findings 1 -> 0; legacy local LINKED 0 -> 124 bytes
  (114-byte parent at RVA 0x000385F0 plus 10-byte EH handler at 0x0075CD91).
- `Rva00891540DebugIOConCreate.cpp`: findings 1 -> 0; legacy local LINKED 0 -> 99
  bytes (89-byte parent at RVA 0x00040E50 plus 10-byte EH handler at 0x0075CED1).
- Paired local prediction: 0 -> 223 existing authored bytes. New authored C++
  bytes: zero. This is self-strict object evidence and a legacy local link
  prediction, not a closed-strict census or full executable/link-cycle gain.

These remain the existing ledger identities; suppressing an unused library
helper supplies no additional identity or layout evidence for the address-named
console factory. Its 17-byte unwind body and the singleton's 17-byte unwind body
also pass byte verification, but are excluded from the 223 authored-byte count.

## Acceptance

For both sources:

- `./build.sh <source>`: 3/3 rows exact in each unit.
- `python3 tools/link_check.py --prepare-current <source>` before and after:
  strict current compilation, 3/3 exact in each unit.
- `python3 tools/link_check.py <both sources>`: both LINKS, 223 bytes combined.
- `python3 tools/link_check.py --new-variants <source>`: passes.
- `python3 tools/eh_verify.py <source> --json <artifact>`: EXACT 1 in each unit.
- `python3 tools/data_check.py --enforce <both sources>`: zero findings.
- `python3 tools/data_check.py --converged <both sources>`: eight addresses,
  zero second names or unjudged rows.
- `python3 tools/class_gate.py <both sources>`: passes.
- `python3 tools/find_declared_unmatched.py <source>`: no undeclared definitions.
- `python3 tools/place_bodies.py <source>`: zero additional bodies/pins each.
- `python3 tools/check_csv.py`: passes.

The object comparison and cohort scan are scratch scripts under `build/`;
the durable results are included here. No full census, link cycle or other
maintainer-only verification runner was launched.

## Shared cause and donor review

The same loser name occurs in 23 indexed units. These two were the only units
whose sole finding was this helper. The remaining 21 have independent blockers;
no repair or gain is claimed for them. The JSONs preserve the cohort snapshot.
In particular, DebugIONet_Create and DebugIOOds_Create each have four findings.

Reviewed BFME1 repair `d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`, which removes
incidental TU-local BfmeStrVKI wrapper constructors. The principle of avoiding
unused competing COMDAT emission applies; that wrapper code/layout does not.
The concrete helper suppression here follows BFME2's already verified
vector-clear repair pattern and the target object evidence above.

BFME1 remains at verified-input checkout/gitlink
`a7c38d3b2597121f178ab5190b3062478823257d`; a read-only official-master fetch
found `a2f54add8e83f114f022a72feecfc163af60834d`. Another live worker holds
`file:reference/open-bfme-1`; the old/new full verification and pointer update
remain under that claim. This repair changes no donor inputs, advances no
pointer and does not mark the overdue freshness verification successful.
