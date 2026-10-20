# Render2DClass::Render 0x11A040 (7476 B): session 2026-10-20 handoff

Start from the bank `reverse/attempts/0x0011a040.cpp` (fit .9451478802311812,
7476 B). Nothing this session beat it; the bank is unchanged.

Later GPT second opinion: see [second-opinion.md](second-opinion.md). It retains
the same best body, disproves the unconditional RS+next rule below, and preserves
a smaller loop2 residue and a recovered-copy variant with only six terminator
sites remaining as diagnostic patches. Read that continuation before
repeating the proposed next angles here.

## Measuring

Fitness hides where the residue sits. Split retail offsets into regions and
count aligned-diff instructions per region (mnemonic+operand alignment):
prologue 0..0x5d0, copy loop 0x5d0..0x7e0, loop2 0x7e0..0x16d1, epilogue
0x16d1..end. Bank: copy 43, loop2 12, total 55. Compile/score one variant in
~6 s; 8 in parallel take ~7 s (`xargs -P 8`).

## Loop2: the StringClass terminator sites (27 sites)

Every inlined RS/TSS snapshot builds `StringClass value_name(0,true)`; the
terminator store is either B (`mov eax,[esp+0x10]; mov cl,[NullChar]`, buffer
first) or N (`mov al,[NullChar]; mov ecx,[esp+0x10]`). Context around each site
is identical in retail and ours.

Site map: 1-3 override TSS2, 4-6 mode6, 7 dot3 RS TF, 8 COLORARG0,
9-11 TSS0 ARG1/ARG2/OP, 12-14 stage1, 15-20 stage2, 21-22 stage3,
23 else RS TF, 24-26 else TSS0 ARG1/ARG2/OP, 27 STENCILENABLE.

- retail: B at 1-13 except 4 (lexical order), N at 14-27.
- bank (NAMED_TERMINATOR shim): B at 1-3,5-11,23,24; 12-13 N. These are the
  bank's loop2 12.
- plain terminator: 20 B (1-3, 5-19, 23, 24). If-form `operator[]`: 11 B
  (site 11 turns N).
- Model (not proven): B means the site's value_name is still within a fixed
  tracking budget. The named terminator spends 2 per site, plain spends 1, and
  the copy-region locals draw on the same budget. Retail with the plain
  terminator would need ~7 more consumers.
- **RS+next observation (subsequently refuted; see second-opinion.md)**: in the dot3 else branch, the Set_DX8_Render_State site and
  the site right after it are always B. Changing value, state
  (TEXTUREFACTOR->AMBIENT), order (ARG1,ARG2,TF,OP gives NNBB), count (TF alone
  gives B) or placing the else first (inverted condition: all 4 E sites B, then
  D sites lexical) never changes that.

## Copy region (0x5d0..0x7e0)

With the if-form accessor (`if(i>=Count) return Data[0]; return Data[i];`),
copy drops to 24 and the run loop matches retail exactly. loop2 rises to 77
because site 11 turns N, so the total is worse (116). What is left in copy:
- `this` in edi in retail, esi in ours;
- the order of the EH state store `mov byte ptr [esp+0x108],2`;
- batch loop slots: retail keeps b in [esp+0x10] and off in [esp+0x20] (with
  `xor esi,esi; mov [esp+0x20],esi`, `add esi,0x74`, reloaded and stored at the
  latch). Ours swaps them (`add dword ptr [esp+0x10],0x74`) and hoists
  `mov edi,[esp+0x1c]`;
- after the locks: retail `mov ebp,[esp+0x28]` (this), `mov edi,2`, and a
  `lea ebx,[ebx]` pad; ours uses eax and `mov ebp,2`.
The `ix_reload` variant (BUFFER_RELOAD) reached copy=9 but loop2=70.

## WorldBuilder twin shape (build/r2d/wb.txt)

- mode6 falls through to a separate `if(mode==3||mode==4)`, so the ifs are
  separate (sepif is inert in retail).
- In the loop: `if(G) Rva00118810();` (0x118810, 129 B, stencil setup:
  RS 0x34,0x39,0x3a,0x3b,0x36,0x35 then 0x38/0x37 per mode 2/1). At the end:
  `if(G) Rva001188A0();` (0x1188A0, 22 B). wb 0x9c1b90 =
  `if(G) Set_DX8_Render_State(0x34,0)`. Both helpers sit just before
  Set_Coordinate_Range 0x1188C0, so they are most likely render2d.cpp
  functions.

## Disproven (do not repeat)

This session:
- Copy factorial: if-form accessor x plain IB size x plain VB size x plain
  batch index x barrier removal. Best is the bank (55); the barrier is inert.
- Dot3 condition shapes d1-d8: single condition, swapped &&, inverted, nested
  duplicate, bool variable, `else if(1)`. None fixes sites 23-24.
- Else content e1-ea (values, order, state, stage, removal, duplication): the
  RS+next rule persists.
- Defining Rva00118810/Rva001188A0 in the TU before Render, and
  `if(G) Rva001188A0()` at the end: byte-identical to the bank.

Earlier sessions (see pick-hard history):
- dead locals; else constants and swap; inverted condition; gt2, notnot,
  braces; bvar;
- forceinline ctor; reload terminator; sepif, norwb, novol; compiler flags;
- f1/f3 factorials (.901325); faithful {head, idxif} .739; BUFFER_RELOAD
  .87164; default ctor .90775;
- batch expression variants; memcpy source variants; real Get_String, VB and
  IB sources; scaffold removal;
- WB viewport bk_a (52 at 7477 B, wrong size); shim pragmas; inline body shape
  factorial; stage-branch removal (7539 B).
- Probe: RS/TSS `__forceinline` does not inline in small functions (C4714), but
  it does inside a probe with prologue + vb/ib + the batch loop.

## Next angles (untried)

1. Fix the copy-region allocation on the if-form base:
   - a batch reference or pointer local (`Render2DBatch &curDescr=Batches[j]`);
   - a j/i loop shape and the order in which b and the induction variable are
     declared;
   - a signed vs unsigned Batches.size(), or std::vector-like batches.
   Then compensate the B budget so loop2 returns to 13 lexical B, e.g. plain
   terminator plus extra locals that stay live.
2. Find the source shape that drops the RS+next B in the else branch while
   keeping 13 lexical B.
3. Run permute.py once only registers or slots differ.

Compiler: `// cl:` line 7 of the bank (-O2 -G7 -arch:SSE -GR- -EHsc- -MD,
NAMED_TERMINATOR + NATIVE_CSTR_ASSIGN shims). model=claude-opus-5-5.
