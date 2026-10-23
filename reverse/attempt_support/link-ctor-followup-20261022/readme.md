# C-string constructor link follow-up, 2026-10-22

Inputs: parent d15f845cf3, BFME1 37c3022de1, published legacy index
08160bc2c9 (2026-10-22 17:08). No donor change or closed-strict measurement.

Current three-source preview: PeerThreadNickError 0/394 B,
MainMenuUtils_hasWriteAccess 0/233 B, stlport_money_put_long_double 0/184 B.
Each has only the referenced non-retail C-string constructor COMDAT blocker.
This extends the prior link-string-ctor-20261022.md sweep to independent units.

Declaration-only specialization changes the nickname allocator argument
EBP+0x0B to +0x0F and the two-byte nickname suffix +0x0E to +0x12;
registry default allocator arguments cease sharing EBP-0x0D (become
-0x0D/-0x0E/-0x0F/-0x10); money_put frame grows 0x4C to 0x50.
The nickname cleanup becomes ambiguous after label renumbering and money_put
loses the first cleanup row. These are real changed parent bytes, not a
verified false reject. No workaround to funclet admission was attempted.

Second trial in the registry caller: explicitly share one allocator across
all four string temporaries. All four use EBP-0x10, and the first registry
result branch loses a redundant test sequence (body 222 versus retail 227 B).
The adjacent patch preserves this diagnostic trial. Other two units restored
after one distinct trial; registry restored after two failed byte builds.
The original constructor remains required for its local escape/lifetime
summary. Future work needs a different compiler/lifetime explanation or a
retail-correct emitted constructor, not the same declaration-only trials.

Local full transcripts: build/seat-link-current/ctor-{before,gate1,gate2}.txt.
No authored coverage or linked-byte gain was retained.

Grid mapper follow-up: the existing /O1-override suggestion was tested, rather
than assumed sufficient. With the complete virtual order carried from the
existing bfmemapper header, normal region /O2 preserves both row bodies and
reduces three blockers to the sole RefCountClass deleting destructor. A local
FLAG_DEFAULTS=off /O1 /arch:SSE /G7 build fails both rows: copy construction
stops inlining Reset (127 -> 80 B) and Reset changes its branch/tail shape.
Thus a whole-file /O1 override alone is not a repair. No protected file was
changed; the adjacent patch preserves only the supported virtual declarations.
Paired current mapper/Grid preview remains 8,123 -> 8,123 B; Grid itself 0/174.
Sources restored. Rehoming discovery could not run: the downloaded published
index has no build/link_census/census.log; no census was launched to create it.

FontLibrary follow-up: declaring the existing virtual init override in the
constructor view removes its undefined abstract-base init reference and passes
all 3 byte rows (1 string literal). It does not repair linking: the retained
FontLibraryFontList view emits a different vtable. The paired current preview
remains 1,245 B (FontList 285 + Init 960); constructor remains 0/139 B. The
960 B Init gain relative to the old census already exists before this change.
Retail VA BE5AD0 begins with deleting dtor 2189A9, init 217561,
loadIniFilesFromLegend 1B5384 and the SubsystemInterface virtual order; reset
is slot 9 at 218BEF. FontList instead declares most slots pure. Copying that
view would hide a known native mismatch. A supported full class/vtable
reconciliation is the prerequisite. Source restored; declaration-only patch
is diagnostic evidence, not a proposed repair. No closed-strict gain claimed.

Session queue assessment: link_rank top 30/near 2 and class_views --blockers
were reviewed. Current-object previews covered 272 eligible near-blocker
units across 4 filtered batches: 66 already link with current providers,
while remaining candidates need substantive identity, ABI, missing-provider
or compiler/lifetime work. No census-to-current gain was counted as ours.
name_globals --dry-run found 0 edits. repair_queue link was reviewed; its
leading items repeated existing blockers or already-fixed units. Rehoming
discovery is unavailable without the missing published census.log artifact.
No census, full link cycle, nightly or boot runner was started.

BFME1 donor review: verified committed pointer 37c3022de1; official master
aef2f16877 was fetched. Updating the donor is blocked by another live
file:reference/open-bfme-1 claim, so the checkout, pointer and freshness stamp
were preserved. Reviewed repairs b3c535569, 4c4394701 and 0a4cb4954; no
identical applicable BFME2 repair was established. This is not a successful
freshness check.

All trials in this handoff used model=gpt-6.1-sol.
