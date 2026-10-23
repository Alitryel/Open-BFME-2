# Signed construction helper (2026-10-20)

Base e859106ab4; published census/index 144ed0ccab (2026-10-20 15:34).
UnsignedSetHelpersBFME2.cpp holds 185 non-padding matched bytes. Before:
zero linked bytes, with only its incidental _Construct<int,int> copy losing
to the retail /Od provider at 00620140. After: 185 bytes link in the same
legacy preview. No closed-strict closure or new authored coverage is claimed.

The signed push_back emitted here is the existing fold-proof witness for
004DFCB0, called by MeshGeometryGetEdges at 0016E5FB. A declaration-only
construction helper preserved the two owned rows but changed that push_back
and gained nothing. Instead, retain STLport 4.5.3's visible placement-new
body as an imported force-inline specialization, following this unit's
existing _M_set treatment. No import is emitted; the signed push_back remains
retail's body, and the conflicting out-of-line construction copy disappears.
The full-body signedness/identity evidence remains in the existing pin notes;
this repair adds no pin or alias.

Before/after self-strict preparation and the normal byte gate pass 2/2 rows.
Frozen-source, EH (no graphs), data and converged-data checks pass. Logs:
build/link-small-current.log and build/link-unsigned/{inline-byte,inline-link,
inline-strict,pin-check}.log. The remaining allocator diagnostic is explicitly
unreferenced and does not block under retail-truth-2; it is unchanged.
