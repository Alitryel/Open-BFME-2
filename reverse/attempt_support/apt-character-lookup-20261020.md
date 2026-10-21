# Character lookup: owned contracts and bounded source controls

Target `Rva006EFBC0ObjectMemberLookup`, independently named by WB1784910 as
`AptCharacterInst::objectMemberLookup`. Read the complete 603-line bank, all
RVA-specific log entries, the earlier Astra evidence JSON and complete native/
WB disassemblies before trials. Input revision: BFME2
`f49f5687dcd0233c1a9c9423e5254f7bc1a22715`, BFME1
`b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b`, stock VC7.1, bank O2/NDEBUG/MD/EHsc.

## Boundary and measurement correction

The executable native body is 5501 bytes, ending at exclusive6F113D. Three
alignment bytes precede dispatch tables at6F1140: 84 bytes,16 bytes,204 bytes
and127 bytes, ending at exclusive6F12EF. Full code/alignment/table extent is
5935 bytes. The CC at6F12EF is padding before the separately owned22-byte
sized-delete helper at6F12F0. Earlier5936-byte comparisons included that CC.

`align_diff.py` searches for four consecutive CC bytes near its size hint.
Here it skips the one-byte pad and next helper and reports5958. Its old full
instruction counts also decode dispatch-table bytes as instructions. Do not
treat those counts as an exact function comparison. The retained scratch
metrics find the first table from contiguous DIR32 code-label relocations and
compare only executable code plus alignment, excluding relocation-backed
operands from the defect counts. Native code/alignment ends at+5504.

## Contract repair retained in the bank

Replace nine provisional callback declarations/addresses with the current
verified owners: GetBounds6EC730, LocalToGlobal6ECCB0, AttachMovie6ED580,
CreateTextField6ED810, SwapDepths6EDBD0, CreateEmptyMovieClip6EDFF0,
ApplyTextFormat6EF570, TextFormat6EF6D0 and TextFormat6EF920. Their complete
current rows establish the pointer-returning cdecl context/count ABI. These
are existing owner spellings and physical bindings; historical misnomers such
as Rva006EDF20SwapDepths are not new semantic claims about that callback.

Use the rowed int-returning rva006E02B0 and isCharacterInst contracts with
retail's low-byte tests. Use the real Rva006DBB30SarDwordField getter and
BfmeAptValue checked-cast/isCIH/isUndefined owners instead of old private alias
spellings. The inline checked-cast adapter forwards directly to the already
verified57-byte provider; no new pin or forwarding row is added.

The primary bank still emits5915 bytes. Machine shape is unchanged, but its
one unresolved REL32 is gone and callback ownership is explicit. Under the
same legacy diagnostic fitness, baseline is0.7892895857 and the retained
canonical-cast body is0.7895675820. This is binding/readiness progress, not a
new exact match. Main register and float cross-jump differences remain.

## Controls and useful alternative

There were34 caller compilations: owner/ABI controls, complete barrier removal,
inline character accessor, fourteen direct numeric-return cases, direct float
expressions, real checked-cast visibility, G6/G7 sibling settings, the true
static method identity, typed instance pointer, the existing float provider's
class view/body, real predicate inlining, debug-break intrinsic, common virtual
prefix view and GC-root setter visibility. An early Ob1-before-O2 control is
not relied upon; an explicit trailing Ob1 control was also run.

The visible providers independently remain exact: checked cast57 bytes,
predicate75, GC-root setter73 and float factory263. None repairs the parent.
These facts do not prove the copied class views' complete ABI or vtable data.
The ordinary/inline predicate reproduces the manually expanded shape; forcing
both calls inline gives5931 bytes and does not fix the register roles.

Removing all three inherited compiler barriers and the redundant scroll
conditional gives6331 bytes. Direct numeric returns/expressions give6287/6223,
with more genuine structural differences. G6 is unchanged; G7 regresses.
The source without the redundant conditional and with intrinsic debug breaks
is a useful5891-byte alternative: code-only structural regions40->37, memory
defects120->51, register defects102->76. Raw-code diagnostic fitness improves
0.59598->0.67606, while the old mixed code/table patched metric drops to0.78116.
Keep it alongside the stronger primary bank rather than silently replacing
the score/metric. It still has three inherited barriers and is diagnostic.
The primary bank also retains its inherited barriers/conditional: neither
candidate is ready to land as production C++.

The read-only AptValue contract sample reports sizeof4 by majority with no
retail field witness, and queues virtual slots2/3 (ForceDelete versus unnamed
slots; GetNativeHashVirtual versus unnamed slot3). Native base/CIH/float
vtable prefixes and existing constructor views do not justify adopting a
complete header from that sample. No header or class registry was written.
Resolve these contracts from independent evidence before a scope-wide change.

Both the typed-unit placement rescan and the already owned post-table helper
yield no additional recovery. No Code, ledger, pin, verifier or baseline edit
is made by this investigation. About25 minutes, gpt-6.1-sol.

Replay the retained `.py.txt` driver from build/ with phases `contracts`,
`returns`, `cast`, `flags`, `identity`, `float`, `predicate`, `shared` in order.
It freezes its seed/provider source at the input revision above. The metrics
driver operates on their normally compiled objects. Summary comparisons, the
unresolved contract output and the useful alternative are retained here;
all trial sources/full diagnostics remain in build/apt-character-contracts-oct20/.

## Round 2026-10-20 (claude-opus-5-5, ~90 min)

Bank unchanged (0.78957, nd 504, 5484B code); `nb` = bank without the three
barriers/scroll ternary scores 0.72249. Retail tail sharing mapped (function
offsets): case17 `jne 0x1c9` into case8's undefined block; case18 loads
`[esi+0xc]->+0x30` and jumps to case10's `test esi,0xffffff` at 0x229; case21
pushes `(mouseWheel>>3)&0xffffff01` and jumps to case10's `call AptBoolean` at
0x233; case19 jumps to case20's `fst [esp+0x10]` at 0x45e; case20 and every
switch-2 numeric case end `call MakeFloat; jmp 0x238` (case10's `add esp,4` +
epilogue), number homed at [esp+0x10]; switch-2 rect clamp `jp 0x931` reaches a
shared `mov edx,[esp+0x10]; push edx; call MakeFloat; jmp 0x238`. Retail has 53
rets, nb 69.

Disproven this round (all scored with the variant_search Scorer):
- function-scope `number` in cases 19/20 (identical bytes), ternary clamp,
  if-wrapped second half, inline `isText(lookupCheckedCIH(...))` without the
  `initial` local (identical, already noted earlier);
- compilers vc71-sp1 / vc71-ddk-4035 (identical to RTM);
- flags /Ox, /Og /Oi /Ot /Oy (+/Ob1, /Ob2, /Gy), /O2 /Ob1, /O2 /Og- (0.327),
  /Og /Os (0.254), /O1, /Os: all worse;
- `/O2 /Op` scores 0.80780 (nd 349) and gives retail's register roles
  (context=edi, cih/text=esi) but wrong float shapes (fstp/fld instead of fst,
  number enregistered in esi in switch 2, constant-propagated `xor eax,eax;
  push eax` instead of `mov [esp+0x10],0; mov ecx,[esp+0x10]; push ecx`).
  Diagnostic only: the esi/edi coloring follows the float/number web, so fix
  the number's lifetime/homing first and the role swap may follow.
- Synthetic TUs (build-local): VC7.1 lays out blocks in source order; identical
  whole return blocks merge keeping the LATER copy (retail keeps the earlier for
  8/17, 10/18, 10/21); a shorter tail can jump into an earlier longer block; no
  cross-callee `add esp,4`+epilogue sharing reproduced; no duplication budget.

Open: what source makes every float return funnel through one
`push; call MakeFloat; jmp epilogue` (a single `return MakeFloat(number)` after
the switch with `break`s, a homed `number` that is address-exposed, or a
`goto`-style shared exit) while keeping per-case epilogues for the
integer/boolean returns.

Merge-direction probes (synthetic TUs, VC7.1 /O2): a case-17-shaped
`if(!s.IsEmpty()) return str; return undef;` next to an earlier
`return undef;` case always keeps the LATER undef copy, whatever the spelling:
if/else, inverted test, ternary either way, result variable, an inline
`getUndef()` on either side, or moving the string case before the undef case in
source (layout then follows source order). The bank does the same; retail keeps
case 8's earlier copy. Partial tails do jump back into earlier blocks
(`test; jne <earlier push/call/epilogue>`), and retail's 19->20 `fst` merge
keeps the later block. Retail case 18 loads wordWrap into ESI and jumps to case
10's `test esi,0xffffff`: the merged value lives in a callee-saved register
across the jump, so that merge happened before register allocation, while the
bank keeps the `test [mem],0xffffff` form and never merges. The Rich header
rules out /GL or another compiler build (docs/recipes.md). A next seat should
look for a source form whose IR already shares these tails: shared locals
assigned per case with one `AptBoolean::Create(v)`/`MakeFloat(number)` return,
or a helper inlined in several cases.

## Round claudeb2 2026-10-20 (production direction, base4)

Best production-direction body: `apt-character-lookup-20261020-base4.cpp.txt`
(it has no `_ReadWriteBarrier` or equal-arm hacks; align sum 239: st=25 ins=32
del=203 mem=3 reg=1, size 5872 vs retail 5935 with tables; fitness 0.7208,
below the 0.7896 bank, which is therefore kept). Shape: switch 1 returns per
case (`case 10: return AptBoolean::Create((text->definition->multiline&0xFFFFFF)!=0);`,
18 the same with wordWrap, 19/20 `Rect r; ... float n=r.bottom-r.top; if(n<0)n=0;
return MakeFloat(n);`, 21 `return AptBoolean::Create(text->mouseWheel);`);
switch 2 assigns `number` and `break`s, factory cases return globals,
`default: return 0;`, then `return MakeFloat(number);`. Helpers `refreshText`
and `makeLookupString` are `__forceinline`.

Retail switch-1 table (cases 1..21, offsets from 0x6EFBC0): 0xb3 0xfd 0x124
0x149 0x170 0x498(default) 0x194 0x1c9 0x1e1 0x223 0x24e 0x290 0x2c9 0x2ee 0x330
0x372 0x39a 0x3d1 0x3dc 0x41e 0x486. Cases 2,3,4,5,7,9,10,11,13,14,15 own their
`add esp,4`+epilogue copy (EXIT4); 1,8,12,16,17 return objects/globals with own
epilogues. Every merge comes from a block after case 17: 17->8 (`jne 0x1c9`),
18->0x229 (case 10's `test esi,0xffffff`), 19->20's `fst` at 0x45e,
20->0x238, 21->0x233, and switch-2's MakeFloat return ->0x238. Retail has
53 `ret`s, base4 74. EH state stores and epilogue interleaving already match.

Disproved this round (do not repeat):
- w2..w7 WB-shape factors (bool locals, ternary clamps, `shr 3; and 1` bitfield
  reads, case order) and w9 (64 spellings of cases 10/18): all stay at sum 239.
- w8 (768 variants): T1 (the 18->10 merge) only appears with bool locals for
  B10+B18 plus one helper, and costs an edi/register shift (sum 308).
- z1: deleting all 27 factory cases leaves tails unmerged (A0 T0): function
  size or a duplication budget is not the cutoff.
- k6: EH-object fillers shift scratch-register rotation like extra calls but
  do not block merges; identical I-cases (`and; push; call; add esp,4`) never
  merge in probes, whereas bool cases (block starting at `test`) do.
- Hidden temp: retail's `mov esi,[eax+0x2c]; test esi,0xffffff` means the
  value was in a register when the tails merged, before the peephole folded
  `test [mem],imm`; base4 folds first and so never merges.

Lead for the next seat (evidence-backed, untested on this body): matched
siblings share `add esp,4` ACROSS different callees at a result-variable join.
`_FunctionAptActionIncrement` 0x703F40
(`Code/Libraries/Source/Apt/AptActionInterpreterConstantHandlers.cpp`:
`if(isInteger) result=AptInteger::Create(..); else result=MakeFloat(..);`)
compiles to `call Create; jmp J` / `call MakeFloat` / `J: add esp,4; mov ebx,eax`.
GameSpy `ProcessAdHocData` 0x6A9920 (`sb_serverlist.c`, `ret = ProcessX(..);
break;` per case) shows the same: two cdecl calls `jmp 0xef` to one
`add esp,4; mov ebx,eax`. Retail's EXIT4 (0x238, `add esp,4` + epilogue)
receives exactly the late cases and switch 2's MakeFloat, so try: switch-1
cases 18..21 (and maybe 17), plus the switch-2 MakeFloat, assigning one
`AptValue *result` and `break`ing to a shared `return result;`, while cases
2..15 keep direct `return`s. Factorial: which cases join (17/18/19/20/21
each), whether switch 2 joins, result declared at function vs block scope.
Tools used (untracked, recreate): align sum via `tools/align_diff.py`, jump
table decode via `read_target_bytes(0x6EFBC0,5935)`.

## Round claudeb2 2026-10-20 (late): result-join, new best L0011

Best body: `reverse/attempts/0x006efbc0.cpp` (L0011), banked as the
attempt. Fitness 0.79096 (structural, 5879 compiled), align sum 112
(st=29 ins=51 del=50 mem=10 reg=1), native 5448 B, 55 rets (retail 53,
base4 74). The diff against base4 is three edits:
- `AptValue *result;` declared after `float number;` at function scope;
- case 10 is `result=AptBoolean::Create(..multiline..);` then a label
  `done: return result;` inside case 10;
- case 21 is `{result=AptBoolean::Create(text->mouseWheel);goto done;}` and the
  switch-2 final is `result=Rva008A4EA0MakeFloat(number); goto done;`.

What the compiler does with it: the done block merges into case 20's identical
`push; call MakeFloat; add esp,4; epilogue` tail, keeping the LATER copy (case
20), so J sits after case 20. Case 21 jumps to J, and the switch-2 copies jump
into case 20's `call MakeFloat`. Retail keeps J after case 10's
`call AptBoolean::Create` (0x233/0x238):
- 18 shares 10's `test esi,0xffffff` (jmp 0x229);
- 21 does `push edx; jmp 0x233`;
- 19 jumps into 20's `fst`;
- 20 and each switch-2 copy keep their own `call MakeFloat; jmp 0x238`.

Remaining L0011 differences: J at 20 instead of 10, 21 and switch 2 enter
20's call, there is no 18->10 test merge, and gUndef is kept at 17 rather than
8.

Disproved this round (e8/e9/e10, 300+ variants, do not repeat):
- the label in case 21, or at function end, with two or more gotos collapses
  back to base4 (sum 239). A join with two or more predecessors is
  re-duplicated into direct returns;
- gotos from 19 and/or 20 destroy every merge (75 rets);
- a goto from 18 has no effect; the label in 18 behaves like the label in 10;
- 19/20 writing `number` instead of a block-local `n` has no effect;
- the compiler flags of the matched Apt siblings (AptCharacterByteCounts,
  ApplyTextFormat, TextFormat) are all `/O2 /DNDEBUG /MD /EHsc`, with no /EHa or /GX.

WB twin facts (0x1784910, debug):
- direct returns everywhere (gUndef is `mov eax,[gUndef]; jmp exit`);
- case 17 is `if(!variable.IsEmpty()){s=Create(); s->str=variable; return s;}
  return gUndef;`;
- case 20 clamps through a ternary temp;
- case 21 is `shr 3; and 1`;
- the default of switch 2 is `return 0`.

The source probably had no gotos; the join is the optimiser's. The result+goto
form is still a useful lever, because it is the only one that moved J.

Next leads (untested):
1. done label in a case before 10 (9, 8), so the merge keeps a later case
   tail and the J copy could land in 10;
2. L0011 plus c10-style single gotos (c10 keeps J at 10 and cross-jumps
   11/13/14/15 into it, plus 18->10 with retail's `mov esi` form);
3. case 17 as `if(IsEmpty()) return gUndef; return makeLookupString(..);`
   inside the full TU (the earlier probes used synthetic TUs only).

## Round claudeb2 e11-e15 (2026-10-20, claude-opus-5-5): merge mechanism

Best is still L0011 (fitness 0.79096, align sum 112), banked in 684db5cf09.
Lead 3 tested: case 17 inverted inside the full TU gives +1 (worse).
Leads 1 and 2 are now explained by the mechanism below; neither as written
reaches retail's merge set.

Disproved (do not repeat):
- e11: the declaration order of `word`/`number`/`result` has no effect;
- e12: `makeLookupString` inline vs a string literal has no effect;
- e13: the WB shape `if(word){switch..} return 0;` crossed with label
  position and goto sets gives 112 at best (= L0011);
- e14: reordering cases 11-15 has no effect; moving 18-21 directly after 10
  kills every merge (see rotation below).

Mechanism findings (target codegen facts, not source facts):
- The case-tail merges are post-register-allocation cross-jumps that run
  before the peephole that folds `mov r,[m]; test r,imm` into `test [m],imm`.
  They need identical registers. 18 merges into 10's
  `mov esi,[eax+0x2c]; test esi,0xffffff; setne cl; push ecx` only when
  18's scratch registers equal 10's. Without the merge, 18 shows the
  `[ecx+0x30]/setne dl` or `[edx+0x30]/setne al` form and the load folds.
- The scratch registers rotate eax/ecx/edx mod 3 over the cases. In the e14
  power-set over 11/13/14/15/18 as knockouts, the merge happens exactly when
  (refresh cases kept among 11/14/15 + 2*[13 kept]) mod 3 == 2. Filler cases
  can realign the rotation.
- Direction: with plain returns, the identical tail keeps the LATER copy
  (10 jumps into 18). With 10 doing `goto done` and `done: return result;`
  at the function end (c10, `build`-local e5/c10.cpp), the EARLIER copy (10)
  is kept, as in retail.
- POP merges (`add esp,4` tails of 11/13/14/15 into 10) in c10 are
  all-or-nothing. They need the 18->10 T-merge seed and enough switch-2
  cases: with 13 or fewer non-factory switch-2 cases only the T-merge occurs,
  with 14 or more (any 14; dropping any single one of the 23 keeps them) the
  full merge occurs. Switch-1 cases 1-9, 12, 16, 17 and 19-21 are irrelevant
  while the rotation stays aligned.
- In c10 the POP-merged set is exactly the add-esp-4 cases strictly between
  the kept block (10) and the T-partner (18). In retail it is 18 and after
  (19/20, 21, the switch-2 MakeFloat copies and the clamp), with J at 10.
- Small synthetic probes (q15) reproduce the T-merge only when the rotation
  aligns. They never reproduced POP merges, not even with 24 extra
  non-candidate switch-2 returns, so the threshold depends on the
  switch-2 candidate tails rather than a raw case count.

Next leads:
1. find a source where the T-partner of 10 brackets 18..end. The POP window
   seems to run from the kept block to the T-partner, so the partner should
   be the last candidate (switch-2 MakeFloat/clamp tail), with 18 aligned by
   rotation;
2. L0011 plus fillers or reordering to realign 18's registers with 10
   (L0011 lost the 18->10 T-merge);
3. tell apart a case-count threshold from a tail-size one at Z13->Z14:
   pad one Z13 case, or swap the 14th case.

## Round 2026-10-21 (claude-opus-5-5, t=70)

Ran alongside claudeb2's rounds above, measured against the older 0.7896
bank; the best body is still their L0011 (0.79096). Local scorer numbers
below use the `sc.py` metric (old bank = 0.7846 on it).

Retail exit structure, offsets from 0x6EFBC0:

- `EXIT4` at 0x238 is the only non-duplicated `add esp,4` + EH epilogue. Case
  10 (0x223: `mov eax,[esi+0xc]; mov esi,[eax+0x2c]; test esi,0xffffff;
  setne cl; push ecx; call AptBoolean::Create`) falls into it.
- Case 18 (0x3d1) loads `[eax+0x30]` and does `jmp 0x229`, landing on case 10's
  `test esi,0xffffff`. Case 21 (0x486: `mov edx,[esi+0x74]; shr edx,3;
  and edx,0xffffff01; push edx`) does `jmp 0x233`, landing on case 10's
  `call Create`. That is classic post-RA cross-jumping against the fall-through
  predecessor, not IR tail merging.
- Cases 19 and 20 share 20's `fst [esp+0x10]` (19 does `jmp 0x45e`), clamp
  through `number`'s slot [esp+0x10], then `push ecx; call MakeFloat;
  jmp 0x238`.
- Every numeric case of switch 2 (0x529..0x674) does `jmp 0x238` after its own
  `mov edx,[esp+0x10]; push edx; mov [esp+0x14],edx; call MakeFloat`. The
  push/call was tail-duplicated into each case after RA, with store forwarding.
- Cases 2..7 and 8 each keep their own full epilogue.

Whole-binary scan (`call; jmp T`, where T is `add esp,4`, a call precedes T and
a ret follows within 26 bytes): 0x6EFBC0 is the ONLY function with it. The
other hits are if/else joins followed by more code: Apt Add 0x700720,
Subtract 0x700880, Multiply 0x7009E0, ToNumber 0x703730, Increment 0x703F40,
Decrement 0x704020, ProcessAdHocData 0x6A9920, End_Scene 0x122BE0,
Lua 0x754780/0x74A9B0, GameSpy 0x699F20/0x6A52C0/0x6B2970. So no matched
sibling demonstrates the source shape.

Disproven this round (none produces EXIT4; our cl duplicates the epilogue into
every return site, joins included):

- base4: helpers `refreshText`/`lookupCheckedCIH` spelled inline at each site:
  0.7323, worse.
- v1: cases 10/18/21 assign `AptValue *result` and `goto done` to one
  `return result;`: 0.7780.
- t1: v1 plus cases 19/20 join the same `result`: 0.7764.
- t2: 19/20/21 plus switch 2 funnel through `number` and one
  `return MakeFloat(number)`: 0.7182.
- Synthetic probes p1..p6 (a 13-case model with an EAStringC EH local): goto
  joins, ternary returns, a shared int local (copy-propagated away), and a
  24-bit bitfield view of multiline/wordWrap (`common2.h`: still emits
  `test dword ptr [mem],imm` and no esi load). Every one duplicates the
  epilogue. The IR tail merge of identical long tails keeps the LATER copy
  (19→20 `fst` reproduces); case 18→10 and 21→10 never merge.

Still untried, ranked:

1. J content removed after the epilogue-duplication decision, e.g. an EH
   state store or a dead store at the shared join that a late pass drops.
   Look for a scoped EH object or a `volatile`-free dead local whose last use
   is the join.
2. Float homing of `number` through an address-exposed use, which might keep
   `number` in [esp+0x10] the way retail does. An `/Op`-scoped
   `#pragma optimize` is an escape hatch: measure it only as a diagnostic.

Untracked tools (recreate): `build/scratch/apt/scan_exit4.py` (scan above),
`build/scratch/probe/probe.py file.cpp f` (compile + disassemble one symbol).

## Round h1 (2026-10-21, claude-opus-5-5, ~25 min, bank unchanged at 0.79096)

30 variants (scratch build/apt/genh1.py, h1/): shared `bool b`/`int v`
return labels for cases 10/18/21, `number` with `goto retNum` to one
`return MakeFloat(number)`, a final `return MakeFloat` after the switch, and
function-scope versus case-scope declarations. Best 0.78046 (rets 73 vs bank
55): every IR join with two or more predecessors is re-duplicated before RA,
so no join spelling reproduces EXIT4. Retail's case 10 loads multiline into
esi (`mov esi,[eax+0x2c]; test esi,0xffffff`), a callee-saved register for a
single use, which hints the value was a variable live across a merged edge.
Untried items 1 and 2 above remain open.
