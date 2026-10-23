# Drawable shroud join review, October 22

Continue `?onComingOutOfShroud@Drawable@@AAEXXZ`, RVA 0x0027893E, 747 B.
The standing amoeba assignment landed before this session; this was the only
unfinished task resumed. Start/end bank is
`reverse/attempts/0x0027893e.cpp`, score 0.995, unchanged. No new match, Code
edit, pin, alias, compiler setting, verifier change or reference update is claimed.

## Current residue, independently reproduced

A fresh ordinary `explain_mismatch.py` build with `BFME_OBJSTORE=off` emits
748 B against 747 B. Full raw-symbol disassembly has 220 instructions on both
sides. Compare instructions after masking their actual COFF relocation sites
and checking that each conditional jump reaches the same instruction index:
there is exactly one difference, at instruction 201 / +0x2BA:

```
retail: mov ecx, edx
bank:   mov ecx, dword ptr [ebp-0x10]
```

Both predecessors have loaded the Object into EDX for the private-status byte
test. The rest of the instructions, including registers and frame offsets,
agree. The first positional difference at +0x35 is a consequence of the extra
byte. `compile_function()['bytes']` truncates to the row size: use the full
`locate.object_functions` body for size and disassembly, as before. Do not raise
the real extent or mistake the shifted relocation diagnostics for new defects.

## New evidence

1. **A static free-function nearest helper is byte-exact.** WB CA4030's explicit
   Object argument suggested testing a genuinely internal C++ function, instead
   of another external calling-convention declaration. Copying the existing
   214 B provider into this unit as
   `static Object *nearestInView(Object *object)` lets this compiler choose ECX
   for the argument. The complete emitted helper at 0x00272AD5 compares equal,
   with zero unresolved relocations, despite its ordinary cdecl source spelling.
   This is stronger evidence than a prologue/size comparison. It supports an
   internal compiler convention as an explanation for the WB/retail argument
   discrepancy; it does not establish an original source name. All 96 parent
   trials with this helper retain either the 748 B common-tail residue or the
   738 B split-tail allocation. No symbol/row ownership change was made.
2. **A diagnostic holder use changes allocation, but does not solve it.** Start
   with the two genuine separate notification tails (738 B, desired EDX move,
   wrong earlier holder/template allocation). One volatile global store of the
   holder immediately after its producer changes the first holder assignment
   from EBX to EDI. This also promotes the Object to EDI later: the final receiver
   becomes `mov ecx,edi`, and the diagnostic body is 745 B. Thus a holder-priority
   change alone is insufficient; preserve the low-priority Object web too.
   `drawable-shroud-register-gap-20261022.patch` reproduces this diagnostic from
   the bank. Apply it with `git apply --unidiff-zero` in a scratch copy only;
   the replay was compared equal to the compiled diagnostic. It compiled with
   the ordinary flags, but contains an extra observable
   store and **must never be landed**. The broader diagnostic family tried four
   use sites, 1/2/4/8 uses and holder/template/Object. Eight oversized bodies
   correctly exceeded the 747 B comparison window; they are not false rejects.

The nearest helper's existing production source remains
`Code/GameEngine/Source/GameClient/Drawable_rva00272AD5.cpp`. Scratch
`static/m0s7t1.cpp` contains the exact internal-function replay and all its real
provider dependencies; `gen_static.py` records the transformations. The callback,
36 B holder provider and 214 B nearest provider were also tested in combinations
before/after the parent; no stand-in bodies were used.

## Finite trials in the new bank context

All 3,896 generated sources compiled into separate private objects, normally
with eight compiler workers. Eight diagnostic scores hit the correct extent
refusal above; the other 3,888 scored trials are nonexact. Counts are generated
trials, not distinct compiler outputs. Retain the earlier handoff's exclusions.

| Family | Trials | Best result / finding |
| --- | ---: | --- |
| Live-Object return carriers, status-pointer views, capture and guard scopes | 160 | Same 748 B residue |
| Real nearest/holder providers, visibility order and Object alias | 32 | All identical 748 B parent |
| Object array/record/union/reference/integer representation, dead test and event guards | 256 | All identical 748 B parent |
| Inline nearest forwarders, argument types, 3 call-site masks, shared/split tails | 192 | 748 B or split-tail regression |
| Recombined notification successors with current callback/kind prefix | 256 | Same residue |
| Actual static nearest provider, convention and call-site combinations | 96 | Helper exact, parent unchanged |
| Notification record, field order, pointer/event types, constructors and capture/read scopes | 512 | Same residue |
| Shared Thing prefix, Object/Drawable inheritance and accessor spellings | 72 | Same residue; trial prefix extents are not layout claims |
| First-sighting successor variants crossed with split final tails | 384 | Best 738 B / 16 normalized differences |
| Positive/nested and negative entry-guard partitions | 128 | Only 748 B or 738 B states |
| Diagnostic reference weights | 96 | Allocation finding above; not eligible source |
| Asymmetric stage placement on each predecessor, real guards, declarations | 400 | Shared: 748 B; split: allocation regression |
| Inner first-sighting guards, early exits, one-iteration loops and scopes | 96 | Same residue |
| Six report guards, positive/negative exits, four holder/controller selectors | 512 | No improvement |
| Genuine event/nearest/Object/Player/Drawable local sharing across regions | 512 | Only 748 B or 738 B states |
| Pending bool/Object/event-reference carriers, sentinels and scopes | 128 | Same residue |
| Whole inline notification helper, Object/event argument types | 64 | Only 748 B or 738 B states |

Control flow, lifetime/declaration scope, type/layout and callee visibility each
received concrete trials. Compiler-family/flag controls and the 54-block passive
c2 trace remain as documented in the previous handoffs; no new evidence justified
repeating those unchanged controls. The shared-tail and split-tail choices keep
trading the last move against earlier allocation. Do not rerun these matrices
without an explanation that changes their inputs.

## Integration limits and resume

`find_declared_unmatched.py Code/GameEngine/Source/GameClient/Drawable.cpp`
passes. However that home still includes ZH-shaped Drawable/ThingTemplate
headers: they do not declare this BFME method or the sighting/revealed/shrouded
fields. The BFME1/bfme2 opaque Drawable shims are separate views, not a ready
replacement for all that home's existing definitions. A full canonical-header
home replay was not performed; simply appending the bank there would redefine
classes. This is an integration constraint, not a missing-callee blocker or proof
that no matching source exists. No `blocked-on=` function was found.

Inputs: BFME2 db448fb4b295802726695adfaa2a0fbf496393c4, BFME1 verified pointer
42bba2ddbd5cb895d99293583891d3b7315fa49e. The recent freshness lock belonged
to claudec2, so this seat followed the runner rule and skipped its pointer update.
Flags unchanged: O1, Ob1, d2inlS100, G7, SSE, MD, EHsc, DNDEBUG, static STLport.
Identity, offsets and the 218-bit interpretation retain the independent target
basis in `drawable-shroud-bitset-20261020.md`; alternative trial views do not
strengthen those claims. No VP6 source was consulted.

Scratch root: `build/drawable27893e-20261022c/`. Each family has its generator,
private objects and JSONL results; `check_residue.py` checks the fresh bank object,
`explain.log` is the independent compiler/tool diagnostic, and `gap_min.cpp`
replays the tracked patch. Existing bank and prior handoffs remain intact.
About 29 minutes, model gpt-6.1-sol. Claim released at handoff; resume this same
body only, starting from the unchanged bank and these negative results.
