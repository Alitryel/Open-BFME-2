# Chain-pool destructor provider isolation

BFME 2 parent 718428f339; published census 11b3872700, 2026-10-23
23:06, retail-truth-4. Before editing, the current-object legacy preview of
Rva006CBF40Siblings.cpp excludes all 525 matched bytes. Seven local complete
destructors are proven non-retail copies: Rva006CC2F0, Rva006CD620,
Rva006D71B0, Rva006D71E0, Rva006E9B50, Rva006EC170 and Rva006FE430.

Preserve those seven class/helper blocks unchanged in Rva006CBF40Deferred.cpp
and repoint only their seven 35 B wrapper rows. They still need genuine
complete-destructor providers. Leave the other eight helpers in the original
unit, including the independently established nonvirtual checkpoint helper
at 6CEA60. The E176F4 chain-pool global stays defined in the original unit;
the deferred unit declares that same global. No symbol, address, ABI, class
layout, body, pool value, pin or compiler flag changes.

After: original unit LINKS 0 -> 280 B. This is a legacy per-file preview,
not self-strict or closed-strict closure or an executable link. The new
deferred unit is absent from the published census and its 245 B receive
zero credit. No local destructor has been suppressed or treated as a match.
The original B14 comparison is preserved in the preparation backup ref.

Both units pass 15/15 byte checks using strict reusable receipts; the one
data row remains byte-exact. CSV, declared-definition, string/float/import
and EH checks pass (no EH-bearing rows). Normal hooks check class, identity,
data and variant admission. Logs: build/link-chain-dtor-isolation/.
New authored C++ bytes: zero. No verifier, baseline, shared-header or donor
input changes. The reference review and unresolved submodule freshness
prerequisite remain unchanged; no donor ABI was inferred here.

Recovery at BFME 2 8847b96bb5 preserves upstream native-provider rehomes
for three former sibling wrappers, leaving five matched helpers (175 B)
in the indexed original. The refreshed legacy preview admits 0 -> 175 B.
The former 280 B figure belongs to the original ledger. Upstream already
repaired the B14 providers, so its isolation was removed; original evidence
remains in refs/runner/preparation/1792806564685037381. The seven deferred
wrapper rows and their genuine destructor prerequisites are unchanged.
