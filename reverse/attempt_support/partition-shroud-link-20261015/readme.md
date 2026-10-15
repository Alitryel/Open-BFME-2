Partition shroud provider reconciliation

Base: 9b9d858d4818317584bfc6f300e633a897970b5c. Discovery: repair_queue.py
link, link_rank.py --kind S --near 1, then current local link previews.
The frozen index measures 19a2565407 (2026-10-15 09:33), census ancestry
5986a99448. Its exact SHA256 is in object-proof.json. The committed
link_status.csv measures a different tree and is not used for gains.

PartitionManager.cpp still defined the 455-byte unrowed ZH
PartitionData::getShroudedStatus. The recovered BFME2 body is independently
rowed at 0x0073A6D0 (392 bytes) in PartitionDataShroudStatus.cpp. It replaces
the donor's reset guard, cell/status layout and visibility bookkeeping;
the native body's existing target and donor evidence remains in that source.
Remove the obsolete definition and its present-unmatched marker. Its unused
4-byte getUpdatedSinceLastReset accessor stops emitting automatically.

The recovered provider also emitted a 36-byte PartitionCell helper under
the donor method's external name. The donor copy reads [this+player*4+8]
and compares 1; the recovered private view reads [this+player*8+4] and
compares 0xFFFF. They have no relocations and are different instruction
bytes. Rename the partial recovered view to PartitionDataShroudCellView,
leaving its bytes intact; no additional application identity is inferred.
Its parent remains the exact same 392-byte native body. The pair of strictly
current objects now shares zero defined names, down from two conflicting
names (the parent and the inline cell helper). No new pins, data globals,
aliases, compiler escapes, class layouts or ledger rows are introduced.

Acceptance:

- link_check.py --prepare-current before and after, and ordinary build.sh,
  verify 11/11 rows across both owners and ObjectGetShroudStatusForPlayer.
  All three have strict reusable current receipts. One string literal is
  verified; no compiler float literals or named imports occur. EH EXACT 1/1.
- proof.py checks every retained nondebug section, raw bytes, characteristics,
  symbolic relocations and names. The legacy unit changes only by deleting
  the two obsolete bodies; all 1,188 retained COMDAT bodies stay identical.
  The recovered unit changes only the cell-view name. The consumer is
  unchanged. Baseline source/object/receipt and after objects/receipts remain
  under ignored build/partition-shroud-link-20261015 for reproduction.
- Frozen definitions, class gate, CSV, new-variant admission and enforced
  converged-data checks pass. Hatch use decreases by one present-unmatched
  marker. The unchanged consumer retains one pre-existing shadow data finding
  for the local HeroDie name-key static; no data finding is introduced by
  these edits. The full findings and command exit codes are in checks.json.
- place_bodies.py on both affected owners finds zero additional bodies/pins.

Measurement limit: the retail provider landed after this census and is absent
from its object universe. Do not append it or invent a link position.
Paired same-index diagnostics refresh only the two indexed objects. They
confirm removal of the bad parent COMDAT/selected findings; the consumer's
selected-wrong diagnostic becomes unresolved because that index cannot see
the retail provider. The prescribed CLI refuses previewing the new provider
as "not in census". PartitionManager also retains its unrelated unresolved,
duplicate and COMDAT debt, all listed in object-proof.json/checks.json.

This is self-strict byte proof and direct removal of two owner-name conflicts.
It claims zero new authored bytes, zero LEGACY predicted linked-byte gain,
no closed-strict result, no census gain and no full-link/runtime result.
The runner's next census must include the recovered provider before it can
measure placement/closure. No maintainer-only runner was started.

BFME1 linking review: retained verified donor pointer
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched
read-only at 9bbab7963c3dac0ef8da8c46860e972ecbafe29d. Reviewed donor
262d3e9507d68409d7cf86e730f4c75eefa58ccd (remove an obsolete ZH
Convert_To_Ver2 copy once a native provider exists) and d003077f0b7ce97622adb7a53f1fe76653433c5c
(declare and call the real provider instead of emitting a second copy).
The obsolete-provider pattern applies here; target-specific layout and byte
proof come from BFME2, and no donor source/settings are imported. The donor
pointer is held by another worker; the already recorded comparative-full-gate
freshness blocker persists. No pointer advance or freshness stamp is claimed.

Queue triage: current previews already link multiple high-ranked module,
drawable, AI, vector and damage consumers that the stale index still ranks.
Garrison load remains banked on frame allocation; the LightClass removal
remains blocked by orphan inline-row ownership. FreeLifeBodyApply is peer
claimed. None was edited or retried. This session completes the supported
partition provider repair without extending those unrelated reconstructions.
