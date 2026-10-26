# W3DBufferManager release-list composition prerequisite

Seat: codexb5, allocated family B shard 1/2; 2026-10-26. Parent revision
`0cd6b45068`. No merge was applied. This is a prerequisite repair, not recovered
bytes, a file reduction, debt retirement or a census linking improvement.

## Demonstrated change

Destination:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager.cpp`.
The planner and current `tu_skeleton --plan` approve 12 rows across four sources.
Before the repair, normal `--merge DEST --dry-run` accepted no composition:
ReleaseResources and Slots failed bytes; ReAcquireResources failed compilation.

ReleaseResources now accesses the retail lists through a body-local view,
following the existing destination's freeAllBuffers approach. Retail vertex
lists start at +0x9000 and the index list at +0x263d0. The destination includes a
ZH header whose slot arrays have 128 rather than retail's 512 entries. No header,
global declaration, compiler flag, class name or counted hatch changed.

After the repair the normal dry-run accepts the destination and
W3DBufferManager_ReleaseResources.cpp: three approved rows, 433 retail bytes,
including the already matched 92-byte ReleaseResources. Slots still fails bytes;
ReAcquireResources still fails a BfmeDynamicNativeVB/DX8VertexBufferClass pointer
assignment. Leave the actual merge to Luna, subject to the helper review below.

## Verification and composition limits

Commands were run from the repository root (DEST denotes the destination above,
and sibling names denote files in the same directory):

- `./build.sh DEST W3DBufferManager_ReAcquireResources.cpp W3DBufferManager_ReleaseResources.cpp W3DBufferManager_Slots.cpp`: baseline 17/17 exact.
- `./build.sh W3DBufferManager_ReleaseResources.cpp`: repaired body 1/1 exact.
- `tools/find_declared_unmatched.py` on the repaired donor: all definitions matched.
- `tools/tu_skeleton.py --merge DEST --dry-run`: accepted two sources/three approved rows as described above.
- `tools/name_lane.py consolidate --under Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/`, then `--check build/consolidation`: fresh planner passed after all temporary trials finished.
- `tools/check_csv.py`: OK, 98,272 functions, 15,668 symbols, 2,214 data rows.
- `tools/data_check.py` on the release donor: zero findings/outside-register findings; `--converged`: ten addresses, zero second names/unjudged names.
- `tools/class_gate.py`: pass; scoped `tools/eh_verify.py`: zero missing rows; `tools/ms_header_audit.py scan`: existing NULL drop-in has the same value, no conflicting/unverified/failed value. Its existing queue entry is preserved.

Ignored local receipts/scripts are under `build/sol-b5-buffer-*`:

- `proof.py` compares the four standalone objects before/after: all 17 scoped
  rows retain external definitions, selected COMDAT flags, undefined symbols,
  data facts and 24 references (18 owner, three alias, three EH). Only existing
  EH local-label numbers are normalized. This is the actual published change.
- `release-composition.py` observes the supported dry-run verifier and preserves
  its composed object: all three approved rows verify; six retained external
  definitions have identical bytes/selection flags; no new undefined symbols.
- `release-composed-bindings.py`: one scoped code binding before/after, no
  additions/removals or preexisting divergent copies.
- `release-data-selection.py`: unchanged two data definitions and zero scoped
  data references, with row_object overlaid for the composed object. All six
  retained providers match the earliest scoped provider under link_check's rank.

The trial composition drops the donor's two emitted helpers
`DX8IndexBufferClass::Release_Ref` and `DX8VertexBufferClass::Release_Ref`.
The actual standalone prerequisite retains both, and its provider bindings are
unchanged. The old local link index (2026-10-25 21:36, f995f30157) says neither
helper is referenced; this is supporting historical evidence only, not current
consumer proof. Luna must verify these removals against current consumers before
applying/publishing the merge. No successful byte build or old census substitutes
for that check. The composed trial has not been applied or published.

## ReAcquireResources attempt, reverted

A method-local retail view removed the initial pointer conversion error and
preserved all four standalone rows exactly. Composition then exposed another
ABI mismatch: the destination header declares
`DX8IndexBufferClass(unsigned short, UsageType)`, whereas retail calls the
`unsigned` constructor at RVA 0x00138980. At RVA 0x001160df the trial emits
`mov ax,[esi+8]` and calls the unresolved ushort constructor; retail pushes the
whole dword. The 198-byte extent also moves the cleanup funclets. No donor was
admitted. The trial source was fully restored and rebuilt 4/4 exact. Recorded
through re_log.py for ReAcquireResources RVA 0x0011604d, then released its claim.
Next prerequisite is a coherent retail index-buffer declaration, together with
the private vertex-buffer pointer views; do not reapply the failed local view.

The destination's preexisting unrowed getDX8Format definition remains untouched
(frozen-file finding); Slots remains a separate byte mismatch. No MessageStream
naming decision or VP6 work was attempted.

## Batch audit and handoff

Before committing, audited the complete outgoing range and staged prerequisite:
no source paths moved/added/deleted, no include/build input/registry references
changed, no protected debt/header/hatch registers changed. There are no path
consumers to repoint, and historical EA paths remain intact. Only the donor,
this evidence file and the tool-written attempt log are authored changes.
The shared docs/linking_obstacles.md claim is held by another worker, so it was
not edited; this handoff records the prerequisite and all remaining obstacles.

Other allocated probes: AptRenderingContext already accepts three donors/six
rows; dx8vertexbuffer and LadderDefs retain prior verified prerequisite repairs.
No redundant merge or unchanged blocker trial was applied. Browser's prior
conflicting COM-wrapper/BSTR handoff was reviewed without repeating its failed
trial. Inherited AptArray/AptCIH/polygon commits were already landed and their
old scope claims were released at session start.

BFME1 official upstream was checked (pinned de077dd5, official f7376375), but its
full before/after update verification is not complete: reference inputs were
preserved, and no freshness success receipt was written. No maintainer-only
link cycle, smoke or nightly command ran.

Publication handoff: retain the destination, release donor, Slots and this
evidence-file claims until this commit lands. Release them after confirmed push;
if the runner cooldown holds the commit, the next session must release them
after the runner publishes it. ReAcquireResources has already been released.

Recovery session: inherited commit was still pending at session start. Rechecked
`./build.sh W3DBufferManager_ReleaseResources.cpp` (1/1 exact, current dependency
receipt) and `find_declared_unmatched.py` (all defined functions matched), and
`check_csv.py` passed. Audited `origin/master..HEAD` again: the release donor is
modified in place; the added evidence document and attempt log introduce no
source-path moves, includes or registry changes. Official BFME1 fetch still
reports f7376375 versus preserved verified de077dd5; the full update remains
blocked on its cross-repository verification, with no success receipt written.
