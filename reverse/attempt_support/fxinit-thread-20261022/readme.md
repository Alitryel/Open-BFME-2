# FXShaderGeometry::Init: null-edge threading decisions

2026-10-22, codexb2. Target `0x0018C84E..0x0018D16B`, 2333 bytes.
BFME 2 input `56efaa1541` (rebased prior handoff, upstream `025f02303e`);
BFME 1 clean verified pointer `42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Flags: `/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`.

The best bank is unchanged: **2333 bytes, nine differing bytes in seven
instructions at +0x707..+0x721, EH EXACT, zero unresolved calls**, score
`0.9961423060437206`. Only its handoff pointer changes. The fresh private
compile equals the previous bank in complete function bytes and relocations.
No exact recovery or production-code change is claimed.

## Continue here

The previous handoff's requested early/late null-edge investigation is now
resolved to specific decisions below. Do not repeat the skipped-edge source
order sweeps or infer condition propagation from a falling block count.
The valid longer diagnostics still get retail's remap register roles but
retain extra checks and different frame homes; none replaces the bank.

A remaining concrete callee-visibility angle is **the final index lock**:
`IndexBufferClass::WriteLockClass` at 0x138790/0x138840. Its real bodies are in
`Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.cpp` (171/113 bytes), with
layout in `reference/shims/indexbuffercount/dx8indexbuffer.h`. This session
read those definitions but did not compile visible index-lock controls.
Test visibility of constructor/destructor independently and together, before
and after Init, while preserving the 24-byte DX8 buffer and 12-byte lock
layout. Check helper code as well as Init. This probes the final EH state's
alias information; it is a hypothesis, not evidence that this helper is the
cause. The analogous vertex-lock controls below are now excluded.

If that context is inert, return to the allocator's split-range/coalescing
inputs rather than repeating null-only edges: the known four extra reloads
and priority change in the split/edges handoffs are real, but the selected
source guard remains observable after allocation. The source shape needs to
change those inputs without relying on the late pass below to prove nulls.
No missing callee prerequisite was found. On landing the parent, also row
its three unwind funclets at 0x768841, 0x76884B and 0x768868 and verify its
emitted EH handler. Start from the original bank.

## Early compiler finding

Read-only breakpoints in stock MSVC 13.10.3077 C2, base `0x10700000`.
No binary, compiler state, production source, gate or pin was modified.
**All nine traced objects equal their ordinary controls in whole Init bytes
and relocations.** Internal addresses below are RVAs unless identified as
runtime data.

`0x61984` inspects outgoing successors, not incoming predecessor facts.
For the original `skipjoin_020000`, the P-copy-tail test is compared with the
N successor test; these are distinct pointer symbols. Comparator `0x5A137`
returns zero for equality, not a Boolean true. Reversing the added guard to
N-before-P makes the last guard compare the same P symbol as the copy tail,
but does not make the early pass fold it. Both original and reversed guards
remain 131 blocks / 1123 tuples across `0x6323E..0x63297`.

The reversed control's P-entry block is `0xCA0DD8`; its fallthrough P-copy-tail
successor is `0xCA0EA0`. At **0x61A8C**, the successor equals the current
block's next layout block. **0x61A94** reads runtime global **0x108A9208=0**;
**0x61A9B** then skips that successor at `0x61AC6`, before `0x61AE5` can inspect
its comparison. The other successor reaches the vertex increment (opcode
0x278), not a matching pointer comparison. This is the concrete reason this
reversed control does not fold in the inspected early pass.

That global is the speed/size optimization choice: `0x74E90` sets it from
optimization bit 23; the option diagnostic at `0x1465BD..0x1465C9` selects the
literal strings `Speed` and `Size` for `OPT:\tOptimizing for %s`. An isolated
`/Ot` appended after `/O1` sets the observed global to 1. The earlier `/O2`
trial changed multiple flags and did not isolate this variable.

The four `/Ot` controls (bank, original skipjoin, reversed guard and sharedcopy)
all emit **the same 2676-byte Init and relocations**. They have unresolved
out-of-line `vector<short>::assign<Rva005E59FCKeyIterator>` and
`BfmeFVFDescriptor::Is_Plain_FVF` calls, so their fixed-row difference scores
are not exact verification. `/Os` reproduces each ordinary control exactly.
The speed trace is already 127/1109 before the inspected early sweep and
127/1110 after it; this does **not** prove that 0x61984 alone removed the
source distinction. `/Ot` is not a match and is not a usable local fix.

## Late compiler finding

The reduction formerly located inside `0x75142` includes flattening, rebuilding
and ordinary branch/block cleanup. It is not evidence that this pass proves
the skipped path's pointers null.

| Snapshot | Skipjoin blocks/tuples |
| --- | ---: |
| 0x75142 through 0x75204 | 143/1021 |
| 0x75255 | 143/1023 |
| 0x7526C through 0x752E0 | 143/1024 |
| 0x952EF, 0x95308 | 143/1024 |
| 0x95390, after 0x5C99B flattening | 1/882 |
| 0x953A0, after 0x5CC02 rebuild | 128/1009 |
| 0x953A6 and 0x953BA | 128/1009 |
| 0x953C0, after 0x5E4C7 | 116/963 |
| 0x95407, after 0x807D3 | 120/967 |
| 0x95580 through 0x955F1 | 120/967 |
| 0x752F3, return from 0x952EF | 120/973 |

`0x5E4C7` walks blocks and calls `0x5E473`, `0x5E29C` and `0x5E3DD`, then
performs adjacent-block work. A targeted trace of **0x5E29C** covers both
added entry checks and both P/N copy-tail checks: blocks `0xC80EF8`,
`0xC80FC0`, `0xC81088`, `0xC812E0`. Each reaches `0x5E2E8` after the
`0x5AD8C` scan of the next layout block, then returns through `0x5E2F6`.
The scanned instruction kinds are not the branch kind 0x12 required by
`0x5E2EC`. The routine never reaches `0xA46D6` for these four blocks and does
not compare their repeated null conditions. Do not treat it as a general
redundant-condition prover. The recorded block/tuple snapshots retain the
checks on both sides of this pass.

The machine-level entry checks use a zero-valued ECX operand, while the copy
checks use literal zero. This difference was observed, but it is **not** the
proven rejection cause above. Also, an early operand's word 4 is SSA metadata,
not a displacement; the scratch pretty-printer's large early offsets must not
be interpreted as memory layout evidence. `0x807D3` first tests graph edges
with `0x5E1C2`, then invokes the `0x4F03D` graph/loop helpers; a full semantic
identification of that machinery is not claimed here.

## Source/context trials excluded

**5012 generated full-body combinations, all compiling; 4480 resolve in the
fixed scoring extent.** There are 528 relocation/extent refusals in edgeorder
and four unresolved `/Ot` controls. Counts include duplicate outputs and
controls, not unique machine bodies. No gate false-reject is claimed.

| Family | Trials | Result |
| --- | ---: | --- |
| qualifiers | 1008 | Nine independently selected T/B guard/source, first P/N stream, basis and optional P/N pointer reads, including whole T/B pointer qualification. Best is the unchanged bank. |
| reverseguards | 512 | N-before-P guards crossed with selective pointer/dispatch qualifiers, comparison spelling and duplicate P tests. Best 2346 B; no improvement. |
| edgeorder | 3456 | N-before-P guard variants crossed with 24 source block orders, three dispatch heads, skipped-edge subsets and four equivalent positive-bone predicates. Best resolved 2347 B, 487 differing bytes, 2 structural regions / 8 structural instructions / 63 operand differences. |
| resizevisibility | 12 | Actual rowed 0x18C7E5 resize body before/after Init; inherited or explicit three-pointer view; noinline/inline/forceinline. Eight non-forced contexts reproduce the bank exactly and emit the exact 61-byte helper. Four forced-inline bodies are 2375 B and worse. |
| lockvisibility | 16 | Actual vertex-lock constructor/destructor source, independently visible or opaque, before/after Init, inline/noinline, with donor layout and a 32-byte allocation assertion. Every Init equals the bank. |
| speed controls | 8 | Four controls under appended /Os or /Ot; results described above. |

The vertex helper source comes from the rowed
`VertexBufferLockClasses.cpp`, including the device guard, D3D virtual calls,
reference count and error reporting. Under this experiment's `/O1` inline
context, its emitted constructor/destructor are **112/89 bytes rather than
retail's 142/113**. This is a semantic/body-visibility experiment, not proof of
exact helper context or a proposed helper landing. The verification JSON
records that limitation explicitly. Init itself is byte/relocation identical
in all sixteen contexts, including layout-only controls. Index-lock visibility
has not been tested here.

These trials address new lifetime/qualification, control-flow/layout,
helper-visibility and isolated compiler-setting hypotheses. The previous
WB, copy representation, types/layout and compiler exclusions remain in
[the phase handoff](../fxinit-phase-20261022/readme.md) and its linked history.
The stronger original bank is retained.

## Checks and reproduction

`check_csv.py` passed at startup (98,069 functions, 15,856 symbols, 2,131 data).
BFME 1 freshness was deferred under the runner's live update lock owned by
`claudec2`; its clean verified pointer was preserved. No success stamp or
other seat's lock was changed. Broad queues were skipped for this standing
assignment. No maintainer-only runner was started.

`bank-verification.json` records fresh resolved bytes, EH EXACT, nine traced
controls, eight resize controls and sixteen vertex-lock controls, plus all
four speed/size control comparisons. `bank-diff.json` records zero structural
regions and the seven remaining real operand differences. `observations.json`
keeps compact phase counts, the selected late blocks, and read-only decision
traces; `results-summary.json` keeps each family's counts and useful extremes.
This partial is not an exact-body gate pass and was not installed in `Code/`.

Restore the `*.py.txt` drivers under ignored `build/fxinit-thread22/`. They use
`build/fxinit-seat22/search.py` and `build/netpacket-20261022e/wdbg.py` preserved
in the schedule handoff. Recreate `skipjoin_020000` and `sharedcopy_00000` from
the edges handoff first. Generators take no arguments; tracer drivers take
`SOURCE PRIVATE_OBJECT`. `earlydecision.py` targets the original skipjoin;
`reversedecision.py`/`fallthrough.py` target `revguard_00000`; `latebranch.py`
targets the original skipjoin and asserts its input-specific block identities.
`speedtrace.py` uses `speed_reverse_t`. Do not run input-specific address
breakpoints on another variant without remapping and checking the blocks.

Run `verify_bank.py` after generating/tracing the first eight controls, then
`verify_extra.py` after lockvisibility and skip-latebranch. Private objects
are never written to `build/match/`. All full trial sources/objects and full
snapshots remain in ignored `build/fxinit-thread22/` for this seat to continue.
