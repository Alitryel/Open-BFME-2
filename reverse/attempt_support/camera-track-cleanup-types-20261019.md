# Camera-track constructor cleanup types

Whole Rva00540B03Ctors.cpp has three69B constructors at540B03/542225/5422CF.
All used vector<BfmeE16> despite reset/read consumers proving different
record strides40/28/20. The external specialization declaration also bound
their exception cleanup to the globally rowed63B vector<BfmeE16> destructor
at52D1CD, while native cleanup jumps to14B conditional-free body7FAB3.

Use the existing element spellings Rva0054000B, Rva00541021, Rva0054103E
from the corresponding reset providers. Their native record strides and
trivial destruction are independently evidenced; original application type
names remain unknown. The separately rowed16B listener-head lifetime remains
external with only its extent represented here.

Evidence and checks:
- Whole reset/locator sources Rva0054034ALocate, Rva00542067 and
  Rva00542148Reset read. Their loops prove40/28/20 bytes respectively.
- Official build: all4 existing rows byte-exact; five complete STL constructor
  folds verified by the build tool, no pins added.
- All3 parent exception graphs EXACT.
- Each of the three newly emitted typed vector destructors is whole14B exact
  at7FAB3, including its resolved free call. The listener-head destructor's
  existing whole14B row at7FAB3 also verified.
- Unit remains link-clean with205 unique bytes in the same census.
- Shared handler797E54 is installed by parents542225 and5422CF and names
  FuncInfo94BFC0. Its two cleanups797E41/797E49 call the proven14B lifetimes.
  Earlier parent540B03 uses handler797DAF and cleanups797D9C/797DA4.

This fixes the actual cleanup type before admitting further generated bodies.

The emitted vector-base constructors were also compared as whole29B bodies
at211E58, including their allocator-proxy relocations: all three exact and
fully resolved. Their native folded owner rows and the three14B destructor
rows were admitted by add_match with the existing ICF owners. No symbols.csv
pin or alias pragma was added. This removes the two new shadow identity
findings that appeared before the constructor fold rows existed.
Paired link prediction remains clean for the constructor and all four
reset/read providers (1482 bytes at the same census).
