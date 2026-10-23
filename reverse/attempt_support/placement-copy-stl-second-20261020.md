# Second STL placement-copy owner family

Five native 45-byte copy helpers previously borrowed existing STLport
template symbols through synthetic object aliases. Each now has a real C++
definition performing the same existing reference copy operation, using the
target's proven cdecl two-pointer ABI. Original application types and signature
spelling remain unknown. Internal STL types are inherited reference/structural
evidence, not newly recovered target names or layouts.

All5 complete bodies and full native EH graphs verified EXACT in isolated
trials with the owner's effective compiler settings. The quoted header was
resolved from the original source and hashed; the tracked source retains its
original portable includes. The existing classes, layouts and flags are unchanged.
Three caller units make3 direct calls to the actual owners. Reference inputs
pass their address; pointer inputs preserve their pointer value. Obsolete casts
and unused local callback typedefs are removed. All15 existing rows across4
units passed normal byte verification with strict current receipts.

Three existing cleanup rows are rebound by their actual complete parent EH
graphs, never adjacency. Existing genuine template bodies and already-owned
handlers remain. The new2 handlers have unique names/ranges; native parent
relocations and exact full EH graphs establish each handler/FuncInfo association.
Each whole10B handler loads its own FuncInfo and jumps to CxxFrameHandler629182.
All code and relocations match in strict current objects. No new pin, object
alias, header, layout, assembly, scaffold or verifier exception is introduced.

| Parent RVA | Handler RVA | FuncInfo RVA |
| --- | --- | --- |
| 0x002BF35B | 0x00776A17 | 0x0091E348 |
| 0x00358CA0 | 0x0077D872 | 0x00927444 |

Removed hatch occurrences: 3 alternatename, 6 object_symbol, 2 pin.
10 existing register entries shrink or disappear; absent entries are never added.
Result:20 newly covered retail bytes. No full-link/census gain is claimed.

The pre-existing Rva0056644EElement compatibility alias is unchanged. Rva0052C404Construct now has a real definition; its former linker alias is removed and its existing same-address pin remains unchanged.
