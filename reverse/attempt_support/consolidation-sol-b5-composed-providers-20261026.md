# Sol B5: composed-provider follow-up, 2026-10-26

Follow-up to the published chunkio and debug_except declaration prerequisites,
after the index-buffer trial exposed why matching standalone objects and a
successful ordinary merge dry-run do not suffice. No source or ledger edit,
merge, debt retirement, file reduction or recovered byte claim in this audit.
Current allocated targets remain family B shard 1/2; scope claims covered the
seed and accepted donors. The preceding index trial is banked and reverted.

## chunkio: composed-provider acceptance demonstrated

`tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WWLib/chunkio.cpp --dry-run`
accepts seed plus chunkio_load_ctor.cpp, 29 rows. In addition to the previously
recorded 29-row standalone source proof, this follow-up inspects the actual
object produced by the supported merge verifier. No hand compilation or check
modification is involved.

- All 36 composed external definitions, their bodies/relocations, COMDAT
  selections and section flags match an existing standalone provider.
  No external definition disappears and no new undefined symbol appears.
- All five ledger call bindings across 29 rows compare equal, including their
  target addresses and identity classifications. Writable-data binding and
  definition sets also compare equal.
- The standalone objects contain two different vector-constructor-iterator
  copies (seed 50 bytes, constructor donor 34 bytes). This was investigated,
  rather than dismissed because a composed copy matched one input. The
  supported allowed_symbols Identity/definitions/kept APIs, with the batch's
  objects replaced in current ledger link order, select the same existing
  W3DTreeBuffer provider before and after. All 36 external names inspected
  retain identical selected digest, size and exclusive-definition status.
  This is scoped current-object selection evidence, not a new census or a
  claim that pre-existing helper debt elsewhere is cleared.

The declaration prerequisite published in 7c2777f0b2 therefore remains a
**demonstrated composition unblock** for the 93-byte constructor at 0x00614ef0.
Leave the donor for Luna; no downstream merge landing has been observed.
Mixed Common donors remain untouched. The ordinary merge must carry hatch
ownership through its tool and run the full batch checks when it is applied.

## debug_except: declarations repaired; another prerequisite remains

`tu_skeleton.py --merge Code/Libraries/Source/debug/debug_except.cpp --dry-run`
accepts seed, DebugExceptionFilter.cpp, DebugCopyDialogReport.cpp,
Rva0088E100DialogWatchdog.cpp and Rva0088E1A0ShowAssertCrashDialog.cpp: 15 rows.
The actual composed object preserves all 56 ledger call bindings and the
writable-data binding/definition sets, with no dropped external definitions
or new undefined names. However three of 26 external definitions change:

| Selected helper | Standalone bytes/digest | Composed bytes/digest |
| --- | --- | --- |
| Debug::RepeatChar constructor | 18 / 4c65958176e8 | 20 / 1b4b1a0c38cd |
| Debug::MemDump constructor | 39 / b5c77a5af01f | 38 / 5dab601ae1f8 |
| Debug::MemDump::Char | 32 / f9827cac910a | 33 / 8b1fd3815685 |

Before composition these helpers are selected from DebugExceptionFilter.obj;
afterward the composed object supplies the changed bodies. This is a real
selected-provider difference, not merely a changed unselected copy. COMDAT
selection and flags agree. Their changed bodies have not been shown equivalent
to retail; **do not merge based solely on the 15-row dry-run**. Investigate the
helper instantiation/compiler context without adding optimization hatches.
The class/include repairs published in 16992602a2 remain standalone-byte-exact
and increase ordinary acceptance from 13 to 15 rows, but this audit narrows the
handoff: complete merge acceptance is still blocked. No merge was applied.
The existing Common RecordInitialize byte rejection and mixed donors remain.

## Commands and receipts

- `./build.sh` on the seven accepted sources across both targets:
  44/44 exact, three data rows exact, 141 literals plus 13 empty-string
  references and 53 imports verified. Five current cached TUs, two compiled.
- Actual composed objects captured from `tu_skeleton.Verifier.matched`, called
  only by the supported `tu_skeleton.merge(..., dry_run=True)` entry point.
  Provider comparison: build/sol-b5-followup-composition.py/.json.
  The initial equality assertion correctly refused debug's three changes.
- Relocation binding comparison: build/sol-b5-composed-bindings.py/.json.
  Its initial strict check correctly reported the pre-existing chunkio iterator
  variants; the selected-provider follow-up resolves that ambiguity above.
- Current object order and selected-provider/data comparison:
  build/sol-b5-composed-selection.py/.json, using allowed_symbols and data_check
  APIs. All objects parse under strict=True; this is not a freshness receipt
  for the whole repository or a substitute for the next census.
- Composed objects: build/sol-b5-{chunkio,except}-composed.obj. Planner refreshed
  for WWLib; no input map, baseline or repository checker was changed.

## Publication and claim handoff

Earlier inherited recovery plus prerequisite batch was published through
7c2777f0b2. The evidence-only 30082a3c86 index-buffer handoff is pending with
this audit; /opt/runner/publish held the first commit below its batching
threshold. There are no source moves/deletions from the outgoing merge base
7c2777f0b2 through HEAD plus this staged audit. Tools, hooks, workflows, includes,
build inputs and registries require no path changes; historical paths remain.

Release source file claims after this read-only audit: no source edits are
pending. Keep the evidence-file claims until the runner confirms publication:
consolidation-sol-b5-index-lock-20261026.md/.patch,
consolidation-sol-b5-index-lock-composition-20261026.json and this handoff.
Settle these manually after landing; release --landed only settles RVA claims.

Earlier pre-push strict receipt freshness remains inconclusive (LINK-008,
index f995f30157 older than base 97cecf650b, three missing current source
receipts, first Eva.cpp). Its shared register was held by another worker;
evidence is retained in the preceding index handoff. No maintainer-only run
was started. File reduction, identity debt retired and recovered C++ bytes:
all zero. The verified result is prerequisite repair and scoped acceptance,
with the remaining helper-provider blocker explicitly retained.
