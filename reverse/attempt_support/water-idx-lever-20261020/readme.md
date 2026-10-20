# 0x0008304A RenderableStandingWaterArea::AllocateAndFillBuffers: idx lever (2026-10-20)

Model claude-opus-5-5. The bank moves from fitness 0.9197 (1163 B, first diff
+0x18F) to 0.9394 (1152 B of 1156, frame 0x88 like retail, first diff +0x188).
The earlier banks are in `water-vector-escape-20261020/` and
`water-buffer-lifetimes-20261020/`.

## What changed

1. The stub `vector<char>` specialization is replaced with the full loader
   graph. That is the text from `#define fill bfmeLoaderHeaderFill` up to
   `class File` in `Code/GameEngine/Source/Common/Rva00240000Load308050.cpp`:
   inline erase, `_M_insert_overflow`, `_M_fill_insert` and resize. With it,
   `flags` does not escape and its start pointer is hoisted.
2. `flags` is a real `_STL::vector<char>` with `flags.resize(total,0)`.
3. The first-pass store is spelled `int idx=y*nx+x; flags[idx]=in; count+=in;`.
   Change 3 is the lever. Without the named index, the full graph alone gives
   frame 0x90 with x in edi (`water-vector-escape` control 18). With it, the
   first pass builds retail's edi cell-pointer IV (a row base at [ebp-0x24],
   `add [ebp-0x24],ebx` per row) and restores frame 0x88. The first-pass loop
   is then byte-identical apart from two slots.

## Remaining residue (about 96 lines)

- (a) Slots. Retail packs count, the operator+ esp-save, the `new` temp and
  the pass-2 cell IV at [ebp-0x14], and y at [ebp-0x18]. Ours swaps the two.
  Tried with no change: `int count=0; int y;` declaration order, and for-scoped
  y per pass (x09, 0.937).
- (b) Cache ctor argument schedule. Retail computes `lea ecx,[ebx+eax*2+1]`
  before loading the boundary pointer `[esi+0x14]`; ours loads it first. These
  leave the bytes unchanged (all 0.9394):
  - a `maxNumVertices` local, with or without WB's `numCells=count` copy;
  - an inline `getBoundaryPoint(0)->z`;
  - a named `Vector3 origin`;
  - a named z local.
- (c) Pass 2 needs the same cell-pointer IV as retail. Retail recomputes
  `y*nx+start` per row with imul into [ebp-0x14], then runs
  `cmp byte [eax],0 / inc eax` per cell.
  - The plain `flags[y*nx+x]` (also `x+y*nx`, `!=0`, `if(!..) continue` as in
    WB twin 0x73F580, or a row base local) only hoists the row:
    `cmp byte [eax+ecx]`.
  - Every spelling that creates the IV gives it ebx and spills nx (frame 0x8C,
    0.841):
    - a pass-2 `int idx`, also unsigned, `==0`, or with `continue`;
    - a function-scope idx;
    - `*p++`;
    - a row pointer.
  - Retail keeps nx in ebx and the IV in memory. This register choice is the
    open question.
- The operator[] spelling (`*(begin()+n)`, `*(_M_start+n)`, `begin()[n]`) does
  not matter in any of the three pass forms.

WB twin facts (`tools/wb_show.py 0x0008304A`):
- y is one function-scope variable; x is declared per loop.
- Pass 2 is `if(!flags[y*nx+x]) continue;`, with a dead `Coord2D` x/y
  position computed per cell.
- The cache is the local class `AllocateAndFillBuffers::CachedVertexAdder`
  (`getOrAddVertex(x,y)`).
- `maxNumVertices = numCells*2+nx+1` and `numIndices = numCells*2*3` are
  locals. The asserts are on `m_vertices.size()`.

Not yet tried: permute.py on this bank, and `--flags`.
