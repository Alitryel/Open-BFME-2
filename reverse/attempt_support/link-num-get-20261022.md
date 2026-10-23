# STLport numeric-reader linking repair

Inputs: BFME 2 `21387ea4c9`; published census/index `ae3b3e68e2`,
2026-10-22 11:05. BFME 1 donor review at
`42bba2ddbd5cb895d99293583891d3b7315fa49e` included the EAString, INI,
MeshClass, MeshRecolor, SortingRenderer, tracker and ShareBuffer linking repairs.
This repair uses the existing BFME 2 STLport providers, not a donor layout change.

Before, `link_check.py` found neither numeric-reader unit linkable:

* `stlport_narrow_num_get.cpp`: 1,181 retail bytes; non-retail signed and
  unsigned 64-bit `__get_integer` COMDATs. The rowed scanner providers are
  `stlport_narrow_get_integer_int64.cpp` (0x8230, 537 bytes) and
  `stlport_narrow_get_integer_uint64.cpp` (0x7ee0, 522 bytes).
* `stlport_wide_num_get.cpp`: 563 retail bytes; competing uint
  `__get_integer` and `_M_do_get_integer` copies differing from the kept copies.

Declare these specializations before the explicit num_get class instantiations,
as these files already do for other separately provided scanners. Suppression
also removes incidental emission of eleven independently rowed helpers. Explicit
iterator instantiations and externally retained function-address anchors preserve
those helpers. These anchors request code emission; they claim no retail data
address. Internal const anchors were discarded by the compiler.

Acceptance on the final sources:

* `./build.sh` scoped to both sources: all 47 matched rows byte-exact.
* `link_check.py --prepare-current` on both sources: all 47 rows, literal,
  float and import checks pass; two strict reusable object receipts.
* `find_declared_unmatched.py`, `class_gate.py`, `eh_verify.py`: pass
  (zero EH rows in these units).
* `link_check.py` on both sources: 2/2 link cleanly, 0 -> 1,744 retail bytes,
  against the same published index. This is the legacy/current-source preview
  result; strict receipts establish the objects, not closed-strict link closure.
  No closed-strict gain is asserted.

Local diagnostic logs: `build/seat-malloc-cohort-before.log`,
`build/seat-num-get-external-anchors.log`,
`build/seat-num-get-self-strict-after.log`,
`build/seat-num-get-final-after.log`.

Separate blocked attempt: ShareBuffer<Vector2> copy constructor 0x15cd00
remains blocked by its O2 RefCountClass deleting destructor versus the retail
O1 provider. novtable breaks the constructor bytes; dllimport inline preserves
them but retains the wrong scalar wrapper and adds an unresolved import. Both
trials were reverted and claims released; the attempt log records the details.

Reference freshness remains incomplete: upstream BFME 1 has advanced beyond the
committed verified pointer 37c3022de1ab944c7ffe536440d637dc8199091c. The old-input
full verification requires 7,758 stale units and remained on the shared compiler
lock; it was interrupted before compilation. No reference pointer or successful
freshness stamp was changed. A future seat must complete the old/new comparison
before updating the pointer.
