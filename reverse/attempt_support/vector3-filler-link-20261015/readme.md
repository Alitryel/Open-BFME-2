# Point-list filler link repair

Base: `9a2dd6c2a37daeffd563ef4fe758034c28271b0a`. The paired local measurement
uses the runner index at `a2839ea429`, dated 2026-10-15 13:35, from census
`5986a99448`. Its SHA-256 is in `proof.json`. The differently dated committed
link-status CSV is not used to calculate this improvement.

`Rva00082D6AInit.cpp` emitted an empty external `Vector3` copy constructor
which lost to the first indexed copy. The index establishes no retail address
for that standalone constructor. Neither matched caller references it: their
uninitialised by-value filler operation is already inline. Marking this local
helper `dllimport forceinline` suppresses its standalone emission without
adding an import or changing the filler operation. This does not establish a
canonical Vector3 layout or assert that an empty constructor is the game's
component-copy constructor.

The earlier blocked attempt at this RVA tried component-copy semantics and
changed both callers. This repair takes a different, object-proven route:
remove the unused competing definition while preserving the existing callers
exactly. The neutral identities and layout evidence remain as documented in
the source and its existing ledger entries.

## Acceptance

- Bounded `link_check.py --prepare-current` passes before and after, with
  strict-current reusable receipts. `./build.sh` passes **2/2** matched rows
  (168 and 15 bytes), with zero string, float or named-import references.
- `proof.py` compares saved before objects with the current object. All three
  retained COMDATs and all other nondebug code/data sections are identical,
  including relocation targets. The only removed section is the unreferenced
  five-byte `mov eax,ecx; ret 4` constructor. Only its external binding is
  removed; linker directives are identical and there are no new imports.
- The paired checks deep-copy the same index and refresh the one consumer
  object. Findings decrease **1 -> 0**, and existing authored bytes predicted
  linked increase **0 -> 183**. All other finding categories remain empty.
- Declared-definition, class, enforced-data, converged-data, new-COMDAT-variant
  and CSV checks pass. Neither row has EH data. The placement resweep finds no
  additional bodies or pins. No ledger row, pin, shared header, compiler flag,
  census index or status CSV is changed.

This is a bounded **legacy** local link prediction using strict-current
objects. It is not a self-strict executable-placement or closed-strict gain.
New authored C++ recovery bytes are **zero**. Full link cycles, census rebuilds,
nightlies and boot checks were not run; broader image verification is pending.

Run `proof.py` from the repository root with the ignored snapshots under
`build/vector3-filler-link-20261015`. `proof.json` preserves source, object and
receipt hashes and complete paired findings. The previous source is available
at the base revision above.

## Reference review and handoff

Reviewed BFME 1 repair `53d32d6b4b377317a3397971629ca3ad20b870e9`, which suppresses
incidental Apt string-constructor copies while preserving their callers. The
ownership technique is applicable here; donor layouts and addresses are not
imported. BFME 2 object equality supplies the local acceptance evidence.

The clean BFME 1 checkout and committed pointer remain
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master was fetched at
`95eeb3bef370a7cd730b0ad5f228c317c8756e72`. Another seat owns
`file:reference/open-bfme-1`; its overdue comparative pointer verification is
deferred to that owner. No successful freshness stamp was written.
