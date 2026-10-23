# Debug allocator reallocation trailer

Target: `?rva006C4730@GeneralAllocatorDebug@@QAEPAXPAXIH@Z`, native
`0x006C4730..0x006C4A4E`, 798 bytes including RET12. Home:
`Code/GameEngine/Source/Common/Rva006C1F60Finish.cpp`. Inputs: BFME2
`e0b591070c`, BFME1 `cf0a80c228583af789772b794ab27abcab2debbf`, stock
13.10.3077 compiler, bank's `/MD` flags.

Read the complete current home, allocator allocation siblings, bank and prior
attempts, especially 66520. The metrics provider is now a real matched
`rva006C26F0(void *, bool)` body. This removes the old ABI prerequisite but
does not remove the remaining trailer-expression mismatch.

The existing bank reproduces the complete 798-byte extent with all calls
resolved. Six instruction lines differ, confined to `0x006C47CA..0x006C47E4`:
retail masks the capacity, adds four on the non-mmapped arm, joins, computes
`lea ecx,[ecx+eax-10]`, and stores a zero word through ECX. The bank distributes
the payload address into the two arms and folds minus ten into the store.
Outside this window the complete body agrees. This is target-byte evidence;
the original public method name remains unproved.

New bounded tests through ordinary `tools/explain_mismatch.py`, in isolated
scratch paths, without direct compilation or shared-cache replacement:

- Four header-origin forms: numeric capacity and integer header-relative
  address regress to 784 bytes; pointer PHI gives 812; ushort indexing retains
  798 but adds a shift/scaled store, giving 20 differing bytes. The latter proves
  the numeric branch join is reachable, but its address calculation is wrong.
- Three accessor-return forms using numeric capacity, integer address, or the
  real two-word chunk header all give 784 bytes. No unresolved calls.
- Pointer-bound two-byte for/while fills give 846 bytes; a one-word pointer
  range gives 830. All change the frame from native 0x544 to 0x540 and regress
  the register allocation. These differ from the old integer-index fill loop.
- Inlining the complete, already verified 71-byte `rva006C1CC0` allocation
  helper (including its flag-controlled two-byte request adjustment) gives
  784 bytes with either `inline` or `__forceinline`. It does not solve the
  trailer join. The wrapper subtracts the caller's existing extra two bytes
  before using that helper, preserving the actual request size.
- Authenticated 13.10.4035 and 13.10.6030 compiler profiles both retain the
  same 798-byte body and first difference at +0x9B in the corrected context.

The existing bank remains the best resumable source and was not overwritten.
No nonmatching source, new pin, alias, ledger row or verifier change was kept.
The earlier value/if-else/memset/struct-store and flag trials remain applicable;
do not repeat them. Remaining prerequisite is a supported C++ expression or
compiler-phase explanation for the exact join and address-materialization
shape while preserving the native register allocation.
