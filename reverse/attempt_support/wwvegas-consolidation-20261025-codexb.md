# WWVegas consolidation handoff, 2026-10-25

Seat: `yasinschroeder-codexb`. Destination scope:
`Code/Libraries/Source/WWVegas/`. The accompanying JSON preserves the merge
engine's accepted, rejected, mixed and refused donor reports.

## Verified work

| Retail TU | Input files | Code rows preserved | Files removed |
| --- | ---: | ---: | ---: |
| WWDownload/Download.cpp | 2 | 4 | 1 |
| WWDownload/FTP.CPP | 3 | 11 | 2 |
| WWLib/straw.cpp | 2 | 3 | 1 |
| WWLib/chunkio.cpp | 2 | 28 | 1 |
| WW3D2/statistics.cpp | 2 | 20 | 1 |
| WW3D2/FramGrab.cpp | 2 | 2 | 1 |
| WWLib/thread.cpp | 2 | 3 | 1 |
| Total | 15 | 71 | 8 |

Every move used `tu_skeleton.py --merge` with normal claims and current routing
rebuilt in memory. Each TU passed `./build.sh` and
`find_declared_unmatched.py`, then normal commit hooks, including identity,
data, EH, pins, flags, strings and imports. Thread's existing data row also
byte-verified. Existing anchors and protected registers remain unchanged.
Only source columns were repointed in the committed TU map. No regenerated map,
new byte coverage, class/header prerequisite or escape hatch is claimed.

Download through Statistics were published together at `5215a314a7`; the push
gate checked 93 code rows across six affected/dependent units and four exact EH
rows. The first GitHub pack upload failed server-side; the wrapper's retry
succeeded. Their file claims and remaining RVA claims were released after
publication, including an explicit `claims.py release --landed` settlement.

## Remaining prerequisites

These are consolidation blockers on existing matched bodies, not regressions.
Twenty-one representative body boundaries were recorded through `re_log.py`.

* HTree: no accepted merge. The seed's included shim lacks the donors' member
  spellings/types (`m_tx`, `CapturedBone`, `M`, `Begin`/`End`, `Owned`, and the
  storage method declaration). Other donors conflict with included placement
  new/new[] definitions. The canonical/shared shim lives outside this seat's
  destination scope. Reconcile ABI-backed declarations and include environments
  in verified prerequisites before retrying. Eleven mixed and four protected
  donors were not split or moved.
* Download: the destructor donor cannot define `CDownload::~CDownload` against
  the composed seed declaration (C2600). Its explicit virtual-slot view of
  Cftp also needs deliberate reconciliation; merely declaring the destructor
  does not establish that the complete merge preserves its deletion ABI.
* FTP: RecvReply and ConnectToServer macro constants collide with the seed's
  enum; MyIPAddress disagrees on the C-linkage getsockname declaration; the
  other donors use incompatible Cftp member views or fclose declarations.
  Several prerequisite donors live outside this scope. One mixed and three
  protected donors remain untouched. No guessed class layout was introduced.
* Thread: the constructor composition gives C2143 before
  `ThreadClass::__ctor`, then C1004. The seed includes the shared ZH-compatible
  thread header, while the constructor spells a BFME-specific novtable view
  and explicit vtable initializer. The lifecycle donor is mixed and the yield
  donor protected; neither was split or moved.
* TARGA: dry-run returned `accepted=[]`, `rejected={}` and
  `no verified merge of two or more donors`. It supplied no per-donor
  diagnostic. No source edit, manual compile, claim or verifier workaround was
  made. Investigate this merge-engine result before repeating the same trial.

The final scoped queue contains only HTree, FTP, TARGA, Download and Thread,
with these unchanged prerequisites. The planner was regenerated after each
relevant move and its final snapshot check passed. Scratch reports are under
`build/consolidation/`; that directory is not publication evidence.

## Path audit and publication handoff

Audited the complete first outgoing batch against fetched `51cc7ed5dc`, and
the final FramGrab/Thread batch against `5215a314a7`, then refreshed the complete
pending-path search against fetched `6e43b9eae5`, including the staged handoff.
Combined deleted paths and basenames were searched in the index; directory
consumers were reviewed across tools, hooks, workflows, includes, build inputs,
registries and documentation. No active consumer required repair.

Retained mentions are donor/source provenance, historical attempts and the
census snapshot. The generated Microsoft-header inventory still contains old
paths; its repair picker explicitly filters nonexistent sources. An optional
current-source `ms_header_audit.py scan` could not preprocess its SDK kitchen
sink and exited 1; normal Microsoft-header commit checks passed. No inventory
was fabricated or partially overwritten. The network reading list's
`native_network.cpp` refers to BFME 1, so it remains historical donor evidence.

FramGrab `d7157ce946` and Thread `cf770d159e` are verified local commits held
by the publisher's batch threshold when this handoff was prepared. Their
claims stay held until the runner publishes them. After confirming their
landing, release the following file claims and run
`python3 tools/claims.py release --landed`; release any residual owned RVA
claims explicitly after checking publication:

* `file:Code/Libraries/Source/WWVegas/WW3D2/FramGrab.cpp`
* `file:Code/Libraries/Source/WWVegas/WW3D2/FrameGrabClassFlushBufferedFrames.cpp`
* `file:Code/Libraries/Source/WWVegas/WW3D2/FrameGrabClassGetBuffer.cpp`
* `file:Code/Libraries/Source/WWVegas/WWLib/thread.cpp`
* `file:Code/GameEngine/Source/GameNetwork/native_network.cpp`

Their code claims cover 0x001767D0, 0x00176860, 0x00610490, 0x00610510
and 0x006105D0. The rejected constructor's body and file claims were released
after recording its blocker. Prior-session changes to `name_agreed.csv` and `name_votes.csv`
were preserved separately and are not part of this consolidation batch.
