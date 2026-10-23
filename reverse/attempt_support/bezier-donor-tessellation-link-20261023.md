# Donor tessellation link repair, 2026-10-23

The imported bezier_segment.cpp supplies only two matched D3DX helpers (183A40,
180 B; 7DE69, 37 B). Its unrowed getSegmentPoints definition pulls in five
undefined BezFwdIterator methods. Remove that unsupported donor definition and
its present-unmatched marker; preserve the other donor methods that emit the
matched helpers. The removed source remains in git history and the reference
source. No matching body was discarded and no new identity is asserted.

Target tessellation is independently rowed as Rva0055A246::rva0055A7DB (55A7DB),
with constructor/init/done/current/advance call relationships documented in
Rva0055A7DBTess.cpp. Those target views stay intact: neither a donor-class rename
nor an alias to the target interface is warranted by this repair. Native callers
are already recovered against those established views. The remaining unrowed
DumbProjectileBehavior donor's call to this donor method has no matched row;
this does not recover or claim its flight-path implementation.

Paired current-object legacy checks against d4fa46f19a (retail-truth-4, census
2026-10-23 19:41): donor helpers 0/217 -> 217/217. The tessellator,
Rva005C76C0Ctor and Rva005C7636 providers remain 923/923. Bounded total rises
923 -> 1140, **+217 existing nonpadding bytes linked**. This is a legacy preview,
not a measured self-strict/closed-strict census or a link.exe placement.

Acceptance: normal byte gate 2/2 functions; frozen-definition check and
check_csv; strict receipt preparation; new-COMDAT-variant check. No compiler
flags, pins, shared headers, verification tools or baselines change. Normal
commit hooks run. Local paired logs: build/link-seat-bezier-before.log and
build/link-seat-bezier/{gate,after,strict,variants}.log.
