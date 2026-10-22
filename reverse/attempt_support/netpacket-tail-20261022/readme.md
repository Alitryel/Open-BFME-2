# NetPacket::getCommandList: exception and lifetime factorials

2026-10-22, gpt-6-astra, runner seat codexb2. Still partial. The best body is
the existing barrier-free bank with 18 stale reader names replaced by the
current ledger names at the same addresses. No production source or matching
row changed. There is no new code-generation improvement.

Inputs: BFME2 `cc801b33096ea96d50213748eeda5c1533412b49`, BFME1
`37c3022de1ab944c7ffe536440d637dc8199091c`. The BFME1 update lock belonged to
another active seat, claudeb3; this seat skipped that update as instructed and
did not write a freshness-success stamp. The initial ledger check passed.

## Current result and reproduction

The complete target is `0x00593F15..0x005944D8`, 1475 bytes: 1351 executable
bytes plus the 124-byte switch table. The picker extent is stale. Normal
`tools/explain_mismatch.py` independently confirms equal 1475-byte sizes and
the first difference at `+0x508` / `0x0059441D`. Fully resolved comparison
finds exactly seven differing bytes, no unresolved relocations, and no other
difference, including the switch table. EH verification returns `EXACT`.

The rebanked score is **1468/1475 = 0.9952542372881356**, literal resolved-byte
agreement. `permute.fitness` reports **0.9980172808694141** on these same bytes;
these are different metrics. Earlier 0.9826 and unresolved-call scores are
not evidence that these experiments improved instruction selection. Resolved
body SHA256: `c2f50c1fb2afd479eb03ce479f505d004ac98a5251c0efa07836076007cf838c`.

At Z's tail, native reloads `this` into EBX and jumps back to D's already
correct `mov esi,[ebp-0x14]; jmp loop_check`. The bank reloads ESI, then EBX,
then jumps straight to the loop check. The native and candidate tails occupy
the same eight bytes. See `resolved-tail.txt` for the actual bytes and branch
destinations. This is still a failed full-byte match, despite exact EH data.

```sh
python3 tools/explain_mismatch.py '?getCommandList@NetPacket@@QAEPAVNetCommandList@@XZ' --rva 0x593F15 --size 1475 --source reverse/attempts/0x00593f15.cpp
```

The candidate belongs in the actual NetPacket home only after this residue
is fixed; do not land the bank or narrow its extent to evade the mismatch.

## Prior evidence respected

Read the picker history and `../netpacket-tail-20261020/readme.md` first.
Previously disproven: the tail factorial, common loop/break/continue/goto
forms, declaration permutations and dummy locals, the full current home with
all readers visible, exact ctor/dtor/detach providers, ACK inheritance by
itself, length accessors, G5/G6/G7 and SP1/DDK profiles, the single
address-taken index by itself, and intrinsic memcpy by itself. No repeat
permutation scan was run. Reused source choices below test new combinations
or provide controls, not new claims about those old hypotheses.

The new initial hypothesis was the documented EH-alias lever: an opaque
throwing callee could keep the wrong alias set live and change reload
placement. Constructor exception specifications do alter frame/code shape;
ordinary callee specifications do not fix the tail.
Independent EH checks on masks `002`, `080`, and `082` (ref constructor,
ACK constructors, both) all report `bytes_differ` in `.text$x` and `.xdata$x`;
the unchanged control is `EXACT`.

## New trials

3864 generated variants, 3824 successful isolated compiles, 40 compiler
rejections. Each object has a unique scratch path; none overwrites the shared
match cache. Eight workers compile per family. Every successful result is
relocation-resolved against the full target, and the best remains the bank.
`measurements.json` records counts, sizes, hashes and best scores per family.

| Family | Variants | Independent choices and result |
|---|---:|---|
| `throw` | 512 | Nine binary declaration groups: detach, ref ctor, ref dtor, addMessage, command-ID predicate, ACK getters, ACK setters, ACK ctors, readers. Four code shapes. Ordinary `throw()` changes are inert; ref/ACK ctor changes produce 1444/1416/1391-byte bodies and lose correct EH/frame shape. |
| `single-throw` | 512 | Same nine choices crossed with WB's single address-taken index form. Four shapes; best 1487 bytes, fitness 0.904432. No exception-specification rescue of the single-index form. |
| `helpers` | 200 | Force-inlined Z completion at four boundaries, value/reference arguments, return void/ref/index, restore index inside/outside, apply to D too where the tail is identical. 24 shapes; no improvement. Some nearest alternatives move a lastCommand store, not the needed reload. |
| `self-aliases` | 336 | Explicit this pointer/const pointer/reference/const-reference aliases in four scopes; independent packet/length/dump uses; signedness. Two shapes; no improvement. |
| `typed-acks` | 256 | Four typed-pointer/lifetime forms for each ACK class, helper extraction, inheritance. 27 shapes; no improvement. |
| `cursor-types` | 120 | Scalar versus one-field struct/union cursor, index unification, ushort command ID, scoped const references and force-inlined index accessor. Two shapes; no improvement. |
| `memcpy-alias` | 120 | Single/two-index forms, CRT versus explicit memcpy declaration, intrinsic/function pragma ordering, /Oi, /Oi-, /Ob1. 80 compile; 40 `__declspec(noalias)` variants fail with VC7.1 C2485. Four successful shapes; no improvement. |
| `copy-lifetimes` | 729 | On WB's single-index form, independently retain each of six memcpy arms or capture its post-increment index before the call in either of two ways, then restore after it. All 729 shapes distinct; best 1488 bytes, fitness 0.930151. |
| `mixed-factorial` | 512 | Recombine typed ACK choices, inheritance, three completion helpers, this alias, short command ID and const index reference. Six shapes; no improvement. |
| `member-accessors` | 324 | Member/free deletion wrappers, member/direct ref and relay getters, combined/separate timing setters, allocation factory scope and enum type setter. Two shapes; no improvement. |
| `placement-new` | 243 | Per class (list/ref/three ACKs), global allocation versus inline class new/delete versus magic-enum placement new/delete forwarding to global allocation. All produce the bank's identical bytes. |

These cover new concrete tests of control-flow/helper boundaries, variable
lifetimes, types/layout, callee visibility and compiler settings. They do not
prove that every source form in any category is exhausted. In particular, the
negative alias trials do not prove that the original source used two indices.

## Target and donor evidence

The WB twin at `0x154E140` was reread. Its `i` is local `-0x14`; retval is
`-0x1c`, lastCommand `-0x20`, commandID `-0x24`, commandType `-0x25`, frame
`-0x2c`, timestamp `-0x10`, player `-0x16`, relay `-0x15`, commandIDSet
`-0x17`. D and Z both finish with ref construction and detach; both readers
and memcpy arms use the same address-taken index. Assert lines place this
source around NetPacket.cpp 6217..6358. The unoptimised twin establishes
these locals and source operations, not release register allocation.

ZH's getCommandList and the BFME1 GameMemory.h allocation macros were read.
The latter's non-debug newInstance magic-enum allocation forwards to global
new. The last family reproduces that mechanism without importing donor
object layouts. Donor APIs motivated the member-wrapper trials; all are
diagnostic equivalents, not newly established BFME2 class definitions.

## Resume without repeating the search

The unresolved issue remains the release compiler's ordering of an explicit
index restoration versus the allocator's this-pointer compensation reload.
Prior evidence puts that compensation after the block's own instructions.
The explicit helper-return and cursor-alias forms above do not move the
index restoration into the desired successor/fixup. There is no identified
missing callee to claim or `blocked-on` dependency. Continue on this body
with a new supported CFG/lifetime or real-header hypothesis; do not repeat
the ordinary throw-specification factorial or the old permutation meter.

The eleven small generator sources are preserved as `.py.txt` under
`generators/`; they are diagnostics, not game sources or new tooling. To
reproduce at these input revisions, copy them without the `.txt` suffix into
`build/netpacket-20261022/` and run from the repository root. `search.py
baseline` checks the control and `search.py throw` runs the first factorial.
Run `next.py`, `helpers.py`, `aliases.py`, `typed.py`, `cursor.py`, `memcpy.py`,
`copies.py`, `mixed.py`, `accessors.py`, `placement.py` for the other families.
`mixed.py` consumes sources generated by `typed.py` and `helpers.py`.
The driver uses `compiler_command` plus its own object paths, never
`build.compile_source`; its full compiler command is in the measurements.
Preserve the existing bank when resuming. Re-run families only if changed
inputs or new evidence justify doing so.
