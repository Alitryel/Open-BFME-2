# Drawable shroud: passive priority terms and real leaf providers

Resume only `?onComingOutOfShroud@Drawable@@AAEXXZ`, 0x0027893E,
747 retail bytes. The existing score-0.995 bank remains better than every
ordinary source tested here and is unchanged. It emits 748 B / 220
instructions: instruction 201, retail +0x2BA, is `mov ecx,[ebp-0x10]`
instead of `mov ecx,edx`. The earlier shifted branch displacement is a
consequence of this extra byte. No production source, ledger, pin, compiler
setting or verifier was changed for these experiments.

Read the exclusions and controls in
`../drawable-shroud-mask-order-20261023/readme.md` and
`../drawable-shroud-allocator-cost-20261022/README.md` first. The latter's
diagnostic allocator intervention remains ineligible and was not repeated.

## New passive observation

The ordinary split-tail control emits 738 B but loses the earlier correct
holder/template allocation. The previous session's unsigned-OR predicate
control emits 757 B: its registers and stack slots agree with retail,
including the final EDX handoff, but both bit-6 predicates expand by 5 B.
This session traced writes to the candidate record's +0x0C ordering field:

| Ordinary source | Holder additions - subtractions | Mask additions - subtractions |
| --- | ---: | ---: |
| Common-tail bank | 36 - 23 = 13 | 50 - 40 = 10 |
| Native split tail | 36 - 23 = 13 | 54 - 40 = 14 |
| Split tail, OR predicates | 36 - 23 = 13 | 54 - 42 = 12 |

These are measured writes, not a claim that +0x0C is allocation cost (cost
is at +0x40). At the addition site, the new value is the old value plus
record word 6 times EDX. At the subtraction sites, EDX is subtracted. The
native split tail's last relevant notification-block addition uses weight
6 instead of the common tail's 5, with word 6 equal to 4: the difference
is +4. The OR predicates increase two earlier subtraction weights from
2 to 3: their combined difference is -2. Holder terms stay unchanged.
This localizes the previous 10/14/12 observation to concrete contributions;
the semantic interpretation of the weights is still unresolved.

`trace_weights.py.txt` uses the previous allocator handoff's `wdbg.py.txt`.
Copy them into scratch as `.py`. It only reads registers and memory at C2
breakpoints. The focus breakpoint is C2+0x83AC8, immediately before the
priority-building call, then write sites +0x8292A, +0x83A56 and +0x83A7D.
An initial +0x83ACD focus probe yielded no records and supplies no evidence.
The complete raw parent symbol and relocation list from each successful
trace equal its ordinary compiler output. Hashes, scalar terms and equality
checks are retained in `observations.json`; there was no debugger write to
compiler state. The existing +0x14-next-record finding is unchanged.

## Finite ordinary source trials

All 2,400 final sources compiled into private scratch objects with eight
workers. None improved the whole-body bank. The generators and scoring
driver are preserved as `.py.txt`; use the bank plus the two earlier
handoffs' `native_split.patch` and `native_or.patch` beside the generators.
Generate a family, then run `driver.py <family-directory>`. The driver is a
search aid that masks actual relocations and aligns branch destinations;
it is not the landing gate. Its JSON records retain result histograms.

| Family | Valid trials | New choices crossed |
| --- | ---: | --- |
| `prefix` | 512 | Common/split tail; four checked-Kind chains, four dead-test helpers, four context constructors/setters, four virtual-ready wrapper combinations |
| `update` | 1,024 | Common/split tail; sixteen status-update forms independently on both arms, local/shared mask scope |
| `kind_chain` | 384 | Common/split/OR control; eight Kind-7 chains, eight Kind-47 chains, local/shared mask scope |
| `castle_control` | 288 | Common/split tail; twelve bit-6 control forms independently at both sites: switch, one-iteration loops, labels and cached predicates |
| `leaf_context` | 192 | Three controls; sixteen combinations of real helper bodies, before/after definition order, proven leaf exception specifications |

The update family initially had 256 split-tail/shared-mask generator scope
errors; they were fixed and those 256 cases were rerun successfully. A
Kind-chain generator token-replacement error was also fixed before its
complete run. These errors are not compiler or verifier findings. The
2,400 count describes final valid trials, including equivalent outputs.

The real provider experiment is independently checked: `Object::getDrawable`
(0x5508E2, 7 B), `Object::getControllingPlayer` (0x28AFA9, 18 B),
`Team::getControllingPlayer` (0x39D7CF, 12 B), and `Object::findModule`
(0x28B6D6, 43 B) all match their complete retail bodies through normal
relocation resolution from the same private object. Making them visible,
with each definition order, leaves all three parent controls unchanged.
The measured Object offsets and virtual-name-key slot were reconciled in
the scratch view; they are not new production layout declarations. Do not
repeat this visibility matrix without another changed dependency.

## Handoff

The useful new evidence is the concrete priority contribution above and
the byte-proven exclusion of four additional helper providers. The earlier
source problem remains: obtain the split tail's final Object allocation
with the common tail's earlier holder ordering and both original byte
TESTs. The common-tail bank is also still one instruction from exactness.
There is no missing-function prerequisite or `blocked-on=` RVA.

Independent explanations have concrete trials here or in the linked
history: control flow and loop entry (castle matrix); lifetime and scope
(mask scopes and context constructors); boundary types and layouts (Kind
and update matrices); callee visibility (four real providers); compiler
settings (earlier recorded finite profiles, unchanged this pass). These
families are exhausted under these inputs, not proof that C++ cannot match.
Destination remains `Code/GameEngine/Source/GameClient/Drawable.cpp`; its
undeclared-definition check passed before work. Production integration is
still pending exactness.

Inputs for the body experiments: BFME2 origin/master `21b0fe73b2` plus two
earlier evidence-only commits; BFME1 verified pointer
`42bba2ddbd5cb895d99293583891d3b7315fa49e`. Flags remain O1, Ob1,
d2inlS100, static STLport, G7, SSE, MD, EHsc, DNDEBUG. Startup pull,
ledger check and published-index fetch passed. The separate BFME1
freshness comparison does not claim an improvement to this body.

Preserve the unchanged score-0.995 bank and resume this same specific task.
Model gpt-6.1-sol; approximately 30 minutes of body investigation, excluding
the independent reference full-gate wait.
