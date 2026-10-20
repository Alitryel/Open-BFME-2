# Audio record range cleanup: +266 B linked

At parent 603e1c2478, paired legacy previews against census b73720bed9:

| Unit | Before | After |
| --- | ---: | ---: |
| MilesAudioManager.cpp | 0 | 0 |
| StlportVectorOverflowBfmeStringTailRecord144.cpp | 0 | 266 |
| StlportVectorStringTailRecord144Dtor.cpp | 0 | 0 |
| stlport_asciistring_record_bodies.cpp (unchanged provider) | 0 | 0 |

The native overflow/clear path calls the existing range wrapper 0x54ED9,
which reaches the 28-byte destructor loop 0x5401D. Both helpers already have
retail providers in stlport_asciistring_record_bodies.cpp. The other three
units emit divergent copies of the loop from their virtual-destructor views.
Declaration-only specializations retain the existing typed calls and select
the verified providers. Suppression in all three units is necessary to stop
a wrong selected copy from blocking the 266-byte overflow unit. The existing
layout and destruction identities remain unchanged; no new pin, alias, row,
compiler override or class view was added.

Checks: all 319 rows across the three changed units byte-match; explicit strict
preparation passed for all three, including 315 manager rows. The unchanged
loop provider emits exactly 28 bytes and matches its whole retail body and
relocations (`explain_mismatch.py` at 0x5401D). The paired link preview is
0/4 -> 1/4, +266 B; this is a legacy-index result with self-strict receipts,
not closed-strict closure. Census and status files were not rewritten.

Trials and remaining blockers:

* Declaring only __destroy_aux made the overflow clear call an unpinned
  __destroy wrapper with an extra argument. Declaring its actual native
  _Destroy range wrapper as well preserves the original 30-byte clear.
* The dedicated vector destructor remains blocked by an unpinned base
  destructor that differs from Miles' kept copy, and by Miles' vector
  destructor copy. Suppressing Miles' vector destructor preserved 315/315,
  but declaring the dedicated unit's base destructor changed its 63-byte
  native body to an external call. These extra trials were reverted.
  Resume that separate repair with inline cleanup visibility evidence,
  not another declaration-only base trial.
* The manager and broad record provider retain many independent unresolved
  names and COMDAT conflicts; no gains for them are claimed.

Local logs: build/audio-destroy-before.txt,
build/audio-destroy-overflow-byte{,2}.txt,
build/audio-destroy-manager-byte{,2,3}.txt,
build/audio-destroy-dtor-byte{,2}.txt,
build/audio-destroy-strict-final.txt,
build/audio-destroy-provider-proof.txt,
build/audio-destroy-final-passed.txt.
