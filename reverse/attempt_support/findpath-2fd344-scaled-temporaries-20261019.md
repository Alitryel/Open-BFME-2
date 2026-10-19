# FindPath scaled-temporary investigation

Result: blocked. Preserve reverse/attempts/0x002fd344.cpp unchanged. Input revision f51bbefda6a8b5ab3437d6028401cf990d39f75d. Model: gpt-6.1-sol. Source owner: Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp. No production source, pin, ledger row or compiler setting was changed.

The target is ?FindPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2PA_N@Z at RVA 0x002FD344, extent 781 bytes through 0x002FD651. WorldBuilder VA 0x00D48230 names Pathfinder::FindPath, supplies its original source path and returns with RET20. The retail body also ends in RET20; the preceding AdjustDestination row ends at its entry and the next row starts at its end. Retail and the baseline agree on every resolved callee, including QuickDoesPathExist, Coord3D length/Normalize, vector erase, FindClosestHierarchicalPath and InternalFindPath. WB's automatic unnamed-callee pairings are not additional identity proof.

All ten prior verdicts and the bank's complete comments were read before experiments. Their cited bank and current owner were inspected. The target-specific crack-g-wave5 ranking and JSON repeat the bank evidence. Historical missing InternalFindPath and erase dependencies are now resolved. The current owner already contains the noinline inline math definitions and Gen_p12pod, so replay omits duplicate definitions and adds only the missing LocomotorSet fields/name accessor and FindPath declaration.

Trials retain the owner's compiler flags: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB, with reference/shims/bfme2_ascii and reference/shims/bfmealloc include directories. Quoted relative includes are resolved against the owner directory for the scratch copies; headers and their contents are unchanged. Object files and dependency receipts are retained in the task's objects directory.

The new hypothesis was that computing scaled y before scaled x into separate scalar temporaries, then storing x,y,z, could separate compiler value identity from emitted store order. Prior subtraction permutations changed both; docs/matching.md identifies first-assignment identity as an SSE allocation input. The registered refutation was an unchanged baseline or new structural, memory or register defects. The hypothesis and both follow-ups were refuted.

| Trial (one probe each) | Emitted bytes | Differing patched bytes | Structural regions | Raw align memory differences | Raw align register differences |
|---|---:|---:|---:|---:|---:|
| Replayed bank | 781 | 4 | 0 | 11 | 0 |
| Scaled y,x,z temporaries in caller, stores x,y,z | 781 | 45 | 0 | 42 | 10 |
| Same temporaries inside inline scale helper | 781 | 45 | 0 | 42 | 10 |
| Preload y,x,z in helper, multiply/store x,y,z | 781 | 4 | 0 | 11 | 0 |

The align tool counts nine absolute-address relocation sites as memory differences in all four trials. The baseline therefore has only two actual memory/register operand differences. Its four differing patched bytes are at offsets 0x1C4, 0x1C5, 0x1C9 and 0x1CA. At retail RVA 0x002FD505 the target reloads y into xmm2 from EBP-0x20, followed by x into xmm1 from EBP-0x24 at 0x002FD50A. The baseline reloads x first and then y. The temporary-product trials change the frame from 0x18 to 0x24, move stack homes and exchange x/y roles, so they are worse. Preload-only temporaries are optimized back to the baseline. No closer body was banked and no new justified experiment remains from this hypothesis.

Raw sources, complete explain/align outputs, patched-byte counts, timestamps, hypotheses and verification receipts are retained under build/findpath-2fd344-worker/. The best replay is baseline.cpp. See identity-wb-retail.log for the complete WB/retail disassembly, baseline.explain.log and baseline.align.log for the remaining mismatch, each trial's .measure.json for exact differing offsets, and handoff-receipt.json for elapsed clock time and check results. Every original bank comment is retained in the bank and trial sources. No background task remains.
