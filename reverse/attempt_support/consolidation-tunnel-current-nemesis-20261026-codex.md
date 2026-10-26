# TunnelTracker current-nemesis prerequisite, 2026-10-26

Seat: codex, family A shard 0/2. The allocated queue includes
`Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp`. No inherited edits or
unpublished commits remained at the start (766153ce00). Read the prior nemesis
handoff before retrying: the current map now makes GetCurNemesis eligible rather
than protected, so this is a changed prerequisite, not a repeat of its old refusal.

The scoped Common/RTS planner reports original-image, WorldBuilder and reference
leads; these are distinct from placement approval. The current in-memory map in
the merge trial approves the three consumers for this destination. No rows move
in this prerequisite. The snapshot was refreshed after the header edit and its
currency checked before the final trial.

## Repair

The seed and UpdateNemesis already composed (five rows). GetCurNemesis failed
because the seed's Object declaration lacked `rva002943B2` and
`isEffectivelyDead`. The new TU-scoped `TunnelTrackerNemesisView.h` shares the
existing accessed declarations among the seed, UpdateNemesis and GetCurNemesis.
It preserves contain head +0x10, nemesis ID/time +0x20/+0x24 and the existing
Object fields at +4, +0x74, +0x274 and +0x438. This is a union of target accesses,
not recovery of a complete retail Object or TunnelTracker class. No method body,
compiler flags, global, pin or ledger row changed.

## Verification

`./build.sh` on all three consumers passes 6/6 matched rows before and after,
including string, float and import checks. `find_declared_unmatched.py` and
`class_gate.py` pass. `allowed_symbols.py --source` reports nine owner references,
zero wrong bindings. `data_check.py` reports zero findings.

Saved before objects were compared to freshly verified objects using the
upstream object readers. Every non-debug section is identical, including its
bytes, relocations, flags and COMDAT selection policy. External code and data
definitions, undefined symbols and alternatenames are identical for each of
the three consumers (4/3/3 external code definitions; 5/4/4 non-debug sections).
Consequently this declaration-only edit cannot change shared-provider selection.
The scoped owner-reference comparison retains all nine references, with zero
added or removed facts. `link_check.py --new-variants --paths-from` the three-source
list exits zero. This is admission evidence, not a new LINKED census claim.

The final official merge dry-run accepts the seed, GetCurNemesis and
UpdateNemesis together: six rows, versus five before. This demonstrates that
the existing 97-byte GetCurNemesis row can join the TU; no merge was applied.

Local evidence is under `build/codex-tunnel-nemesis-*`, plus
`build/codex-tunnel-{before,after}-dry-run.txt`, `-build-{before,after}.txt`,
`-identity.txt`, `-data.txt` and `-link.txt`. The scratch comparisons call
`allowed_symbols.Obj`, `_object_defs`, `_comdat_selections`, `Identity`/`scan` and
`link_check.alternate_names`; no hand compilation or link cycle was used.

## Other surveyed target

AssaultTransportAIUpdate's allocated dry run accepts no donor: missing inherited
helper/receiver declarations, BfmeXfer's Xfer redefinition and a canonical
GameLogic collision. No edits or claim were made there. Evidence:
`build/codex-assault-before.txt` and the corresponding blocked re_attempts entry.
It requires coherent receiver/header work before another trial, not isolated
retrying of the same bodies.

## Scope and handoff

No source path moves, file reduction, debt retirement or recovered C++ bytes.
The source-file count is unchanged; one scoped declaration header is added.
No entries for these three sources exist in the code/data identity or header
registers; protected Xfer and other donors retain their debts and owners.
The compatible donors are left for Luna; trial acceptance does not assert a
later merge landing or a census improvement. Remaining donors still encounter
allocator<char>/receiver reconciliation or mixed/protected ownership. The
deleting-destructor trial now lacks the EmitVtableTag constructor declaration;
its earlier byte mismatch remains history rather than a newly verified result.
Retain that history and do not repeat unchanged failures.

Fetched origin at c85d92855d before the publication audit. There are no existing
outgoing commits or source moves; the staged prerequisite adds one header and
changes three include consumers. The upstream-only changes since 766153ce00 do
not touch this scope. Searched the combined basenames in active tools, hooks,
workflows, Code, build.sh, and identity/data/header registers. The only new path
consumers are the three intended quoted includes. Other source matches are
existing provenance and pending-donor comments, retained as historical evidence.
No build input, active tool or mutable registry needs repointing. The pending
batch does not change the TU map, ledgers, queues, debt baselines or hatch counts.

The four scoped file claims (three sources and the new header) remain held until
publication is confirmed. No RVA claims were needed for the declaration repair.
