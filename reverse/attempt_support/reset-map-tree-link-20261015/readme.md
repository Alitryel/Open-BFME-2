# Reset and model erase iterator ownership repair

At BFME 2 revision `bef69669efd01778016cbc1b2fd4409cd9ce7e8b`, both
`InGameUIReset.cpp` and `Rva000B8F5AMapErase.cpp` emitted an incidental external
`_STL::_Rb_tree_base_iterator::operator!=` COMDAT that conflicted with the kept
copy. A TU-local typed iterator comparison removes that competing definition.
The matched callers already inline their comparisons.

`context.json` identifies the measurement inputs: local index revision
`19a2565407`, census revision `5986a99448`, and the index SHA-256. The paired
preview used genuine before/after objects with the same index, refreshing only
these consumers in memory. It did not rewrite the census or link status.

## Verified result

- `link-proof.json`: legacy local findings fall from 4 to 3 for reset and from
  6 to 5 for model erase. Exactly the base iterator comparison finding disappears
  from each consumer; all remaining findings are unchanged. Both consumers remain
  unlinked. This records no self-strict placement or closed-strict gain.
- `object-proof.json`: all 107 retained COMDAT bodies, relocation targets and
  extents are unchanged, as are other normalized nondebug sections and directives.
  The only removed external binding is the 18-byte base comparison. Its local
  typed replacements have no nondebug caller relocations, as did the old helper.
- `./build.sh` passes both rows (717 retail bytes). Strict current-object receipt
  preparation passes before and after; see `prepare-before.txt` and
  `prepare-after.txt`.
- `find_declared_unmatched.py`, `class_gate.py`, `link_check.py --new-variants`,
  `data_check.py --enforce`, and `data_check.py --converged` pass for both units.
  `eh.json` reports no EH-bearing rows or missing objects. A `place_bodies.py`
  resweep finds zero additional bodies or pins.
- The prescribed local `link_check.py` still exits 1 for the remaining findings;
  its output is retained in `link-after.txt`. Authored and linked byte gains are
  both zero; the improvement is removal of two conflicting consumer definitions.

## Provenance and remaining work

The existing BFME 2 tree-iterator repair in
`reverse/attempt_support/tree-iterator-link-20261014/` supplies the same local
ownership pattern. BFME 1 donor repair
`de59a7e9f891b3ed2d4221d151ca881f4b75a583` was reviewed for its treatment of
incidental nonretail COMDAT ownership; its Apt-specific predicate is inapplicable.
The target object and byte evidence above establishes this repair independently.

Reset still needs its BannerUI global provider, iterator increment reconciliation
and vector erase reconciliation. Model erase still needs node allocator,
allocator/proxy, integer comparator and tree erase reconciliation. Those are
separate dependencies. No full link cycle or census was run.

The BFME 1 verified pointer remains `a7c38d3b2597121f178ab5190b3062478823257d`.
Freshness was checked against official master, but the reference update scope is
held by another worker and its existing verification blocker remains unresolved;
no success timestamp or unverified pointer update was made here.
