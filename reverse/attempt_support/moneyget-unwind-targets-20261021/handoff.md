# Three wide money_get cleanups: strict relocation blocker

Targets: `0x0075BF13`, `0x0075BF48`, `0x0075BF67`, each 31 bytes through
its terminating `ret`. No new matched bytes or function ownership landed.
The parent is the already recovered wide `money_get::do_get(string)` at
`0x00012190`, in
`Code/Libraries/Source/WWVegas/WWLib/stlport_wide_money_get_string.cpp`.

## What changed since their old attempts

Their last individual notes said the parent was a gen-dump. That is obsolete.
The normal source build now passes 4/4 existing rows. The parent's EH graph
verifies EXACT and independently places these compiler-local labels:

| Retail RVA | Label in the tested object | State bit | Local |
| --- | --- | --- | --- |
| 0x0075BF13 | $L17612 | 0x08 | EBP-0x24 |
| 0x0075BF48 | $L17618 | 0x10 | EBP-0x48 |
| 0x0075BF67 | $L17620 | 0x20 | EBP-0x60 |

However, strict `build.compile_function(..., allow_weak=False)` comparisons
fail for all three. Every non-relocation instruction agrees. The branch at
offset 26 resolves to **0x00142D70**, whereas retail jumps to **0x0000B3C0**.
There are no unresolved symbols. An EXACT parent EH verdict alone does not
prove these calls: `eh_verify` masks relocation operands while checking the
graph. [strict-verification.json](strict-verification.json) preserves the
resolved and native disassembly, complete extents, parent/source/object hashes
and tested base revision.

## Existing identity prerequisite

The current ledger names the 14-byte body at 0x142D70
`basic_string<wchar_t>::~basic_string` and the 63-byte body at 0xB3C0
`_String_base::~_String_base`. The generated complete-object cleanups therefore
resolve to 0x142D70 under today's names. This directly reproduces the identity
problem already established from constructor/complete-object unwind states in
[df20-funclet-naming-20261021/handoff.md](../df20-funclet-naming-20261021/handoff.md).
That packet contains the independently tested corrected owner form and the
coordinated repair plan; do not invent a second pin or alias to route around it.

That earlier packet also measured that an isolated identity swap would regress
ten linked units, approximately 19.3 KB, because their emitted wide-string
destructor copies disagree with the corrected provider. The prerequisite is
the documented wide-string identity/class reconciliation, including affected
callers and COMDAT copies. It is not the missing parent anymore. Do not use
`blocked-on=0x00012190`: that parent is already matched.

## Trials excluded in this batch

All were private `variant_search.Scorer` trials; no production source changed.
Every variant that kept the parent and its EH graph exact still failed the
three strict cleanup comparisons:

- Vendor-equivalent explicit wide basic_string destructor, with forceinline,
  nothrow, dllimport and dllexport combinations; empty scalar-character
  teardown specializations; `throw()` specifications.
- `/Ob2`, `/Oi`, `/d2ehopt`, inline depth/recursion pragmas, `_STLP_NO_EXCEPTIONS`,
  `/EHs`, `/GX`, `/EHc-`. `/EHa` changed the parent and was rejected.
- Direct versus copy initialization, explicit branch/outer copies, and
  forced-inline conditional/if/named-result helpers for negative_sign,
  positive_sign and curr_symbol. Helper extraction changed the parent.
- Base-subobject reference views of the returned real string temporaries,
  singly and together: the parent could remain exact, but destructor calls
  still resolved to 0x142D70.
- Pinned compiler profiles: SP1 changed the parent; DDK4035 preserved its
  text but produced an EH relocation-placement conflict.

[trial-summary.json](trial-summary.json) records the tested families and their
outcomes. Repeating these unchanged source forms will not fix a name mapping.
The useful next work is the existing coordinated identity repair, followed by
reverification of these three complete cleanup bodies with their calls resolved.

Inputs: BFME 2 `de52e089b67f36497dfef0f17c8a91739bd732b4`; BFME 1
`a80da2e3be84ebdb3b6bc280faca3f99a44788af`; pinned default MSVC 7.1;
source flags `/Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC`.
Approximately 15 minutes shared across the batch; model: Codex (GPT-6 family).
