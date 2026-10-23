# CameraMarker copy/erase isolation

Base 265b888254; published index 456ce161c5 (2026-10-23 06:28,
retail-truth-4). The current-object legacy preview before editing excludes
all 197 B in stlport_copy_camera_marker.cpp because its vector base
constructor does not reproduce its pinned body at B63B2.

Existing evidence (symbols.csv pin note and the refuted FixedObject60
attempt at 42545A) establishes that B63B2 allocates 24-byte elements.
The copy/erase helpers use the existing eight-byte CameraMarker view and
rowed assignment at 28876F. The 42545A constructor and 42536A fill wrapper
were incidental whole-class instantiations; matching their outer bytes
does not establish the element identity. No name, pin or layout is changed.

Instantiate only copy48C897 and erase523EC8 in the original unit; preserve
the two fill-path rows and their original flags/view in the adjacent
stlport_camera_marker_fill_deferred.cpp. That unit explicitly records the
unresolved element-layout prerequisite. It is absent from the published
census and receives zero link credit. No duplicate row remains.

After: original unit LINKS 0 -> 102 B in link_check.py. This is a legacy
per-file preview, not self-strict or closed-strict closure or an executable
link. The deferred unit's 95 B remain uncredited. This follows the existing
BFME2 bucket-resize isolation pattern (link-hash-resize-isolation-20261022.md);
BFME1 linking revisions 138757e9/0a12ba59/d91e1d41 were reviewed, with no
new donor ABI or identity inferred. Reference upstream remains 21ef97bd;
the unchanged full-gate freshness blocker is documented in
link-reference-freshness-20261023.md.

Acceptance: both units 4/4 byte-exact with strict reusable receipts;
string/float/import and declared-definition checks pass; EH EXACT 1/1;
class gate and new-variant admission pass. No compiler flag, shared header,
verifier or baseline changes. Scratch before/after/strict outputs are under
build/link-seat-20261023c/camera-*.log. New authored C++ bytes: zero.
