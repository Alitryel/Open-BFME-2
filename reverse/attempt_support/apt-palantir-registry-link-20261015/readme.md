# AptPalantir registry constructor dependency repair, 2026-10-15

AptPalantirUpdate.cpp now declares the real Rva005248D0 constructor at
0x002D2C34 instead of forwarding through the undefined address-derived
Rva002D2C34::rva002D2C34 method. The existing 106-byte constructor provider
and AptPalantirConstructor.cpp already establish this target identity and ABI.
The consumer keeps its existing novtable view, layout and flags.

The change removes a proven-wrong 12-byte registry constructor COMDAT. The
consumer's emitted 2777-byte AptPalantir constructor keeps every byte and
changes only its relocation at +22 to the real constructor name. Its full
body/relocation digest now equals the owning constructor unit's copy. Every
other retained COMDAT, including the rowed 1260-byte update, is unchanged.
Both explicit provider objects remain unchanged. No ledger rows, pins, shared
headers, layouts or compiler settings change; authored bytes grow by zero.

## Evidence

Work starts at BFME 2 6e1375537c; the consumer file was claimed before editing.
object-proof.json records source/object hashes, final strict receipt hashes,
the removed wrapper, changed constructor digests and paired local findings.
Both sides use the same index, unchanged on disk:

- index 19a2565407, 2026-10-15 09:33;
- underlying census 5986a99448, 2026-10-15 04:52;
- exact index SHA256 in the proof.

Refreshing only the explicit consumer and two providers in memory removes
three findings from the consumer: one unresolved call name, the wrong registry
constructor loser, and the AptPalantir constructor loser whose call relocation
previously differed. No findings are added, and both providers' findings stay
the same. Legacy link-clean units and bytes remain zero. This is a verified
local emission/dependency improvement, not a closed-strict gain or a new census
measurement. All three explicit objects are self-strict/current and pass their
ordinary byte gates; currency of the other census providers is not claimed.
No index, census/status ledger or measurement artifact was rewritten.

The existing duplicates of AptPalantir constructor/destructor/init and the radar
helper, STL/holder destructor differences, and g_Va00A04450 global-name blocker
remain. The index also retains wrong registry constructor copies from other
units; some were already repaired by the preceding queued commit and require
future index measurement. AptRowListCallbacks' independently recorded constructor
ownership blocker was not retried. No full link cycle was run.

## Acceptance

- check_csv.py: pass (91177 function rows at session start).
- link_check.py --prepare-current on consumer, Rva005248D0Ctor.cpp and
  AptPalantirConstructor.cpp, before and after: 75/75 byte-exact; 32 string
  literals, one float literal, zero skipped strings; strict reusable receipts.
- eh_verify.py on the edited consumer: EXACT 1/1, zero baselined parents.
- link_check.py --new-variants, find_declared_unmatched.py and class_gate.py
  on the consumer: pass.
- data_check.py: one existing shadow wrong-name finding at 0x00A04450;
  the update's body and relocations that reference it are unchanged.
- data_check.py --converged: eight addresses, zero second names/unjudged rows.
- Paired proof: exactly one wrong 12-byte wrapper removed; all other COMDAT
  digests unchanged except the single constructor callee spelling; its resulting
  digest equals the owning provider; three legacy findings removed, none added.
- Standard local link_check.py on all three: 0/3 clean, 0 -> 0 linked bytes,
  exit 1 with the remaining findings recorded verbatim in object-proof.json.
- place_bodies.py on the edited consumer: zero bodies, zero pins.

## Donor review and freshness

Reused the dedicated donor review recorded in ../apt-base-ctor-link-20261015/
for verified BFME 1 revision a7c38d3b2597121f178ab5190b3062478823257d and
repair d3f9000fe08615a100e844adfff57fa4a39cd615 (suppress an incomplete implicit
constructor by declaring the real provider). Its declaration-only principle
applies; no donor source, layout, address or identity was imported. The direct
callee spelling and target constructor body come from BFME 2 evidence.

Official BFME 1 master was fetched during this session. Freshness migration is
still held by another worker's file:reference/open-bfme-1 claim; the verified
pointer and old success stamp were preserved. No update was marked successful.
Before/after sources, objects, receipts and the assertion script remain under
ignored build/apt-palantir-registry-link-20261015/.
