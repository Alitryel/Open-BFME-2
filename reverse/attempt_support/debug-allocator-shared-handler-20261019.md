# Shared debug-allocator allocation handler

The whole owner is Code/GameEngine/Source/Common/Rva006C4300Malloc.cpp. Its three allocation workers at 0x006C40C0 (369 bytes), 0x006C4300 (348 bytes) and 0x006C4530 (319 bytes) pass normal byte and complete EH verification. Existing source evidence describes the debug-record sizing, allocation retry and scoped counted-lock lifetime; address-derived type and method spellings are retained.

The first two native prologues install handler 0x007A7D1B and FuncInfo 0x0096170C. Their sole unwind action is the already owned 11-byte cleanup at 0x007A7D10: LEA ECX,[EBP-140] followed by JMP to the existing 0x000317C0 lock-release body. Both compiled parent graphs reproduce all bytes and relocations. The third worker uses a distinct already owned handler at 0x007A7D3B and is not conflated with them.

The shared handler is exactly 10 bytes, 0x007A7D1B..0x007A7D25, followed by INT3 padding: MOV EAX,0x00D6170C then JMP to the CxxFrameHandler thunk at 0x00629182. Both emitted handlers are 10 bytes with DIR32 at offset 1 to their FuncInfo and REL32 at offset 6 to ___CxxFrameHandler. The ledger adds only the 0x006C40C0 parent's emitted handler as the single owner. No alias or pin is added, and no source/generated file is changed.

Whole-file placement search found no further free bodies. The published 10:38 census reports unresolved allocator providers and a competing lock-guard destructor; the two allocation/free targets 0x00033ED0 and 0x00033150 still have only pins, while the metrics provider 0x006C26F0 has since been rowed. The handler's exact proof is not a claim that the complete unit links. Raw parent graphs and handler disassembly are in ignored build/next-batch-oct19d/allocator-proof.txt. Model: gpt-6.1-sol.
