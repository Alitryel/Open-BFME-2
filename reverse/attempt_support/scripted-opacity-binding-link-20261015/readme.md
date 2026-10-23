# Scripted animation distance-opacity dependency repair

BFME2 base: `5bc83f98f4358615ca081ca7134a320dec26abf6`.
Consumer: `W3DScriptedProcessAnimationsRva000BFDFE.cpp`, existing processAnimations
row `0x000BFDFE..0x000C0386` (1416 bytes), plus three unchanged helper rows.
Provider: `Draw/W3DModelDrawDistanceOpacity.cpp`, existing 463-byte B5A72 row.

The call at BFE24 formerly used a separate Rva000B5A72 class and void-pointer
declaration. It now names the existing Rva000B5C41 method and forward-declared
Arg000B5A72 argument. Remove the obsolete old-name pin. This changes only the
relocation's C++ spelling; no body, pin, alias, field layout, original method
name or argument identity is newly claimed. The parameter remains an opaque
ABI view. Target call bytes establish the destination and this/module calling
contract; the existing provider establishes its current symbol spelling.

## Paired evidence

The frozen runner index has receipt commit `825b86983f` (2026-10-15 12:37),
underlying census `5986a99448` (04:52), SHA256
`672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c`.
The committed link-status measurement `4b7e7091c4` serves discovery only.
Both phases refresh the saved-before/current consumer and the same
strict-current provider into independent in-memory copies of that index.
No census, index, link status or history was modified.

Unresolved references fall **2 to 1**. All duplicate, COMDAT, address and
wrong-selected findings remain empty. The provider's complete finding set
stays empty. All ten consumer COMDATs are retained; the parent has identical
1416 instruction bytes and exactly one changed relocation spelling at offset
39. All normalized nondebug sections are identical after that substitution.
The other nine COMDAT byte/relocation digests are unchanged. proof.py checks
these facts and no new variants; proof.json records hashes and exact findings.

Legacy local LINKED bytes remain **0 to 0** for the consumer and **463 to 463**
for the provider. New authored C++ bytes: **0**. This is a verified dependency
repair, not a self-strict or closed-strict link gain. The consumer still needs
`?rva000BEE25@Rva000B8F5AOuter@@QAEXPAXMHHH@Z`. Existing deferred reconstruction
of that callee was not retried. The bounded current-ledger preview refuses
**801 missing provider objects**; it never starts a whole-tree rebuild. No
full census, link cycle, nightly, boot or scheduler runner was invoked.

## Checks and remaining data-ledger discrepancy

- Normal whole-consumer gate: **4/4**. Bounded strict preparation of both
  consumer/provider: **5/5**, current reusable receipts; all 19 float references
  verified, no unverified/skipped strings or imports.
- Default local link_check: consumer retains only BEE25 unresolved, provider
  LINKS; exit 1 reflects the documented remaining dependency.
- Pin consistency, class gate, declared-definition, ledger and whitespace
  checks pass. Placement resweep: zero bodies and zero pins.
- EH verification: no applicable rows or missing objects. Converged-data
  enforcement checks both sources at eight addresses: zero second names or
  unjudged rows.
- Optional data_check --enforce reports one **pre-existing** wrong-name at
  0x009E1B40. data_rows.csv and GlobalGetterSingles.cpp already name the sole
  int provider g_bfmeDisplayAnimationSyncClock, while data_ledger.csv retains
  g_Va00DE1B40 and its historical 12-byte inventory extent. proof.py verifies
  identical before/after data findings. No baseline or verifier was weakened;
  the separate data-ledger reconciliation remains outstanding.

## Reference review and triage

Reviewed BFME1 `d003077f0b7ce97622adb7a53f1fe76653433c5c`: direct declaration
of an existing matched provider removes a stale wrapper. The existing-provider
principle applies here; no BFME1 source or layout is imported. Previously
reviewed constructor/allocation suppression repairs do not address this ABI
spelling. Clean donor checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`; official master fetched as
`98f9c4fc7a457bb4c754231e0ed5b073c41db06e`. Freshness remains blocked by
another worker's reference-scope claim and incomplete controlled old-input
comparison. The success stamp and verified checkout were not advanced.

repair_queue.py link and link_rank.py supplied discovery. Many high-ranked
units already link with current objects. A read-only current-object sweep
identified this recoverable declaration mismatch among existing hard missing
providers. LightClass ownership, Apt constructor emission, garrison frame
shape, Apt mask-stack and stream encoding blockers were not retried unchanged.

Run proof.py from the repository root with the saved baseline under ignored
build/scripted-opacity-binding-link-20261015/. Tracked proof files are attempt
evidence; object binaries and preparation backups remain ignored scratch.
