# Distance-opacity math-wrapper link repair

Starting BFME2 revision: cff8ffc6edc009005c2e3e927c103b92b5c1b568.
Local census index: 147cfae2cb, 2026-10-14 07:27 UTC; its SHA256 is
recorded in proof.json. The older committed link_status.csv was used only
for discovery. Neither census nor status was changed.

W3DModelDrawDistanceOpacity.cpp emitted an unused external MSVC sqrtf
COMDAT that differed from the first link-order copy. It was this unit's
only local blocker. Include math.h with the established scoped static-inline
pattern from the portal/geometry repairs. The native caller already inlines
the square root. No call, arithmetic, class view, flag, pin, global, marker,
row extent or identity changes. Its sole row remains the complete 463-byte
0x000B5A72 body; its original method name remains unknown. Existing target,
WorldBuilder and ZH provenance and layout qualifications remain in the source.

Controlled object comparison removes exactly _sqrtf (7 bytes). All four
retained COMDATs have identical raw bytes, symbolic relocations, sizes and
byte/relocation digests. Strong definitions, undefined externals and weak
bindings are identical. proof.json and before/after-facts.json record these
checks; original source/object and dependency backups remain under build/.
The removed loser was not a kept provider and has no remaining external
reference in this object. Other consumers keep their existing provider.

Acceptance:

- Scoped strict reusable preparation before and after: 1/1 complete matched
  rows, two compiler float literals exact, no string or named import refs.
- Ordinary ./build.sh on the changed source: 1/1 matched, full 463-byte extent
  and float checks pass. No new authored C++ bytes.
- Same-index legacy local check: one losing _sqrtf copy -> zero blockers;
  0/1 -> 1/1 clean, existing LINKED bytes 0 -> 463. Strong/undefined/weak
  bindings and kept-provider selection are unchanged.
- New-variants admission, declared-definition, class, enforced data, CSV and
  whitespace checks pass. Converged data: eight addresses, zero second names,
  zero unjudged rows. EH: zero applicable rows. Placement rescan: zero new
  bodies or pins.

This is strict self verification plus a legacy local preview. Closed-strict
closure, actual link.exe placement and fresh measured census gains are not
claimed. No full link cycle, census build/measure/history, nightly or boot
runner was started. The explicit source was refreshed in memory for the local
check; no broad recompilation was needed.

Shared-cause read-only probes of FlightDeckBehavior.cpp,
RailroadGuideAIUpdate.cpp and WorldHeightMap.cpp still find other unresolved
symbols and competing class/math COMDATs. They were not claimed or edited;
their broader provider/class repairs are separate work. An isolated wrapper
edit would not establish that these consumers link.

BFME1 donor review: verified checkout/gitlink
23b143233b5a8664a3bdf8572df6d905c310a5a1. Relevant linking repair
de59a7e9f891b3ed2d4221d151ca881f4b75a583 reconciles Apt isUndefined
COMDAT copies while preserving native callers; the surplus-emitter principle
applies, but no donor type, address or code is imported. BFME2's already
verified geometry-math-link-20261013 evidence supplies the exact header pattern.

Official BFME1 master fetched as a7c38d3b2597121f178ab5190b3062478823257d.
The due verified pointer update remains outstanding: preserved prior
build/link-seat-freshness-20261014/comparison.json records an interrupted
full baseline at e4dfd1e4d73662ad379c496b10168aeab5617f66 with 2,806 stale
TUs remaining, before any new-pointer comparison. That is not a successful
freshness check or evidence of an update regression. Last verified inputs
and the absence of a success stamp were preserved; the unchanged full
comparison blocker was not retried in this bounded link-repair task.

## Preparation recovery

The runner stopped replaying 6730c1055e onto
e7a0806313c524852de5f3748d84d73eb1e67d4c at this source's math.h include.
Upstream 6dfde03620a9ad7d1c2ff0c1002404a53c974c83 already owns the same
repair with push_macro/pop_macro scoping. Recovery retains that exact upstream
source and preserves all 17 saved evidence files and the solved attempt entry.
No code change or additional link gain is attributed to recovery.

The sole rebase stop was resolved and continued without skipping or aborting.
The preparation record names no stash; the stash list and untracked-file list
are empty. The retained backup ref
refs/runner/preparation/1791990090637894822 and original build/ backups remain.
The original evidence files were checked equal to that backup before adding
this recovery note. No other saved edits needed restoration.

Reconciled acceptance at the recorded upstream revision:

- Strict --prepare-current: complete 1/1 matched body, two float literals exact;
  self-strict only, no closed-strict claim.
- Ordinary byte gate: 1/1 matched, complete 463-byte extent, float/string/import
  checks pass (recovery-byte.txt).
- Local link check against unchanged census147cfae2cb: 1/1 LINKS, legacy preview
  0 -> 463 existing bytes (recovery-link.txt). The repair is already upstream;
  this is a repeat confirmation, not a new measured gain.
- Reconciled object matches saved after-facts, ignoring only truth annotations.
  All four retained COMDATs have the original raw bytes and symbolic relocations;
  only _sqrtf is removed from the preserved before-object (recovery-proof.json).
- New-variants admission, declared-definition, class, enforced data, converged
  data, EH, CSV and whitespace checks pass; conflict index is clear.

No census build/measure/history or maintainer-only runner was invoked.
BFME1 remains at the verified 23b14323 pointer; the interrupted full freshness
comparison and broader link verification described above remain outstanding.
