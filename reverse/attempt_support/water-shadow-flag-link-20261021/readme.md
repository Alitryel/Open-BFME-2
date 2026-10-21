# Water-track shadow flag binding

Retail flush 0x0010004D (392 bytes, RET4) tests byte VA 0x00DEC404 at
0x0050008F. The existing data row owns exactly that byte as private
WW3D::IsCurrentlyRenderingShadowMap, initialized by
W3DShadowMapManagerUpdateShadowMap.cpp. The old expression reached it as
DX8Wrapper::stats + 2, leaving the stats aggregate unresolved. No new data
or aliases are defined. The private static-data declaration agrees with the
owner and the snow/water render consumers; the TU suppresses the donor
WW3D view, which lacks this BFME2 member. Donor snapshot macros and accessor
are retained for the existing DX8 inline definitions.

Paired legacy link previews use identical explicit source sets and the same
published index (17918792f6, 2026-10-21 09:22): current object 0 -> 391 linked
nonpadding bytes. Normal byte gate: 1/1, two float literals verified.
Self-strict prepare-current: 1/1 and receipt accepted. Closed-strict closure
and runtime are not measured. No other indexed unit is blocked on this
statistics name; all other water/snow guards inspected already use WW3D.

BFME1 donor review reuses verified revision
5987fd1b859e86801d093256eadc6fb63d87785f and the earlier link-seat-20261021
review. This repair follows the BFME2 data row and native byte access;
no BFME1 layout is imported.

Publication reconciliation: upstream independently landed the same flag binding
while this repair awaited publication. Retain upstream's WW3D accessor/header
view and reverify it; this commit now preserves local verification evidence,
not an additional 391-byte improvement beyond the updated origin/master.
Reconciled upstream source passes the normal byte gate and self-strict
prepare-current again (1/1, two float literals); no source change remains.
