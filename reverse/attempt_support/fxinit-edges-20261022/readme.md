# FXShaderGeometry::Init: a two-predecessor join fixes the remap roles

2026-10-22, codexb2. Target `0x0018C84E..0x0018D16B`, 2333 bytes.
BFME 2 input `fe1c655f28`; verified BFME 1 pointer and clean checkout
`42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Flags: `/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`.

The best bank remains **2333 bytes, nine differing bytes in seven instructions
at +0x707..+0x721, EH EXACT, zero unresolved calls**, score
`0.9961423060437206`. A fresh private compile reproduces the preceding bank's
bytes and relocations. Only its handoff comment changes. This session adds
compiler evidence and a better diagnostic join, not an exact recovery.

## Continue here

The previous session's two outstanding investigations are complete: the
five predecessors are mapped below and the loop has reduced probes. The new
question is **when redundant incoming edges disappear**. Compare the retained
bank-result `sharedcopy_00000` with `skipjoin_020000`: the latter's skipped
path enters a P/N tail that cannot write on that edge, but its null checks
survive into machine code. Find the C2 pass that removes the former's redundant
edge, and the last opportunity to remove the latter's checks after allocation.
Trace that phase before another guard-spelling sweep. No such pass trace was
performed here. The existing read-only traces identify the relevant remap
block and join and can anchor that investigation.

The closest new diagnostic is `nulljoin_0020002`, **2343 bytes**, with retail's
remap register roles and only the remap-base frame displacement wrong within
that region. Its extra ten bytes and changed stack homes make it worse than
the bank. Preserve it as a regional lead, not as the next starting body.
`skipjoin_020000` is the simpler, traced version: 2346 bytes, thirteen extra.
The original bank remains the starting source. There is no missing-callee
prerequisite; the signed-short vector constructor was already solved.

## Map of the old diagnostic's five incoming paths

The preceding `pn_300000` diagnostic places P/N unconditionally at the common
dispatch tail. Its scope is wrong and it is unsuitable for landing. At the
first selected edge-reload event, successor `C727A8` has these predecessors:

| Predecessor | Source path, identified from the branch chain and stores |
| --- | --- |
| `C72230` | `m_Passes > 1`, store the named `pass` value |
| `CA4CF8` | Merge of nonpositive bone count and null `links[0]` |
| `C72550` | One-bone remap store |
| `CA4C08` | Positive bone count other than one or two |
| `C726E0` | Two-bone remap and weights |

The pass store uses the named `_pass` and `_vertices` symbols. The one- and
two-bone paths are distinguished by their remap loads and the comparisons to
one and two. These source-path identifications are based on this control flow;
the opaque memory operands are not a new independent class-layout proof.
The existing target/WB layout evidence remains in the earlier handoffs.

## New valid-scope diagnostic and measured priorities

The new edge is from the skipped-skinning path into the existing two-bone
P/N tail, **only when both optional pointers are null**:

```cpp
// Within the two-bone arm, after the original remap and weight stores:
CopyBoth:
    if (positions[1]) /* original position copy */;
    if (normals[1])   /* original normal copy */;
// ...
// On the nonpositive-count/null-link path:
    if (!positions[1] && !normals[1]) goto CopyBoth;
    goto FinishSkin;
```

That additional edge performs neither copy, preserving the original condition
under which each store occurs. No uninitialized local is bypassed and no
outer stream pointer is modified. This is the complete
`skipjoin_020000.patch`, not an unconditional-tail diagnostic.

Read-only stock MSVC 13.10.3077 traces show that its remap block `DEC1F0`
reaches shared successor `DEC448`. The latter has **only two predecessors**:
`DEC1F0` and `DEC380`, the second null-test block. Five incoming paths are
therefore unnecessary for the useful allocation change.

| Candidate | Bank priority (previous trace) | New diagnostic priority |
| --- | ---: | ---: |
| Remap base | 60 = 6 * 10 | 48 = 6 * 8 |
| Split link pointer | 36 = 6 * 6 | 60 = 6 * 10 |

At C2 RVA `0x8292A`, the new remap base is candidate 51, serial 618, symbol
`C25FB4`; the split link pointer is candidate 176, serial 652, symbol
`DB51CC`. The captured remap IR uses those same symbols for the map-base
reload and the link-pointer reloads/movzx operations, establishing their
roles independently of guessed candidate numbers. The base has three
definition entries and five flagged live entries. The split has two
definitions and six flagged live entries, plus the bitset contribution in
the existing cost calculation. Its six flagged entries are 129/0, 127/649,
125/650, 93/405, 92/401 and 128/652 (candidate/serial). Do not carry these
IDs into a different input without rediscovering them.

The emitted remap instructions now use retail's ECX/EAX roles and scheduling;
only the frame slot for the remap base differs in that region. The original
P-null comparison is no longer scheduled before the final weight stores,
and the new skipped-path null tests plus a jump survive. Replacing the two
null tests with an unsigned pointer OR reduces the diagnostic from 2346 to
2343 bytes; it does not eliminate the extra path or restore the bank's frame.

Four completed traced objects reproduce their ordinary controls' complete
Init bytes **and relocations**: the old diagnostic predecessor trace, two
new cost traces, and the new predecessor trace. `observations.json` retains
real IR operands (label pseudo-operands excluded), predecessor graphs and
the two relevant cost events. This was observation only: no compiler memory,
DLL, flags, gate, pin or production source was modified.

## Source families excluded this session

Private objects, eight workers per family. **7440 generated full-body trials,
all compiling, 7240 resolving within the 2333-byte scoring row, 200 extent or
relocation refusals.** Counts are combinations, not unique machine-code
results. There is no gate false-reject claim. None improves the bank.

| Family | Trials | Scope |
| --- | ---: | --- |
| sharedcopy | 1152 | Two independently selected predicates, three forward-edge shapes, P/N selection and polarity |
| sharedboth | 384 | Corrected combined-P/N subset of sharedcopy |
| skipjoin | 432 | Extra null-only edges from subsets of skipped dispatch paths into P/N tests |
| nulljoin | 1152 | Pointer/bool/integer guards, two scopes, eight null expressions, copy order and enclosing guards |
| copyblocks | 1152 | All 24 orders of separate P/N tests and stores, branch polarity, guard form and label scope |
| countloops | 1152 | Numeric zero/one-trip optional-copy loops; P/N forms crossed with T/B forms, bank and new-join contexts |
| dispatchjoin | 648 | Pass/one-bone/two-bone/skip block permutations and dispatch forms with the new incoming edge |
| selectededge | 288 | Null selections passed only along skipped incoming edges; pointer/bool/integer representation, scopes and assignment sites |
| crossstride | 1080 | Derive link/weight indices from a 12-byte T/B cursor; subsets, equivalent unsigned divisions, scope and P/N cursor use |

The first sharedcopy generator omitted indentation in its combined-P/N token,
so **384 of its trials were unchanged controls**. The corrected sharedboth
family actually applies all 384 combinations and asserts that the token exists.
Those controls are not counted as evidence against a source hypothesis.
The reduced-probe driver initially used a relative path rejected before the
compiler launched; its corrected absolute-path run is the one recorded below.

The smallest selectededge result is 2353 bytes and retains the bank's wrong
remap roles, adding boolean materialization. Null-pointer selections and
numeric copy loops do not provide a free join. Cross-stride expressions
retain arithmetic and substantially disturb the body. No new full-body
result is close enough to replace the nine-byte bank.

## Reduced probes

`probe.py` extracts the skinning loop into `_FXProbe`, with 32 subsets of the
preceding position, normal, color, UV and tangent/binormal work. Four controls
per subset give **128 successfully compiled probes**: native P/N scope,
unconditional common tail (diagnostic only), explicitly guarded common tail,
and a single deferred-copy boolean.

For all 32 subsets, the boolean-control object's complete probe bytes and
relocations equal the native-scope control. Ten subsets, including all five
preceding regions, retain the unconditional-tail remap sequence in the
explicitly guarded common-tail variant. Those small probes have different
parameters and frames; their register choices are not BFME 2 match claims.
They establish that the single boolean is folded back to the native shape,
whereas rechecking the dispatch condition can retain the alternative shape.
Selected probe disassembly contexts and all masks are recorded.

## Checks and reproduction

`check_csv.py` passed at startup and after the trials: 98,064 functions,
15,855 symbols, 2,128 data. The published-object fetch completed and retained
the newer local index. BFME 1 freshness was skipped under the runner's active
lock owned by `claudec2`; the clean verified pointer was retained. No other
seat's lock or successful-check stamp was changed. Broad queues were skipped
under the standing assignment. `bank-verification.json` and `bank-align.json`
record the fresh resolved byte/EH verification and all four trace controls.

Restore the `*.py.txt` files into ignored `build/fxinit-edges22/`. They import
`build/fxinit-seat22/search.py`, preserved in
`../fxinit-schedule-20261022/search.py.txt`, and the debugger helper from that
handoff under `build/netpacket-20261022e/wdbg.py`. Each generator runs without
arguments. Run nulljoin before countloops, which reads its selected source.
Tracers take source and private object paths; addresses are input-specific.
The old diagnostic source comes from the schedule handoff's pn_300000 patch.
`verify_bank.py` compares against the preceding bank control under
`build/fxinit-split22/` and those ordinary diagnostic controls. Recreate those
objects from the recorded sources in a fresh checkout. The patches here use
the incoming bank; its handoff-comment change is immaterial to compilation.
