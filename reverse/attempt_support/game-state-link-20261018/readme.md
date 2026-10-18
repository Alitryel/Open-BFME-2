GameState destructor link repair, 2026-10-18

GameStateConstructor.cpp already uses the BFME2 SubsystemInterface shim and
Snapshot name-slot interface. The destructor used a one-slot padded subsystem
view and left both inherited Snapshot and subsystem slots unoverridden. Its
two emitted GameState tables therefore disagreed with the constructor.

Adopt the existing subsystem header, its real allocator declaration, and the
same virtual overrides as the constructor. Preserve the already certified
folded CameraMarker list ABI view and every destruction operation. Add the
constructor-proven E14/E18 scalar fields and assert the native E1C extent.
There are only two providers of these GameState tables in the published index;
both are checked together. No other source needs this cause repaired.

Target evidence (game.dat, ImageBase 400000): Snapshot table C0401C RVAs
2DE585, B3FD0, 2DE57F, 2DBCCA; primary table C0402C RVAs 2DF2DA, 2DE641,
1B5384, B3FD0, 5CB9FF, 47A699, D43D0, 47A69C, B3FD0, 2DEE9A,
B3FD0, 5CB9FF, B3FD0, 47A69C. These establish the same overrides and
fourteen-slot subsystem layout used in the constructor, rather than a shorter
compatible-looking table. Constructor stores prove E14/E18 and allocation
proves E1C. The existing donor-derived names and folded list-view uncertainty
are retained; this repair adds no donor identity claim or pin.

Checks: paired legacy link preview, census c2c5ac8c27, 199 -> 379 B (+180),
2/2 units link after the change. Strict reusable preparation byte-verifies
26/26 rows, six renumbered funclets, three complete constructor folds and the
class-name literal. Destructor alone is 6/6 byte-exact, including four complete
EH cleanups. The first compile exposed allocator redefinition after header
adoption; removing the private allocator view fixed it. No body-byte repair
or gate exemption was needed. No closed-strict link closure was measured.
