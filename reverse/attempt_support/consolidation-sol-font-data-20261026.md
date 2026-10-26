# W3DGameFont data prerequisite, 2026-10-26 (codexb)

Allocated family B shard 0/2 destination:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DGameFont.cpp`.
Inspected master `0bdd549334`; current parent naming planner and ordinary
`tu_skeleton.py --plan` approve the existing routing in memory. No merge,
split, path move, TU-map regeneration or new name is applied.

## Repair and bounded verification

`W3DFontLibraryLoadFontData.cpp` declared TheGlobalLanguageData through its
private GlobalLanguageData layout, requiring three alias pragmas. The data
ledger already records `?TheGlobalLanguageData@@3PAVGlobalLanguage@@A` at
RVA 0x009FDC84 and the private spelling as its alias. Declare the real
GlobalLanguage pointer and cast it to the existing private layout at the read.
Remove the three pragmas. No donor layout or recovered name is inferred.

Before and after:

- `./build.sh W3DFontLibraryLoadFontData.cpp W3DGameFont.cpp` (full paths):
  7/7 existing matched rows, one literal and one empty-string reference pass.
- `find_declared_unmatched.py` over both sources: all definitions matched.
- `data_check.py` over both sources: one finding before, zero after;
  `repair_queue.py retire data <load-source>` passes and retires exactly one
  wrong-name key. `data_check.py --converged` also passes.
- Staged source followed by `hatch_counters.py --update`: alternatename
  occurrences 3953 -> 3950. Two register keys represented three occurrences.
- Scoped `code_identity_gate.check` reports the same eleven findings and the
  same existing outside-baseline divergent
  `??_EPendingSurfaceStruct@Render2DSentenceClass@@QAEPAXI@Z` before and after.
  It comes from the unchanged destination's header closure. No code-identity
  key is retired and no new finding is introduced by this repair.
- `link_check.py --new-variants --staged-peers --shadow` over both sources
  completes before and after without new-variant findings. This is a preview,
  not a census result.

Objects copied before editing are recorded in `build/sol-font-before.json`.
`build/sol-font-identity-proof.py` uses allowed_symbols Obj/body and census
COMDAT selection APIs to compare every external code/data provider, its bytes,
relocations, flags and selection. The destination is identical. The load
donor differs only in one data relocation referent and corresponding undefined
symbol: the registered alias becomes the ledger's real GlobalLanguage name.
That referent still denotes the same retail data address; all provider bytes,
flags, COMDAT choices and other undefined bindings are identical. No changed
provider can alter other consumers' selected function bodies. No maintainer
link cycle, smoke test or nightly run was started.

## Remaining composition prerequisites

Normal `tu_skeleton.py --merge <destination> --dry-run` completes before and
after, accepting no pair. The repaired load donor's GlobalLanguage redefinition
is cleared; its next failure is GameFont's incompatible private field names
(`m_pointSize`, `m_nameData`) against the donor header. The private view has a
float at +0x0C and an extra request word at +0x1C; the ZH header has an integer
pointSize and no extra word. Its struct/class and method-access spellings also
differ. Reconciliation must preserve the real BFME 2 ABI and existing bindings.
This is not a demonstrated complete merge unblock.

The cache donor still needs four-argument FontCharsClass methods absent from
the destination's header. The destructor donor still redefines SimpleVecClass
and SimpleDynVecClass templates. Mixed BfmePod4 rows remain with their owner.
No unchanged failed donor was edited or retried independently.

Receipts: `build/sol-font-{before,after}-{build,trial,link}.txt`,
`build/sol-font-plan.txt`, scoped provider proof above. File reduction zero;
data debt retired one; code-identity debt retired zero; alias hatches removed
three; recovered/authored C++ bytes zero.

## Outgoing audit

At this commit, origin/master..HEAD is empty. Pending staged work is an in-place
load-donor edit, tool-owned data/hatch register shrinks and this evidence.
There are no source path additions, removals or moves requiring active tool,
hook, workflow, include, build-input or registry repoints. Historical EA paths
are preserved. No ledger, owner, fold proof, header queue, Microsoft queue or
flag override changes are needed for this declaration-only repair.

Keep destination/load/evidence file claims until publication is confirmed.
