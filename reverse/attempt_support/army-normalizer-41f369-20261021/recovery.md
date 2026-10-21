# ArmyDefinition normalizer 0x0041F369: exact recovery

2026-10-21. The normalizer now emits the complete 200-byte retail body, with
all relocations resolved. The solution restores real translation-unit context:
the existing `ArmyMemberDefinition::getInterpolatedPercentageOfArmy` body
precedes the normalizer, and the vector's trivial `begin`/`end` definitions are
explicit inline-only specializations. The function remains ordinary scalar C++.
No compiler modification, artificial preceding function, inline assembly,
intrinsics, or optimization pragma is part of the exact source.

The coherent home is
`Code/GameEngine/Source/GameLogic/SkirmishAI/ArmyDefinition.cpp`.
The independently compiled pre-installation source/object are
`build/army-causal-20261021/real_prior_inlined/integration.cpp` and `.obj`.
Its ordinary-compiler comparison is saved in `full_verification.json` beside
those files and preserved here as [full_verification.json](full_verification.json).
The earlier near-match and WorldBuilder reconstruction are in
`reverse/attempt_support/army-normalizer-41f369-20261020/`.

## Reproduction inputs

The integration verification used BFME 2 base revision
`a2fe7665ed515a7aad86d5d4738d8e00af02d45c` with BFME 1 checkout
`a80da2e3be84ebdb3b6bc280faca3f99a44788af`. The base commit still recorded
the earlier verified pointer `3f00bbbe9b0c477c2182782b7401aa4fa8b1aa80`;
the integration object was compiled after the checkout update. All 62 header
dependencies still match that ordinary compile's dependency receipt.

The accompanying BFME 1 pointer update passed paired full gates at the same
BFME 2 source/ledger revision: both pointers verified all 97,924 functions and
1,381 data rows, with no regressions or pre-existing failures. The candidate
reused all 23,422 compiled units. The gate summaries and log hashes are retained
in [bfme1-comparison.json](bfme1-comparison.json).

The compiler is the repository's VS2003 MSVC 7.1 profile, with STLport enabled
and these source flags:

```text
/O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
```

The driver prepends `/nologo /c /O2 /GR- /EHsc-`; the later source flags
override `/O2` and `/EHsc-`. Source, ordinary object, compiler backend and raw
trace SHA-256 hashes, plus the dependency-hash fingerprint, are preserved in
[trace_summary.json](trace_summary.json). Once installed, reproduce the byte
gate with `./build.sh Code/GameEngine/Source/GameLogic/SkirmishAI/ArmyDefinition.cpp`.

## Full-body verification

All three emitted definitions were checked across their entire COFF symbol
extent, including relocations, rather than only a requested prefix:

| RVA | Definition | Extent | Result |
| --- | --- | ---: | --- |
| 0x0041F28C | ArmyMemberDefinition index-to-weight pointer accessor | 28 B | Exact; no relocations |
| 0x0041F2A8 | ArmyMemberDefinition::getInterpolatedPercentageOfArmy | 104 B | Exact; manager datum at +12 and record-lookup call at +17 resolve correctly |
| 0x0041F369 | ArmyDefinition normalizer | 200 B | Exact; 100.0f relocation at +75 resolves correctly |

The accessor and interpolation method were already matched in
`Code/GameEngine/Source/Common/Rva0041F28CMethod.cpp` and
`Code/GameEngine/Source/Common/Rva0041F2A8Method.cpp`; their bodies are preserved
in the coherent home. The normalizer is the newly recovered retail body.
Normal repository byte, identity, and link checks remain the landing authority.

The installed unit passed `./build.sh` for all three complete bodies and
`find_declared_unmatched.py --fail`. The current-ledger link preview also passed:

```text
python tools/link_check.py --refresh --current-ledger Code/GameEngine/Source/GameLogic/SkirmishAI/ArmyDefinition.cpp
link_check: transient current-ledger preview (23,443 providers); census record unchanged
Code/GameEngine/Source/GameLogic/SkirmishAI/ArmyDefinition.cpp: LINKS
link_check: 1 of 1 link cleanly; LINKED 0 -> 332 bytes (268.0s; transient preview)
```

This preview used the fixed BFME 2 base and BFME 1 revision above plus this
recovery. All 1,381 data rows passed. Before the preview, the supported
`--prepare-current` mode refreshed missing strict compiler receipts for 260
explicit providers, with each preparation's ordinary byte and reference gates
passing. No verifier, census, index or link-status data was changed. The full
local preview log and command/exit record are
`build/army-current-ledger-preview-20261021.log` and `.json`. The 332 linked bytes
include the two existing siblings; the net newly recovered body is 200 bytes.

## What caused the mismatch

MSVC 7.1's backend keeps integer-register availability in a global array.
The word at c2.dll RVA 0x1a7b30 is `_regAvail[6]`, EBP availability. The name and
index are supported by the SP1 public-symbol mapping and the target's matching
register-availability setup code. `CmdAdjustRegAvail` is at target RVA 0x70a9a;
its caller `CmdGetNumIntRegs` is at 0x80718.

The target's SSE register allocation runs **before** this function's integer
availability refresh. Consequently its scalar spill-cost calculation observes
the preceding compiled function's EBP-availability state. The later integer
pass refreshes availability using the normalizer's own descriptor.
This is observable compiler state, not a source-order guess.

The isolated candidate starts with availability 1. Total0's spill benefit is
38 versus the first scale's 32, assigning total0 XMM2 and scale XMM3, opposite
retail. Under `/Oy-`, their benefits become 22 and 22; the scale's higher
candidate ID wins the tie and takes XMM2. But `/Oy-` also changes integer
allocation and emits 198 bytes, so it does not recover the function.

The real 104-byte interpolation method finishes with EBP unavailable. An
ordinary combined source still fails: the compiler emits out-of-line vector
`begin` and `end` copies between that method and the normalizer, and those
simple functions restore availability 1. Equivalent `dllimport` + `forceinline`
specializations suppress the unused external copies while retaining their
real `_M_start` / `_M_finish` inline bodies. This is the same provider-emission
pattern already used by matched SkirmishAI units such as AIStatCollector.

The normalizer then receives the required combination: availability 0 for
SSE costs, followed by availability 1 for its own integer allocation. The
arithmetic and loop bodies are unchanged from the earlier 200-byte candidate.
The final trace confirms this order and costs:

| Stage | EBP availability | Relevant benefits |
| --- | ---: | --- |
| Interpolation method finishes | 0 | Real framed/x87-return method |
| Normalizer SSE `OrderGlobregs` (class 6) | 0 | total0=22, scale0=22; scale candidate 19 precedes total candidate 16 |
| Normalizer `CmdAdjustRegAvail` | 0 -> 1 | Its own descriptor allows EBP |
| Normalizer integer `OrderGlobregs` (class 0) | 1 | first scaling iterator=52, loaded member pointer=48 |

[trace_summary.json](trace_summary.json) preserves the three emission names,
the decisive availability transitions and candidate costs, with zero-based
record indices into the final 151-event diagnostic trace. The 1.7 MB raw trace
remains at `build/army-causal-20261021/exact_trace/exact.trace.json`. No vector
accessor body appears between the real interpolation method and the normalizer.

## Controls and provenance

- Isolated shared-iterator candidate: 200 B, nine differing bytes, only XMM
  roles wrong. `/Oy-`: 198 B, native XMM roles but different integer roles.
- Adding the real interpolation body while allowing ordinary vector emission
  leaves the 200 B / nine-byte mismatch. Full pass traces show the intervening
  vector bodies restoring availability 1.
- Removing the real interpolation definition from the exact context, or moving
  it after the normalizer, restores the same 200 B / nine-byte mismatch. Both
  controls retain the inline-only vector specializations; their results are
  in `build/army-causal-20261021/exact_controls/`.
- Giving only the original accessor a diagnostic `/Oy-` policy also fails:
  the emitted vector bodies still intervene. That diagnostic pragma is not
  present in the exact source.
- Equivalent vector `inline`, `forceinline`, `nothrow`, and `throw()` declaration
  controls without suppressing external copies are byte-inert.
- Pinned RTM, SP1 and DDK4035 compilers produce the same isolated near-match;
  changing compiler profile was not the solution.

The interpolation body and both vector accessor operations are existing real
code, not inserted dummy work. The target's identity/layout remain supported
by its caller, the independently matched ArmyDefinition constructor/destructor,
weight accessor, and the WorldBuilder normalizer twin at 0x01333240.
WorldBuilder's 418-byte body supports four traversals, three totals, positive
sum guards and 100/sum scaling. Iterator lifetime in the recovered optimized
body is a reconstruction choice; its exact bytes establish retail code shape,
not a claim that the shared local was the original source spelling.

Diagnostic scripts and complete outputs are under
`build/army-causal-20261021/`: `trace_pair.py`, `trace_availability.py`,
`trace_whole_order.py`, `trace_exact.py`, and the isolated source probes.
The debugger only installs transient breakpoints in its private compiler child;
none of its objects is used as landing proof. The successful full-body checks
above used an ordinary unmodified compiler invocation.
