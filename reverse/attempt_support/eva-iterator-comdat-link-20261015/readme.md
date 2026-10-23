# EVA iterator COMDAT repair

Source base: 596d8d1ad9. Paired local predictions use the same runner index,
825b86983f, dated 2026-10-15 12:37 (original census 5986a99448). See
object-proof.json for index, source, object and current strict receipt hashes.
The committed link_status.csv is queue evidence, not this measurement.

EvaMessageName.cpp defines Rva000411084::next out of line as an exclusive
COMDAT. PlayerUpdate.cpp and LivingWorldManagerXferObjects.cpp already emit
identical inline copies. Give the owner's definition inline linkage and retain
noinline calls, allowing these existing copies to coalesce. The row, identity,
class layout, compiler flags and caller code stay unchanged.

Target evidence: the existing row owns next at RVA 00411084, extent 22. Its
retail body follows the current node's next pointer, calls advance on null,
stores the result and returns this. Its owner and both consumer copies have
retail-truth verdicts. This repair makes no new semantic identity or layout
claim, imports no donor code and adds no pin, alias or escape hatch.

Acceptance:

- build.sh passes all 3 rows, both string literals and all reference gates.
  link_check --prepare-current passes before and after for the claimed owner;
  its resulting object is self-strict current. EH verification: zero EH rows,
  zero missing objects. Frozen definitions, class gate, converged data (eight
  addresses), shadow data, new COMDAT variants and whitespace checks pass.
  place_bodies reports zero bodies and zero pins. check_csv passes.
- The asserting scratch proof is build/eva-iterator-link-20261015/proof.py.
  The old and new objects are both 7955 bytes. Apart from the COFF timestamp,
  precisely one byte changes: the next section auxiliary record's selection
  changes from 1 (NODUPLICATES) to 2 (ANY). All body bytes, relocations, section
  headers, symbol names, external bindings, EH references and directives are
  identical. The 22-byte body-and-relocation digest remains 0c5a3d7117e1.
- Refresh only these three current objects into the same index in memory for
  each prediction. Exactly the next duplicate disappears from each; every
  other finding remains identical and the two consumer objects are unchanged.
  The EVA owner goes from not linking to linking: paired legacy eligible
  existing retail bytes 0 -> 212. The other two units retain independent
  iterator, vector and list blockers. The CLI's census-relative 320 -> 212
  aggregate includes stale census evidence and is not this repair's gain.
- Authored C++ and total matched bytes grow by zero. External providers retain
  legacy census evidence; no closed-strict closure, link.exe placement, fresh
  census gain or data-back gain is claimed. No census, full link cycle,
  nightly, boot or other maintainer-only runner was started.

Selection: repair_queue.py link and link_rank duplicate/COMDAT rankings;
current-object checks distinguish already-repaired units from live blockers.
The particle debug getter already links, so no change or gain is claimed for
it. Existing callback, terrain, destructor-import and compiler-shape blockers
were not retried without new evidence. No per-row data-back artifact was
available or used to rank work.

Reference review: clean verified BFME1 pointer and checkout
a7c38d3b2597121f178ab5190b3062478823257d retained. Existing donor review in
../link-inline-emitters-20261014/readme.md covers allocator declarations and
duplicate inline emission. Inspected upstream de59a7e9 (identical Apt COMDAT
forms) and 66b19a8e (suppress surplus Apt allocation emission). The former's
coherent-copy principle applies; target-specific Apt changes and layouts do
not. The official master fetch observed 4cdfd6e37afae409885e0bb78f2cecb7c269c207.
Freshness update remains blocked by another worker's live reference file
claim and outstanding old/new full-byte comparison. No pointer edit or
successful freshness stamp is made.
