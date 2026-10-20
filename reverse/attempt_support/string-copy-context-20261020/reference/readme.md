# Donor, actual-header and primary-template timing review

**Blocked:** no tested source context preserves all matched parents while
reconciling the shared copy provider. No production change is proposed.
The useful new result is a primary-template-only context that reproduces
the complete 740-byte insertion and 41-byte helper together; its existing
501-byte replacement still has the wrong frame.

Inputs: BFME2 `cbf7608fb05a1180b2e2c7fa19a5a523e1f95d7c`;
verified BFME1 `92f6bbe8e1dcdb46b5d27da0674313efc822b790`.
`inputs.json` records baseline sources, selected headers, compiler binaries,
image and diagnostic-tool hashes. Local headers declare STLport `0x452`;
the donor headers declare `0x460`. Historical “4.5.3” ledger wording does
not establish a different selected header version.

## Executed results

Root executed the normal `tools/explain_mismatch.py` checks. `results.json`
preserves their classifications, first mismatches, frame excerpts and
relevant helper inventories, distilled from the three reference-seat result
files and root's restored-inline diagnostic. Exit zero means the diagnostic
ran; it does **not** mean the body matched.

| Control | Insertion 740 | Replacement 501 | V21/V22 149/170 | Emitted neutral copy |
| --- | --- | --- | --- | --- |
| Actual `_uninitialized.h`, existing extern/nothrow worker switch | Exact in all three units | Exact | Exact | 68B, wrong |
| Actual header, inline worker visible | 1024B, wrong | 501B, frame `130` vs `118` | Same extents, frames `A8/AC` vs `84/88` | 39B outer calls 97B inner, wrong |
| Primary only, insertion out of class, EOF optimization; `/Ob1` or `/Ob2` | 665B, unresolved outlined `distance`, `advance`, `copyIter` | 501B, frame `9C` vs `118` | Not tested | Exact 41B |
| Same, force the five genuine iteration templates inline | Exact | 501B, frame `9C` vs `118` | Not tested | Exact 41B |
| Root restores insertion in class with the same forced iteration policy | Exact | 501B, frame `FC` vs `118` | Not tested | Exact 41B |

The exact helper's raw SHA256 is
`07d84357dc85cbcdfcfccbb4e7b9f4c6e342b9f26802457e6d29523d941653a4`.
Its sole relocation is DIR32 at `+0x1e` to `__imp__memmove`, matching the
canonical 41-byte worker at `0x179B0`. The existing wrong 68-byte helper
instead has REL32 `+0x39` to canonical `__copy_trivial`.

## Donor and sibling review

- Donor `game/Libraries/Source/STLport/Rva008314E0StringReplace.cpp` retains
  genuine `<memory>` mutable-copy context and a declared const-source
  forwarding helper. Published status remains `no,4,0,5,0,3,0,0`; sibling
  `Rva008312E0StringReplace.cpp` remains `no,1,0,2,0,2,0,0`.
  Neither supplies a finished inherited provider reconciliation.
- Donor `game/Libraries/Source/WWVegas/WWLib/NumPutIntegerNarrow.cpp` has a
  visible noinline conditional-expression `__copy_aux` under optimized
  flags, a real 41-byte body at `0xA3790` through ILT `0x33A50`. Its older
  `object-symbol` alias row is not a permitted new repair pattern.
  The unit's published status itself remains `no,0,0,1,0,2,0,0`.
- Local `stlport_narrow_put_integer.cpp` is the successful analogous body
  visibility repair: the compiler knows the empty tag is unused. It does
  not prove that `/Od` string parents can discard their helper copies.
  That four-argument `__copy_aux` ABI also cannot simply replace native
  string copy calls, which push only three pointers.
- Donor's old `0x82EB30` vector-copy history uses genuine headers, forced
  POD dispatch and a noinline/nothrow worker declaration. It has no exact
  emitted generic provider applicable to these string parents.
  The record is
  `targets/game/reverse/attempt_history/0x0082eb30/528d30f741a66841b77dd3093513bf575b48218aecb2bc085990c736e2fe493d.json`.
- Donor `Rva0082C6E0VectorErase.cpp` uses canonical copy through
  independently resolved ILT `0x18179 -> 0x65E30`; its shallow forwarding
  does not reproduce this nested inliner problem.
- Root's donor path history found only `cf0a80c2`, the 2026-10-19 census,
  among the last twelve commits touching the three requested donor paths.
  No newer applicable source repair was found.

The local `_STLP_BFME_COPY_TRIVIAL_EXTERN` header repair declares the worker
`throw()`. The donor header lacks this switch. Both headers use an empty
aggregate `__true_type`; normal VC7.1 configuration supports class partial
specialization. Hence the local null-char type queries and empty POD tag
follow the selected vendor path. Alternate nonpartial query calls or a
user-provided constructor on canonical `__true_type` lack this provenance.
The latter would also create an ODR mismatch against actual header users.

## Hypotheses and remaining prerequisite

The actual-header controls rule out a missing real trait definition as the
simple explanation: all exact parents and the same bad 68-byte provider
survive together. Exposing the full worker changes expansion and breaks
parents rather than repairing the provider.

The timing controls retain one primary template, forced genuine inner copy
dispatch and the conditional memmove body. They compile the parent under
optimization-off, then enable `gty` at EOF for deferred template emission.
Moving insertion out of class isolates its parsing time. `/Ob1` and `/Ob2`
give the same result. Forced iteration resolves the measured outlined-call
problem, yielding exact insertion/helper bytes without an explicit copy
specialization. The remaining replacement frame is materially wrong.
Putting insertion back in class recovers some analysis context but still
leaves seven dwords missing (`118 - FC = 1C`).

Do not publish an isolated exact specialization with a conflicting primary
definition, add an exact provider alongside wrong consumer COMDATs, retire
the canonical worker identity, or hide the discrepancy with a new pin.
The next viable repair must preserve every parent and its native call
destinations, reconcile ODR across both owners and both wrappers, and pass
the normal combined provider/consumer link check. The exact 41/740 result
is a prerequisite lead, not a completed link repair.

## Replay

`replay.py` is standalone generation logic based on the tracked baseline
sources. It requires no prior `build/` source, object, JSON cache, or scratch
driver. Input hash checks stop a stale replay. It regenerates all eleven
controls under `build/string-copy-context-reference-replay/`.
Generation was checked in memory against all eleven executed scratch sources:
the text agrees after whitespace normalization. All 64 recorded inputs were
readable and hash-current; the actual-header owner's dependency receipt also
agreed with every recorded dependency. Packaging did not rerun the compiler.

```text
python3 reverse/attempt_support/string-copy-context-20261020/reference/replay.py
python3 reverse/attempt_support/string-copy-context-20261020/reference/replay.py --run --case timing-force-iter-ob1
```

`--run` uses only normal `explain_mismatch`; no direct compiler API is used.
The header controls' original helper verdict came from emitted-definition
inventory; replay additionally requests its explicit 41-byte diagnostic.
No production sources, ledger rows, pins, claims or verification rules were
changed by this reference-seat investigation.
