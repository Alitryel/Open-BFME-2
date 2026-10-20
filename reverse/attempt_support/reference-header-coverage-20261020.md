# Additional reference coverage at BFME1b3cc6b1588f2

These are read-only leads, not source imports or new coverage. Decoder/dump
paths were excluded before reading sources. All compilations used normal
place_bodies.py; no external donor path was placed in BFME2's ledger.

-1000 clean address-named engine/device/common units,2000 compiler profiles:
  donor settings and the established O1/G7/SSE retail profile.1992 compiled
  immediately. Four failed profiles used separated `/I game/...` operands;
  joining each intended operand and resolving it to the real donor directory
  repaired them. Four required the verified original PlatformSDK, including
  both BfmeConv1024 profiles. All2000 then
  compiled; zero body/pin leads. This is distinct from the earlier426-unit
  GameClient address-named pass and the named-file passes.
-88 clean STLport donor units with explicit donor4.6 standard headers and the
  target's const bfmealloc ABI.59 compiled immediately. A scratch-only allocator
  overlay adds the standard optional char-allocation hint argument and removes
  an invalid explicit instantiation of the already-specialized allocator<char>.
  Neither change alters the allocation algorithm.82 then compiled; the remaining
  six needed the actual donor STLport src/stlport_prefix.h or original SDK.
  All88 ultimately compiled; zero body/pin leads. Intended files/directories
  were checked explicitly. No fallback header substitution was used.

These findings do not establish that all reference source is exhausted. The
unvisited address-named engine families and other compiler/semantic adaptations
remain independent leads. Unchanged profiles above should use their cached
results rather than repeat the searches. The scratch allocator compatibility
repairs are not production changes and are not a byte-proof receipt for any
claimed BFME2 row.

Hash-bound source/profile/revision manifests and complete outputs are under
build/reference-address-remaining-oct20/, reference-address-repairs-oct20/,
reference-stlport-headers-oct20/, reference-stlport-api-repair-oct20/ and
reference-stlport-final-headers-oct20/. The latter four paths share build/.
Code and the reference pointer remain unchanged.

## Previously failing Zero Hour units

At the same BFME1 revision, refreshed zh_sweep reported 919 cached successful
objects and 68 compile failures. Isolated wrappers put the verified original
PlatformSDK and DX81 include directories before the sweep shims, and add the
real ZH WWAudio and Benchmark directories. Ten non-decoder units were tested
under their original settings and O1/G7/SSE2. Seven immediately compile:
animatedsoundmgr, mono, rawfile, registry, WWCOMUtil, verchk and shdhwshader.
wwmouse additionally needs the real windows.h/mmsystem.h declarations;
W3DShaderManager needs the standard placement-new declarations before
always.h's duplicate block, plus the real PersistFactoryClass forward name.
Both then compile in both profiles. These 18 successful profiles yield zero
unclaimed body/pin leads. mpu remains blocked on an unsigned abs overload in
its CPU-frequency routine; no invented signedness fix was applied.

Driver/input/source hashes and exact flags are in
build/zh-sdk-repair-oct20.py and its sibling directory; the four declaration
follow-ups are in build/zh-sdk-followups-oct20.py and its sibling directory.
The ordinary placement tool compiles every wrapper. No shared header/tool,
vendored source, pointer or ledger row was edited. Other failures (including
missing original audio SDK and generated shader inputs) remain separate work,
not evidence that all reference paths are exhausted.

## Further ZH header and API controls, 20 October

At the same b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b donor revision,
ten additional units compile in 22 profiles and yield zero unclaimed body/pin
placements. Original O2 and the matched-sibling O1/G7/SSE2 settings were tested.

- prim_anim, assetmgr, ringobj and sphereobj: an isolated, same-guard copy of
  prim_anim.h adds the missing dependent `typename`. Real game include roots
  precede the original SDK, which precedes stand-ins: the SDK also has a
  different persist.h and must not hide WWSaveLoad's PersistClass definition.
  Preinclude the real windows.h before this header overlay.
- w3d_dep: standard placement new before always.h's duplicate array-new block.
- urllaunch: real Windows, stdio, wchar and tchar declarations.
- Debug: the real AsciiString and StackDump headers declare g_LastErrorDump.
- IMEManager: original imm.h; remove the invalid default argument from the
  Display callback typedef in an isolated header copy, preserving its ABI.
  An unchanged copy of the existing sweep PreRTS.h is isolated from its Windows
  stand-ins; no sweep directory remains in this unit's include search.
- dazzle: explicit double/double and float/float pow overload controls (four
  profiles). This is a source-search adaptation, not proof of retail rounding.
- textdraw: both old character-argument calls use the same header's current
  no-argument single-atlas Peek_Texture API.

simpleplayer still needs Windows Media declarations/debug macros; GameSpeech
uses obsolete speech interfaces. No substitute definitions were invented.
Replay drivers are reference-zh-prim-animation-20261020.py.txt,
reference-zh-remaining-headers-20261020.py.txt and
reference-zh-api-followups-20261020.py.txt alongside this record. Hash-bound
manifests and complete ordinary place_bodies outputs live under the matching
build/zh-*-oct20/ directories. No Code source, shared header, ledger row,
vendored source or verifier was changed by these searches.
