# Auto-resolve battle comparison link repair

At BFME2 base `047485c8eb586f28cfe8096804212d7d42aa22d3`, repair only
`Code/GameEngine/Source/GameLogic/System/LivingWorld/AutoResolve/LivingWorldAutoResolveBattle.cpp`.
Keep typed tree-iterator inequality local and integer comparison inline through
an inline-import specialization. Both retain the established library operation
while suppressing conflicting external copies. This is the same supported
pattern as LivingWorld/Rva0059DA34.cpp; no layout, flags, header, ledger, pin,
external ABI or data owner changes.

Object proof establishes that all 200 retained COMDAT byte strings, extents and
relocation digests are identical. The two removed comparisons are unreferenced
by nondebug sections. The only added section is an unreferenced 12-byte local
node comparison. Every other normalized nondebug section, external binding,
linker directive and data fact is unchanged. The existing target identities and
layout evidence are preserved; suppression does not establish new identities.

## Measurement and acceptance

Paired previews independently refresh the old and new consumer object into the
same frozen index. The measurement receipt is `19a2565407`, 2026-10-15 09:33,
with underlying census `5986a99448`, 04:52. Its SHA256 is
`a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3`.
The committed discovery status is from `28269d8e8d`; it is not a fresh
measurement of this repair. No index, status or census was rewritten.

Local findings decrease **12 to 10**, exactly removing the two comparison
conflicts with no other finding change. The consumer has 2,412 unique
nonpadding authored bytes; legacy predicted LINKED remains **0 to 0**.
New authored C++ bytes: **0**. Strict receipts establish byte verification of
the current object, not self-strict or closed-strict link placement gains.
No full link cycle, census, nightly or boot runner was invoked.

- Before and after `link_check.py --prepare-current`: all 33 rows exact with
  strict reusable receipts. Saved postchange log and object-proof assertion
  record the current receipt; the old source/object remain in scratch build/.
- Normal `./build.sh`: 33/33; string, float and import checks pass.
- `eh_verify.py`: seven EXACT, no baseline exception. Existing funclets are
  resolved through their parent EH records despite compiler label renumbering.
- `data_check.py --enforce`: zero findings; paired object data facts identical.
  Converged check: eight addresses, zero second names or unjudged rows.
- `link_check.py`: expected exit 1, ten remaining findings; paired proof
  asserts exact removal of the two old COMDAT findings.
- New-variants, class gate, declared-definition check and diff whitespace check
  pass. `place_bodies.py`: zero bodies and pins. Initial `check_csv.py` passes.

Remaining blockers are three strong UnitVector helper duplicates, five losing
copy/destroy/range-insert/overflow COMDATs and two wrong-selected providers.
They require a supported shared vector-provider reconciliation. Neither these
providers nor their other consumers change in this repair. The exact names
and original findings remain in link-before.txt, link-after.txt and the paired
JSON. The census also has a stale wrong-selected PlayerCopy constructor finding
which the unchanged current consumer already lacks; it is not credited here.

## Donor review and handoff

Reviewed BFME1 repair `66b19a8e95a4add525ef808fcea088e306798e2b` (inline-import
emission with forceinline); official master was fetched at
`86d49b09744d9dfb7896d0d1b6e621d3536f30d2`. Its suppression principle applies,
with independent BFME2 byte, relocation and caller proof. No donor source,
address or layout is imported. The verified BFME1 checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`. Another worker holds the reference
scope; the recorded old/new full-verification blockers remain unresolved.
The stale freshness-success stamp was preserved, not advanced.

Initial lane checks ran repair_queue.py link and link_rank.py. Current local
checks found EvaRva001DDF04 and ParticleSystemDebugDisplayBody already LINKS,
so no edits were made and the particle file claim was released. A read-only
current-object scan confirmed that many near-link entries are stale. The
water-ocean unit still has eleven mixed duplicate/COMDAT/selection blockers;
no trial or claim was made there. Unrelated reverse/zh_sweep work is preserved.

Proof scripts are saved evidence, not production tools. They read scratch
`build/autoresolve-compare-link-20261015/0/before.obj`, the current object and
this frozen index. Run from the repository root in object, link, data order
while these private inputs remain available. JSON/logs preserve their results
without committing objects. This repair completes the comparison task;
remaining vector reconciliation belongs to a separate claimed repair.
