# Prototype base destructor link repair

Base: `a86e290c807a130e6420bae148eab8ca6f1b79cd`. Local paired measurement
uses runner index `a2839ea429`, dated 2026-10-15 13:35, from census
`5986a99448`. Its hash is recorded in context.json and proof.json. The committed
link-status CSV describes a different measurement and supplies no gain here.

Rva00136794Ctor.cpp emitted a one-byte, empty virtual GenBase009EB7D0
destructor using a compiler barrier. This first copy displaced the destructor
unit's five-byte tail jump to the existing bfmeResetUB provider. Replace the
empty body with the same reset call used in Rva00136794Dtor.cpp.

Target evidence, independent of donor names: the first unwind actions in the
retail constructor and destructor are 0x765A86 and 0x765B12. Both reload the base
receiver at EBP-0x10 and jump to 0x135E35. The complete five-byte body there
jumps to the rowed reset worker at 0x61ED80. The compiled constructor's unchanged
first unwind action jumps to its destructor COMDAT; that COMDAT now contains
the corresponding reset tail jump instead of returning without cleanup. This
reconciles the existing neutral class spelling without assigning another name
or pin to either native address. It does not establish an original class name.

Acceptance:

- Bounded prepare-current passes before and after: strict reusable receipts,
  six matched bodies verified across the two consumers. The changed source's
  direct build passes 3/3. No string, float or named import references.
- proof.py checks both objects and their exact retained code/data/relocations.
  Only the constructor unit's base destructor COMDAT changes, from RET to
  JMP bfmeResetUB. Every other nondebug section is identical, including EH
  actions and tables; the destructor unit's object is unchanged.
- Paired in-memory refresh of these same two providers against the same index
  removes the sole COMDAT finding. Existing predicted linked bytes increase
  180 -> 402 (+222). Ordinary local link_check agrees, both units LINKS.
- New-variant, declared-definition, class, CSV, enforced-data and converged-data
  checks pass. The placement resweep finds no new bodies or pins.

This is a bounded legacy local link prediction with strict-current source
objects. It is not self-strict executable placement or closed-strict closure.
New authored recovery bytes: zero. No full link cycle, census rebuild, nightly
or boot check was run; broader executable verification remains outstanding.
No flags, pins, ledger rows, shared headers or census records changed.

The proof script runs from the repository root using ignored before snapshots
in build/genbase-destructor-link-20261015. The base revision supplies the old
source; proof.json preserves source/object/receipt hashes and paired findings.

BFME 1 review: committed donor a7c38d3b; reviewed repair 53d32d6b4b37 (incidental
Apt COMDAT suppression). Suppression alone would not repair this required EH
cleanup; target evidence instead supports restoring the destructor operation.
Other inspected near-linking candidates either already link unchanged or have
recorded unresolved EH/provider/layout blockers; those attempts were not repeated.

BFME 1 freshness remains assigned to the other seat holding
file:reference/open-bfme-1. Clean checkout/pointer a7c38d3b is retained after
fetching official master 95eeb3bef370. No successful freshness stamp was written.
