# FXShaderGeometry::Init: used flags and a valid pointer-value diagnostic

2026-10-23, codexb2, gpt-6-astra. Target `0x0018C84E..0x0018D16B`,
2333 bytes. BFME 2 input `495df77f5f`; clean verified BFME 1 checkout/pointer
`f890413e75e671748215ba2ef3304aa7953993e9`. Stock MSVC 13.10.3077,
`/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`.

The bank remains **2333 bytes, nine differing bytes in seven remap instructions
at +0x707..+0x721, EH EXACT, zero unresolved calls**, score
`0.9961423060437206`. A fresh private compile equals the preceding bank's
complete bytes and relocations. Only the bank's date/handoff comment changes.
No production source, row, pin, compiler, gate or baseline was changed.

## Continue here

The prior handoff's admission question is answered below: both inputs carry
47 live records; the position comparison changes their **used flags**, not
membership. A volatile-qualified guard removes one contribution, but its
base cost of 54 still precedes the 36-cost pointer split. Do not repeat the
admission trace, setup duplication, helper-ABI or qualifier families below.

A new, semantically scoped diagnostic gives retail's remap register roles
**without moving P/N outside the two-bone arm or moving the early P test**:
`valuebundlesafe_0000110.patch`. It is 2345 B, with 883 differing positions,
so it is worse overall and must not replace the bank. It passes a real
three-pointer value (remap base, link0, link1) by value to an inline pack
helper. The value is initialized at the start of the vertex iteration.
Every field is used; there is no inert padding or object overlay.

Its remap base is read from an additional home at **EBP-0x124**, versus the
bank's remap vector start at **EBP-0x58**. The two MOVSX base operands identify
compiler symbol `0xC3E3D4` as that copied map pointer. Its initial cost update
is **-43 + 6*10 = 17**, whereas the bank's base starts at zero and reaches
60. The copied base then splits: candidate 176 and link-pointer candidate
175 both receive **6*6 = 36** in round 1. This is a different cost history
from the old common-tail diagnostic. Equal costs alone do not prove the
later coloring order; this session did not trace that order for this input.

**Next concrete investigation:** trace the copied map's earlier negative
cost contributions and its split/coalescing decisions. Seek a source that
retains this allocation effect while using the existing remap home. The
simple reference-field, declaration-position and UV-visibility combinations
below already failed. The extra home belongs to a real value copy, not to
an unidentified external callee. The IR snapshot and first-use tuples in
`observations.json` locate the copied map independently of guessed candidate
numbers. Start from the original bank; use this patch only as a diagnostic.

No missing-callee prerequisite was identified. The previous
[index/context handoff](../fxinit-index-20261023/readme.md) and its linked
history retain all earlier exclusions. WB A39110 supports P/N inside the
two-bone arm after weights. On an exact parent landing, also row its emitted
EH handler and unwind funclets `0x768841`, `0x76884B`, `0x768868`.

## Used flags: observed distinction

Read-only breakpoints in stock c2, DLL base `0x10700000`. All five completed
traced objects equal their ordinary controls in **whole Init bytes and
relocations** (`trace-verification.json`). No debugger writes changed compiler
state. Addresses and candidate IDs below are specific to these inputs.

- At C2 `0x82540`, both original bank and `pn_300000` diagnostic link
  candidates 1 and 29 into the live list in predecessor block `0xC72618`.
- Both have **47** records on the live list at the selected initial remap
  cost update in block `0xC726E0`. There is no separate admission event for
  those two records in this block. Static `0x823D3` code supports reuse of
  the predecessor list; that fast path was not dynamically traced here.
- In the bank, tuple `0xC4B9EC`, opcode `0x2F`, compares the second-position
  pointer with literal zero. C2 `0x826A5` marks both consumed records used
  by setting flag `0x100000`: candidate 29 from `0x00000D02`, candidate 1
  from `0x00008D02`.
- The bank's flagged list is `[161,160,159,143,29,27,1]`, versus the
  diagnostic's `[161,160,159,143,27]`. Both have definitions `[105,113,51]`.
  Base reference cost 6 therefore gives `6*(3+7)=60` or `6*(3+5)=48`.
  Candidate 1 is literal zero, as corrected in the earlier live handoff.

The old `pn_300000` common-tail input remains non-equivalent and unsuitable
for banking. It is only a controlled allocator comparison.

A separate trace of the previously compiled `guards_001` control qualifies
only the existing P guard's pointer read as volatile. Its final bytes still
equal the bank. It does **remove candidate 29's used contribution**, while
candidate 1 remains used. The base therefore reaches **54 = 6*(3+6)**.
The final relevant link-pointer split is candidate 177, still **36 = 6*6**.
At the observed pop sites, base 51 (54) precedes intermediate pointer 130
(50) and split 177 (36). The six-point change is real but insufficient.
`cost_slim.py` stores rounds starting at -1; the archived summary normalizes
this to round zero for the initial cost pass.

Two initial admission traces failed while treating block marker opcode
`0x2C4` as an ordinary operand-bearing instruction. Bounds checking and
skipping the end marker fixed the observer. Those incomplete objects are
not evidence. The successful v2 traces are the ones compared to controls.

## Source searches and limits

Counts are generated combinations, including controls, not unique objects.
**6369 combinations compiled; 6354 resolved in the fitness harness.**
Fifteen extent/relocation refusals are ordinary trial failures, not gate
false rejects. Resolution/fitness is not a full byte-gate pass.

| Family | Generated | Result |
| --- | ---: | --- |
| latepack | 512 | Duplicate equivalent pack paths with 32/64-bit, scalar/reference, shift/multiply, nested basis and four guards. Best 2385 B / 538 differences. Simple staged/reference cases overlap the prior branchmerge controls; novel 64-bit/nested/link1 cases also fail. |
| setuppaths | 2041 | Eight independent duplicate setup sites, four predicates, if/else versus labels. Every regional winner retains seven remap operand differences. |
| remapabi | 648 | Free/static/value-view helpers, raw/vector inputs, integer versus link-element pointer parameters, argument permutations, cdecl/stdcall/fastcall and a named result. Best remains bank. Named-result regional control has 48 differences, not correct complete roles. |
| valuebundle | 1152 | Three used-field aggregates, member order, aggregate/constructor/copy constructor, by-value/reference arguments, declaration position and signedness. Best remains bank. See invalid-hoist exclusion below. |
| valuebundlesafe | 360 | Corrected hoisted subset; best 2345 B / 883 differences. New valid register-role diagnostic above. |
| volatileparam | 216 | Volatile by-value pointer/integer parameters, volatile-reference reads, optional-copy helper/value wrapper and P/N selection. Best remains bank. True volatile values add code/homes; reference controls can remain identical. |
| recombineview | 1152 | All pointer-reference subsets, actual vector-reference input, four declaration positions, six field orders, aggregate/constructor and volatile P guard. Best remains bank. Four extent/relocation refusals. |
| recombineuv | 288 | Three selected view controls crossed with the previous real UV accessor/legacy-body visibility family. No improvement; inherited helper identity/extent limits remain in the live handoff. |

**Invalid-hoist exclusion:** 360 initial valuebundle combinations prepared
optional pointers outside the two-bone arm, including subtraction of a null
link1 or arithmetic on a null optional pointer. Do not use those variants
as semantic evidence or candidates. The safe subset instead stores base
pointers and passes `i` to the helper; delta views compute the difference
only when link1 is nonnull. All 360 corrected combinations compile/resolve.
Thus 6009 generated combinations remain after excluding the original unsafe
subset; 5994 of those resolve. Original unsafe results are retained only in
aggregate counts for an honest experimental record.

`regional-results.json` uses aligned instructions in +0x707..+0x722. A smaller
regional count does not prove correct roles or a whole-body match. The new
value-view's disassembly separately confirms retail's ECX map base/EAX link0
roles and early memory P test, with changed frame displacements. The supplied
patch and full alignment JSON preserve that evidence without thousands of
redundant variants.

Control flow, declaration lifetime, types/value boundaries, callee visibility
and calling conventions received concrete trials. Earlier compiler flag,
real-header and WB findings were consulted; unchanged disproved sweeps were
not used as a reason to abandon this task.

## Checks and reproduction

`check_csv.py` passed at startup and after the searches: 98,083 functions,
15,851 symbols, 2,138 data rows. The original bank privately verifies to its
known nine-byte residue, EH EXACT, zero unresolved calls. This remains a
partial, not a normal exact-body gate pass. `progress.py origin/master`
reports +0 authored/exact C++ bytes. No maintainer-only runner was invoked.

AGENTS.md blob `d9e649de1731eabe044f45471071a62ec24da170` was unchanged from
its previous read within 24 hours. BFME 1 freshness was deferred under the
live shared update lock owned by `codex4`; the verified f890 pointer, another
seat's lock and old success stamp were preserved. Broad queues were skipped
under the explicit standing assignment.

Restore the `.py.txt` files under ignored `build/fxinit-admit23/`. They use
`search.py` from the schedule handoff, restored to `build/fxinit-seat22/`,
and its `wdbg.py` under `build/netpacket-20261022e/`. The search harness saves
raw failures to `.errors`; it uses private objects and never calls
`build.compile_source` or writes the shared match cache. `recombine_uv.py`
also uses the live handoff's `uvvisibility.py`, whose trials are documented
there. Generate value_bundle before value_bundle_safe, then recombine_view
before recombine_uv. Each generator runs eight compile workers.

`admit_trace.py`, `cost_slim.py`, `region_cost.py` take source and private
object paths. The region tracer locates the remap block by its two 0x20C
conversion tuples and 0x2A shift, asserts a unique block, and records costs
there; it does not assume the bank's candidate IDs for the value diagnostic.
The compact observations retain the comparison, used lists, map operands
and initial/split costs. Failed initial traces and huge debugger transcripts
are intentionally not archived. Scratch objects remain in this checkout.
