# Path curve candidate at 0x00365309

Result: blocked; the existing bank (weighted fitness .97907, 16 structural regions, 26 memory and 0 register differences) is kept. The candidate's only executable-source change is removing Vector3's empty user-written destructor. That makes the final midpoint exact and drops structural regions to 14, but adds 5 register and 3 memory differences and lowers the weighted fitness to .976, so it was not banked. It is worth combining with a fix for the new register differences rather than repeating.

## Measurements and validation

The authoritative run receipt is build/path-365309-w8/handoff-measurements.json. Both candidates emit the full native extent with no unresolved calls. Commands are recorded in build/path-365309-w8/*-command.json. Raw CLI measurements were repeated independently through explain_mismatch.py and align_diff.py after removing stale comments from the candidate.

| Measurement | Incoming bank | New bank |
|---|---:|---:|
| COFF extent | 2177 | 2177 |
| Differing bytes after gate relocation substitution | 126 | 124 |
| align_diff structural regions | 16 | 14 |
| align_diff raw memory differences | 26 | 29 |
| align_diff register differences | 0 | 5 |
| Memory differences excluding COFF relocation operands | 7 | 10 |
| Weighted scorer fitness | 0.97907 | 0.976 |

The structural count is the first ranking key specified by the assignment. Relocation and branch lines are excluded as defects. align_diff's raw memory count includes absolute DIR32 constants, which its classifier labels memory; relocation-counts.log removes those using actual COFF relocation spans. The byte count is diagnostic only. build.compile_function substitutes DIR32 operands at the current positional retail offsets, so shifted relocation sites in a failing candidate can contain nonsensical diagnostic operands. Those values are not address claims.

Raw validation paths: build/path-365309-w8/baseline-explain.log, baseline-align.log, best-explain.log, best-align.log, relocation-counts.log, identity.log, home-declarations.log, check-csv.log and pin-consistency.log. The explain runs compile successfully but report byte mismatches. The actual replacement bank was recompiled and measured in final-bank-explain.log and final-bank-align.log. final-state.json verifies that its emitted bytes reproduce the chosen candidate and that removing the empty destructor is the only executable-source change. final-check-csv.log and diff-check.log contain the post-bank checks. The home unit's find_declared_unmatched check, check_csv and pin_consistency --check pass. add_match and build.sh were not run because the candidate is still in the attempt bank and there is no new matched source to gate.

## Identity and inputs

Base commit: fb5b8848171738ca8cdd8e92e959c6824291efed. Donor checkout: a18d9ed50607e9175de4d6568798d7d73119de09. Flags: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /Oy-. Compiler profile remains the repository default MSVC 7.1. No compiler, header, layout, pin or retail extent was changed. Destination from repair_queue.py dest is Code/GameEngine/Source/GameLogic/AI/PathDtor.cpp, using the neighbour heuristic; no approved original TU mapping exists.

Target facts: Ghidra records the boundary 0x00365309..0x00365B8A, retail ends in RET28 and the next body has a distinct prologue. ECX carries Path this, seven stack arguments are consumed, the final blocked argument is passed through as an argument word to IsLinePassable, and the existing Boolean signature agrees with the rowed caller. Native accesses independently establish optimized link +8, position +0xC, layer +0x18, portal +0x20 and DirectionOptions offsets 0/1/4/8. Native call destinations are enumerated with their COFF names in identity.log and resolve through existing owners/pins. The original method name remains unknown; retain ?rva00365309@Path@@QAE_NPAVObject@@PAVPathNode@@PBUCoord3D@@PAUDirectionOptions@@HM_N@Z.

Donor facts: the inspected ZH GeneralsMD Vector3 header has no destructor, uses the same three float members, member-wise copies, the same Normalize arithmetic and rotation formulas. AIPathfind.h supplies getPosition and setPosition accessors. Their use was tested as source leads; they do not establish BFME2 identity or donor layout. WB VA 0x00F1FC60 remains a curve-construction semantic guide. No additional real name is asserted.

## Experiments and remaining work

Every registered hypothesis states its refuting observation in build/path-365309-w8/hypotheses.md. H1 local coordinate lifetimes and midpoint accumulators, H2 static/output-pointer/value-return rotations, H3 donor node accessors and setters, and H4 isolated midpoint x accumulators either reproduce the incoming bank or worsen alignment. H5 removal of the artificial destructor improves the structural count and corrects the final midpoint; the donor scalar constructor, assignment and scalar operator forms alone do not. H5 follow-ups through Set/array/copy/component initialization, H6 Length2/Normalize locals and static wrappers, and H7 scalar/copy constructor store order do not improve the chosen candidate. Some Length2 local forms recover the incoming bank's initial register cycle but also restore its wrong midpoint order. All trial sources, objects and raw output remain under build/path-365309-w8/; aggregate probe outputs are probe.log, accessors.log, vector.log, direction.log, normalize.log and construct.log.

Remaining mismatch: the initial direction normalization has operand/register differences, cosine FSTP placement and independent SSE loads differ at four rotations, zero/load ordering differs around +0x46E, and node/options restores are reversed around +0x790. There is no unresolved callee prerequisite and no compiler-impossibility claim. A next experiment must address this lifetime/operand-identity coupling or provide a new source-context explanation; do not repeat the recorded negative forms.

Model: gpt-6.1-sol. Clock receipt: 2026-10-19T02:02:31+00:00 to 2026-10-19T02:11:52.982760+00:00, 9.37 minutes at recording. No commits, network calls or background tasks were started.
