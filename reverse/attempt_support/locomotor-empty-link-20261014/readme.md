# Locomotor pointer-vector link repair

Two existing parser consumers inline STLport's pointer-vector emptiness test
but emit a competing `vector<const LocomotorTemplate *>::empty` COMDAT.
`AIUpdate.cpp` owns its independently byte-verified 13-byte retail body at
RVA 0x00142C90. Compare `begin()` and `end()` in a file-local forced-inline
helper instead. STLport `_vector.h` establishes the equivalence: these return
`_M_start` and `_M_finish`, the two fields compared by `empty()`.

Both normal row byte gates pass (223 and 302 retail bytes). The saved before
objects and current after objects have identical retained COMDAT bytes,
extents, relocation bindings, nondebug ordinary sections and linker directives.
The only deleted definition is the conflicting 11-byte `empty()` copy. The
only added external definitions are STLport's const `begin()`/`end()` accessors
(3/4 bytes, no relocations); the new-variant check passes. No undefined symbol,
global datum, pin, baseline, compiler flag or escape hatch was added. These
incidental accessors are not reported as newly recovered retail bodies.

## Measurement and scope

Base checkout: 965dcca8cd3c37e94ddf81cf63f528990ea5cee4.
Local census index: **147cfae2cb, 2026-10-14 07:27**; SHA-256 is recorded in
both object proofs and remained unchanged. `reverse/link_status.csv` belongs
to a different measurement and is not the basis of the claim.

`LocomotorSetSetLocomotorAndBaseSpeed.cpp`: same-index local legacy preview
loses its only finding and changes **0 -> 222 authored linked bytes**.
`AIUpdateParseLocomotorSet.cpp`: its empty conflict is removed; **0 -> 0**
linked bytes, with all eight remaining findings unchanged: two node allocator
import references, a duplicate and wrong-selected parseLocomotorSet provider,
getLoadType, allocator::allocate, allocator::deallocate and allocation-proxy
deallocate COMDAT differences. These need separate supported repairs.

Both changed consumers have current **self-strict reusable receipts**, obtained
with bounded `link_check.py --prepare-current`. The retail empty provider passes
its named byte gate; its full strict receipt is not current. No closed-strict
closure, new census result, actual linked executable or full link-cycle gain is
claimed. New authored retail bytes: **0**.

## Acceptance

- `link_check.py --prepare-current` for each changed source: passed normal
  byte, string, float and import gates and prepared current strict receipts.
- COFF comparison and same-index before/after previews: passed (object-proof.json
  and peer-object-proof.json). Original source/objects remain in ignored
  `build/locomotor-empty-link-20261014`; base sources are recoverable from git.
- Paired local `link_check.py`: first source LINKS, peer retains exactly the
  eight independent findings listed above (expected exit 1).
- `link_check.py --new-variants`, `find_declared_unmatched.py`, `class_gate.py`,
  `data_check.py --converged`: passed for both consumers.
- `eh_verify.py`: no matched EH data; `place_bodies.py`: no bodies or pins.
- `check_csv.py` and `git diff --check`: passed.

## Reference review

Retained BFME 1 pointer: a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed donor linking repair de59a7e9f891b3ed2d4221d151ca881f4b75a583:
its separation of incidental helper copies from verified retail ownership is
applicable; its types/layouts are not imported. This repair uses BFME 2's current
provider, STLport declarations and independently verified caller bytes.

Freshness remains outstanding: fetched BFME 1 master is
58ab850fd1f734e310048b2e19c1ecb7ba112a3f. The preceding session's full old/new
verification stalled refreshing thousands of dependencies. The last verified
inputs and pointer were retained; no successful freshness stamp or pointer
advancement is claimed. No census build/measure/history or maintainer runner was
started in this session.
