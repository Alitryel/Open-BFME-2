# Fire watcher semantic repair at 0x00287552

Result: partial under the assignment's semantic-repair exception. The farm bank omitted the persistent box rowY update and instead made a volatile update to the discarded inner-loop sy. The repaired bank advances rowY, restores Cos(angle) from the cached angle, copies position components in retail order and removes the source-only compiler barrier. Every existing comment is preserved. No reconstruction was placed in Code/, and no ledger match or pin was added.

Symbol: `?rva00287552@FireLogicSystem@@QAEXPAURva00287C21Other@@H@Z`. Extent: [0x00287552, 0x00287B2A), 1496 bytes. Destination: `Code/GameEngine/Source/GameLogic/Map/FireLogicSystemObjects.cpp` (destination tool's neighbour heuristic, not an approved TU proof). The current bank is `reverse/attempts/0x00287552.cpp`.

## Retail evidence

The preceding function returns at 0x28754F; this body starts at 0x287552, returns with ret 8 at 0x287B27 and abuts the next body's prologue at 0x287B2A. The inventory independently gives the same start and extent. The incoming receiver is ECX, the object is the first stack argument, and only the low byte of the second argument controls add/remove. The matched RegisterObject and UnregisterObject twins at 0x287C21 and 0x287C39 call this address with 1 and 0, respectively, according to the sign of object+0x49C. These support the existing class and address-derived method name; no recovered real method name is claimed.

At 0x28791F retail loads rowY from ebp+0x4C, at 0x287929 adds rowStepY, and at 0x287933 stores back to the same home. The next row loads that home at 0x287856. Its inner sy instead occupies ebp+0x3C. This proves the farm update drops a real operation. Retail also caches object+0x44 before the shape loop and uses the cached angle for both trigonometric calls.

Direct callees were checked in retail: the watcher operation is 0x286D4E; template flammability is 0x285F43; geometry indexing at 0x6BD980 uses 36-byte elements and returns a pointer; the transform at 0x6BD390 takes point and angle with ret 8; Cos and Sin at 0x2FBC0 and 0x2FBB0 are x87 float wrappers. The existing declarations reproduce these calls with no unresolved relocation. No donor source was imported in this attempt. Historical evidence names geometry functions imported from BFME 1; the declaration and accessed offsets here were checked against BFME 2 itself.

## Measurements and remaining blocker

Raw align_diff outputs and patched byte counts are adjacent to this file and are authoritative. The corrected candidate has the same emitted length and instruction count as retail. It is not a strict alignment improvement: the structural count and register count are unchanged, and memory differences increase slightly. Its lower positional byte count is not used as an alignment claim. The correction is banked because the assignment expressly requires replacing semantically wrong farm banks at comparable alignment.

The remaining frame is retail 0x94 versus compiled 0x8C. Circle xMax/yMax reuse the sine and box ceil temporary homes that retail keeps separate. Three pop/fstp store schedules differ: first box ceil at retail +0x27F and both circle floors at +0x427 and +0x463. A shared named ceil result did not repair these schedules and worsened alignment. Copy-order changes and removing the compiler barrier do not close the frame. Earlier documented declaration, geometry visibility, floor overload, swap and conversion-form sweeps were not repeated. No further evidence-backed hypothesis remains in this run.

## Reproduction and inputs

Base checkout: `394012baa68b43c4b3098e57286b4a3375d91837`. The source retains its first `/O1 /arch:SSE /G6 /DNDEBUG /MD /GX /ICode/Libraries/Include /I.` cl line. Tools use the default MSVC 7.1 compiler; BFME_OBJSTORE was off for every build and measurement. Each trial used a fresh object through tools/align_diff.py, never a manual compile into the shared cache. Historical `build/big/fire-watch` evidence is absent in this checkout; every existing verdict and the bank were read before experiments, and no verdict cites a tracked support file for this target.

Scratch and raw outputs remain in `build/w4-fire-287552/`, including original-bank.cpp, h1.cpp, h2.cpp, h3.cpp, best.cpp, retail.log, each align/compiled log, original-bank-explain.log, h2-explain.log, patched-counts.log, checks.jsonl and elapsed.json. `semantic-repair.patch` reconstructs the correction from the original bank. No background process was started and no git write or network operation was performed.
