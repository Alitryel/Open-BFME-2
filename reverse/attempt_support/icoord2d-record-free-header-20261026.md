# Coordinate record: native allocation declaration

Base `1f497305a4`, on upstream `d831bc2403`, 2026-10-26. This follows
the canonical-coordinate adoption in the same whole source,
StlportCoordVectorRecordInsert.cpp, under the existing ICoord2D claim.
Its only remaining Microsoft-header queue entry was a private C++ `free`
declaration. The source, existing allocator owner and prior attempts were read.

## Target and binding evidence

The native append body `0x002BC830..0x002BC8C9` calls RVA `0x00030830`
at offset `0x72`. This is the 17-byte game allocator wrapper owned by
GameMemoryFree.cpp, whose strong C symbol is `_free`. That owner already
binds `?free@@YAXPAX@Z` to `_free` through its recorded alternate name.
The source's existing `/D_CRTIMP=` keeps the standard declaration direct,
and `/EHs` preserves its exception treatment. No pin or alias is added.

The `_free` pin at `0x00628F98` is a different CRT import thunk. The
byte verifier accepts candidate addresses from both the ledger and pins;
its success alone would not establish the link binding. Here the native
call target, the existing strong game definition and its existing alternate
name independently establish that changing the spelling preserves the
physical provider. This is a per-file result, not a blanket free migration.

## Change and checks

The final source includes native `<stdlib.h>` and removes its unused
`// stlport` include-path marker. Its private container views and compiler
flags are unchanged. An initial `<cstdlib>` trial with the marker retained
also matched, but added STLport and msvcprt default-library directives;
the final native-header form preserves the original directives exactly.

Normal whole-file build passes all four rows (258 bytes), and both EH
graphs remain EXACT. A complete COFF comparison retains all 13 non-debug
sections, 463 bytes and 26 relocations, including both destructor COMDATs,
EH funclets and `.drectve`. Exactly three external references change from
the existing C++ spelling to `_free`; the comparison normalizes only that
documented alias. All 15 external symbols otherwise retain their identities.
Compiler-local label numbering changes, but physical targets do not.

The frozen-file check passes. The owning Microsoft-header scan reports
clean, and its scoped `refresh_queue` removes exactly this source's one
row while preserving every unrelated queue byte. Ordinary link preview
against index `47e030bafc` reports LINKS, 258 to 258 bytes. This is bounded
preview evidence, not a new census, strict link or runtime result.

Local receipts: `build/codex-cleanup-20261025/iteration29-stdlib-build.log`,
`iteration29-verification.log`, `iteration29-link-preview.log`; the scratch
verification script records the object comparison and native call decode.
No linking, ownership or C++ exact byte gain is claimed.
