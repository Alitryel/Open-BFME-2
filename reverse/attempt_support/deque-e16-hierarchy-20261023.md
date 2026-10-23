# E16 deque constructor hierarchy correction

Scope: `stlport_deque_e16_o1.cpp` and `Rva00558D56.cpp` only. The existing
`StlportOwnedRecordDeque.cpp` provider and all shared headers are unchanged.
Reference inputs remain BFME1 `138757e9b74645fbcbb7724a7af2764e34931e11`.

Integration with upstream `882792da63630740315f49aa5bb6a57b8a4693a7`
preserves its existing `BFMENetworkQueue1` wrapper name and its old-name
tombstone. The corrected 1408-byte member type remains unchanged. The union
merge's reintroduced old wrapper row is removed rather than admitted as a
second identity at `0x558D56`. This retains upstream naming, not a new claim
to the original record identity. Combined source and consumer verification
must supersede the earlier address-named wrapper receipt.

## Target evidence versus structural names

- Native base constructor `0x55334A`, 75 bytes, initializes the two iterator
  records, constructs its map proxies through `0x14F3C4`, and calls map
  initializer `0x55315A`. The native allocator constructor `0x55387C`, 20 bytes,
  calls this base with zero elements. Wrapper `0x558D56`, 21 bytes, also calls
  this base with a temporary allocator and zero elements.
- The already rowed `0x55315A` initializer advances node bounds by `0x580` and
  calls already rowed create-nodes `0x553032`, which allocates `0x580` bytes per
  node. These facts support the existing 1408-byte record view, not E16.
- Reused declarations are exactly the established `BfmeOpaqueOwnedRecord1408`
  view, including its `PSPlayerAllStats` member. This is not a newly inferred
  application identity: the original record owner remains unknown.
- The true E16 increment `0x419DF6` (38 bytes), construction `0x59CE9E`
  (21 bytes), and allocation `0x2226BE` (28 bytes) retain their existing rows.
  Their native element stride, four-dword copy, and allocation multiplication
  are consistent with 16-byte storage; they are not renamed with the constructors.
- The alleged distance wrapper `0x2619A0` (14 bytes) calls `0x2615C0`.
  The latter is independently rowed `BitFlags<69>::test`, not deque subtraction.
  Prior attempts 527, 659, 1148, and 26906 already refute that subtract binding.
  Retract this false row without inventing a replacement identity in Common.

## Admission and rejected shapes

`rename.split_function_name` refuses the constructors as special-member/template
names; its function engine only changes a plain identifier. A class-wide rename
would corrupt the three true E16 specializations and is not this correction.
The documented signature-correction exception in `docs/naming.md` applies:
retire the old names, write tombstones through `gen_small.write_tombstones`,
and admit replacement matched rows with normal `add_match_batch.py` verification.
No `name_basis.csv` record, alias, new application identity, or unmatched row is
created. Normal `add_match.py --replace-rva 0x55334A` explicitly refused the old
real claim as non-scaffolding; this refusal is not bypassed with scaffold notes.

Two original constructor-proxy pins at `0x14F3C4` are replaced with 1408
spellings. Both complete emitted 11-byte bodies, including all relocation sites,
passed normal `pin_admission.py --add` with a new fold proof from the corrected
owner TU. The unrelated E16 vector-pointer proxy pin is retained. False E16
map and subtract pins are removed, not redirected.

The fold gate automatically checks all non-alias 11-byte owners at `0x14F3C4`:
`BfmeOwnerZKRelink.cpp`, `PlayerAITypeSetCtor.cpp`,
`RTS/ScienceStoreFindScienceInfo.cpp`,
`AI/AIGroup_groupDoSpecialPowerAtObject.cpp`, and
`stlport_list_drawable_base_ctor.cpp`. Parent explicitly approved these five
as read/compile-only after reviewing isolated mappings. All compiler receipts
have no forced include; source files are unchanged. No further expansion is
authorized. Admission's unrelated hatch-register regeneration was restored;
only the two false-pin count reductions are retained, with all unrelated
allow metadata preserved.

The initial full E16 instantiation emitted the false distance body. Two attempts
to retain it by explicit generic `__distance` instantiation failed VC71 C2785
because iterator-traits return-type deduction disagreed. These are not repeated:
target call identity independently refutes the row. Three explicit true E16
instantiations preserve the supported bodies without retaining the false call.

## Verification results

- Normal `add_match_batch.py` admitted the two corrected constructor rows and
  verified all five owner rows. Normal `add_match.py --replace-existing`
  reverified the wrapper and updated its provenance. No unmatched row was made.
- `link_check.py --prepare-current` prepared exactly these two TUs and verified
  all six rows with strict reusable dependency receipts. String, float, and
  import-reference checks passed with no unverified references.
- `eh_verify.py` found no EH-bearing rows, no mismatches, and no missing objects.
  `find_declared_unmatched.py` and `check_csv.py` passed. Both corrected proxy
  names passed individual consistency checks; global `pin_consistency.py --check`
  reported zero new, zero stale, and zero baselined violations.
- Normal two-source `link_check.py` reports both TUs LINKS, owner 0 -> 182 bytes
  and wrapper 0 -> 21 bytes: scoped preview 0 -> 203 bytes against the published
  census index dated 2026-10-23 14:28 at `b711de3634`. Fetching the current index
  imported zero objects with object-store reuse disabled. This is a scoped
  prediction, not a new census or an integrated-parent verification.

Accounting: owner plus wrapper 217 -> 203 unique row bytes, an honest 14-byte
coverage correction, not new recovery. Predicted link gain is separately 203
bytes against that index. Parent must reverify its integrated inputs and pin.

## Normal commit footprint blocker

The ordinary commit hook passed scoped code/data identity, ledger, pin
consistency, complete fold admission, and undeclared-definition checks. Its
`name_dependents.py --staged` then reported seven lost call targets and three
function targets relevant to data initializers, expanding verification to
1,168 referencing units of 23,428 scanned. These are the retired distance,
two E16 constructors, two E16 constructor proxies, map initializer, and subtract
names. Missing/unusable object receipts cause conservative source-text matching
on the generic identifiers `deque`, `_Deque_base`, `_STLP_alloc_proxy`,
`__distance`, `_M_initialize_map`, and `_M_subtract`; this is not proof of 1,168
actual calls to these particular E16 specializations.

This expansion exceeded the explicit two-TU plus five fold-owner compile grant.
The hook and its expanded build descendants were terminated, leaving no commit.
The first 174-source chunk had already started: guest receipt
`944a8acf0b254a59969eacc55dc9698f` confirms one additional completed compilation,
`Code/GameEngine/Source/Common/AwardSystemManager.cpp`, at
2026-10-23 18:33:41Z, return code zero and no forced includes. No source outside
the two approved TUs was edited. The compiler grant was unset afterwards.
The commit log also contains `wine: Unhandled illegal instruction at address
70D92A0F (thread 007c), starting debugger...`; fold admission nevertheless
completed OK. No runtime or wrapper repair was attempted.

The normal hook is not bypassed, reduced, or modified, and false pins are not
retained to suppress dependent discovery. Parent needs to approve and map the
actual wider verification footprint, or run normal integration with sufficient
current object evidence. This is a verification-scope blocker, not a byte or
identity mismatch in the corrected six rows.

## Superseding normal verification and parent integration

The earlier blocked hook above is retained as operational history, not the
final result. Seat1 subsequently received the expanded verification grant and
committed normally as `bfece861fc748620b4d13d35849ee9c886e1ad5f`.
Its successful hook verified 1,119 sources and 9,175 function rows, with
1,247 exact EH rows, one existing baselined difference and no missing objects.
The footprint reconciles as 1,167 approved sources minus 50 normal exclusions
plus the two edited units; usable completed object receipts narrowed the
normal generic-name dependent fallback to 1,117 sources. No manual gate
filtering was used. Seat-local footprint, receipt and exclusion inventories
are retained in `build/seat1-deque-final-footprint.json` and the corresponding
verified/pruned source lists.

Parent integration used the subsequently published donor
`f5140c1cff6a58e16276fd6de6788186286953d4`, whose paired full verification is
recorded independently in
`reverse/attempt_support/bfme1-reference-f5140c1c-20261023/readme.md`.
The upstream rename from `Common/Rva0055AA06ListPush.cpp` to
`Common/ScoredKillTracker.cpp` was reconciled explicitly rather than dropping
a missing source. The union of the prior 137-source scope and current normal
name dependents contains 140 sources. Every inspected compiler command and
resolved input directory passed seat-local existence and pin checks, including
the existing forced-header consumer; no compiler flag or verifier change was
introduced by this integration.

An initial parent build failed while parsing a zero-byte transferred host
object, not on a semantic byte comparison. Its successful guest receipt and
38,425-byte guest object were preserved separately; both later diagnostic
transfer modes succeeded, so no capture-versus-stream causal claim is made.
The ignored OrbStack bridge was hardened to validate receipt identity, captured
size/SHA256 and bounded i386 COFF structure before atomic replacement, preserving
previous outputs on refusal without retry or fallback. Nineteen mocked object
tests and five channel fixtures passed. A separate isolated compiler smoke
produced 54/54 exact relocated bytes, and normal verification of the affected
LivingWorldPlayerDtor unit passed 57/57 rows. Only the original zero-byte object
and its sidecar were quarantined before normal rebuilding; no diagnostic object
was installed into the build cache.

The first complete ordinary parent build passed 2,975/2,975 full function rows across
140 sources, 29 data rows, 447 string literals plus 79 empty-string references,
92 float literals and 176 named imports. Five units compiled; 135 had current
dependency receipts. Scoped EH verification passed 294/294 exact, zero
baselined differences and zero missing objects. Normal `link_check.py
--prepare-current` for the two edited sources passed all six rows with strict
reusable receipts and left the census/index/status unchanged. Raw parent
mapping, build, strict-receipt and EH artifacts are retained under
`build/orbstack/deque-parent/current-f514/`; the earlier failure and transport
diagnostics remain under its sibling `empty-object-transport/` directory.

After the next normal upstream rebase, dependent discovery named ModuleFactory
and CreateAHeroHero instead of the preceding dependent set. Neither edited
deque source nor any source in the prior 140-source scope had changed. Both new
commands were inspected separately, including ModuleFactory's existing bare
`/FIzh_ascii.h`: the unchanged mapper preserves header-search semantics and the
first selected header is the existing `bfme2_ascii_zh/zh_ascii.h`. An initial
filesystem-only assertion incorrectly assumed these new commands had no forced
header; it was corrected to check the actual existing input, with no compiler
or wrapper change. The conservative union is 142 sources, not a reduced gate.
The subsequent ordinary build passed 3,094/3,094 rows, 30 data rows, 475 string
literals plus 86 empty-string references, 95 float literals and 177 imports.
One source compiled and 141 had current receipts. Scoped EH passed 326/326
exact with zero baselines or missing objects. The explicit source union,
mapping resolutions, build and EH receipts are retained as `scope-post-rebase`
and `post-rebase-*` artifacts in the same ignored parent evidence directory.

These results supersede the verification-scope blocker without erasing it.
Accounting remains a 14-byte integrity correction with no new recovery; the
203-byte historical link prediction above is neither a current census nor a
claim of current closure.
