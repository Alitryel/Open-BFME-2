# Quaternion array-transform dependency repair

Source base: `2c3f113b15fa440d92644c9f577e14e10b74bf7c`. Local census index:
`147cfae2cb`, 2026-10-14 07:27. Its SHA256 is recorded in object-proof.json.
The committed status is discovery evidence, not a current measurement.
No census, index, status, ledger, pin, shared header or compiler flag changed.

Rva00168C40QuatTransformArrays.cpp includes quat.h only to name the storage
of four floats. That header pulls in matrix headers and causes MSVC to emit
an unused 50-byte vector-construction helper, `??_H@YGXPAXIHP6EPAX0@Z@Z`.
The census selects the retail 34-byte helper from
Code/Libraries/Source/ATL/atl_vector_constructor_iterator.cpp. The 50-byte
copy is wrong, and is this unit's sole local link blocker.

Use an anonymous four-float aggregate for the existing rotation storage and
retain vector3.h for translation and array elements. Native accesses already
prove rotation X/Y/Z/W at +0/+4/+8/+12, translation at +16/+20/+24 and
12-byte array strides. No Quaternion operations are used. The mathematical
expansions retain their existing WWMath donor provenance; class/method names
remain address-derived because neither target function has a known caller or
data reference. This introduces no new target identity or layout claim.

Acceptance:

- Before and after bounded strict preparation passes both matched functions,
  373 and 358 bytes, with reusable strict compiler receipts. The ordinary
  byte gate also passes 2/2; no literal baseline or skip is involved.
- The saved before object and strict-current after object differ by removal
  of the unused helper and the unnecessary header's debug.lib default-library
  and DebugIncludeInLink1 force-include directives. All four retained COMDATs
  have identical full bytes, extents and relocation names/offsets/types. All
  retained external definitions, undefined names and binding kinds agree;
  __fltused is the only undefined symbol. The remaining default-library
  directives are unchanged. There is no EH data. object-proof.json records
  hashes and assertions; the scratch reproducer is
  build/quat-array-dependency-link-20261014/verify.py.
- Paired local predictions refresh the same unchanged index in memory with
  each object. Before: one wrong-helper COMDAT finding. After: zero unresolved,
  duplicate, COMDAT, selected-provider or hard-address findings. Standalone
  link_check.py agrees: LINKS, legacy local LINKED 0 -> 731 existing bytes.
  Compiler currency is self-strict for this explicit unit. No closed-strict
  gain, actual link.exe placement or maintained census gain is claimed.
  New authored C++ bytes: zero.
- Frozen-definition, class and new-variant checks pass. Converged-data check:
  eight protected addresses, zero second names, zero unjudged rows. EH check:
  zero EH rows, zero missing objects. CSV and whitespace checks pass.
  Affected placement resweep reports zero bodies and zero pins.

BFME 1 linking review used the clean committed donor checkout
`a7c38d3b2597121f178ab5190b3062478823257d` and reviewed repair
`de59a7e9f891b3ed2d4221d151ca881f4b75a583`. Its incidental-COMDAT
reconciliation principle applies; its Apt layout and predicate do not.
No donor source was imported. Official master was fetched at
`58ab850fd1f734e310048b2e19c1ecb7ba112a3f`. Freshness remains blocked on
the existing unfinished old/new full-gate comparison: the earlier old-input
gate needed 2982 stale TUs and stopped after 21 minutes with 2806 remaining
(re_attempts.log freshness records). The bounded repair seat retained inputs,
did not repeat that unchanged multi-hour rebuild, advance the pointer or
write a successful freshness stamp.

Lane probes included repair_queue.py link; link_rank.py top/near/U/L;
twenty current local unit checks; name_globals.py --dry-run (zero edits).
Many census blockers already have source repairs or unresolved recovery
dependencies, and live foreign claims were respected. rehome_rows.py --limit12
cannot run without build/link_census/census.log; that failure is not an empty
queue. No per-row link-cycle status artifact is available for data_back_rank.
No maintainer verification runner or census build/measure/history was started.
