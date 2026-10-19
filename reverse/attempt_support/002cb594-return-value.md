# getLinearPosition at 0x002CB594

## Result and next prerequisite

The replacement bank is a strictly closer compiler probe, with a byte-exact helper after normal relocation resolution. It is not a production recovery: replace linearPositionCompileProbe with the genuine Weapon::privateFireWeapon caller at RVA 0x002CE30A, and reconcile the proven Coord3D constructors with its canonical class contract/header before landing in Code/GameEngine/Source/GameLogic/Object/Weapon.cpp. No production source, ledger row, symbol pin or gate was changed. The bank keeps every original comment, including its warning about the synthetic caller.

The compiled symbol is `?getLinearPosition@@YA?AVCoord3D@@ABV?$vector@VCoord3D@@V?$allocator@VCoord3D@@@_STL@@@_STL@@HPBVObject@@@Z`. The former reference-return symbol remains only in historical comments. The replacement returns Coord3D by value, uses the existing coord3d.cpp owner's class/base view and componentwise copy constructor, and removes padding aggregates, constant equal-arm ternaries and the unused barrier declaration. The explicit output-reference signature was diagnostic, not established source provenance.

## Measurements

These values are generated from the raw align_diff logs and build.compile_function results in build/worker-002cb594. Both measurements used fresh objects and BFME_OBJSTORE=off.

| Probe | Emitted/retail bytes | Structural regions | Memory differences | Register differences | Differing bytes after relocation resolution |
|---|---|---|---|---|---|
| Previous bank | 188/199 | 7 | 11 | 4 | 111 |
| Replacement | 199/199 | 0 | 1 | 0 | 0 |

The replacement's single raw memory difference is only the DIR32 TerrainLogic operand (`mov ecx,[0]` versus `[0xDFEC50]`); explain_mismatch resolves it and reports exact match with no unresolved symbols. Branch and relocation lines are not defects. The source compiles reproducibly at both best.cpp and the bank path; the final bank-path replay is logged separately.

## Evidence and tested hypotheses

All seven prior verdicts were read before the first experiment and captured in prior-verdicts.log. They cite the bank but no retained trial path. Related closure records in crack-d-closure-20261014, crack-g-parents-20261014 and crack-e-finish.md agree on the genuine caller requirement; no unavailable historical 189-byte source was reused. Each new hypothesis, supporting observation, refutation criterion and result is recorded in hypotheses.md before its experiment.

Target facts: the Ghidra inventory and native disassembly establish the complete 199-byte body from 0x002CB594 through RET at 0x002CB65A, immediately followed by the next body at 0x002CB65B. The native caller at VA 0x006CE497 establishes ECX vector, EAX index, EDI object and ESI result. Native bytes establish 12-byte vector elements, object matrix +8, position +0x38/+0x3C, virtual terrain slot +0x18, and the exact x/y arithmetic grouping. Matrix3D::Get_Z_Rotation is the verified eight-byte owner at RVA 0x00712020; sin/cos are the existing CRT import thunks at 0x00629216/0x0062920A; TheTerrainLogic is the existing converged global at RVA 0x009FEC50. No new alias was introduced.

Identity and source-shape evidence: WorldBuilder VA 0x00BB9080 asserts `getLinearPosition`, `ndx>=0 && ndx<linearVec.size()` and the original Weapon.cpp path. WB BB911D..BB9344 proves the input pair, three-component rotation local, position add and return construction. WB return-construction state at BB9330..BB9336 supports return by value. The existing BFME2 coord3d.cpp owner supplies the user-written copy constructor at RVA 0x004216D3, the empty constructor at 0x0047A6A9 and destructor at 0x000B3FD0. Using that proven copy constructor enables MSVC NRV and reproduces the retail ABI, spill homes and both scheduling clusters. The generated canonical header currently omits these constructors and uses the ZH struct view; it was not edited.

Donor facts, kept separate from target proof: the unchanged GeneralsMD Vector3::Rotate_Z header supports the rotation semantics, and Thing.h/TerrainLogic.h support getter and normal-parameter declarations. Vector3 ownership of the local is a structural inference, not a recovered target name. The final bank uses Coord3D arithmetic directly and does not import a donor helper. All actual donor headers remained unchanged with EA comments intact.

Ruled out by raw trials: scalar cleanup, y regrouping alone, trivial Coord3D block copies, unchanged donor Vector3, scalar/pair/product staging, local planar shapes, cached terrain pointer, inline getters and pointer/reference/base views. Several intermediate trials traded one defect class against another and were not retained. One broad replacement temporarily also changed the Object position view in scratch; isolated controls restored its Coord3D declaration and reproduced the measurements. Return by value with the trivial canonical struct recovered scheduling but emitted MOVSD copies; the proven owner copy constructor removed that precise blocker. No volatile operations, extra stores, asm, naked code or optimization pragma were added.

## Reproduction and raw outputs

Input BFME2 revision: `394012baa68b43c4b3098e57286b4a3375d91837`. BFME1 input revision: `a18d9ed50607e9175de4d6568798d7d73119de09`. Compiler flags are the bank's first cl line: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC, with its original include paths. All scripts, trial sources, failed dependency-setup sources and raw logs are retained under build/worker-002cb594. trials.py deletes both object and dependency receipt before every align_diff measurement; each substantive trial also has its own source path.

baseline-align.log, best-align.log and bank-align.log are raw align_diff outputs. baseline-explain.log and final-explain.log are raw explain_mismatch outputs. probe-verification.log independently checks full relocated bytes, unresolved callees and preservation of every original bank comment. retail.log contains native, caller, WB and callee disassembly plus original WB assertion strings. pin-consistency.log and check-csv.log contain the repository checks. initial-trials.log, vector-trials*.log, staging-trials.log, planar-trials.log, isolated-trials.log, input-trials.log, api-trials.log, return-trials.log and nrv-trials.log preserve all trial outputs; missing always.h and duplicate placement-new were setup failures, repaired only in scratch.

No production source was written, so add_match, build.sh and find_declared_unmatched were not run for a landing. No claims, network, git writes, commits, pushes, verification runners or background jobs were started. Timing receipt is timing.json; model=gpt-6.1-sol.
