# Four-colour quad owner linking

The rowed four-colour `Render2DClass::Add_Quad` (42719, 430 B) was a strong
definition. `Render2DSentenceDrawBFME2.cpp` needs a visible noinline, select-any
copy to preserve its matched caller's dead-storage optimization. The strong
owner and that copy caused a duplicate, holding the whole 1,956 B owner out.

Make the owner noinline/select-any too. Move the existing 24 B forwarder at
456F0 into the same unit: its real call emits the inline owner without adding
an artificial anchor. Remove the now-empty split source. No body, name,
signature, layout, global binding or compiler setting changes.

Original cohort: owner 0/1,956 B, split forwarder 24/24 B, sentence 0/2,185 B.
Final cohort: combined owner 1,980/1,980 B, sentence still 0/2,185 B.
**Net legacy gain: 1,956 B**, excluding the already-linked 24 B forwarder.

The initial census was b73720bed9, 2026-10-20 05:34. The normal
`link_check.py --update-index` refreshed current objects and dropped the retired
split source (6,298 reread, one dropped, 14 new units unpreviewable). It records
6b860817af, 07:11, dirty tree, retaining the census origin. To isolate this
change against that same refreshed index, replayed the strong definition with
the moved forwarder: all five byte rows still exact, combined owner 0/1,980 B
with the quad duplicate. Restoring select-any gives 1,980/1,980 B. Sentence's
independent floor, surface, vector and pending-surface blockers remain.

Checks: normal byte gate 5/5 for both shapes; final explicit self-strict
provider preparation 5/5; seven float references; class gate, declared-body
gate, enforced data/converged checks, new-variant admission, check_csv and
diff whitespace checks pass. EH has zero rows in this unit. Link previews
include the unchanged sentence provider/consumer. No closed-strict gain is
claimed; no full link cycle or census was run.

Reproduce final preview:

```
./build.sh Code/Libraries/Source/WWVegas/WW3D2/Render2DClassAddQuadColor.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WW3D2/Render2DClassAddQuadColor.cpp Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceDrawBFME2.cpp
```
