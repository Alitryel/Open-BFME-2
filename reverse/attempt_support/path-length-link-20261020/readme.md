# Path 0x00365B8A linked-byte blocker

Starting root 44f33aef2a, BFME1 01b84526fc8a43c9dea1cfe6abd0a6859b34eee5,
published index 5366c4f808. Strict baseline gate passes the existing 614-byte
row (611 nonpadding); the sole local preview blocker is Coord3D::length.
Read the original reconstruction attempts before editing. Canonical layout and
method ownership already exist; the private inline body agrees semantically
with coord3d.cpp but emits a different instruction body at these flags.

Trial 1: remove just visible length(), retaining visible normalize(). Normal
byte gate fails: caller frame grows 0x4C -> 0x58 and local sharing changes.
This confirms the previously recorded escape-analysis requirement; a plain
external declaration is not a repair.

Trial 2: keep both original bodies, change /Os /arch:SSE to /Os /arch:SSE2,
matching the shared owner's architecture. Trial through normal build.sh with
FLAG_DEFAULTS=off passes all caller bytes and 7 float literals. Link preview
still refuses length() as not retail's body: 0 -> 0 linked bytes. Math sqrt
wrappers also change but are unreferenced diagnostics, not blockers under
retail-truth-2. flag_defaults.py propose confirmed /Os override still needed;
its sole SSE2 override change was restored together with the source. No
alternative helper, pin or inline-assembly escape was introduced.

The remaining difference is not resolved by helper visibility suppression or
the architecture setting alone. A local helper-emission/codegen reconciliation
must preserve the visible bodies and the caller's 0x4C frame. Canonical owner's
/O1 mode differs from the caller /Os, but /O1 is already known to lose caller
bytes (original landing history). No failed reconstruction is left in Code/.
The exact gate/preview diagnostics are retained here; no new C++ identity or
closed-strict result is claimed. Claims released after original revalidation.
