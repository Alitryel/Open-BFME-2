# 0x758DE0: dispatch qualifications and surrounding functions

Continue the same assignment. The bank is unchanged: **333 bytes, zero
relocations, 31 positional differences, 308/333 complete instruction-pair
bytes aligned** (score 0.924924924924925). Independent compilation reproduces
SHA256 `01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
No body landed and no production source or ledger row changed.

The remaining test and first-response windows are still wrong. The bank's
reverse-only fastcall pair is an **unproven ABI diagnostic**. The retained
uniform-interface control is 333 bytes / 41 positional differences / 302
aligned bytes. These experiments establish no original callback type or
new class identity.

## Preparation and existing negative evidence

Input HEAD was `1332d6907154a70569129b8c89009f7c56c6f147`, over origin/master
`d3c58ecca8f4ddb0c257bd8830222672746acf82`, preserving the preceding unpublished
aggregate evidence commit. The checkout was clean. Read AGENTS.md, the
per-RVA history through pick-hard, recipes, the original vcall packet and
the lowering, local-register, source-shape, rounds, interference, edges and
aggregate handoffs before editing. Those already disprove the recorded
control-flow, scope/lifetime, real-header/layout, callee visibility and
compiler-setting families. They were not repeated as new hypotheses.

Claimed the assigned RVA. Ledger checks passed (98,096 functions, 15,853
symbols, 2,139 data). Fetched/reused the published link index. BFME 1's clean
checkout equals its committed pointer `f890413e75e671748215ba2ef3304aa7953993e9`.
The fresh update lock belonged to codex4, so no update or freshness-success
record was made. No maintainer-only runner or broad queue was started.

Compiler inputs are in `inputs.json`: stock RTM c2.dll 13.10.3077,
`/O2 /MD /EHsc /I.`. All experiments used private objects via compiler_command,
not the shared match cache. Native extent remains 0x758DE0..0x758F2D, 333 bytes.

## New hypotheses and results

All **16,364 corrected variants compiled successfully with zero relocations**.
None is exact and none improves the full bank. The compact `summary.json`
records complete `(mnemonic, operands)` alignment and regional winners.
Search.py's separate mnemonic-first metric is not the bank score.

| Family | Compiles | Distinct bodies | Hypothesis |
| --- | ---: | ---: | --- |
| context | 256 | 1 | The rotating local-register cursor might retain state from preceding functions. Eight function shapes, eight counts, before/after placement and inline/noinline models all reproduce the bank. |
| dispatch | 8,192 | 660 | Explicit one-word member-call tables with independently ordinary, volatile-vptr or volatile-slot reads at all six calls; bank and uniform controls. |
| floating | 2,916 | 66 | Scalar float arguments to ordinary/fastcall callbacks use stack slots rather than EDX; exact pointer-bit copies by union or intrinsic memcpy, six independently selected sites and both controls. |
| freecall | 5,000 | 131 | Does a C function-pointer target fold differently from a member-pointer target? Four first-test/response occurrences independently select ordinary/volatile reads; four argument-pack constructions and both controls. |

The context hypothesis has a static countercheck: the local allocation driver
at c2+0x75782 clears the holding array and writes 0x108a9738 to its cursor at
+0x75844. Another reset exists at +0xdff94. `cursor-reset.txt` preserves the
first sequence. This is static inspection plus the compiled context controls,
not a newly traced execution of every reset path.

Explicit volatile **slot** reads can put the first-response vptr into EAX
after both pushes, just as retail does. However, the tested lowering then
emits a separate `mov edx,[eax+0xc]; call edx`, rather than retail's
`call [eax+0xc]`. The complete response region rises from 19 to 27 aligned
bytes, but the prefix loses bytes and the whole body is worse. In particular:

* dispatch/v00384 uses the volatile-slot prepare only in the first response:
  335 bytes, 131 positional differences, 298 aligned bytes. The target load
  is late but the source/data register roles and the extra call instruction
  remain wrong.
* dispatch/v08064 also applies volatile-slot member dispatch to both test
  calls: 333 bytes, 86 positional differences, 289 aligned bytes. It obtains
  the same 27-byte response region while losing the test's outer-table cache.
* freecall/v3720 reproduces that same full-body hash using C callback pointers.
  Changing the target representation alone does not remove the extra load.
* freecall/v3120 raises the test's small region from 13 to 14 aligned bytes,
  but loses the prefix and does not solve the test. It is retained only as a
  diagnostic, not a stronger bank or a legal source splice.

`call-windows.txt` and four selected source texts preserve those distinctions.
The floating models produce no new regional winner. Every family's best
whole-function output is the unchanged bank. Initial context sources had 32
malformed inline forwarding expressions; they were corrected and all 256
cases were rebuilt. An initial dispatch generator stopped on an inconsistent
control spelling; only the complete corrected 8,192-case run is counted.

## Continuation and reproduction

Do not repeat surrounding-function padding, these dispatch qualifications,
float-bit callback parameters or the member/free target comparison unchanged.
The late-vptr controls now provide a concrete comparison for earlier virtual
call lowering: they obtain the desired lifetime but lose memory-call folding.
Investigate the ordinary virtual-call representation before c2+0x73108, using
the previous lowering packet's checkpoints. Decode its argument linked lists
as high-level operands rather than applying post-lowering field meanings.
The useful question is how to obtain the short, late target lifetime with an
ordinary nonvolatile virtual call while retaining the outer-table cache and
retail's return push/reload sequence. No missing callee or external prerequisite
was identified; no blocked-on RVA is justified.

Copy `.py.txt` and `.cpp.txt` files to a fresh directory directly under build/,
dropping `.txt`. Run each named generator and `search.py FAMILY` (eight private
workers), then `regions.py context dispatch floating freecall`. The generators
read bank.cpp and uniform-control.cpp. Reconfirm either control with
`tools/variant.py <source> bfmeTwoCGD 0x758de0 333`. `independent-checks.json`
records this session's separate variant.py controls. Script syntax, ledger,
path-case and whitespace checks accompany the evidence commit. The best body
is re-banked unchanged and the claim released for the next session.
