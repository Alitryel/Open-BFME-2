# Unsigned-word vector provider repair

At BFME 2 `474e999e64`, the current word-vector unit has two blockers in the
published runner index (census `144ed0ccab`, 2026-10-20 15:34): its unused
allocator-proxy copy loses to the first provider, and wide_stringbuf keeps a
non-retail unsigned-word fill loop before the verified word-vector copy.

The allocator specialization preserves the STLport header's exact inline
operation and marks it dllimport/forceinline so the unused external copy is
not emitted. This follows the existing BFME 2 wide-proxy repair and the reviewed
BFME 1 `66b19a8e95a4add525ef808fcea088e306798e2b` technique. Donor evidence is
technique only; BFME 2's own bytes and current object findings establish this
application. Current BFME 1 pointer reviewed: `4483e88da1c2f3b9a273f779baac7458bd8bb891`.

The wide-string-buffer unit declares the unsigned-word fill and its two
forwarding wrappers without defining competing bodies. The new-variant check
caught the wrappers changed by the initial fill-only declaration; binding both
to their existing providers removes those new variants. No imports or alternate
names are added to the matched bodies. No layout, runtime operation, pin,
verifier, baseline, ledger ownership or retail coverage changes.

`paired.json` refreshes exactly these two before objects and then their after
objects into separate copies of the same frozen index. Local legacy linked
bytes rise **0 -> 577**, all in stlport_vector_word_o1.cpp. Strict-current,
byte-verified receipts exist for both cohort objects before and after; the
external index providers have not all been refreshed, so this is not a
closed-strict or census-wide gain. The wide-string-buffer unit itself still
has its previous string destructor, append and dispatch blockers.

Acceptance: normal byte gate **9/9**, strict preparation before/after, no new
COMDAT variants, EH (zero EH rows), enforced data and converged-global checks,
class gate and declared-definition checks pass. Placement rescan finds no
additional bodies or pins. Companion proxy/fill providers PeerThread,
ChatSendChat and GSConfig still have independent blockers; they are left alone.
The broad read-only rehome search found only already-linking or previously
blocked placements and was interrupted after checking many homes. No full
link cycle, census or maintainer-only runner was started.

Scratch sources, before objects and command logs: `build/link-word-oct20/`.

## 2026-10-21 publication reconciliation

Rebasing the unpublished repair onto the concurrently landed UTF16 provider
work left two definitions of the same imported inline allocator specialization.
The push hook correctly rejected MSVC C2995. Remove only the duplicate; the
upstream specialization already preserves the identical STLport operation.
Current self-strict preparation passes all seven rows and all reference checks;
the unit is no longer a compilation blocker for this outgoing batch. This is
a prerequisite repair of the named word-vector unit, not additional linked
coverage. The original paired 577-byte measurement above used the older index.

The current 03035cf02c legacy index also contains a newly recovered Thai sentence
consumer's non-retail resize COMDAT, so a single-unit current preview still
links zero bytes (duplicate resize and the unrefreshed wide-string fill owner).
The Thai consumer's declaration-only control changes its 2151-byte parent;
restore its original and verify 2/2 rows. This remaining ownership/visibility
problem is separately logged and its claims released. No closed-strict gain
is claimed. Diagnostics: build/word-rebase-repair/, build/word-rebase-*.log.
