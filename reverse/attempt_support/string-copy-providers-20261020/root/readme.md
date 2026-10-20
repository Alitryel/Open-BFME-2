# Root causality controls

`inputs.json` reconstructs 29 measured source variants using pinned production
blobs and the primary source preserved under `../frames/`. `results.json`
contains the actual 93 diagnostic results: three caller/helper checks per
variant plus a separate canonical worker check in six worker variants.
Nine older records use `role`; the others use `target` for the same label.

| Hypothesis | Controls | Result |
| --- | --- | --- |
| Full optimization restoration or intrinsic policy | 3 | 740/copy41 exact; replacement501 still has the wrong frame. |
| Genuine non-template copy worker, eager versus late visibility | 6 | Ordinary leaf gives correct worker41 but neutral outer5; forcing leaf gives outer41 but insertion964. Replacement stays wrong. |
| Empty type-query forcing causes the dead-slot loss | 7 | All740/copy41 exact; replacement frame unchanged atFC. |
| Individual copy-dispatch forceinline boundaries | 7 | Forced imported inner preserves740/41 but not501; ordinary imported inner produces719/36. |
| Nonstatic templated member move carrier | 3 | 740/41 exact;501 frameFC and wrapper116/134 remain. |
| Compiler flags alone versus optimized dispatch | 3 | Original O2/off and Od/off preserve740/501 plus wrong68. Optimized original dispatch gives outer5 and wrong501. |

These are source-context experiments, not admitted bodies. No result repairs
the caller-frame prerequisite. Neither a readable source nor the correct41-byte
leaf is enough when the caller or a provider still differs.

Materialize and validate every source hash without compiling:

```sh
python3 reverse/attempt_support/string-copy-providers-20261020/root/replay.py
```

Add `--case query-force-0 --run`, for example, to run that control through the
normal diagnostic CLI. The expected mismatch remains visible in the output;
`explain_mismatch.py` can return zero for a mismatch. Files are written only
under `build/string-copy-providers-replay/root/`.
