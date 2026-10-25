# FunctionLexicon registry access prerequisite, 2026-10-25

Scope: Common/System/FunctionLexicon.cpp and Common/Rva00DFF024RegistryLookup56.cpp.
Read current AGENTS.md, consolidation workflow, the Common Luna handoff, scoped
planner packet and current in-memory TU plan. Both sources passed frozen checks;
file claims acquired before editing. Rva0039AF9B and GameClient destinations held
by other seats were left untouched.

The seed's protected findFunction omitted the registry wrapper's existing friend.
Both files now carry the same FunctionLexicon declaration: existing table offsets,
12-table limit, TableIndex vocabulary and callable signatures, plus that friendship.
The donor's wrapper expressions, signatures and bodies are unchanged. These are
existing BFME2 row facts, not an external layout/name claim. No pin, hatch, flag,
global or register changed.

`./build.sh` verifies all six rows (seed four, donor two), 371 retail bytes.
`find_declared_unmatched.py` passes for both. The ordinary supported
`tu_skeleton.py --merge ... --dry-run` now accepts both sources and six rows;
previous protected-access rejection is cleared. Leave the compatible donor for
Luna. The constructor donor still fails Bool-before-subsystem-header include order;
its base/receiver reconciliation also remains unproved. Mixed donors stay intact.
Local exact trial: build/codex-functionlexicon/dry-run.txt.

Publication audit: origin/master..HEAD and staged changes contain no source path
moves; no path consumer requires repointing. No identity debt retired, files removed
or newly recovered C++ bytes. Retain the two file claims until confirmed publication;
then release them. No RVA claims were acquired in this file-scoped prerequisite.
