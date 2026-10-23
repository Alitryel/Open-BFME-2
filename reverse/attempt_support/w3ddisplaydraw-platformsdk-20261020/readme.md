# W3DDisplayDraw Platform SDK prerequisite

`W3DDisplayDraw.cpp` includes the Windows and multimedia SDK headers but did not
opt in to their existing per-source include profile. On this Mac/Wine toolchain,
the missing header path previously blocked the full baseline compile. This
repair adds only `// platformsdk` beside the existing `// stlport` marker.

The existing build driver appends the pinned toolchain's
`Vc7/PlatformSDK/Include` directory after the STLport and VC include directories
for this source. The compiler arguments, source statements, global configuration,
shared headers, reference pointer, and ledger remain unchanged.

## Fresh validation

At parent `930dcce6263119884147dbe00e342836ff6bcefe`, with the pinned BFME1
checkout synchronized to `4483e88da1c2f3b9a273f779baac7458bd8bb891`, the normal
scoped build passes all three existing rows (1,296 bytes), one nonempty and one
empty string reference, two floating-point literals, and six imports. The
callback, draw function, and EH-handler bodies compare exactly with all resolved
relocations; the complete draw EH graph is EXACT.

The normal compile receipt records 92 opened dependencies, including 64 real
Platform SDK headers and their hashes. `Windows.h` and `MMSystem.h` come from
the pinned toolchain. Every dependency, source, and object hash was rechecked.
`proof.json` records the before/after effective compiler environment and confirms
that appending this SDK directory to INCLUDE is the only environment change.

There was no authenticated current pre-change object available. The earlier
private SDK-only diagnostic remains supporting evidence, not a fresh baseline:
it used a command-line include directory, whereas this repair uses the ordinary
per-source INCLUDE profile. No failing missing-SDK compile was repeated, and
no paired-link improvement is claimed.

A read-only check against the published 18:52 census (`3f413ed3ff`) finds six
unresolved provider names in this source: the application-window handle, three
statistics callbacks, `StatDebugDisplay`, and `W3DDisplay::gatherDebugStats`.
The other linkage categories are empty. This change restores the normal compile
prerequisite; it adds no recovered bytes, rows, symbols, or linkage credit.
The full baseline build and reference freshness check remain separate coordinated
work after this scoped repair.
