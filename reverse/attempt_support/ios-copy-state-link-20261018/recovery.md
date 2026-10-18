# Recovery disposition, 2026-10-18

The original preparation rebase is complete. The earlier recovery skipped
a8d75f0c66 because upstream 22e3f49ede already supplies the complete Apt
tables, including padding. The stream repair and blocker evidence were
replayed without content changes as bfc8c03474 and d023679cd3.

Against upstream d504d305c6, the stream repair still passes self-strict
provider preparation (1/1 byte row, three literals, thirteen imports).
The same-index legacy prediction remains 0 -> 429 linked bytes. This is
not closed-strict or full-link evidence.

The required dry-run push completed the ordinary full gate: 96639/96639
function rows and 950/950 data rows passed, as did literals, imports,
pins, module registry, source claims and no-op patch verification. The
sole failure is the pre-existing external vtable name
`??_7Rva0007DF07@@6B@` resolving to both 0xBC6F20 and 0xC7A630.
Upstream already documents the same failure in
reverse/attempt_support/bfme1-freshness-38ca-20261018/readme.md.

Recovery instructions permit taking an unpublishable source change out
in a new commit while preserving its attempt. The stream source is
therefore restored exactly to upstream; deferred-repair.patch preserves
the complete verified fix (apply with git apply --unidiff-zero).
Reapply it after the shared vtable identity
conflict is repaired, then rerun the byte gate, self-strict preparation,
paired legacy preview and required full push gate. The earlier solved
record is superseded by a publication-blocked record. No current linked
byte gain is claimed for the deferred repair.

All six untracked reverse/zh_sweep files restored by the earlier recovery
are byte-identical to stash 554a3953247d5ff2fcd614fbec193c09e02b89f8^3;
the stash has no tracked edits. They remain untracked generated sweep
artifacts. The stash and refs/runner/preparation/1792340332734527920
remain intact. No additional work was selected.
