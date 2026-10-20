# Render2D: +209 B in the legacy link preview

Base c9660021f5; frozen census 144ed0ccab (2026-10-20 15:34).
Paired current-object link_check previews change render2d.cpp from 0 to
209 matched linked bytes. Its two matched rows are unchanged: coordinate
range 0x1188C0, 202 B, and texture accessor 0x5CCB37, 7 B.

The two remaining donor Add_Line overloads with UV rectangles are explicitly
unmatched. Expand their Vector2::Normalize operations at the call sites,
preserving the donor's len2 != 0, Inv_Sqrt, and component multiplication.
This avoids emitting a second external Normalize body under this unit's
compiler settings. The retail helper has its own /O1 /Oy- owner in
Vector2_Normalize.cpp. No class layout, pin, ABI or target identity changes.
The frozen ranking lists no other unit with this Normalize blocker.

Acceptance: both matched rows exact; all byte/string/float/import checks
pass; self-strict reusable current receipt; no EH-bearing row in this unit;
converged-data check clean; frozen-source check passes. The companion
point-batch repair's EH result is corrected to 1/1 EXACT in its evidence.
No closed-strict gain or fresh census is claimed. Donor revision and due
freshness-update limitation remain as recorded in the point-batch evidence.

The filter attempt logged alongside this repair was reverted completely:
declaring its base destructor changes inline cleanup to calls; importing
the derived destructor leaves an unresolved import even with exact rows.
Its claims were released. It needs a supported reconciliation of external
destructor binding with native inline cleanup, not another simple declaration.
