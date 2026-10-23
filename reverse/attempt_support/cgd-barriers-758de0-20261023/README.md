# 0x758DE0: compiler barriers and integer-address lifetimes

The best bank remains **333 bytes, zero relocations, 31 positional byte
differences**, with **308/333 complete instruction-pair bytes aligned**
(score 0.924924924924925). Its emitted SHA256 is
`01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
No body landed. The remaining differences are the test and first-response
virtual-call windows. The bank's reverse-only fastcall pair interface remains
an unproven ABI diagnostic; closer bytes do not establish its original type.
The ordinary thiscall control remains available as `control.cpp.txt`.

## Inputs and new hypotheses

Input BFME 2 HEAD was `466c8a891a6cdcd3dbcdacad166c7248452af2bf`.
The clean BFME 1 checkout and committed pointer were both
`f890413e75e671748215ba2ef3304aa7953993e9`. Another seat (`codex4`) held the
fresh BFME 1 update lock, so this session did not advance the pointer or write
a successful-freshness timestamp. `inputs.json` records source/compiler hashes.
The compiler remains stock RTM c2.dll 13.10.3077, base `0x10700000`, with the
bank's `/O2 /MD /EHsc` flags. Native extent is still 333 bytes through the RET
at 0x758F2C; three INT3 bytes follow. Do not use align_diff's larger default span.

Before editing, the previous per-RVA history and the vcall, source-shapes,
lowering, state-boundaries, global-homes and edges packets were read. Their
negative results already covered declaration padding, ordinary getters,
pointer-bit memcpy/union identities, vector layouts, argument/return ABI
models, compiler versions/settings/LTCG, and duplicate branch assignments.
Those were not treated as new hypotheses.

The new allocator recipe in `docs/recipes.md` and
`corealloc-32b00-20261022.md` supplies a supported `_ReadWriteBarrier()` example
that changes scheduling without a CPU instruction. The first hypothesis was
that ordering barriers at argument, receiver or result boundaries could fix
these windows. The second was that exact unsigned identities, including
inverse rotation intrinsics, could postpone simplification of the point
address until after global-expression allocation. The final factorial
recombined these boundaries with the old branch winner rather than repeating
its branch-only search.

## Searches and controls

All families use eight private-object workers via `compiler_command`, never
`build.compile_source` or the shared match cache. `trial-summary.json` includes
region winners; fitness is diagnostic, not verified coverage.

| Family | Successful compiles | Distinct bodies | Best pair-aligned / positional differences |
| --- | ---: | ---: | ---: |
| readwrite | 512 | 16 | 308 / 31 |
| write | 512 | 8 | 308 / 31 |
| uniform | 512 | 16 | 302 / 41 |
| identity | 768 | 137 | 308 / 31 |
| recombine | 4096 | 40 | 308 / 31 |

These are **6,400 supported, relocation-free compiles**, including controls.
The barrier families vary nine independent sites: both test arguments, test
result, bridge receiver, both bridge arguments, bridge result, state-2 guard,
and the second response's guard. `uniform` substitutes the ordinary prepare
interface at the reverse call while retaining the data bridge. Its best
control is the historical 333-byte/41-difference body, SHA256
`fb1009de36137ad2a9d51456fb0b4b6f75176beeca9c0e6292549ec39c845eb3`.

The 24 integer forms vary independently over the three point-use masks,
before/after adding +0x14 and cdecl/fastcall inline helpers. Inverse rotates
remain actual ROR/ROL instructions; they do not provide a zero-cost late
identity. Multiplicative inverses and the forms that do collapse never beat
the bank. The recombination family combines bank/edge source, independently
selected point casts, node/reference helpers, helper convention, and six
argument/receiver/result barrier choices. No region winner preserves the
solved prefix while fixing the first-response window.

`_ReadBarrier` is **unsupported by this compiler**: C4163, followed by an
external call relocation for each use. An initial 512-way diagnostic included
511 such objects and one unused-barrier control. They are excluded from the
6,400 count and from eligible winners; `read-warning.txt` preserves the warning.
Do not repeat that family or treat its apparent region scores as a lead.

## Completed read-only traces

Both traces reached compiler termination and emitted the exact same bytes as
their normal, untraced compiles (`trace-checks.json`). No compiler instructions,
IR, flags or gate were changed.

* `readwrite/v0160`: 338 bytes, SHA256
  `60fc10ad10f488b223185badce3c3e9374481b7ab09bf2ce75d74c20a92cb879`.
  The test-normal and bridge-receiver barriers change load ordering and yield
  23 aligned first-response bytes, but lose the prefix. At c2+0x7C0C8 the
  first response's normal/point are still global candidates (raw word 7:
  23/24). At +0xB0037 they map to EDI/EAX. The barrier did not make the point a
  short-lived local or delay the vtable load to retail's position.
* `identity/v0008`: 338 bytes, SHA256
  `989f954d5365980b83059a426534f0d5310eec83e0bfc6d91cc46ba500e32a87`.
  This is the simple integer address round trip at the first response, without
  inverse arithmetic. Normal/point are still global candidates 25/26 at
  +0x7C0C8 and +0x821A7. After +0xB0037 the two point definitions map to EDX
  and ECX, while the normal stays EDI. Thus the type boundary changes register
  ownership, but does not prevent global-expression creation; spills and the
  earlier call sequence are worse.

The compact address stages and selected IR retain the evidence. Raw pointer
values and candidate numbers are observations, not recovered compiler types.
The independent bank compile again checks 333 bytes, zero relocations and
the unchanged hash (`bank-check.json`). `call-windows.txt` shows retail,
bank, both traces' normal controls and an inverse-rotation control.

## Handoff

Keep the existing best bank. There is no identified missing callee or justified
`blocked-on` RVA. Identity, layout and extent remain the prior target evidence;
this session makes no new donor-name or source-layout claim. The earlier real
headers, optimized WB twin, sibling context and compiler-setting evidence
remain applicable; none supplied a new settings hypothesis here.

A concrete remaining investigation is to compare allocation/splitting rounds
for the integer-address control with the bank, now that the former is known
to move the point from EAX to EDX/ECX without suppressing its global candidate.
Determine which interference/liveness difference causes those assignments
before another source search. The previous global-homes packet has the
rounds decoder. Barrier-only, inverse-rotation-only, and the recorded
branch/barrier/cast combinations are now disproved; do not repeat them.

Copy `.py.txt` and the three `.cpp.txt` files to a directory two levels below
the repository root, dropping only `.txt`. Run `generate.py`, `identity.py`,
and `recombine.py`, then `search.py FAMILY` sequentially for `readwrite`,
`write`, `uniform`, `identity`, `recombine`; run `regions.py` with those names.
Do not run the generated unsupported `read` family. To reproduce traces:

```text
python3 build/<directory>/global.py early-barrier readwrite/v0160.cpp > build/<directory>/early-barrier.out 2>&1
python3 build/<directory>/global.py early-identity identity/v0008.cpp > build/<directory>/early-identity.out 2>&1
python3 build/<directory>/analyse.py
```

The ledger check passed before work. This is a partial research handoff, not
a byte-exact recovery or a linking repair. Continue only 0x758DE0 next session.
