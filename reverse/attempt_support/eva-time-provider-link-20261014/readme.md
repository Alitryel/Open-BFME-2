# Eva timing accessor: one verified provider

At BFME 2 commit `22f22abcf35179f0cfc5a7defeeab8d08d496c30`, both
`Code/GameEngine/Source/GameLogic/System/Rva001DCDAF.cpp` and
`Code/GameEngine/Source/GameClient/EvaRva001DDF04.cpp` strongly defined
`?rva001DCE4C@Rva001DCDAF@@QAEMPBUArg001DCDAF@@@Z`.
The ledger owned the accessor in the first unit. Its definition must stay visible
in the Eva unit: the existing retail caller retains edx and xmm0/xmm1 across
that call, as documented in the matched caller's source.

Both compiled accessor copies reproduce the complete 31-byte retail body at
`0x001DCE4C`, including the unsigned conversion constant relocation at offset
21 (`__real@4f800000`, DIR32). This repair repoints the existing row to Eva and
removes the other definition. It adds no recovered bytes or symbols. Target
evidence establishes the body, relocation, field access and caller relationship;
the private view's names remain structural labels, not new retail identities.

The read-only BFME 1 donor review used verified checkout
`a7c38d3b2597121f178ab5190b3062478823257d` and reviewed upstream repair
`d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`: dropping redundant BfmeStrVKI
constructor bodies in favor of a retail provider. Only its general provider
reconciliation pattern applies here; no donor code, alias, ABI or address was
imported. Official upstream was fetched at `58ab850fd`; the verified pointer
was retained because the previously recorded same-revision full comparative
gate remains blocked on thousands of stale objects. The freshness success stamp
was not advanced.

## Measurement and checks

The before and after paired `link_check.py` checks use the same runner census
index, measurement commit `147cfae2cb`, timestamp `2026-10-14 07:27`, SHA256
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
Both selected objects were prepared with strict reusable receipts and ordinary
whole-source gates before and after. The index and committed census status were
not rewritten. Discovery queue status at `de7bb30890` is not this measurement.

* Before: both units fail on the duplicate accessor; Eva also has the iterator
  COMDAT conflict listed below. Paired legacy LINKED total is 0 bytes.
* After: `Rva001DCDAF.cpp` links, accounting for 192 existing matched bytes.
  Eva still fails; paired legacy LINKED total is 192 bytes.
* `link_check.py --prepare-current` passes all five ledger bodies, string,
  float and import checks, using two strict-current owned objects.
* Object comparison proves that only the duplicate accessor COMDAT and its
  strong external definition were removed. All six retained helper-unit COMDATs
  and all 20 Eva COMDATs retain their bytes and relocations; ordinary sections
  are unchanged. Both before copies and the surviving after copy have exact
  whole-body size 31, matching retail without alias masking or unresolved calls.
* Local `--new-variants` admission passes. Frozen-definition and canonical-class
  checks pass. Enforced converged-data check: two sources, eight addresses,
  zero second names and zero unjudged rows. Ledger and diff checks pass.
* `place_bodies.py` rescans both affected units: zero bodies and zero pins.

The strict receipts prove the touched providers' currency; the **192-byte gain
is a legacy census prediction**, not a closed-strict result. The permitted
`--refresh --current-ledger` preview refuses 439 missing current-ledger objects
without compiling them. No closed-strict gain or full-link result is claimed.
No maintainer-only verification runner was started.

## Remaining blockers

Eva's `??9_Rb_tree_base_iterator@_STL@@QBE_NABU01@@Z` differs from the first
copy in census link order; no retail address establishes the winner. The repair
does not choose an iterator implementation or change that shared dependency.
Full current-ledger closure and the BFME 1 update comparison remain outstanding.
The attached logs and snapshot hashes allow the local before/after result to be
distinguished from those broader checks. Reproduction scripts and object
snapshots remain untracked under `build/eva-time-provider-link-20261014/`.
