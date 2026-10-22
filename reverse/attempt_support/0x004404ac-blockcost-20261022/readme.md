# AptMpGameSetup 0x004404AC: block costs and source-family exclusions

The standing assignment remains unfinished. Preserve the existing standalone
bank `reverse/attempts/0x004404ac.cpp` (recorded score 0.9): a fresh compile
still emits 526 bytes and 183 instructions, with zero structural differences
and 31 operand differences (align_diff classification: seven memory, 24
register). All differences disappear under a mechanical ESI/EDI exchange.
Retail keeps `this` in ESI and `slot` in EDI; the bank reverses those roles.
`residue.txt` records every difference. No better body was found, so this
session does not overwrite the bank or add another partial header.

There are 5,275 generated variants, 5,271 successful compiles, four ordinary
probe compile errors, and no exact match. Of the compiled trials, 448 leave a
new helper call because the requested whole-body inlining did not happen;
those are explicitly unresolved, not scored as valid near matches. No game
source, ledger row, pin, gate or baseline was changed. No additional function
was selected. This is evidence for continuing this same assignment.

## Inputs and checks

BFME2 HEAD before this evidence commit is
`7e7bb10b525f054146123a043077fed3a807635d`; its verified BFME1 pointer is
`42bba2ddbd5cb895d99293583891d3b7315fa49e`. `results.json` contains source,
control, compiler and compiled-body hashes, family counts and compact outcome
histograms. All new trials use those reference inputs, not the previous
session's 37c3022 cache. Flags remain the bank's `/O1
/Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB`, with
STLport and repository MSVC 13.10.3077 under Wine.

Target identity, ABI and layouts remain those of the earlier bank investigation:
RVA 0x004404AC, extent 526, ECX receiver and bool/int arguments, slot clamp,
observer/map tests, GUI arrays, rules +0x15C/+0x160, GameInfo virtual slots
+0x30/+0x34 and preview receiver +0x60. No new donor name or original source
spelling is asserted. All sixteen baseline calls resolve to established
rows/pins; no missing function blocks the attempt.

At session start: nonrecursive upstream pull, `check_csv.py` (98,065 rows),
published link-index fetch, claim, and `find_declared_unmatched.py` on the
unchanged home all passed. A live BFME1 updater lock owned by `claudec2`
prevented this seat from starting a concurrent pointer update; the submodule
stayed clean at the committed verified pointer. Do not remove that other
seat's lock. Use `git -c submodule.recurse=false pull --rebase origin master`
in this checkout: the previous session documented an unwanted nested rebase
from a recursive pull.

## Prior exclusions reviewed before editing

Read pick-hard history plus the 20261019 worker, 20261020 visibility,
20261021 WB frame and 20261022 allocator-cost handoffs. Those already tested
common loop/guard forms, scopes and names, inline rules/validity/map accessors,
getter/copy-ctor visibility, destructor visibility, compiler profiles,
declaration-count scans and the existing permuter. The last session also
exhausted the documented exception, qualifier, rule-view, accessor-layer,
receiver-alias and preview-address families. Those are not fresh hypotheses.

The starting hypothesis here was the previous handoff's concrete next step:
measure individual block contributions, rather than just sorted-list inputs.

## Read-only C2 trace: the new finding

The compiler was not modified, and no debugger write was used. WineDbg only
read the running compiler. At candidate-list insertion from return site
`0x1078474f`, baseline `this` has priority 41 and 12 references; `slot` has
priority 49 and 14 references. `block-costs.json` records all initial candidate
insertions and every contribution to this/index priorities across 53 blocks.
The summed contributions reproduce the insertion priorities exactly.

Trace sites in this c2.dll (fixed image base 0x10700000):

- `0x10760539`: function entry; EAX points at the backend function, word 0
  points at the frontend symbol, whose word 1 names the function.
- `0x10782897`: block boundary, before live-candidate popcount. Stack +0x20
  is the CFG block, +0x24 its frequency. Candidate-list counts and live bits
  determine the scaled factor subsequently in EDX.
- **Both** `0x10782919` and `0x10783a45`: positive contributions. EAX is the
  candidate record; record word 6 times EDX is added to word 3 (priority).
  Tracing only the first site misses most positive costs.
- `0x10783a7b`: subtract EDX for a live candidate unreferenced in this block.
- `0x10782b26`: insertion; record words 0/3/9/17 are backend symbol,
  signed priority, reference count and candidate ID. Symbol word 7 is its ID.

The late flag computation is expensive for the receiver's live range:
blocks 41..52 subtract **17** from `this`; the final preview block 53 adds
only three. The slot's last reference is the local-slot comparison, block 40.
Other useful anchors are block 7 (observer/combo), 15 (handicap), 21 (hero),
22 (hero rule), 29/30 (hero handlers), 31 (player template), 33/34 (team).
These ordinal anchors refer specifically to the bank's traversal.

The early-slot-copy control from the older session explains the role flip.
Immediately after the getter, before the game-null check, insert
`int index = slot;` and use index thereafter. Its final priorities are
`this=49`, corrected `index=44`, original `slot=10`. In block 1 the scaled
factor changes from three to five: the receiver's existing cost four
contributes 20 instead of 12, an eight-point gain. Blocks 2..6 split the
original/corrected index contributions; after block 6 their receiver costs
are identical to the bank. The control gets the desired roles but moves the
slot save/load and restoration across the null branch, so it is not a match.
`controls.py.txt` reproduces it; do not bank it as an improvement.

This narrows the problem to candidate/lifetime costs. It is not evidence of
another missing call, a layout error, or a required compiler modification.

## New families tested

Each family was compiled once in parallel with eight workers and scored over
its complete emitted extent, with relocations resolved. The saved generators
and histograms distinguish changed code from baseline twins.

| Family | Trials | Finding |
| --- | ---: | --- |
| Corrected-index clamps | 160 | Twenty clamp forms, four types, two declaration placements. 140 baseline twins, sixteen same-size structural changes. Four predeclared ternary forms fail to compile; no gate false reject. |
| Concrete small callees | 486 | Opaque, strong noinline and inline-noinline definitions of getConstSlot, isAI, isObserver, getter and combo copy constructor, before/after target. 324 baseline twins; 162 bodies are 522 B with two structural regions. |
| Inlined existing regions | 1,024 | Five regions independently extracted into member/static helpers with value/reference arguments and placement choices. All baseline twins. |
| Additional compiler settings | 17 | EH variants, alias settings, Og-/Oi-, debug-information and remaining listed switches. Fifteen baseline twins; two changed bodies. No change to bank flags. |
| Guard/exit graph | 1,024 | Eight clamp graphs, eight validity checks, null/local-slot exits, AI goto and explicit preview exit. 896 baseline twins, 128 same-size structural changes. |
| Receiver base types | 256 | Integer/pointer/reference aliases, eight placements and four use groups. All baseline twins. |
| Typed array wrappers | 512 | Five fixed-array wrappers, index argument types and equivalent subscript forms. All baseline twins. |
| Valid-receiver assumptions | 256 | Subsets of already-valid receiver checks at eight sites. All baseline twins. No assumptions added to bank. |
| Real hero handler context | 162 | Actual rowed HandleHeroSelection and UpdateHeroDisplay bodies, visibility, placement and order. All baseline twins. |
| Concrete preview/providers | 162 | Concrete 0x70-byte preview member versus view, plus real preview, winEnable and HideList definitions. All baseline twins. |
| Whole-body helper | 448 | Parameter order, value/reference arguments, static/member, one/two layers and placement. Compiles, but C2 leaves the EH-bearing helper out of line; every trial has an unresolved new helper call. |
| Local pointer reads | 576 | Every subset of nine game-pointer reads, then subsets of five hero reads and team test. Only two baseline twins; others change loads/code. Best changed game trials are 527 B, still wrong roles. |
| Initial slot reads | 64 | Subsets of four existing clamp reads, with equivalent equality forms. No improvement; qualifications add loads or alter allocation. |
| Argument-home aliases | 128 | Eight stable argument-address representations, four placements and four use groups. None improves the bank. |

The real callee definitions come from current matched providers. Their use
here is a compiler-context trial, not a new recovery of those bodies or a
claim that retail compiled every provider in this unit. Concrete preview
layouts retain the known offsets and 0x70 member extent.

## Reproduction and continuation

Copy the `.py.txt` scripts to fresh ignored `build/4404ac-blockcost/` with
`.txt` removed. Adjust ROOT/OUT if using another seat. The compiler driver
uses `build.compiler_command`, never `build.compile_source`; objects stay
isolated. The scratch source-equality shortcut is valid only within these
fixed inputs: delete scratch objects when source, flags, headers, reference
revision or compiler changes. The full-helper unresolved calls are deliberately
recorded and never qualify as matches.

For traces, run `controls.py` to create `bank.cpp` and `early.cpp`, then run
`trace_blocks.py bank` and `trace_blocks.py early`.
The included `wdbg.py.txt` is the read-only helper with this checkout's ROOT.
Raw debugger logs and thousands of objects stay ignored; the compact trace
contains the useful candidate costs and verifies their sums.

The ~30-minute reassessment now has concrete trials for control flow, lifetime,
types/layout, actual callee visibility and settings. Preserve the bank. A next
session should investigate C2's entry/null-branch web merging using these
specific block factors, or explain the two WB /Od unused dword homes with new
source/header evidence. Do not repeat the broad spelling, qualifier or
visibility sweeps above. In particular, an early value copy is already known
to move the wrong instructions, and whole-body inline extraction is blocked
by the actual emitted helper call.

Final ledger/frozen-file checks, progress measurement, claim release and commit
are recorded in the session log/runner metadata. No byte gate success is
claimed for this nonmatching body. Model: gpt-6.1-sol.
