# Horde damage callback integer-construction link repair

Base: `9333e3e53e14d9b1a4afd469b2ed20041b72fb58`. Retained runner index:
2026-10-15 09:33 at `19a2565407`, from census `5986a99448`.
`context.json` records its hash. The committed status CSV has a different
measurement and is not used to calculate this paired improvement.

The callback emitted a nonretail external `_STL::_Construct<int,int>` copy.
Its real provider is the complete 17-byte row at `0x00620140` in
`stlport_deque_int.cpp`. A file-static placement-construction overload preserves
the vendor operation without emitting a competing external definition. This
uses the existing approach in `AIBuilderUpdate.cpp` and other integer-list
consumers. No class, alias, pin, import, compiler flag or ledger row is added.

Target identity, boundary and field evidence remain those of the existing
539-byte callback at `0x004BB176`: named factory, secondary vtable and native
accesses documented in its source. This repair establishes no new layout or
semantic name. The helper's placement construction comes from STLport's vendor
implementation; its null guard and store are also visible in the compiled
objects. Byte equality is the acceptance evidence for the target callback.

## Acceptance

- Ordinary byte verification passes **1/1**, with its float literal checked.
  Bounded preparation establishes strict reusable receipts before and after.
  The unchanged shared provider passes **24/24** with a strict receipt.
- `proof.py` compares saved before and current objects: all **35 retained
  COMDATs** have identical bytes, sizes and relocation digests; all remaining
  nondebug sections and directives are identical, except replacement of the
  unused 17-byte external helper by a 9-byte file-static helper. Both helpers
  have zero nondebug references. The new helper uses local storage class 3,
  adds no external binding and has no relocations. A first ordinary-inline
  trial also matched; force-inline retains the same local helper emission.
- Paired previews deep-copy the same retained index, refresh only the caller
  and the same strict-current provider, and report caller legacy findings
  **1 -> 0**, linked existing authored bytes **0 -> 538**. The provider is
  unchanged between these previews and remains **LINKS, 960 bytes**. Its saved
  witness was taken after strict preparation, rather than from the earlier
  ordinary cached object. No stale-provider improvement is credited.
- Ordinary `link_check.py` reports both units LINKS, **960 -> 1,498 bytes**.
  Declared-definition, class, data, converged-data, new-variant and CSV checks
  pass. The callback's EH graph is **EXACT**. Placement resweep finds zero
  additional bodies or pins.

The proof runs from the repository root with ignored saved objects under
`build/horde-int-construct-link-20261015`; its hashes and results are preserved
in `proof.json`. No census index or status is rewritten. New authored C++ bytes
are zero. This is a bounded local legacy improvement with strict-current
objects, not self-strict executable placement or closed-strict closure. Full
link cycles, census rebuilds, nightlies and boot checks were not run; broader
linked-image verification remains outstanding.

## Related work and reference review

`sweep.json` records all seven retained-index consumers of this exact blocker.
The six others have additional independent findings. `Rva00396E4ARemove.cpp`
is foreign-claimed; the remaining formation, chat, audio, animation and special
ability units are follow-up candidates requiring their own current-object
checks. No improvement for them is claimed. The callback is the only consumer
for which this helper alone prevented linking. Initial local checks also
confirmed independent UV-buffer constructor and transition-record destructor
blockers; neither was edited or retried.

Reviewed BFME 1 repair `d3f9000fe08615a100e844adfff57fa4a39cd615` and reused
the prior ownership review: remove an incidental competing definition while
preserving the retail caller. Its donor-specific TileData layout is inapplicable;
no donor source, ABI or address is imported. BFME 2's own helper owner, caller
bytes and object comparison establish this change.

The clean verified BFME 1 gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master was fetched at
`e27a65cb6bd7b2b3cc8ee320ef7ef8a3797b1d0e`. The overdue comparative pointer
update is held by `codex-6bc6-20261008` on `file:reference/open-bfme-1`;
verified inputs and the old success stamp are preserved. No freshness success
is claimed. The index fetch retained the newer runner index and restored
published objects to the cache.
