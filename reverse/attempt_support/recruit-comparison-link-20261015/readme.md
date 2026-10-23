# Recruitment comparison link repair

`Rva0059DD3FRecruit.cpp` no longer emits the losing shared
`_Rb_tree_base_iterator::operator!=` and `less<int>::operator()` copies.
A TU-local typed iterator comparison and the established imported-inline
integer comparison retain STLport semantics. Swapping the operands of the
unsigned vector-size sum preserves the original native load order; its value
and overflow behavior are unchanged.

Baseline source: 94f8b9616be649596056e987a78e7bb228f3346c.
Measurement index: 28269d8e8d, 2026-10-15 09:31; SHA256 in object-proof.json.
The bounded cohort is the recruitment consumer and existing integer-comparison
provider `Code/Libraries/Source/WWVegas/WWLib/stlport_list_int.cpp`.
The provider source and object are unchanged. No ledger, identity, layout,
address, pin, alias, shared header or verifier changes.

## Acceptance evidence

- `link_check.py --prepare-current` on the explicit two-source cohort: 5/5
  matched rows, strict reusable receipts; strings, floats and imports pass.
- `./build.sh` on the consumer: its complete 545-byte native row passes.
- `eh_verify.py`: 1 EXACT EH row; `find_declared_unmatched.py`: all matched.
- `data_check.py --converged` on the cohort: 8 addresses, no second names or
  unjudged rows. `place_bodies.py` on the consumer: 0 bodies, 0 pins.
- Paired checks replace the same object names in separate in-memory copies
  of the unchanged census. Losing COMDAT findings decrease from 5 to 3;
  the existing wrong-selected ScienceType allocation helper remains.
- Every retained nondebug COFF section, full body extent, data section, EH
  section and symbolic relocation is identical. The compiler also emits one
  unreferenced 12-byte internal comparison outline: no external binding and
  no incoming nondebug relocation. It claims no retail row or new bytes.
- Both shared comparison winners and all other copies' selection results
  remain unchanged. Provider findings are unchanged; no new variants.

This is a self-strict, bounded local improvement: **2 losing copies removed,
0 new authored bytes, 0 legacy linked-byte gain**. The consumer still has
ScienceType vector base destruction, allocate/copy and overflow conflicts;
the allocation helper is also wrong-selected. No closed-strict gain, census
change, full link, boot or runtime verification is claimed.

The first overload trial changed only the order of the two vector-size loads;
reordering the commutative sum recovered the exact body. A later direct-node
comparison experiment changed that instruction order again and was discarded.
The final overload form is the verified one. Two other investigations are
recorded in re_attempts.log: the Apt counted-key destructor needs cross-unit
identity reconciliation, and ChatWindows overflow suppression changes the
native caller (the class extern-template alternative removes no copy).
Both claims were released and both source files restored. ChatWindows was
byte-verified again after restoration.

Donor review reused the unchanged a7c38d3b2597121f178ab5190b3062478823257d
review in ../link-inline-emitters-20261014/readme.md: duplicate forwarding
and unnecessary inline-copy repairs are applicable as techniques; no donor
address, layout or body is transplanted. Existing BFME 2 typed-comparison
and imported-inline repairs supply the local precedent. Upstream BFME 1
master was fetched at session start, but its reference path is held by another
seat's live file claim. The verified pointer was retained and no freshness
success stamp was written.
