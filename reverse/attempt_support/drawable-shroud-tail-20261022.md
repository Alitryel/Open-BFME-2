# Drawable shroud: one instruction remains

Target `?onComingOutOfShroud@Drawable@@AAEXXZ`, 0x0027893E..0x00278C29,
747 bytes. The new bank emits **748 bytes / 220 instructions**, against
retail's 747 bytes / 220 instructions. Excluding genuine COFF relocation
operands and branch displacements, exactly one instruction operand differs:

```text
retail +02BA: mov ecx, edx                 ; 2 bytes
bank   +02BA: mov ecx, dword ptr [ebp-10]  ; 3 bytes
```

This is the nearest-object receiver in the shared revealed/shrouded tail.
Both predecessors already loaded the same Object pointer into EDX for the
private-status test. All earlier instruction operands, frame slots and
holder/template registers now agree. No unresolved calls remain. The first
positional mismatch at +35 is a branch displacement caused by the extra byte,
not the cause. The bank score 0.995 describes instruction similarity, not
verified byte coverage. This is still a partial; no Code source or ledger row
was changed for it.

## What improved the October 20 bank

Start was the checked-STLport 740-byte bank at commit f236b5b159, after reading
the complete picker history and the three October 20 shroud handoffs. The old
holder-in-EBX/template-in-EDI allocation was the substantive residue.

1. Share the final revealed/shrouded notification source, carrying its event
   in a function-scope local. Keep both original status/death guards and both
   event-field reads in their original paths; enter the common notification
   only after the status store. This makes retail's holder-in-EDI allocation
   and template reloads appear. A diagnostic equal-arm successor helped find
   the shape, but the retained source has no equal-arm conditions or unused
   numbering locals.
2. Load the sighted event into its own local before initializing the callback
   data. WB CA3700 has precisely this temporary (local_70) before the two
   context stores. This keeps the value in EDX until after the argument pushes,
   reproducing the native scheduling.
3. Test the constant kind-7 bit through the unsigned-byte representation of
   the existing bitset and the live 0x80 mask. This reproduces the memory/BL
   test. The first kind-47 check still uses the real checked STLport bitset.

The common tail and temporary are source-shape inferences supported by emitted
code; they do not establish original variable names. Identity, event/flag
offsets and WB method/source naming remain the independent target evidence
recorded in the October 20 handoff. The 218-bit KindOf interpretation has its
separate native table/xfer evidence there. ZH BitFlags remains a semantic
guide, not evidence for another imported class layout or donor identity.

## Trials and negative results in this context

All counts below are generated trials, not distinct compiler outputs. Builds
used separate private objects, at most eight compiler processes, with the
normal compiler command and relocation resolver. Never force compiler state
to admit a match.

| Family | Generated / compiled | Result |
| --- | ---: | --- |
| Shared first-sighting completion, pointer aliases, predicates, entry edges | 384 / 384 | No improvement over old bank |
| Actual 36-byte holder provider visible, crossed with six throw annotations (diagnostic only) | 128 / 128 | Same old 740-byte parent throughout |
| Shared final notification, four work placements, predicates, entry edges and local placement | 256 / 256 | Fixes holder/template selection; best initially 750 B |
| Callback initialization, kind-bit expression, pointer carrier, mask scope factorial | 512 / 512 | Best 748 B, single operand residue above |
| Tail carrier placement, references, pointer casts, condition forms and scopes | 256 / 236 | No improvement; 20 invalid combinations are not evidence |
| Separate native notification sources, event/nearest scopes and guard forms | 512 / 512 | Regresses holder allocation; best 738 B, 16 normalized instruction differences |
| Event/nearest guards and work moved between real predecessors and shared tail | 256 / 256 | No improvement |
| `permute.mutate`, deterministic seed 0x27893e, combinations of 1–6 mutations | 512 / 150 | No improvement; invalid mutations excluded |
| Joined exit labels, early event/nearest guards, const-reference alias, compiler flag variants | 70 / 70 | No improvement |

The permutation run must preserve `// stlport` as well as `// cl:`. Two
preliminary generator mistakes omitted those markers; their output was
discarded, not counted as trials under the intended inputs. The final run
above uses the complete cleaned source with both markers.

A passive c2 trace of the cleaned source reports **54 IR blocks in all seven
allocation rounds**. The trace changes no compiler data and its raw parent
bytes reproduce the ordinary build. Thus the large-body 100-block complex
split threshold from the amoeba investigation is not a supported explanation
here. Do not repeat the old volatile-pointer, declaration-only, context-pair,
provider-only or baseline inline-budget sweeps without changed evidence.

## Verification and resume

Inputs: BFME2 f236b5b159 (origin/master e33d802535 at measurement), clean BFME1
42bba2ddbd5cb895d99293583891d3b7315fa49e. Flags stay O1, Ob1, d2inlS100,
G7, SSE, MD, EHsc, DNDEBUG and static STLport. Destination discovery says
`Code/GameEngine/Source/GameClient/Drawable.cpp`; this bank has not been
integrated there. Earlier provider and ABI reconciliation findings still
apply; do not add another pin or alias to 4A1828.

`explain_mismatch.py` independently reports compiled size 748 and the same
nonexact body. Raw full-symbol disassembly has zero structural regions and
one nonrelocation operand difference. Do not measure emitted size from
`compile_function()['bytes']`: its 747-byte comparison window truncates longer
trials. Use `locate.object_functions` for the complete symbol. No compiler
flag or extent adjustment makes this a match.

Scratch: `build/drawable27893e-20261022b/`, with generators, private objects,
JSONL results, full raw-symbol scorer, WB disassembly and passive c2 trace.
The bank itself preserves the useful source. Next work is specifically the
Object web carried across the two tail predecessors; the old broad
holder/template allocation problem is solved. No missing-function dependency
was found. About 25 minutes, model gpt-6.1-sol.
