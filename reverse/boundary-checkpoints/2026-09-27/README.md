# Function-boundary discovery checkpoint — 2026-09-27

This checkpoint preserves the accepted additions from 42 local discovery
batches. These are anonymous machine-code boundaries and entry evidence.
They do not establish original class/function names, layouts, or recovered C++.
No source, ledger, symbol pin, or canonical Ghidra inventory is changed.

## Result

| Inventory | `.text` entries | Body bytes |
| --- | ---: | ---: |
| Original saved Ghidra inventory | 74,555 | 7,317,505 |
| Validated additions | 5,038 | 342,601 |
| Combined local map | 79,593 | 7,660,106 |

The combined map covers 94.6043% of the 8,096,994-byte `.text` section.
The original inventory remains inherited analysis, not independently proven
source recovery. Its full export has 74,561 starts including six outside `.text`.
Body ranges can be noncontiguous: never interpret the summed body size as
`entry + size` to find the end.

The final census uses ledger snapshot
`9f02df9f2c7f45d2bbdeda25d9ae89138ea1d0e0`: 112,712 decoded orphan bytes and
195,150 unexplained bytes remain, alongside defined data and probable padding.
These historical counts are not the current ledger's recovery percentage.
The checkpoint was prepared after rebasing; the preparation HEAD is recorded in the manifest.

## Files

- `validated-entries.jsonl`: one record per accepted entry, including batch,
  actual ranges, entry provenance, exits, historical ledger overlaps, and the
  SHA-256 of retail bytes concatenated in the recorded range order.
- `ranges.tsv`: only the accepted additions, with exclusive range ends.
- `seeds.tsv`: anonymous seeds with **zero sizes**, preserving inferred extents.
- `batches.json`: per-batch results, ledger/image hashes, review notes, and
  supporting switch/tail-dispatch evidence.
- `held-entries.json`: unsuccessful probes still unaccepted at this checkpoint.
- `reanalysis-review.json`: the isolated seeded run's candidate entries and
  changed bodies, compared with batch 39. `accepted_since_comparison` lists
  the subsequent accepted additions; other candidates require review.
- `manifest.json`: image/tool versions, export hashes, census, artifact hashes,
  and the original project's integrity check.

## Evidence standard

Entry evidence includes target-checked initializer/dispatch/parser tables,
direct calls, installed vtable slots, RTTI structures, and callback argument or
store paths with checked invocation sites. Per-entry records and batch notes
state the particular basis. Reference-source context does not confer a target
identity. Address proximity and instruction shape alone are insufficient.

For accepted additions, read-only Ghidra probes inferred ranges without forced
sizes. Independent Capstone checks compared instruction extents with Ghidra,
walked control flow, checked exits and applicable switch/tail evidence, and
rejected conflicts with the existing map or another accepted body. Two corrected
orphan decodes and manually supplied switch references are disclosed in the
batch notes. An indirect tail with a proven restored stack still has an
unresolved runtime target; its recorded evidence does not claim a callee name.

The follow-up auto-analysis ran on a copy of the saved project with 5,019
zero-sized seeds. It exported 79,788 `.text` functions: 214 unsupplied starts,
97 outside prior bodies, and 111 changed prior bodies. No prior entry or seed
was lost. Coverage gained 3,359 bytes and lost 71 relative to batch 39, which
is why its map was not adopted wholesale. Batches 41–42 independently accepted
16 direct callees / 1,273 bytes from that result. Batch 40 separately accepted
three function-object callbacks / 295 bytes. Original project hashes remained
unchanged.

## Check and resume

From the repository root, with the retail baseline and Capstone available:

```text
python tools/check_boundary_checkpoint.py reverse/boundary-checkpoints/2026-09-27
```

To additionally reproduce the combined count and check against the exact
original range export retained on the discovery machine:

```text
python tools/check_boundary_checkpoint.py reverse/boundary-checkpoints/2026-09-27 --baseline-ranges build/ghidra/boundary-audit-20260927/function_ranges.tsv
```

The checker verifies artifact/image hashes, complete decoding, sizes, unique
entries, disjoint addition ranges, and zero-sized seeds. It does not rerun the
per-batch Ghidra or semantic/control-flow proofs. Their scripts, raw probe
exports, logs, and projects remain local under the manifest's `local_artifacts`
paths, outside this compact checkpoint. Reconstructing that analysis environment
is separate from checking the committed evidence.

Resume with the stored-address candidates and changed-body queue. Review each
entry and actual range before promotion; retain the 71 lost bytes for explicit
boundary review. Do not seed the structured-data gap at RVA `0x629f20` merely
because it remains unexplained. Source recovery remains paused at this
checkpoint; any future landing needs identity/provenance and the normal byte
verification and commit gates required by `AGENTS.md`.
