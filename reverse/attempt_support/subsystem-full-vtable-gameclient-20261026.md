# GameClient's complete SubsystemInterface view

On `79763c8d95`, after rebasing the published `9839a436af` package onto
`9885fa1597`, GameClientDrawableTOC.cpp adopts the canonical SubsystemInterface
header. The whole source was read in the preceding same-file pass. Its source,
the canonical header and contract are unchanged by the rebase; frozen checks
pass before and after. The source and class claims are held.

## Native slots and the incorrect old binding

The native base table at RVA `0x007D77A0` and GameClient table at
`0x007ED850` have the same fourteen-slot prefix except the destructor, init,
reset and update. Slot six is RVA `0x000D43D0`: complete bytes `33 C0 C3`.
The contract already records the slot order. Its method names at slots 4-8
and 11-13 are structural spellings, not recovered original names.

GameClient's old private view instead declares `virtual void draw()` at
slot six. Its object has exactly one reference to this name, at primary
vtable offset `+0x18`; no direct call exists. The existing
SubsystemInterface.cpp object defines `?vslot06@SubsystemInterface@@UAEHXZ`
as the complete three-byte native body, with no relocations. A normal
before-change build passes all 466 rows in that provider and the consumer.

The historical index `47e030bafc` (2026-10-26 08:28) places
PartitionManager.cpp first for `draw` (object section 1829, `C3`) and
MilesAudioManager.cpp first for `vslot06` (section 2519, `33 C0 C3`). The
independently inspected subsystem provider is section 38, `33 C0 C3`.
All three are COMDAT ANY (selection 2, association 0). These are indexed
order and current-object facts, not proof of a new final linker selection.
No new pin, alias, body or ledger row is introduced.

## Minimal shared view

`SUBSYSTEMINTERFACE_VIEW_FULL_VTABLE` exposes the existing fourteen-slot
declaration order in the canonical header, with `virtual int vslot06();`.
The default view remains unchanged because existing consumers declare their
own virtual prefixes. The mode must be selected before first inclusion and
lasts for the whole translation unit. The contract records the mode and
qualifies its historical default-view omission accordingly.

Canonical fields remain `m_flag` at +4 and `m_name` at +8, size 12; existing
out-of-line default/copy constructors and destructor remain declarations.
GameClient references only the default constructor and destructor. Its
separate Display view does not inherit SubsystemInterface and keeps its own
draw declaration. This is one consumer's adoption, not completion of the
whole class or proof that arbitrary translation units can be merged.

## Verification

Normal after-change verification passes every one of the consumer's 92 rows
(8,863 ledger bytes), eleven EXACT EH graphs, one STLport fold, 28 literals
plus two empty references, one float and three imports. Complete object
comparison preserves all 353 non-debug sections, 16,313 bytes and 991
relocations, allowing exactly one evidenced external-name substitution:
primary GameClient vtable +0x18, `draw` to the existing `vslot06` provider.
Every other external identity and relocation target remains unchanged.
Independent review also preserves all 353 section auxiliary records and
COMDAT associations; 59 local-label references only change spelling.

The owning header acceptance removes exactly this source's queue item.
Ordinary preview retains LINKS, 8,248 to 8,248 non-padding authored bytes,
against index 47e030bafc. There is no census gain. This completes all currently
queued header and Microsoft-header items for GameClientDrawableTOC.cpp;
remaining class adoption and image-link prerequisites stay open.

Local receipts under `build/codex-cleanup-20261025/`:
`iteration37-native-slots.log`, `iteration37-before-build.log`,
`iteration37-after-build.log`, `iteration37-coff-proof.py`,
`iteration37-accept.log`, `iteration37-link-preview.log` and the normal
`iteration37-commit.log`. Shared-header dependent verification is the final
commit gate. No ownership measurement or runtime result is claimed.

The normal commit gate completed in `7eb94b780a`: 4,551 functions and 104
data rows across 552 dependent sources, seventeen STLport folds, 1,122
string literals plus 125 empty references, 414 floats and 244 imports.
Converged-data enforcement finds zero second names and zero unjudged rows.
The changed-source repeat again passes 92 functions and eleven EXACT EH
graphs; that repeat is not added to the dependent-source totals.
