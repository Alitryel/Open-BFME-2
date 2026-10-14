Seat N checkpoint history, 2026-10-14. The final update below supersedes the earlier placement status; FindAttackPath remains partial.

- Landed assigned bodies: 418a6712ed, HordeContain movement position 0x46B05B/2037B; 1a778ffb6c, HordeContain::_updatePosition 0x471464/2966B.
- ABI repairs: eea6f2960b Locomotor receiver1E4194; e59dfc9375 Pathfinder receiver/coordinate values2EE49B; 97317fa06f getPortTransform392802 Boolean return; 6745c2f45f overlap30596C nontrivial position value and exact1701B message caller; c0e439cf5c feedback constructors4E6745/70B and4E669A/171B. Normal hooks, no pushes.

FindAttackPath 0x2FAD13 has a proven2117B extent, ending2FB558 RET32 (the original2124-byte request was oversized). Bank score.97969, frame7C and size2117 exact. All instruction opcodes and137 patched call/jump/return edges agree; remaining differences are stack displacements. Two ordered volatile reads of a normalized local are a provisional scheduling aid, not an object-layout claim. The adjacent patch restores the nonvolatile.97875939 draft.

The major gains were jointly visible86B normalize and41B movement-context constructor, the Object+A8 geometry accessor returning a float instead of a reference, visible23B holder deletion without a false throw specification, and ending the quick-search3D delta lifetime while retaining only its scaled XY values. Many earlier declarations, lifetimes, helper visibility and compiler variants were rerun after these gains; thousands of guarded permutations did not resolve the remaining stack homes.

Native start/victim indices occupy-3C/-38; bank-4C/-48. Native quick normalized delta and retained XY use-48/-44; bank norm temporary-6C and retained XY-4C/-48. Native curPos, victim delta and outer cell center share-78; bank curPos-44, victim delta-6C and outer center-78. Other principal scalar slots, goal-60, query-88, frame and control flow match.

Landing still requires helper ownership reconciliation, not just those slots. The visible2F83F5 neighbor remains partial; its newer seat-T f10bba95e4 bank was reviewed and tested with no parent gain. Existing code at2F314A has an exact544B coordinate-reference LOS provider. Private proofs also reproduced the48B typed wrapper2F1C25, the83B hierarchy lookup53446D with integer cell coordinates, and the168B movement predicate2E6DC4 with query-context first, cell second. Their foreign-owned home files were not edited. The search counter at VA DFF0CC still needs a real data owner. WorldToCell and other diagnostic helper context must pass owner checks before any recovery claim.

handleBuildPlacements 0x2A21E1 has proven4212B extent ending2A3255. Full WorldBuilder DAD2E0/9324B and native instructions supplied the reconstruction. Current bank.92583 emits4214B/frame194. No partial parent source was placed in Code.

The former private-EAX blocker29B9E5 is resolved: an ordinary visible static C++ helper emits all67 bytes exactly through the real reconstructed parent. Its module-data virtual slot is+60, and TerrainResourceBehaviorModuleData supplies the self-return there. An unreferenced static helper is omitted, so it cannot honestly land independently before a retained real caller.

The full reference Matrix3D implementation plus visible BuildListInfo::getLocation reproduces the native SSE sequence. WorldBuilder's FOUR tint branches matter: combining the first two conditions changes codegen. A one-call command selection expression is required in the port-data path; a trial with two virtual calls scored higher but was rejected as inconsistent with retail. Position vectors with nontrivial element lifetime, visible placement-record destructor, field getters, allocator/destructor variants, named module key and visible63B module finder/8B and16B collector helpers did not improve the current bank.

Remaining placement instruction changes are in the port-preview setup: the module pointer spills at EBP-44 instead of ESI; zero remains in ESI; the command value uses EAX with an extra branch instead of a default held in ESI. Most other operations align once registers and stack slots are normalized. Native end-pixel-54/-50 becomes-48/-44; native port/math point-4C/-48/-44 becomes-54/-50/-4C. The native194 frame matches.

The bank embeds an extended copy of the current GameLogic declaration to represent its resource manager at+170; landing must use the shared header. The existing home InGameUI.cpp still has a present-unmatched ZH placement body that must be removed when its complete replacement lands. UI+574 is a20B feedback font/color settings record, not a pixel coordinate; the landed constructor repair establishes that contract. The bank's struct layout agrees.

Post-repair place_bodies scans across the four affected overlap/feedback sources found0 bodies and0 pins. link_check could not run because the worktree has no census index; no verification runner was started. The feedback repair's normal hook verified246 source units (including1549/1549 rows in its180-source dependency pass). The overlap repair verified18 dependent rows. Both are existing-coverage repairs.

2026-10-14 08:14 UTC: Four typed FindAttackPath helpers now also verify TOGETHER in one private context: 48+168+544+83 bytes, no unresolved relocations, exact full bodies. Parent remains2117/frame7C/.97969, or.97876 without the ordered local reads. The typed-context patch and JSON manifest preserve this combined proof. Applying that diagnostic patch adds an extended private Coord3D view; production landing must reconcile the shared header and real owners. The current pathfinder.cpp/neighbor claim belongs to crack-z and was not touched.

Ghidra MCP became unavailable (HTTP transport to127.0.0.1:8000); a retry after a minute failed too. Prior saved Ghidra evidence, full native disassemblies and WorldBuilder bodies remain available.


2026-10-14 final placement recovery: `InGameUI::handleBuildPlacements` at
0x002A21E1 is now whole-body exact, 4212 bytes, with the complete seven-state
EH graph and native 0x194 frame. The static module lookup at 0x0029B9E5 is
also whole-body exact, 67 bytes, compiled through this real caller. Production
source: `Code/GameEngine/Source/GameClient/InGameUIHandleBuildPlacements.cpp`.
Both rows passed `add_match`; the new source and the old InGameUI home passed
9/9 rows together, with one string and eleven floating literals verified.
The old unpinned ZH placement definition was removed from the home file.

The decisive source change was joint: initialize the default command before
fetching its button, and retain WorldBuilder's named Boolean result from
getBuildPortData. Either change alone missed; together they restored all
register and stack allocation and the EH graph. Native chained assignments
then fixed store order. One final commutative SIB byte at 0x002A2DD4 required
a qualified distinct read of the icon pointer after setPosition. That local
volatile access changes no instruction count and makes no volatile layout
claim. Broad helper-visibility, type, lifetime, compiler and constructor-order
trials had left that same single-byte difference.

The data audit also mattered: the terrain renderer is the existing
`g_00DFF080` owner, not the draft's `TheTerrainVisual` name. DIR32 masking alone
would not have caught that wrong binding. Shared GameLogic, PlaceCoord and
feedback headers now provide the relevant layout and call contracts. Retired
the false Object::unlook pin at this address and the redundant correct parent
pin, and removed their hatch entries plus the obsolete present-unmatched
entry; no baseline grants were added.

FindAttackPath is the remaining handoff: bank .97969, native extent 2117,
all opcodes and control flow aligned, different local stack homes as detailed
above. Later named-Boolean and helper-visibility trials made no further gain.
Its body claim was released after several hours without measurable progress;
foreign-owned helper files remain untouched. The typed-helper patch and JSON
are diagnostic proofs, not production recovery claims. Ghidra stayed down;
link prediction remains unavailable without the census index.

The shared Coord3D-to-PlaceCoord constructor initially shifted two pointer
spill slots in the existing 1701-byte PlaceEventTranslator body. Private
isolation proved the constructor, not GameLogic's manager field, caused it.
Restoring that consumer's direct native kind-bit test (the same field, mask
and condition as its prior accessor) restores the complete body with the
new constructor present. Providers and both consumers are verified together.
