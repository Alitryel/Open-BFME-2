# map<int,AsciiString>: the 0x50xxxx family is a different map (link blocker)

Link-repair handoff, 2026-10-24, census 11b3872700.

PeerDefs.cpp (7,256 B) and UserPreferences.cpp (3,108 B) do not link because a
second STL map family carries the real `map<int,AsciiString>` mangled names.

Target evidence (retail):
- 0x383BAC `_M_insert` (pinned, real AsciiString) calls 0x3834CD, which
  allocates a 0x18 node (pair<int, 4-byte AsciiString>). 0x3834CD is rowed as the
  placeholder `?Rva003834CDCreate@@YG...pair@$$CBHH...` (stlport_map_int_int_os.cpp);
  its `_Construct` is 0x382BC3, the placeholder `?Rva00382BC3Construct@@...TreeKey00242F5E`.
- 0x50116B, rowed as `_M_create_node<int,AsciiString>`, allocates a 0x2C node.
  Its `_Construct` 0x500CFE calls 0x500839 (`pair<const int,Rva0050055D>` copy,
  StlSweepW4Rva00500839.cpp), which calls 0x50055D (`Rva0050055D` copy ctor, 24 B
  value). The family is therefore `map<int,Rva0050055D>` (allocator unverified;
  its `_Rb_tree_base` ctor is 0x417B55, not the 0x1F0534 that real 0x3B1EBB calls).
- The copy ctor name is both rowed at 0x52D25D (fake) and pinned at 0x3B1EBB
  (real, called by getIgnores 0x3B224D), so getIgnores is "not retail's".

Rows and pins that name the fake family with `pair<const int,AsciiString>`:
rows 0x500CFE, 0x50116B, 0x5014FF, 0x501587, 0x501BD8, 0x5041D8, 0x50427F,
0x504496, 0x504591, 0x52D25D (+ __ehhandler 0x797228); pins 0x500839 (1598),
0x500CFE (19), 0x5041D8 (6572), 0x50427F (6584), 0x417B55 (1360), probably
0x4FF471 (14166). The units are stlport_rb_tree_copy_0052D25D.cpp (private 24-byte
`class AsciiString`), stlport_map_int_asciistring_clone.cpp, the three
stlport_rb_tree_int_asciistring_insert*_005014FF/00501587/00501BD8 units,
WOLBuddyOverlay.cpp (0x50427F, 0x504496) and Rva00566695Assign.cpp.

Fix outline (one class-scope rename, docs/naming.md rules apply):
1. Respell the fake family's value type AsciiString -> Rva0050055D in rows, pins
   and units, with tombstones; the fake units currently link (951 B) and must
   keep linking.
2. Give 0x3834CD and 0x382BC3 the real `_M_create_node`/`_Construct`
   `<pair<const int,AsciiString>>` names, so the PeerDefs/UserPreferences
   `_M_insert` copies prove against 0x383BAC.
3. Remaining per-unit blockers after that: PeerDefs' `??A map<int,AsciiString>`
   copy calls `??1AsciiString` (row 0x48BA39) where retail 0x385C19 calls
   releaseBuffer 0x36410 (PeerDefs is built with /DBFME_ASCII_DTOR_DECL);
   `??1 pair<const int,AsciiString>` (no address) differs between
   WOLBuddyOverlay/PeerDefs (calls ??1AsciiString) and UserPreferences/
   Rva00566695Assign (calls releaseBuffer).
