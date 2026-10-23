# Copy-helper provider repair and caller-frame investigation

Continuation of `../string-copy-context-20261020/`, using BFME2 input
`a8a094883d9c9a0d21d4c966b70cf6263d7defd8` and committed BFME1 donor
`4483e88da1c2f3b9a273f779baac7458bd8bb891`. Three GPT-6 Astra ultra seats
prepared source/context experiments and independent audits; the root ran the
compiler diagnostics, production gates, and Git operations. Original retail
inputs were not modified.

## Production outcome

The fill insertion at RVA `0x00029530` remains exactly 662 bytes. Seven
imported-inline ownership annotations remove ten unused emitted definitions;
five of those were conflicting providers at known native addresses. All ten
surviving function definitions retain their complete bytes and relocations.
There is no new function, pin, alias, helper reference, DLL import, or linker
directive. `audit/production.json` preserves the before/after inventory.
The normal byte gate, declaration check, and new-COMDAT-variant check pass.

This is a provider-debt reduction, not new recovered bytes or a fully linked
unit. Its remaining known wrong provider is the original 68-byte mutable-copy
helper bound to the 41-byte native body at `0x000179B0`. The published census
at `e7a7769fe5` predates the fill unit, so ordinary `link_check` cannot preview
its LINKED-byte contribution. No verification runner or census was started.

The older range-insertion unit now declares its first-reference-on-equality
`max` in the actual `_STL` namespace. The global owner has different equality
semantics. Its 848-byte insertion, 511-byte replacement, and all other emitted
definitions are unchanged. This source-identity cleanup removes no production
provider: the original unit did not emit `max`. Both ledger rows pass the
normal byte gate. Existing other link blockers remain; the census preview
reports zero LINKED-byte gain.

No ledger coverage was added. The two source changes are committed separately.

## Unresolved shared-copy closure

There are now five consumers, including the newly landed fill insertion.
The optimized explicit specialization plus imported-inline inner helpers gives:

| Context | Verified complete bodies | Remaining constraint |
| --- | --- | --- |
| Older range unit | 848 / 511 / copy41 | Banked; requires the same specialization before first use in every consumer. |
| Fill unit | 662 / fill48 / copy41 | Same scope requirement; production keeps the original copy68. |
| Newer range unit | 740 / copy41 | Replacement501 reserves `0xFC` instead of native `0x118`. |
| Counted wrapper | shared740 / copy41 | Frame loses eight bytes; emitted116 instead of native149. |
| NUL wrapper | shared740 / copy41 | Frame loses eight bytes; emitted134 instead of native170. |

The independently checked primary-template candidate also gives 740/copy41
without adding an explicit specialization, but retains the same frame failure.
It cannot be mixed with explicit-specialization banks to bypass the scope rule.
The named inner `__uninitialized_copy` has an existing 21-byte native owner at
RVA `0x004598CC`; its wrong 41-byte copies cannot be repinned to the copy41
owner. Imported-inline expansion suppresses those copies without leaving any
undefined, direct, data, import, or directive reference to them.

For replacement501, first mismatch is operand byte `+0x5`, RVA `0x0002B055`.
The caller's named/live local offsets remain intact; its receiver and four
compiler result slots move by `0x1C`. For the wrappers, the first differences
are RVA `0x0002AB43` and `0x0002ABE5`; displacement-width changes explain the
shorter bodies. The frame maps and their independent checks are under
`frames/`. No arbitrary padding, empty constructor, assembly, renamed callee,
or verifier exception was used to force those frames.

Tested explanations include compiler-policy restoration, authentic copy-worker
visibility, query/dispatch inlining, storage/base and allocator-proxy layout,
the actual allocator rebind path, traits/max boundaries, and const/nonstatic
move/copy member ownership. They did not close the frame gap. The pre-existing
replaceBase frame mismatch (`0xC0` versus native `0xC4`) also remains; the new
copy context yields `0xB8` there. This body is not newly claimed as exact.

The precise prerequisite is a source-supported declaration/inlining context
that preserves these caller reservations while emitting the native copy41
provider consistently in all five units. Original TU/compiler inline-context
evidence, or a compatible donor unit compiling to the caller and helper
together, would address that missing fact. Additional readable disassembly
alone does not establish the source context. Confidence is high in the measured
byte/relocation and frame deltas; the original cause of the reservations is
still uncertain.

## Reproduction

`providers/replay.py` materializes four hash-checked banks from the pinned
input revision. `frames/replay.py` reconstructs selected source-context controls.
`root/replay.py` reconstructs all 29 root controls from recorded edits and checks
their hashes. These commands write only under `build/`; their `--run` options
use the normal `tools/explain_mismatch.py` CLI. See each subdirectory README
and `--help` for selection and audit commands. Diagnostic exit zero does not
mean exact bytes: retain the reported size, classification, and relocations.

The compact hypothesis/result tables distinguish positive provider repairs
from rejected frame hypotheses. The underlying full-copy candidates remain
evidence, not matched source or credited progress.
