# AudioEventRTS declaration prerequisite

The remaining filename-prefix and transfer blockers recorded in
`consolidation-common-20261025b.md` reproduced in a fresh normal dry run.
The longer AudioManager view was deferred beyond the seed's TheAudio extern;
the seed view also lacked the existing a29 and slot134 APIs.

The seed now declares the three existing donor APIs in a single view: a29 at
virtual byte offset 0x74, its existing slotD0 at 0xD0, and slot134 at 0x134.
The extra padding declarations come verbatim from the filename-prefix donor;
a29 replaces the existing unused slot-29 padding declaration one for one.
AudioData is forward-declared for the existing accessor return type. The
seed's AudioEventRTS also declares the filename-prefix static API already
implemented by that donor. These are declaration reconciliations, with no
implemented function renamed, virtual slot inserted, body changed, or layout
identity inferred beyond the existing callers' retail-dispatched slots.

Verification on 2026-10-25:

- `./build.sh Code/GameEngine/Source/Common/Audio/AudioEventRTS.cpp`: 17/17
  byte exact; string, float and import checks pass.
- `find_declared_unmatched.py` passed before and after the change.
- Scoped consolidation planner regenerated, and its `--check` passed.
- Normal merge dry run now accepts the seed plus
  `AudioEventRTS_generateFilenamePrefix.cpp` (100 bytes, 0x002D9622) and
  `Rva002D9FD9Seq.cpp` (151 bytes, 0x002D9FD9), retaining 19 matched addresses.
  A separate scratch Verifier check confirms all 19 ledger rows match in the
  proposed combined source. Local reports are
  `build/audio-slots-{before,after}.txt`.
- `check_csv.py` and `git diff --check` pass; commit hooks recheck the source.

Leave both now-compatible donors for the mechanical consolidation seat. No
paths moved, files removed, bytes recovered, hatches added, or identity debt
retired. The pending local prerequisite batch has no moved/deleted paths to
repoint; original retail path strings remain intact.

Independent blockers remain: Rva002DA0CFFinish.cpp and Rva002DA153Scale.cpp
cannot establish destination-environment baselines. Mixed sources and the
protected position donor are untouched. The existing GameLogic header-adoption
debt on the seed is unchanged and is not claimed as fixed here.
