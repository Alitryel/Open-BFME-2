# Apt wrapper row ownership and duplicate removal

At BFME2 a0ff253f2ae22e656a6565763f9b763c3c45512f, rehome two existing matched
rows (0x00216332/104B and 0x0021639A/149B) into BannerUIUpdate.cpp, which already
emits retail-exact copies. Remove the latter's redundant definition from
AptInvokeWrappers.cpp and retire Rva00216332Finish.cpp. No new identity, layout,
pin, global, alias, authored body or matched byte is claimed.

BannerUI's existing caller requires these definitions visible for MSVC's escape
analysis and retail frame sharing. Declaration-only calls would lose that
established compilation property. Keeping the existing noinline inline bodies
and making them the ledger owners avoids competing strong definitions. The
supported local pattern is tools/rehome_rows.py; its all_exact comparison was
performed on these two rows against the already-built home object before edits.
Both resolved bodies equalled retail over their whole extents with zero
unresolved relocations (resolved-body hashes in proof.json). add_match.py
--replace-existing then verified each replacement through the normal gate.

## Measured local improvement

The runner index is the 2026-10-15 14:25 measurement at ac77c85054, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
It is unchanged by this work. Strict reusable compiler receipts were established
for all three initial providers and both surviving providers using bounded
`link_check.py --prepare-current`, which also passed ordinary byte/ref gates.

The same-index paired preview in proof.json uses link_check.refresh/check_object
on saved before objects and strict-current after objects, preserving every
other provider and census order. The deleted source's definitions are omitted
from the after projection because it has no current ledger rows. This removes
its stale definition without rebuilding or modifying the census. Results:

- AptInvokeWrappers: one duplicate -> no findings; 941 retained nonpadding bytes
  change from blocked to locally predicted LINKED. All 11 retained rows match.
- BannerUIUpdate: two duplicates -> zero duplicates; the same five unresolved
  address-view/member names remain. Its 899 nonpadding bytes remain blocked.
- Rva00216332Finish: one duplicate before; retired after moving its 104-byte row.
- No new COMDAT loser, wrong-selected provider, address or unresolved edge.

The prescribed ordinary CLI local check independently reports AptInvokeWrappers
LINKS, LINKED 0 -> 941. Its BannerUI result still reports the retired object's
stale 0x00216332 duplicate because ordinary CLI refresh replaces only requested
objects, not removed providers; the paired projection explicitly accounts for
that omission. No closed-strict or actual full-link gain is claimed. The
read-only `--refresh --current-ledger` preview refuses 700 missing current-ledger
objects (closed-strict.txt); it performs no whole-tree compilation. Maintainer
full link runners were not started. Committed link_status.csv is unchanged.

## Integrity and acceptance

- `link_check.py --prepare-current <three before / two after sources>`: 14/14
  row bodies exact before and after; all string, float and import refs pass.
- All 33 BannerUI COMDATs and every normalized nondebug section/relocation are
  unchanged. Apt retains all 17 other COMDATs unchanged; only the 149-byte
  wrapper, its 26-byte EH cleanup/handler and 44-byte EH metadata disappear.
  The matching SafeSEH entry alone is removed. integrity.json records the
  normalized removed sections and their relocation targets. No directives,
  bindings or live data are introduced.
- `eh_verify.py <two surviving sources>`: nine EH rows EXACT, zero debt.
- `data_check.py --enforce <sources>`: one existing baselined finding, zero
  outside baseline. `--converged`: eight addresses, zero second names/unjudged.
- `class_gate.py`, `find_declared_unmatched.py`, `check_csv.py`,
  `link_check.py --new-variants`, and `git diff --check`: pass.
- `place_bodies.py <sources>`: zero new bodies or pins; no placement changes.

Commands use the two full paths in proof.json. Raw before/after gate and link
outputs, exact EH verdicts, and the closure refusal accompany this record.
Scratch scripts and saved objects remain under build/apt-wrapper-home-link-20261015.

## Reference and other blockers

Official BFME1 master was fetched to eb0f55825, while the clean verified
checkout/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d. Its stale
freshness check remains blocked by the documented unfinished comparative
old-input gate (record 53899: 2982 stale TUs, interrupted after 21 minutes with
2806 remaining) and a foreign reference-scope claim. No unchanged multi-hour
retry, pointer update or success-stamp write was made. Donor repair
66b19a8e95a4add525ef808fcea088e306798e2b was reviewed for its surplus-definition
suppression principle only; no BFME1 code, addresses or layouts were imported.
The established provider/convergence repairs de59a7e9f8, d003077f0b and
2c86b2326 remain reviewed leads, not new BFME2 evidence.

repair_queue.py link and link_rank.py near/U/D/L queues were inspected. Several
high-ranked entries are already fixed in current objects. SpawnBehavior's
lookup COMDAT and GameEngineControl/W3D destructor candidates remain deferred
on their recorded compiler-shape/EH dependencies; their unchanged failed
reconstructions were not retried. This independent duplicate repair completes
the selected task without extending those blocked attempts.
