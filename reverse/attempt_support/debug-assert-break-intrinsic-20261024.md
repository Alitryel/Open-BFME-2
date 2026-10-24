# Debug::AssertDone breakpoint intrinsic, 2026-10-24

Target: `?AssertDone@Debug@@UAE_NH@Z`, RVA `0x0003A8A0`, complete
948-byte ledger extent including the switch table. The source retains its
existing identity, class layout, globals, import bindings and input domain.

Replace its sole `__asm int 3` with the genuine VC7.1 `__debugbreak()` intrinsic
between recognized `_ReadWriteBarrier()` compiler intrinsics. The shipped
`crtdbg.h` uses `__debugbreak` for `_CrtDbgBreak`. The barriers emit no helper
calls or machine instructions; no byte emitter or register constraint is used.

The old opaque assembly block prevented memory accesses moving across the
breakpoint. A bare intrinsic is insufficient here: VC7.1 sinks the static
'dialog answered' store after INT3 and rearranges shared switch exits. A debugger
or handler must see the native store before the trap. Compiler memory barriers
preserve this existing observation contract on both sides of the breakpoint.
This is the same memory boundary the former opaque assembly provided.

The candidate emits native `mov byte ptr [0xDE089D],1` at RVA `0x3AA84`,
INT3 at `0x3AA8B`, then JMP `0x3AAEE` at `0x3AA8C`. All 948 bytes and
relocations match, including every switch-table destination. Extent problems,
unresolved references and masks are all empty. Compiler diagnostics show only
the unchanged EHc override warning, no unknown-intrinsic warning or helper call.

Normal whole-file verification passed 1/1 bodies, 11 string literals plus two
empty-string references, and 13 named imports with no skipped references.
Published-index link preview at `7e43384268` reports LINKS and 947 -> 947 linked
bytes under that census's existing extent; no linked-byte increase is claimed.
The complete normal hooks remain mandatory on integration.

This removes assembly from an already-counted C++ body; coverage classification
delta is zero. Private diagnostics: `build/inline-family/assert-intrinsic.json`
(refused bare intrinsic), `assert-barrier.json` (exact replacement), and
`assert-link.log`. The successful source remains in its proper tracked unit.
