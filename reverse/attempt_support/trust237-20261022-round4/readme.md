# 0x237D3D: exception scopes and the compiler padding emitter

Continue `../trust237-20261022-round3/readme.md`. Target remains
`?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, extent 226. Input BFME2
`a96b3fd81f` and verified BFME1 pointer
`37c3022de1ab944c7ffe536440d637dc8199091c`. Model: GPT-6.1-sol.
No Code source, ledger row, pin, gate or compiler binary changed.

## Bank unchanged

Retain `reverse/attempts/0x00237d3d.cpp`, score 69/86 = 0.802326.
Independent `variant.py` compilation again reproduced 219 bytes, 21
diagnostic positional differences, first at +0xCD. G3 and G4 independently
reproduce its raw hash:
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
Retail's sixteen 0x90 bytes at +0xCD..+0xDC and the return-tail ordering
remain unresolved. No exact admission or new recovered bytes are claimed.

## New hypotheses and negative trials

Before editing, read the per-RVA history and the preceding handoffs.
Status identities, ordinary lifetime/layout/visibility changes and modern
CPU alignment controls had already been tested. This round investigated
whether empty exception scopes leave individual NOPs after handler removal,
and whether the compiler's actual padding routine or older CPU targets
explain the unusual sixteen-byte span.

`exception_scopes.py.txt` tests eight kinds: SEH empty finally, SEH filter
zero (continue search), C++ catch/rethrow, and five empty destructor forms
(ordinary, throw(), forceinline, forceinline throw(), noinline). Each has
1/4/16 nested scopes, four positions (trust call, LocalFree, return, whole
tail), three previously established return forms, G6/G7 and EHsc/EHa.
All **1,152** compiles succeeded, emitting **167** distinct raw bodies.
None contains a NOP or improves the bank. Empty destructors reproduce
existing bodies; SEH retains prologue/epilogue helpers, changes the frame
and has first difference +0. Catch/rethrow either disappears or retains
EH machinery. `summary.json` keeps grouped results and regional examples.

`legacy_cpu.py.txt` separately tests G3/G4 with SSE or default architecture
for the bank and the previous real-loop control. All eight final compiles
succeed: four target bodies equal the bank and four controls equal one
52-byte body. The controls use the same six-byte identity padding, with no
NOP. This rejects the specific hypothesis that these older CPU targets
use a repeated-0x90 padding path. An initial `/arch:IA32` spelling was
ignored with D4002; the saved driver correctly omits the architecture flag
for the default mode. Do not use an ignored flag as acceptance evidence.

All target scoring is diagnostic DIR32 masking with REL32 maps
memset=0x6291AE and WinVerifyTrust=0x655652. Shifted relocations and added EH
helpers can make positional scores misleading. The recorded scores do
not establish relocation correctness or an admissible match.

## Positive compiler finding

The actual MSVC 7.1 RTM c2.dll has SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
The padding pointer table at VA 0x10870C5C supplies recipes for lengths
1..15. Every one of the preceding session's 18 observed CPU/length recipes
matches this table. Code at 0x107A7E32..0x107A7E85 copies the short recipe;
the block at 0x107E8640..0x107E869C handles longer requests by copying
15-byte recipes and returning to the short path for the remainder.

`emulate_padding.py.txt` executes these **actual compiler instructions**
in Unicorn 2.1.4, with the compiler image mapped at its preferred base,
a private output buffer and stack, and the request at ESP+0x34. EDX starts
at output+1 because the first block decrements it. The zero-request path
reads the instruction node's default byte at EBX+0x16; the test supplies
a zero-filled node. All 65 requests, 0..64, reach the expected exit at
0x107B2471, produce the requested byte count and equal the table model.

A **16-byte request emits**
`eb0d8da424000000008d9b0000000090`, not sixteen single-byte NOPs.
This independently verifies this padding path, including a size beyond
the earlier C++ controls. It does not prove that every compiler path uses
this emitter, nor that retail was post-link patched. Those remain distinct
hypotheses. Do not repeat an unsupported universal no-NOP claim.

The targeted sibling-image probe found neither WinVerifyTrust nor
CommandLineToArgvW imports in the BFME2 or BFME1 WorldBuilder, and no
contiguous verification GUID. This corroborates the missing automatic WB
pair but does not rule out every indirect/dynamic counterpart. No broad
reference sweep was repeated.

## Resume

Keep working only this body. A further explanation must account for the
individual 0x90 instructions, the retained dead status save and the exact
xor/increment/restore ordering. The observed ordinary npad path is now
accounted for; another spelling of its alignment option is insufficient
new evidence. No missing-function prerequisite was identified.

To reproduce, copy the saved `.py.txt` drivers and `base.cpp.txt` to
`build/trust237-round4/` as `.py` and `base.cpp`. Run from the repository
root. The inspection and legacy CPU drivers use tracked inputs directly;
scope tests write only private scratch objects. For the emulator, a scratch
venv with `unicorn==2.1.4` and `pefile==2024.8.26` is sufficient. The
installed venv and compiled objects are disposable; scripts and compact
results are tracked here. No shared match-cache object was written.

Prework check_csv passed. BFME1 freshness update was skipped under the
other seat's live claudec2 lock; no success timestamp was written.
Preserve unrelated untracked `reverse/zh_sweep/`.
