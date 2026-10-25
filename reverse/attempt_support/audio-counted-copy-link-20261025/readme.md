# Audio counted-reference list binding

BFME2 base 8d4b145924; clean verified BFME1 0bf534ea7. Published census
ce1b975697 (2026-10-25 03:51, retail-truth-4), unchanged during this repair.
MilesAudioManager.cpp's 41,647 existing nonpadding matched bytes move from
unresolved to linking in the paired **legacy scoped preview**. No new authored
C++ recovery or closed-strict/full-image gain is claimed.

The unresolved `_Construct<PlayingAudioRef>` was reachable only through the
local list push_back -> insert -> _M_create_node chain. Native EOS and audio
callers target push_back 0x55475, whose existing row is under the four-byte
Rva0036CA00Str view. It calls insert 0x54B75 -> node creation 0x53DA3 ->
_Construct 0x2393AA -> owning-reference copy 0xA8C7C. That copy increments
pointee+4, matching PlayingAudioRef's target-supported owning-pointer view.
The existing fold pin at A9840 comes from a separate trivial deque view and
must not be used for these owning copies.

Replace the unprovided copy declaration with an imported forceinline bridge
to the existing counted-reference construction operation. The compiler retains
its original visible list bodies. All 1,533 external COMDATs remain, and just
one changes: the 34-byte node helper keeps every byte and changes its second
relocation to the counted constructor. Its whole body and both relocations
now exactly equal the existing native node owner in stlport_list_create_nodes.
The other 1,742 nondebug sections retain normalized bytes, flags, symbols and
relocations. The only directive change removes the former unprovided
constructor's compiler-generated fallback /alternatename. No pin, ledger,
layout, name, compiler setting, shared header or baseline is changed.

The operation relationship and refcount offset come from target calls and
retail owner bytes; the Rva0036CA00Str spelling remains an existing layout-view
name, not a newly established audio class identity. Reviewed the existing
BFME1 linking audit and latest verified donor handoff; this repair uses BFME2's
already-rowed operation, with no new donor transfer or reference input change.
Only this unit has the unresolved owning-copy name, so there is no broader
same-cause consumer sweep to edit.

An initial trial bound all eight push_back call sites directly to the rowed
view. It preserved 336/337 rows but xfer 0x5E3E5 grew from 1396 to 1401 bytes:
the unknown helper made its local savedStreams escape and changed stack
allocation/scheduling. That trial was discarded. Binding only element copying
preserves every parent row, including xfer. Do not repeat the whole-list cast.

Acceptance:

- `./build.sh <source>`: 337/337 functions, 19 string literals, 32 float
  literals and 105 imports pass; six existing STL fold owners verify.
- `link_check.py --prepare-current <source>`: strict reusable current receipt
  and all normal byte gates; this is self-current evidence, not link closure.
- `link_check.py --refresh <source>`: 0 -> 41,647 B, 1/1 unit linking.
  `proof.py` independently pairs original/current objects against the same
  census, and proves the exact node twin and unchanged retained sections.
- EH: 77/77 EXACT, no missing objects or baseline entries.
- Frozen-definition, class gate and new COMDAT variant admission pass.
- `data_check.py --converged`: ten addresses, no second names or unjudged rows.
  Optional `data_check.py --enforce` reports two pre-existing wrong-name
  local-static guard bindings at 9E1E68/9E1E70. Original and edited objects
  have exactly the same findings; the shadow data check is not newly clean.
- `place_bodies.py <source>`: zero bodies/pins. No census, full link cycle,
  nightly or boot runner was started.

Reproduce with the original source/object saved as
build/audio-list-bind-20261025/before.cpp and before.obj, then the edited
strict-current object. The tracked proof uses those scratch inputs; the
recorded report binds both object hashes and the unchanged census hash.

`link_check.py --refresh --current-ledger <source>` refuses closed-strict
measurement because 11,865 providers lack current compiler evidence. This
was not worked around or replaced with a census rebuild. The reported
41,647 B gain remains the paired legacy prediction above.
