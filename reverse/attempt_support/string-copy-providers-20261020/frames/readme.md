# Caller frame investigation, 2026-10-20

This is blocked research, with no new recovered or linked bytes claimed. The
newer string insertion remains exact at 740 bytes and its shared copy helper can
be exact at 41 bytes, but the 501-byte replacement and 149/170-byte callers lose
compiler stack reservations. The full five-consumer shared-copy scope is not
closed. Separate provider repairs and their gates belong to the parent handoff.

Investigation: GPT-6 Astra; compiler executions: root Codex. This extends
`../../string-copy-context-20261020/`, after the incoming `a8a094883d` tree and
the new 662-byte string-fill recovery in `6798492d1a`. It does not repeat the
older extern-template/imported-outer experiments. Parent and reference seats
owned optimization-policy and provider-suppression controls concurrently.

## Reproduce selected controls

From the repository root:

```text
python3 reverse/attempt_support/string-copy-providers-20261020/frames/replay.py
python3 reverse/attempt_support/string-copy-providers-20261020/frames/replay.py --run
```

The first command only prepares five sources under
`build/string-copy-provider-frame-replay/`. It checks their exact recorded
SHA-256 hashes, the two production wrapper inputs, and the 17 compiler-header
dependencies. The second uses normal `tools/explain_mismatch.py` for 15 checks.
`--case primary`, `--case v21`, `--case v22`, `--case rebind` and
`--case shared-move` select individual controls. No Code source, ledger or gate
is changed. A successful replay means that the expected caller **failures** and
the exact insertion/helper results were reproduced; it does not mean that the
repair passed.

`primary01.cpp.txt` preserves the reference seat's primary-template candidate
verbatim, including old comments. Its inherited comment about reproducing
"both retail stack frames" is not true of this diagnostic: the 501-byte
replacement still has the short frame. Its declaration of `__copy_trivial`
also retains the existing spelling rather than establishing new name evidence.
The two strict patches retain only the additional allocator and shared-move
controls. `selected.json` binds all five generated outputs to the measured
sources. The selected replay is deliberately smaller than the complete result
matrix; it does not claim to regenerate all 31 controls.

## Inputs and source basis

The starting explicit-specialization candidate was the earlier tracked
`exact-copy-Od-depth6.cpp.txt`: `/Od /Ob1`, depth 6, exact 740/41 with the
501-byte replacement frame already short. The new primary candidate uses
`/O2 /Ob1`, ordinary functions under `#pragma optimize("", off)`, owner depth 6,
and EOF `#pragma optimize("gty", on)` for deferred template emission. Wrappers
retain their default inline depth. Only the forced inner
`__uninitialized_copy` carries `dllimport`; independent provider audit found no
emitted import references. Its ordinary outer entry is a primary template,
not an explicit specialization.

Source hashes and first-line flags are in `results.json`; compiler dependency
and source-reading hashes are in `inputs.json`. Compilation still selects
local STLport 0x452. The semantic reference is BFME 1's STLport 0x460 from the
previously recorded donor revision
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`; its source hashes are included so a
later checkout cannot silently stand in for the inspected files.

Source facts used in the new controls:

- `_String_base` owns start, finish and the allocator proxy's data pointer;
  the native three-pointer layout is independently established. Moving those
  fields into a base or an empty-base proxy did not restore the caller frame.
- Local `vendor/stlport/config/stl_msvc.h:103` disables member-template classes
  unconditionally on the MSVC path, selecting `_alloc.h`'s real
  `__stl_alloc_rebind` reference-return path. BFME 1's corresponding setting at
  line 138 is conditional on compiler versions below 1200; its VC7.1 path is
  different. These configurations must not be conflated.
- The rebind controls use a neutral state-free allocator view carrying those
  source bodies. They preserve the existing static raw allocation facade at
  RVA `0x307F0`, the zero-count guard, and the 12-byte string layout. No new
  canonical allocator ABI is asserted.
- BFME 1 `_string.h:841` supplies a non-template, const-pointer member `_M_move`
  backed by `char_traits::move`. Its generic overload at line 827 is an element
  loop, not the same memmove body. The const-pointer overload, actual
  `max<unsigned>` boundary, and `__char_traits_base<char, int>` inheritance were
  tested as separate causes. The selected shared-move control routes insertion
  and replacement through one such member instead of duplicate helpers.
- The actual VC7.1 POD dispatch uses empty trait values directly. There is no
  source basis here for an extra artificial trait-query wrapper or padding.

## Complete measured matrix

`results.json` contains **31 controls / 93 normal diagnostic checks**. IDs
00–30 below are local to this frame lane. The first runs of 08/11/14 omitted
the V22-only `bfmeMakeOX` declaration; those harness inputs failed to compile,
were repaired, and only their current hash-matching reruns are counted.
The matrix includes two listing controls and baseline controls, not 31 distinct
semantic hypotheses.

| IDs | Context change | Measured result |
| --- | --- | --- |
| 00 | Earlier exact-copy `/Od` baseline | 740/41 exact; replacement 501 bytes, frame FC |
| 01 | Storage moved into genuine base | Same as 00 |
| 02 | Empty-base allocator proxy and base deallocation | Same as 00 |
| 03 | Production source, listing flags only | 740/501 exact; wrong copy remains 68 bytes |
| 04 | 00 with listing flags only | Same as 00 |
| 05–06 | `/Od` specialization on untouched wrapper context | 740/41 exact; V21 116 bytes, V22 134 bytes |
| 07–08 | New primary-template helper on wrapper context | 740/41 exact; V21 116, V22 134 |
| 09–11 | Actual `max<unsigned>` template | Insertion 716; replacement 501/FC; wrappers 116/134; copy exact 41 |
| 12–14 | Actual char-traits base template | Insertion 645; replacement 467/CC; wrappers 116/131; copy exact 41 |
| 15–17 | Ordinary non-template const member move | 740/41 exact; replacement 501/FC; wrappers 116/134 |
| 18–20 | Same const member, forced inline | Same as 15–17 |
| 21–23 | Ordinary real proxy/rebind/allocator chain | Insertion 667 with unresolved outlined proxy/base calls; replacement 501/F4; wrappers 116/131; copy exact 41 |
| 24–26 | Force only those actual forwarding functions | 740/41 exact; replacement 501/FC; wrappers 116/134 |
| 27 | Copy-range helper becomes nonstatic member | 740/41 exact; replacement 501/FC |
| 28 | Move-range helper becomes nonstatic member | Same as 27 |
| 29 | Both range helpers become members | Same as 27 |
| 30 | One genuine const member move shared by insertion/replacement | Same as 27 |

## What the frame evidence establishes

`frame-map.json` records source, object and body hashes for a fresh read-only
comparison of current production objects against the primary candidate and
wrappers 07/08. It checks all instruction operand types/sizes/registers,
non-frame memory operands, branch-target instruction ordinals, and relocation
kind/name/raw addend. These agree apart from stack reservation and EBP-relative
homes. This is a diagnostic comparison, not a substitute for the normal
byte-and-relocation gate.

For replacement RVA `0x2B050`, both bodies contain 162 instructions and 501
bytes. Retail/production reserve `0x118`; the candidate reserves `0xFC`, first
different byte at `+5`. All live local homes from EBP-4 through EBP-0x48,
including the one-byte tags, remain unchanged. `this` moves from EBP-0x108 to
EBP-0xEC; four compiler result slots move by the same 28 bytes. The intervening
region has no directly referenced local homes in the emitted body. The MSVC
listings do not name those removed slots. Declined-inline temporary reservation
is the supported structural explanation, but the exact original variables or
inliner decision producing those 28 bytes remain unknown.

For V21 at `0x2AB40`, frame `0x84` becomes `0x7C`; its 43 instructions encode
in 116 rather than 149 bytes. For V22 at `0x2ABE0`, frame `0x88` becomes `0x80`;
its 48 instructions encode in 134 rather than 170 bytes. Both lose 8 bytes
between live local homes and `this`; V22's result slot also moves. Tag homes
EBP-5/EBP-6 stay unchanged. Instruction sequence, branch graph and call targets
are preserved, with shorter stack-displacement encodings accounting for the
body-size change. This does not justify adding artificial stack storage.

The incidental 285-byte `replaceBase` at `0x2A730` is already wrong in current
production: frame `0xC0` versus retail `0xC4`. The primary candidate changes it
to `0xB8`, a further 8-byte loss. The two calls remain erase `0x12150` at operand
offset `+0x7E` and insertion `0x28820` at `+0x10B`. This is a pre-existing
unmatched body, not a newly regressed matched row or a successful recovery.

The concrete unresolved prerequisite is a supported helper/compiler context
that preserves the newer callers' unused stack reservations while emitting
the correct shared 41-byte copy body and no conflicting providers. Layout,
const-member overloads, actual allocator forwarding and shared move identity
did not supply it in the measured contexts. Changes to control flow or added
dummy lifetimes would require new evidence; the measured bodies already retain
the native operation graph.
