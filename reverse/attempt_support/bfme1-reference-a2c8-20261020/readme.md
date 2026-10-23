BFME1 a2c8039e reference refresh

At fixed BFME2 c4edff6088f14756dbd55b0e7cfe364166c99af4, compare verified
BFME1 b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b with official master
a2c8039e61ad4dfb20c095d8eafe048248d31f25 (one commit: "data: own DX8 lock
thread datum at 0x013405E0"). It touches GadgetRadioButton.cpp,
DX8WrapperDeviceLockInfo.cpp and BFME1's own ledger; no header, include
directory, // cl: flag or layout changed, so the game/ and inputs/ layout
resolved last time still applies.

Both complete byte gates pass at the same BFME2 revision: 97253/97253
functions, 1112 data rows, no-op patch, FULL GATE OK. Complete EH
verification is identical under both references: 11759 rows, EXACT 11722,
bytes_differ 35, retail_only 2, all 37 baselined, no missing objects.
No update regression, no repair needed.

Reference lanes after the update: scan 5522 unique placements, all owned,
5515 independent boundary controls; ranked 0; near 1 (the previously blocked
25-byte Fade cleanup 0x0076962A); lift lane 154 bodies, 107 servable.
Forced ZH compilation: 918 built, 68 refused of 986 units (refusal list in
comparison.json); exact matches all owned; the sole packet is still the
15-byte 0x007A86AF without a clean C++ parent. Both changed donor TUs compile
cleanly with BFME2 flags and place nothing new (0 bodies, 0 pins).

No verifier, baseline, compiler setting or source edits. The pointer must
pass the normal whole-tree commit hook before publication.
