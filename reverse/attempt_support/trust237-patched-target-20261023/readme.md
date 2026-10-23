# Patched signature check at RVA 0x00237D3D

## Scope and authorization

On 2026-10-23 the user authorized Jonathan Wilson's proposed assembly exception
for this target's signature-verification check. This is an assembly recovery,
not an authored-C++ match. No verifier, coverage rule or baseline was weakened.

## Evidence

The 226-byte target builds WINTRUST_FILE_INFO (16 bytes) and legacy
WINTRUST_DATA (44 bytes), uses WINTRUST_ACTION_GENERIC_VERIFY_V2, calls the
WinVerifyTrust import thunk at 0x655652, frees CommandLineToArgvW's argv, and
returns 1. Its dead status save is followed by XOR EAX,EAX, sixteen single-byte
NOPs at +0xCD..+0xDC, and INC EAX. The call from initVersionGlobals at 0x238666
consumes the returned integer. The boundary and APIs were already established
in worker_237d3d_20261020.md and subsequent trust237 handoffs.

Jonathan Wilson reported an apparent unmodified ROTWK Worldbuilder.exe,
MD5 5215df09d2dc21ceca80f2b60c7b0971, containing the corresponding function at
VA 0x00EA4740 with status checks after WinVerifyTrust. That is supplied human
evidence, not an independently reproduced binary comparison here. The exact
patch author, original status-test bytes and original source remain unknown.
The target bytes and unconditional-success behavior are independently verified.

## Implementation and verification

VersionSignatureCheckPatched.asm preserves the observed API calls, stack
structures, calling conventions, saved registers and patched return sequence.
API references use named externs and normal relocations, not hard-coded IAT
addresses. WinVerifyTrust uses the existing rowed import thunk. No new pin is
needed. add_match.py verified all 226 bytes and three named IAT references.
The normal tool recorded the landing and removed the bank; the prior bank
remains retrievable from Git history.

mixed-candidate.cpp.txt preserves the narrower C++/inline-assembly alternative.
It emits 226 bytes and matches except for the order of PUSH ESI and MOV EBX,EAX
at +0xC2..+0xC4. The assembly island has the sixteen NOPs and return shape exact.
C++ LocalFree keeps argv live in ESI but pushes it after the status-save island;
referring to argv directly inside assembly instead forces a stack spill and
changes the frame. O1/G5/G6/G7 and Og/Os controls retain the three-byte ordering
difference; O2/Ot diverge further. Do not relaunch the older broad NOP searches.

This exact assembly implementation can supply a linker definition, but this
run does not claim a newly measured linked-byte gain or authored-C++ gain.
