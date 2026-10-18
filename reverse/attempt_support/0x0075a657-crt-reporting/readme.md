# Whole CRT runtime-check reporting member

Twelve native `error.obj` routines (1,450 unique bytes) are reconstructed as real
C++ in `Code/Libraries/Source/CRT/RtcError.cpp`, preserving the original public
and private identities. The original seven-byte FS-segment `GetCurrentTib.asm`
primitive remains ASM-owned and adds no C++ coverage; its private inline copy
is the documented compiler-machinery boundary that supports the real C++ TIB
field access and predicate. There are no naked bodies, byte emits, new pins,
object-symbol overrides or present-unmatched markers. Native private static
visibility and optimized register argument passing are preserved by compiling
the complete file together. Each reporting body is banked separately.

Native COFF symbols, exact retail placement, call relationships and data accesses
establish identity and layout facts. Public SDK/CRT declarations supply ABI.
The TIB is only a prefix view exposing the evidenced pointer at offset 0x20;
no full native TIB extent is claimed. BFME1 at the recorded pointer retains
these bodies prebuilt rather than supplying authored C++. No Microsoft CRT
implementation source was read. VS2003's documented missing FS intrinsic is
already proven in the unchanged ASM primitive's record; only that primitive
needs inline assembly. ReturnAddress uses the compiler's actual intrinsic.

All twelve functions reproduce their entire native raw object code, not just
masked bytes, and every external relocation name, position, kind and addend.
Compiler-local scope labels are resolved as graphs: both full twelve-byte SEH
tables match retail, including filters at body offsets 0x38/0x4a and handlers
at 0x3c/0x4e. Ordinary C++ EH graph verification reports no graph for this form,
so the separate 24-byte scope proof is required. The debugger probe preserves
its partially initialized native six-DWORD payload. The reporting paths retain
original allocation sizes, evaluation order, signed decimal-remainder behavior
and null-name branch order, rather than silently repairing retail behavior.
G6 size optimization, builtin wchar_t, explicit inlining and direct table use
reproduce the native compiler shape without synthetic wrappers.

All 79 bytes of native data are verified: the public 16-byte error-level array,
private 20-byte suppression flags and 20-byte message-pointer array, cached
four-byte debugger function pointer, fifteen-byte decimal buffer and four-byte
initialization guard. Public ownership has a typed data row; private ownership
stays private. The complete 889 literal bytes (619 reached through the message
table and 270 direct) match retail including terminators. The existing RTC
error-type setter and the reporting unit resolve the same named error levels.
Current compilation receipts prove the actual SDK and CRT headers used; hashes
are in `inputs.json` along with the native archive and unchanged ASM primitive.

A non-executed focused DLL forces 26 public C++ routines across the accumulated
CRT/startup/free-adapter units and the existing ASM primitive. Their private
helper graph and data are included naturally. The original CRT archive supplies
remaining helpers, and scoped IAT-only entries supply DLL slots for authored
callable imports. WinMain and the game-free function-pointer slot are explicit
test doubles. The link succeeds without public duplicates and its map selects
the authored RTC entries/error levels and original ASM primitive. This is
bounded symbol closure, not full-game placement, census or runtime proof.
No full link cycle, census, boot or maintainer verification runner was run.

`verification.json` records full raw/native code and relocation checks, data,
literals, scope tables and source hash. `focused-link.json` records the exact
closure scope. After normal source builds, `check_reporting.py` checks current
objects/retail read-only and uses the existing data-row tool's isolated sizeof
probes; its report stays under ignored `build/resume-eh-local/`.
