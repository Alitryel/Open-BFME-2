# NetPacket::getCommandList: cursor and inline-boundary experiments

2026-10-22, gpt-6-astra, runner seat codexb2. Still partial. This pass did
not improve the existing bank's generated code. The bank is preserved with
its repeated historical score headers consolidated; no production source,
ledger row, pin, or verifier changed.

Inputs: BFME2 `56c82a5980a473e4be5a7d6e53768756a1b1e6b3`, BFME1
`37c3022de1ab944c7ffe536440d637dc8199091c`. Initial pull and ledger check
passed. BFME1's freshness lock belonged to active seat claudeb3, so this
seat deferred the update under the runner rule and wrote no success stamp.
The published link index and available cached objects were fetched.

## Best body and acceptance checks

The full extent is **1475 bytes**, `0x00593F15..0x005944D8`: 1351 code bytes
and a 124-byte switch table. The picker still reports the older 1351 extent.
Normal `explain_mismatch.py` independently confirms equal 1475-byte sizes,
with the first difference at `+0x508` / `0x0059441D`. Relocation-resolved
comparison finds **seven differing bytes**, no unresolved relocations, and
EH verification is `EXACT`. The switch table and every other byte agree.

Literal agreement is **1468/1475 = 0.9952542372881356**. The separate
`permute.fitness` metric is `0.9980172808694141`. The resolved SHA256 remains
`c2f50c1fb2afd479eb03ce479f505d004ac98a5251c0efa07836076007cf838c`.

At Z completion, retail reloads EBX from `[ebp-0x2c]`, then jumps back to
D's `mov esi,[ebp-0x14]; jmp loop_check`. The bank reloads ESI, then EBX,
then jumps directly to the loop check. These alternatives occupy the same
eight bytes. See `resolved-tail.txt`; its instruction ranges are decoded
independently so differing instruction lengths do not shift the comparison.

```sh
python3 tools/explain_mismatch.py '?getCommandList@NetPacket@@QAEPAVNetCommandList@@XZ' --rva 0x593F15 --size 1475 --source reverse/attempts/0x00593f15.cpp
./build.sh Code/GameEngine/Source/GameNetwork/NetPacket.cpp
```

The existing home unit passes **162/162** matched rows, plus string, float
and import-reference checks. This verifies the unchanged home, not the
partial candidate. Do not land the bank or shorten its extent.

## Prior exclusions and new hypothesis

Read the picker history and `../netpacket-tail-20261022/readme.md` before
resuming. The earlier tail factorial, common loop forms, declaration and
dummy-local scans, full home context, exact ref constructor/destructor and
detach bodies, ordinary throw specifications, ACK and getter shapes,
placement allocation, single address-taken index, and intrinsic memcpy
trials were already negative. No ordinary throw or permutation scan was
repeated here.

The new hypothesis was that changing which source value owns the loop
cursor, or where an inline boundary exposes memory effects, could turn the
explicit ESI restore into a split-register reload ordered after EBX's
compensation. The WB twin's single address-taken index is evidence for that
source shape, but the previous single-index candidate changes header code.
New combinations below use that shape as a control, not as a newly found
solution.

## Factorials and results

**2610 generated variants**, **2578 successful compiles**, **2570 scored
bodies**. There were 32 compiler rejections and eight post-compile extent
rejections. Of the scored bodies, 24 whole-parser wrappers retain an
unresolved helper and are unusable; 2546 have all relocations resolved.
All compiles used isolated objects and eight workers. No scratch compile
wrote the shared match cache. `measurements.json` preserves full compiler
flags, counts, best candidates, sizes and hashes per family.

| Family | Variants | Choices and result |
|---|---:|---|
| `visible-memcpy` | 96 | Single/two-index forms, opaque/noinline/visible noinline memcpy, throw specification, pragma ordering, /Oi, ID width. Six emitted shapes; best remains seven differences. Visible byte-loop memcpy changes body and frame shape. 32 intrinsic-definition trials fail C2169 with follow-on C3861; not gate false rejects. |
| `inline-boundary` | 72 | Extract whole parser, after list allocation, or after scalar initialization; member/static helper; pointer cv type; return/out reference; carried cursor; ID width. Six shapes. Whole-parser variants do not inline despite forceinline and leave 24 unusable wrappers. Best usable body has 20 differences at 1475 bytes; tail unchanged. |
| `loop-carrier` | 216 | Persistent cursor with iteration-local index, declaration scopes, common/per-arm updates, condition order, duplicated offset assignment, D/Z copies. Ten shapes; best is the unchanged bank. |
| `aggregate-state` | 372 | Group i and address-taken offset with subsets of self, lastCommand, ID, IDset and type; field order, local/global type, direct/member accessors. 62 shapes; grouping escaped fields changes frame/register choices throughout. Best literal comparison has 1174 differences at 1517 bytes. |
| `pointer-restoration` | 378 | Independent D/Z cursor recovery via offset, packet-pointer differences, this-relative pointers, integer-address differences, template helper and cached aliases; ID width. Four shapes; algebra mostly folds back to the bank. |
| `reader-boundary` | 144 | Inline D-reader switch with private offset escape; message return/index out, index return/message out, or pair return; initialization order; saved Z cursor; scope and ID width. Eight shapes, all worse; best literal comparison has 980 differences at 1511 bytes. |
| `duplicated-exits` | 480 | Nine D/Z completion forms crossed with while/guarded-do/for and comparison order, duplicating bounds or index assignments at continuation/exit edges. 472 scored, 70 shapes; best 1483-byte body has 232 literal differences. Eight longer bodies have a relocation beyond the real 1475-byte row extent and are correctly rejected. No extent was increased to admit them. |
| `explicit-destruction` | 192 | Inline member/free/reference wrappers or explicit destructor and operator delete; D/Z/both; null guards; visible real destructor; throw; replacement-pointer copy. All 192 emit exactly the bank's bytes. Null deletion semantics are preserved in the final generator. |
| `copy-boundary` | 288 | Inline memcpy wrappers with dynamic, constant-template or deduced-destination argument; void/pointer result; helper local count; independent intrinsic/function pragmas around helper and caller; single/two-index forms. Six shapes; best unchanged. Deduced destination still receives the explicit copy width, including the two-byte command ID. |
| `scalar-state` | 372 | Keep address-taken offset separate while grouping i with subsets of self, lastCommand, ID, IDset and type; field order, scope and member accessor/mutator. 65 shapes, all worse; best literal comparison has 1159 differences at 1517 bytes. |

Literal difference counts on shifted bodies are not alignment scores. The
summary records both; none improves the bank. Generator development errors
and the superseded unsafe null-cleanup / incorrect deduced-copy-width
prototypes are excluded from these final runs and evidence.

These are concrete new tests of control flow, variable lifetime, types and
layout, callee visibility and inlining, and compiler settings. They do not
establish that every possible source form in those categories is exhausted.

## Evidence and next session

The WB twin and BFME1/ZH parser sources were reread. Their single index and
member APIs remain source leads. ZH's actual pool base adds a vptr before
NetCommandRef's message field, whereas the verified BFME2 view accesses the
message at +0. Wholesale header substitution would therefore contradict
target layout evidence. No new missing-function prerequisite was found.

The split-register explanation remains an inference from emitted code and
the compiler notes in `docs/recipes.md`,
`../0x0004826c-draw-headmerge-20261020/README.md`, and
`../0x005881db-c2trace-20261021/README.md`; no C2 trace was run in this pass.
A focused trace comparing the bank and the WB single-index diagnostic could
identify exactly which web/split edge creates the ESI versus EBX restores.
That would distinguish an allocator-lifetime issue from a pre-allocation
tail-merge issue before more broad source scans. Stay on this body.

The best remains `reverse/attempts/0x00593f15.cpp`. Small diagnostic
generators and the scoring driver are preserved in `generators/`. To
reproduce, copy them without `.txt` into `build/netpacket-20261022b/` and run
from the repository root. Run each of `memory.py`, `inline.py`, `carrier.py`,
`state.py`, `pointer_restore.py`, `reader_boundary.py`, `loop_exit.py`,
`delete_lifetime.py`, `copy_boundary.py`, and `scalar_state.py`; each generates
its own inputs. `regions.py FAMILY...` examines completion instructions.
The driver uses `build.compiler_command` and explicit private object paths,
then relocation-resolves them with `build.compile_function`; it never calls
`build.compile_source`. Do not rerun these unchanged families without new
input evidence. Nothing from these diagnostics is production source.
