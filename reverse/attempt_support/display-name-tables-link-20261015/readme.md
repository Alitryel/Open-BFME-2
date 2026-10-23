# Display-debug name-table ownership repair

Base: `9194434b7acbe6e6315580447c103b115474ff9a`. The edited display-debug
unit was file-claimed before editing. Retained runner index: `19a2565407`,
2026-10-15 09:33, underlying census `5986a99448`, 04:52. Its hash and paired
results are recorded in `proof.json`; no measurement artifact is rewritten.

The existing gatherAnimationDebuggingInfo body indexed two undefined pointer
tables. Define their existing symbol spellings in its unit and own their full
retail ranges through two data_rows entries: animation-debug names at DB3BB4,
16 bytes, and weapon-status names at DBC7AC, 32 bytes. Target pointer contents,
ten complete strings and two null terminators establish the initializers.
Compiler sizeof independently proves each extent. The existing call sites
establish the roles; original identifier spellings remain unproven. No class,
layout, code identity, pin, alias, import, compiler flag or baseline changes.

Acceptance:

- Bounded strict preparation before and after passes all 14 code rows across
  display-debug, unchanged LivingWorldEyeTowerXfer and Rva0042CB81; 27 code
  literals, 19 empty references and seven floats checked without skips.
  Both new data rows pass full bytes, pointer and string verification.
- `proof.py` proves all 64 pre-existing COMDAT bodies, extents and relocation
  digests identical. Only ten string COMDATs are added; exactly the two table
  symbols change from undefined to defined. Both comparison units retain
  identical nondebug sections and relocations (a receipt rebuild changes
  COFF/debug bookkeeping). Strict current receipts and hashes are recorded.
- Paired local previews refresh precisely the same three explicit objects
  into the same retained index. Display-debug findings go from two unresolved
  names to zero; the other units stay clean. Legacy predicted linked bytes
  are 2,566 -> 5,585, a **3,019-byte** gain attributable to this repair.
  The ordinary local link check also reports all three units LINKS.
  Its printed 0 -> 5,585 census comparison includes the earlier FP-guard
  repair; that earlier gain is excluded from this paired result.
- EH EXACT 1/1; declared-definition, class, CSV, new-variant, whitespace and
  shadow data checks pass. Enforced converged-data check finds no second
  names across eight protected addresses. Placement resweep: zero bodies,
  zero pins.

New authored C++ code coverage is zero; newly verified data coverage is 48
bytes. This is a bounded legacy link prediction using strict-current explicit
objects. It does not establish self-strict executable placement, closed-strict
closure, a new census measurement or runtime behavior. Full link cycles,
census rebuilds, nightlies and boot checks were not run. Their broader
verification remains outstanding.

The name sweep found only this unit declaring either table. Historical queue
entries for getDrawModules, the FP guard and AutoPickUp's filter are already
resolved in current sources/objects and were not retried. The retained index
alone is insufficient to re-serve those stale blockers.

Donor review: inspected BFME 1 `92a8d854746f059994f8ab370c133f3ba71eec24`,
which resolves a debug user's data reference through its verified data_rows
owner. That ownership principle applies; its existing-owner rewrite does not,
because neither target table had an owner. No donor initializer, address or
layout is imported: retail and the target data gate establish this change.
Clean verified BFME 1 checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master was fetched
at `d6862244`; the overdue comparative update remains foreign-claimed on
file:reference/open-bfme-1 and blocked on the previously documented old-input
full baseline rebuild. Verified inputs are retained; no freshness success
stamp or pointer advancement is claimed.

Reproduce the paired proof at the repository root with this session's ignored
saved objects and context under build/display-name-tables-link-20261015.
Model: gpt-6.1-sol.
