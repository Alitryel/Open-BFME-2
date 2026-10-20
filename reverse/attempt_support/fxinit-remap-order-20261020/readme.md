# 0x0018C84E FXShaderGeometry::Init: two-bone remap load order (2026-10-20)

The bank `reverse/attempts/0x0018c84e.cpp` is unchanged at 0.996142 bytes
(permute fit 0.9964). Its build and landing notes are in
`../fxinit-wbinline-20261020/readme.md`.

## Residue

The residue is 7 lines at retail +0x707..+0x71e, in the `m_BonesPerVertex==2`
arm of the vertex loop. P at [ebp-0x2c] is the strength-reduced pointer to
`links[0][i]`. D at [ebp-0x8c] is `links[1] - links[0]`, and the weight
bases are differences from P in the same way. B at [ebp-0x58] is `remap`'s
begin. L0 and L1 are the link words.

    retail: mov ecx,D; mov eax,P; movzx edx,[ecx+eax]; movzx eax,[eax]
            mov ecx,B; movsx eax,[ecx+eax*2] (R0); movsx edx,[ecx+edx*2] (R1)
    bank:   mov eax,D; mov ecx,P; movzx edx,[eax+ecx]; movzx ecx,[ecx]
            mov eax,B; movsx edx,[eax+edx*2] (R1); movsx eax,[eax+ecx*2] (R0)

## Mechanism (inferred, not proven)

A backward register-allocation model reproduces both outputs exactly. R0 must
end in eax, because the following `mov ecx,[ebp-0x94]` is hoisted above the
add.

- If the basic block holds R0 before R1, the result is retail's registers.
- If R1 comes first, the result is the bank's.

So the whole residue is the order of the two remap loads inside the block.
The SIB operand order (`[D+P]` vs `[P+D]`) is a separate axis: it follows the
global IL temp count, as the wbinline handoff found, and it is already right
in the bank.

The diagnostics below run on a body without the P and N stores in the arm
(noPN), which flips the block to retail's order. Adding back one statement
after W:

- **Keeps retail's order:** an unconditional constant store (c0); a plain
  pointer store.
- **Brings back the bank's order:** a conditional store; any store that loads
  through the loop IVs (positions, normals, tangents, a float, an int).

The order therefore depends on what follows W in the same block. No faithful
spelling of the P and N stores has been found that keeps R0 first.

## Disproven this session (do not repeat)

- **Control flow.**
  - P and N made unconditional, each alone and together.
  - An `m_FVF` condition on P and N.
  - 1–12 branchy throwaways after the loop.
  - Single-statement deletions in the arm: only deleting P and N together
    flips the block.
- **Variable lifetime.**
  - 62 staged link/remap locals: best 0.9914.
  - Address-first destination: 0.971.
  - 0–63 throwaways at the end of the function: block unchanged at every count.
- **Types and spelling.**
  - 11 P/N spellings: AP, NP, Pne, Pptr, Pref, Psrc, Pmem, Pblk, Pnest,
    WAPN_off, Pidx. Each gives the bank pattern.
  - 11 W spellings: a named temp, `*0.01f`, float casts, ref/ptr member
    stores, a float array, locals, double. All give the bank pattern, and five
    are byte-identical to it.
  - `begin()[]`, casts, `*(p+i)`, and a `|` mask instead of `+`.
- **Vector3 copy.** `operator=` through `operator[]`, or with a copy
  constructor added: byte-identical to the bank. A temp copy (0.905), reversed
  member order (0.967) and the implicit `operator=` (0.597): worse.
- **Callee visibility.** Three inline pack helpers (high/low int arguments in
  both orders, and short arguments): no change.
- **Compiler settings.**
  - /G5, /G6, /GB: block unchanged.
  - `permute --flags`: 9 trials, inert.
- **Random search.** permute: 1634 trials, no gain.

Earlier seats' disproven lists are in `../fxinit-r46-20261020` and
`../fxinit-wbinline-20261020`.

## Open question

Under a critical-path heuristic R1 (load, shl, add) should go first, which is
the bank's order. Retail puts R0 first anyway, so retail's source or IL gives
the scheduler a different tie-break. No spelling of the arm reproduces that
tie-break yet. The WB twin's accessor shapes were already tried by an earlier
seat.

Scratch, untracked: `build/c18c84e/`. `mini.py` scores files and writes
`.dis`; `t5`–`t12` hold the sweeps.

Model: claude-opus-5.5.
