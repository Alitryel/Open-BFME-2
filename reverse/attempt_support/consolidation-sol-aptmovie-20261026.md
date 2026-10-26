# AptMovie declaration prerequisite, 2026-10-26 (codexb)

The runner allocation's `--check-tu Code/Libraries/Source/Apt/AptMovie.cpp`
returned zero. The Apt parent naming planner's original-path evidence,
alternatives and prerequisites were reviewed; current routing approves the
two clean sources. No merge, split or ledger move was applied.

## Demonstrated unblock

The ordinary merge dry-run initially rejected Rva0070EDC0.cpp with C2039:
the seed's AptNativeHash declaration lacked DestroyGCPointers. The donor
already declares and calls that same method. Adding its existing signature
to the seed makes the dry-run accept both sources and all six rows, including
the cleanup EH row. The donor's 584 existing retail bytes are preserved,
not recovered bytes. AptMovieFrameControls.cpp remains mixed and untouched;
Luna can perform the now-compatible clean merge through tu_skeleton.py.
This is a demonstrated dry-run unblock, not a confirmed downstream landing.

## Verification and provider bindings

Before and after `./build.sh Code/Libraries/Source/Apt/AptMovie.cpp
Code/Libraries/Source/Apt/Rva0070EDC0.cpp` pass 6/6 rows, 22 strings and two
funclet locations. Both sources pass find_declared_unmatched.py. The seed's
/MD /EHsc context and the donor's existing explicit compiler flags are kept.
The ordinary composition also passes all six rows.

The two original objects were copied and indexed with source/object SHA256
in build/sol-aptmovie-before-20261026.json. The complete standalone and
composed external code/data provider sets were compared using allowed_symbols
objects and the census COMDAT-selection reader: exact bodies, relocation
targets, section flags, COMDAT selections and undefined references, with no
missing, added or changed provider and no reference change. There are no
pre-existing multiple-body provider variants in this scope. Local switch
labels are compared by their containing external provider and exact byte
offset, proving the same eight-entry switch targets despite label renumbering.
EH-handler spelling is normalized only to the verified parent; its EH graph
is EXACT, with funclets at 0x007AAF7F and 0x007AAF70. No native table changed.
The comparison script and receipts are build/sol-aptmovie-*20261026*.

No relevant identity, data, header or Microsoft-header register keys belong
to the two sources. No register key is retired or transferred. Scoped current
object preparation, staged identity/data checks and the normal commit hooks
provide the additional acceptance receipts; byte verification alone is not
the provider-selection evidence above.

## Pending-batch audit and handoff

This source edit adds one declaration and changes no path or include. The
complete pending batch comprises the NetCommandList recovery, Line3D compiler
context prerequisite and this change. The only new source headers are the two
NetCommandList views and Line3DCompileView.h. Active tools, hooks, workflows,
includes, build inputs and registries were audited for those paths and their
consumers. Their references resolve locally; historical EA paths and current
TU-map/census source names remain valid. No source ownership moves or TU map
regeneration occurred. The batch audit needs renewal if later paths or
consumers change. No maintainer-only link, smoke or nightly job was run.

Measured result: one clean donor and six total rows accepted by dry-run;
zero files removed, zero identity keys retired and zero recovered C++ or
linked bytes claimed. Retain the two source file claims and this handoff's
claim until publication is confirmed, then release them. Other pending claims
and remaining NetCommandList/Line3D blockers are in their respective handoffs;
cross-owner LocalFileSystem and DIKeyboard prerequisites are recorded in the
DisconnectManager survey rather than repaired outside this seat's scope.
