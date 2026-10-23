# 0x237D3D: return conversion carriers and the full native encoder

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, extent 226.
Previous handoff: `../trust237-20261022-round11/readme.md`. Inputs: BFME2
`4bae5b8bf6`, committed/checked-out BFME1 `42bba2ddbd5c`. Model:
GPT-6.1-sol. No Code source, ledger, pin, verifier or compiler binary changed.
Read the current instructions, per-RVA pick-hard history and prior evidence
before these trials; earlier control-flow, lifetime, layout, visibility,
compiler, reference and exchange families remain ruled out as recorded.

## New source hypothesis

A return-value conversion object may couple status lifetime, return
evaluation and cleanup differently from the previously tried argv owners
and empty lexical guards. `carriers.py.txt` crosses value/reference/pointer
status storage; cleanup outside, in conversion or in the destructor;
aggregate/user-defined construction; int/bool conversion; ordinary/throw()
members; the bank's range predicate versus `(u|1u)!=0`; ordinary/forceinline
members; G6/G7; and named/direct temporary or aggregate scope forms.
All expressions return one for every unsigned status and preserve the
single WinVerifyTrust and subsequent LocalFree effects. These are diagnostic
source shapes, not recovered identities or evidence of original source.

All **1,152 compiles succeed**, yielding **26 distinct main bodies**. None
contains NOP/NOP16 or ends in retail's `40 5e 5b c9 c3` increment/restore
suffix. None improves the bank. There are 960 fully resolved main-body
diagnostic receipts and 192 with an out-of-line same-unit conversion call:
96 int and 96 bool. Do not assign those helpers fabricated retail addresses.
Their ten distinct emitted bodies also contain no NOP/NOP16.

Sequentially reread every object and independently check raw hashes,
relocations, diagnostic scores and instruction inventories. Emulation
includes the emitted helpers and their recursive relocations, not helper
API stubs. All candidates plus the bank form **36 complete unit code and
relocation groups**, 14 with local helpers. **22,752 executions pass**:
158 statuses times four LocalFree-return/argc combinations per group, checking
return=1, stack/callee-saved registers, external ECX/EDX/flags clobbers,
observable API order/counts, GUID and file16/data44 fields. These finite
behavior checks are diagnostics, not full byte/identity admission.

## Full native encoder probe

Earlier round4 emulation entered inside padding at 0x107A7E32. This round
starts at the actual encoder entry **0x107B2250** and returns through its
normal `ret 10h`, covering the outer dispatch and node attribute handling.
Use the actual RTM c2, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
Opcode A9, node type 0D, byte9=1 and word+A=6000 come from round7's
positive trace; byte9|=2 is the previously identified alignment flag.

The initial harness incorrectly interpreted argument 3 as padding length.
Disassembly shows the entry replaces that argument's stack home with
`word[node+A]&0FFF`, falling back to byte[node+16] when zero. Correct the
harness, rather than counting that setup assertion as a candidate failure.
Cross lengths 0..64, high attribute bits 0/6000, flags 1/3, fallback lengths
1/7/16 and context argument 0/1/16. All **2,340 executions** pass output,
boundary, return-length, stack and callee-saved checks. Each agrees with
the earlier static padding recipe; length16 is
`eb0d8da424000000008d9b0000000090`, never sixteen 90 bytes. The recipe
pointer table 0x10870C5C and long recipe 0x10870D1C lie in read-only
`.rdata` (40000040). No actual compiler memory or code is patched; only
private emulator context is initialized. This finite probe does not prove
all compiler paths impossible or establish a post-link patch.

## Bank and continuation

Independent variant.py reproduces the unchanged **219-byte** bank,
**69/86 = 0.802326**, masked prefix **205**, **21 positional differences**.
Raw SHA256:
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
Retail's sixteen 90 bytes at +0xCD..DC and increment/restore order remain
unresolved. No missing game callee is identified. Do not repeat these
return-carrier or observed-A9-attribute matrices unchanged. A further
compiler producer hypothesis needs distinct evidence.

To reproduce, restore the four saved scripts without `.txt` under
build/trust237-round12. Restore round9's tracked frontends.py and round5's
base.cpp.txt as their handoffs describe; the emulator uses round4's scratch
Unicorn install. Run carriers.py (eight isolated compiler workers), run
variant.py on the retained bank with the command in round10's handoff,
then emulate_carriers.py, encoder.py and summarize.py. Never use
build.compile_source. summary.json retains compact checked receipts and
helper bytes; full disposable matrix objects remain under build/.

Ledger, Python syntax, diff and ordinary evidence-commit hook checks pass;
these checks byte-verify zero source units and do not admit an exact match.
BFME1 freshness update remains delegated under the live claudec2 lock; no
success stamp was written here. Claim released on banking. Preserve
unrelated untracked reverse/zh_sweep/ and continue only this assignment.
