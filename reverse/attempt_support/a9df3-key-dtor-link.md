# ??1Rva006D07E0Key@@QAE@XZ (0x000A9DF3) link blocker in the Apt units

Census: sole blocker (L+S) of AptAnimation, AptLoad (2313 B), AptLoadCountedOwner
(879), AptListContainsCountedKey (203), Rva006D0C60 (292), Rva006D1680 (652).
Retail's kept key destructor is a 5-byte `jmp ??1BfmeRefVGO@@QAE@XZ` (0x000A9822,
30 B, /O1 shape: calls Rva006CFDF0DecRef and bfmeDropVGO). AptLoad's unwind
funclet calls 0xA9DF3 (target fact). Each Apt unit emits a flat inline body.

AptAnimation.cpp trials (2026-10-21, claude-opus-5-5, ~90 min):
- Original key class wrapped in `#pragma optimize("t",off)`/`("s",on)`: 8/8 rows,
  but the emitted copy is the flat 30 B body (BfmeRefVGO's shape under the key's
  name), not the jmp: still a census loss.
- Key derived from (or holding) a `BfmeRefVGO` whose inline dtor holds the
  release, pragma /Os around both: the copies are retail's (key = jmp digest
  9013e94b3667, BfmeRefVGO digest 07d9a33f1551), but
  ?rva006E5050@Rva006E58D0 swaps one load pair at +0xE6
  (`mov ebp,[esp+24]`/`mov ebx,[esp+28]`, retail loads ebx first). The swap
  happens with no pragma too, so it comes from the extra inline layer.
- Variants that keep the swap: a base or a member, an implicit or empty
  explicit key dtor, `__forceinline` on the base or key dtor, release() helper
  layering, a nested `if`, struct vs class, a base ctor or copy ctor,
  `((BfmeRefVGO*)this)->~BfmeRefVGO()` on a flat key, operator= in base,
  base defined at the top of the file, rva006E5050 moved to the end of the
  file, a renamed base (not hash-dependent), main-body tweaks (scoped `i`, a
  separate import/export counter, hoisted list pointer, top `int i`).
- Not tried: the other units first (AptLoad's /O2 inline release uses `dec` +
  ~Rva006D0280 + freeBlock, so its BfmeRefVGO copy needs DecRef/Drop as
  non-inlined calls under /Os, e.g. `#pragma inline_depth(0)`), and
  permute.py over AptAnimation with the base structure.
