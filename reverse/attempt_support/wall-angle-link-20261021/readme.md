# Wall placement angle helper link repair

At BFME2 HEAD before this repair, the current wall-placement object loses its
visible Coord2D::toAngle COMDAT: it calls CRT double acos rather than the
retail float ACos helper. The verified owner coord2d.cpp and the existing
AODHordeContainRva0047AC8F.cpp use the float helper. Preserve the noinline
visible definition, including its no-escape information, and use that helper.
The two wall-placement ledger rows remain byte exact. No ABI/layout, pin,
row extent, or data definition changes.

Paired previews use the same published index (17918792f6, 2026-10-21 09:22),
current objects and the same three-source set. Wall unit: 0 -> 2,218 linked
nonpadding bytes. Combined: 9,723 -> 11,941 (+2,218). BuildAssistant's already
resolved duplicate is included on both sides and contributes no claimed gain.
Self-strict prepare-current passes 46/46 rows across wall unit and Coord2D
owner. This is a legacy link preview gain; closed-strict closure and runtime
are not measured.

Same-cause sweep: rank-current names only RailedTransportDockUpdate as another
toAngle loser; it has ten independent blockers, so no zero-gain edit was made.
The other explicit toAngle consumers already use ACos.

BFME1 donor review is reused from the same verified revision
5987fd1b859e86801d093256eadc6fb63d87785f and the tracked
link-seat-20261021/readme.md review. Its coord2d.cpp also calls float ACos.
The repair uses BFME2's established owner, preserving BFME2 layout and flags.
