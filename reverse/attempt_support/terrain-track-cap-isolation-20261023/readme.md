# Terrain-track unmatched cap isolation

At c886350aeb, W3DTerrainTracks.cpp emits a nonmatching Zero Hour
TerrainTracksRenderObjClass::addCapEdgeToTrack body. Its legacy pin names
0x00084271, but the actual 793-byte native body is independently recovered as
Rva00084206Track::addCapEdgeToTrack in W3DTerrainTracksBind.cpp. Both current
model-draw callers already declare and call that address-derived owner.
The donor class layout and application class identity are not newly reconciled.

The unmatched donor body has no caller inside its old unit. Preserve it verbatim
in W3DTerrainTracksCap.cpp.txt, with its include environment and compiler flags,
and remove its competing definition from the matched unit. The diagnostic TU
compiles through place_bodies (read-only, --min 500), yielding no placements or
pins. No matched body, ledger range, pin, data definition or canonical type changes.

Same b711de3634 index (2026-10-23 14:28), current objects:
W3DTerrainTracks.cpp 0/202 -> LINKS 202/202 bytes; its losing/wrong-selected
cap definition disappears. The two unchanged model-draw callers remain
LINKS 725/725 and 145/145. Paired final check: 870 -> 1072 bytes, 3/3 units link.
This is +202 legacy preview linked bytes, zero authored C++ bytes;
closed-strict link closure has not been measured.

Normal byte gate: 7/7 functions and 1/1 data row; string, float and import
checks pass. --prepare-current confirms strict reusable compile receipts.
EH verification: 1/1 EXACT, including the naturally renumbered cleanup label.
Declared-definition check and check_csv pass. No census or link cycle was run.
