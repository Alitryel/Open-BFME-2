# GenBase cleanup provider repair

The constructor unit for Rva00136794 no longer emits a competing ret-only
GenBase009EB7D0 destructor. Its declaration uses the existing reset-calling
COMDAT in Rva00136794Dtor.cpp. The unused compiler barrier declaration is removed.
No names, pins, aliases, layout, compiler flags or ledger rows are added.

Target evidence is independent of the opaque donor names. The constructor's
native EH cleanup relocation at RVA 0x00765A8A and the destructor's at
0x00765B16 both call RVA 0x00135E35. That complete five-byte trampoline jumps
to the already matched 17-byte reset worker at 0x0061ED80. The retained
COMDAT emits precisely this tail call. This establishes the needed cleanup
relationship, without recovering a new application name or broader class ABI.

## Acceptance

Before and after, the two-source self-strict gate verifies all 6 rows. Both
associative EH records are EXACT. The bounded object proof removes just the
one-byte competing destructor; all five retained constructor COMDATs and all
retained nondebug sections, flags, external bindings and relocations are
identical. The destructor provider object is byte-for-byte unchanged. In
particular, the existing EH references retain their external spelling and now
resolve to the reset implementation rather than the empty copy.

Independent before/after refreshes use the same frozen legacy index:
`a2839ea429`, 2026-10-15 13:35, based on census `5986a99448`,
2026-10-15 04:52. Its SHA256 is in object-proof.json. The committed status
queue has a separate measurement at `ac77c85054`; it is not used as a paired
baseline. The index, status, ledger and baseline files are unchanged.

| Unit | Before findings | After findings | Existing nonpadding bytes |
| --- | ---: | ---: | ---: |
| Rva00136794Ctor.cpp | 0 | 0 | 180 |
| Rva00136794Dtor.cpp | 1 COMDAT loser | 0 | 222 |

Both units predict LINKS. The local legacy linked total changes 180 -> 402
bytes, a gain of 222 existing bytes. New authored C++ coverage is zero.
Closed-strict closure and link.exe placement are unmeasured; no such gain is
claimed, and no full census or maintainer-only runner was started.

Checks: `link_check.py --prepare-current` on both units; ordinary `build.sh`
for the changed constructor; paired proof.py; `link_check.py` and
`--new-variants` on both; `eh_verify.py` (2 EXACT); `data_check.py` (zero
findings); `data_check.py --converged` (zero second names/unjudged rows);
class gate and declared-definition gate on the changed source.

## Donor review and limits

The retained BFME 1 revision is a7c38d3b2597121f178ab5190b3062478823257d.
Its current game/GameEngine/Source/Common/MidVptrOnlyDerivedCtors.cpp and
BfmeThreeHundredFiftyThree.cpp were reviewed for the existing base constructor
and reset implementation. The reset relationship is applicable; the BFME 2
EH call targets above supply the target-specific proof. Prior donor forwarding
copy repairs are documented in link-inline-emitters-20261014, but this checkout
is shallow and those historical commits are not locally readable. No new
donor-history proof is claimed. The donor's opaque names do not establish
application identity. The fresh upstream pointer is newer, but another live
seat holds file:reference/open-bfme-1; the verified checkout/pointer is preserved
and no freshness success stamp is written.

The index has exactly two copies of this destructor, in these two units; both
are included. PlayerList's duplicate getter and the counted-key/StringBase
families retain their recorded compiler-summary/type blockers and were not
retried. Scratch before objects, source and receipts remain under
build/genbase-link-20261015; proof.py consumes those snapshots and the fixed
index to reproduce the bounded comparison.
