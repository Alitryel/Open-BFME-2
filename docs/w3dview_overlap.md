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

## How it was measured

- Function bodies were compared with relocations masked (call targets and in-image addresses).
- Function boundaries came from Ghidra plus a simple disassembly pass.
- Engine and viewer code were told apart by the call graph: engine code never calls viewer code.
- The engine/viewer split is approximate, and nothing was compiled.
