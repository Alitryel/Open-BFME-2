# File I/O rendering-dependency cleanup

BFME2 base `24bc709a164cff181a32062b16b3d663aa82a933`; BFME1 reference remains `92f6bbe8`. The donor file-I/O sources under `game/Libraries/Source/WWVegas/WWLib/` do not include rendobj.h or synthetic VCI anchors. Independently decoded current native rows contain no direct array-constructor-iterator calls, but included real constructors must also be checked.

Remove the unused render-object include in chunkio.cpp, ffactory.cpp and rawfile.cpp. The latter two can also dispense with the artificial VCI function and its two pragma-optimize directives. Preserve all actual implementation bodies, source flags, ffactory's StringClass and destructor views, and rawfile's separate WWFILE optimization block. Chunkio's real ChunkHeader[256] initialization still causes an iterator definition to be emitted, so its existing anchor is retained.

Normal whole-unit builds pass100/100 rows,7170 claimed bytes. Frozen before/after object comparisons retain identical relocated bytes at all100 rows and all3 units remain link-clean under one census index. The15 EH graphs are EXACT both before and after. The only external definition removed is the redundant iterator copy from ffactory and rawfile; no external definition is added, and canonical providers remain. Chunkio's external definition set is unchanged. Focused placement reports0 bodies/0 pins. This is0 new unique bytes and0 new linked bytes; the credit is two synthetic anchors, four pragma hatches, and three unused rendering includes removed.

The bounded compatible-sibling sweep rejected anchor deletion in chunkio_load_ctor.cpp: with its native path-derived /G7 flag projected into isolated scratch, its93B constructor remains exact but the iterator copy becomes nonretail. Whole-unit /O1 and /O1 /Oi instead change the constructor and emit another conflicting ChunkHeader constructor. In chunkio.cpp, whole-unit /O1 preserves only10/27 rows, so it is not a valid replacement. Initial scratch constructor trials lacking /G7 were discarded, not used as evidence. Production chunkio_load_ctor.cpp is unchanged, and its claim is released. No shared headers, aliases, pins, gates or baselines were modified.

`paired.json` holds all native row hashes, source/object hashes, definitions and complete current-object link verdicts. `array-trials.json` preserves rejected profiles; the native/donor packet and both EH reports are included. Frozen objects, original sources and dependency receipts remain in ignored `build/fileio-anchor/` in the writer checkout.

Agent: Codex (runtime model not exposed).
