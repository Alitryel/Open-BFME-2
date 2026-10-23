# Structure phase parser link repair

The six matched parser bodies (570 nonpadding bytes) referenced three undefined
phase-name arrays. Define each in its consuming unit and row its exact native
extent: Collapse at VA DCBC8C (24 bytes), RubbleRise at DCBCE0 (20), Topple at
DCBD30 (16). Pointer values, complete literal contents, order and null terminators
come from BFME 2 retail, independently of the existing parser names/layouts.

Reviewed BFME 1 donor 4483e88da1c2f3b9a273f779baac7458bd8bb891:
`game/GameEngine/Source/GameLogic/Object/Update/StructureCollapseUpdate.cpp`
uses a static phase-name array for the same parser purpose, but only four phases.
BFME 2's ALMOST_FINAL and the distinct RubbleRise/Topple lists are target facts;
the donor's four-entry list must not be copied verbatim. No donor layout change.

`./build.sh` passes all six existing function rows and all three new data rows.
`link_check.py --prepare-current` establishes a strict current object receipt;
ordinary `link_check.py` then predicts this unit links. `proof.py` compares the
saved pre-edit object with the verified object against the same published census
(144ed0ccab), refreshing only the owned object in memory: 0 -> 570 linked bytes.
This is a legacy prediction with self-strict inputs, not a closed-strict gain.
The published index is unchanged. The before object remains ignored under build/.

Sweep: SlowDeathBehaviorParsers.cpp has the same undefined phase table but also
two missing callees and three nonretail STL bodies; defining its table alone
would free no bytes, so it was left untouched. No other phase-table-only consumer
appeared in the census blocker scan.
