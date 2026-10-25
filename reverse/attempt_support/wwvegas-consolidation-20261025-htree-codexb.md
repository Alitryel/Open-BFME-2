# HTree consolidation follow-up, 2026-10-25

Seat `yasinschroeder-codexb`, source/destination scope
`Code/Libraries/Source/WWVegas/`. This extends the earlier follow-up; its
published FTP/Download work is not counted again here.

## Verified result

The normal `tu_skeleton.py --merge` accepted the seed and six donors into
`WW3D2/htree.cpp`: Scale, Is_Bone_Captured, Control_Bone, Get_Bone_Control,
Release_Bone and the 36-byte-record vector insertion. Six actual source files
are removed. All eleven rows (2,088 retail bytes) remain byte-exact; no new
matched/C++ coverage is claimed. The companion JSON preserves the complete
accepted/rejected report and paths. Current routing was rebuilt in memory;
only five existing TU-map source columns changed, with no regenerated map or
protected-register changes. Eleven mixed and four protected donors stay put.

Every prerequisite passed its own `./build.sh` and normal commit hooks.
The eight distinct affected bodies are Scale 110, Is_Bone_Captured 48,
Control_Bone 112, Get_Bone_Control 442, Release_Bone 70, insertion 288,
Capture_Bone 229 and destructor 26 bytes. The shared HTree header is used
through its existing OwnedSequence1C words. The compact Scale pivot view is
explicitly target-derived, not a claimed donor layout. Capture_Bone and
insertion now spell the seed capture record and its scalar copy order.
The real merged destination passed `./build.sh` (11/11 and six float
literals), and `find_declared_unmatched.py` passed. No pins, hatches or
identity baselines were added. Normal hooks remain the final acceptance gate.

The prior pending four-file/five-row HTree merge and its CRT prerequisite
were also confirmed published this session; their three removed fragments
are not part of the six-file count above.

## Remaining scope blockers and evidence

* HTree storage 00160FC0: the shared HTree header has no storage-method
  declaration; header work lies outside this seat's source scope.
* HTree destructor 001667E0: its verified word-field rewrite is published.
  Further header adoption requests private `?Free@HTreeClass@@AAEXXZ`, while
  the existing provider/pin is public `?Free@HTreeClass@@QAEXXZ`. The failed
  adoption was reverted and its original 26-byte body verified again. No
  second binding or visibility macro was introduced.
* Capture_Bone 00166980: the standalone 229-byte header/record prerequisite
  is verified and committed, but composition still rejects it with C2143 /
  C2065 (`BfmePod36` undeclared, generated line 110). The current dry run and
  applied merge agree on the six accepted donors. Reconcile declaration and
  template ordering before another unchanged trial; do not hand-compose it.
* TARGA: the seed has two top-level conditional include groups. `compose`
  deduplicates all preprocessor lines, removing the second identical
  `#endif`. The companion JSON retains the exact before/after chunk proof.
  This explains its old empty accepted/rejected report without another
  unchanged build. A tooling seat must fix and test this false reject;
  the 00614200 identity donor also lies outside this prerequisite scope.
* Thread: its clean donor defines a one-argument constructor and writes a
  private vtable; the seed's shared header declares a two-argument constructor.
  The unchanged header/ABI prerequisite remains outside scope. Mixed lifecycle
  and protected yield donors remain untouched.
* FTP: all three remaining clean donors live under GameEngine/Common/Bfme.
  They still need Cftp field/declaration and fclose-linkage reconciliation;
  no out-of-scope donor edits or speculative seed aliases were made.

An earlier intermediate HTree dry run reported accepted donors but emitted
literal `compile` as its final source. It was never applied. `Verifier`
currently caches object-or-None without restoring errors on cache hits, and
`_merge` does not refuse a final attempt sentinel before apply. The JSON
retains that report. This is a separate tooling handoff, not permission to
bypass verification. Current successful source was independently built after
application. Blocked evidence was recorded with `re_log.py`, and rejected
storage/destructor/Capture_Bone claims were released.

## Tooling audit and publication handoff

All pending source moves were audited together against fetched origin
`d9f789c76e`, across `origin/master..HEAD` plus the staged merge; incoming
upstream-only changes were distinguished using the outgoing merge base.
Searches combined full old paths, basenames and WWLib/WW3D2 directory consumers
through tools, hooks, workflows, includes, build inputs, registries and docs.
No active consumer needed repair. Remaining mentions are source provenance,
`name_basis.csv` rename history, census snapshots and historical handoffs.
Original EA paths were retained. The real destination build verifies include,
STLport and compiler-environment discovery after moving the vector fragment.
No maintainer-only runner was invoked.

The companion JSON lists seven file claims and eleven RVA claims to retain
until this merge is confirmed on origin. After publication release its file
claims and run `claims.py release --landed`; explicitly release residual
accepted RVA claims if settlement reports zero. A cooldown-held batch is for
the runner to publish, never a reason to call publish alone. Existing
name_agreed/name_votes edits are preserved in the named reassessment stash
and restored after publication; older preparation backups remain intact.

## Confirmed publication and final checks

Merge `584f3a434d` and its six latest prerequisite commits are confirmed on
origin/master. The push gate passed 39 code rows across three sources, four
exact EH rows, ten string literals plus five empty-string references and twelve
float literals, with no new pins or baseline growth. All seven accepted file
claims were released after confirmation. `release --landed` settled zero;
explicit release cleared fifteen remaining file/RVA claims (the other accepted
RVA claims were already absent). Rejected claims were released earlier.

The normal hook reports the existing shadow Vector3 copy-constructor
`??0Vector3@@QAE@ABV0@@Z` divergence. Reading its COFF body from both historical
seed objects and the current merged object proves identical 23-byte code and
no relocations; exact bytes and paths are in the JSON. No identity-debt
retirement is claimed.

Final scoped planner refresh and snapshot check passed. Its queue is FTP
(three remaining donors), HTree (three), TARGA (one) and Thread (one), with the
prerequisites above. No unchanged failed build was repeated. The user restricts
application to normal merges; the newly available split lane was not used.
`progress.py origin/master` passed: BYTE-MATCHED 100.00%, LINKING 97.74%,
LINKED 95.24%, all deltas zero. Six fewer source files, preserved matched rows
and separately verified prerequisites are this session's consolidation result.
