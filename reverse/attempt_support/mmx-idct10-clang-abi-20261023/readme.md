# MMX IDCT: alternate compiler and saved-register investigation

Retail `_MMX_idct10_DX`, RVA 0x001D4D50..0x001D515A, is 1034 bytes.
This is a blocked investigation, with no production change or recovered bytes.
Elapsed investigation: approximately 10 minutes; model GPT-6.

Read the existing attempt-log records, the October 12 intrinsic banks and their
verification evidence, the clean-room README, spec `001d4d50.md`, and the complete
existing retail assembly owner. No external VP6 decoder source was consulted.
The existing 1390-byte C++ candidate remains a better bank and is unchanged.

## Target facts and new hypothesis

The retail owner saves EDX, ECX and EBX in that order, uses MMX registers, has no
aligned local frame, and calls no functions. Its incoming EAX is not preserved:
the first argument replaces it. The spec describes a void cdecl function with
three stack arguments. The constant block is the existing 48-word
`g_vp6IdctConstantBlock` array; the diagnostic sources use that canonical global,
without an additional global, pin or address alias.

A separate ordinary C++ probe showed that Clang's
`no_caller_saved_registers` attribute can generate the EDX/ECX/EBX save order.
This was a concrete new compiler/ABI lead rather than another MSVC source matrix.
It does not solve the target by itself: a void function also saves modified EAX.
We did not change the target's declared return type to manufacture an exemption.
Clang's `preserve_all` attribute is rejected on the 32-bit target; the already
available Clang 3.9.1 rejects `no_caller_saved_registers` as unknown.

## Whole-function trials and independent controls

The input body is the approved in-repository `root-o2-g6.cpp` intrinsic bank.
All compiles write private objects under ignored `build/` in this worktree.
They do not call `build.compile_source`, write shared match-cache objects, or
truncate the emitted symbol to 1034 bytes. Input receipts record full extents,
relocations, source/object hashes and the actual commands.

Using the old MSVC MMX header with Clang 23 leaves ordinary unresolved intrinsic
calls: 10389 bytes and 249 relocations. This is not an intrinsic implementation
or a viable candidate. Using the unmodified x86 header from the verified Clang
23 release instead fails with SSE2 disabled. LLVM's release notes explain that
from version 20 these intrinsics use SSE2 and the old MMX builtins are removed:
https://releases.llvm.org/20.1.0/tools/clang/docs/ReleaseNotes.html#x86-support

Two official, portable LLVM-MinGW releases were therefore tested without
installers or registered compiler-profile changes:

| Compiler | Source shape | Whole bytes | Relocations |
| --- | --- | ---: | ---: |
| 19.1.7 | original helper references, extra saves | 2713 | 46 |
| 19.1.7 | helpers passed by value | 2736 | 46 |
| 19.1.7 | SSE2 enabled | 2904 | 31 |
| 18.1.8 | original helper references, extra saves | 2713 | 46 |
| 18.1.8 | ordinary cdecl, no extra-save attribute | 2707 | 46 |
| 18.1.8 | helpers passed by value | 2736 | 46 |
| 18.1.8 | size optimization | 2704 | 46 |

These bodies emit no calls, but have an aligned frame and extensive transfers
between general registers, stack memory and MMX values. The SSE2 control also
uses 113 XMM instructions. Removing the save attribute, changing helper value
lifetimes and selecting size optimization do not remove the core mismatch.
Clang 18 and 19 emit identical baseline body bytes: the hypothesis that their
intervening MMX IR change caused this residue is ruled out, not established.

## Reproduction and remaining work

`input-proof.json` records the official release URLs, archive sizes/hashes,
unmodified x86 header hashes, host compiler/runtime hashes and exact commands.
Older release assets did not publish an API digest; the archive hashes are our
receipts for downloads from those official HTTPS release assets. The two
`.cpp.txt` files preserve exact trial source bytes. Their scratch profile comment
is not an admission claim: the recorded private commands explicitly replace the
driver with the indicated unmodified Clang 18 or 19 executable, in MSVC mode.
Their own x86 `mmintrin.h` is extracted from the same release's
`lib/clang/<version>/include/` directory and selected explicitly. No MinGW target
headers or libraries replace the established VS2003 inputs.

Resume only with an explanation for the scalar/vector round trips, a genuinely
different implementation shape, or a compiler capable of the complete native
schedule and ABI. Do not repeat the listed controls or treat extra-register
preservation alone as byte recovery. No new implementation is admitted; the
verified assembly owner and stronger existing bank remain intact.
