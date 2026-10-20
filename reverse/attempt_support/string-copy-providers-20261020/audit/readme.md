# Independent provider audit

The integrated fill consumer removes ten definitions without changing any of
its ten surviving function bodies or relocation tuples. Known wrong providers
fall from six to one. This is provider debt reduction: zero newly recovered
retail bytes and no claimed linked-byte gain. The published census did not
contain this source, so an ordinary link preview could not establish placement.

`production.json` compares the frozen original source with the integrated
`Code/Libraries/Source/WWVegas/WWLib/stlport_string_insert_fill.cpp`, including
the explanatory comments. `replay.py` reads current cached COFF objects,
rechecks their inputs before returning, and never compiles or changes a cache.
It records every defined function's complete span hash, body hash, relocation
fields, native anchor verdict, symbol residue, imports and linker directives.
Both objects have no runtime data sections. Debug records differ with source
paths and are not runtime data or body evidence.

## Before and after

| Control | Definitions | Wrong known providers | Complete surviving bodies |
| --- | ---: | ---: | --- |
| Original | 20 | 6 | Baseline |
| 46: inner helpers, max, size | 12 | 3 | All 12 unchanged |
| 47, integrated: also null construction | 10 | 1 | All 10 unchanged |

Seven annotation sites remove ten emitted definitions: `__copy_ptrs` (25 B),
`__copy_aux` (50 B), `__uninitialized_copy` (63 B), `_IsOKToMemCpy` (16 B),
the two `_Ret` queries (16 B each), namespaced `max` (45 B), `size` (22 B),
`_M_construct_null_aux` (19 B), and `_M_construct_null` (26 B). No definition
is added. None of these names, their import slots, or their references remain
anywhere in the final COFF symbol table or section relocations.

The only import remains `__imp__memmove`; default-library directives are
unchanged. Flags remain `/O2 /Ob1 /DNDEBUG /MD`, with the source's existing
optimization regions. No pin, helper name, algorithm, tag type, explicit
specialization or new optimization pragma is introduced.

Whole native anchors remain exact: insert 662 B at RVA `0x29530`, fill 48 B at
`0x237C0`, and fill_n 37 B at `0x24970`. The insertion ends at `0x297C6` and
has twelve relocation fields: four calls to `0x179B0`, two to fill, two to
char_traits::assign, and one each to the memmove IAT, allocator, empty destroy
and free. The receipt records every operand offset and resolved target; no
trailing bytes are omitted from the survivor comparison.

The legacy mutable-copy definition remains 68 B, raw SHA256
`038f7ab27195d2771e676cdc8f12fddab747c34e92387187933fe182da8fb593`,
with REL32 `+0x39` to canonical `__copy_trivial`. It still fails its 41 B
native destination `0x179B0`. That destination's real provider is unchanged;
the existing pin is not evidence that the 68 B definition is correct.

## Inputs and interpretation

The original Git LF source SHA256 is
`b23dea147dc32bfbe7f481c7112b429ce9d17eeb9f2279c9f5dcb7b276bec5e8`.
Its original CRLF working file had hash
`5ee964320b12acfb947209bccb7eef47d12639f76c7fec80de3bc3f2471c8e1f`.
The full before/after source and object hashes are in `production.json`.
Control 46 source hash was
`2192e570aa8cc712862275ee6e788d9e231ad204e70761bec9c6bd1040e1205c`;
its object hash was
`0fc2363684419aafc2c71aefc3aa595a427ba127f87c45d5ec8e75837be94b9c`.
Pinned revisions, original source and reproducible patches are in
[`../providers/`](../providers/readme.md).

Microsoft documents that imported inline definitions can expand without an
out-of-line instantiation. The measured absence of import edges is essential
here; the attributes do not claim that retail imported these templates.
See [Microsoft's inline import documentation](https://learn.microsoft.com/en-us/cpp/cpp/defining-inline-cpp-functions-with-dllexport-and-dllimport?view=msvc-170).
The production comments accurately describe this bounded emission result.

This audit does not establish a canonical class/template definition across
the repository's existing private STLport views. It introduces no outer
specialization. The broader 41 B specialization banks remain incomplete:
the same specialization must be declared before implicit use consistently
in **all five** consumers (both StringReplace units, BfmeConv1461,
BfmeConv1462 and this fill unit), with compatible definitions and lookup.
Equal emitted bytes alone cannot excuse a conflicting primary instantiation.
The older source's separate max namespace cleanup emits no fewer providers
than its original object and receives no provider/byte credit in this audit.

## Replay

The original measured receipt used the already compiled baseline:

```sh
python3 reverse/attempt_support/string-copy-providers-20261020/audit/replay.py --baseline-source build/copy-resume-provider/20-fill-baseline.cpp
```

For a fresh checkout, prepare the saved inputs with
`providers/replay.py --case fill-providers`. Its optional `--run` compiles
the candidate through normal diagnostics. Compile the prepared baseline
through the same normal diagnostic path:

```sh
python3 tools/explain_mismatch.py '?insert@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEXPADID@Z' --rva 0x29530 --size 662 --source build/copy-provider-replay/fill-original.cpp --context 2
python3 reverse/attempt_support/string-copy-providers-20261020/audit/replay.py --baseline-source build/copy-provider-replay/fill-original.cpp --candidate-source build/copy-provider-replay/fill-providers.cpp
```

The audit exits on missing/stale objects or malformed extents and reports
verdicts, including the retained wrong copy, as JSON. Its successful execution
is not a byte gate or link pass. Root separately ran the production unit's
normal gate (1/1), declaration and variant checks successfully.
