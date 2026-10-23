# Renderer 0x00177F82, wave 2 (2026-10-20, claude-opus-5-5)

Bank: `reverse/attempts/0x00177f82.cpp`, which is the w1 bank plus two source changes:

- `int current=0;` now follows the `defaultDiffuse` conversion. Retail homes the receiver at `[ebp-0x50]`, and ours now does too.
- The diffuse and normals branches each compute `out=vb+...Offset()` inside their own `if` and `else` arms, and each arm has its own `input`. The arm structure now matches retail.

Measured with `permute.fitness`: the w1 bank scored 0.8879, emitted 3781 B and had 214 normalised diff lines. The new bank scores 0.9024, emits 3780 B and has 198 lines. "Normalised diff" means objdump lines with immediates of 5 or more hex digits masked and jump/call targets masked.

## What is still wrong (retail versus ours)

1. **`push edi` is shrink-wrapped.**
   - Retail saves EDI in the entry block (`cmp [esi+10h],ebx; push edi; mov [ebp-50h],esi; je`). Retail's epilogue is `mov ecx,[ebp-0Ch]; pop edi; pop esi; mov fs:0,ecx; pop ebx; leave`.
   - Ours pushes EDI at +0x384. That is the first block holding an EDI use; the material `mov edi,eax` is at +0x4C1.
   - Calls do not end blocks, so the push lands at the join after the two inline transform diamonds (`je 0xe5/jmp 0x1ed`, `je 0x27d/jmp 0x37d`).
   - Retail has the same control flow: the only jumps to the epilogue are the entry `je`, the same `jl 0x72c` back edge and the same inner `jne` loops. The EH FuncInfo is also the same (1 unwind state, no try blocks).
   - With `/Ot`, `/O2` or `/Ox`, EDI goes to the entry block, but the body grows to 3938+ B and gets a different prologue. `/Oi`, `/Oy-`, `/Ob1` and `/G6` leave the push late.
   - The cause is still unknown. The BFME 1 analogue 0x90FEE0 shows the same residue and is also unsolved.
2. **MIN codegen.**
   - Retail: `cmp eax,ecx; jge L; mov esi,eax; mov [ebp-54h],esi; jmp M; L: mov [ebp-54h],ecx; mov esi,ecx`, so delta is register-primary.
   - Ours: `mov [ebp-54h],eax; jl; mov [ebp-54h],ecx; mov edi,[ebp-54h]`.
   - These forms are identical to e3: the explicit `if`/`else`, and `template<class T> T TMin(T,T)` taking values.
   - `const T& TMinR` scored 0.865.
   - The clamp form `delta=count-current; if(delta>512) delta=512;` scores 0.913 by permute fitness, only because its length is 3781. It moves the receiver home to -0x54 and the stride home to -0x30, so it is not closer.
3. **Loop register coloring.**
   - Retail: ebx=this (reloaded at +0x70A), edx=fvf, ecx=vb, edi=out, eax=current*0x30, esi=n=delta*4.
   - Ours: esi=fvf, eax=vb, ecx=current*0x30, edi=n, edx=out.
   - The CSE spill slots around the asm loop are swapped. Retail has n at -0x120 and current*0x30 at -0x118; ours has the reverse.
4. **Loop guards.** The diffuse and normal loop guards are `jbe` in ours and `je` in retail. Changing these guards to `!=` was rejected in w1 (H7/H8): it regresses the alignment classes.
5. **Store order.** In the inline `Set_Transform(WORLD, identity)`, one store is swapped: retail stores `[0xDEE7CC]` before `mov [0xDEC4F4],eax`.

## Trials this wave (all in build/w177, untracked)

| trial | change | fit |
| --- | --- | ---: |
| v1 | drop the `volatile` input | worse |
| e1 | `if(count){...}` instead of the early return | identical |
| e2 | move `current` only | 0.89 |
| e3 | per-branch out/input (banked) | 0.9024 |
| e4-e8 | ordinary fvf getters, `!=` guards, volatile removals | worse |
| e9 | input passed as `const Vector3*&` to an inline copy helper (address-taken theory for the memory-resident input) | 0.782 (input gets promoted) |
| m1-m4 | MIN spellings (see 2) | 0.9024 / 0.9024 / 0.913* / 0.865 |
| va/vb | truncated bodies to probe the shrink-wrap rule | push goes to the nearest dominator block of the first use |
| flags | `/Ot /O2 /Ox /Oi /Oy- /Ob1 /G6` (see 1) | none matches |

Independent explanations tried:
- control flow: if-wrap, MIN forms, branch arms.
- variable lifetime: `current` placement, per-branch cursors.
- types and layout: getter volatility, address-taken input.
- callee visibility: template min, reference helpers.
- compiler settings: the flag sweep above.

Untried leads:
- the real `dx8wrapper.h` `Convert_Color_Clamp`/`Clamp_Color` inlines in place of the bank's forceinline helpers;
- a ZH-style index loop (`for(i=current;i<current+delta;i++)`, `vb+=stride`) for the positions copy;
- a named `n=delta*4` declared before the inputs, to test the CSE slot order.

## Shrink-wrap probes (synthetic, MSVC 7.1 `/O1 /G7 /arch:SSE /EHsc`)

These were synthetic `T::run` bodies with an entry `if(cnt==0)return;`, a loop holding a dtor'd local and late callee-saved uses (`build/w177/sw/`, untracked).

The push sinks to the dominator of the register's uses unless the function contains one of these. Each one keeps every save in the entry block:
- try/catch;
- `_alloca`;
- `setjmp`;
- inline asm holding `push`/`pop`, `pushfd`/`popfd` or `call`;
- a by-value class argument copy-constructed into the outgoing area of an out-of-line call (tell: `mov ecx,esp` and `mov [ebp-x],esp`).

Every disabler leaves a byte tell, and retail 0x177F82 has none: no `,esp` copies and no asm push or call.

These leave the push sunk:
- asm `sub`/`add esp` or `nop`;
- asm touching a named local, `ebp`, or `[esp-4]` with `fldcw`;
- `_ReadWriteBarrier`;
- volatile or address-taken locals;
- dead asm, `throw` and static locals;
- copying `this`/count at entry;
- every early-exit spelling (`if(cnt){...}`, `<=0`, `!cnt`, goto);
- `__forceinline` by-value helpers;
- body size up to 800 statements.

A plain `inline` by-value `ConvertPointColor`/`ConvertDefaultPointColor` in e3 is not inlined (0.65/0.63/0.54), so it is no lever.

The 757 matched bodies whose saves sit before an early `je` are mostly multi-exit bodies. Two examples: 0x33541C `ObjectCreateAndFireTempWeapon` and 0x3B1244 `canUseSpecialPower`. In both, a later exit (taken after the late register's first use) shares the early exit's tail block, so no single restore point exists.

0x177F82 has one exit edge into 0xEB4, plus the fallthrough, so that explanation does not apply here. Two hypotheses remain open:
- A use of the late register in some exit path that the source has and the bank lacks.
- Save placement decided on a preliminary allocation, before the loop recoloring (retail has 119 EDI references, ours 97). If so, fixing residue 3 may move the push by itself.

`tools/permute.py 0x00177f82 --minutes 30 --jobs 6` from the bank ran 1810 trials and reached 0.9025 at best (from 0.9024), so there is no ordering/naming close.

Once 0x177F82 lands, 0x560B11 (blocked-on 0x00177F82, bank 0.967) and 0x5601D9 can proceed.
