# FXShaderGeometry::Init: origin of the remap allocation priorities

2026-10-22, codexb2. Target `0x0018C84E..0x0018D16B`, 2333 bytes.
Input BFME 2 `8600a9442a`; verified BFME 1 inputs
`37c3022de1ab944c7ffe536440d637dc8199091c`. See `measurements.json`
for the incoming bank hash and trial summaries.

## Best body and remaining work

The retained bank still emits **2333 bytes, nine differing bytes in seven
instructions, EH EXACT, zero unresolved calls**. Its score remains
`0.9961423060437206`. Only its handoff-link comment changes. A fresh private
compile reproduced its bytes and relocations. Nothing was landed in `Code/`;
no pin, gate, inline assembly or compiler-state modification was used.

The residue is the same EAX/ECX remap-base/link-pointer role swap at
`+0x707..+0x721` described in
`../fxinit-schedule-20261022/readme.md`. That handoff also establishes that
allocation precedes the final scheduling difference. The signed-short
constructor prerequisite is already solved; do not revisit it.

**Next task:** identify the extra live records in the link-pointer split
(serials 644/645 and anonymous records in the diagnostic below), and the
whole-loop uses/splitting that produce them. Seek equivalent source that
changes those live ranges while preserving the bank's native two-bone arm,
early position comparison and in-arm copies. The simple guard, alias and
relative-address families below did not achieve that. The current evidence
does not justify another final-scheduler operand-order sweep.

## New measured fact: how 60 and 48 are calculated

Read-only breakpoints on stock MSVC 13.10.3077 c2 observed the actual writes to
candidate `+0xC` (the allocation priority used in the previous handoff).
Compiler RVAs are relative to the DLL loaded at `0x10700000`:

- `0x82133` counts bits in a linked bitset; `0x82897` calls it to seed EAX.
- `0x828C2..0x828D4` adds the length of the definition list at stack `+0x1C`.
- `0x83A3C..0x83A43` adds live-list entries with flag `0x100000` set.
- `0x828E4..0x828ED` multiplies that count by the block weight at stack `+0x24`.
- `0x82919..0x8292A` and `0x83A45..0x83A56` add
  `candidate[+0x18] * factor` to the priority. The `+0x18` value is a weighted
  reference count/cost, not the number of source expressions.
- `0x83A7B..0x83A7D` subtracts the factor on the observed unused-live path.
  There is also a mode-dependent subtraction at `0xC21CE`; this is not a
  complete specification of the allocator.

For the remap-base candidate 51, both inputs have reference cost 6 and block
weight 1. The initial bitset contribution is zero. Both have three definition
records (105, 113, 51). The bank has seven flagged live records, while the
successor diagnostic has five, giving **6*(3+7)=60** versus **6*(3+5)=48**.
The two removed live records are candidate 29 (serial 405, reference cost 1)
and candidate 1 (serial 0, reference cost 0). Their interpretation as the
second-position pointer and its condition flag follows the changed source
and the block's position-null comparison; the raw records themselves have
no readable names. Preserve this distinction between observation and inference.

The other initial flagged records agree: 161/160/159 (reference cost 3 each),
143 (the link pointer, cost 12), and 27 (`vertices`, cost 6). Thus this is a
specific live-range difference, not merely a different temporary number.

## The pointer is scored again after splitting

The split pointer records that the previous color trace observed being
assigned are created by the same cost routine:

| Input | Candidate | Reference cost | Factor | Priority |
| --- | ---: | ---: | ---: | ---: |
| Bank remap base | 51 | 6 | 10 | 60 |
| Bank link-pointer split | 175 | 6 | 6 | 36 |
| Diagnostic remap base | 51 | 6 | 8 | 48 |
| Diagnostic link-pointer split | 174 | 6 | 9 | 54 |

At those pointer updates there are two definition records and an initial
bitset contribution of two in each input. The bank has two flagged live
records: 129 (serial 0) and 130 (serial 647). The diagnostic has five:
130 (644), 129 (0), 128 (645), 109 (0), and 131 (647). This accounts for
factors 6 and 9. `observations.json` preserves these records and the base
updates. Later ranges of the same original pointer also receive costs;
not every later record is the two-bone range that the color trace assigns.

The original whole-loop pointer initially finishes at priority 73 in the
bank and 47 in the diagnostic. Those whole-loop candidates subsequently
split; comparing those two initial numbers alone does not explain the
chosen registers. In particular, the base retains its early score while
new pointer ranges are scored against a changed set of live candidates.

The diagnostic is the previous `pn_300000`: copies in the common successor,
2326 bytes, wrong copy scope/layout. It is **not a bankable solution**. Its
only purpose here is to explain the known register flip. Both completed
cost-traced objects have exactly the same function bytes and relocations as
their ordinary compiled inputs (`bank-verification.json`).

## New families excluded

History was read only through `/opt/runner/pick-hard --rva 0x18C84E`; prior
handoffs and relevant `docs/recipes.md` examples were reviewed before trials.
The source families below target alias lifetime, guard representation and
remap-base uses rather than repeating the previous P/N-hoisting sweep.

| Family | Generated | Concrete scope |
| --- | ---: | --- |
| guards | 256 | Selective volatile reads of eight existing guards |
| aliases + aliasesscope | 576 + 252 | Pointer/reference aliases, four scopes, one-/two-bone uses, high-link delta |
| postypes | 288 | Position/normal pointer arrays, paired fields, integer/volatile fields, guard forms |
| posflags + posflagsscope | 336 + 48 | Actual P/N predicates cached in bool/integer locals at seven scopes |
| guardhelpers | 864 | Return/parameter types, inline/null predicates, conversion wrappers |
| cursoruse | 512 | A link cursor reused across six link/weight/P/N expressions |
| mapbase | 512 | Volatile or ordinary remap-base loads, value/reference locals, scopes and R/W order |
| relativebase | 256 | One mapped address reused for the other bone through a signed index difference |
| relativecancel + relativecanceltypes | 768 + 128 | Typed/byte/integer pointer algebra, eight equivalent offset trees, staging and references |

There were **4796 generated trials, 4328 compiling and fully resolving**;
none improved the bank. These are generated combinations, not 4796 unique
machine-code results. Compiler errors and extent/unresolved results are
separately recorded in `measurements.json`; they are not gate false rejects.
An early abbreviated loop-token replacement hit the helper before Init
(252 alias and 48 flag trials), and an unsigned-reference spelling failed
in 128 cancellation trials. The corrected subsets were rerun separately.
The saved generator fixes these mistakes; historical failure counts are
retained honestly. The remaining 32 map-base trials also failed compilation and were
excluded; eight flag trials had extent/resolution failures.

`relativebase_10000001` gets retail's first five remap instructions, but
retains extra `lea/sub` address arithmetic and changes the result register
and store schedule. It is 2337 bytes with 496 full-body differing bytes
(offset shifts included), and is worse than the bank. Its small patch is
preserved for diagnosis. The wider cancellation family did not remove the
arithmetic while retaining the desired registers.

Control flow/loop entry, variable lifetime/scope, types/layout and callee
inlining were concrete axes here. Prior compiler-setting sweeps and the
WorldBuilder source-shape correction were reviewed, not repeated. WB's actual
P/N copies remain inside the two-bone arm, after the weights; the earlier
A3A22C/A3A251 copies were tangent/binormal. No missing callee blocks this bank.

## Reproduce

Use stock MSVC 13.10.3077 under Wine and the bank flags
`/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`. All trials use private objects;
none calls `build.compile_source` or modifies the shared match cache.

1. Restore the previous handoff's `search.py.txt` into
   `build/fxinit-seat22/search.py`. Restore its `wdbg.py.txt` into
   `build/netpacket-20261022e/wdbg.py` (the import path used by the tracer).
2. Copy this handoff's three `*.py.txt` files into `build/fxinit-cost22/`,
   removing `.txt`. Run `python3 build/fxinit-cost22/search.py FAMILY` from
   the repository root. The generator uses eight compile threads.
3. `guards_000.cpp` is an unchanged bank control. Regenerate the prior
   `pn_300000.cpp` only in scratch using its preserved diagnostic patch.
4. Run the following read-only traces, with private output paths:

```sh
python3 build/fxinit-cost22/cost_trace.py build/fxinit-cost22/trials/guards_000.cpp build/fxinit-cost22/baseline-cost-v3.obj
python3 build/fxinit-cost22/cost_trace.py build/fxinit-seat22/trials/pn_300000.cpp build/fxinit-cost22/successor-cost-v3.obj
```

The tracer filters candidate 51 and symbol serial 647 for these exact
inputs. Rediscover these IDs after material source/compiler changes.
For `verify_bank.py`, first copy the current bank to
`build/fxinit-cost22/bank_reverified.cpp` and ensure the ordinary `guards_000`
object exists. The verifier recompiles the bank privately, resolves its
complete body, checks EH and compares the old/new bytes and relocations.

Session housekeeping: ledger check passed and the published object index was
fetched (newer local index retained). BFME 1's update lock was fresh and owned
by `claudec2`, so this seat retained the verified pointer and recorded no new
freshness success. The pull fetched official upstream `aef2f168`; updating the
pointer belongs to that other seat. Broad reference/dump queues were skipped
under the explicit standing assignment. Continue this body next session.
