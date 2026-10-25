# MetaEvent deleting-helper prerequisite

The mechanical-seat handoffs recorded missing MetaMap member declarations.
The current plan already includes the earlier record/initializer donors in
the seed. A fresh normal dry run still rejected Rva001DB66ADelete.cpp with
C2039 for rva001DB66A and accepted neither clean donor.

The seed now derives MetaMap from the registered canonical SubsystemInterface
header and declares the existing virtual destructor and deleting-helper API.
This replaces the seed's opaque 12-byte prefix with the established base,
preserving the record-list pointer at +0x0C. Target evidence is already
recorded in Common/MetaMap.cpp: constructor 0x001DB3E8, destructor 0x001DB60F,
vtable RVA 0x007DBA7C and chain to SubsystemInterface::~SubsystemInterface.
No new private base copy, invented member identity or inferred donor layout
is introduced.

Verification on 2026-10-25:

- Regenerated the scoped consolidation planner and passed its snapshot check;
  reviewed original-path evidence and the current approved skeleton plan.
- Both sources pass find_declared_unmatched.py before and after the repair.
- ./build.sh verifies the seed's three code rows and data row, and the
  unchanged helper's one code row; string, float and import checks pass.
- Normal merge dry run now accepts both clean sources, four matched rows,
  with no rejection. Separate scratch Verifier confirms all four rows.
- check_csv.py and git diff --check pass. Local reports are
  build/metamap-prerequisite-{before,after,plan}.txt.

Leave the helper for Luna's mechanical merge. No files moved or removed, no
bytes recovered, and no debt retired. Four mixed sources and the two
protected parser/lookup donors remain outside this repair. Existing header
and data register entries remain intact.

Publication audit covers origin/master..HEAD (pending GameWindowGlobal
prerequisite) plus this staged change. Neither change moves an existing
source path. The canonical header already exists at its registered path;
the seed uses a relative include consistent with its existing library
includes. No active tool, hook, workflow, build input or registry needs
repointing. Historical paths and protected registers are unchanged. Retain
the seed and helper file claims until publication is confirmed.
