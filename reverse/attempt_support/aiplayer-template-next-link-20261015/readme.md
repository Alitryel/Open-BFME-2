# AIPlayer template-list getter link repair

Base: `c402d83e3d`. The fixed published index is identified in `index-meta.json`:
refresh commit `a2839ea429`, original census `5986a99448`. No census or full link
cycle was run. The committed link-status queue is older; the evidence here uses
paired local previews against the same index, refreshed independently with the
before and after consumer objects.

`AIPlayerTeamBuild.cpp` emitted an unused 7-byte copy of
`ThingTemplate::friend_getNextTemplate`. Its digest `79a1c5ae0bea` is wrong
against retail; the selected `ThingFactory.cpp` provider has retail digest
`eb15bdb94a70` at RVA `0x00406D4A`. These were the index's only two copies.
Marking the consumer's inline definition `dllimport` and `__forceinline` removes
the unused copy while preserving the inline factory-list walk in the exact
349-byte `AIPlayer::queueDozer` at `0x004F288C`.

The existing source records the ZH factory-walk provenance and target-specific
next pointer at +0x484. The byte gate establishes the target caller's behavior;
the selected provider's name and address come from the existing ledger. BFME 1
repair `66b19a8e95a4add525ef808fcea088e306798e2b` supplies the compiler-mechanism
lead (suppress unused inline outlines), not BFME 2 identity or layout evidence.

Acceptance:

- `link_check.py --prepare-current` before and after: 35/35 retail rows; the
  changed consumer has a reusable self-strict current receipt.
- `./build.sh` consumer: 35/35, including 37 strings, three empty strings and
  seven floats. `eh_verify.py`: 13/13 exact, no baselines or missing entries.
- `./build.sh` provider: 8/8. Its current getter reproduces the selected retail
  digest. The provider has no self-strict current receipt; closure freshness and
  closed-strict linking are therefore not established.
- Object comparison: one unused COMDAT removed, all 180 retained COMDATs and all
  retained nondebug section bytes, flags, definitions and symbolic relocations
  unchanged. External/weak bindings and data facts unchanged. No retained
  relocation targets the removed helper, and no new variants appear.
- Paired local legacy preview: 18 to 17 findings, solely the getter conflict.
  Eight unresolved references, seven other COMDAT conflicts and two selected
  provider findings remain. Winner selections are unchanged. The unit's 9,097
  existing nonpadding bytes remain unlinked; legacy linked-byte gain and new
  authored-byte gain are both zero. No closed-strict or link.exe gain is claimed.
- Enforced data check: zero findings. Converged-data check: eight addresses,
  zero second names/unjudged. Class gate, declared-definitions check and diff
  whitespace check pass. Placement sweep finds no new bodies or pins.

`object-proof.json` contains the paired findings and selection details.
`reproduce.json` identifies the proof derivation and source hashes. The one-off
proof and before-object snapshots remain under
`build/aiplayer-template-next-link-20261015/`.

BFME 1 freshness remains pending: the clean verified submodule was retained at
`a7c38d3b2597121f178ab5190b3062478823257d`, while the official fetched master was
`95eeb3be`. Another worker owns `file:reference/open-bfme-1`, so this seat did
not change its pointer or record a successful freshness check. The owner must
complete comparative verification and affected donor refreshes before advancing
the pointer. No new donor source was imported by this repair.
