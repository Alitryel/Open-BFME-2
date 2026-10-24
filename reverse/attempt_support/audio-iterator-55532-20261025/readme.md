# Restore the 22-byte iterator under the correct audio identity

Upstream 67313f71ea correctly retracted assetmanager_impl.cpp's false Q1
integer-map iterator row at 55532 and its false skip-helper pin at 54DC7.
That reopened 22 bytes. Preserve that correction: the stock integer map
does not have the target's pointer-key hashing semantics.

The existing MilesAudioManager.cpp C++ already emits the complete 22-byte
const iterator increment for its pending request set. Its value is a pointer
to the address-derived 24-byte request record. Target evidence fixes the
set at manager+9C, its hash's null handling and request+8 key access, and its
pointer equality fallback. The existing 47-byte skip helper at 54DC7 calls
the owned bucket helper 53EA8 and hash 51B89. This is not the asset manager's
integer-key division. The request's original class name stays unasserted.

The candidate's whole 22 bytes and its only relocation independently equal
retail, with the REL32 target decoded as 54DC7. Four existing native audio
callers at 56FD9, 575CE, 577E3 and 609A1 independently call 55532. Their
compiled callee spellings, native sites and sources are recorded in proof.json.
The earlier assetmanager evidence and attempts 83223, 83496 and 83620 already
documented this identity distinction. The existing correct audio pin at
55532 is retained; no new pin or synthetic alias is introduced.

Add the real source's emitted iterator through add_match with the full
boundary. No Code body, header or compiler setting changes. The whole audio
unit's normal gate passes 337 bodies, one data row, 19 strings, 32 floats and
105 named imports. All 77 exception graphs are EXACT with no baseline or
missing objects. A placement scan found only this one unowned body and no
pins, so the file's currently viable placement work is drained.

The literal progress.py origin/master run reports C++ exact +22 bytes and
unclaimed real game code back to zero. This restores coverage after the
upstream retraction; it does not credit the previously false integer-map
identity or assert an executable boot test.
