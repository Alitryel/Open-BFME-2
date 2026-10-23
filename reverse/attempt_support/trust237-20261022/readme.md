# 0x237D3D: SDK layout and status-save experiments, 2026-10-22

Target: `?Rva00237D3DCheck@@YAHXZ`, RVA `0x00237D3D`, 226 bytes.
Inputs: BFME2 `772548d476398bdbea0d76d5c783970a67c7f8c8`, BFME1
`37c3022de1ab944c7ffe536440d637dc8199091c`; default MSVC 7.1 RTM,
`/O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc` unless specified below.
Model: GPT-6.1-sol. No source under Code, ledger row, symbol pin, gate or
baseline was changed. This is an unfinished conversion, not recovered bytes.

## Starting evidence and new hypothesis

Read the complete per-RVA history through `/opt/runner/pick-hard --rva
0x237D3D` and `../worker_237d3d_20261020.md` before editing. Prior work
already rejected the null volatile store, the equal-arm trust-call ternary,
and explicit assembly NOPs. None was retried. The clean bank calls
WinVerifyTrust once, frees argv and returns 1. It emits 208 bytes, with
68/86 retail mnemonics aligned, three structural regions, and a relocation
masked first difference at +0xC3.

The new hypothesis was that actual SDK declarations, the old SDK layout,
and late control-flow simplification could retain the status across
LocalFree and explain more of the tail. The status save is independently
reproducible from semantically equivalent C++; it is not itself proof that
an assembly hatch is needed.

## Findings

`status-save.cpp.txt` emits 217 bytes and agrees with retail through +0xCA,
including `push esi; mov ebx,eax; call [LocalFree]`. Its final expression is
`((unsigned long)status | 1u) != 0`, which is always 1 for 32-bit unsigned
long. It calls the same APIs once and adds no memory side effect. RTM,
SP1 and DDK 4035 all emit the same body. However, it replaces the retail
tail with `mov eax,ebx; or al,1; ... neg/sbb/neg`, still aligns only 68/86
mnemonics, and is not a better overall reconstruction. Preserve the simple
208-byte bank rather than replacing it with this artificial expression.
The diagnostic has two mnemonic structural regions and 23 positional byte
differences, versus three regions and 27 differences for the bank. Those
metrics do not constitute a byte match or an instruction-identity score.

The currently committed SDK's WinTrust.h includes dwUIContext and defines
WINTRUST_DATA as **48 bytes**. This corrects the earlier handoff's assertion
that this particular header defines 44 bytes. Retail passes size 44 and
uses the preceding layout. `sdk-legacy-layout.cpp.txt` uses the actual SDK
Windows/ShellAPI/WinTrust declarations and GUID/WINTRUST_FILE_INFO, plus an
explicit legacy TrustData. Compilation with /showIncludes verified the
intended submodule headers; compile-time assertions verified file=16,
legacy data=44 and current SDK data=48. That version reproduces the same
217-byte diagnostic exactly. Using the current SDK structure wholesale
changes the frame and offsets, with first difference +5. Do not silently
substitute its layout or trim a vendored header.

`wb_show.py 0x237D3D --gd` confirms no paired WorldBuilder body. The prior
reference search found no game-source counterpart; no broad sweep was
repeated in this assigned lane.

## Experiments not to repeat unchanged

There were 3,072 successful matrix compilations, not 3,072 independent
emitted bodies. `summary.json` records distinct raw bodies and grouped
measurements. No successfully compiled function contained sixteen
consecutive 0x90 bytes. All compilation used isolated objects under
build/trust237-session through compiler_command, never compile_source.

| Family | Successful compilations | Choices |
| --- | ---: | --- |
| factorial | 1024 | shim/current SDK, early/late status, signed/unsigned, nested/flat TrustData lifetime, shim throw(), direct/inline cleanup, 16 return/control-flow shapes |
| compatibility SDK | 512 | same source choices with SDK APIs and explicit legacy data; SDK throw() choice is intentionally inert |
| flags | 384 | shim/legacy SDK, 16 tails, 12 settings |
| compiler profiles | 48 | RTM/SP1/DDK4035, 16 tails |
| region recombination | 280 | five unsigned predicates, 14 result/loop/cleanup shapes, status declaration timing, O1/O2 |
| original status-check diagnostics | 72+96+80+576 | two-status tests, if/switch/goto/loop/Boolean forms, constants, const/int/unsigned/register, initializers, copies/reference aliases and repeated comparisons |

The recombination family includes 112 explicitly marked negative-predicate
diagnostics that can return 0 or loop; they are **not** candidate banks.
Sixteen invalid const declaration/assignment combinations in status_probe3
were rejected by the compiler and are excluded from the successful count.
An initial SDK setup lacked its include path; an initial recombination
scorer rejected a relocation crossing the comparison extent. The saved
drivers include the include-path/scorer corrections. These setup failures
are not evidence about the target.

Flags covered G5/G6/G7, Oy, Og-, O2, Ob0/Ob2, Os/Ot, Oi, Od, disabled
C++ EH, and GA. Og- has a 226-byte output but differs extensively; equal
size does not imply closeness. Ob0/Od can introduce unresolved helper
calls; no such result is eligible for admission. Throw(), inlining and
declaration-scope choices did not improve the status-save diagnostic.
Status-consuming original-check reconstructions are diagnostic only:
their conditional return changes retail's unconditional result. No error
constant tested here is established as an original target-source fact.

The leading interpretation of the remaining sixteen NOPs is still a
post-link patch, but these finite trials do not prove that interpretation
or impossibility of every C++ spelling. The unused status save should no
longer be described as independently impossible from clean C++.

## Measurements and reproduction

`comparison.txt` preserves retail/bank/status-save tail disassembly and the
current local link predictions. Scratch DIR32 fields are filled from retail
for diagnosis; REL32 maps use memset=0x6291AE and the actual WinVerifyTrust
import thunk=0x655652. This is not a substitute for identity, relocation,
extent and full-byte admission checks. No match or new pin was admitted.

Copy the saved *.py.txt drivers to build/trust237-session/*.py and copy the
bank to build/trust237-session/base.cpp. From the repository root run
`python3 build/trust237-session/search.py factorial`, then its `compat` and
`flags` modes. Run the other saved drivers by name. Each driver uses eight
compiler threads and disjoint scratch names; run the families sequentially.
The initial setup/probe calls are not part of the matrix counts.

Prework check_csv passed. BFME1 checkout equals the committed pointer;
freshness update was skipped per the runner because the live shared lock
was owned by claudec2. No freshness-success timestamp was written. Fetching
the published link index succeeded at census 08160bc2c9.

The current direct blocker is VersionInitGlobals.cpp: its 200 matched
bytes have one unresolved symbol, this check. VersionDestructor.cpp now
passes its local link prediction at 1,275 bytes. This does not establish
transitive closure; the historical 1,584-byte blocked-unit figure is stale.
Neither prediction constitutes a new linking improvement from this work.

## Handoff

Keep the clean bank at score 0.791 (68/86 aligned mnemonics); it remains
the simpler semantic reconstruction. Outstanding: reproduce retail's
sixteen internal NOPs at +0xCD..+0xDC and the complete xor/inc/restore tail
without a prohibited hatch. The status-save diagnostic is a new region
winner to use if a supported tail shape is found. No missing callee is a
prerequisite. Declaration, lifetime, API/layout, callee visibility and
compiler-setting explanations all received concrete trials this session.
Do not rerun these matrices without a new explanation. The standing
assignment remains this body; no other task was taken.
