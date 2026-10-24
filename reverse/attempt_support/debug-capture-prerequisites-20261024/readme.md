# Debug caller-capture and FPU compiler prerequisites, 2026-10-24

No production source change or recovered byte is claimed here. Existing exact
assembly-backed implementations and all stronger earlier banks remain intact.
Trial source revision: master5c7cb7f78b plus this worker's independent debug
breakpoint repairs. Stock pinned VC7.1 profile and current region policy used.

## Caller capture

Whole DebugHeapAbort.cpp target is __heap_abort at0x398A0,80B. Fourteen fresh
controls compare the genuine _ReturnAddress and _AddressOfReturnAddress
intrinsics under unchanged flags and /Og-, /Ob0, /Oi, /Oy-/Og-/Ob0, /Ow, /Oa.
No volatile, unused home slot, emitter, ABI change or pin was introduced.
The first intrinsic emits71B; the address-read form73B. /Og- emits113B;
other controls preserve those respective sizes. First difference is+3,
where native reserves its single capture home slot before reading the caller.
Ordinary C++ eliminates the nonescaping slot and its reloads. The public
optimizer controls did not reproduce native materialization and scheduling.
The diagnostic complete71B source is banked as heap-return-address.cpp.txt;
it is not a claimed partial or a replacement for any earlier better bank.

The related Debug_recordCallsite.cpp owns two existing33B names at0x38790.
Replacing both assembly captures with either genuine intrinsic is refused
with C4716: the existing bool Debug::SkipNext has no C++ return statement.
Opaque assembly had suppressed that diagnostic. The native body forwards
through vtable+0x5C and leaves the callee's EAX result untouched. A correct
return-value contract and owner/virtual prototype evidence are required;
no guessed return, warning suppression or ABI/name alias was added. The
unchanged owner whole-file gate still passes2/2.

## Floating-point exception clear

Whole DebugExceptionFilter.cpp was examined for its1255B ExceptionFilter at
0x3DCD0 and957B unchanged dialog sibling. A genuine _clearfp CRT operation plus
__debugbreak was tested as a full-file candidate. VC7.1 reports C4163:
_clearfp is not available as an intrinsic, then emits an unresolved __clearfp
call; first mismatch+774, emitted1254B. This does not reproduce native FNCLEX.
No helper pin or ignored warning can turn a CRT call into the native operation.
The x87 clear remains a concrete compiler-lowering prerequisite. Source was
restored exactly; no nonmatching reconstruction remains under Code/.

Private diagnostics: build/caller-capture/results.json and recorder-results.json,
build/inline-family/filter-clearfp.json and its referenced compiler log.
