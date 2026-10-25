# Recorder file-handle donor prerequisite

The supported Common planner and Recorder.cpp plan route these three System
donors to the existing Recorder.cpp seed: RecorderClass_writeArgument.cpp,
RecorderClass_readArgument.cpp and RecorderClass_logPlayerDisconnect.cpp.
All three were unheld when their file claims were acquired. The seed claim is
retained while testing the composition prerequisite.

The previous normal merge trial, after the global-view macro repair, accepted
four files and 56 non-alias rows. Each of these three donors still failed with
VC7 C1001 in the composed TU. The donors forward-declared a distinct struct FILE
and spelled the file-handle member m_file10. The destination includes stdio.h
and spells its existing +0x10 member m_file. The checked-in MSVC 7.1 stdio.h
defines FILE as a typedef of struct _iobuf; this is compiler-header evidence,
not a BFME class-layout or recovered-name claim.

Use that same CRT forward declaration and the destination's existing m_file
spelling in this homogeneous batch. The +0x10 access, method signatures, control
flow, imports, compiler flags and receiver storage remain the same. No shared
header, class contract, pin, hatch, source path or protected debt key changes.
The three existing stdio MS-header adoption rows remain open, as does the
seed's separate Xfer adoption row. There are no identity or data-register keys
at these three donor paths to retire or transfer.

Official ./build.sh passes all four existing rows before and after: writeArgument
0x0037AF05 (131 bytes), readArgument 0x0037AF88 (446), logPlayerDisconnect
0x0037B287 (159), and its parent-bound EH row 0x0077ECA6 (10). All 15 named import
references and declared-unmatched checks pass. These 746 bytes were already
matched; this trial recovers no additional C++ bytes.

Scratch receipts: build/codex-recorder-file-donors-{before,after,dryrun}.txt.
The normal composition trial determines whether this removes a prerequisite;
standalone byte agreement alone does not establish merge compatibility.

The completed normal merge dry run accepts all three repaired donors together
with the previously accepted four-file composition, including the seed: seven files,
60 non-alias rows, up from four files and 56 rows. Their C1001 refusals are
cleared. No merge is applied: Xfer adoption still appears in adopt_first, and
the other donors retain their declaration, layout, STL or compiler failures.
In particular, the untouched Rva0037B7C7, Rva0037B3D1 and Rva0037B3F7 donors
still report C1001; the result does not clear those separate files. The three
mixed and three protected-register files remain behind. Leave the now-compatible
donors and the separate Xfer acceptance prerequisite for their normal lanes.

The path-consumer audit against fetched origin/master d7fa8a31bf finds no
outgoing source moves, renames or deletions, including this batch. Active tools,
hooks, workflows, includes, build inputs and registries need no path transfer.
The existing MS-header and Xfer queue owners remain at their original paths.

Recovery verification, next Sol session: the clean inherited commit was rebased
onto current master without source changes. `./build.sh` on the three donors
again passes 4/4 matched rows and all 15 named imports; the three-file
`find_declared_unmatched.py` check passes. `check_csv.py` passes 98,252 rows.
The outgoing range against origin/master contains only these three in-place
source edits and this handoff; no paths move, so no active path consumer needs
repointing. Preserve the three file claims until publication is confirmed.
