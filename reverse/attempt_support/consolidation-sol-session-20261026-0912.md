# Sol family B prerequisite handoff, 2026-10-26 (codexb)

The dedicated runner allocation is family B, shard 0/2. Read current AGENTS.md,
consolidation (including provider and tooling audit requirements), naming and
claims instructions. No helper agents or maintainer-only runners were used.
Recovered the inherited unpublished handoff first; no preserved work discarded.

## Verified prerequisites

Each repair has its own normal-hook commit and detailed evidence handoff:

| Destination | Concrete repair | Ordinary dry-run result | Pending commit before final publication |
| --- | --- | --- | --- |
| WWDownload/FTP.CPP | Make Async status constants function-local and share the seed's sockaddr declaration shape; remove unused competing declarations. | Seed plus Async accepted, 15 existing rows. Other Common donors still have socket/member/hostent conflicts. | 380ffa4c0b |
| W3DDevice/GameClient/TileData.cpp | Reconcile the setter's existing class/reference declarations with the seed and remove stale suppressions. | Seed plus setter accepted, six existing rows. Common mip donor remains incompatible; supported mixed-file split refuses an unspellable deleting destructor/lost residual row. | 7af2fbf30d |
| WWLib/wwstring.cpp | Remove the unused mutex.h include that redefines the lock-word class supplied by the seed's wwstring.h. | Seed plus Get_String accepted, 12 existing rows. Free_String stays mixed. | 51db67216b |

All are demonstrated composition unblocks for Luna, not confirmed downstream
landings. No actual merge/split or source move is applied. Detailed receipts
and supported object/provider comparisons are in the ftp-declarations,
tiledata-declarations and wwstring-lock handoffs from this date.

The final ./build.sh over all seven scope sources passes 34/34 rows (including
the read-only FTP resolver dependency), two data rows, one funclet pin,
31 string literals and 46 imports. Frozen-file and case/class checks pass.
Scoped code/data identity and link_check shadow checks introduce no findings.
EH handler and associated funclets are EXACT. Standalone and composed external
providers, COMDAT choices, relocations and undefined bindings were compared
through allowed_symbols/census APIs. TileData's removed private helpers and
identical replacement provider are explicitly accounted for; other scopes
have identical provider sets. No changed consumer binding is left unverified.

Measurements remain separate: file reduction zero; identity/data debt retired
zero; recovered/authored C++ bytes zero. TileData removes three stale
present-unmatched markers through hatch_counters --update (4336 to 4333).
The repairs make 33 existing rows composition-compatible.

## Attempted and skipped targets

Fresh allocated runner queue (build/sol-allocated-final-20261026.txt) lists
27 eligible destinations and no explicit repair entries. No paired-seat half
was selected. Parent naming reports and current upstream routing were reviewed.

Network: normal --plan and --merge --dry-run finish with no accepted pair.
The seed fails byte verification under every composed flag set; GameLogic
adoption and Common-owned BFMEConnectionManager/interface/API declarations
also block donors. Do not infer a new standalone regression from that scope
verdict. Receipt: build/sol-network-current-trial.txt. Cross-family declaration
repair belongs with the assigned owner; no source edited.

AptMiscObjects: normal dry run accepts no pair. The seed's AptValue header
lacks donor SetString and rva006ddde0 declarations, while BFME view ordering
and methods also conflict. The shared header reaches about 32 consumers,
including Common. This needs a coordinated dependency set, not a local
duplicate class. Receipt: build/sol-aptmisc-current-trial.txt. No source edited.
Both scope blockers are recorded through re_log.py; their temporary destination
claims are released.

NetPacket: a new exploratory normal dry run was interrupted after several
minutes without a final verdict. A transient defunct compiler child did not
prove a deadlock: the later parent was running and its child had gone. No new
acceptance/refusal or false-reject claim is made. Its own generated temporary
source was preserved under build/sol-netpacket-interrupted-trial.cpp, with no
production change; no build remains running. Do not treat this interruption
as evidence that the queue is empty or the candidate is inherently blocked.

Existing handoffs were checked instead of repeating unchanged blockers:
WaterTracks has an initializer-semicolon composer refusal; Firewall and
Disconnect have flag/byte boundaries; debug net/ODS have an unresolved extra
virtual slot; GameFont and GSConfig require broad interface/template work;
Win32LocalFileSystem/DIKeyboard need cross-family ABI reconciliation;
Vegetation's binder donor is Common-owned. FramGrab, NetCommandList,
NetCommandWrapperList, AptValue, AptMovie, line3d, BIG, Bib/Smudge subsets and
TARGA already have accepted subsets or prior prerequisite results for Luna.
No new identity/naming vote or MessageStream identity decision was attempted.

## Final complete batch audit and publication

Rebased all four inherited/new commits on dd4a917878 without conflicts and
reran check_csv plus the seven-source byte build. No upstream edit touched
AGENTS.md or the repaired source files. Before the final handoff commit,
origin/master..HEAD contains fa0f4a2581 (inherited recovery), 380ffa4c0b,
7af2fbf30d and 51db67216b. Add this handoff and its two tool-written attempt
records to that range. Rebase can change these SHAs at publication.

git diff --name-status --find-renames origin/master..HEAD plus staged paths
shows only in-place game source edits, documentation/attempt additions, the
scoped SDK report refresh and the tool-owned three-hatch shrink. No source
addition/deletion/move needs tool, hook, workflow, include, build-input or
registry repointing. Historical EA paths remain. Code/data debt keys, ledger
owners, flag overrides, fold proofs and TU map remain intact. The Microsoft
queue refresh changes only FTP declarations; wwstring's identical queue row
was left in place. Provider proofs cover all three prerequisite compositions.

tools/progress.py origin/master: byte-matched 7,978,500 (100%), LINKING
7,351,388 (97.85%), LINKED 7,596,747 (98.53%), each delta zero. The linking
figures remain the 2026-10-26 00:54 census at 763dc8759f; no new census or
ownership receipt is claimed. build/sol-final-prerequisites-build.txt and
build/sol-progress-20261026-final.txt hold the final local receipts.

Use only commit && /opt/runner/publish. The runner may hold the batch because
another seat owns the account slot. Keep these file claims until the batch is
confirmed on origin, then release them and settle RVAs with release --landed:

- reverse/attempt_support/consolidation-sol-session-20261026-0732.md
- Code/Libraries/Source/WWVegas/WWDownload/FTP.CPP
- Code/Libraries/Source/WWVegas/WWDownload/CftpAsyncGetHostByName.cpp
- Code/GameEngine/Source/Common/SmallGaps/resolveHostAddress.cpp
- reverse/attempt_support/consolidation-sol-ftp-declarations-20261026.md
- Code/GameEngineDevice/Source/W3DDevice/GameClient/TileData.cpp
- Code/GameEngineDevice/Source/W3DDevice/GameClient/TileDataReplaceCompanionRef.cpp
- reverse/attempt_support/consolidation-sol-tiledata-declarations-20261026.md
- Code/Libraries/Source/WWVegas/WWLib/wwstring.cpp
- Code/Libraries/Source/WWVegas/WWLib/wwstring_get_string.cpp
- reverse/attempt_support/consolidation-sol-wwstring-lock-20261026.md
- reverse/attempt_support/consolidation-sol-session-20261026-0912.md

The pre-push link_batch_audit still runs once through the normal hook; review
its selected-provider, lost-byte and freshness output before claiming a link
improvement. Scoped composition proofs above establish the prerequisite
unblocks independently; consumer linked-byte totals await a fresh census.
