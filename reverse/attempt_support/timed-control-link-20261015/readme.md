# Timed-control callback destructor link repair

BFME2 base: `459f87bb336f7d1ae6e4760931fcf8ec1a495370`.
Both files were claimed before editing. No ledger row, address, class layout,
compiler flag, shared header, pin, alias or verifier changed.

AptTimeLineCallbacks.cpp emitted an unused standalone Rva00211E75 destructor
beside GameEngineControl.cpp's exclusive external definition. Their complete
bodies and relocation digests agree (`361dbf55f6ea`); this equality does not
establish a retail address or a stronger identity for the destructor.
Only a debug relocation references the timeline copy. Mark that local inline
body dllimport forceinline, preserving all inline cleanup and suppressing the
unused external definition. The provider source is unchanged.

## Paired measurement and acceptance

The frozen runner index measures `ac77c85054`, 2026-10-15 14:25 UTC, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
Before and after independently refresh the same two explicit objects into
copies of that index. No saved index, census status or history is modified.

| Unit | Local findings before | After | Legacy predicted linked bytes |
| --- | ---: | ---: | ---: |
| GameEngineControl.cpp | 1 duplicate | 0 | 0 -> 276 |
| AptTimeLineCallbacks.cpp | 5 | 4 | 0 -> 0 |

Bounded strict preparation before/after and ./build.sh pass **17/17** rows,
including one verified compiler-label renumbering. All retained nondebug
sections, characteristics, definitions, bytes and relocation referents are
identical, including EH and linker directives. The only removed code section
is the unused base destructor. Undefined external symbols are unchanged;
there is no new imported call or data. Compiler receipts are strictly current.
proof.py verifies these facts and complete paired findings; proof.json records
object/receipt hashes and measurement metadata. Object timestamps/debug data
may differ after recompilation and are not claimed identical.

EH: five EXACT, no missing objects or baseline debt. Enforced data: one existing
baselined finding, zero new findings. Converged data: eight addresses, zero
second names or unjudged rows. Frozen definitions, class admission, new COMDAT
variants, CSV integrity and whitespace checks pass. Placement rescan: zero
bodies, zero pins. The ordinary local link_check also reports GameEngineControl
LINKS at 276 bytes and the timeline's four remaining findings.

This is a **legacy local link prediction** using strict-current object receipts.
Authored C++ growth is zero. Self-strict executable placement and closed-strict
closure gains are unmeasured. No census rebuild, full link cycle, nightly or
boot runner was started. Broader image verification remains outstanding.

## Donor review, blocked trials and handoff

BFME1 repair `c1315665a1b22beb7e6d9279548fe5b1c26ed1f9` applies the same
unused-emitter suppression to DamageInfo constructors. Its source and validation
were reviewed; only the emission technique transfers, without donor layouts,
addresses or code. The previously reviewed declaration-only provider repair
`d003077f0b7ce97622adb7a53f1fe76653433c5c` was tested here: removing the
GameEngineControl destructor body changed registration from 155 to 153 bytes.
That trial was restored completely before the successful timeline-only change.

The timeline retains three unresolveds (g_Va00E04920, Rva0023C666::rva0023C666,
AptTimeLineScreen::rva00520CD1) and a Rva00211E75Callback destructor COMDAT
mismatch. The class/source scan found no further inline base-destructor copies
to suppress. Its other occurrences are declarations or the retained provider.

Earlier this session, declaring the three KeyToBucketMap helpers in the
voice-response unit failed two scoped byte gates: main's stack frame changed
0x364 -> 0x368, and main/funclets differed even with insert's body retained.
Original source and 28/28 verification were restored, the blocked attempt was
logged, and both file claims released. Existing GameInfo/PlayerList register-
summary blockers and claimed audio-cache work were not retried.

Official BFME1 master was fetched at `003e59cd`; clean verified checkout/gitlink
remains `a7c38d3b2597121f178ab5190b3062478823257d`. Reference freshness is
still blocked on the recorded comparative full verification: the old-input
baseline previously left 2806/2982 stale TUs after 21 minutes. No unchanged
multi-hour retry, reference pointer advancement or successful check stamp was
made. No missing or mismatched per-row data-back artifact was used for ranking.

To reproduce, at the base revision run strict prepare-current on both sources,
then capture.py. Apply the timeline source patch, repeat strict prepare-current,
and run proof.py from the repository root. Ignored snapshots and acceptance
logs are under build/timed-control-link-20261015; the proof requires the same
index and asserts dependency/command currency.
