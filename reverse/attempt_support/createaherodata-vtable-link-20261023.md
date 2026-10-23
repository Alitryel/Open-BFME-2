# CreateAHeroData vtable: why its three units do not link (2026-10-23)

Analysis only; no source or ledger edit was made (session wind-down).
Census 456ce161c5 plus `tools/link_check.py --refresh`.

## Target facts (retail)

Vtable at VA 0xC38D88 (RVA 0x838D88), four slots:

| slot | RVA      | ledger row                                             |
|------|----------|--------------------------------------------------------|
| 0    | 0x409D31 | `??_GCreateAHeroData@@UAEPAXI@Z` (CreateAHeroDataDtor.cpp) |
| 1    | 0x0B3FD0 | `?loadPostProcess@CreateAHeroData@@MAEXXZ` (same unit)  |
| 2    | 0x409353 | `?name@Rva00409353Named@@QBEPBDXZ` (SubsystemNameGetters4.cpp, 6 B, returns "CreateAHeroData") |
| 3    | 0x408C11 | `?DoXfer@CreateAHeroHero@@QAEXAAVXfer@@@Z` (CreateAHeroHero.cpp, 1489 B) |

Slot order dtor, loadPostProcess, const name getter, xfer is the moduledata
Snapshot shim with `BFME_SNAPSHOT_NAME_SLOT` (and `BFME_SNAPSHOT_REFERENCE_XFER`
for `DoXfer(Xfer&)`).

## Current unit views (all disagree with retail)

- `CreateAHeroDataDtor.cpp`: declares dtor and loadPostProcess only, so slots
  2 and 3 are purecall. Its `??_7CreateAHeroData@@6B@` copy differs from the
  first copy in link order (CreateAHeroDataCopy.obj), holding out 1,954 B.
- `CreateAHeroDataCopy.cpp`: public `crc(Xfer*)`/`xfer(Xfer*)`; unresolved
  `?xfer@CreateAHeroData@@UAEXPAVXfer@@@Z`.
- `CreateAHeroDataCtor.cpp`: protected crc/xfer; unresolved
  `?crc@`/`?xfer@CreateAHeroData@@MAEXPAVXfer@@@Z` and a differing vtable copy.

## Structural inference (not yet target-proven)

CreateAHeroHero.cpp's view has `m_id` +0x04, `m_name` (UnicodeString) +0x08
and `m_savedCRC` +0x134, the same layout as CreateAHeroData's
word04/text08/word134, and WB107D500 names slot 3 `CreateAHeroHero::DoXfer`.
CreateAHeroData and CreateAHeroHero are probably one class with two names
(snapshot name string "CreateAHeroData"). Settle the class name with
docs/naming.md before binding.

## Fix

Give all three units one view, either a shared header or identical TU views,
with retail's slot layout. Bind slot 2 to the 0x409353 body and slot 3 to the
0x408C11 body, preferably by a real name rather than `/alternatename`. Then
run `./build.sh` on each file and `link_check` on the three together.

CreateAHeroHero.cpp was claimed by astra-s2 for "helper linkage audit;
excludes Data ctor/table reconciliation". Check its claim before renaming
anything there.
