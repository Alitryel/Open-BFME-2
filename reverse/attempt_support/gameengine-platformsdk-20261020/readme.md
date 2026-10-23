# GameEngine header prerequisites

The ordinary full baseline at parent e6748864e0356d5f3cb1dc22f44666b446581278
stalled while compiling GameEngine.cpp. Its direct windows.h include had no
resolvable Windows header in the source's existing include profile. A two-second
noninvasive sample found all 96 active samples in Wine's exception setup loop.
The coordinator stopped that incomplete full attempt; it earned no full-gate or
reference-freshness receipt.

This repair adds the existing per-source `// platformsdk` opt-in and an explicit
`#include <stdio.h>` for the three existing sprintf calls. Marker alone ended the
compiler loop and reported those missing sprintf declarations in 5.65 seconds.
The former stale object receipt named sweep/windows.h, which transitively supplied
stdio.h. That object does not authenticate the current original source profile and
is diagnostic evidence only. No current paired baseline or linkage gain is claimed.

All executable statements, layouts, imports, compiler arguments, shared headers,
tools, ledger entries, and the pinned BFME1 revision remain unchanged. The existing
driver appends the genuine pinned VS2003 PlatformSDK/Include directory after the
VC include directory, for this source alone.

## Verification

The ordinary scoped build completed in 5.23 seconds with all four existing rows
exact (789 bytes), four string literals, and nine named imports. A separate read
of the resulting COFF compares every complete body and resolved relocation with
retail without masked or unresolved fallbacks. There are no owned EH graphs in
these four rows. The dependency receipt records 74 opened headers, including 64
Platform SDK headers, and every source, object, and dependency hash was checked.
The current read-only link check against the published 18:52 census has no
unresolved, duplicate, COMDAT, address, selected-copy, or unreferenced-copy blockers.

The prior source, stale receipt, effective before/after command and environment,
failed marker-only diagnostic, successful ordinary build, dependency hashes,
exact-body evidence, and current link result are recorded in proof.json. The
source is eligible under the frozen-source gate. This prerequisite repair adds
no recovered bytes, new rows, symbols, or paired-link credit. A coordinated full
baseline remains necessary after all known source prerequisites are repaired.
