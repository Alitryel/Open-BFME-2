# Apt checked-cast intrinsic family

The19 existing checked casts comprise18 complete50B bodies and one57B body (957B total).
Their predicates, assertion literals/callers, address-derived method names, flags and
native thiscall ABI remain unchanged. No new identity or layout claim is introduced.

Bare genuine MSVC7.1 __debugbreak reproduces the prior54-vs-50B mismatch for isKey:
MOV EAX,ESI is scheduled before the branch and the shared return is duplicated.
The native opaque INT3 is a debugger observation/resume boundary. Pairing the genuine
_ReadWriteBarrier intrinsic before and after the genuine __debugbreak preserves that
memory boundary without emitting assembly or changing the callback/control-flow contract.
The pinned CRT uses __debugbreak for _CrtDbgBreak (crtdbg.h:391); both intrinsics are
compiler-recognized declarations, not replacement stubs or raw opcode injection.

Each body is independently byte/extent/relocation compared in the private harness, then
banked as its own commit only after the ordinary whole-file gate passes19/19 rows and
38 literal references. All same-file siblings are rechecked after each source edit.
Published-index link previews remain LINKS938->938 linked bytes; this is distinct from
the957B full gate extent. No verifier, baseline, symbol pin, ABI, input restriction,
volatile object, register constraint or compiler flag is changed. These are repairs
of inline assembly in already-counted C++ files and add zero aggregate coverage bytes.

Verified native bodies, each banked separately:
- `rva006DD020` at `0x006DD020`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD060` at `0x006DD060`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD0A0` at `0x006DD0A0`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD0E0` at `0x006DD0E0`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD120` at `0x006DD120`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD160` at `0x006DD160`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD1A0` at `0x006DD1A0`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD1E0` at `0x006DD1E0`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD320` at `0x006DD320`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD220` at `0x006DD220`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD260` at `0x006DD260`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD2A0` at `0x006DD2A0`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DD2E0` at `0x006DD2E0`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DCF60` at `0x006DCF60`: complete57B, compiler intrinsic trap with genuine paired memory barriers.
- `rva006DCEA0` at `0x006DCEA0`: complete50B, compiler intrinsic trap with genuine paired memory barriers.
