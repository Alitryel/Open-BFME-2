# Explicit SDK profiles for glyph and mapped-file helpers

Two more existing donor ports directly include windows.h but have no provider
for it on their current effective initial include paths. TargetCheck searches
its source directory and Vc7/include; the narrow filebuf also searches
STLport and its native-header sibling directories. None contains windows.h.
Both now request the existing per-source `// platformsdk` opt-in. Compiler
argv, optimization flags, bodies, layouts and ledger identities are unchanged.

`Rva0093C4A0TargetCheck.cpp` stores GDI handles as void* and uses the old sweep
header's opaque HDC/HFONT/HGDIOBJ contract. Select the SDK's documented
NO_STRICT mode before its first header, as for the registry cohort. This uses
the real SDK declarations without new casts, typedef shadows or aliases.

`stlport_narrow_filebuf_mmap_underflow.cpp` now uses the SDK's mapping constants
and imports instead of redundant local declarations. PAGE_READONLY remains
2 and FILE_MAP_READ remains SECTION_MAP_READ=4. The genuine CreateFileMappingA
prototype takes LPSECURITY_ATTRIBUTES where the old manual declaration used
void*; this code passes the null pointer constant 0. The real MapViewOfFile
prototype preserves the existing 32-bit argument ABI. All mapped-file body
statements and types remain unchanged.

Current ordinary build: four rows, 1,152 complete native bytes EXACT, twelve
named imports verified, no EH-bearing rows. Supported --prepare-current also
passes with strict reusable receipts; actual Windows.h, WinBase.h and WinGDI.h
resolve under the toolchain's Vc7/PlatformSDK/Include. Frozen sources, objects
and receipts are in build/near-batch4-sdk-followup/final; proof.json records
hashes and each native row. Affected-unit placement finds 0 bodies/0 pins.

No current prechange compile is claimed: the effective initial header gap is
proven, and the previously sampled Wine missing-header loop was not repeated.
Older sweep-header receipts may reflect the driver's fallback on another
host; they do not establish a current native-equivalent baseline. New recovery
and linked-byte credit are zero. This source-only prerequisite repair changes
no shared headers, tools, pins, data or metadata rows. Verification uses
BFME1 pin4483e88da1c2. t=15min model=Codex(runtime-model-not-exposed).

The standalone normal link preview encountered a Python/git cat-file mutual
pipe-write stall under Python 3.14 and again on an unchanged retry under
isolated fleet Python 3.12.14. Only the owned stalled process trees were
sampled and stopped. No link-preview CLI completion is claimed. Independent
frozen current-object checks find the two sources clean, with no added
variants, but this is not a paired before/after linking measurement.

The normal commit hooks completed under Python 3.12.14, including all four
native rows and twelve import checks. No gate, hook, repository runtime
configuration or acceptance rule was changed. The alternate interpreter
helped that hook run; it did not resolve the separate link-preview stall.
