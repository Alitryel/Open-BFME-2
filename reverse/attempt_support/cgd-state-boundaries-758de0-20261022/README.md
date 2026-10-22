# 0x758DE0: state-read probe and data-level inline boundary

Continue the assigned `BfmeThingCGD::bfmeTwoCGD`, extent **333 bytes**.
The bank now emits 333 bytes, zero relocations, **31 positional differences**,
first at +0x94, and **308/333 bytes in aligned identical complete instructions**
(score 0.9249249249). The incoming bank had 34 positional differences and the
same aligned score. This is a modest fixed-offset improvement, not an exact
recovery. No source was installed in Code; no ledger row, pin or gate changed.

## Best body and its uncertainty

The only effective source change from the incoming bank is a data-level
inline helper around the first response's prepare call:

```cpp
__forceinline void *__cdecl bridge(ContactData *s,
    const ContactVector &p,const ContactVector &n) {
    return s->source->prepare(p,n);
}
// First response:
node->first->source->respond(bridge(node->second,node->point,node->normal));
```

It changes the first response's initial loads from
`edx=[esi+4]; ecx=[edx+4]; edx=[esi]` to
`eax=[esi+4]; edx=[esi]; ecx=[eax+4]`. The second instruction now occupies its
retail position, although the first load still has the wrong register. All
other emitted bytes are unchanged. Both a free helper (`bridge/v06917`) and
an inline ContactData member (`memberbridge/v0005`) emit SHA256
`01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
Removing the unused reverse helper preserves that hash; `best.cpp.txt` is the
cleaned candidate actually banked. `candidate-diff.txt` retains the call regions.

The reverse call still uses the incoming bank's stack-compatible eight-byte
fastcall interface model. This does **not** establish the original signature
or justify two interface views in production. The consistent-interface
control remains in the final-schedule packet. Contact* and BfmeThingCGD are
inherited diagnostic names; no new target identity or layout claim is made.
The first test and first response still differ in vtable scratch registers
and push/reload order. No missing function or justified `blocked-on` RVA was
identified.

## New compiler evidence

The earlier minimal 69-byte test probe caches the guarded inner receiver and
can schedule its table load after the normal push. Adding only
`if (node->state==0)` produces the 77-byte `probe-p01.cpp.txt`: the state read
overwrites that cached receiver's register, the forwarding shortcut disappears,
and its inner table load precedes the argument pushes. The state-containing
probe is a better reduced control for the full body's residue. The 69-byte
control and a 118-byte probe with the first response are retained too.

Read-only debugger traces now capture the actual scheduler graph at compiler
RVAs +0xb4e16 (after graph construction), +0xb4e20 (after priority calculation)
and +0xb4e2a (after reordering). These belong to RTM c2.dll 13.10.3077, base
0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
The function pointer at +0xb299b is **EDI**, not ESI. An initial debugger
attempt using ESI failed before collecting evidence; the retained runs use EDI.

`selected-dag.txt` shows the state probe and the incoming/new bank's first two
call windows. Nodes are numbered by their original ordinal; edge annotations
are `(successor ordinal, stored latency)`. The priority field and IL linked
order are observations, not recovered internal symbol names. Register IDs are
1=EAX, 2=ECX, 3=EDX, 5=ESP, 6=EBP, 7=ESI, 8=EDI.

In the first-response window, the point-address LEA is node 4, the inner table
load is node 8, and the point push is node 10. Before scheduling, EAX holds the
point address across node 8, consistent with the earlier allocator trace's
forbidden EAX at this load. In the incoming bank, reusing EDX for the first
inner-data pointer adds an ordering edge from node 2 to node 5. The helper
changes that data pointer to EAX, removes this serialization, and changes the
scheduled prefix from `1,2,5,6,7,8,...` to `1,5,2,6,7,8,...`. It does **not**
move the inner table after the point push or change that table's EDX home.
This explains the three-byte fixed-offset gain without claiming the main
register-lifetime problem is solved.

`selected-ir.txt` keeps the state probe before/after the previously located
forwarding and scheduling passes. All four retained debugger runs completed
compilation and reproduced their untraced controls, with zero relocations
(`trace-checks.json`). The debugger only reads state. No compiler instructions
or IR were changed.

## Trials and independent explanations

`trials-summary.json` records the corrected model families and per-region
winners. Full `(mnemonic, operands)` alignment gives the reported score; the
search helper's mnemonic-first score and fixed-offset difference count are
different metrics. There is no legal byte-splicing of region winners.

There were **29,184 successful variant compiles**. The 256 initially ambiguous
state models are excluded from that success count and replaced by fixedstate;
three reduced probes and the independent reproduction/trace checks are separate.

| Family | Successful / attempted | Distinct bodies | Best aligned / positional differences |
| --- | ---: | ---: | ---: |
| fieldmodels | 768 / 1024 | 6 | 308 / 34 |
| fixedstate | 256 / 256 | 4 | 274 / 185 |
| bridge | 13824 / 13824 | 48 | 308 / 31 |
| memberbridge | 4096 / 4096 | 25 | 308 / 31 |
| callbridge | 2048 / 2048 | 56 | 308 / 34 |
| datapair | 8192 / 8192 | 5 | 285 / 43 |

- Storage/type/layout: four-byte inline state, source-pointer and data-pointer
  storage wrappers; conversion/reference getters, assignment/equality shapes,
  copy visibility and vector getters. The state equality overload initially
  caused 256 C2666 ambiguities; rerunning those with unsigned comparison
  literals fixes the generator. The other 768 compiled initially. No gain.
- Callee visibility and lifetime: inline prepare helpers take the source,
  source field, data pointer or data field, by value/reference/address. All six
  receiver/point/normal parameter orders, pointer/reference vector arguments,
  three conventions, named returns and independent call sites were combined.
  The data-pointer boundary gives the bank's small fixed-offset gain.
- Scope/source shape: Data member/static and Node member helpers, including a
  captured point, source locals, vector-reference locals, declaration order,
  constness and independent sites reproduce the same best hash, not a closer
  body. Combining each whole nested test/response inside a Data/Node/free
  helper, with receiver-local order or a named prepare result, does not help.
- Interface recombination: the new Data/Node helper families were also applied
  to a consistent eight-byte fastcall prepare interface, using pointer/reference
  pair fields and direct/member-wrapper dispatch. All 8,192 variants compile
  to only five bodies; the best still loses 26 solved prefix bytes, exactly
  the previous consistent-interface result. The new boundary does not repair it.
- Control flow: the state-read probe concretely isolates the cached-receiver
  loss; the previous large control-flow/loop-entry family was not rerun.
  Compiler settings and real vector/header trials in earlier packets remain
  applicable and were not repeated. Their negative results are not evidence
  that every conceivable original source shape has been exhausted.

## Inputs, checks and continuation

Input HEAD was `eb93f08015b2a4c5762e7105794dc8f29b638556`, including the
previous unpublished evidence commit, which was preserved. BFME 1 checkout
and committed pointer both remained the clean
`42bba2ddbd5cb895d99293583891d3b7315fa49e`. The fresh update lock belonged
to claudec2, so this seat skipped the update as instructed and did not record
freshness success. Initial ledger validation passed (98,069 functions,
15,856 symbols, 2,131 data). The published link index was fetched/reused;
no census or maintainer-only runner was started.

`tools/variant.py best.cpp bfmeTwoCGD 0x758DE0 333` independently reproduced
the 333-byte/31-difference result. All searches used eight private-object
workers through `compiler_command`, never the shared match cache. This is a
diagnostic mismatch, not a false gate rejection.

Continue with the new bank and the old uniform-interface control. The useful
remaining question is how the original source permits the first-response
point address to be pushed before the inner table occupies EAX, while keeping
the already solved iterator, guards and reverse-normal code. Compare the new
candidate's pre-allocation push/vtable lifetime with the scheduler graph;
further nominal type, padding, flag or identical inline-getter sweeps have no
new supporting evidence. A consistent explanation for the reverse interface
is also still required. Do not substitute the diagnostic cast for that proof.

To reproduce, materialize the `.py.txt` files in a new ignored build directory,
use the final-schedule packet's `control.cpp.txt` as `base.cpp` and its incoming
bank (`git show eb93f08015:reverse/attempts/0x00758de0.cpp`) as `diagnostic.cpp`.
Generate/score the named families with their scripts and `search.py FAMILY`.
Run `fixstate.py` after fieldmodels to generate its corrected 256 cases.
`datapair.py` consumes memberbridge's even-numbered uniform-interface sources.
`regions.py FAMILY...` writes the complete-instruction summaries. The trace
commands are `trace.py end-state probes/p01.cpp` and
`trace_scheduler.py dag-state probes/p01.cpp`, `dag-bank diagnostic.cpp`,
or `dag-bridge bridge/v06917.cpp`.
