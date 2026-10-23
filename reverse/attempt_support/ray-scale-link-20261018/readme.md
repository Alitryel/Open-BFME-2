# Preserve inline Coord3D scale without a nonretail SSE helper

Rva003FAAA1RayOverlap emits the 236-byte box/ray overlap row at 0x003FAAA1
(235 non-padding bytes). Target call and WorldBuilder identity evidence remain
in the source. Its /arch:SSE Coord3D::scale copy loses to the existing /arch:SSE2
49-byte owner at 0x000036D1 in WWMath/region.cpp. The parent needs the inline
component multiplication, not a new out-of-line call.

A temporary method-only macro annotates scale in the existing Coord3DCtorView
include as dllimport/forceinline, then is undefined before the caller. This
preserves the header's constructors, class view and full native parent body,
suppresses the incompatible emitted helper and creates no import reference.
No shared header, layout, pin or alias is changed. This is not the earlier
non-inline/refcount false-reject trial: this unit has just this one blocker,
its parent fully inlines scale, and the normal import gate and link prediction
prove that no IAT call is introduced.

Published index 2d2ca9cd35 (2026-10-18 18:45, retail-truth-2): before 0->0;
after 0->235. Paired with current region.cpp: provider stays at 1,287, combined
1,287->1,522. These are legacy local predictions, not closed-strict census
gains. Strict reusable receipt preparation passes the complete parent1/1,
1 float literal, and imports. Data enforcement/converged and EH checks pass.
No authored C++ coverage is added. Census/status files are unchanged.

Cause sweep: the index lists eight other scale-blocked units, each with
2..163 independent blockers. GenericObjectCreationNuggetDoStuffToObj is the
nearest, also missing consume@Rva003909FAObj; no zero-gain suppression changes
are retained in those units.
