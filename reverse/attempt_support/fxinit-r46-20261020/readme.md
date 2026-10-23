# FXShaderGeometry::Init 0x18C84E, r46 (2026-10-20, claude-opus-5-5, ~70 min)

State unchanged from the 0.995 bank: 2333/2333 B, EH exact, 8 lines
(unresolved call +0x473 and the 7-line two-bone block 0x18CF55..0x18CF6C).
Scratch: build/nbr/r46/18c84e (best.cpp = bank + WB-backed accessor shapes,
all byte-neutral: Get_Vertex_Array(bool) branch per WB 0x4B3B10, Poly->Get_Array,
split Define_FVF, uncast VB/IB counts).

## Two-bone block
- WB accessor shapes, STLport operator[]/size_type/iterator overloads,
  unsigned char vertices: inert. /Ob1, /GR inert; /GX 304 lines, /Oi 416,
  /G6 506, /Oy- 245.
- Code placed elsewhere in the TU (5..300 statements) inert: per-function.
- Mini kernels (/O1): cl orders the two movsx loads like the index loads for
  every equivalent spelling of the sum (+ | ^ - *256, casts, commuted, store
  types, raw short* base). Retail loads links[1] first but computes
  remap[links[0]] first; no spelling of the statement does that. Untested:
  IV/CSE structure of the whole vertex loop (weights and positions[1] share
  the induction variable).

## 0x211E58 call: F/G naming contradiction (structural inference from ledger)
Needed: ??0?$_Vector_base@FV?$allocator@F@_STL@@@_STL@@QAE@ABV?$allocator@F@1@@Z
(no row/pin; 0x211E58 holds 43 folded _Vector_base(const A&) rows, none 2-byte).
- F proxy pinned at 0x7410 (symbols.csv ~line 1399, from 0x513D55), so a
  fold-proof base pin fails at +0x13 (0x211E58 calls proxy 0x14F3C4).
- ?allocate@?$allocator@F@_STL@@QBEPAFIPBX@Z is rowed 0xAD722 AND pinned 0x17710
  (~line 15943, the 29 B allocator<G>::allocate row); its note cites 0x7EAA7,
  now rowed as the G _M_insert_overflow. 0x7410 also carries the G proxy pin.
- Consistent reading: 0x7410/0x17710 = unsigned short (G, wchar_t without
  /Zc:wchar_t) family; 0x14F3C4/0xAD722 = signed short (F). Unverified: the G
  pair is 16-byte aligned (/O2 pattern), the F pair not.
Resolution order: retire the two F pins; rename rows 0x513D55 and 0x513DD0 to
G with consumer 0x513ED1 (AptCreateAHeroDrawMapComponent.cpp) retyped (the
UTF16 seats measured 412 B for that retype: the blocker, see
fxinit-utf16-family-20261020); then pin_admission --add the F proxy at
0x14F3C4 and the base ctor at 0x211E58 with fold-proof=stlport_vector_s_o1.cpp.
Also: Rva0018C7E5Vector::resize row types the fill as unsigned short (IG) but
remap is signed; may need the same F/G review.
