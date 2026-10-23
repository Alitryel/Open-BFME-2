# Direct allocator-provider binding repair

## Preparation recovery on 2026-10-14

The original evidence below describes the pre-rebase four-consumer repair.
Recovery rebased its saved commit e467089e3e onto 6b844bcadc3569bf77314b122fd948a98b02096d.
Upstream commit 147cfae2cb6be9a8364ab8e80e4fbb535371fc1b already contains the
BfmeConv583 and BfmeThreeHundredFiftyFive direct-delete repairs, their pin
removals and provider alias removals. Their source files are retained byte
identical to upstream; redundant delete declarations are not reintroduced.
The recovered delta binds BfmeConv1039 and Rva005B7DC3Box directly to scalar
new, removes their two pins and one remaining provider alias, and preserves
all unrelated upstream mem_ops removals. No commit was skipped or rebase aborted.
The baseline keeps merged scalar-delete/array-delete pin counts at 6/36 and
reduces scalar-new pins from 4 to 2. Net recovered hatch reduction is three.

Recovery evidence is in recovery/. The independent byte gate and bounded
link_check --prepare-current both verify 8/8 matched rows across the five
original providers/consumers. The retained original COFF snapshots still prove
all five current objects self-strict, unchanged section bytes/extents/external
definitions, and all four retail allocator targets. The same cb660e4d97 census
index remains in use; its hash matches the original evidence. The local preview
again reports 3/5 units linking and 162 -> 162 legacy LINKED bytes, with exactly
the original after-repair blockers: Consume, Xform and _bfmeVftUD. Its exit 1
reports those pre-existing blockers, not an allocator regression. The three
already-clean providers/consumers are checked separately for a clean exit.
No new authored bytes, closed-strict linked gain or new census measurement
is asserted. CSV, declared definitions, pins, classes, and both data checks pass.

The preparation stash 3cd6e8d4e25dde0d842d9a16bd18ec5267aa2edc contains no
tracked edits. All six untracked ZH sweep files were restored with --index
and checked byte-for-byte against its untracked parent. They remain untracked
for their original work; they are not part of this allocator repair. The stash,
backup ref refs/runner/preparation/1791955861566613587, original build snapshots,
and preparation record are retained. No new task was selected and no donor
update, census build, full link cycle, nightly or boot operation was started.

BFME 2 base: cabfdc16e1ddc08c2fa3480ffca474b6d3341f52. Discovery used
repair_queue.py link, link_rank.py and supported BFME 1 allocator repairs.
Committed discovery status measures 67e1365aa9; both local previews use
cb660e4d97 (2026-10-13 04:02), SHA256 in index-meta.json. These are distinct
measurements. No census/index/status/history or per-row artifacts changed.

## Supported change

Bind four existing consumers directly to the real scalar operators in mem_ops:
Rva005B7DC3Box::Run and BfmeD1039::bfmeGo1039C use operator new(unsigned int),
and BfmeThingCDE::bfmeGoCDE and BfmeThingUD::bfmeKillUD use operator delete(void *).
Remove their four obsolete symbols.csv pins and the three matching provider
alternatename directives. The keyed hatch baseline shrinks by four pins and
three directives. No other source users of these removed spellings remain.
No new pin, alias, declaration marker, layout or compiler setting is introduced.
Existing consumer names and semantic provenance remain unchanged.

Target evidence: functions.csv owns scalar new at 0x0002FDA0 (19 bytes) and
scalar delete at 0x0002FD60 (21 bytes). Both operators and their array siblings
independently pass the byte gate. The four consumers' retail REL32 operands
reach precisely those scalar operator bodies. object-proof.json records each
native destination and relocation offset. This establishes allocator identity
independently of the donor's address or spelling; no new class-layout identity
is asserted. Integer allocation constants 0x28/0x38 have identical unsigned
representations, and the cdecl stack ABI is unchanged.

All five self-strict before/after objects have identical non-debug/non-directive
COFF section bytes, sizes, flags, section positions and external definitions.
The only relocation referent changes are the four wrapper-to-operator names;
provider code is unchanged. The proof checks every section and its relocations,
all four native matched call operands, the provider definitions, absence of the
old names, and current reusable strict receipts. Scratch proof and original
objects are retained under build/allocator-link-20261014.

## Donor review and freshness

Official master was fetched; reviewed fea964f85433012ec0c95a44a8d88f77b4c29af5
(direct operator calls in 33 files) and e0c623620c077cc216eb49c8e74c16e6349a9a7d
(direct delete calls in three files). BfmeConv583 and BfmeThreeHundredFiftyFive
are supported donor leads; the same cause was independently checked in the
two allocation consumers. Their direct-provider principle is applicable;
BFME 1 addresses were not imported. Verified checkout/gitlink remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Prior full old-input baseline evidence
records unchanged-input MSVC hangs; later evidence records compiler-lock and
stale-TU preparation blockers. No unchanged blocker was retried and no freshness
success stamp was written. The overdue comparative donor update is outstanding.

## Acceptance and limits

- Bounded link_check --prepare-current before/after: 8/8 exact matched rows
  across all five sources, strict reusable receipts, no skipped or baselined
  literals/imports. The independent ./build.sh gate also passes 8/8.
- Same-index legacy local link findings: four before, three after. The allocation
  stand-in in Rva005B7DC3Box is resolved to the real new definition. Other findings
  are identical. BfmeConv1039, BfmeConv583 and mem_ops continue to LINKS; the other
  two consumers remain excluded. Cohort LINKED stays 162 -> 162 bytes.
- Authored C++ byte delta is zero. Self-strict object receipts and legacy local
  improvement are proven; strict closure and closed-strict linked gains are not.
- Placement rescan: zero bodies, zero pins. Declared definitions, CSV, pin
  consistency, canonical class and converged/shadow data checks pass. Final
  commit/push hooks are required without bypass.

Remaining local findings: Consume and Xform in Rva005B7DC3Box; _bfmeVftUD in
BfmeThreeHundredFiftyFive. Remaining mem_ops aliases serve other consumers and
are outside this batch. Full census/current closure and donor comparative gate
remain outstanding. No full census, link cycle, nightly, boot or scheduler
operation was started. Unrelated untracked reverse/zh_sweep preparation retained.
