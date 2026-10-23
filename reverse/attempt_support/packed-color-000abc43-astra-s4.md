# Packed-word expansion at 0x000ABC43

Input: BFME2 e3f343867c (parent 7aae99cc67); pinned BFME1
138757e9b74645fbcbb7724a7af2764e34931e11; repository MSVC 7.1 with
/O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c-.

Target evidence establishes a complete 46-byte cdecl function from PUSH EBX
at 0xABC43 through RET at 0xABC70. It reads a 16-bit second stack argument
and stores a dword through the first. EBX and EDI are preserved. An
executable-section E8/E9 target scan finds no direct references. The
address-derived name records the behavior, not an original identity.

The compiler blocker is specifically the register-only high-byte shift and
low-word splice: SHL BH,3 followed by MOV AX,BX. Prior scalar narrowing/mask
trials produced 53–63 bytes; five union byte/word variants under O1/O2,
G6/G7 and Ob0 produced 59–74 bytes with stack spills. Those trials are
documented in parallel_recovery_20261022.md section 10 and the attempt log.
The new experiment uses ordinary typed C++ parameters and one mnemonic
inline-assembly core. The compiler supplies both saved registers, their
restores, stack-relative parameter references and RET. The emitted body is
exactly 46 bytes; no naked declaration, byte emission, pin, data alias, gate
change or existing C++ replacement is involved. This is an assembly
codegen-blocker recovery, not a claim of pure C++ implementation.

The independent arithmetic model is:

    spread = ((value & 31) << 3)
           | (((value >> 5) & 31) << 11)
           | ((value >> 10) << 19);
    output = spread + ((spread >> 5) & 0x003f3f3f);

Unicorn execution of the retail body passed this model for all 65,536
unsigned-word inputs, and checked unchanged EBX/EDI plus cdecl stack
balance on each call. In particular, bit 15 is preserved and participates
in replication; no RGB555-only input precondition was invented.

The s1 donor checkout was empty apart from its .git file during this pass,
so its files could not be used. Read-only searches of the seat's pinned
BFME1 WWVegas/GameEngineDevice sources and their Zero Hour references
found no corresponding instruction sequence, constant or 555-to-888
routine. TileData.cpp corroborates the neighboring tile subsystem only;
it does not establish this helper's original identity or implementation.

Diagnostic source is under build/astra-s4-color. The tracked production
source preserves the complete candidate. Normal add_match passed the full
46 bytes; commit gates remain required.
