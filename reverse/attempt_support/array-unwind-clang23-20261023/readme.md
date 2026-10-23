# ArrayUnwind: callback ABI expressed, SEH lowering still differs

Target: `?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z`, native RVA `006290B2`,
whole 94-byte `ehvecdtr.obj` body. The original archive owner remains in the
ledger; no production source, pin, alias or byte claim changed.

Previous attempts established that VC7.1 rejects the ordinary free
`__thiscall` callback type, or silently makes it cdecl after C4234 suppression.
This trial tests a new prerequisite: the pinned, unmodified `clang23-x86`
profile landed with the security-cookie conversion.

Clang accepts `void (__thiscall *)(void *)`, emits the exact native decorated
ArrayUnwind name, and the separate 11-byte ABI control loads the object into
ECX, calls the callback without pushing an argument, and returns with RET 8.
This is a real callback ABI result; the older cdecl objection does not apply
to this compiler.

The substantive body is not exact. Clang emits a 129-byte parent plus a
separate 52-byte filter. Native's whole 94-byte extent includes its filter and
landing pad. Native begins with two pushes and a call to `__SEH_prolog`, and
leaves through `__SEH_epilog`. Clang instead constructs and restores the FS:0
registration inline, uses a different frame and loop-variable allocation,
and outlines its filter. The native SEH scaffold is therefore a concrete
remaining backend prerequisite, independent of the now-correct callback type.

An explicit MSVC 13.10 compatibility control produces the identical 129-byte
parent and identical relocations. The compiler's own backend option inventory
offers no SEH-specific old-prologue selection; generic outlining controls do
not establish support for the native CRT helper protocol. No explicit
stack-frame manipulation, raw bytes or synthesized helper calls were tried.

The source is preserved in `candidate.cpp.txt`; it includes the clearly marked
scratch ABI control, which has no retail claim. `disassembly.txt` contains the
complete candidate/control/native disassemblies and relocation identities.
`inputs.json` records source, object, compiler and input revisions. Private
objects were emitted only under ignored `build/`, using `compiler_command`;
`build.compile_source` and shared `build/match` objects were not used.

This is a blocked handoff, not a close byte match or a coverage increase.
BFME 1 ranked/near returned zero; its named lift lane was run at f5140c1c.
The ZH cache check reported 919 current objects and 68 independently failing
reference TUs; refreshed match/packets produced no free packet. These queue
results do not exhaust every possible clean reference-source transfer.
