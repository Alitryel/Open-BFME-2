# GarrisonContain composition recovery audit (2026-10-26)

Recovered the saved `tu_skeleton.py` composition that moves the approved
0x0047840C getter from `Disp8ByteChaseGetters.cpp` into
`GarrisonContain.cpp`. The existing `trackTargets` row remains in the TU.
No source file was removed; this recovery changes one row's source ownership.

Verification against current `origin/master`:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp`: pass, 2/2 matched rows.
- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp`: pass; all defined functions are already matched.
- `python3 tools/check_csv.py`: pass.
- `python3 tools/tu_ownership.py --staged --shadow`: pass (no findings).
- `python3 tools/data_check.py --staged --converged`: pass; 10 addresses, no second names or unjudged rows.
- `python3 tools/link_check.py --staged --new-variants --shadow`: pass; both staged TUs had current compile receipts and no new variant finding.
- `python3 tools/code_identity_gate.py --staged`: shadow mode reports five new divergent definitions for Sol to reconcile: `_STL::list<Object *>::_List_iterator` constructor, `OpenContain::asOpenContain`, `_STL::list<Object *>::begin`, `Object::getBodyModule`, and `Object::getContain`. No identity register was edited and no identity debt is claimed retired.
- The staged path-consumer search found only the expected `docs/doxygen/sources.cfg` input. Historical EA path evidence remains unchanged.

The current TU planner still reports 23 donors, five mixed files and three protected-register refusals; those are separate future consolidation work and were not altered here.
