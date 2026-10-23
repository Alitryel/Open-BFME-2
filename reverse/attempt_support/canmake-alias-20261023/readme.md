# canMake 0x00596e15: two register bytes remain

Continue only `AIBuildableWallSegment::canMake`, retail `0x00596e15` through
`0x00596eed` (218 B, RET4), WB twin `0x15386c0`. Read the preceding
`canmake-priority-context-20261022/readme.md` for the old allocator evidence.
This session improves the bank from 216 B / fitness 0.945980 / six differing
instructions to **218 B / 0.990570 / two differing instructions**. This is a
partial attempt, not exact C++ coverage or a new ledger row.

The complete frame, branch order, offsets, cache store and both cleanup tails
now match retail. `residue.txt` contains the only differences:

| Offset | Retail | Bank |
| --- | --- | --- |
| +0x8b | `pop esi` | `pop ebx` |
| +0x94 | `mov eax,esi` | `mov eax,ebx` |

The bank's EH graph verifies **EXACT**. Its masked code SHA256 is
`f54565adda9cdd992a36d7f917d0dcfb7f5fcf84313d6d1c01fd8549b91c4695`.
`bank-validation.json` records an independent compilation after restoring
portable home-relative includes and cleaning obsolete comments.

## What changed

Start from the earlier `early` 216 B control: original status switch, followed
by the funds do/break/return-zero experiment. Introduce a local `MakeCodeLife`
with an integer field, zero initializer and empty force-inline destructor
before the base fallback. Assign each literal result to its field and return
the field. This keeps the separate success cleanup while fixing the switch's
shared return-two block and default back edge. Replay `return-lifetime`, case
`lifetime-100000`. This is an equivalent C++ compiler experiment; it does not
establish that EA used this helper type. The redundant funds predicate is
proved true on entry, with no intervening call or store.

The WB and previously matched siblings remain the identity/layout basis;
byte similarity is not new evidence for a target class name or full layout.
No production source, pin, ledger row, header or verifier changed.

## Completed experiments: do not repeat unchanged

There were **9,256 factorial source trials**, zero compile errors and no exact
candidate. The 88 unresolved diagnostic variants comprise 16 declined inline
value-return helper calls and 72 floating-literal relocations. None is a
landing. `receipt.json` gives each family's best result and distinct body count.

| Family | Trials | New question and result |
| --- | ---: | --- |
| numeric-status | 1,344 | Arithmetic from the known status and direct/value/reference bindings: three old shapes, no gain. |
| register-return | 108 | Register/plain return locals, scopes, shared/local initialization: no gain. |
| range-return | 1,152 | Twelve path-proved funds predicates and eight return calculations: ESI variants need extra arithmetic/branches. |
| cpu-context | 384 | Four controls, processor/architecture flags, alias flags and precision: unchanged four shapes. |
| narrow-return | 540 | Narrow scalars/bitfields, scopes and return routes: no gain. |
| return-lifetime | 1,296 | Three controls, six local-only destructors, scopes, return routes, field types and getters: finds the new bank. |
| lifetime-interactions | 1,296 | Six return selections at all four failures, recombined in the new 218 B context: one body, still EBX. |
| receiver-union | 128 | Overlap the receiver pointer and return field, varying receiver uses/constructor/destructor: still EBX. |
| lifetime-declarations | 1,024 | Full 2^10 factorial of scope, initializer, type, padding, reference alias, three declaration moves, receiver alias and quote boolean: still EBX. |
| lifetime-conversions | 256 | Enum/scalar fields, implicit conversion, inline getter, copies and reference/value adapters: no gain. |
| lifetime-storage | 320 | Wide integer, pointer, floating and narrow fields crossed with initialization, local destructor writes and casts: no gain. Self-assignment destructor cases are initialized, including the fallback path. |
| lifetime-exceptions | 256 | Full 2^8 exception-specification factorial for opaque callees and local helper members: no gain; specifications are diagnostic, not asserted contracts. |
| lifetime-esi | 576 | Recombine the prior 223 B ESI control with helper lifetime, six destructors and independently routed literal/conditional returns: best remains 223 B. |
| lifetime-initial-values | 576 | Keep constructor-selected 0/2/9 live through the quote by omitting corresponding assignments, crossed with scope/type/getter: still EBX. |

`tools/permute.py` then ran for five minutes on the new two-byte residue:
**2,211 trials, start=best 0.9906, no exact candidate**. The direct CLI could
not compile home-relative includes from its scratch directory. The saved
`permute-218` adapter invokes the unchanged tool with a private copy resolving
those includes to the real home; its scorer resolves all baseline calls.
No gate code or pin was changed. Do not simply repeat this seed/mutation run.

Reproduce from the repository root:

```sh
python3 reverse/attempt_support/canmake-alias-20261023/replay.py.txt --list
python3 reverse/attempt_support/canmake-alias-20261023/replay.py.txt return-lifetime
```

Private outputs stay under `build/`. The older 216 B input is frozen at
tracked blob `20afdd90f70d238a5f035acc08f72ff23e28a844`; the new input is
frozen by its tracked Git blob in `context.py.txt`.
Each family uses eight private compiler objects, never `build.compile_source`
or the production object cache. New-context drivers can therefore be replayed
after another bank update. `permute-218` uses the project's own private compiler.

## Read-only compiler findings

`setup-trace.py.txt` observes c2 RTM 3077 at +82219, +82225, +82232, +82239 and
+83aac. `creation-trace.py.txt` observes the caller at +7c08e and the record
constructor +7c10f / insertion +7c1d2. Neither writes compiler state. All eight
traced old-control objects reproduce their normal hashes and EH EXACT
(`setup-validation.json`, `creation-validation.json`). `alias-observations.json`
keeps the relevant raw records and stage counts, without the multi-MB IR dumps.

Both old-bank and ESI return records are constructed during +7c367, from caller
+7fd0c, before +7c0c8. Both begin with flags word 1=0x102, priority word 3=0,
references word 9=0; symbol word 4=0x1004 and word 8=4 also agree. Their local
symbol numbers differ. Initial record construction/type flags therefore do
not explain the register difference. The setup pass removes other records,
not the return record; later priorities, uses and joins are the useful angle.

The new 218 B trace (`lifetime-color.json`) still colours receiver index 3 to
ESI in round 1 (priority/references 38/6), fixed-zero index 1 to EBX (36/11),
and the return-related index 10 to EBX in round 2 (8/6), with no neighbours.
The holder fixes flow without raising the return record's allocation priority.
Raw field meanings remain partly inferred; the emitted object confirms the
register correlation. c2's SHA and the reference pointer are in the receipt.

Next investigation: observe the return-copy joins / surviving value uses in
c2 +844a4 and the priority pass +82473 for this exact 218 B input versus the
223 B ESI selector. The latter retained conditional value arithmetic until
allocation and got ESI; determine a source shape that retains its allocation
constraint while removing that calculation. Do not repeat the folded-use,
declaration, conversion, type, exception or same-seed permutation families above.
No missing callee has been established as a prerequisite.

## Checks and handoff

Pull/rebase, ledger validation, published link-index fetch, home's declared-
definition check and `./build.sh AIBuildableWallSegment.cpp` (2/2 existing bodies,
source/string/float/import checks) passed. Saved evidence scripts compile as
Python. Portable bank recompilation and all nine traced objects verify EH EXACT.
No maintainer-only runner was started. The claim is released at session end;
reclaim the same target before continuing.

The experiments used BFME1 pointer
`42bba2ddbd5cb895d99293583891d3b7315fa49e`. The final upstream rebase inherited
verified pointer `f890413e75e671748215ba2ef3304aa7953993e9`; the bank and home
were rechecked there. Initial freshness work was skipped under the live
`claudec2` update lock; at final pull another live updater held it as `codexb`.
No local success timestamp was written. Final `progress.py origin/master`
reports +0 exact C++ bytes; the session result is the substantially improved
bank and reproducible compiler evidence.
