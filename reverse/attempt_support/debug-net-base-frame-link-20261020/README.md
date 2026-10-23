# Debug network destructor link repair

Target: `Code/Libraries/Source/WWVegas/WWDebug/DebugIONetPipeDestructorThunk.cpp`.

The retail base scalar deleting destructor `??_GDebugIOInterface@@MAEPAXI@Z`
at RVA 0x0003F340 is the 31-byte frameless body already rowed in
`Rva0088FAA0DebugIOInterfaceDestructor.cpp`. The derived destructor at
0x0003F4F0 requires the frame pointer and its original EH graph. The unit-wide
`/Oy-` made the live base deleting-destructor copy differ from retail.
Compile the base using the default frame-pointer omission, then disable
omission before the derived class. This changes only that base COMDAT; no
COMDAT is added or removed. The scoped pragma is a compiler-shape repair,
not an identity or vtable claim. The existing virtual contract is unchanged.

The donor linking pass was reviewed at BFME1 92f6bbe8e1 (same revision as the
formation-preview handoff). Recent donor repairs concern named callees,
Free_String and duplicate Pathfinder constructors; the frame split is proven
by BFME2's rowed base and derived bodies rather than inferred from the donor.

## Verification

- `./build.sh <source>`: all 4 rows exact, string/float/import checks pass.
- `link_check.py --prepare-current <source>`: strict reusable receipts current.
- `eh_verify.py <source>`: 1/1 EH graph EXACT.
- Data shadow and converged checks: zero findings; class and declared-definition
  checks pass.
- `paired.json`: frozen index 5366c4f808 (2026-10-20 12:21), both before and
  after objects refreshed independently. Before: sole wrong base deleting
  destructor. After: no legacy closure findings. Self-strict object current.
  Legacy predicted linked bytes **0 -> 130** (87-byte derived destructor,
  33-byte deleting destructor, 10-byte EH handler). The 8-byte generated
  unwind row is excluded from authored bytes. No closed-strict gain measured.

The other four debug units with this base scalar conflict also have duplicate
constructors, incomplete virtual contracts or an unresolved DebugIONet
complete destructor. They were not changed: the frame split alone does not
make them link.
