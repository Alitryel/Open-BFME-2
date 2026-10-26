# FTP Async composition prerequisite, 2026-10-26 (codexb)

Allocated destination: Code/Libraries/Source/WWVegas/WWDownload/FTP.CPP,
family B shard 0/2. The runner --check-tu succeeds. Current AGENTS.md,
docs/consolidation.md and docs/naming.md were read. The parent-scoped planner
retains its case-different Ftp.cpp donor hint and routing alternatives; these
do not authorize a rename. The in-memory --plan approves 22 ordinary rows,
seven donor files and one mixed constructor. No merge or split is applied.

The ordinary baseline --merge --dry-run accepts no pair. Async's global
FTP_SUCCEEDED/FAILED/TRYING macros expand inside the seed's enum, causing
C2143. Make these identical values a function-local enum, and give Async's
16-byte sockaddr_in the seed's identical scalar field declarations. Remove
the now-unused in_addr wrapper and s_addr macro. No symbol is renamed and
no function, global, layout size, import or compiler flag is added.

The same ordinary dry run now accepts FTP.CPP plus
CftpAsyncGetHostByName.cpp: 15 existing rows, including the 165-byte Async
body; no baseline row is lost. This demonstrates an unblock for Luna, not a
confirmed downstream merge. The mixed constructor is unchanged. Remaining
Common donors still reject: Rva00885980 and Rva00885920 refer to m_socket8,
Rva008859D0 to m_dir34, Cftp.cpp also conflicts on fclose, and the resolver's
gethostbyname return view conflicts with hostent. They need their assigned
owner's declaration reconciliation; no Common source is edited here.

## Acceptance and bindings

Before and after: ./build.sh on FTP.CPP, CftpAsyncGetHostByName.cpp and
Common/SmallGaps/resolveHostAddress.cpp passes 16/16 matched rows, 31 literals
and 43 imports. find_declared_unmatched.py passes all three. Scoped
code_identity_gate.check reports shadow mode, 16 rows, zero problems and
zero notes. data_check.py reports zero findings. link_check.py
--new-variants --staged-peers --shadow on the same scope exits zero.

The supported allowed_symbols.Obj/body and census._comdat_selections APIs
compare complete external code/data provider bodies, relocation offsets,
types and referents, section flags, COMDAT selections and undefined sets.
Each current standalone object is identical to its before-edit snapshot,
including the unchanged resolver dependency. The accepted composed object
build/tu_skeleton/92e87203126176af.obj has no added, missing or changed
external provider. Its only removed undefined reference is Async itself,
now satisfied by the identical admitted body. Local references to listline,
stat, threadId and s_iRemoteFileSize compare exact names, data contents,
extents and section flags; none is hidden by generic local-label masking.
There are no native EH parents in this scope. No changed shared provider or
consumer binding is left unverified.

Receipts: build/sol-ftp-declarations-{before,after}-build.txt,
{before,after}-trial.txt, before.json, bindings.txt and link-check.txt.
The scratch proof is build/sol-ftp-declarations-proof.py and uses the APIs
above; it compares original snapshot objects before checking composition.
The first proof stopped on its unclassified local-data guard; the final
proof explicitly classifies and compares all four static-data referents.

ms_header_audit.scan_files/refresh_queue rescans exactly seed and Async,
preserving every unrelated record. The seed's entry is unchanged; Async's
local declaration count falls 9 to 7, still conflicting on sockaddr_in.
This is no SDK-header adoption or debt retirement. No affected Cftp header
adoption row exists. The code-identity key retained from the earlier callback
repair stays registered; global identity retirement previously required
missing ledger objects and was not retried or bypassed.

## Batch audit and publication

At audit time the sole inherited pending commit is 19dac002b0, its final
session handoff. The complete pending range plus this staged change has
one in-place source edit and no source move, rename, addition or deletion.
Active tools, hooks, workflows, source/header includes, build inputs and
registries need no repointing. Original EA paths remain intact. Functions,
data owners, protected debt registers, hatches and the TU map are unchanged.
The refreshed planner is checked after all tracked changes.

File reduction: zero. Identity/data debt retired: zero. Recovered C++ bytes:
zero. Fifteen existing rows are now composition-compatible. Keep the four
FTP/dependency/handoff file claims, plus the inherited final-handoff claim,
until confirmed publication. The publisher is called only with a commit;
the runner owns any final held batch. Final session metadata records SHAs
and claim release status. No maintainer-only measurement was started.
