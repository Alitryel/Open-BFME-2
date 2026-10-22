# 0x237D3D: intrinsic byte swaps and 64-bit rotations

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, extent 226.
Previous handoff: `../trust237-20261022-round10/readme.md`. Inputs: BFME2
`9555fa4885d7`, committed/checked-out BFME1 `42bba2ddbd5c`. Model:
GPT-6.1-sol. No Code source, ledger, pin, verifier or compiler binary changed.

## New hypothesis and results

Read current instructions, per-RVA history through pick-hard, earlier
handoffs and recipes before editing. The earlier control-flow, lifetime,
layout, visibility, settings, front-end, reference, ordinary copy/swap,
padding and private atomic-exchange matrices are already recorded. Do not
repeat them unchanged.

The new hypothesis is a different possible producer of opcode-9 register
exchange: intrinsic byte swaps or 64-bit half rotations might lower through
an exchange that survives late coalescing as 90. Prior manual arithmetic
identities and atomic memory exchanges do not test this lowering route.
These source choices are diagnostics, not established original source.

`swaps.py.txt` crosses eight complete unsigned-status identities: double
16/32/64-bit byte swaps, two half rotations, equal-half rotation, inverse
17-bit rotations, equal-byte 16-bit swap and equal-byte 64-bit swap.
Factors are 1/16 repetitions, before/after LocalFree, retained bank predicate
versus discarded status/return 1, block scopes versus forceinline helper,
G6/G7 and O1/O2. All **512 compiles succeed**, yielding **118 distinct raw
bodies**. None contains NOP, NOP16 or improves the retained bank. Every
REL32 resolves in the final diagnostic scorer.

The initial scorer omitted `__allmul` in 32 receipts. Add its independently
matched RVA 0x629580 and rescore the existing objects without recompiling;
the raw hashes and instruction inventories remain unchanged. The initial
emulator also stopped on this missing helper mapping. Its corrected run
executes the actual 52-byte matched retail helper, including its arithmetic
and ABI, rather than treating it as an API stub. Neither setup omission is
a source-candidate failure; only the completed corrected run is counted.

## Native compiler controls

The actual RTM stdlib.h declares all five tested intrinsics, and their
intrinsic pragmas are accepted. Five small functions exercise 16/32/64-bit
byte swaps, one 32-bit half rotation and inverse half rotations. Across
G3/G4/G5/G6/G7 all five compiles succeed, and each function's raw bytes and
relocations are identical across CPUs. The 16-bit swap uses MOVs through
CH/CL; the 32/64-bit swaps use BSWAP; the rotations exchange halves through
load/register selection. None emits XCHG or NOP.

RTM c2 SHA256 remains
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
Use the preceding round's read-only Wine debugger conditions at the
opcode-9 encoding selector 0x107B2311 and generic constructor 0x107A7DD8.
The five-function control finishes and emits its object with **zero hits**.
Every traced function's bytes equal its independent untraced counterpart.
This trace supplies no register-exchange producer; it is not an exhaustive
proof about all compiler paths. No debugger write alters compiler code/data.

## Checks, retained bank and resume

Sequentially reread all 512 final objects and independently audit hashes,
relocations and NOP inventories. Symbol-relocated Unicorn execution covers
them plus the bank: **119 distinct code/relocation groups**, 158 status
samples times four LocalFree-return/argc combinations, **75,208 executions
passed**. Check return=1, balanced stack/callee-saved registers, external
caller-saved clobbers, exact observable API order/counts, GUID, 16-byte file
and 44-byte data fields. O2 may inline memset. This is diagnostic validation,
not full byte/identity admission.

Independent variant.py reproduces the unchanged **219-byte** bank, score
**69/86 = 0.802326**, diagnostic masked prefix 205 and 21 positional
differences. Raw SHA256:
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
Retail still differs in sixteen 90 bytes at +0xCD..DC and the increment/
restore ordering. No missing game callee has been identified. No exact
match or new link repair is claimed. Previous link receipts remain current:
VersionDestructor already links 1,275 bytes; VersionInitGlobals has 200
bytes held by this unresolved symbol. These finite trials establish neither
C++ impossibility nor a post-link patch.

Restore the six saved source/scripts under build/trust237-round11 without
`.txt`. The scoring driver imports round9/frontends.py; the trace imports
round7/wdbg.py; the emulator uses round4's scratch Unicorn install. Restore
those tracked scripts as their handoffs describe if scratch is gone. Run
swaps.py and control_cpus.py, then trace_swaps.py
build/trust237-round11/swap-control.cpp swap-control. Independently run
variant.py on the retained bank with the exact command in round10's handoff,
then emulate_swaps.py and summarize.py. All objects are isolated; never use
build.compile_source. summary.json preserves compact receipts and emitted
control bytes. Full matrix objects/logs remain disposable scratch.

Do not repeat this intrinsic family unchanged. Further exchange work needs
evidence of a distinct producer selecting register operands. Retain the
current best bank and continue only this assignment next session.

Ledger, Python syntax and diff checks pass. Published link-index fetch
succeeds. BFME1 freshness update remains delegated under the live claudec2
lock; no success stamp was written here. Claim released on banking.
Preserve unrelated untracked reverse/zh_sweep/.
