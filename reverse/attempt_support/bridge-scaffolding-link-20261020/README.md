Bridge scaffolding provider repair, 2026-10-20

Legacy paired preview frees 1,843 existing nonpadding matched bytes in
BridgeBehaviorCreateScaffolding.cpp (complete native 1,851-byte row at
0x00457737). Authored byte growth is zero. The old present-unmatched ZH body
in BridgeBehavior.cpp used a different layout/ABI, emitted a second strong
definition, and won link order despite being proven nonretail. Remove that
obsolete body and its stale marker so calls resolve to the rowed BFME2 body.
The same original unit already delegates its other reconstructed bodies to
separate retail-specific units. The new provider remains byte-for-byte unchanged.

Acceptance: ./build.sh passes the original unit's 2/2 rows; both original and
retail provider pass link_check.py --prepare-current, 3/3 rows total, with
string/float/import checks. find_declared_unmatched.py and diff --check pass.
Paired in-memory link preview on index 5366c4f808 (2026-10-20 12:21) changes
provider findings from duplicate + wrong_selected to none; both self-strict
receipts are current. Closed-strict gains were not measured. No ledger, pin,
header or verifier changes; no census or full link cycle.

The 62-byte original unit still has independent unresolved AudioEventRTS destruction,
DISABLEDMASK_NONE and UpdateModule crc, plus BehaviorModule memory-pool,
List_base and UpdateModule phase COMDAT conflicts. These require their own
class/provider reconciliation; this patch does not claim that unit now links.
Current BFME1 donor 92f6bbe8 was reviewed as documented in the formation-preview
handoff; this uses BFME2's already verified target-specific replacement.
