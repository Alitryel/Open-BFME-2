# INI array-allocation failure cleanup, 2026-10-23

Target: Unwind@00ba70a0, RVA 0x007A70A0, 11 bytes. Parent:
IndexClass<int, INISection*>::Increase_Table_Size, RVA 0x00616190, 208 bytes.

The parent's retail EH graph independently binds compiler label $L13390 in
this build to the complete cleanup. It frees the raw allocation if an element
constructor throws: MOV EAX,[EBP+4]; PUSH EAX; CALL scalar operator delete at
0x2FD60; POP ECX; RET. This is independent of queueSupplyTruck.

## Cause and repair

ini.cpp previously supplied inline global operator new[] / delete[] forwarding
to scalar operators. Hot paths inline those forwards and therefore matched,
but MSVC's cold allocation-failure action retained the array-delete name and
emitted an eight-byte tail jump. Forceinline on that function was already
refuted by an earlier handoff.

Isolated header-free VC7.1 probes show that scalar-only allocation declarations
allow array-new expressions but select scalar allocation-failure cleanup.
Array overload visibility changes the cleanup selection. Removing just the
array-delete definition gives the desired call/pop shape but still leaves an
array-delete relocation in the real TU. Moving its definition to the end
restores the incorrect tail jump. RAII/manual-placement alternatives introduce
different EH actions and are not used.

The repair gives this TU the legacy scalar allocator interface before always.h:
stddef.h, the existing _OPERATOR_NEW_DEFINED_ header guard, and ordinary scalar
operator new/delete declarations. The existing array-placement overloads remain.
The teardown header is included explicitly at that point rather than forced
before it; both normal-array forwarding definitions are removed. No header,
allocator implementation, compiler executable or global verifier rule changes.
This establishes a working reconstruction context, not the original header text.

The array elements have trivial destructors and the retail allocation/free
calls already prove scalar allocation/deallocation for this TU. Existing object
layouts and allocation sizes stay unchanged. Other translation units are unaffected.

## Validation

- Normal source gate: all 141 prior rows remain exact, followed by 142/142 after
  adding the cleanup; strings (52 literals + 6 empty refs), floats (2) and named
  imports (48) pass.
- Parent EH graph EXACT; eh_verify reports 18/18 exact EH-bearing rows for this TU.
- add_match verifies the complete 11-byte funclet with the actual scalar-delete
  relocation, without new pins, aliases, inline assembly or generated code.
- eh_verify --write-baseline removes only this parent's resolved debt entry.
- Numeric labels of 19 existing funclets changed; the normal verifier follows
  their exact parent EH graphs and verifies their original addresses.

## Remaining handler dependency

Image.frame_funcinfo(0x4F37B0) returns handler RVA 0x792E4C and FuncInfo RVA
0x9457DC. The remaining handler belongs to the currently banked queueSupplyTruck,
claimed by another worker. Its owner must land before admission from the real
parent object. Its temporary claim here was released; no duplicate implementation
or reconstruction of that parent's work was attempted.
