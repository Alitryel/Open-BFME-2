# Link provider reassessment, 2026-10-24

Inputs: BFME 2 `1cdea68ab6`, BFME 1 checkout `f5140c1c`, published
census `11b3872700` (2026-10-23 23:06, retail-truth-4). No production
source changes or new linked-byte gain. All numbers below are current-object
legacy predictions; neither self-strict nor closed-strict gains are claimed.

## Changed prerequisite evidence

The current three-provider preview of ProductionPrerequisiteRecVectorCopy.cpp,
ProductionPrerequisiteCopyCtor.cpp and
stlport_vector_stringrecord_2cf5b1_allocate_copy.cpp reports all three linking,
145 -> 437 B. This supersedes the failing selection described in
link-seat-selection-recheck-20261024.md for these current objects. There is no
new repair here to credit. Both file claims and both worker/parent RVA claims
were released after this check.

Fetched official BFME 1 master `242ea837f5d27517edde485235954e111e8b7e1b`.
Reviewed its prerequisite specializations (`242ea837f`, `226c5abf7`) and
StringBase map-index repair (`f83d0355a`). The prerequisite principle is
already satisfied by the current preview. Existing BFME 2 string and map
failures retain their documented parent-codegen/type prerequisites; these
donor commits do not prove a new target repair. The submodule scope is
foreign-claimed. Kept the verified checkout/pointer unchanged and did not
write a successful freshness stamp.

## Shroud updater contract

Rva0073CE30.cpp has two native 96 B wrappers at 0x0073CE30 and 0x0073CC60.
Its current preview remains 0/192 B, with competing derived updater tables
`??_7Rva0073BB40@@6B@` and `??_7Rva0073BAA0@@6B@`.
The separate constructor and predicate providers already link; their current
gain relative to the old census is inherited, not this session's work.

Target facts: the two derived table slots at VA CF13A4 and CF13A0 point to
the rowed 106 B and 146 B callbacks 0x0073BEA0 and 0x0073BE00 respectively.
BfmeCellAt.cpp owns these under Rva0073BEA0 and Rva0073BE00, with a grid at
+4 and sink at +C. The wrapper arguments are 16 B updater values.

Current private views disagree: Rva0073CE30.cpp inherits a `char(int,int)`
predicate without an override, while Rva0073BB40.cpp declares pure derived
overrides. The callback owners declare `void(int,int)` virtuals on separate
16 B views. Making the tables agree by copying either private view would not
establish the native callback contract. Reconcile owner identity, return type,
and by-value raster consumers together before changing these wrappers. No
alias, table-suppression or source trial was made. This is a class/provider
prerequisite, not an unprovided callback body.

## Other lanes and checks

Checked link_rank top 30, near 2, unresolved and owner-gap rankings;
class_views --blockers; repair_queue link. The read-only receipt-current,
unclaimed-object probe found 26 failing previews / 6,660 census-sized bytes.
It is triage, not a repository-wide exhaustion proof: a preview which omits
a current peer can still report an inherited failure.

Direct current previews also show AptAnimation.cpp, BfmeResultSourceA.cpp,
Rva003F86F9Ctor.cpp and Rva00600352.cpp already linking. Existing PoolDelete
destructor trials, mutable string helper lifetime trials, shader singleton
ownership and PartitionFilter/Debug virtual-contract evidence remain the
specific blockers; no unchanged failed trial was repeated.

name_globals --dry-run offers zero edits. The read-only rehome rescan again
finds the known 100 split candidates and EntryCtor placement; stopped after
the leading pairs because the previous handoff already verifies that exact
placement adds no linked bytes. No matching data-back measurement artifact
exists. No census, full link cycle, nightly or boot runner was started.

check_csv passes. progress.py origin/master reports +0 coverage and linking
deltas. Source and banked attempts are preserved; all session claims are
released. Resume when native class/provider evidence or the current objects
change, rather than repeating the same zero-gain trials.
