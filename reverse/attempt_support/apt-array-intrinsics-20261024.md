# Apt array debug-trap intrinsic repair

Target: `AptArray::DestroyGCPointers`, RVA `0x006D93D0`, complete extent195B.
Worker baseline: `5c7cb7f78b`; compiler: pinned MSVC7.1 RTM with the existing TU flags.

The existing native assertions call the Apt assert callback and conditionally execute INT3.
Both inline `__asm int 3` statements are replaced by the genuine `__debugbreak()`
compiler intrinsic, declared with the shipped calling convention and `#pragma intrinsic`.
The pinned CRT itself uses this intrinsic for `_CrtDbgBreak()` in `crtdbg.h:391`.
No class layout, callable ABI, memory order, callback, literal, compiler flag or native
body extent was changed. The previous identity and layout evidence remain the ledger's.

The private diagnostic compile matches all195 native bytes with a complete195B emitted
extent, no unresolved references and no extent problems. The ordinary whole-file gate
passes1/1 rows and all4 literal references with no skipped references. Declared-definition
checking passes. Published-index link preview reports LINKS,193->193 linked bytes; this
is the index's measure and is distinct from the195B complete gate extent.

This removes inline assembly from one already-counted `.cpp` body; it adds zero coverage
bytes. No verifier, pin, baseline, ownership or canonical-class exception changed.
