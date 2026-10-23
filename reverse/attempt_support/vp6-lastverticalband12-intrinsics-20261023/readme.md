# LastVerticalBand_1_2_Scale_MMX intrinsic repair attempt

This is assembly-hatch removal research, not additional matched coverage.
The existing matched 31-byte implementation is retained unchanged. No external
decoder source was read. Identity and ABI come from the approved clean-room
spec `reverse/vp6_cleanroom/specs/001d26e0.md`; the instruction ordering and
counter predicate below were independently checked against retail.

## Inputs and runtime

- BFME2 checkout: b070af86da230bf77203cfc1d73c45a2b400865e.
- Verified BFME1 toolchain pin: 138757e9b74645fbcbb7724a7af2764e34931e11.
- Retail game.dat SHA256: f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640.
- Granted seat: t3-b3925755, isolated OrbStack runtime, BUILD_POOL=1,
  BFME_OBJSTORE=off. Only normal build.sh and explain_mismatch compilation.
- No full-tree gate, reference edit, runtime edit, new pin, or EMMS was used.

## Measured findings

The saved candidate is the complete single-function TU, not a partial kernel.
It emits genuine MMX MOVQ loads/stores from __m64 assignments, with no inline
assembly and no EMMS. That disproves the existing source comment that there is
no C form for this copy; it does not establish exact compiler scheduling.

An explicit __m64 temporary emits 42 bytes with an aligned stack frame.
Removing the temporary emits 38 bytes and removes stack realignment, but omits
the retail EBP frame. Adding /Oy- gives the saved 39-byte candidate. The remaining
differences are argument-load order/register allocation, loop alignment, and a
separate preserved-width comparison. A register band parameter leaves ESI
holding pitch, not the retail band pointer. A guarded-decrement loop is rewritten
into trip-count arithmetic. A signed-countdown diagnostic emits 35 bytes with
SUB before pointer ADD and a separate TEST; it is not the saved candidate and
does not justify signed-overflow assumptions for the unsigned-width ABI.

IMPORTANT: requested /O1 and /G5 source-comment changes were NOT independent
compiler trials. The normal region policy replaces them with /O2 and the
default region tuning. The saved source actually receives the extra flags
`-O2 -Oy- -DNDEBUG -MD`; /Oy- does pass through. The /Og- diagnostic also passes
through, but worsens the frame and argument reloads. No flag-default bypass or
override-proposal tool was used.

Retail bytes, RVA 0x001D26E0, complete 31-byte extent through RET at 0x001D26FE:

    558bec568b75088b4d0c8b55100f6f060f7f040e83c60883ea087ff15e5dc3

Saved candidate bytes, complete 39-byte COFF symbol, no relocations:

    558bec8b55108b4508568b750c8d49000f6f008bca0f7f043083c00883ea0883f9087fec5e5dc3

Retail keeps band in ESI, pitch in ECX, width in EDX, and executes pointer ADD,
width SUB, then JG. The candidate keeps band in EAX, pitch in ESI, width in EDX,
copies width into ECX, then executes pointer ADD, width SUB, CMP ECX,8, JG.

## Counter semantics and validation limits

Retail executes at least one eight-byte copy even for zero width. SUB width,8
followed directly by JG means continuation iff signed(previous width) > 8.
Testing only signed(wrapped subtraction result) > 0 is not equivalent at
0x80000000..0x80000007, because JG also observes overflow. The saved candidate
preserves the pre-subtraction test and uses unsigned subtraction.

The predicate was checked against simulated x86 ZF/SF/OF on 104295 boundary
and deterministic random widths, including zero and the signed boundary.
This is arithmetic analysis, not function execution or exhaustive proof.
Unicorn differential execution was attempted but could not start because the
authorized Python environment has no unicorn module; no packages were installed.
explain_mismatch reports the native Apple objdump -b incompatibility; COFF bytes
were instead read without compiling and decoded using existing capstone.

To resume, temporarily put candidate.cpp.txt at the original VP6 source path,
then run the normal scoped build and explain_mismatch there under a fresh
parent compiler grant. Do not replace the matched implementation with this
nonmatching bank, weaken flag policy, or bank a row over the existing match.
The open problem is obtaining the native register/flags schedule from a
semantically valid whole-function C++ form under admitted compiler settings.
