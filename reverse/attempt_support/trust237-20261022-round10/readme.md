# 0x237D3D: native exchange producer controls

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, extent 226.
Previous handoff: `../trust237-20261022-round9/readme.md`. Inputs: BFME2
`0b14a96d7d04`, committed/checked-out BFME1 `42bba2ddbd5c`. Model:
GPT-6.1-sol. No Code source, ledger, pin, verifier or compiler binary changed.

## Hypothesis and result

Read AGENTS freshness, per-RVA history through pick-hard, prior handoffs and
recipes before editing. Prior trials already covered control flow, local
lifetimes, types/layout, callee visibility, compiler settings, front ends,
reference/twin searches, copy coalescing and native padding. Do not rerun them.

New hypothesis: the xchg encoding table's 90 could arise from native atomic
exchange lowering followed by promotion of a private local to a register,
leaving a self-exchange. This is a different producer from the A9 padding
paths and prior ordinary C++ copy/swap probes. Test `_InterlockedExchange`
and `_InterlockedCompareExchange` on private local words whose values do not
change. Cross 1/16 operations, plain/volatile local, zero/status initializer,
one shared/per-operation scope, before/after LocalFree, G6/G7 and O1/O2.
These are diagnostic source choices, not evidence of original target source.

All **256** isolated compiles succeed, yielding **192** distinct raw bodies.
No NOP, NOP16 or bank improvement; every REL32 resolves in the diagnostic
scorer. The exchange operations retain memory instructions and stack homes.
The proposed promotion-to-self-exchange effect does not occur in this finite
family. This does not prove that every native xchg route is impossible.

## Actual compiler trace

RTM c2 SHA256 remains
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
The opcode table calls opcode 9 xchg (row starts 90 86), versus A9 nop.
The encoding selector at preferred VA 0x107B2311 reads opcode from [ebx+4]
and indexes the six-byte encoding/descriptor tables. Read-only Wine debugger
breakpoints at that selector and the generic constructor 0x107A7DD8 are
conditioned on opcode 9. No debugger write alters compiler code or data.

The private-local exchange positive control reaches the selector twice with
the same opcode-9 node, but never the generic constructor's opcode-9 case.
Its successfully emitted native object is 19 bytes; the exchange at +0xC
is **87 01**, `xchg [ecx],eax`, not 90. The trace thus supplies a concrete
native producer control while distinguishing it from bare-NOP emission.
It does not establish an exhaustive constructor inventory. Summary includes
source hash, node/operand snapshots, control bytes and disassembly.

## Verification, retained bank and resume

Sequentially reread every final object and verify its hash, relocations and
NOP inventory independently of parallel scoring. Symbol-relocated Unicorn
emulation covers 256 objects plus retained bank, **193** distinct code and
relocation groups. **121,976 executions pass**: 158 status samples times
four cleanup-return/argc combinations per group. Check return=1, exact API
order/counts, caller-saved clobbers, balanced stack/callee-saved registers,
GUID, file16 and data44 fields. Private atomic memory instructions execute
in the emulator. These tests are not the full byte/identity admission gate.

Independent variant.py again reproduces the **219-byte** bank, score
**69/86 = 0.802326**, masked prefix 205, 21 diagnostic positional differences,
raw SHA256
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
The bank is unchanged. Retail's sixteen 90 bytes at +0xCD..DC and return
increment/restore ordering remain unresolved. No missing game callee has
been identified. No exact match or new link repair is claimed. Last session's
link receipt remains current: VersionDestructor already links 1,275 bytes;
VersionInitGlobals has 200 bytes blocked by this symbol.

Restore the five .py.txt scripts under build/trust237-round10 without .txt.
The driver imports round9/frontends.py, the trace imports round7/wdbg.py, and
the emulator uses round4's scratch Unicorn install; restore those tracked
scripts as their handoffs describe if scratch has been removed. Run
exchanges.py; trace_exchange.py exchange-control.cpp exchange;
inspect_exchange.py; independently variant.py on the bank; emulate_exchanges.py;
summarize.py. Restore the saved control to its named .cpp path as needed.
All compiler objects are isolated; never use build.compile_source.
Do not repeat the completed exchange family unchanged. Further xchg work
needs evidence of a distinct producer that can select a register operand.

Ledger, Python syntax and diff checks pass. Published link-index fetch
succeeds. BFME1 freshness update remains delegated under the live claudec2
lock; no success stamp was written here. Claim released on banking. Preserve
unrelated untracked reverse/zh_sweep/. Continue this assignment next session;
these finite failures prove neither a post-link patch nor C++ impossibility.
