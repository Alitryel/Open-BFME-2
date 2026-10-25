# W3DView.exe vs game.dat

Question: could W3DView.exe from the BFME2 Mod SDK be a secondary target, and is it
built from the same source tree as game.dat 1.06?

Short answer: yes. Most of its code is game.dat code we have already matched.

## The binary

- From `BFME2_ModSDKv2.exe` (SDK v1.01). The SHA-1 matches EA's original in the Wayback Machine.
- `W3DView.exe`: 3,526,656 bytes, built 2006-06-06, PDB `D:\Projects\BfME2\Run\W3DView.pdb`.
- game.dat 1.06 was built 2006-09-25, so W3DView is about 3.5 months older.
- Release build (MSVCR71/MFC71), no RTTI, no relocations, incrementally linked.

## Result

Shares of W3DView's 1.81 MB of code (int3 padding excluded):

| Part | Share |
|---|---|
| Identical to matched game.dat code | 61% |
| Changed version of a game.dat function | 4% |
| Engine code not found in game.dat | 13% |
| Library code reached only through pointers | 11% |
| Viewer UI (MFC, Win32) | 5.5% |
| Too small to classify | 5.5% |

Other numbers:

- 85% of game.dat's matched WWVegas functions appear byte-identical in W3DView: WW3D2 92%, WWMath 85%.
- Even 16 KB functions match 1:1, so it is the same source with the same compiler flags.
- Changes between June and September show up mostly in particles, shaders and device setup.

## What it means

- About 60% would transfer for free.
- The new work is the viewer UI, about 100–200 KB, plus fixing up the changed engine code.
- The Zero Hour source release has no W3DView source to use as a donor; Renegade's was not checked.
- `Max2w3d.dle` from the same SDK has relocations and a donor (`Tools/WW3D/max2w3d`).
- `AssetCacheBuilder.exe` is small and comes from an older branch, so it is not worth it.

## Folded functions (ICF)

W3DView was linked incrementally, so the linker did not fold identical functions.
game.dat did.

- game.dat has 6,268 addresses with two or more names (ledger rows plus pins).
- W3DView has two or more separate copies of the body for 1,493 of them.
- For 1,153 of those, at least two copies are each called from code identical to game.dat.
- Conservative count (2–5 copies, bodies of 32 B or more): 392 groups with 1,218 names.

Use: a shared caller calls one specific copy in W3DView. The caller's matched source
says which name it calls, so this can show which names really belong to a folded body.
That last step (reading the names from the caller's relocations) has not been done.

## Dead code

- W3DView keeps about 320 KB of unreferenced functions.
- game.dat also keeps about 500 KB of unreferenced code: no call or pointer refers to it,
  probably from units not built as separate COMDATs.
- The `absent-from-retail` markers in WWVegas are mostly helpers that force template
  instantiation, so W3DView cannot be used to check them.
- About 90 KB of W3DView's unreferenced code is not in game.dat: leads for source
  functions the game never linked.

## WorldBuilder for comparison

- `worldbuilder.exe` is a debug build. It matches only 6% of game.dat's matched WWVegas
  bytes (3% for bodies of 64 B or more), against 81% for W3DView.
- WorldBuilder stays useful for names (its asserts); W3DView is the better source for bytes.

## How it was measured

- Function bodies were compared with relocations masked (call targets and in-image addresses).
- Function boundaries came from Ghidra plus a simple disassembly pass.
- Engine and viewer code were told apart by the call graph: engine code never calls viewer code.
- The engine/viewer split is approximate, and nothing was compiled.
