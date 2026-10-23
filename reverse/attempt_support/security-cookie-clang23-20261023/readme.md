# Security-cookie reconstruction through an unmodified LLVM backend

Target @__security_check_cookie@4, 0x00629BAB..0x00629BB9, 14 bytes.
Inputs at the initial proof: BFME2 008879c78e; BFME1 96c88c73a5.
The native ABI and identity are already established by secchk.obj, the
adjacent report_failure body and the existing October 18/22/23 handoffs.
Read those before repeating the exhausted MSVC 7.1 source/profile trials.

A new, independent backend hypothesis succeeds privately. Clang 23.1.1 from
the pinned LLVM-MinGW 20260908 release emits a 13-byte CMP/JNE-to-external/RET
by default. Its ordinary -branch-folder-reorder-blocks=false option retains
CMP/JNE/RET/JMP. With a returning declaration of the real report_failure,
the complete COFF function is 14 bytes. A noreturn declaration instead emits
a CALL and is not exact. No source probability hint is needed.

Raw COFF: 3b0d000000007501c3e900000000
DIR32 at +2: ___security_cookie, independently established VA 0x00DD7F10.
REL32 at +10: _report_failure, independently established RVA 0x00629B7A.
Resolving these two actual relocations reproduces every native byte. There
are no additional bytes past the 14-byte body. EAX and EDX are untouched;
the only ordinary instruction effects are the original comparison and tail
transfer. No custom ABI view, new pin, global or identity is introduced.

The reconstructed source is the ordinary unsigned comparison and failure
call, with the established extern C/fastcall entry and extern C/cdecl callee.
No inline assembly, emitted byte array, patched compiler decision or modified
object is used. Clang is an alternate reconstruction compiler, not asserted
to be the historical retail compiler. The compiler profile is a separate
verifier change and all normal byte/identity/data/hook gates remain required.

Further controls: current MSVC 19.41 emits a 13-byte conditional tail jump;
Clang 3.9.1 emits the right branch order but memory/register CMP opcode 39
rather than native 3B. Neither control is landed. The pinned profile uses the
whole-byte exact Clang 23 result, not a masked comparison or truncated body.

Normal explain_mismatch with the explicit pinned profile independently reports
14-byte compiled symbol, classification exact match. Production admission
and normal hooks must still pass before this is reported as a C++ recovery.

The production declaration uses unsigned long, the established x86 DWORD_PTR
underlying type of the cookie definition in security_cookie_init.cpp. This
was rechecked against the actual BaseTsd.h typedef and the whole body remains
exact. input-proof.json records the final source, complete object extent,
native bytes, both actual relocations and the archive/binary input hashes.

Production add_match --replace-existing passed the whole function and all
reference checks with the real regional settings. The profile translates the
old MSVC CPU-tuning flag to Clang -mtune, without changing default MSVC
commands. The two adapter regressions passed alongside the original cases
(110 tests passed, one empty optional test matrix skipped). The first full
gate refused an unrowed source prepared too early; the file was parked and
then admitted normally before retrying. No gate or whitelist was weakened.

The explicit provider passes link_check --prepare-current with strict
reusable receipts and --new-variants. The published census predates this
new owner, so no LINK status or census credit is claimed. The pre-publication
progress report measures +14 C++ exact bytes and -14 ASM-only exact bytes.
