# Skirmish game-info pointer: verified owner and consistent declarations

Base `c63ad61ed9`, on upstream `3f8f6eb0b5`, 2026-10-26. All affected files
were claimed and passed the frozen-file check before editing.

SkirmishGameOptionsMenu.cpp and its gameinfo shim already define/declare
`SkirmishGameInfo *TheSkirmishGameInfo`. Commit `80184fd340` previously removed
a second GameInfo-pointer definition and reconciled consumers. Later
`3a8ff9f8e0` changed 24 declarations in 23 files to GameInfo* to match the
heuristic catalogue, leaving those consumers without a matching provider.

This repair records the existing four-byte owner, which the supported data
index prefers to its heuristic entry, then restores that owner's type in the
24 declarations. GameInfo views, constructors, pointer stores, virtual deletion
and casts are retained. The merged Recorder.cpp is edited in place. The owner
source and shared header are unchanged. No duplicate global, pin, alias or
generated catalogue edit is introduced.

## Target facts and data verification

Native DIR32 operands establish VA `0x00E02EF0` / RVA `0x00A02EF0`, all with
zero in-object addends. Independently checked representative anchors:

| Matched body RVA / extent | Operand offsets | Operation |
|---|---|---|
| Recorder::isMultiplayer `0x0037B18C` / 110 B | `+0x5E` | Dword test |
| GameEngine::init `0x0022E2E4` / 8,808 B | `+0x1CE1` | Pointer store |
| GameLogicSnapshot::DoXfer `0x0024797E` / 2,195 B | `+0x84`, `+0xB5` | Read/store |
| AptSkirmish destructor `0x00521977` / 315 B | `+0x47`, `+0x67` | Read/reset |

The four native bytes are loader-zero in the virtual tail of `.data`, not
bytes to read at a raw file offset. The normal data gate proves a four-byte
pointer under the owner's existing flags and verifies its initial value.
The heuristic eight-byte span was not a size proof; the following four bytes
are excluded. Source/COFF establish the existing owner and spelling; consumers
establish the address. No original-source class-layout recovery is claimed.

All 24 current cohort objects use the real Skirmish-pointer spelling; exactly
one defines it. The owner object is identical to its saved verified before
object. One additional stale declaration in AptMainMenuCallbacks.cpp has no
use and emits no symbol; it is removed after separate whole-file verification.
No GameInfo-typed Skirmish extern remains under Code/.

## Verification and retained diagnostics

- The main 24-source cohort passes **729/729 functions**, **13 data rows**,
  four STLport folds, 323 string literals plus 56 empty references, ten float
  literals and 86 named imports. All **100 EH graphs are EXACT**.
- The unused-declaration companion passes **39/39 rows** and **four EXACT EH
  graphs**. Frozen-file checks pass for all 25 files.
- Independent before/current COFF comparison covers **3,033 non-debug sections,
  173,026 raw bytes and 9,078 relocations** across all 25 objects. External
  symbols agree after only the intended global-name mapping. Local targets
  agree by section/value/type/storage: 327 changed `$L` spellings do not change
  physical targets. Unrowed COMDAT and EH sections are included. This is an
  additional comparison, not a substitute byte gate.
- Shadow data diagnostics remain **21 findings, 18 outside the register**.
  All 18 printed findings are identical before/after and unrelated to this
  global. No data-debt key is retired.
- Code identity reports 21 rows with wrong bindings: 22 wrong and seven
  divergent references. Those physical references already exist in the before
  objects, with unchanged bytes and targets. Ten diagnostics involve changed
  mappings of literal `$L` labels, resolved by the normal parent-EH verifier.
  There was no pre-edit identity run, so an identical pre-edit diagnostic count
  is not claimed. Genuine prior bindings and stale-label diagnostics still
  require separate review. No physical code-binding change or key retirement
  follows from this data repair.

Against unchanged index `763dc8759f`, the 24-current-object ordinary preview
changes from **0/24, 70,102 -> 0 authored bytes** to
**22/24, 70,102 -> 64,163**. No TheSkirmishGameInfo unresolved reference
remains. These restore already-censused bytes in a bounded comparison; they
are not a new census or C++ coverage gain. Recorder retains six old-index
duplicates and a selected-copy finding after its upstream consolidation.
The menu owner retains missing callees and divergent Money/runInit definitions.
The combined preview still exits 1; neither remaining unit nor a complete
executable is declared link-clean.

Reproduce normal build, EH, frozen-file, data and identity checks with the
cohort in `build/codex-cleanup-20261025/iteration24-skirmish-sources.txt`, plus
the separately checked companion. Local receipts are
`iteration24-skirmish-{before-build,build,eh,before-link,link,data,identity}.log`,
the native/owner/data-parity/frozen logs and `iteration24-unused-menu-decl-*.log`.
The independent comparison script and receipt are
`iteration24-skirmish-coff-parity.py` and `.log` in that folder.
