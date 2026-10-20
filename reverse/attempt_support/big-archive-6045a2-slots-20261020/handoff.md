# 0x006045A2 `Win32BIGFileSystem::rva006045A2` (270 B) — 2026-10-20

## State

The body is **already in the unit** `Code/GameEngine/Source/GameClient/Win32BIGFileSystemRva006046B0.cpp`
(lines 122-150, marked `present-unmatched`) and is **text-exact against retail except two
`lea` displacements and the one funclet byte they move**:

| retail | ours | meaning |
|---|---|---|
| `8d 45 b0` = `lea eax,[ebp-0x50]` | `8d 45 c0` = `[ebp-0x40]` | `make_pair` return-value buffer |
| `8d 4d b4` = `lea ecx,[ebp-0x4c]` | `8d 4d c4` = `[ebp-0x3c]` | that pair's map-member destructor |
| funclet `lea` | off by 0x10 | follows the same slot |

Compiled size is 270 with the committed source (269 with the refuted variant below), frame `0x44`,
flag byte `c6 45 fc N` EH states 0/1/2/1/0 and every other instruction identical.

## Remaining wall 1 — the 11 unresolved callees (gate output)

`tools/add_match.py` refuses with `unresolved call(s):` 11 real `BigArchiveMemberInfo` map
instantiations (pair copy ctor, both `_M_find`, `make_pair`, `map()` ctor, `~_Rb_tree`,
two `insert_unique`, ...). They are the **same ICF-folded STLport bodies the ledger already
owns under the placeholder mapped type `Rva00603A00Mapped`** (4-byte view):

- `reverse/functions.csv`: `??$_M_find@PBD@?$_Rb_tree@PBDU?$pair@QBDURva00603A00Mapped...` at 0x00603A2D
  (82 B, `stlport_cstring_tree_find_00603A2D.cpp`), plus the `find` body at 0x00600A2C,
  the `~_Rb_tree`/`insert_unique`/`make_pair`/pair-ctor twins around 0x603AA8, 0x603E50,
  0x604251, 0x60426C, 0x6044A0, 0x413727.
- `reverse/symbols.csv` already pins `??$_M_find@...V?$map@PBDURva00603A00Mapped...` to 0x00603A2D.

Ours mangles with `BigArchiveMemberInfo` (the **native 12-byte member descriptor** the bank
proved: `File*`, offset, size), so the symbols do not resolve. Two honest routes:

1. **Fold pins** — `tools/pin_admission.py --add` for each name with
   `fold-proof=Code/GameEngine/Source/GameClient/Win32BIGFileSystemRva006046B0.cpp`
   (this unit compiles each name to retail's whole body; the mapped type only changes
   offsets in the payload copy, which the fold-proof must check per name).
2. **Family rename** — rename `Rva00603A00Mapped` to `BigArchiveMemberInfo` in the tree
   family rows/sources (the bank's own "cleaner" note). Never substitute the 4-byte
   placeholder for the 12-byte descriptor.

Then the three funclet rows for the parent's EH graph (`$L` labels) land with the parent.

## Remaining wall 2 — local slot allocation (coin-flip, one lever short)

Retail's frame `0x44` is fully used, low to high:

```
-0x50 pair<const char*,BigMemberMap> temp (make_pair buffer, 20 B)
-0x40 BigMemberMap::value_type buffer for the members insert (16 B)
-0x30 the const-key copy (20 B)
-0x20 the empty BigMemberMap() temp (16 B)
-0x14 iterator result / second _M_find argument home
-0x04 EH state byte
```

Ours reuses `-0x40` for the pair buffer and leaves `-0x50..-0x41` unused; the frame size and
every other slot agree. Retail's pair buffer is the **lowest** slot, i.e. allocated first.

Refuted: a named `_STL::pair<const char*,BigMemberMap> source = _STL::make_pair(...)` inside the
`if` block compiles to **269 B** (one byte short; `lea ecx,[ebp-0x4c]` becomes a 3-byte form).

Next levers to try (docs/shape_levers.md in `reference/open-bfme-1`): an aggregate/union local
whose padding keeps the frame (`union { pair<...> source; unsigned char pad[4]; }`), a
declaration in the scope above the branch with assignment inside, or making the `-0x40`
`value_type` buffer live across the branch so the allocator cannot reuse that slot.

## Provenance

Bank `reverse/attempts/0x006045a2.cpp` (score 0.99) is the drop-in TU; the in-unit variant is
newer and equal-or-better. Donor/name evidence for the class and the descriptor is in the unit's
header comments. The class is a private view here (no canonical header).
