# STL placement-copy owner family

Twenty-seven native 45-byte copy helpers previously borrowed existing STLport
template symbols through synthetic object aliases. Each now has a real C++
definition performing the same existing reference copy operation, using the
target's proven cdecl two-pointer ABI. Original application types and signature
spelling remain unknown. Internal STL types are inherited reference/structural
evidence, not newly recovered target names or layouts.

All27 complete bodies and full native EH graphs verified EXACT in isolated
trials with the owner's effective compiler settings. Both quoted headers were
resolved from the original source and hashed; the tracked source retains its
original portable includes. The existing classes, layouts and flags are unchanged.
Sixteen caller units make18 direct calls to the actual owners. Reference inputs
pass their address; pointer inputs preserve their pointer value. Obsolete casts
and unused local callback typedefs are removed. All80 existing rows across17
units passed normal byte verification with strict current receipts.

Twenty existing cleanup rows are rebound by their actual complete parent EH
graphs, never adjacency. Existing genuine template bodies and already-owned
handlers remain. The new16 handlers have unique names/ranges; native parent
relocations and exact full EH graphs establish each handler/FuncInfo association.
Each whole10B handler loads its own FuncInfo and jumps to CxxFrameHandler629182.
All code and relocations match in strict current objects. No new pin, object
alias, header, layout, assembly, scaffold or verifier exception is introduced.

| Parent RVA | Handler RVA | FuncInfo RVA |
| --- | --- | --- |
| 0x001D9B0F | 0x0076968E | 0x0090E658 |
| 0x0020D5E6 | 0x0076D367 | 0x00912D44 |
| 0x0020F321 | 0x0076D560 | 0x00912FDC |
| 0x00211F6D | 0x0076DA08 | 0x009135BC |
| 0x0022112D | 0x0076EF87 | 0x009150B4 |
| 0x002FE87D | 0x00779124 | 0x009214B4 |
| 0x00317CA0 | 0x0077A70D | 0x009232B4 |
| 0x0031BDC1 | 0x0077ABE6 | 0x009238CC |
| 0x0035CA02 | 0x0077DD06 | 0x009279A8 |
| 0x003EEFDB | 0x007838A4 | 0x0092F898 |
| 0x0041FA07 | 0x00786E08 | 0x009340DC |
| 0x0049DD0B | 0x0078D8C1 | 0x0093DA64 |
| 0x004C3A9F | 0x0078FF62 | 0x00941448 |
| 0x0052B6AC | 0x00797084 | 0x0094ADE8 |
| 0x00460F18 | 0x0078A841 | 0x00939268 |
| 0x00511CB9 | 0x00794CF8 | 0x0094807C |

Removed hatch occurrences: 11 alternatename, 41 object_symbol, 14 pin.
52 existing register entries shrink or disappear; absent entries are never added.
Result:160 newly covered retail bytes. No full-link/census gain is claimed.
