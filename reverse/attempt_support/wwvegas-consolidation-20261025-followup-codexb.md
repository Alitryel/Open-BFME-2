# WWVegas consolidation follow-up, 2026-10-25

Seat `yasinschroeder-codexb`; destinations restricted to
`Code/Libraries/Source/WWVegas/`. This follows the earlier same-day handoff
`wwvegas-consolidation-20261025-codexb.md`; its Download and FTP prerequisites
are partly cleared below. The accompanying JSON retains the merge reports.

## Verified consolidation

| Retail TU | Input files | Matched code rows preserved | Files removed |
| --- | ---: | ---: | ---: |
| WWDownload/FTP.CPP | 4 | 14 | 3 |
| WWDownload/Download.cpp | 2 | 5 | 1 |
| WW3D2/htree.cpp | 4 | 5 | 3 |
| Total | 10 | 24 | 7 |

Every move used normal `tu_skeleton.py --merge` claims and current routing
rebuilt in memory. Only the source columns of existing TU-map rows changed;
no regenerated map or protected register is included. Each destination passed
`./build.sh` and `find_declared_unmatched.py`. All accepted existing rows remain
byte-exact. This removes seven source fragments and adds no retail byte coverage.

Six separate verified prerequisites made these merges possible:

* RecvReply: local constants and the seed's signed recv declaration, using the
  CRT strlen intrinsic; 268 bytes exact.
* MyIPAddress: getsockname's signed socket declaration agrees with the seed;
  178 bytes exact.
* ConnectToServer: local constants and one compatible sockaddr_in/socket view;
  the seed's 16-byte command address is now typed without changing its offset.
  Donor 562 bytes and all eleven seed rows exact before merging.
* Download: declare the actual destructor and four concrete retail virtual
  slots in the seed; keep Cftp's actual type and use a destructor-local slot
  view for retail's flag-zero deleting-destructor call and separate free.
  The 40-byte destructor and four seed rows matched independently. The retail
  table at VA 00CE89A0 and Cftp deleting destructor at RVA 006CB5B0 supported
  the ABI reconciliation; no donor spelling was treated as target proof.
* HTree: include the existing SDK shim before engine memory declarations and
  STLport. Its existing placement-array-new guard prevents CRT redefinition.
  The 44-byte seed constructor still matches.
* HTree element construction: use `<new>` instead of a second private placement
  operator. Both bodies, 77 and 81 bytes, still match before consolidation.

The HTree hook's shadow `Vector3` copy-constructor divergence also appears in
cached seed objects before the include prerequisite. The before/after bodies
are identical; cache hashes and bytes are retained in the JSON. No identity
baseline was changed and no identity debt retirement is claimed.

## Remaining prerequisites

* HTree: shared headers outside this seat's scope still disagree with donor
  member names/types (`m_tx`, `CapturedBone`, `M`, `Begin`/`End`, `Owned`, and
  the storage-method declaration). Release_Bone also exposes an iterator-tag
  redefinition. After clearing placement new, vector insert exposes C2908:
  its explicit copy_backward specialization follows an instantiation in the
  combined TU. Capture_Bone exposes missing Rotation/Translation in the
  selected Elem36 view. These require coherent ABI-backed declaration/template
  reconciliation, not a verifier workaround. Eleven mixed files and four
  protected files remain untouched.
* FTP: three remaining clean donors under GameEngine/Common/Bfme need the
  seed's Cftp member view and fclose linkage. They are outside the prerequisite
  scope of this seat. One mixed and three protected donors remain untouched.
* Thread: unchanged constructor parse failure against the seed's shared thread
  header and explicit private vtable initializer. The lifecycle file is mixed
  and yield file protected. No unchanged rebuild was repeated.
* TARGA: unchanged merge-engine result `accepted=[]`, `rejected={}` and
  `no verified merge of two or more donors`. No per-donor diagnostic was
  supplied. Investigate that result before another identical trial; its donor
  lives outside this seat's prerequisite scope.

The old HTree placement-new failures and Download destructor failure are
cleared for the accepted bodies. New visible HTree prerequisites and solved
boundaries were recorded with `re_log.py`. Unaccepted claims were released.
The final scoped planner, snapshot check and queue were refreshed after moves.

## Tooling compatibility and publication

FTP/Download's four removed paths were audited across the complete unpublished
batch against fetched `4e835ab16a`, and published with the include prerequisite
at `ce5e16cd06`. The push gate verified 47 code rows in four units, four exact
EH rows, strings, floats, imports, pins, ledger and converged data. Two GitHub
pack uploads failed server-side; the publisher's third retry succeeded. All
FTP/Download file and RVA claims were released after confirmed publication;
the prior session's FramGrab/Thread batch was also published and released.

HTree's three removed paths are audited across `origin/master..HEAD` plus
staged moves before its commit. Searches cover full paths, basenames, active
tools, hooks, workflows, includes, build inputs, registries and directory-derived
consumers. The final audit used fetched `17d211067f`. No active consumer needed repair.
Remaining mentions are donor provenance, historical attempts, the census
snapshot, and the generated Microsoft-header inventory (whose picker filters
nonexistent sources). WWLib-to-WW3D2 include/STL discovery and flag handling
were reviewed and the real destination build verified the composed environment.
Original EA source-path strings and all protected inventories were retained.

The pending final batch consists of the CRT-placement prerequisite
`45a8023ebf` and this merge/handoff. The publisher may rebase their SHAs or hold
them for the runner to publish when this session ends. Keep these four file
claims and five RVA claims until the merge is confirmed on `origin/master`:

* `file:Code/Libraries/Source/WWVegas/WW3D2/htree.cpp`
* `file:Code/Libraries/Source/WWVegas/WWLib/Rva00161050Finish.cpp`
* `file:Code/Libraries/Source/WWVegas/WWLib/StlportCapturedBoneCopyBackward.cpp`
* `file:Code/Libraries/Source/WWVegas/WWLib/StlportCapturedBoneCopyForward.cpp`
* `0x00161050`, `0x001610F0`, `0x001611B0`, `0x00161350`, `0x00166270`

After confirming publication, release those file claims and run
`python3 tools/claims.py release --landed`. Explicitly release any residual
owned accepted RVA claims if settlement reports zero: the merge tool claims
existing seed rows as well as moved rows, without necessarily queuing a
landing receipt for every claim.

Prior-session name_agreed/name_votes edits were preserved in the named
`codexb-preserved-naming-20261025-session` stash during builds/publication and
are restored after this seat's commits. Other preparation backups are retained.
