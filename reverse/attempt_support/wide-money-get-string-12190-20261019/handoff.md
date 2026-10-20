# 0x00012190 `?do_get@?$money_get@GV...` — 2802 B wide twin, residue sharpened

Verdict: `blocked` (re_attempts.log). Best bank: `reverse/attempts/0x00012190.cpp`
(score 0.7, 2740 B / 679 insns) — **untouched, still the base**. Do not replace it
with a plain-string variant (see "Refuted this session").

Rows: `?d_00012190@@YAXXZ` (122 B) + `?d_0001220a@@YAXXZ` (2680 B) in
`Code/gen_asm/d_000112aa.asm`; retail code 0x12190..0x12C82, then 20 B switch
table (0x12C84), extent 2822. Narrow twin 0x11230 is matched by
`stlport_narrow_money_get_string.cpp`.

## Measured this session (bank, and a fresh plain-string variant)

`tools/explain_mismatch.py '<wide mangled name>' --rva 0x12190 --size 2802 --source <file>`
(the exact decorated symbol is required as the selector when `--rva` is used):

* **Bank** (`reverse/attempts/0x00012190.cpp`): 2740 B compiled / 2802 retail,
  classification `size mismatch`, **first diff +0x23D (RVA 0x123CD)** — a single
  byte, `88 44 24 12` vs `88 44 24 1a`. Everything before it (prologue, frame
  `sub esp,0xc8`, locale/facet setup, `__format`, `__ns`/`__ps`, the head
  `equal`/`je`, EH state stores) is byte-identical: the 573 B prefix claim is
  exact.
  The byte is `mov byte ptr [esp+0x12], al` — the `__symbol_required =
  (__str.flags() & showbase) != 0` store; the bank puts that bool at **0x1a**,
  retail at **0x12**, and retail's 0x12 has 4 uses while the bank never uses
  0x12. `mov byte ptr [esp+0x13], 1` (the `__is_positive = true` store) matches
  in both, so exactly one bool's slot differs.
* **Plain-string variant** (this session: narrow source transplanted to
  `wchar_t`, wide `_String_base<unsigned short, allocator<unsigned short> >::
  ~_String_base()` declared at namespace scope before first use, no `/Ob1`):
  2724 B / 666 insns, **first diff +0x17 (RVA 0x121A7): `sub esp,0xcc` vs
  retail's `0xc8`**, prologue `push ebp; xor ebp; xor ebp,ebp` vs retail's
  `push edi; xor edi,edi`. Worse than the bank on both counts — the bank's
  `_MoneyNameStorage` model is what buys the 0xc8 frame and the EDI prologue.
* Instruction-level alignment (`align.py` in this directory, difflib over
  (mnemonic, operands-with-numbers-masked), 679 vs 679): equal 527, replace 91,
  delete 98, insert 71. The non-equal opcodes are **moved blocks**, not missing
  logic: retail materialises the iterator result (`mov esi,[esp+0xe8]; mov
  edx,[esp+0xec]; mov eax,[esp+0xf0]`) inside the early failbit return at
  +0x298, the bank does the same copy later (+0x53a); retail's `mov byte
  [esp+0x13],0` tag store (idx 318) has no partner. Same slot values on both
  sides (0xe8/0xec/0xf0).
* Frame slot histogram (`frame_cmp.py`, retail tail vs bank): the offset sets
  coincide almost exactly — 0x28/0x38/0x44/0x50 and the six conditional temps
  0x78/0x84/0x90/0x9c/0xa8/0xb4/0xc0/0xcc are all present on both sides. The only
  *absent* retail offset in the bank is 0x12 (the bool above); count-only
  differences elsewhere are the call/free mix below.
* `/Ob1` is **inert on both sources**: bank with and without `/Ob1` compiles to
  the same 2740 B / 679 insns (`stash_noob1.cpp`), the plain variant to the same
  2724/666 (`v3ob1.cpp`). `#pragma optimize("s", on)` around the body collapses
  it to 1871 B (rejected). `#pragma inline_depth(1)` on the bank = 2740 B with
  frees 0 (rejected earlier, re-confirmed).

## The central paradox (two independent agents, still unresolved)

Retail destroys the three named wide strings (`__buf`@0x28, `__ps`@0x44,
`__ns`@0x38) with **out-of-line `call 0xB3C0`** at the shared early-failbit
cleanup (+0x88D) and at the value-case return (+0x90A), and with **inline
frees** at the final exit (+0xA87). Both agents' EH-state readings show states
**9/4/0** at all three places, i.e. the *same three objects*, at the *same*
`lea ecx,[esp+0x28/0x44/0x38]` slots. Totals: 13 calls to 0xB3C0 + 7 inline
frees; no `~locale` call (inline via `_M_impl->_M_decr` vtable slot 2); 3 wide
copy ctors; the 6 wide conditional temporaries at 0x78/0x84/0x90/0x9c/0xa8/
0xb4/0xc0 are always calls; the narrow `__grouping` and the narrow conditional
temporaries are always inline frees.

Consequences for the next agent:

* A second object set is ruled out — the EH states identify the objects, and
  states 9/4/0 appear at both treatments.
* Declaration visibility alone cannot produce it: definition visible ⇒ every
  site inlines (all-inline variants), declared-only ⇒ every site calls (2724 B
  variant). The inlined and called bodies are byte-identical instruction
  sequences (`mov eax,[obj]; test; je; push; call free`, or the 63 B framed
  form at 0xB3C0), so no type/visibility split can single out the final exit.
* Therefore retail's per-site inliner decision (calls at the early cleanups,
  inline at the final exit) is not reachable from declaration state; it needs
  either an inliner-budget effect we have not found a knob for, or a source
  shape where the early cleanups and the final exit destroy *different*
  expressions with identical slots.

## Next levers, in the order I would try them

1. The bool slot 0x12 vs 0x1a. Retail reuses a *dead* low slot for
   `__symbol_required`; the bank does not. Slot reuse is decided by the
   interference graph, so a source change that shortens the live range of the
   temp feeding the store (or that lets the compiler fold the `flags()` temp
   into the bool's slot) is the concrete experiment. It is the very first
   differing byte, so any fix shows up immediately.
2. The early-return iterator copy ordering (+0x298 vs +0x53a): retail writes the
   return slot before the cleanup; the bank's copy is sunk. This is the second
   diverging byte and it is inside the first 0x400 bytes, so it gates the same
   prefix.
3. Only then the call/free mix — the paradox above.

## Reproducing the diagnostics

The three scratch tools live in `build/note/` (untracked): `asm_list.py` (repo cl
+ `/FAs` into `build/scratch/`), `mine_dis.py` (capstone disassembly of a COMDAT
body), `frame_cmp.py` (`[esp+N]` histograms vs `build/note/d_0001220a.dis`).
`align.py` here is `insn_align.py`; it needs `build/note/<body>.dis` from
`mine_dis.py`. All of them are read-only w.r.t. retail bytes.

Standing refutations to avoid re-running: `/Ob1`, `/Ob2`, `/Os`, `/O1`,
`/Og-`, `#pragma optimize("s", on)`, `#pragma inline_depth(1..8)`,
`extern template class` for `_String_base<wchar_t>`/`basic_string<wchar_t>`,
`__forceinline`/`inline` on `__get_string`/`__get_symbol`/`operator++`/`equal`/
`_M_getc`, non-inline specialization without an emitter, explicit `assign`
declarations (C1001).
