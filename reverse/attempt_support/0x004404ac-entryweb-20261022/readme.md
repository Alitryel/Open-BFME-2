# AptMpGameSetup 0x004404AC: entry webs and hidden CFG blocks

The assignment remains unfinished. Preserve the existing bank at
`reverse/attempts/0x004404ac.cpp` (score 0.9); no candidate improved it.
A fresh isolated compile emits 526 bytes and 183 instructions, with zero
structural regions and 31 operand differences: seven memory and 24 register.
Every difference disappears under an ESI/EDI exchange. Retail retains the
receiver in ESI and the corrected slot in EDI; the bank reverses them.
`residue.txt` records the fresh comparison. All sixteen calls resolve.

This session continued only this body. It tested 3,696 generated variants,
all compiling, with no exact match. Of these, 416 retain an unresolved new
helper/destructor call and are excluded from valid comparisons. The bank,
Code, ledger, pins, tools and baselines are unchanged. This is continuation
evidence, not credited C++ recovery or a successful gate for the target.

## Inputs and checks

Starting BFME2 HEAD: `4c4d886f52ae903190c833ac9181e39d957ced2b`.
Verified committed BFME1 pointer: `42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Flags are the bank's `/O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
/D_STLP_USE_STATIC_LIB`, STLport, MSVC 13.10.3077 under Wine. Input and
compiler hashes and family counts are in `results.json`.

At start, the tree was clean and the prior runner handoff named this task.
Nonrecursive upstream pull, `check_csv.py` (98,065 function rows), published
link-index fetch, claim and frozen-home check passed. BFME1 remained clean at
the committed pointer: another seat's fresh updater lock, owned by `claudec2`,
required skipping a concurrent update. Do not remove that lock or stamp a
freshness success for this skipped update. Use
`git -c submodule.recurse=false pull --rebase origin master` in this checkout.

The unchanged home unit,
`Code/GameEngine/Source/GameClient/GUI/Rva0043F483PopulatePlayerCombo.cpp`,
passes `./build.sh`: 5/5 matched functions, its data row, six literals plus an
empty-string reference, float and import checks. This verifies the existing
home, not the nonmatching bank. Final ledger, diff and progress checks and
claim release are recorded with the session result.

## Prior exclusions reviewed

Read the targeted pick-hard history, the 20261020 visibility, 20261021 WB frame,
and both earlier 20261022 allocator-cost handoffs before trials. Those exclude
ordinary guards/loops/scopes, names and inert-local/permuter scans, broad
throw/qualifier/accessor grids, receiver aliases, array wrappers, real-provider
visibility, compiler profiles, preview-address motion and full-body inlining.
The known early slot copy gets the right registers but moves the push/load
across the game-null branch; the known early preview pointer gets the right
registers but replaces the final LEA with ADD/MOV and adds two bytes. Neither
is a bank improvement. Those broad families were not repeated.

## New measured finding

`prologue-049` is a byte-for-byte bank twin. It extracts the getter and slot
clamp into a force-inlined member returning GameInfo*, with the slot passed by
reference. Its second clamp is spelled as two separate early returns.
`split-clamp-control.patch` reproduces it (zero context; apply with
`git apply --unidiff-zero` against a copy of the bank).

Read-only WineDbg traces of the unmodified C2 show that identical emitted code
can have different allocation costs. Compared with the bank's initial
`this=41, slot=49` priorities, this twin has `this=39, slot=51`.
It introduces one extra pre-allocation CFG block, ordinal 7, frequency one:
slot receives +2 (one reference, scaled factor two), while the live receiver
receives a -2 penalty. All other receiver/slot contributions in the initial
pass are identical, with subsequent ordinals shifted by one. The slot gains
one reference (15 versus 14); the receiver remains at 12. The extra block
worsens the gap rather than closing it.

`allocator-delta.json` records initial candidates and this delta. The
preservation script checked equality against the previous tracked bank trace
for blocks 1..6 and new 8..55 versus bank 7..54, and checked contribution sums
against insertion priorities. The last block has no receiver/slot costs;
the final preview reference is new block 54, formerly 53. Later allocation
passes have additional blocks and must not be confused with this initial pass.

The pure preview-result helper `foundhelper-002` is also a bank twin. A second
initial-priority trace confirms exactly `this=41, slot=49`; its extra inlined
result parameter does not change the useful costs. Debugger sites and record
word meanings remain those documented in the preceding blockcost handoff.
No compiler memory or binary was modified.

## New source families

| Family | Trials | Result |
| --- | ---: | --- |
| Getter/clamp helper contracts | 512 | Eight result/reference contracts, four clamp graphs, four scopes, inline/forceinline and throw specification. 256 unresolved helpers; 44 valid bank twins. Some correct-role variants still move the entry save/load. |
| Corrected-index lifetime objects | 384 | Four declaration points, value/reference representations, four nontrivial destructor forms, three accesses and copy construction. 108 bank twins; no improvement. |
| Getter boundary types | 256 | Eight ABI-sized return spellings, four local forms, opaque/real/noinline/forceinline provider visibility, early index copy. 96 bank twins. Alternate mangled return names exist only in the scratch resolver map, never pins. |
| Index cleanup/write-back | 240 | Parameter-reference cleanup, activation point, initialization timing, destructor control flow and scope. 32 unresolved destructor calls; every valid body is worse (minimum 546 B). Uninitialized null-exit combinations were excluded. |
| Bound preview receiver | 512 | Pointer/reference receiver, four declaration points, four destructor forms and four direct/proxy/member-pointer calls. 128 unresolved proxies, 384 bank twins. |
| Evidence-supported hierarchy context | 64 | Flat polymorphism versus one/two base layers, known 0x58 base fields, opaque/empty destructor, preview/slot polymorphism, GameInfo virtual destructor slot. All bank twins. |
| Pure preview-result helper | 512 | Return versus out parameter, nested versus guard exits, for/do loops, parameter order/reference types and scope. 128 bank twins; direct-return forms change structural code. |
| Explicit exception regions | 192 | Six region subsets and catch-all/int/char-pointer rethrow handlers, preserving combo lifetime. Only three unchanged controls are bank twins; every added region is worse. |
| Switch control-flow factorial | 1,024 | Ten independent equivalent condition sites, including the clamps and map test. Only the unchanged control is a bank twin; every nonzero mask adds structural differences. |

The concrete validated getter's body/layout comes from the already rowed
`Rva0043DA65Getter.cpp`; the 0x58 polymorphic base and preview's virtual
member context come from the rowed `Rva004421E1Dtor.cpp`. GameSlot's virtual
reset is also present in the ZH header. These are compiler-context probes;
no new original type/return identity is claimed. Target offsets, ABI, calls
and behavior remain those established in previous bank evidence. The WB twin
was reread only as target/reference evidence, not byte-match proof.

## Reproduction and next step

Copy the `.py.txt` files into ignored `build/4404ac-entryweb/`, dropping `.txt`,
from the repository root. Run each `*_search.py` with Python 3; compilation
uses `build.compiler_command`, eight isolated workers and whole emitted
extents. Never use `build.compile_source`. Delete scratch objects when any
input changes: the source-equality shortcut is valid only within fixed inputs.
Unresolved new helpers are never matches, even when their size looks good.
Run `trace.py prologue-049`, `trace_blocks.py prologue-049` or
`trace.py foundhelper-002` after generating those source files. Raw traces and
thousands of trial objects remain ignored.

The review point has concrete new trials for control flow, lifetime,
types/layout, and callee visibility, with settings already excluded by the
previous session. No missing function or external prerequisite is identified.
Continue this same body from the unchanged best bank. A focused next step is
to minimize the entry/null-branch web in a small probe and inspect the actual
live-candidate bits behind factor three versus five. The new hidden-block
control proves that cost changes can survive until allocation even when their
instructions disappear. Seek such a change that raises receiver priority
without moving the index save/load; do not repeat the early-copy control or
these completed factorials.

Model: gpt-6.1-sol. Claim released after recording this continuation evidence.
