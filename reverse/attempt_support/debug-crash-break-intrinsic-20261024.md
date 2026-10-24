# Debug::CrashDone breakpoint intrinsic, 2026-10-24

Target: `?CrashDone@Debug@@UAE_NH@Z`, RVA `0x0003AED0`, complete
ledger extent 1,132 bytes, including the switch table. Identity, class layout,
imports and control flow are the existing recovered body's established facts.

The whole file contained one inline-assembly statement: `int 3` in the dialog's
retry case. Replace it with the compiler's actual `__debugbreak()` intrinsic.
The shipped VC7.1 `crtdbg.h` uses this intrinsic for `_CrtDbgBreak`; it is a
compiler operation, not a newly linked helper. No flags, types, layouts,
visibility, input restrictions, pins or data definitions change.

Native compiler trial: complete emitted extent 1,132 bytes; byte comparison
identical, switch-table extent check empty, unresolved references empty, no
masks. The diagnostic harness properly retained `landing_verified=false`
because DIR32 operands require the ordinary checks.

Normal whole-file gate passed 1/1 bodies, 14 string literals plus two empty
string references, and 19 named imports, with no skipped references. The normal
published-index link preview against census `7e43384268` reports LINKS and
1,131 -> 1,131 linked bytes (the published metric's existing extent); this is
not a new linked-byte claim. Normal hooks remain required on integration.

This removes assembly from an already-counted C++ source body, so coverage
classification delta is zero. The conversion replaces the whole 1,132-byte
body's remaining assembly use with genuine C++ compiler semantics.

Private diagnostics: `build/inline-family/crash-intrinsic.json` and
`build/inline-family/crash-link.log`; successful source is the tracked unit.
