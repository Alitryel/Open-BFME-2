# Crack-d wave 5: reproducible findings

Lane began at de7bb30890 and refreshed against a4d6996c34 after three landings.
The initial top 25 and refreshed top ten are in the machine-local
`~/crack-seats/d.rank.md`. Ranking uses latest-per-RVA records and deduplicated
transitive blocked bytes, with size-weighted scores >= .95. Claims and the
priority A/B/C seat assignments are excluded. No census or runner was started.

## Verified transfers

* **006D77B0, 685 bytes**, WB0177F430: delimiter construction, argument lookup,
  then limit initialization match the debug lifetime order. The ordinary and
  final segment each own their AptString local; incrementing the loop index
  inside the segment-string scope before destruction restores cleanup order.
  The complete body matches without the bank's barriers or conditional no-ops.
* **006D7D80, 1856 bytes**, WB0177FAB0: after the split provider landed, the
  property dispatcher matched directly. Its 13 cases use the existing twelve
  cache globals and matched callbacks. The extent ends at 006D84C0, including
  the 52-byte switch table. The inventory's larger extent consumes the adjacent
  integer constructor. The assertion path must preserve exact backslashes.
* **002A3E5A, 252 bytes**, WB00DC4300: making STLport's actual lower_bound body
  visible changes the bank's .871106 / 251-byte result to .986639, restoring
  the 0x1c frame and key/decal register roles. The actual multimap::insert
  wrapper then restores the returned-iterator load from the reused argument
  slot, producing all 252 bytes. Canonical string types preserve the result.
  The existing home file was claimed by another owner, so the final getter
  lives alone in FormationPreviewPoolLookup.cpp.

All three passed complete body, relocation, string/float/import and exact EH
checks through normal commit hooks. Rescanning each unit placed no additional
bodies or pins. link_check had no census index; no full-link claim is made.

The split unlock is concrete: its 1856-byte caller is now also recovered.
The pool removes one prerequisite for updateFormationPreview's 2462 bytes;
that parent still depends on 002A4BFC and 0029D9F9. Do not credit those bytes
as recovered or fully unblocked.

## Retained partials

* **006EE6C0**: .988992422 / 3749 bytes. Thirty-one parent-loop, visible
  predicate, shared-return and color-store trials did not improve the bank.
  The remaining parent reload/register cluster and shared success-return
  layout need a new source hypothesis.
* **0009B28C**: .975533093 / 644 bytes. Fifty-six helper-visibility,
  trigonometric-contract, real local-lifetime and color-copy trials did not
  move the final UCOMISS/MOVSS/POP ordering. All direct callees resolve.
* **001F1609**: .573046252 / 14 versus 43 bytes. See
  `crack-d-allocator-eh.md`: diagnostic ways to retain state 0 either introduce
  a nonexistent import in the unwind graph or misrepresent object lifetime.
  The honest bank is retained; parent-only equality is insufficient evidence.
* **002A4BFC**: the old .85 metadata remeasures .818939884 / 545 versus 547
  bytes. The WB decrement before coordinate accumulation improves fitness to
  .827321698. A total of 124 sequential trials tested WB local scopes, guard
  polarity, the real nonempty helper, typed vector access, coordinate compound
  operations, /O1-/O2-/Os-/Og variants, G6/G7 and Ob2. Native hoists an EBX
  zero used by the first loop and keeps remaining in EDI; the bank uses EBX
  for remaining, with different second-loop homes and loop-entry placement.
  Normal explain_mismatch confirms the true 545-byte extent and first
  difference at +6. The improved bank is committed, with no production draft.
  Trial timestamps show five minutes; the first log's t=13 estimate was
  corrected through re_log rather than editing the log. Timestamp review
  also corrected the earlier Apt/light/allocator estimates to approximately
  3/2/5 minutes of sequential trials respectively; trial counts and outcomes
  are unchanged. Historical time estimates are not impossibility evidence.

## Stopping condition

Stopped after three landings under the user's top-of-ranking wall condition,
not a claim that the repository has no remaining work. At the refreshed top
ten, 00108FBD needs genuine-caller recovery for its custom register ABI;
0007C637 retains the allocator/free and hull-loop mismatch; 0052E6E6,
000F2FFA, 00706660, 00405E3D and 002AD25B retain crack-y's documented
code-generation walls. No new supported hypothesis emerged for those banks.
001F1609 was revisited with new EH hypotheses and retained honestly;
001F206E depends on it; 001F21E8 needs the same missing empty allocator
lifetime state. Lower-ranked candidates remain available.

No Ghidra tool was exposed to this seat; local retail disassembly, WorldBuilder
bodies and recorded evidence were used. BFME1 stayed at verified committed
23b143233b5a8664a3bdf8572df6d905c310a5a1. The fetched a7c38d3b2597121f178ab5190b3062478823257d
changes Apt's string-transform source and its attempt log. The pointer advance
and old/new full verification comparison remain outstanding; no success stamp
was written. No push, subagent, gate/baseline edit or speculative pin was used.
