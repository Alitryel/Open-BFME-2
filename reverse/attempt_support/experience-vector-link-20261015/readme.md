# Suppress unused private vector helper copies

Base: d3d0d1dc7652bff206a04047d01ed45306d44563. Published index measurement:
ac77c85054, 2026-10-15 14:25, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
The five consumers and unchanged STLport provider were file-claimed.
No census, index, link status, baseline, ledger, pin or shared header changed.

These private vector views emit unused optimized copies of begin/end, whose
native providers in stlport_vector_voidptr.cpp are the 16-byte row at
0x00023B90 and 17-byte row at 0x00023BA0. The private copies are 3 bytes
(`8b01c3`, digest afd9af583299) and 4 bytes (`8b4104c3`, 78e4fbf1d9d9).
LargeGroupAudioKeyMap additionally emits the wrong unsigned size() copy;
the native 25-byte provider is rowed at 0x00023BC0 in the same STLport unit.
ObjectDestructor and Rva00421242Dtor additionally emit unused clear() copies
that disagree with the index's first kept copy (no native address proven).
No clear identity or native address is newly asserted.

TU-local dllimport/forceinline specializations preserve the original field
accesses and erase calls while suppressing twelve unused external bodies.
No retained nondebug relocation calls any removed body, and no replacement
import reference appears. This applies the compiler-emission technique reviewed
in BFME1 commits 66b19a8e95a4add525ef808fcea088e306798e2b (Apt allocation) and
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 (DamageInfo constructor); BFME1
commit de59a7e9f891b3ed2d4221d151ca881f4b75a583 was also reviewed for its
consistent inline COMDAT repair. No donor layout, identity or behavior was
imported. Current target byte gates and object relocations establish
applicability independently for each consumer.

## Paired local result

proof.py refreshes only the five explicit consumers and unchanged provider in
two in-memory copies of the same measurement index. Saved original objects and
current strict-receipt objects produce:

| Consumer | Findings before | After | Removed copies | Retained COMDATs |
| --- | ---: | ---: | --- | ---: |
| ExperienceLevelSystem | 4 | 2 | begin, end | 57 |
| LargeGroupAudioKeyMapBfmeAddKey | 8 | 6 | begin, size | 44 |
| ObjectDestructor | 13 | 10 | begin, end, clear | 22 |
| Rva00421242Dtor | 5 | 2 | begin, end, clear | 4 |
| Rva0053ED1AUpdates | 3 | 1 | begin, end | 7 |

All 134 retained COMDATs, and every other nondebug section, relocation,
external binding and directive, are identical after normalizing compiler-local
label numbering. The twelve removed bodies are the entire object delta.
All other consumer findings and all provider findings are identical.
proof.json records exact removed bytes, relocations, digests, object hashes,
measurement identity and complete before/after findings.

The data-check reader reports three identical pre-existing findings in both
object sets: the audio map static and guard at 0x009FEC74/0x009FEC80 have
wrong-name findings, and TheExperienceLevelSystem at 0x009FECC4 has a
duplicate-definition finding. No data finding or baseline was added.

Acceptance checks:

- Edited-source byte gates pass 42/42 rows. Bounded strict preparation of the
  five consumers plus unchanged provider passes 64/64, two data rows, four
  literals plus two empty-string references, zero float literals and one named
  import. All six objects have strict reusable receipts.
- EH verification: 7 EXACT, zero nonexact or missing objects.
- Converged-data check: 8 addresses, zero second names or unjudged rows.
- New-variants admission, class gate, declared-definition check, check_csv
  (91522 function / 15479 symbol / 464 data rows) and diff whitespace pass.
- Placement rescans of all five edited units: zero bodies, zero pins.
- Local link_check confirms the twelve removed findings, still 0/6 clean units
  and LINKED 0 -> 0. These are byte-strict objects and a legacy local link
  preview; no closed-strict gain, actual link placement, full census or boot
  result is claimed. Full verification runners remain maintainer-only.

Original sources, objects and receipts are preserved in ignored
build/experience-vector-link-20261015 (root consumer plus audio, object,
subsystem and windows subdirectories). proof.py uses those snapshots and the
frozen downloaded index without changing the shared cache or measurement.
Reproduction needs that index and the original objects from the base revision,
then normal build.sh/--prepare-current receipts for the changed sources.

## Sweep and remaining work

The indexed same-begin/end-digest sweep mapped 101 consumers. After the initial
ExperienceLevelSystem repair, 83 local objects still emitted either helper;
four additional sources used a private vector view without including vector.
sweep.json records that discovery snapshot (before strict preparation of those
four). All four were repaired in this batch. Other consumers use real/shared
STL headers; the private-view specialization must not be copied there blindly.
ExperienceLevelAssign was inspected and uses real vector with existing
specializations, so requires a separate supported change.

Vector destructors in ObjectDestructor and Rva00421242Dtor have retained EH
callers; suppressing them would add replacement imports. They remain, together
with their vtable conflicts. ExperienceLevelSystem still needs the record
assignment and g_00BFBAC0 providers. The audio unit still needs key-tree globals,
by-value resize, allocator reconciliation and the kept comparator.
Rva0053ED1AUpdates still needs Rva005C6D4D::rva005C6D9C. The native vector
provider's unrelated assignment/constructor/erase/allocation blockers remain.

Several top-ranked entries were already locally clean in current objects:
Rva00057378, AptMpGameSetupRefreshMapList, AIAttackApproachTargetStateOnExit
and AIIdleStateUpdate. No improvement is credited for those read-only probes.
W3DView and the counted-key Bfme5ThirtyFour family need separate shared-type
or provider evidence; neither was edited or claimed here.

BFME1 checkout and committed gitlink remain a7c38d3b2597121f178ab5190b3062478823257d;
fetch found upstream 95eeb3bef370a7cd730b0ad5f228c317c8756e72. The freshness
update remains with the live file:reference/open-bfme-1 claimant. This seat
preserved its inputs and did not stamp a successful freshness check.
