# Local list-iterator comparison repair

BFME2 base: `00a8045a35e1f08cb4b88e7aa115483379004ba5`.
Consumers:

- `HordeMeleeHoldGroundRva005D7011.cpp`: 377 matched bytes.
- `MilesAudioAdvanceMusic.cpp`: 318 matched bytes.

Both units emitted an unused external STLport list-base inequality whose body
differs from retail. A TU-local typed inequality compares the same node pointers
and suppresses that conflicting emission. The source pattern is already used
by BFME2's Miles audio pool initialization and other iterator repairs. This
changes no flags, shared headers, layouts, identities, pins or ledger rows.

## Paired evidence

The before and after objects are refreshed independently into copies of the
same published index: census `ac77c85054`, 2026-10-15 14:25. Index SHA256:
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
The index, census and committed link status are unchanged.

All 18 retained horde COMDATs and all 13 retained music COMDATs have identical
bodies, sizes and relocation digests. Each removed external comparison has no
incoming nondebug relocation. Each added private comparison is also
unreferenced. Every other normalized nondebug section, external binding and
linker directive is identical, including EH data and unwind code. Local labels
are compared by their target section and offset; `.sxdata` by symbol name.
Paired data facts are identical, with zero findings.

Each consumer's current-object local findings decrease **1 to 0**. The paired
proof asserts that removing this single COMDAT conflict is the only change.
Default local `link_check.py` passes both files: legacy predicted LINKED
**0 to 695 bytes**. New authored C++ bytes: **0**. Strict reusable object
receipts establish compile currency, not self-strict or closed-strict placement
gains. Those gains have not been measured. No full census, link cycle, nightly
or boot runner was started.

## Acceptance

- Before/after explicit `link_check.py --prepare-current` passes each unit,
  with strict reusable receipts and no provider expansion.
- `./build.sh` passes both matched bodies; one compiler float, zero string or
  named-import discrepancies.
- `eh_verify.py`: music parent EXACT 1, zero exceptions or missing objects;
  the horde row has no EH record.
- Enforced data checks: zero findings. Converged check: eight addresses,
  zero second names or unjudged rows.
- Local link prediction and `--new-variants` pass both consumers.
- Class gate, declared-definition check, CSV ledger check and whitespace
  check pass. Affected-unit placement rescan returns zero bodies and zero pins.

`object-proof.json`, `link-proof.json`, `data-proof.json`, `eh.json`,
`receipts.json` and `acceptance.txt` retain the paired checks and hashes.
The proof scripts run from the repository root using the corresponding
`build/holdground-list-link-20261015` snapshots and frozen index; object files
remain untracked scratch. Both file claims were held during the repair.

## Queue, donor review and handoff

Discovery used `repair_queue.py link`, `link_rank.py` and the fetched published
index. The list-base conflict appears in 17 census consumers. These two are
the only ones for which it is the sole blocker; the other 15 each have 3-44
additional findings requiring separate investigations (`sweep.json`). Stale
queue entries already fixed in the current sources were skipped.

Reviewed BFME1 linking repair
`d003077f0b7ce97622adb7a53f1fe76653433c5c`: removing a duplicate wrapper
emission preserves matched callers and lets the real provider win. That is
supporting method evidence; no donor body, layout or identity was imported.
Official BFME1 master was fetched at `95eeb3bef370`; the clean verified
checkout/gitlink remains `a7c38d3b2597121f178ab5190b3062478823257d`.

The overdue reference update is still separately claimed. Its previous-input
full-gate comparison was interrupted after 21 minutes with 2806 stale TUs
remaining (2982 initially), as already recorded in the attempt log. The
freshness stamp is not advanced and the verified inputs are retained. Broader
link placement and that reference update remain outstanding.
