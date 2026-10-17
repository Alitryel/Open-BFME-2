# Complete native GUI CRT startup reconstruction

The complete `crtexew.obj` member is replaced by genuine C++ in
`Code/Libraries/Source/CRT/WinMainStartup.cpp`: the private 86-byte
`check_managed_app` helper and 511-byte `WinMainCRTStartup`, including its SEH
filter. Their 597 unique retail bytes move from prebuilt CRT to authored C++.
BFME1 pointer `a0e8f345a9b22b4b42088e402962287d7015e3c2` retains this member in
prebuilt form, so it supplies native identity corroboration, not an authored
donor. No Microsoft CRT implementation source was read.

Retail instructions and native COFF establish the identities, complete boundaries,
call relationships and globals. Public Platform SDK declarations establish PE
header layouts and Win32 ABI. The command-line scan uses unsigned bytes,
quote state and the native DBCS lead-byte call. The two exit-table sentinel stores
preserve the original relocation names and order, not merely equal constants.
The independent proof checks complete raw object bytes and every external
relocation's name, position and type against the native member. It resolves the
compiler-local scope-table label separately and reproduces all 12 retail bytes,
including filter offset `+0x1c6` and handler offset `+0x1da`; ordinary C++ EH
verification reports no EH graph for this SEH form.

Three additional six-byte typed C++ import providers replace generated veneers
for `_XcptFilter`, `_amsg_exit` and `_initterm`. They add no C++-exact coverage
because the generated imports already counted. The native `dllargv.obj`
`_setargv` and `merr.obj` `_matherr` definitions are complete three-byte zero-return
ICF twins at RVA `0x000d43d0`, adding no unique bytes and no pin. Their identities
come from native definitions and the startup's call/callback relocations, not
from instruction shape. Public `math.h` corroborates the math-error callback ABI.

`merr.obj` also owns `__defaultmatherr`, a four-byte integer initialized to one
at RVA `0x009d7f14`. Moving and data-row-verifying the flag with the callback
prevents the original strong archive member being selected and defining a second
callback. A focused link initially exposed this duplicate and passes after the
complete member's ownership is reconciled.

Normal source gates verify all seven functions, the new four-byte data row and
15 named startup imports. Placement scans of both startup units find no further
body or pin. The current census index predates all five new units and cannot
preview them; no new census evidence is claimed. The separate, non-executed
focused DLL forces the previous eleven CRT routines plus these six public
support/startup definitions, using the original CRT archive, Win32 libraries,
source-owned import thunks and scoped IAT-only import entries. Its WinMain is an
explicit test double. This proves bounded symbol closure without duplicate
public definitions; it does not prove full-game placement or runtime behavior.
No full link cycle, census, boot or other maintainer verification runner was run.

`verification.json`, `focused-link.json` and `inputs.json` preserve the results,
source and input hashes and resolved SDK header paths. `check_startup.py` checks
current normal-build objects and retail read-only; its optional sizeof probe
uses the existing data-row tool's isolated probe directory. Run it with the
normal Python dependencies after the ordinary source builds. It writes its
report only under ignored `build/resume-eh-local/`.
