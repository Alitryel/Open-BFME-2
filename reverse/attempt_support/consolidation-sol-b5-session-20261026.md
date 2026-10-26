# Sol b5 prerequisite batch, 2026-10-26

Seat codexb5, family B shard 1/2. Allocation was checked through
`python3 /opt/runner/consolidation_queue.py --limit 20`; no paired-seat work
was taken. Three declaration prerequisites were verified, without merging
files or recovering new bodies:

| Destination | Prerequisite commit at handoff | Newly compatible existing rows | Ordinary dry-run result |
|---|---|---|---|
| Apt/AptInput.cpp | a0048e28d8 | 2 / 418 bytes | seed plus three donors, 11 rows |
| Apt/string/StringPool.cpp | a1da59ef20 | 1 / 405 bytes | two donors, 2 rows |
| WW3D2/dx8vertexbuffer.cpp | e93cedd062 | 2 / 10 bytes | four donors, 9 rows; no rejects |

The per-target input, stringpool and vb handoffs contain commands, layouts,
before/after evidence and remaining prerequisites. Each source batch passed
`./build.sh`, frozen-file checks, EH, scoped data and code-provider/binding
comparisons, and normal commit gates. External code definitions, COMDAT
selection kinds, undefined-symbol sets and data facts were preserved. Local
EH labels were compared by the byte verifier's exact parent placement. These
are demonstrated composition unblocks, not confirmed subsequent Luna merges.
New C++ bytes, file reduction and identity debt retired are all **zero**.

## Trials left unchanged

* surfaceclass: `--split SurfaceByteSize.cpp --for surfaceclass.cpp --dry-run`
  selects eight approved rows but refuses because the residual loses static
  helper 0x00116560 (105 bytes). No edits were applied. Commit 3ff6af9361 and
  the surface handoff record the full dependency. Do not force emission or
  manually move the helper.
* htree: ordinary `--merge .../htree.cpp --dry-run` accepts the seed, storage,
  StlVectorRva00162800, destructor and CaptureBone: five files / 16 rows.
  This confirms the earlier storage/split prerequisites remain usable; it is
  no new unblock. CopyConstructor's private BfmeRva00166110 view loses the
  seed's Start/Finish fields. Other rejects require the compact PivotClass
  layout, specialization ordering, cross-family ArchiveFile declarations or
  investigation of compiler C1001. Receipt: build/sol-b5-htree-trial.log.
* W3DPropDraw: retried after upstream eb276b365a added seed flag/include retry.
  The normal dry-run still exits 2 with no accepted subset: final C2011
  Coord3D redefinition. React requires a copy constructor/destructor view,
  while the seed includes the canonical POD; a declaration-only replacement
  has no proof. PoolKey also lacks rva000CEEE6, and ModuleDataCtor lacks
  m_distanceFog. Existing header debt is retained. Receipt:
  build/sol-b5-prop-current-trial.log.
* dx8webbrowser: current planner packet and normal dry-run reviewed. The
  destination does not exist yet. The seed CreateBrowser is accepted, six
  rows; Rva001776a0Cluster fails C2660 because the chosen Rva00958D30 lacks
  its one-argument invoke overload. Is_Browser_Open's private DX8WebBrowser
  view omits seed CreateBrowser/hWnd. BSTR views also differ in copy/lifetime
  definitions; this is a dependency to investigate, not a proven safe union.
  Existing global identity/hatch/data debt is preserved. Receipt:
  build/sol-b5-browser-trial.log. Planner original-path evidence remains
  investigatory; only current routing approved the trial inputs.

Blocked evidence was recorded through re_log.py; all trial-only destination
and donor claims were released. No failed reconstruction remains in Code/.
AptRenderingContext's already accepted subset was left for Luna. The earlier
prerequisites handoff was consulted to avoid repeating unchanged GameInfo,
Bridge, Tree, BufferManager, debug, BuddyThread and cross-family blockers.

## Publication audit and handoff

The complete pending range from origin/master (3dc4f03f8e at audit) through
3ff6af9361, plus this staged handoff and attempt log, has no source path
changes, row moves, build-input changes or protected-register edits.
The merge-base outgoing diff contains only three modified source paths, new
handoffs and the attempt log. During audit origin advanced to 9fd130644a;
the two-dot diff additionally shows that incoming commit's 39 data-key
retirements in reverse. Those are not authored changes in this batch. Thus there
are no old paths to repoint in tools, hooks, workflows, includes, registries,
build configuration or historical EA evidence. No TU map was committed.
Upstream pull/rebase touched none of the three verified source areas or
their reviewed htree shim dependency; check_csv.py passed afterward.

The runner has queued the prerequisite commits. Until publication is
confirmed, retain this seat's file claims on AptInput and its BIL/cluster
donors, StringPool and shutdown/remove donors, dx8vertexbuffer and
LockClasses/engine_ref donors, and their four handoffs plus this handoff.
After landing, release those file claims and run claims.py release --landed.
Exact outstanding claims are saved locally in build/sol-b5-final-claims.txt.

`python3 tools/progress.py origin/master` reports BYTE-MATCHED 7,978,500
(100%), LINKING 7,351,388 (97.85%) and LINKED 7,596,747 (98.53%), all delta
zero. Linking figures are the 2026-10-26 00:54 census at 763dc8759f, not a
new measurement attributable to this batch. No maintainer-only measurement,
link cycle or smoke runner was started.

BFME 1 reference freshness remains an explicit limitation: the official
upstream check found clean pinned ff391a5e versus official master 0337dcca.
No reference checkout update or success receipt was fabricated without the
full before/after validation required by docs/matching.md.
