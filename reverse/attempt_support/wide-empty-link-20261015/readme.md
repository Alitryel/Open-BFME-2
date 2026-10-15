# Wide-string empty-test provider repair, 2026-10-15

DozerAIUpdateCtor.cpp and GameLogicDispatch.cpp emitted the same non-retail
20-byte StringBase<unsigned short>::isEmpty COMDAT, digest c63cf5a09df8.
The existing matched owner string_base_inline.cpp supplies the retail 22-byte
body at RVA 0x00035740, digest 378d5c8a69ec. Mark the two private inline views
as dllimport, an existing repository technique: MSVC keeps the tests inline
but leaves any out-of-line body to the owner. Neither object gains an import
reference. Class layout, flags, ledger and provider source are unchanged.

A declaration-only Dozer trial changed a matched caller; forceinline retained
the unwanted COMDAT. Neither trial is retained. The final import views preserve
all retained COMDAT bytes and normalized relocations, including TU-local label
values (the dispatcher compiler labels are renumbered).

## Paired evidence and acceptance

object-proof.json records before/after source, object and strict receipt hashes,
retained COMDAT digests, removed bodies, and every local link finding. Both
pairs start at BFME 2 9c06aea9ee. All three explicit objects have strict reusable
current receipts on both sides. Each pair refreshes only its consumer and the
unchanged provider in memory into the same frozen index:

- index commit 19a2565407, 2026-10-15 09:33;
- underlying census commit 5986a99448, 2026-10-15 04:52;
- index SHA256 is recorded in the proof and unchanged across both pairs.

Exactly two retail-rule loser findings disappear, one per consumer. Dozer
COMDAT findings fall 6 -> 5; dispatcher findings fall 15 -> 14. No finding is
added, and exclusive definitions, undefined externals and weak externals are
identical. The provider object is byte-identical. All retained body bytes and
relocation offsets, kinds, symbols and values agree after ignoring COFF table
indices and compiler-local label renumbering.

This is a self-strict object repair with a paired legacy local link preview.
Both consumers retain other blockers; the provider remains clean. Normal
link_check reports 1/3 clean and LINKED 3,011 -> 3,011 bytes. Authored C++ and
legacy linked-byte gains are zero. Closed-strict gain is unmeasured: unrelated
indexed providers are not collectively proven current. No census, status,
index or measurement artifact was rewritten, and no full link cycle was run.

Checks:

- link_check.py --prepare-current, Dozer plus owner: 95/95 matched rows,
  12 literals plus 18 empty references, 20 float literals, 16 imports; no skips.
- Same check, dispatcher plus owner: 54/54 rows, 11 literals plus 12 empty
  references, one float literal, 16 imports; no skips.
- eh_verify.py, both consumers: EXACT 7/7, zero baselined or missing objects.
- data_check.py --converged: eight addresses, zero second names or unjudged rows.
- Shadow data_check: four existing dispatcher wrong-name findings; replaying
  the saved before/after objects proves these identical. Dozer has none.
- find_declared_unmatched.py and class_gate.py, both consumers: pass.
- link_check.py --new-variants, both consumers: pass.
- place_bodies.py, both consumers: zero bodies, zero pins.
- Assertion proof: only the two wrong empty-test copies disappear; every
  retained body and normalized relocation agrees; no new link findings.

The ignored build/wide-empty-link-20261015/ and
build/wide-empty-dispatch-link-20261015/ directories retain snapshots, objects,
strict receipts, source backups, preparation logs and the assertion script.

## Donor review and remaining blockers

Reviewed verified BFME 1 a7c38d3b2597121f178ab5190b3062478823257d, including
TileData constructor-emission repair d3f9000fe08615a100e844adfff57fa4a39cd615.
Its applicable principle is suppressing redundant private COMDAT definitions;
the declaration-only form does not preserve this Dozer caller. No donor code,
layout or identity was imported. BFME 2's already matched owner and emitted
consumer objects establish the repair. Both wrong wide-isEmpty consumer
variants in this index were addressed.

Dozer retains 166 unresolved names, five COMDAT findings and four wrong-selected
dependencies. Dispatcher retains two unresolved globals, one duplicate,
14 COMDAT findings and one wrong-selected NAMEKEY dependency. These require
separate evidence and repair; the complete lists are in object-proof.json.

Official BFME 1 master was fetched at 75ff0c1485a68eafb10344670711edbee8679b62.
The freshness/layout update is held by another worker's live
file:reference/open-bfme-1 claim. The verified gitlink and old success stamp are
preserved; freshness is not marked successful.

Model: gpt-6.1-sol.
