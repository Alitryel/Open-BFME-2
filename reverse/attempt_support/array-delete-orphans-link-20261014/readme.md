# Retire unused array-delete donor pins

BFME 2 base: e04645659d584a1acd4e770ea494dc5ed1c8614d.
Remove 28 obsolete stand-in pins at RVA 0002FD80. The actual pin count and
its keyed hatch allowance both decrease **31 -> 3**. Retain the global
array-delete operator and the two class operator pins. No source definition,
alias directive, function row, layout, ABI or compiler setting changes.

pin-users-before.json enumerates every removed and retained pin. A word-boundary
scan of Code, reference/shims, vendor, functions.csv, data_rows.csv,
data_ledger.csv and pin_consistency_baseline.csv finds no live user of any
removed spelling, including the undecorated C names. The sole text hit is a
historical donor-provenance comment in BfmeConv794.cpp; it remains accurate.
No removed pin is needed by a ledger definition or claimed data row.

Target evidence: the real global operator delete[] owns the 21-byte body
at 0002FD80 in WWLib/mem_ops.cpp. BfmeConv794's previously repaired
bfmeGoDXKa at 00176B60 independently calls that exact symbol: its native
REL32 operand at +25 reaches 0002FD80. objects-before.json and
objects-after.json record strict-current receipts, complete object hashes,
row counts and the native call proof. They are identical. This establishes
the existing allocator destination, without assigning identities to the
discarded stand-ins or adding any target class/layout claim.

Acceptance:

- Bounded link_check.py --prepare-current before and after: 6/6 matched
  rows, two strict reusable receipts, zero skipped/baselined literals and
  one verified named import. Independent ./build.sh: 6/6 exact rows.
- Same-index ordinary local link_check.py before and after: both units
  LINKS, **144 -> 144 legacy linked bytes**, with no findings.
- CSV, pin consistency, declared definitions, class and whitespace checks
  pass. Converged-data enforcement judges eight addresses with zero second
  names/unjudged rows; shadow data checks report zero findings. The staged
  hatch check and normal commit/push hooks are required as well.
- No census index, status CSV, receipt or history is changed. The index
  measures 147cfae2cb at 2026-10-14 07:27; SHA256
  690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a is
  unchanged across the repair. The discovery queue's committed status
  measures 67e1365aa9 and is separate evidence.

Verified improvement is 28 fewer unnecessary pins/escape hatches. New authored
C++ bytes and incremental local linked bytes are zero. Strict reusable
receipts establish object currency and exact bytes; this legacy preview does
not establish self-strict placed linkage or closed-strict closure gains.
Broader link verification remains maintainer work. No full link cycle,
census build/measure/history, nightly, boot or scheduler operation was run.

Donor review: official BFME 1 master fetched at
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed allocator repair
fea964f85433012ec0c95a44a8d88f77b4c29af5: use real global operators and
retire unused stand-in pins. Its repair principle applies directly; no donor
bytes, addresses, names or layout claims are imported. The clean verified
checkout/gitlink remains 23b143233b5a8664a3bdf8572df6d905c310a5a1.
The live foreign file:reference/open-bfme-1 claim
(yasinschroeder-claude2) prevents this seat updating the pointer. Comparative
freshness verification remains outstanding; no success stamp is written.

Discovery checked repair_queue.py link, link_rank.py help/top/near and its
address/unresolved/selected-definition rankings. Already repaired code and
unchanged deferred blockers were not reconstructed. The two ledger files
and both verification witnesses were file-claimed before the edit. Scratch
audit/proof scripts remain untracked in build/array-delete-orphans-link-20261014.
