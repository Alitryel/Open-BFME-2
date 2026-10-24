# Rendering-context box getter intrinsic, 2026-10-24

Existing target: `?rva0070E440@Rva0070E440@@QAEXPAURva0070E440Box@@@Z`,
RVA0x70E440,151B, proper owner Rva0070E440Cluster.cpp. Existing target evidence
identifies the AptRenderingContext pMatrix assertion, count at+0x3BC, six-float
box at+0x20 and six-float default atVA0xE180C4. These identity/layout facts,
all declarations and the global definition remain unchanged.

Replace the file's sole inline `int3` statement with VC7.1's genuine
`__debugbreak()` intrinsic. The complete151B candidate matches byte-for-byte,
with no unresolved calls, masks or extent problems. No barrier, flag, layout,
ABI, input-domain or symbol-pin change is needed. The entire file is this body.

Normal add_match --replace-existing retained the existing source/name/RVA/size
and notes exactly, verified whole-file1/1 and both string references with none
skipped, and queued a normal claim-settling receipt. Published-index preview at
7e43384268 reports LINKS149->149 under its existing metric; no new linked-byte
claim. Normal hooks remain required on integration.

The file already counts as C++ coverage, so classification delta is zero.
Private diagnostics: build/render-context/bare.json and link.log. Successful
code is retained in the tracked unit; no instruction emitter or asm remains.
