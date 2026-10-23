# 0x001F1609 — `??1?$_Vector_base@PAVObject@@...@@_STL@@QAE@XZ` trio — hand-off

Status: blocked (identity + ABI proven by `reverse/symbols.csv` pin 15549; body
unrecovered). Companion funclet `0x0076B1CA`, ehhandler `0x0076B1D5`. This file
carries the full mechanism hunt so the next attempt starts from facts, not flags.

## Retail bytes (verified)
- dtor 43 B @0x001F1609:
  `b8 <VA 0x00B6B1D5>` `e8 <__EH_prolog 0x629188>` `51` `89 4d f0`
  `8b 01` `83 65 fc 00` `85 c0` `74 07` `50` `e8 <free 0x30830>` `59`
  `8b 4d f4` `64 89 0d 00000000` `c9` `c3` — helper EH frame (`__EH_prolog`),
  this-spill at `[ebp-0x10]`, state slot `[ebp-4]`, free-direct of `[this+0]`,
  count DCE'd. Wrapper `0x001F22A3` = 5 B `e9` into it. FuncInfo data at
  0x00910608 (no row needed; matches the rowed PAX trio family).
- funclet 11 B @0x0076B1CA: `8b 4d f0` `83 c1 08` `e9 <ext>` — destroys the
  `_STLP_alloc_proxy` subobject at `this+8`; jumps the shared 1-B `c3` fold
  0x00B3FD0 (ICF with Region2D/3D, Coord2D/3D rows).
- ehhandler 10 B @0x0076B1D5: `b8 <FuncInfo VA 0x00D10608>` `e9 <thunk 0x629182>`.

## Census cofacts (link_index.pkl comdat groups)
- `??1?$_Vector_base@UCoord3D...` group: 22 units, ALL tag `retail`, modal
  digest `07644a8ba00d` x19 → retail's Coord3D twin IS the 14-B frameless
  family shape, and in-repo units already compile it at /O1+EHsc+shim. Multiple
  digests per group each still tag `retail` (per-copy retail-truth).
- `??1?$_Vector_base@PAVObject...` group: 18 units, ALL tag `wrong` (17x
  14-B + 3x 24-B count-aware). Retail kept the 43-B; every in-repo holding a
  competing 14-B/24-B copy blocks its file (`wrong_selected`) — the trio
  unblocks ~18 units' census status when it lands.
- BFME1 donor claims of "matched 45-B / 14-B" bodies are NOT byte-verifiable
  locally (no BFME1 image); treat them as leads only.

## Mechanism conclusions (probe-verified, build/probe/ rounds v1..r3 + toys)
Rule observed across 17 flag combos with the bfmealloc shim:
- /O-level (/O1, /O2) — with or without /GS, /EHsc variants,
  /D_STLP_NO_EXCEPTIONS, /D_STLP_USE_MALLOC, member vs full-class explicit
  instantiation, corrected decl-only `_STLP_alloc_proxy<Object**,Object*,...>`
  spec-decl, PAX-style outer-member suppressions — ALWAYS yields the 14 B
  frameless body (`8b 01 85 c0 74 07 50 e8 free 59 c3`) plus an UNREFERENCED
  1-B `c3` proxy-dtor fossil (find_refs: only `.debug$F` mentions it).
- /Od — yields the manual-prolog EH frame, never the helper form:
  - /Ob0: 107-B, this@[ebp-0x10], state mov-imm, count kept, out-of-line
    2-arg deallocate call (x2/x3/z3/g2/m2 shapes).
  - /Ob1: 109-B, this@[ebp-0x18], count dead-stored, free-direct (byte-identical
    to retail PAX 0x00251F0 modulo masks — the PAX donor recipe IS this).
  - /Ob2: 64-B plain prolog, free-direct, count dead, plus orphan funclet stub.
- Vendor headers without the shim (/O1): 24-B count-aware 2-arg call; (/O2):
  45-B SGI 128-byte-threshold two-branch body. Neither matches retail.
- /GS never selects the `__EH_prolog` helper; only /Od-without-Ob0 keeps
  machinery, always as the manual 6a ff/68 stub prolog.

Why machinery-at-/O-level cannot be had through the template route: at /O1 the
compiler proves the whole `~allocator -> ~_STLP_alloc_proxy` (shim -> header)
chain empty-visible and elides the unwind action AND the sub-dtor call.
Explicit-specialization declarations on the dtor are honored for plain direct
calls (minim toys prove it) but do NOT suppress the <vector> in-TU chain
materialization the template instantiation performs; the shim chain remains
empty-provable regardless. The empty-class-specialization forward-decl route
fails to compile (`_M_end_of_storage` member needs the complete class).

Working theory for the next attempt (unproven): retail's 43-B TU saw the
`_STLP_alloc_proxy<Object**, ...>` chain as EXTERNAL (non-visible definition) —
machinery is then kept even though the funclet e9 binds to a 0xB3FD0-folded 1-B
`c3` later. How retail's TU achieved externality of an STLport template member
under MSVC 7.1 with `<vector>` visible is unknown. Do not re-spend the flag
matrix above; it is exhausted.

## Adjacency lead (unexplored)
Ledger row `?rva001F1513@GenericObjectCreationNugget@@QBE_NPBVObject@@@Z`
(246 B, ends exactly at 0x001F1609) and the pin's creator/consumer
0x001F1634 / 0x001F2F0E bracket the trio: the retail TU almost certainly
emitted requirement-check + vector-base-dtor + next function in one run, with
cl: `/Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc`
(GenericObjectCreationNuggetRequirements.cpp). That TU instantiates
vector<AsciiString>, not vector<Object*>; check which sibling零售 TU owns the
Object* usage and whether its source context (a `throw`/guard inside a scope
destroying a vector<Object*>) forces what the plain dtor family cannot.

## Recipe that DOES work (banked, wrong target)
`Code/Libraries/Source/WWVegas/WWLib/stlport_vector_voidptr_alloc.cpp` (PAX)
at `/Od /Ob1` reproduces retail's `_Vector_base<void*>` 109-B family exactly.
The same recipe on a `_Vector_base<Object*>` TU reproduces the 109-B bytes for
the WRONG address (no retail row hosts them). That donor TU was therefore NOT
committed; its content lives only in the probe history (build/probe/, untracked)
and this note.
