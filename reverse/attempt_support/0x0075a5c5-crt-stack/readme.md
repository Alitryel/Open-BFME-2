# Complete native RTC stack-check member

`RtcStack.cpp` independently recovers the ordinary fastcall guard checker at
0x0075A5C5 (90 bytes). `RTC_CheckEsp.asm` retains the complete flag-dependent
compiler helper at0x0075A5A2 (35 bytes) as mnemonic MASM, with zero C++ credit.
Both original native `stack.obj` rows have been repointed. There is no remaining
native member row that would select a competing public definition from the CRT.

Target/native COFF identities and relocations establish the public names and
callees. Native CodeView and public rtcapi.h agree on the8-byte frame descriptor
and12-byte variable descriptor: signed count at0, pointer at4; signed offset0,
signed size4, char-pointer name8. The checker preserves the signed loop bound,
32-bit address arithmetic, both0xCCCCCCCC guards, short-circuit failure and
caller return-address attribution. An explicit unsigned descriptor-byte induction
variable gives native's add12 loop and final SIB encodings. No Microsoft
implementation source was read, no data or pins were added, and no shared header
was edited. The native code and all relocations match byte for byte.

The CheckEsp entry reads its caller's ZF before any prologue and preserves live
EAX/EDX on failure. Ordinary C++ has neither this input contract nor the required
entry instruction. Assembly is retained only for that proven compiler machinery;
it is not a naked C++ recovery. Its only REL32 calls the authored RTC failure
reporter. The90-byte C++ body calls the authored named-variable reporter.

The independent non-executed focused DLL links both new providers plus the
previous CRT/startup/adapter closure with the original CRT archive and scoped
IAT-only import libraries. Its map selects the new objects for both symbols and
it has no unresolved or duplicate-definition errors. WinMain and the game-free
function-pointer slot are explicit test doubles. This proves focused symbol
closure only, not full-game placement, census or runtime behavior. The two new
units are absent from census2967eab33e and cannot yet be previewed there.
`place_bodies.py` reports0 incidental bodies and0 pins.

The conversion gate initially falsely classified the old prebuilt .lib row as
clean C++. The refusal was recorded with re_log; the independent verifier commit
33b7534498 reuses progress.source_kind. Ten staged/committed regression cases
failed before the fix; conversion-range and gate exploit suites passed60 cases,
with one existing open-audit case skipped. This also closes the inverse hole
where C++ could appear to survive a move into .lib or .s. Production recovery
commits are separate from that verifier correction.

Run `python3 reverse/attempt_support/0x0075a5c5-crt-stack/check_stack.py` after
normal builds to reproduce the native-code/relocation and retail-byte checks.
It reads current objects; its report stays under ignored build/resume-eh-local.
