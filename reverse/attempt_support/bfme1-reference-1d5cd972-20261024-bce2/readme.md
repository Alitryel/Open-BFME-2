# Verified BFME 1 reference update, 2026-10-24

This pass verified the clean donor update from `f5140c1cff6a58e16276fd6de6788186286953d4` to official master
`1d5cd9725d113c0a58b58f09f282340d8e7b26a7`, fetched at the start of this pass. The prior pointer remains
reachable in the new revision's history. No dirty or unpublished donor work
was overwritten. This is reference maintenance, not new BFME 2 C++ coverage.

## Paired verification

Both ordinary `./build.sh` runs used fixed BFME 2 revision
`563b86b09fd2262c608117c6c0e7d84af138a747` and `BUILD_POOL=2`. The production tree fingerprint was
`df420969d1aed4deb6199aa5748be58ab5a2e7bf6be393ca6d877040b79f424f` before and after both runs.
Both full gates passed all 98,189 function rows and 2,175 data rows, including
literal/import/float checks, DIR32 consistency, pins, module registry, source
claims and the no-op patch. No baseline failure or update regression occurred.
No verifier, baseline or whitelist was changed.

The baseline needed 3,232 stale production objects: 1,774 were restored from
the published object store and the rest compiled normally. The updated donor
reused all 23,422 current production TUs. Full-gate durations were
52.6 minutes (old) and
28.2 minutes (new). Receipts bind the
commands, revisions, timing and full-log hashes; both full logs are retained.

The complete `eh_verify.py --all --json` outputs are byte-identical, SHA256
`76c843d3c11b941498efa932ce702f363cf25462d11b903b5b70a9986ceaa9c2`: 11,870 exact rows, 23 existing baselined bytes_differ findings,
one existing baselined retail_only finding, and no missing objects. Text
summaries and a comparison receipt are tracked; both complete JSON outputs
remain in ignored `build/resume-eh-local/turn71-reference/`.

## Inputs and discovery

The donor delta changes two game C++ files and three evidence/log files.
Its entire `inputs/` tree is identical. All six existing layout resolutions
exist; the actual Vector3/AsciiString headers, C2 compiler DLL and lift tool
were checked at both revisions. Git blob hashes and local checkout hashes
are recorded separately because Windows text checkout uses CRLF.
No layout migration or missing-header substitution was needed.

The dependency audit read 26,315 production and 913 ZH receipts, with no
malformed receipt and no receipt reading either changed donor source. This
supports cache reuse for the donor delta; it does not replace the full gate.
Because the newly pulled BFME 2 compiler-option code had changed, the ZH
discovery cache was independently rebuilt with `compile --force --jobs 2`:
919 units rebuilt, zero cached, and the same 68 failed units as the prior
local run. There are no new or resolved failures. Failed identities and the
log hash are retained; full diagnostics stay in ignored build output.
The forced rebuild used the old donor, whose relevant input tree is identical
to the new donor. All subsequent searches ran at the new revision.

BFME 1 scan checked 38,787 donors, with 5,516 independent boundary controls
and zero free placements. Ranked and near each serve zero candidates.
The lift lane reports 146 bodies (105,306 B), including 103 servable leads
(79,182 B). ZH match examined 27,013 functions from 919 freshly built objects;
packets returned zero. Packet output was directed under ignored build/ so
existing queue files were preserved. These are discovery results, not proof
that all reusable reference C++ is exhausted.

The published link index at 0393df10e2 was fetched; 14,007 objects were added
to the local store. No census, link cycle, nightly or boot runner was started.
The freshness stamp is written only after the paired verification succeeds.
The user requested stopping after this next publication; no further recovery
target is selected in this batch.

Tracked evidence copies use LF line endings and omit trailing whitespace.
Receipt `log_sha256` values bind the original raw logs retained under ignored
build output; `tracked-files.json` binds the normalized tracked copies.

## Publication reconciliation

The first push was interrupted before its full gate completed; that incomplete
push log is not validation evidence. On resuming, master already contained
newer verified donor `32774ab03393709a7f14331ba8d98d281a55ffd9` via
`14104369c88`. Git ancestry proves that donor includes `1d5cd9725d`. The rebase
keeps master's newer pointer; this final commit banks the completed historical
comparison above and makes no production or reference-pointer change. The
newer pointer's own paired evidence is in
`../bfme1-reference-32774ab0-20261024/readme.md`.
