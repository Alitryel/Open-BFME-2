# RadarUpdate receiver prerequisite, 2026-10-26

Seat codex, family A shard 0/2. Recovered the interrupted preceding session's
verified declaration repair before selecting new work. No source path or ledger
row moves in this prerequisite commit. No debt key is retired, no file is
removed, and no new authored C++ bytes are claimed.

The allocated destination is
`Code/GameEngine/Source/GameLogic/Object/Update/RadarUpdate.cpp`.
Its existing update/extend receiver omitted the pool-key method and the transfer
consumer's complete Xfer operand forward declarations. The original merge trial
accepted no composition: the pool-key donor failed C2039/C2270, transfer failed
BfmeXfer.h operand declarations, and the constructor failed its base/receiver
declarations. `RadarUpdateView.h` now shares only the receiver declarations
needed by the seed, pool-key and transfer consumers, with the existing target
field offsets and update-interface adjustment. The constructor's complete
virtual interface is deliberately unresolved.

The supported merge dry-run now accepts the seed, `RadarUpdatePoolKey.cpp` and
`RadarUpdateXfer.cpp`: five matched rows across three sources, versus no
composition before. This is a demonstrated prerequisite unblock, not a claimed
Luna landing. Leave the accepted composition to the consolidation seat. The
constructor remains rejected (C2511, no matching RadarUpdate constructor in the
shared receiver), and `Code/GameEngine/Source/Common/Rva0024A797Derived.cpp`
remains mixed. A future merge must preserve the pool-key data register and
ledger keys that the tool reports for transfer; do not silently retire them.

Verification and audit:

- `python3 tools/check_csv.py`: all ledgers accepted.
- `python3 tools/find_declared_unmatched.py` on the three consumers: all defined
  functions already matched.
- `./build.sh` on the three consumers: five of five matched rows retained,
  including literal/reference checks.
- `python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`
  and the current six-row `tu_skeleton.py --plan` retain the original-path
  evidence and placement distinctions. Planner donor hints are not target ABI
  proof. The before/after `--merge ... --dry-run` reports are local
  `build/codex-radar-before-20261026.txt` and
  `build/codex-radar-after-20261026.txt`.
- Scoped COFF comparison using upstream allowed_symbols/link_census object
  readers: all 12 external code definitions, undefined-symbol sets, alias
  directives, all 22 non-debug sections with their relocation targets/COMDAT
  policies, and external data definitions unchanged across the three objects.
  Thus this header repair changes no shared provider candidate or consumer
  binding; it does not rely on the byte gate alone to establish that fact.
- `allowed_symbols.load/scan` before/after finds the identical nine code-reference
  tuples; `data_check.object_facts` finds identical data definitions/references.
  Proof scripts and receipts are local `build/codex-scoped-object-proof.py`,
  `build/codex-radar-object-proof.json`, `build/codex-radar-refs-proof.py`,
  `build/codex-radar-reference-delta.json`, `build/codex-radar-data-proof.py`,
  and `build/codex-radar-data-delta.json`.
- The two pre-existing shadow wrong-name data findings on the pool-key statics
  remain; no baseline or gate was changed.
- Tooling compatibility audit covers `origin/master..HEAD` plus this staged
  prerequisite. There are no moved/deleted source paths, affected path
  consumers, ledger repoints or protected-register edits. The new header has
  exactly the three verified consumers above; historical EA paths remain.

Fresh `tools/link_check.py` on all three consumers reports three LINKS, with
312 -> 312 predicted linked bytes. This is diagnostic only, never a census
measurement. Receipt: `build/codex-radar-link-recovered-20261026.txt`.
No maintainer-only link cycle, smoke test or nightly builder was run.
