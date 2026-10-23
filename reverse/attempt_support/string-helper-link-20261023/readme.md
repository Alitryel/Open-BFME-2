String helper link repair, 2026-10-23
=====================================

Inputs: BFME2 dc623d4c10, BFME1 96c88c73a5cd1a58fc2f8db691beea50acd996db,
published legacy index b711de3634 (2026-10-23 14:28). Original TU flags are
/Od /Ob1 /DNDEBUG /MD; the const-source unit also uses inline_depth(6).

The current two Rva00831[24]E0StringReplace units hold 2587 matched bytes
out of the legacy link preview. Each emits non-retail erase and replaceBase
copies at its pinned target. Native erase12150 is57B; mutable-view copy101B.
Native replace2A610 is279B with a D4 frame; emitted249B has a44 frame.
These are helper-emission defects, not new identity evidence for donor names.
The retail call targets and existing owner rows independently establish ABI.

Trials:
- optimize(gty,on) around in-class erase leaves its101B emission unchanged.
- Moving erase inline out of class under those options yields54B, with an
  out-of-line move call absent from native. Both trials preserve all4 owned
  body rows and7 named imports, but link preview remains0/2587B.
- Mutable source: remove helper definitions and call the existing STL erase
  owner and BfmeStrV24 forward-replace row directly. Its parent loses declined
  inline context: frame9C becomes54; insertRange still matches. Thus merely
  changing callee spellings does not preserve caller code generation.

All source edits restored. Final normal gate:4/4 exact, literal/float/import
checks pass. No new pins, aliases, rows or pragmas retained. Next work needs
visible inline analysis context without wrong external helper emission, or
retail-exact helper recovery preserving parent frames. Avoid replaying these
three trials. Scratch diagnostics were build/stringviews-link/{trial1,trial2,
trial3,after1,erase1,erase2,restored}.txt; no useful candidate supersedes
tracked sources.
