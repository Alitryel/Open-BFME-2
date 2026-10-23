# TexturePacker::UpdateResultTexture (0x001711A6, 892 B) handoff

## Result

The banked body `reverse/attempts/0x001711a6.cpp` (symbol `?rva001711a6@Rva00171024@@QAEXXZ`) compiles to 892 bytes that equal retail at every byte outside relocation slots (0 unmasked differences over 0x001711A6..0x00171522), with the same frame (`sub esp,0x144`), the same register assignment and the same six unwind funclets (frame offsets -0x50, -0x30, -0x38, -0x1C, -0x28, -0x20, in retail's order; the parent states were not compared). Every REL32 site reaches the retail target its name implies. It cannot land yet because six call sites, and four of the unwind funclets, name typed STLport or handle members whose retail addresses are rowed under different (address-derived or differently typed) spellings.

## Measurements (`tools/align_diff.py <file> ?rva001711a6@Rva00171024@@QAEXXZ 0x001711A6 892`)

- Previous bank (farm, score 0.617): ours 835 B, 27 structural regions, 33 memory and 27 register differences, frame 0x144.
- This bank: ours 892 B, 1 structural region, 2 memory and 0 register differences, frame 0x144.
- The one remaining region is retail's following functions from +0x37C, which align_diff includes because the next body abuts this one without `cc` padding (its boundary search reports 1200 B). Both memory differences are the `__real@3f800000` DIR32 load (the 1.0f constant at 0x007BB8D8), which the gate fills from retail.

## What closed the shape (each read from WB A12EB0 and checked against retail)

- The area loop inserts `make_pair(area, it->first)`: retail and WB build the `pair<unsigned, AssetReference>` temporary (0x00170A3D), convert it to the multimap's value type (0x001709BA), insert (0x00170E3D) and release both temporaries (EH states 2, 1). Constructing `value_type` directly drops both calls.
- `Width() * Height()` in source order compiles to retail's call order (0x00132784 first, then 0x0013275A). The farm bank's separate width/height locals called them in the opposite order.
- Only `skyline[0]` is zeroed up front (WB stores one zero); the doubling step zeroes `[side, 2*side)`.
- The texture size in pixels is written `side<<5` at each of its three uses, as WB evaluates it three times; a `pixels` local moved the esi/edi assignment of loop 1 and of the post-loop code.
- The D3DX destination rectangle is a `RECT` built member by member from the packed map rectangle (WB copies the four members through a reference). A struct copy compiled to `movsd` and took esi/edi, which pushed `&result` out of edi, the node out of esi and `&rectangles` out of ebx in the copy loop, and grew the frame to 0x148.
- The validity test is an inline null-guarded virtual call (retail's `xor al,al` arm), and the surface clear receives the +0x1D flag as a byte (`mov al,[ebx+1Dh]; push eax`, no zero extension), so its parameter is bool-sized.
- Writing the packing loop in WB's `for(;;) { ... if (no fit) { double } else { place; break; } }` form compiles to the same code as the earlier `if (fits) break;` form; it is kept because it follows WB.

## Remaining blocker: callee spellings

| site | name this source emits | retail target | existing row or pin at that address |
|---|---|---|---|
| +0x03C | `??0?$multimap@IVAssetReference@@U?$less@I@_STL@@V?$allocator@U?$pair@$$CBIVAssetReference@@@_STL@@@3@@_STL@@QAE@XZ` | 0x0033C432 | shared 25 B empty-tree constructor, many gen-alias owners |
| +0x081 | `??$make_pair@IVAssetReference@@@_STL@@YA?AU?$pair@IVAssetReference@@@0@ABIABVAssetReference@@@Z` | 0x00170A3D | `?Rva00170A3DGet@@YA?AVRva00151DAB@@ABIABVAssetReference@@@Z` |
| +0x08D | `??$?0IVAssetReference@@@?$pair@$$CBIVAssetReference@@@_STL@@QAE@ABU?$pair@IVAssetReference@@@1@@Z` | 0x001709BA | `??0Rva00151DAB@@QAE@ABV0@@Z` |
| +0x0A1 | `?insert_equal@?$_Rb_tree@IU?$pair@$$CBIVAssetReference@@@_STL@@...` | 0x00170E3D | the same member typed with `Rva00170E3DElement` |
| +0x2C0 | `?clear@W3DRadarResetSurface@@QAEX_N@Z` | 0x00116780 | `?clear@W3DRadarResetSurface@@QAEXI@Z` (real name, unsigned parameter) |
| +0x369 | `??1?$_Rb_tree@IU?$pair@$$CBIVAssetReference@@@_STL@@...@QAE@XZ` | 0x00170D7F | `??1Rva00170B19@@QAE@XZ` |
| funclet 0 | `??1?$multimap@IVAssetReference@@...@QAE@XZ` | 0x00170E78 | `?rva00170E78@Rva00170E78@@QAEXXZ` |
| funclets 1, 2 | `??1?$pair@IVAssetReference@@@_STL@@QAE@XZ`, `??1?$pair@$$CBIVAssetReference@@@_STL@@QAE@XZ` | 0x00151DAB | `??1Rva00151DAB@@QAE@XZ` |
| funclets 3, 5 | `??1AssetReference@@QAE@XZ` | 0x0017098D | `??1?$RefCountPtr@VTextureClass@@@@QAE@XZ` and its gen-alias names |

The seat rules allow a pin only under the name an address's row already uses, and `stlport_folds.py` proves only vector, allocator-proxy and list-base members, so none of these resolve today. Two routes remain:

1. Typed provider rows. Add gen-alias rows (`add_match.py --icf-owner`) for each typed instantiation in a unit that compiles it to a byte-and-relocation twin. `Code/Libraries/Source/WWVegas/WW3D2/texturepacker_area.cpp` already holds the typed pair constructor at 0x00170A14, so `make_pair` (0x00170A3D) is the next cheap one. `insert_equal` and the tree destructor need their typed closures as well: `_M_insert` 0x00170C87, `_M_create_node` 0x00170B70, `_Construct` 0x00170A97, `clear` 0x00170BD6, `_M_erase` 0x00170B19 and `_Destroy` 0x00170A7C.
2. Respell this body against the address-derived provider classes (`Rva00151DAB`, `Rva00170B19`, `Rva00170E3DElement`) and keep the emitted bytes. The make_pair-to-conversion copy must stay a real copy (a temporary copied straight into a same-typed object is elided).

Either route still needs the `clear` parameter reconciled. Retail's caller here proves a byte-sized parameter, while the row and its other caller (W3DRadar::clearShroud, which pushes an immediate 0) are spelled `unsigned`. Renaming it to `bool` means re-verifying `Code/Libraries/Source/WWVegas/WW3D2/SurfaceByteSize.cpp` and that caller's unit.

## Identity and destination

WB A12EB0 is `TexturePacker::UpdateResultTexture` (assert path `texturepacker.cpp`, line 112), and the native call graph agrees: rowed 0x00171625 calls this body after its dirty test. The bank keeps the address-derived receiver `Rva00171024` that the rowed constructor 0x00171024 and getter 0x00171625 already use. `python tools/repair_queue.py dest 0x001711A6` names `Code/Libraries/Source/WWVegas/WW3D2/matinfo.cpp` (approved `tu_map.csv` region 0x001708D0..0x00171522); WB's file name is `texturepacker.cpp`.

## Inputs

Compiler profile: the bank's own `// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc` with `// stlport`. `/EHsc` matters: retail has no EH state for the source surface across the `extern "C"` D3DX call.
