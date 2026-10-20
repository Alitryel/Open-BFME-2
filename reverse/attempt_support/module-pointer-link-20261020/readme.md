# Pointer-vector helper visibility repair

Against the unchanged published legacy index b73720bed9 (2026-10-20 05:34),
Rva0056BF1FParse.cpp and Rva0056BDFCParse.cpp each fail solely on their emitted
vector<const ModuleData *>::_M_insert_overflow. LocomotorSetDoXfer.cpp fails on
that helper and __copy_trivial. These are current-object before/after findings,
not gains inferred from stale census source rankings.

The parsers' declaration-only proxy allocate, allocator deallocate, clear and
set specializations force calls where the rowed owner in ModuleFactory.cpp
inlines them. Removing those declarations while retaining the real out-of-line
allocator allocate call gives the complete 140-byte owner body with every
relocation identical. All parent, handler and cleanup rows remain exact.
Declaring growth itself instead changes the parents' stack/register allocation;
that trial was discarded.

LocomotorSetDoXfer receives the same game allocator header and allocator
boundary, plus the existing extern-copy switch. Its explicit BFME1 STL include
was replaced with the normal repository STLport include selection (the stlport
marker), preserving the complete 413-byte parent and 10-byte handler. This also
makes include inventory reusable: the external include previously prevented a
strict receipt. Putting native vendor headers before bfmealloc in an intermediate
trial bypassed the game allocator shim; that trial was discarded. The final
140-byte growth body is the owner's byte-and-relocation twin. No application
element identity is inferred from this shared helper spelling.

Paired legacy preview: 0 -> 933 linked non-padding retail bytes across three
units (255 + 255 + 423). proof.json records frozen index/object hashes, paired
findings, owner-twin checks and current self-strict receipts. No closed-strict
or new full census result is claimed. Existing BFME1 a2c8039e reviewed in this
session; no donor source was imported. Its freshness blocker is recorded in
../link-seat-20261020/readme.md.

Acceptance: build.sh 10/10 rows exact, four string references verified;
link_check --prepare-current three reusable strict receipts; link_check all
three clean; EH 3/3 EXACT, no missing objects; data_check --enforce and
--converged pass; declared-unmatched and git diff --check pass.

Cause sweep: ControlBarForgetStaleCommandSet, HordeContainParseComboHorde and
SpecialPowerStoreParseSpecialPowerDefinition already link in current sources,
so no changes or gains claimed there. Rva00506A52 remains blocked: declaring
push_back, or leaving its body visible but declaring growth and _Construct,
both grow the parent's frame from 12 to 16 bytes and separate the allocation
and pointer-reference slots (EBP-14 versus the retail EBP-0C); one cleanup row
also no longer resolves its original local label. Same /Ob0 /EHsc /MD settings.
The second diagnostic is retained as navy-trial2.patch; both attempts were
reverted, the original verified 3/3, and its file/body claims released. Do not
repeat these declarations without new compiler/lifetime evidence.
