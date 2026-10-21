# 0x00655B90 FESL record-field replacer (549B) -- seat6 d8 handoff

Partial. Bank `reverse/attempts/0x00655b90.cpp` replaced (old 0.30 C++ rewrite with a
volatile separator read -> 0.883 clean, no volatile/barrier).

Target evidence: native 0x00655B90..0x00655DB5, cdecl, args (buffer, size, field) read at
[esp+4]/[esp+8]/[esp+0Ch], returns -1 / 0 / written length-1; only caller is the FESL unit's
escaped-field writer (Code/GameEngine/Source/GameNetwork/Rva007E8D30FeslSetField.cpp), which
today calls it through the placeholder pin `?d_007e8b00@@YAXXZ` and is that unit's sole link
blocker (391 B).

Donor fact: the body is the same function as the matched /Od DirtySock C copy `_Rva007EC780`
(0x006596B0, Code/Libraries/Source/DirtySock/Y4TextToValue.c). Copying that C body verbatim
into the owner unit (FESL tables `g_bfmeFeslFieldClassTable` / `g_bfmeFeslFieldSeparator`
substituted, field index cast to unsigned char as retail's `movzx edx,bl` requires) compiles
544B with the full control flow, loop shapes, inline memcmp/memcpy and the two memmove calls
in retail's order. Structural inference: same source, optimized (/O2 default of the unit).

Residue (only two, both allocation/scheduling):
1. Register roles: retail keeps pValue in EBX (re-using the EBX that held the first field byte
   BL during the scan) and the field length `i` in EBP, whose `push ebp` is delayed to
   0x00655CE7; cl 7.1 gives i=EBX, pValue=EBP and pushes EBP in the prologue. That one byte
   shift plus EBX/EBP swaps are ~200 of the 209 diff lines.
2. Tail: retail `cmp byte [sep],0Ah` then reloads sep in the else arm; cl hoists one
   `mov al,[sep]` above the `pValue[i]==0` branch.

Inert (all 544B, identical residue): separate length variable (int/unsigned, declared
first/last), pValue declared first/last, `register`, four pTail/pValue assignment forms,
no pBuffer copy, a pField copy, static helper + direct call from Rva007E8D30, plain .c compile
with signed/unsigned index, /G5 /G6 /Ox /Ob1 /Oi /Ot, vc71-sp1 and vc71-ddk-4035 profiles;
/G7 555B, /O1 or /Os 443B, /Oy- 579B; tail forms (unsigned casts, inverted if, early return,
ternary 548B, `i--` first). tools/permute.py: 793 trials, no gain.

Landing note: when exact, define it in Rva007E8D30FeslSetField.cpp, call it directly from
Rva007E8D30 (drop the `d_007e8b00` cast) and retire the placeholder pin; the unit then links.

## Update: register roles closed (0.883 -> 0.957)

Writing the length loop as `for ( i = 1; (unsigned int)field[ i - 1 ] >= ' '; i++ ) {}`
(same final value as the donor's `for ( i = 0; ...field[ i ]...; i++ ) {} i++;`) makes cl
choose retail's roles: pValue=EBX, i=EBP with the late `push ebp`, and retail's epilogue
order. The body is then exact through 0x00655CE7. A `field[ i + 1 ]` index flips the roles
too; plain `field[ i ]` with `i = 1`, unsigned/long/short `i`, cast spellings, while/for/do
forms, `++i` inside the iDelta expression, separate or early-initialised length variables
do not. So the roles hinge on a near-tie in cl's allocator that the loop's address
displacement tips.

Remaining residue on the new bank: (a) that loop is rotated `mov ebp,1` / `[esi+ebp-1]`
instead of retail's `xor ebp,ebp` / `[esi+ebp]` / trailing `inc ebp`; (b) the hoisted
separator load in the tail (if/else, early return, inverted condition, nested ifs and
store-first forms on the new base all keep it). permute.py: 836 trials from the new bank,
no gain. Next lever to try: a form that keeps the donor loop but tips the same tie (another
displacement or a different base pointer for `field` in that loop only).

## Diagnostic: the displacement is the tipper

The semantically WRONG probe `for ( i = 0; field[ i + 1 ] >= ' '; i++ ) {} i++;` emits
retail's exact length-loop structure (`push ebp; xor ebp,ebp; cmp [esi+1]; jb; inc ebp;
cmp [esi+ebp+1]; jae; inc ebp`) and retail's roles; only the +1 displacement differs. So
with a displaced loop address cl 7.1 picks i=EBP/pValue=EBX, and with retail's undisplaced
`[esi+ebp]` it picks the opposite in every spelling tried. Constant offsets that cl folds
early (`(field + 1)[ i - 1 ]`, `field[ i + 1 - 1 ]`, `f = field + 1; f[ i - 1 ]`,
`(field - 1)[ i + 1 ]`) do not tip it; neither do `i[ field ]`, `*( i + field )`,
`i[ pValue ]` tail spellings, or ten code-neutral rewrites elsewhere (`!p`, `*p++ =`,
operand swaps in the iDelta/class tests, `*p` for `*p != 0`, `field[ 0 ]` for `*field`).

## Round 2 sweep (seat6, same day): bank unchanged at 0.957

These were scripted against the donor-loop base (roles wrong) and the 0.957 base. Nothing
gave retail's undisplaced loop with retail's roles, and nothing removed the hoisted tail load:
- Length spellings: pointer walk (`while`/`for`, `i = q - field (+1)`), separate
  `const char *base = field`, unsigned and signed char views of field, forceinline and inline
  length helpers (count, count+1, end pointer, unsigned view), index casts
  (`(unsigned)i`, `(long)i`), separate unsigned counter, comma-expression pointer temp,
  `i = i + 1`, compare spellings (`>= (unsigned)' '`, `> ' ' - 1`, `!( < ' ' )`), and
  late-folded offsets (`i + d` with d = 0 or 1, `(f + 1)[ i - 1 ]` through a local,
  `i * 1`, `i | 0`, `(&field[ i ])[ 0 ]`, `*&field[ i ]`). Every one either keeps the
  donor's wrong roles (209 diff lines) or changes the prologue (pBuffer moves to EBP).
- 120 random permutations of the eight local declarations: all identical (209).
- Function placement after Rva007E8D30Name (retail's TU order): no change.
- Scan-loop restructures (`while ( *++p >= ' ' )`, `for ( p++; ... )`, `while ( 1 )`, `!*p`):
  no change.
- Scoping the whole length/tail section in a `{ int n; ... }` block, with and without
  iDelta inside it: no change.
- Tail on the 0.957 base: a byte local for `pValue[ i ]`, a braced scope, the negated
  condition with the arms swapped, nested ifs, a flag local, a `cSep` local in the else arm,
  an else-if chain, unbraced arms, and type-punned unsigned or signed reads of the separator.
  The fitness stays at 0.9567 or drops (0.917 / 0.929).

Conclusion: cl folds every constant or copy-propagated offset before it allocates, so the
EBX/EBP choice is set by the final address forms; only a real loop displacement flips it.
Retail's identical code with the opposite roles points to a toolchain or IL difference not
reachable from this source family. One untested lead: a VC 7.0 or VC6 build of the EA FESL
library. No profile for either is in the tree.

## Session 2026-10-21c (claude-opus-5-5): tail solved, the role tie is still open

Candidates: `fesl-655b90-volatile-tail-20261021.patch.txt` (patches against the bank).

**Tail residue solved (target evidence).** Retail's tail compares `cmp byte [0xDD7F45],0xa`
and reloads the separator in the else arm. That is a volatile access. Two forms each give
exactly retail's tail: `*(volatile char *)&g_bfmeFeslFieldSeparator` on the condition, or in
the else-arm read. The head still reads the separator once, non-volatile. Every non-volatile
form hoists the load into a register: if/else shapes, nested ifs, flag locals, inline helpers,
statics, arrays, a struct member, 26 flag sets, the SP1 and DDK profiles, and now LTCG too (SP1
`msobj71.dll`, `link /LTCG`; the tail probe still hoists).
A volatile on the separator also fits an EA lib reading a global that another thread or module
may change. Structural inference: it is not proven to be in the original header.

**d0_e** = the donor loop (`for ( i = 0; field[ i ] >= ' '; i++ ) {} i++;`) + the volatile
else arm. It is exactly 549 B and every instruction and branch lines up with retail. The only
residue is that pValue and i swap EBX and EBP: retail pushes ebp late (0x157), d0_e at 0x29.
Two padding shifts follow from that (0xaa `jmp` vs `lea ebx,[ebx]`, 0x15f `mov edi,edi` vs
`nop`). By permute fitness it is 0.896 because of the swaps. **base_e** = the bank loop + the
volatile arm: 551 B, roles right, loop rotated, fitness 0.9557 < bank 0.957. Bank unchanged.

Disproved for the role tie, all on the volatile base:
- control flow and declaration scope: a 576-variant factorial (`build/f655/gen3.py`).
  It crossed decl order ×4, int vs unsigned i, a separate head index j, assignment form ×3,
  volatile placement ×3, for vs while, and a pBuffer alias. None flips.
- permute.py, 793 trials: none flips.
- compile as C (`.c`): none flips.
- compiler settings: the SP1 and DDK-4035 profiles, and LTCG (`/GL` + `link /LTCG`). None flips.
- callee visibility: the tail and loop have no calls, and memmove/Rva007EC030 visibility
  does not touch the loop region.

More families on d0_e (scripts `build/f655/gen4.py`..`gen7.py`, untracked):
- lifetime: the `*field` byte that shares EBX in both builds (retail: bl, then pValue; d0_e: bl,
  then i) made an explicit local. 4 types × 2 forms × 3 decl positions × 2 bases × 2 volatile
  placements = 96 variants: none flips (d0 stays regs=26, or worse).
- length loop spellings: `field[ i++ ]` in while/for/do (556 B), a pointer scan with
  `i = q - field` (542/545 B), `++i`, `i += 1`, `(unsigned char)`, `i = -1; do`: none flips.
- split length variable `j` + `i = j + 1` / `j++; i = j` / `i = ++j`, at function or block
  scope, int or unsigned: 552 B, worse.
- operand order: `i[ field ]`, `*( i + field )`, `i[ pValue ]`, `*( pValue + i )`, and three
  iDelta commutations (80 variants). cl canonicalises them all to identical code.
  Note: d0_e's `[ebx+esi]` vs retail's `[esi+ebp]` is no independent clue; ebp cannot be a SIB
  base without a displacement.
- types: pValue as `char *` / `signed char *`. The parameters are free because the name is a
  placeholder: field `const char` / `const unsigned char` / `char` / `unsigned char` pointer,
  buffer `char *`, size unsigned (16 variants). All give identical code.
- control flow: one common `pValue = pTail` at the join (break + goto, 3 forms) merges the
  duplicated append blocks (486/502 B). Retail keeps the donor's per-branch assignments.

Next leads:
1. A VC 7.0 c2 (cl 13.00), which no profile in the tree provides. An older register
   allocator could explain the tie that every VC 7.1 build reproduces.
