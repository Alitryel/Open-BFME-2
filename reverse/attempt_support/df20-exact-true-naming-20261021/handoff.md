# 0xDF20 money_put::do_put (wide): byte-exact under the true string-dtor naming

Session 2026-10-21, model=claude-opus-5-5, seat claudeb3.

## Result
`reverse/attempts/0x0000df20.cpp` (new bank) compiles to retail's 2610 B with
frame 0x118 and every relocation identical **under the true naming**
W<G> = `~basic_string<G>` = 0xB3C0, S<G> = `~_String_base<G>` = 0x142D70
(evidence: `df20-funclet-naming-20261021/handoff.md`, re-confirmed from DF20's
own unwind map, funcinfo 0x8FD718, handler 0x75BCA7: complete-object states
call 0xB3C0, base-only state 21 calls 0x142D70). Under the current ledger
naming the nine destructor relocations are all swapped (fit 0.9937), so the
row cannot land until the ledger reconciliation in that handoff is done.
The previous bank (0.9993 ledger naming, residue at 0x28c) is kept as
`prev-bank-ledger-0.9993.cpp.txt`.

## What made it exact
Base `ex_n6_k9_s0` from `df20-late-fold-unroll-20261021` (bank plus a W<G>
specialisation with six `if (this == 0) exit(1);` before `_Destroy`, no sign
pragmas; its call map was already retail's, but the late fold rolled the
space-count loop: 0.8652). Replacing the loop with two halfword reads

    unsigned short __lo = ((unsigned short*)&__format)[0], __hi = ((unsigned short*)&__format)[1];
    if ((char)__lo == space) ++__length; if ((char)(__lo>>8) == space) ++__length;
    if ((char)__hi == space) ++__length; if ((char)(__hi>>8) == space) ++__length;

reproduces retail's scalar form even with the late fold present.
Generator: `u4gen.py.txt` (six loop forms x {a9, ex}). Other forms on ex:
dword+`>>=16` 0.9307, union 0.9307, 2-iteration loop 0.7985, shift loop 0.9021.
On a9 the halfword form stays 0.9986 (the map, not the loop, is a9's residue).

## Remaining work: landing
Follow the repair plan in `df20-funclet-naming-20261021/handoff.md` (owner TU
respelled to emit W<G> at 0xB3C0, W<G>@0x142D70 twin deleted, S<G> fold pin at
0x142D70, callers respelled). Its measured link impact (10 units, 19.3 KB
unlinked because their header views emit a 14 B W<G> COMDAT) is the open cost.
