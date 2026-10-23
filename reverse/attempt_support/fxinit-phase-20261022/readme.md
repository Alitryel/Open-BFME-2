# FXShaderGeometry::Init: locate the early and late branch cleanup

2026-10-22, codexb2. Target `0x0018C84E..0x0018D16B`, 2333 bytes.
BFME 2 input `6b48d28f03`; clean verified BFME 1 pointer
`42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Flags: `/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`.

The best bank is unchanged: **2333 bytes, nine differing bytes in seven
instructions at +0x707..+0x721, EH EXACT, zero unresolved calls**, score
`0.9961423060437206`. Its only edit is this handoff pointer. No exact recovery
or production-code change is claimed. A fresh private compile reproduces the
preceding bank's complete function bytes and relocations.

## Continue here

The prior handoff asked when redundant incoming edges disappear. That question
is now narrowed to concrete compiler passes below. Next inspect the branch
threading/cleanup decisions inside **C2 RVA 0x61984 (early)** and
**0x75142 (after allocation)** for the actual optional-copy successor in
`skipjoin_020000`. The late call is at `0x753CB`, with a snapshot immediately
on return at `0x753D0`. Determine why the skipped path's proven null pointers
cannot bypass its copy-tail checks there. The aggregate phase traces do not
yet identify the exact subroutine/condition inside 0x75142 that makes that
decision. Do not repeat the tail-tree, duplicate-copy or vector-header trials
below. Continue from the original nine-byte bank, not a longer diagnostic.

The previous `skipjoin_020000` remains the useful valid-scope allocation
control: 2346 bytes, retail remap register roles, thirteen extra bytes and
changed frame homes. Its null-only skipped edge reaches the P/N tail without
performing either copy. The closer 2343-byte `nulljoin_0020002` and the
non-equivalent unconditional-tail diagnostic remain documented in the earlier
handoffs. No missing-callee prerequisite was found; the short constructor
family is already repaired. The normal landing must also row the parent's
three unwind funclets at 0x768841, 0x76884B and 0x768868.

## New compiler evidence

All observations use read-only breakpoints and memory reads in stock MSVC
13.10.3077 C2, loaded at `0x10700000`. No compiler binary/state, gate, pin or
production source was changed. **All fifteen completed traced objects match
their ordinary controls' complete Init bytes and relocations.**

The comparison is the incoming bank versus the previous handoff's
`sharedcopy_00000` and `skipjoin_020000`. The sharedcopy source redundantly
retests the same position pointer and has duplicate position-copy paths;
its final bytes equal the bank. The skipjoin source retains an extra valid
incoming edge to both optional-copy tests.

| Snapshot RVA | Bank blocks/tuples | Sharedcopy | Skipjoin |
| --- | ---: | ---: | ---: |
| 0xAFFF7, after early IR construction | 133/1051 | 138/1079 | 137/1064 |
| 0x5F950, return from 0x66AFB | 137/910 | 137/910 | not sampled |
| 0xB0030, immediately before allocation | 125/880 | 125/880 | 128/890 |
| 0x83AAC, allocator round zero | 128/909 | 128/909 | 131/919 |
| 0xB0037, after allocation | 139/1009 | 139/1009 | 143/1021 |
| 0xB003E, after 0x74F92 | 117/966 | 117/966 | 120/977 |
| 0xB00A1, late flattened IR | 1/803 | 1/803 | 1/811 |

Equal counts are not asserted to prove identical graphs. The independently
verified emitted bytes and relocations establish the sharedcopy/bank control
result. The counts delimit where to inspect the transformations.

The early convergence occurs inside **0x66AFB**, called at 0x5F94B, well before
register allocation. Before its cold continuation (0x66B5E), bank/sharedcopy
have 127/1110 and 132/1140 blocks/tuples. They remain different through
0x6323E. The backward block sweep calling **0x61984 at 0x6328B** removes
17 sharedcopy tuples and changes one opcode; the bank loses none there.
One affected block contains comparison opcode 0x288 and branch 0x291.
The following **0x631AE call at 0x632EE** removes three sharedcopy blocks,
leaving 129/1118 versus the bank's 127/1110. Subsequent work inside 0x66AFB
converges the aggregate counts to 137/910 before 0x5F950. The exact source
meaning of every deleted internal tuple has not been independently decoded.
`observations.json` retains the affected blocks and deleted/changed tuples.

The important late reduction in skipjoin occurs in **0x75142**, called by
0x7532E at **0x753CB**. Earlier calls to 0x75460, 0x7595E and 0x754C9 do not
change its 143/1021 counts. On return from 0x75142, the counts are 120/973;
the next call to 0x75CAE adds four tuples, yielding 120/977. Three extra blocks
relative to the bank survive the enclosing post-allocation pass. Its extra
null tests/jump also survive emission; this is not a free allocator-only edge.
The phase trace locates the effect but does not establish internal pass names.

For orientation, the outer pipeline calls 0x5F923 at 0xB0001 (early optimizer),
0x7C937 at 0xB002B (lowering), 0x7C08E at 0xB0032 (allocator), 0x74F92 at
0xB0039, and 0x5C99B at 0xB0060 (block flattening). Later snapshots at
0xB0087 and 0xB00A1 account for further instruction cleanup.

## Source trials excluded

Private objects, eight workers. **2064 generated full-body trials, all
compiling; 2006 resolve in the fixed scoring extent, 58 hit relocation/extent
refusals.** These counts include eight donor-header controls and 24 intrinsic
controls; they count combinations, not unique emitted bodies. No gate
false-reject is claimed. None improves the bank.

| Family | Trials | Finding |
| --- | ---: | --- |
| tailtrees | 1008 | Twelve nested/duplicated P/N truth-table trees; direct/bool/unsigned/byte existence flags, two scopes, three null guards and skipped-edge subsets. Best 2333 B / 49 differing bytes; original wrong remap roles plus changed stack homes. |
| copytypes | 512 | Duplicate P/N paths with eight independently selected copy spellings for P and N, four predicates and two branch scopes; explicit memcpy intrinsics. Best 1326 differing bytes; global intrinsic effects prevent treating this as a purely local change. Six extent refusals. |
| copyplain | 512 | Same family without the intrinsic pragma, including ordinary assignment controls, field copies, temporaries, byte loops and representation-preserving memcpy. Best 1218 differing bytes, 52 extent refusals. Original remap roles remain in the duplicate-assignment control. |
| intrinprobe | 24 | Isolate intrinsic/function pragmas, four spellings of the final variable-size memcpy call, and an optional fixed-size copy helper. Even unchanged-copy controls alter the body; these pragmas do not isolate the copy-tail effect. |
| donorvectors | 8 | Complete BFME 1/ZH Vector3 headers, real WWMath context, donor or canonical Vector2, and include order. Every body and relocation is identical to the bank. |

The duplicate-copy hypothesis was that source-distinct but equivalent copies
might retain a join until machine-level cleanup. The resulting bodies have
substantial changes, including x87 field transfers and stack allocation; the
ordinary duplicate-assignment control still has the wrong remap roles. No
regional winner justifies replacing the stronger bank.

The donor-header check uses the actual `game/Libraries/Source/WWVegas` tree
and `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas`
at the recorded BFME 1 pointer. The WWLib, WWMath and WWDebug directories and
both vector header files are asserted present. The unchanged existing sweep
platform shim supplies ancillary platform declarations; neither vector header
is silently substituted. Vector3 size is statically checked as 12. Actual
Vector3 assignment and storage agree with the bank; bringing its remaining
constructors, methods and force-inline context into the TU is inert.

Control flow/copy entry, scope/lifetime and copy representation received new
factorial trials here. Full donor vector visibility was checked explicitly.
The previous compiler-settings, actual UV helper, WB and layout investigations
remain in the linked history. No previously disproven sweep was rerun unchanged.
An initial copytypes generator had a Python f-string syntax error before any
compile; the corrected driver is preserved and all reported counts are from
its completed runs.

## Checks and reproduction

`check_csv.py` passed at startup and after the trials (98,068 functions,
15,856 symbols, 2,128 data before any subsequent upstream publication).
Published-object fetch completed, retaining the newer local index. BFME 1
freshness was deferred under the runner's active update lock owned by
`claudec2`; the clean verified pointer was retained and no success stamp or
other seat's lock was changed. Broad queues were skipped for this standing
assignment. No maintainer-only verification runner was started.

`bank-verification.json` records the fresh resolved-byte/EH check, fifteen
traced controls, and all eight header controls. `bank-diff.json` records zero
structural regions and seven real operand differences. This partial is not
an exact-body gate pass and was not placed in `Code/`.

Restore the `*.py.txt` drivers under ignored `build/fxinit-phase22/`. They
import `build/fxinit-seat22/search.py`, preserved in the schedule handoff,
and `build/netpacket-20261022e/wdbg.py` from that same handoff. The generators
take no arguments except `copytypes.py --plain` for the non-intrinsic family.
The consolidated tracer takes `PROFILE SOURCE PRIVATE_OBJECT`; profiles are
`frontend`, `opt`, `early`, `cold`, `lower`, `post`, `post2`, and `post3`.
It uses the same read-only snapshot algorithm and breakpoint sets as the
exploratory drivers. `lower` ignores allocator rounds other than zero.

Recreate sharedcopy and skipjoin controls from the preceding edges handoff
before tracing. `verify_bank.py` compares against those ordinary objects and
the preceding bank control, and scans this session's completed trace objects.
The ignored `build/` directory retains full snapshots and every trial here;
this tracked handoff keeps compact phase observations, measured best results,
reproduction drivers and the unchanged best candidate. Eventual home and
select-any helper requirements remain in the wbinline handoff.
