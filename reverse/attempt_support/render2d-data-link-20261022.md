# Render2D data ownership, 2026-10-22

Current original objects at BFME 2 057fbe766a, with the published 08160bc2c9
census index (2026-10-22 17:08), link 6,395 authored nonpadding bytes across
nine related units. Render2DSentenceDrawBFME2.cpp alone fails: its visible
multicolor Add_Quad copy is non-retail, and the correct owner's copy is still
unproven because eight data relocation fields have no rowed addresses.

The existing float owner in Rva00118B50State.cpp is `g_Va00DEC49C`.
Its native setter stores a four-byte zero at VA DEC49C; the vertex writers
load the same scalar, and all four retail loader bytes are zero. The existing
`g_Va00DB5FC8` owner in GlobalGetterSingles.cpp has a four-byte integer
initializer 10568192: retail holds `00 42 A1 00`, the color callback address
used by the matched quad bodies and the 117C00 getter. New data rows verify
both existing objects' scalar sizes, addresses and complete initial values.
Their address-derived names and types are retained; no second datum or new
application identity is introduced.

Six render units now reference the existing float owner directly. One redundant
Convert_Vert alternatename is removed; the owner's existing compatibility alias
still serves the unchanged sentence consumer. That consumer's body claims are
held elsewhere, so it was neither edited nor prepared as an owned provider.

The correct 430-byte Add_Quad copy's four Z references and four callback
references can now all be judged against retail, so the current census rule
accepts the losing consumer copy when the kept owner is retail-proven. The
nine-unit current-object link preview changes 6,395 to 8,787 B: **+2,392 B**,
all from the sentence consumer. The eight providers' own 6,395 B were already
linked and are not credited. Other uses in W3DAptAux and W3DDisplayStringDraw
already use the real globals; their unrelated blockers are not changed.

Acceptance: `./build.sh` passes all 72 provider rows; strict reusable self
receipts from `link_check.py --prepare-current` verify those rows and their
string/float/import references. `data_rows.py --verify` passes both owners
(three rows including an existing owner row). Frozen-source checks pass.
The link gain is a same-index legacy prediction, not closed-strict closure or
actual link.exe placement. No census or status artifact was rewritten.
