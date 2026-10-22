# 0x237D3D: native padding producers and register coalescing

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, extent 226.
Previous handoff: `../trust237-20261022-round6/readme.md`. BFME2 input
`aaf3c83ffe`; committed and checked-out BFME1 input `42bba2ddbd`.
Model: GPT-6.1-sol. No Code source, ledger row, pin or gate changed.

## New hypotheses and finite trials

Read the per-RVA history with `pick-hard --rva`, prior evidence and recipes.
Earlier sessions cover predicate identities, loops, lifetimes, ABI/layout,
callee visibility, EH and supported compiler profiles. This round tests
whether late register coalescing leaves NOPs, then traces native c2 padding
producers instead of repeating the previous source matrices.

| Family | Attempts | Objects produced | Distinct raw bodies | With `nop` mnemonic |
| --- | ---: | ---: | ---: | ---: |
| Full-function copy/coalescing combinations | 480 | 480 | 9 | 0 |
| Acyclic byte/short/branch probes | 512 | 512 | 252 | 0 |
| Adjusted branch-distance probes | 576 | 576 | 224 | 0 |
| QI/managed option controls and whole bodies | 36 | 30 | 6 | 0 |

The 480 combinations cross ten copy/swap/reference/union/member patterns,
one or sixteen repetitions, placement before/after LocalFree, three tails,
G6/G7 and O1/O2. They reduce to existing outputs and do not improve the bank.
Union trials are compiler diagnostics, not a new layout or identity claim.
The acyclic probes cross four narrow-load types, add/xor chains of length
0..31 and G6/G7. The adjusted probes cross byte/short, lengths 8..15,
G5/G6/G7, add/xor and six adjustments. No loop or alignment directive occurs.
Distinct counts overlap between families and must not be added.

## Actual c2 evidence

RTM c2 SHA256 remains
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
All addresses below are this DLL's preferred VAs. `inspect_nops.py.txt`
hash-checks it and reproduces bounded disassemblies and table findings.

The six-byte encoding rows at 0x108719C0 contain 0x90 for twenty opcodes.
Only opcode A9 is `nop`; the others are xchg, conditional-set and 3DNow
encodings whose operand/prefix handling must also be considered. This table
search alone is not a proof about all possible NOP emission paths.

Four immediate-A9 constructor sites call 0x107A7DD8. The two untraced native
sites were investigated further: 0x10734471 receives `(-offset)&3` from
0x10734092 (at most three bytes); 0x107C4D85 computes `(align-offset)&(align-1)`
and sets node flag 2. These are alignment-size calculations, not evidence of
sixteen one-byte NOP nodes. The existing measured A9 emitter uses the padding
table described in round4; one request of sixteen bytes is not 90 repeated.

Read-only Wine debugger traces now wait for c2 to load before installing a
conditional constructor breakpoint. Each retained trace checks that the
compiler actually produced its object. The positive loop control creates
one A9 node at 0x107A7EC9, size seven. At object +0x19 it emits
`8D A4 24 00 00 00 00` (`lea esp,[esp]`), the expected alignment padding;
Capstone calls this `lea`, not `nop`. The bank creates no A9 node and its
object has no NOP. No debugger write changes compiler code, data or instructions.

A different pass at 0x1082EE91 can insert a size-one A9 node at 0x1082F171.
Its caller requires global 0x108B025C nonzero, 0x108B0258 zero and settings
bit 0x02000000. Option descriptors identify `-Gmanaged` as writing
0x108A8060, which initialization copies to 0x108B025C. `/QI0f` controls the
settings bit. Native controls leave the global zero, even with `/QI0f`.
The pass also checks settings+0x1EC against 2 and 3; the trace records three
words starting at +0x1E8, so the middle word is this field.

`/d2Gmanaged /QI0f` reaches the pass. The managed diagnostic control reaches
the 33-byte-distance check, but its following concrete branch node is opcode
1A7, whereas the insertion logic tests generic 0F or data BB. It inserts no
NOP. These hidden-mode objects are not eligible native candidate bodies:
the control's final C3 byte becomes 01. The 36 option trials comprise
18 native objects, 12 hidden-mode diagnostic objects and six `/clr` setup
failures (C1108: missing alink.dll). `/QI0f /arch:SSE` is D2016 incompatible;
the accepted QI matrix omits SSE. These setup failures do not establish a
source/compiler impossibility, and no alternate toolchain was substituted.

## Retained bank, checks and resume

Keep the 219-byte bank, score **69/86 = 0.802326**, raw SHA256
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
Independent `variant.py` and the debugger-built object reproduce it.
Diagnostic masked comparison: prefix 205, 21 differences, first +0xCD.
Sixteen 90 bytes at +0xCD..DC and return-tail ordering remain unresolved.
There is no missing game callee or proof of an original post-link patch.
These finite trials do not prove that native C++ cannot produce the retail.

Copy the five `.py.txt` files to `build/trust237-round7/` without `.txt`.
Restore round5's `search.py` and `base.cpp` as its handoff describes. Copy
`qi-control.cpp.txt` to `qi-control.cpp`. Run coalescing.py, branch_padding.py,
branch_padding.py adjust, qi_modes.py and inspect_nops.py from the repo root.
`summary.json` preserves counts, setup errors and object hashes. The full
function closeness scores use diagnostic DIR32 masking, not relocation
admission. There is no new semantic-test claim for the hidden-mode objects.

For debugger reproduction, restore the saved padding/managed controls to
scratch `.cpp` files and run trace_nops.py SOURCE NAME (add `--detail` for
the managed control). The script adapts the existing tracked Wine helper.
The three saved trace JSON files record source hashes and guard/node values.
All compiles use isolated objects, never `build.compile_source`.

Do not rerun these matrices unchanged. Following the size-one insertion path
further requires evidence of how a native generic 0F branch survives to it;
passing `/QI0f` alone does not activate the pass. The target itself has no
0F-prefixed instruction or conditional branch. Neither this path nor ordinary
alignment currently explains its NOP run.

Ledger checks pass. The BFME1 freshness lock is live under `claudec2`, so this
seat skipped updating it and wrote no success timestamp. The claim is released
on banking. Preserve unrelated untracked `reverse/zh_sweep/`.
