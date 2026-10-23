# String-copy provider ownership controls

This packet records compiler diagnostics prepared by the reference seat and
executed by the root seat. It changes no production code, ledger, pin or gate.
The parent owns integration and normal whole-unit verification.

Inputs are BFME2 `a8a094883d9c9a0d21d4c966b70cf6263d7defd8` and BFME1
`4483e88da1c2f3b9a273f779baac7458bd8bb891`. The reviewed STLport sources and
headers are unchanged from donor `92f6bbe8`; this continuation did not repeat an
unchanged reference sweep. `inputs.json` records original Git-blob hashes,
candidate hashes, target names and flags through the preserved source patches.
`fill-original.cpp.txt` freezes the fifth consumer before production edits.

The exact checked-in header version macros differ: local
`vendor/stlport/stl/_config.h:56` defines `_STLPORT_VERSION` as `0x452`, while
BFME1's `inputs/vendor/stlport/stl/_config.h:56` defines `0x460`. The preserved
production comments label the family 4.5.3; that label is not a claim that the
two header sets or versions are identical. These controls retain BFME2's local
headers and toolchain. Donor 4.6 provides semantic comparisons, with target bytes
and call relationships proving the BFME2 behavior separately.

## Measured results

| Control | Complete matching bodies | Provider result and limit |
| --- | --- | --- |
|30/31|Older insertion848, replacement511, copy41|Imported forced-inline inner helpers disappear with no import edges. The optimized char-pointer specialization must be visible consistently in all five consumers.|
|32/33|Fill insertion662, fill48, copy41|Same specialization and ownership result; also requires all-five consistency.|
|40|848/511/41|Correcting the older max namespace preserves bytes, but emits45B against the existing17B owner.|
|41|848/511/41|Correctly named max is inline-only; no global or namespaced max definition or edge survives. Best older full-copy bank.|
|42|662/48; original copy68 unchanged|Three ownership attributes remove the conflicting inner-copy definitions. No outer specialization or algorithm change.|
|44|Same as42|Also removes unused namespaced max45.|
|46|Same as42|Also removes unused size22, whose native owner is6B.|
|47|Same as42|Also removes the unused null-construction26/19B copies, whose native owners are10/10B. Final provider-only bank.|
|43/45|Original848/511 and original copy68 unchanged|Original older object never emitted max. Namespace repair is source-identity cleanup, with zero provider or byte credit.45 uses ordinary inline and no needless import attribute.|

The original 68-byte copy's complete raw SHA256 is
`038f7ab27195d2771e676cdc8f12fddab747c34e92387187933fe182da8fb593`;
its sole REL32 operand at `+0x39` names the canonical `__copy_trivial`.
The correct41-byte provider has raw SHA256
`07d84357dc85cbcdfcfccbb4e7b9f4c6e342b9f26802457e6d29523d941653a4`
and sole DIR32 operand `+0x1E` to `__imp__memmove`. Full definitions and fixups
for the selected banks and baseline are retained in `results.json`.

The older original replacement precedes an alignment byte and its insertion
in one COFF section. Some diagnostics report1360 section bytes; the function
remains511 bytes plus one CC alignment byte, bounded by the next typed symbol.
No1360-byte replacement is claimed.

## Source and ownership evidence

Local and BFME1 `_algobase.h:79` define namespaced max as `a<b?b:a`, returning
the first reference on equality. Existing `_STL::max<unsigned>` at13740/17
has that contract. The global owner9FDE5/16 instead returns the second reference
on equality (`DataChunkTableOfContentsRead.cpp:59`). Therefore moving the old
helper into its authentic namespace is an identity repair, with no new pin or
alias. Suppressing the incompatible global definition alone is not the repair.

The fill getter and null construction match local `_string.h:416` and328–334:
finish-minus-start, writing a null character, and forwarding through the
integral-character tag. Existing owners are size73D0/6, null665B20/10 and
null_aux13730/10. These helpers are completely inlined into the verified662
body and have no remaining references in the candidate object.

The repository already uses visible `__declspec(dllimport) __forceinline`
definitions to retain inline expansion without a competing local provider,
including `stlport_pod_vector_bodies.cpp` allocator-proxy deallocation and
`Rva0009D9BDFinish.cpp` vector accessors. The annotation does not claim a new
retail DLL import. Any surviving direct or import edge to a suppressed helper
falsifies this use. No new weak identity, alternate name, source padding or
retail address is introduced.

The full41-copy banks are **not a complete shared repair**: the newer501
replacement and149/170 wrappers still require a compatible source/inliner
context, and an isolated explicit specialization cannot be admitted. Earlier
primary-template timing controls are summarized in `results.json`; the original
root packet retains the best primary source. The provider-only bank deliberately
preserves the original68-byte outer copy and makes no claim that the unit links.

## Replay

Prepare all four saved controls, without compiling:

```sh
python3 reverse/attempt_support/string-copy-providers-20261020/providers/replay.py
```

The generator reads the pinned input commit with `git show`, checks its hash,
applies the tracked patch, and checks the exact measured output hash. It writes
only `build/copy-provider-replay/`. Cases are `older-full-copy`,
`fill-full-copy`, `fill-providers`, and `older-identity`.

Add `--case fill-providers --run` to invoke the normal `explain_mismatch.py`
diagnostics. That case is expected to match662/48 and still report68 versus41
for the legacy copy. A diagnostic's exit zero is not a gate or link pass.
Production whole-unit gates and independent provider audits are separate.
