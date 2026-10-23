Living World army-mover vector-growth linkage, 2026-10-19

Base 44cfe0e99a50e91fa88730e2c6a261f87465e92b. Published index: 495c0e1789, 2026-10-19 01:53,
retail-truth-2. link-proof.json records the index hash and paired object hashes.

The native 20-byte vector growth worker at 0x59B809 is complete 189-byte
STLport 4.5.3 allocate/copy/construct-or-fill/copy-tail/release/set code, without
an internal cleanup-and-rethrow path. The army mover emits a 244-byte version
with that additional EH path. The first library provider also emits a wrong
catch-enabled copy, so even the existing exact owner is selected incorrectly.
These are code-generation element views, not newly recovered application types.
The native owner and direct callers already establish the 20-byte stride, five
arguments and all six call destinations; no new layout or name is inferred.

Use the native owner's existing _STLP_NO_EXCEPTIONS configuration for the army
mover's STL headers while retaining /EHs for its C++ object lifetimes. The first
library provider needs a type-local no-catch growth specialization instead:
other element copies in that file have native cleanup paths. It retains the
unchanged vendor growth/copy/fill/release algorithm, with the omitted catch
block justified by the whole native 189-byte body and its lack of an EH frame.
No shared header, alias, pin, ledger ownership or verifier changes are needed.

Object proof reads the normal-gate-built COFF objects without recompiling.
The library specialization, army-mover copy and existing dedicated provider
all equal the entire native 189 bytes with every call relocation resolved.
Each changed object changes exactly one external COMDAT, the growth worker;
2,261 other retained COMDAT bodies/normalized relocation digests are unchanged.
Strong bindings are unchanged, no new undefined binding, import or unresolved
name appears, no retail-equal copy regresses, and removed exports leave no
newly missing matched foreign caller in the same-index graph.

Controlled current-object legacy preview across the eight-unit growth cohort:
ten findings removed, none added; the army mover (3,921 nonpadding bytes) and
the dedicated worker (189) become clean, LINKED 0 -> 4,110. Six other units
retain independent blockers. This is neither a closed-strict measurement nor
a full executable link. C++ exact coverage is unchanged.

Validation: 175/175 bodies across eight sources, all 16 EH graphs EXACT;
seven literals plus one empty reference, fourteen float literals and ten
imports verified without baselines/skips. Both provider units have strict
reusable receipts (152/152 rows). The army mover's existing parent-traversing
include is outside the strict inventory roots, so it has ordinary byte/EH
proof, not a strict receipt. Frozen-definition and CSV checks pass. Placement
rescans of both edited files find zero bodies and zero pins. Normal hooks run.

Rejected trials, retained here to avoid repetition: an early growth declaration,
extern template and late extern template each preserve seven of eight scoped
rows but move one store around two pops in the 779-byte 0x59C631 caller.
A global _STLP_NO_EXCEPTIONS setting in the broad library file fails 17 of 151
rows, including native copy-constructor EH handlers; it was fully discarded.
The final specialization preserves all those original rows and exception graphs.
Scratch trial sources, original objects and diagnostic logs remain under
build/local-macos/link-next-c-20261018; the final accepted source is this commit.

Required BFME1 scan/ranked/near/lift and ZH match/packets lanes refreshed at
verified BFME1 a18d9ed5. Ranked donors and ZH packets are zero; existing near
leads remain separately blocked. Reviewed existing provider-binding practice
including BFME1 67f4eab2; its private-helper rename is inapplicable to this
native template call. The library source and existing BFME2 native owner
supply this repair, with no donor ABI or target class identity substituted.
