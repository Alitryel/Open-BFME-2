# 0x394879 BuildAssistant::isLocationClearOfObjects - session 2026-10-19 22:00-22:08 PT (hans-agent-oct5)

Bank (built at Code/GameEngine/Source/Common/System for its relative includes): struct 16, mem 82, reg 35, 1843 B vs 1838. R=153 / O=154.
The main wall is the frame: `sub esp,0x12c` vs retail 0x11c, so 16 bytes extra. Most memory diffs are the resulting offset shift.

Frame-slot census (ebp-relative):
- Retail: c 10 14 18 19-1c 20..38 48 50 53 70 cc e8 128
- Ours: c d e 14 18 1c-1e 24..48 58 60 63 80 dc f8 138
- The extra 16 bytes come from the door tail. Ours puts `Coord3D center` at -0x48..-0x40 and the Rva00261353Filter temp at -0x3c/-0x38.
- Retail puts center at -0x38, overlapping storage that is dead by then, so retail's tail temporaries share slots that ours keeps separate.
- `this` spill: retail -0x10 (overlaps pt.z later), ours -0x14. The five option bools land at different byte slots.

Inert this session: a named Vector3 for Transform_Vector, renaming Coord2D dir, wrapping the pt/door tail in a block.
Worse: reversing the bool declaration order (reg 39). Scoping Matrix3D tm inside a block: 1861 B. Moving center after the iterate call: frame unchanged, mem 75 but R 154.
Next idea: find which tail temporary retail overlaps with center (likely the Vector3 out or the exit-loop dir/pt), and test scoping or lifetime of the BitSet/KINDOFMASK temporaries in the iterateObjectsInRange call.
