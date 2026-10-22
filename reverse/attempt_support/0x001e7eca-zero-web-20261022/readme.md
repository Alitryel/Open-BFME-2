# Locomotor 0x001E7ECA: zero-web allocator trace, 22 October

The best C++ body remains `reverse/attempts/0x001e7eca.cpp`, score 0.975.
It emits 1567 bytes against the proven 1563-byte extent (1527 code plus
36 bytes of jump table). No matching body or new Code source was landed.
This session tested 3712 source/settings variants in 14 families, with no
compile errors and no improvement over the bank. The new result is a
reproducible explanation of the integer allocator's two remaining decisions.

Inputs: BFME 2 cc801b3309; BFME 1 checkout and committed pointer
37c3022de1ab944c7ffe536440d637dc8199091c. The freshness update was owned by
another runner seat (`bfme1-update.lock/owner`: claudeb3), so this seat followed
the runner's instruction to skip that update. Ledger validation passed:
97945 function rows, 15928 pins, 1386 data rows. The assigned body was claimed
before work. Earlier history was read through `pick-hard --rva` only.

## Residue and measurement

Symbol: `?rva001E7ECA@Locomotor@@QAE_NPAVObject@@PBUCoord3D@@@Z`.
Flags: `/O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc`; the bank names its include paths.
The isolated baseline's raw COFF symbol SHA-256 prefix is `e1e741da4121`.

`final-align.log` is the normal `tools/align_diff.py` report with object-store
reuse disabled. It retains the five real structural regions and four register
differences. Its jump-table disassembly and unpatched absolute operands add
noise. `final-mismatch.log` independently confirms 1567/1563 and the first
displacement difference at +0x52, caused by the later four-byte size delta.
Neither report is a passing byte gate.

The small search scorer stops at RET 8 and ignores relocated absolute operands,
direct-call addresses and branch displacements. The baseline scores 12:
5 structural instructions, 4 register operands, 3 memory operands. Case 1
accounts for 8 and case 6 for 4; the rest of the code scores zero. This metric
is for searching, not admission or a replacement for full byte verification.

* Case 1: ours defines EDI=0 for two underwater arguments and the layer normal
  argument, spilling the layer vptr to `[ebp+0xc]`. Retail pushes three literal
  zeros and keeps that vptr in EDI. This costs ours five bytes.
* Case 6: ours defines EDI=0 before the ground normal argument. Retail pushes
  that argument as a literal zero and first defines EDI=0 at the mask ctor.
  Ours is one byte shorter here, leaving a net four-byte excess.

All 22 direct callees are matched. No missing callee currently blocks this body.
The original method spelling is still unknown; the bank's donor provenance and
independent target layout evidence remain authoritative. No names or pins were
added in this session.

## New allocator evidence

`trace_rounds.py.txt`, `trace_split.py.txt`, `trace_costwrites.py.txt` and
`wdbg.py.txt` drive the pinned RTM c2.dll through Wine's debugger. The DLL is
never modified on disk. The harness checks SHA-256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
An unmodified observed compile is byte-identical to the ordinary baseline.

The single integer zero candidate still exists after the initial ordering.
It splits during integer colouring, rather than initial CSE or setup:

| Round | Zero index | References | Cost | Meaning |
| --- | ---: | ---: | ---: | --- |
| 1 | 3 | 22 | 11 | Initial zero |
| 2 | 38 | 18 | 9 | First split |
| 3 | 4 | 2 | -4 | Unprofitable piece |
| 3 | 7 | 3 | 1 | Case 1 |
| 3 | 8 | 6 | 2 | Case 6 |
| 3 | 11 | 2 | -2 | Unprofitable piece |
| 3 | 13 | 4 | 1 | Another region; not case 1 |

In round 3, colour order includes 8, 13, 11, 7, 4. Zero candidates 7, 8
and 13 survive. `rounds.json` and `baseline-rounds.log` retain the observations.
`costwrites.json` keeps the raw tuples at every zero-cost write and all colour
candidates, for further decoding. Case 1's cost starts at -2 for its reload
and gains one at each of its three PUSH uses, ending at +1.

Three **diagnostic interventions**, applied only to the debugger's in-memory
candidate cost before colouring, establish causality:

| Forced cost=0 | Emitted size | Search score | Case 1 | Case 6 | Other |
| --- | ---: | ---: | ---: | ---: | ---: |
| index 7 | 1562 | 4 | 0 | 4 | 0 |
| index 8 | 1569 | 15 | 8 | 7 | 0 |
| index 13 | 1568 | 17 | 8 | 4 | 5 |

Thus disabling candidate 7 produces retail's instruction/operand choices in
case 1, with relocation/branch positions normalized. Disabling all of candidate
8 also destroys the required later zero web and makes case 6 worse. The desired
case-6 change excludes only its first ground NULL. A diagnostic change of the
initial candidate's post-order priority to -1000 was inert; the later pieces
get their own priorities. **These modified-allocator objects are not banked,
are not matches, and must never be landed.** The tracked scripts retain the
optional intervention solely to reproduce these causal observations.

Useful c2 offsets (base 0x10700000): after first costs 0x83acd; per-round
filter 0x82978; colour candidate 0x82a4d; finished 0x82273. Cost writes:
0x82692 source, 0x84c3e definition, 0x8281c reload, 0x8cb73 store.
Globreg records: index +0x1c, refs +0x24, hash-chain next +0x30, cost +0x40.
There are 1024 hash heads at 0x108807b8. A zero's anonymous symbol begins
`[0,0x100d]`, its operand is at symbol +0x28, operand opcode is 0x24b,
and operand words 4..6 are all zero. Some other constant candidates have the
same symbol prefix; test the operand too.

Wine loses some deferred breakpoints if many are set before c2 loads. The
scripts set one deferred breakpoint, then arm the rest after the first hit.

## Source hypotheses tested

`families.json` records actual counts (some older scratch labels overstate
their counts). All generators and the scorer are preserved as `.py.txt`.
The baseline is a control in several factorial families; the new work was in
their combinations, not a claim that previously rejected single choices were
new discoveries.

| Family | Trials | Tested choices | Best score |
| --- | ---: | --- | ---: |
| cfg128 | 128 | Duplicate sea tails/requires stores, inverted tests, outer guard, water scope, inline query wrappers | 12 |
| inline64 | 64 | Entire building query as inline helper, pointer/reference result and position, loop/lifetime forms | 128 |
| sea64 | 64 | Entire sea arm as inline member, pointer/reference position, result versus mutation | 12 |
| access256 | 256 | WB getter chains, kind mask, disabled/speed/height/behavior/damping getters, visible Object layer getter, pointer translation setter | 12 |
| life1024 | 1024 | Coord3D identity, height local, loop entry/increment, highest scope, max ternary, case labels and exit form | 12 |
| layer128 | 128 | Layer-query timing/scope, visible layer getter/body/throw, ground result and highest timing | 12 |
| flags288 | 288 | Optimization, global-CSE, inlining, debug info, frame pointer, floating consistency combinations | 12 |
| eh256 | 256 | Exception specifications across result/copy/dtor, mask/filter ctor, query, iterator, height/layer callees | 12 |
| bits128 | 64 | Mask first-argument enum/bool/signedness, actual mask-ctor visibility, query and layer enums | 12 |
| cpu384 | 192 | G3/G4/G5/G6/G7/GB, O1/O2 plus size/speed, SSE/SSE2, intrinsic and inline settings | 12 |
| identity512 | 256 | 64-bit NULL constants, pointer qualifiers, pure virtual declarations and receiver identity combinations | 12 |
| realflags256 | 256 | Actual STLport bitset operations, bool tests, Object disabled, model/kind/Locomotor flags, behavior enum, Ob2 | 12 |
| visible-last16 | 16 | Faithful visible 0x1E5F1D and 0x1E6532 bodies, ordinary/noinline-inline, before/after target | 12 |
| order720 | 720 | All permutations of the six non-early-return case blocks | 12 |

The whole-query helper always outlines despite forceinline, so it changes the
call structure and cannot solve this residue. The visible-last16 family is
byte-identical in every variant. The full bitset family produces other code
differences in some combinations but never improves these zero webs. Every
case-order variant still pushes EDI for both underwater zeros and the ground
NULL; none changes either web, independently of its changed code layout.

This covers concrete trials of control flow/loop entry, variable lifetime,
types/layout, callee visibility and compiler settings. Do not repeat the
earlier NULL-identity, local-numbering k-scan, terrain throw/const, or same-unit
helper trials documented by the earlier banks.

## WorldBuilder correction and remaining angle

The full `wb_show.py 0x001E7ECA --raw --max-lines 2000` listing of the
0xAEB870 / 4953-byte twin **does contain case 6**. The 20 October zero-web note's
statement that it does not is incorrect. It passes ground normal=0, keeps a
named range=1 and highest=0, builds the temporary mask/filter, calls the query,
and loops through next/max-height, consistent with the bank's source shape.
The sea arm also visibly passes literal zero arguments. This is a different
revision and supplies structural evidence, not byte proof.

Next useful work is earlier in the split/reload machinery or the later local
allocation around the layer vptr. Trace why the first ground NULL stays in the
same piece as the later query zeros, and how a source-level live-range split
could exclude it without losing the later web. The cost arithmetic explains
the current choice but does not yet establish the original C++ or a valid fix.
Do not treat the diagnostic cost edit as such a fix. Permuting only register
names is premature while these structural insertions remain.

## Reproduction

Create `build/locomotor-zero-cfg/`, copy the `.py.txt` files there without their
`.txt` suffix, and copy the bank to `base.cpp` and `baseline.cpp`. Extract the
1563 retail bytes at 0x001E7ECA to `retail.bin` with the build module's image
reader. Run a selected generator with Python; each compiles unique scratch
source/object paths in eight threads using `compiler_command`, never the
shared `compile_source` cache. `search.py` also scores existing objects when
its source argument is None. The trace scripts run against `baseline.cpp`.

Ordinary final checks:

```sh
python3 tools/check_csv.py
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameLogic/LocomotorHeight.cpp
BFME_OBJSTORE=off python3 tools/align_diff.py build/locomotor-zero-cfg/baseline.cpp '?rva001E7ECA@Locomotor@@QAE_NPAVObject@@PBUCoord3D@@@Z' 0x001E7ECA 1563
BFME_OBJSTORE=off python3 tools/explain_mismatch.py '?rva001E7ECA@Locomotor@@QAE_NPAVObject@@PBUCoord3D@@@Z' --rva 0x001E7ECA --size 1563 --source build/locomotor-zero-cfg/baseline.cpp --context 8
```

No maintainer-only verification runner was started. The claim is released when
this evidence is banked; the next session should reclaim the same assignment.
