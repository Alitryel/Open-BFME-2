# Result

Closer partial for `?rva000FF5E6@Rva0007E90ECallee@@QAEXH@Z`, RVA `0x000FF5E6`, 788 bytes. The new bank removes both structural regions of the previous one: the end cursor's owner store `mov [ebp-0x4c],edi` now sits in retail's loop preheader, between the guard's equality test and `push ebx`. No exact match, no `Code/` source, no ledger row and no pin.

| Body | Bytes | Structural | Memory | Register |
|---|---:|---:|---:|---:|
| previous bank (`before-align.log`) | 788 | 2 | 13 | 4 |
| new bank (`final-align.log`) | 788 | 0 | 12 | 4 |

Six memory lines in both counts are unpatched absolute addresses (`0xde2000`, `0xbc2a24`, `0xbc26f0`, `0xbbaeac`, `0xdec218`, `0xe099f8`), so the real memory differences are 7 before and 6 after.

# What closed the owner store

Two changes act together; each alone does nothing useful.

1. The cursor equality is defined in the unit, as the landed siblings `W3DWaterAreaRenderables.cpp` and `W3DWaterStandingWaveQuery.cpp` already do (`extern "C" inline __declspec(noinline) bool __cdecl rva0007E394CursorEqual`). It compiles byte-identical to retail 0x7E394 (29 bytes, 0 differences under `align_diff.py`). With the body visible, cl knows the call keeps no cursor address, so the loop can be the natural `for (it = set->begin(); it != set->end(); it++)` and the latch's owner store is hoisted to the preheader. With an opaque declaration, the natural loop, a postfix increment, a const owner field and a guarded do-while all keep the store in the latch.
2. With the visible body alone, cl also keeps the entry array pointer (`[set+0x14]`) in a register across the latch call, which moves the collection to ESI and the zero to EDI (8 structural regions, `visible-equality-only.cpp.txt`). Retail reloads it at the loop top. The bank breaks that common subexpression with a joined begin receiver, `(collection?collection:collection)->begin()`. This is the same "area-begin PHI" the 0x0008026B landing uses for the same walk over `AreaSet<StandingWaveArea>`.

The iterator now follows WorldBuilder's `AreaSet.h` (0x4E9FE0 begin, 0x4EA010 end, 0x4EBD40 constructor, 0x4EA060 prefix and 0x74CC90 postfix increment, 0x4EA1B0 `getPtr` reading `m_set->m_areaEntries[m_index]`). These are facts from the WorldBuilder build; the names inside the bank stay address-derived views.

# Not landable as is

- The equal-arm receiver is a compiler-steering construct (matching.md asks for a natural spelling with the same shape). Spellings that did not reproduce the join: a constructor taking `const AreaSet &`, a default-constructed iterator assigned in the loop, a reference to the set, and `begin()` declared const. Each gives the same 8-region result as the visible equality alone.
- The `if(0){EliminatedLifetime ...}` stub from the earlier bank is also steering. WorldBuilder 0x829D80 shows the real source: `Bool loadFromFile = false; if (loadFromFile) { ...read <map>.wak... } else { ...this body... }`. `dead-branch-trial.cpp.txt` writes that branch out from WorldBuilder and Zero Hour `loadTracks`, keeping EA's comments on duplicate detection, flip toggling and the second wave. It compiles, but measures 788 B with 4 structural, 29 memory and 15 register differences: it pushes EDI in the prologue, puts the zero in EDI, and gives the live AssetList EH state 3 where retail has 2. The extra EH state and the register shift are the next things to explain before this branch can replace the stub.

# Remaining mismatch

Only the three 8-byte homes in the segment loop differ. Retail: midpoint-X home `-0x6c`, first endpoint `-0x64`, second endpoint `-0x5c`, perpendicular `-0x54`. Bank: endpoint aggregate at `-0x6c`/`-0x64`, midpoint-X home `-0x5c`. All other frame slots, the 0x74 frame and the 788-byte length match.

Ruled out for the homes in this run (all with the new loop):

- Separate `Vector2` endpoint locals, at function scope or inside either loop, in either declaration order: the pair moves above the cursors (`-0x44`/`-0x4c`), 23 memory and 8 register differences. Declaration position is not the lever.
- The second endpoint as one sum `midpoint+perp`: 14 memory with the aggregate, 24 with separate locals.
- The midpoint written straight into the first endpoint (no named midpoint): 780 B, 7 to 9 structural regions.
- WorldBuilder-faithful geometry (`Set` from the polygon points, `startPos = startPos + dir*0.5f`, `endPos = startPos + perp`): 790 B, 9 structural regions.

Observation for the next attempt: with separate locals, everything except the endpoint pair already sits in retail's order (cursors, end temporary, perpendicular, midpoint home at `-0x6c`). The pair only has to drop below the perpendicular, which looks like an allocation-priority question rather than a declaration-order one.

# Inputs

Start clock 2026-10-20 02:53:10 (seat shell `date`). Every measurement used `BFME_OBJSTORE=off BFME_HOST_TAG=fleet` and a fresh trial path under `build/ff5e6-w2/`. The bank keeps the previous first `// cl:` line (`/O1 /arch:SSE /G7 /MD /EHsc`, BFME 2 ASCII shim, donor WWMath and WWLib includes) and every earlier comment line. Model: `claude-opus-5-5`.
