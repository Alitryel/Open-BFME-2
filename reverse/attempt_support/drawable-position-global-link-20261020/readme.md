Drawable position/global owner repair, 2026-10-20

Parent 7a5d066b54. Published legacy census 5366c4f808 (2026-10-20 12:21).
The 27B18C damage notification caller used an obsolete BFMERopeDrawable getter
spelling and an address-derived g_pRva003BD424 global. Target direct-call
relocation resolves to 2763E6, already rowed Drawable::getPosition; the exact
691-byte getter/rebuild provider establishes the class ABI. Declare it on the
existing Drawable view. The caller global relocation is VA DFF028, data ledger
9FF028: RadarWindowOverrideSource *theRadarWindowOverrideSource, defined by
UiCallbackFirers.cpp. Use that single datum and cast to the local call view.
The pointee view and damage caller name remain structural; no new identity,
layout, data pin or alias is asserted. The getter provider records its donor
revision; the BFME1 checkout reviewed remains 92f6bbe8e1dcdb46b5d27da0674313efc822b790.

Before: caller 0 B plus getter provider 691 B. After: caller 761 B, getter
691 B and global provider 841 B all link in current-object legacy preview.
The two providers retain their census bytes: expanded cohort 1532 -> 2293 B,
+761 B. Self-strict preparation verifies 27/27 rows across these three units,
41 literals plus one empty string, two floats and one import. Scoped caller
gate passes 2/2 rows and one float. This is not closed-strict or a full link.
Declared definitions, canonical class and ledger checks pass. No new pins,
ledger rows, shared headers or verifier changes.

Sweep: LaserUpdateInitLaser already links 756 B with its current declarations;
no change. W3DRopeDraw has independent blockers and is left untouched. The
old data name has no other active source consumer. No failed byte trial.
The expanded pre-edit probe overlapped editing and was discarded; before.txt
is the valid two-unit original measurement, after.txt adds the explicit data
provider. Census bytes for that provider establish the expanded baseline.
