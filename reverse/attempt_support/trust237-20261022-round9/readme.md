# 0x237D3D: alternate front end, unmanaged annotations and hint encodings

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, extent 226.
Previous handoff: `../trust237-20261022-round8/readme.md`. Inputs: BFME2
`768da5bbf2`, committed/checked-out BFME1 `42bba2ddbd`. Model: GPT-6.1-sol.
No Code, ledger, pin, gate or compiler binary changed. Target identity,
legacy WinTrust layouts and boundary remain the retail facts recorded earlier;
the compiler experiments below establish no original source/provenance claim.

## New hypotheses and finite results

Read the per-RVA history through `pick-hard --rva`, the previous handoffs
and relevant recipes before editing. Prior seats concretely tried control
flow, lifetime/scope, types/layout, callee visibility/inlining, compiler
settings, reference/twin searches and compiler padding paths. Those finite
matrices must not be rerun unchanged. This session tests three gaps:

| Family | Successful final compiles | Distinct raw bodies | Result |
| --- | ---: | ---: | --- |
| C / C++ / extern-C C++ front ends | 288 | 28 | All 96 triples have identical code **and relocations** |
| Native/unmanaged annotations and hidden backend mode | 96 | 12 | All 24 groups ignore the four annotation choices at byte level |
| Pause and fence intrinsics | 96 | 48 | No unprefixed NOP; every pause retains F3 |

The C front end is a separate c1.dll route, rather than another C++ linkage
choice. Cross four unsigned identities, three return/control shapes, nested
versus hoisted C89 declarations, O1/O2, G6/G7 and the three front ends.
Imports retain their real C linkage in all final inputs. Initial plain-C++
trials mistakenly mangled the API declarations: corrected and recompiled only
those 96. Final totals exclude the superseded 96 and contain no unresolved
REL32. This setup correction did not improve any body.

The annotation family crosses bank/probe, O1/O2, G6/G7 and native/hidden
Gmanaged/hidden Gmanaged+QI0f. `#pragma unmanaged` and managed-then-unmanaged
leave the hidden-mode output unchanged. All 64 hidden-mode outputs still
end in 01 instead of native RET C3; they are ineligible diagnostics and were
not emulated as native functions. `managed(push,off)`/`managed(pop)` are
unsupported syntax in this compiler (C4081 in 24 trials), so those cases
cannot establish a working mixed-mode configuration. The supported plain
annotations also fail to recover a valid native return under hidden mode.

The hint family crosses pause/SFENCE/LFENCE/MFENCE, 1/8/16 repetitions,
G3/G5/G6/G7 and O1/O2. All 24 pause variants emit exactly their requested
number of F3 90 instructions; no CPU setting drops the prefix. Fences retain
their real opcodes. These diagnostic additions cannot supply the sixteen
retail 90 bytes. A pause variant's 20 positional differences versus the bank's
21 is not a bank improvement: it still has the same 69/86 matched mnemonics
and adds different instructions with no target provenance. Keep the bank.

## Verification and retained bank

Independent `variant.py` compilation reproduces 219 bytes, masked prefix
205 (+0xCC inclusive), 21 diagnostic positional differences, raw SHA256
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
Retain score **69/86 = 0.802326**. Sixteen 90 bytes at +0xCD..DC and the
increment/restore ordering are still unresolved. No exact admission or new
linking improvement is claimed; no missing game callee was identified.

All inventories and raw hashes were checked sequentially after the parallel
compilations. The emulator independently resolves relocations by symbol,
checks the 288 front-end objects, sixteen native bank controls and bank
(305 objects, 28 distinct code/relocation groups). **17,696 executions pass**:
158 status samples times four LocalFree return/argc combinations per group.
Checks cover return=1, stack/ABI, caller-saved clobbers, exact API order/counts,
GUID, file16 and data44 fields. Inlined memset is permitted and its results
are checked at WinVerifyTrust. Hidden-mode and hint diagnostics are excluded.
These tests and diagnostic relocation masking are not the full byte gate.

`summary.json` retains compact receipts and compiler hashes including c1.dll.
Restore the three `.py.txt` scripts without `.txt` under build/trust237-round9.
Run frontends.py with frontends, mixed, hints; independently run variant.py on
the retained bank with `_memset=0x6291AE`, `_WinVerifyTrust@12=0x655652`;
then emulate_frontends.py and summarize.py. Drivers read the tracked round5
base and round7 probe, use eight private compiler objects, and never touch
the shared match cache. The emulator uses round4's scratch Unicorn install.
Full scratch results/objects are disposable. Do not repeat these matrices.

Ledger and Python syntax checks pass. The published link-index fetch succeeds.
Current link prediction confirms VersionDestructor.cpp already links (1,275
bytes); VersionInitGlobals.cpp remains blocked by this symbol (200 bytes).
This corrects the older assignment total; it is not a new linking improvement.
BFME1 freshness remains delegated under the live `claudec2` update lock; this
seat skipped the update and wrote no success timestamp. Preserve unrelated
untracked reverse/zh_sweep/. Release the claim on banking. Continue this same
assignment; these finite negative trials do not prove that a C++ match is
impossible or establish a post-link patch.
