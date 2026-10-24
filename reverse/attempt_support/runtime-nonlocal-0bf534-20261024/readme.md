# Runtime continuation-transfer C++ interface controls

BFME2 baseline61395e08f7; committed verified reference0bf534ea7ccde110c456edb9cd2dd5dae823c953.
Pinned Clang23 i686-pc-windows-msvc profile, existing compiler_command path, /O2 /Ob2
/Oy /GR- /EHsc-. All objects were private cached experiments, not build/match.
No production source, ledger, pin, verifier, class view or baseline was changed.

The remaining8809 ASM-only bytes partition into CRT822, VP6/MMX7686, the separately
authorized patched target226 and75 special-entry bytes (runtime dispatch40, RTC35).
This seat investigated the two13B runtime cores as one file/family; CRT, VP6 and
patched-target investigations belong to other workers. Existing evidence read:
reverse/attempt_support/runtime-dispatch-20261023/readme.md and the attempt log.

## Native contract and fresh hypothesis

At7AF3/7C63, native MOV-immediate / POP ECX / LEA / MOV / JMP consumes a synthetic
CALL return slot, reads its PC-relative cell, leaves EAX=target and ECX=consumed
returnPC, preserves EFLAGS/other GPRs, and transfers with ESP advanced4. A normal
C++ RET to that synthetic PC would be wrong. The target's original identity and
runtime writer remain unknown; no signature was invented.

The new hypothesis used genuine compiler continuation APIs rather than source
permutations: _ReturnAddress with __builtin_eh_return for a nonlocal continuation,
and a separate [[clang::musttail]] ordinary tail-call control. The attached C++
files are diagnostic interface projections, not eligible native providers.

Both13B cores were tested independently with their native biases3509 and4341.
__builtin_eh_return emits22B in both cases, with no unresolved references. Its
actual full body saves EBP, reads the synthetic PC, reads the target into ECX,
stores it over the saved return address, sets ECX to that stack slot, restores
EBP/ESP and RETs. It consumes the slot correctly, but EAX stays incoming and ECX
is the stack-slot address rather than the required returnPC. It also has the
wrong frame, instructions and complete extent. It is not a semantically valid
partial, despite expressing a genuine nonlocal transfer.

The musttail control emits9B: MOV EAX,[ESP]; JMP [EAX-bias]. It leaves the synthetic
return slot on the stack, EAX=returnPC rather than target and ECX unchanged. Again
it is not a native-compatible partial. Full emitted disassembly and four independent
symbol/extent results are retained. No truncation, mask, fake argument/return,
register constraint, manual frame, inline assembly or emitted instruction was used.

The concrete prerequisite is a compiler-visible continuation entry model that
both consumes the synthetic stack record and supplies the native EAX/ECX/flags
state without ordinary C++ call/return lowering. These two stock compiler APIs
do not provide it. This finding does not claim every future compiler route is
impossible. The existing reviewed assembly remains the correct owned provider.

## Updated reference/frontier checks

The required scan/lift/ZH lanes were refreshed once because the pin changed.
BFME1 ranked and near serve0 free candidates; scan retains5516 independent
boundary controls. The named lift listing completed. Forced short-path ZH builds
919/987 TUs (68 existing API/configuration failures), examines27008 functions,
and writes0 packets;1112 unique exact placements are already claimed,798 are
multi and4749 near. The default served naked queue is empty. These are bounded
search results, not a claim that all possible source reconstruction is exhausted.

The older shared bfme1-pointer-27429e78 request is superseded by the selected
0bf534 reference update, committed asdadf344e56 with paired full verification
and receipts at reverse/attempt_support/bfme1-reference-0bf534ea-20261024/.
0bf534 precedes27429e78; this is not a claim that27429e78 itself was verified.
The historical request is closed in favor of the project's committed verified
snapshot. Normal future AGENTS freshness checks remain required; no new success
stamp, pointer advance or nested-reference initialization was made in this seat.
