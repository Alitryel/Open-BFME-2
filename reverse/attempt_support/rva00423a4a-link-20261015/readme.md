# Rva00423A4A destructor provider reconciliation

Two size-only element views defined an empty `Rva00423A4A` destructor. Remove
those definitions and retain external declarations, allowing the existing
vector-owning definition in `stlport_vector_rva00423a4a_single.cpp` to supply
destruction. No class name, layout, pin, ledger row or compiler flag changes.

## Evidence and scope

The matched holder constructor at 0x00423A4A constructs a vector of pointers;
the matched count constructor at 0x0042499E constructs the same 12-byte element
as a temporary. That unit's destructor releases the vector allocation
(`mov eax,[ecx]; test eax,eax; ... call _free; ret`, 14 bytes). The two other
units established only the element's size and nontriviality. Their empty
destructors asserted unsupported lifetime behavior and took precedence in the
linker's first-copy order. Keeping their size-only representation while
declaring destruction externally removes that assertion. This is a structural
lifetime inference from existing target-supported views; no original retail
class name or independent address for this destructor is claimed.

The two edited views now generate calls to the existing destructor in their
element cleanup helpers. The six affected cleanup COMDATs in `Rva0042476C.cpp`
and five in `StlportVectorCopyCtorFamily.cpp` are enumerated in `proof.json`.
Every other retained COMDAT is unchanged. Exclusive definitions and weak
bindings are unchanged; the only additional undefined external in each edited
object is the destructor, resolved by the existing vector-owning unit.

## Controlled acceptance

Base checkout: b5f310ba55. Census measurement: ac77c85054, 2026-10-15 14:25 UTC.
The exact index SHA-256, before/after object and strict-receipt hashes, provider
selection and complete per-unit findings are recorded in `proof.json`.
The same three object slots are replaced in separate in-memory copies of that
index; the on-disk index and census/status files are unchanged.

- `./build.sh` on both edited sources: 9/9 matched functions pass.
- `link_check.py --prepare-current` on both edited sources and the destructor
  provider/consumer: 12/12 matched functions pass; all three objects have strict
  reusable receipts. Matched bytes and symbolic relocations also equal the
  saved before objects independently in `proof.py`.
- `eh_verify.py` before and after: all 9 EH-bearing rows EXACT, verdicts equal.
- `link_check.py` on all three sources: the count/LightSubPoint constructor
  unit becomes link clean, **legacy local LINKED 0 -> 150 nonpadding bytes**
  (107-byte count constructor, 33-byte LightSubPoint constructor and 10-byte
  handler). Other two units retain their identical unrelated findings.
- `link_check.py --new-variants` passes. The proof repeats admission with
  original census debt, peer replacement and current link order.
- `data_check.py --enforce`: zero findings; before/after data bindings equal.
  `data_check.py --converged`: 8 addresses, zero second names or unjudged rows.

This is +0 newly authored C++ bytes. **No closed-strict link gain is claimed**:
the rest of the index is the runner's census snapshot, not a refreshed strict
dependency closure. No maintainer-only runner was started. Current-unit strict
receipts establish self-strict byte validity, not whole-program linkability.

Reproduction while the ignored before snapshots remain available:
`python3 reverse/attempt_support/rva00423a4a-link-20261015/proof.py`.
The snapshots and their source backups remain in
`build/rva00423a4a-link-20261015/before/`.

## Reference review and remaining blockers

Reviewed BFME 1 lifetime repairs 121fc40f6a502481e19d1b9fa7964248edcefd97 and
cd216a2e81babe49c0ceac937559111fbf35bb32, which forward private lifetime views
to existing shared destruction. They support the investigation strategy, but
their download/FXList classes and BFME 1 addresses are inapplicable here. No
donor body or layout was imported. No same-named Rva00423A4A donor definition
was found in the available BFME 1 game source.

BFME 1 stays at verified pointer a7c38d3b2597121f178ab5190b3062478823257d.
Its freshness check is overdue; the submodule update is held by another
worker's live `file:reference/open-bfme-1` claim. The fetched upstream master is
d21d4bc6; a controlled old/new full-byte comparison and pointer migration remain
that worker's work. No successful freshness stamp was written.

The two edited units still have allocator, copy/construct and unrelated element
cleanup conflicts listed without change in the proof. Canonicalizing the full
seven-unit class family or repairing those independent providers remains
separate work; this change removes the unsupported empty lifetime definitions.
