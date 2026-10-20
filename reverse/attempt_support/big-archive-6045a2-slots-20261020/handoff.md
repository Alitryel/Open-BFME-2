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

## Wall 1 — solved 2026-10-20: 8 fold pins proven and admitted

The gate's `unresolved call(s):` list is 8 distinct `BigArchiveMemberInfo` map
instantiations (10 REL32 sites, some names repeating). All are ICF twins of bodies
the ledger already owns under the 4-byte placeholder `Rva00603A00Mapped`.
`tools/decode_calls.py` decodes each site from retail and prints the ready pin:

```
python3 tools/decode_calls.py '?rva006045A2@Win32BIGFileSystem@@QAE_NPBD0PAUBigArchiveMemberInfo@@_N@Z' \
    --rva 0x006045A2 --source Code/GameEngine/Source/GameClient/Win32BIGFileSystemRva006046B0.cpp
```

`tools/pin_admission.py --add NAME RVA ... --notes "fold-proof=<this unit>"`
**proved and admitted all 8 on 2026-10-20** — it compiles the unit, requires each
pinned name to reproduce retail's whole body at the address with the owner row's
relocations, one identity per address, and writes nothing unless every pin passes.
`tools/pin_consistency.py --check` then reports OK (6 multi-pinned symbols,
0 baselined, 0 new, 0 stale). The eight:

| instantiation | address |
|---|---|
| `_M_find` of the folder map (`pair<const char*, map<...>>`) | 0x00603A2D |
| `_M_find` of the member map (`pair<const char*, BigArchiveMemberInfo>`) | 0x00603A2D |
| `map<const char*, BigArchiveMemberInfo>::map()` | 0x00413727 |
| `make_pair<const char*, map<...>>` | 0x00604251 |
| `pair<const char*, map<...>>::pair(const pair&)` (const-key conversion) | 0x0060426C |
| `insert_unique` (folder map) | 0x006044A0 |
| `~_Rb_tree` (member map) | 0x00603AA8 |
| `insert_unique` (member map) | 0x00603E50 |

Driver: `admit_pins.py` in this directory — it re-runs `decode_calls.py`, harvests
the `pin: NAME,RVA` lines and calls `pin_admission.add_pins` in-process, so the
`$`/`<` in the mangled names never meet a shell. One cached compile per name.

The pins were **reverted with this handoff** because no landing followed: they add
8 hatch counts, and a pin no landed row needs is debt. Re-run the driver when the
body is byte-exact; it re-proves them in a few minutes (do not paste pins by hand).

The alternative route, if a future owner prefers no pins: rename the
`Rva00603A00Mapped` family to the 12-byte `BigArchiveMemberInfo` descriptor across
its rows and sources. Never substitute the 4-byte placeholder for the descriptor.

Three funclet rows for the parent's EH graph (`$L` labels) land with the parent.

## Wall 2 — local slot allocation (two bytes, one lever short)

Frame `0x44` = 68 bytes, fully packed low to high. Sizes are measured from the
emitted code, not the earlier note: the STLport `map` here is **12 B**, so
`pair<const char*, BigMemberMap>` is **16 B** (the pair copy ctor at 0x60426C
copies the key dword then calls the map copy for `[this+4]`).

| slot | object | live (retail) |
|---|---|---|
| -0x50 | `pair<const char*,BigMemberMap>` — `make_pair` buffer (16 B) | 0x6045fa .. 0x60463c |
| -0x40 | `BigMemberMap::value_type` buffer for the members insert (16 B) | 0x604672 .. |
| -0x30 | const-key conversion copy (16 B) | 0x604607 .. 0x604630 |
| -0x20 | empty `BigMemberMap()` temp (12 B) | 0x6045e6 .. 0x604645 |
| -0x14 | iterator (`parent`, also the second `_M_find` argument home) | |
| -0x04 | EH state byte | |

With the pins in place the compiled body is byte-identical to retail **except two
bytes**: the pair buffer sits at `-0x40` (the allocator reuses the value buffer's
slot, whose lifetime is disjoint) and the destructor funclet's
`lea ecx,[ebp-0x4c]` follows it to `-0x3c`. `-0x50..-0x41` stays unused; the frame
is still `0x44` and the body is exactly 270 B.

### Shapes tested on 2026-10-20 (all with the pins admitted)

| shape | result |
|---|---|
| committed: plain temp — `insertFolder(m, make_pair(folder, BigMemberMap()), out)` | 270 B, **2 bytes** (pair home + funclet) |
| named pair inside the `if` (`source = make_pair(...)`) | 269 B: splitting the statement destroys the `BigMemberMap()` temp before the copy ctor; retail's dies after the insert (0x604645) |
| native `m_folders.insert(make_pair(...)).first` (no helper) | 269 B, same temp-lifetime break |
| function-scope `BigMemberMap::value_type memberValue;` assigned in the branch | no change: a trivial object's storage sinks to first use and still shares `-0x40` |
| members insert moved into an inlined helper | no change |
| **`FirstMapPairPad`**: 32 B struct `{ pair value; unsigned char pad[15]; }`, ctor `value(make_pair(k,m))`, used as `FirstMapPairPad(folder, BigMemberMap()).value` | pair home **correct at -0x50** but +3 B (273 B): a redundant `lea eax,[ebp-0x50]` after `make_pair` |

### Why the padded shape costs the extra lea

`make_pair` returns its hidden return buffer in `eax` (retail 0x604251 ends
`mov eax,[ebp+8]`), and retail pushes that same `eax` straight into the const-key
copy ctor (0x604606 `push eax`). With the padded struct the pair is built inside a
constructor, after which `eax` is undefined, so the compiler re-materializes
`&value` (`lea eax,[ebp-0x50]`) and the body is 3 bytes long. Routing the struct
through the helper by `const&` does not change that.

### Next levers

1. Put a **32-byte** object at `-0x50` whose live member is the pair at offset 0,
   with **no call boundary** between `make_pair` and the copy ctor (the packer only
   gives 16-byte objects `-0x40`; only a 32-byte object lands at `-0x50`), or
2. make the `-0x40` value buffer live across the folder branch **without emitting
   code** (a declaration the optimizer cannot sink), or
3. find the original declaration shape that produced retail's allocation order —
   every instruction, the frame and all EH states already match, so only the way
   these two buffers are declared is missing.

## Provenance

Bank `reverse/attempts/0x006045a2.cpp` (score 0.99) is the drop-in TU; the in-unit variant is
newer and equal-or-better. Donor/name evidence for the class and the descriptor is in the unit's
header comments. The class is a private view here (no canonical header).
