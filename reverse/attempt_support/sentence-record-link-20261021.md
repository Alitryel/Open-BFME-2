# Sentence record helper ownership

Inputs: BFME2 a1ce27576a, unchanged retail-truth-2 index 03035cf02c,
2026-10-20 22:09; BFME1 verified pointer 68c5ce2789 unchanged.

Record_Sentence_Chunk's native 249-byte parent inlines the surface assignment
and sentence default construction. Its emitted surface assignment differs
from the independently rowed 43-byte COM AddRef/Release owner at 0x00072381
(W3DMouse_loadD3DCursorTextures.cpp); the implicit sentence constructor also
differs from the first kept copy. Imported force-inline declarations retain
the exact inline lifetime effects and suppress both conflicting outlines.
The explicit empty sentence constructor still invokes the existing surface
base constructor. No identity, field layout, callee pin or data owner changes.

Paired current-object LEGACY prediction: 0 -> 249 nonpadding bytes linked
against the same frozen index. Ordinary byte gate 1/1; parent EH graph EXACT;
prepare-current gives a strict reusable receipt. No self-strict placement or
closed-strict gain claimed. The same-name consumers Draw, AllocateSurface,
GlyphSurface and PendingSurfaceStructResize retain multiple independent
blockers, so no zero-gain suppression edits were made to them.

Logs: build/seat8-sentence-before.log, seat8-sentence-after.log,
seat8-sentence-byte.log, seat8-sentence-receipt.log,
seat8-sentence-sweep-before.log. EH command:
python3 tools/eh_verify.py Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceRecordChunkBFME2.cpp.
