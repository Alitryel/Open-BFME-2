UnicodeString vector destructor link repair
==========================================

The 63-byte destructor at RVA 0x00059F7C passed the byte gate but lost four
COMDAT selections in the runner index (measurement a2839ea429, 2026-10-15
13:35). Its allocator, allocation proxy, vector base destructor and vector
destructor called `_free`; the kept MilesAudioManager definitions called
`?free@_STL@@YAXPAX@Z`. The local source now uses MilesAudioManager's existing
game-allocator declaration around the STLport include. No allocator body,
pin, class layout or ledger row was added.

Target evidence: the normal byte gate resolves the destructor's free call to
retail RVA 0x00030830; both pre- and post-change bodies pass. The existing
namespace spelling is pinned there. The source-level declaration pattern is
carried from BFME 2's MilesAudioManager.cpp, not inferred from byte equality.
BFME 1 linking repairs c1315665a1b22 and 53d32d6b4b were reviewed as suppression
leads; the final change reconciles the allocator name instead.

`proof.py` uses the saved baseline under build/unicode-vector-dtor-link-20261015.
It compares both objects against the same index and checks every nondebug
section, extent, definition and relocation. All compiled instruction/data bytes
are identical; exactly four call relocations change allocator spelling. The
paired legacy local preview changes four findings to zero and 0 to 63 linked
bytes. The index and committed census/status remain unchanged. This is zero new
authored C++ bytes, not an executable-placement or closed-strict gain. The
current unit has a strict reusable receipt; the full provider closure was not
rebuilt or measured.

Acceptance checks passed:

- ./build.sh Code/Libraries/Source/WWVegas/WWLib/StlportUnicodeStringVectorDtor.cpp
- link_check.py --prepare-current: 1/1 row, strict reusable receipt
- link_check.py: LINKS, 0 -> 63 bytes in the legacy local preview
- proof.py: paired findings 4 -> 0, all nondebug bytes preserved
- eh_verify.py: EXACT 1/1
- data_check.py --enforce: no findings
- class_gate.py and link_check.py --new-variants: passed
- place_bodies.py: no additional bodies or pins
- find_declared_unmatched.py: all definitions already matched

The reserve, fill and XferUnicodeStringVector units show the same allocator
mismatch but have other workers' file claims; they were not edited. The earlier
Rva002214A6 pair-destructor suppression attempt was restored, byte-verified 8/8,
logged blocked and its file claim released. Its dllimport trial changed the
matched constructor and introduced unresolved EH cleanup imports.

Reference freshness remains blocked on the already-claimed donor update:
verified BFME 1 pointer a7c38d3b2597121f178ab5190b3062478823257d versus fetched
master e082760734795655f086939df77b393f4b728375. No pointer or success stamp was
changed, and no maintainer-only verification runner was started.
