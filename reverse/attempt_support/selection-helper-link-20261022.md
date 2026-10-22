SelectionTranslator helper ownership repair, 2026-10-22
=====================================================

Starting HEAD: 21387ea4c9. Published census: ae3b3e68e2,
2026-10-22 11:05. No census, full link cycle or status regeneration was run.

Paired current-object link_check.py previews of
Code/GameEngine/Source/GameClient/MessageStream/SelectionXlatTranslateGameMessage.cpp:
0 -> 4,145 nonpadding matched bytes, one whole unit newly links.
The original three row extents total 4,150 bytes including padding.

Before: const vector<void*>::operator[], the selection table's bucket-key
helper, and the selected allocator-proxy copy prevent linking. Preserve the
stock inline accessor and both one-argument bucket helpers using imported
forceinline specializations. Exchange only the stateless allocator proxy's
stored pointers, as already done by SelectionIDMap.cpp and Armor.cpp. This
eliminates the generic swap's reference to the wrong selected proxy copy.
The first trial merely declared that copy external: rows still matched, but
the selected provider remained wrong and the caller bucket helper then lost.
That trial was replaced, not accepted.

Acceptance: build.sh verifies 3/3 rows, float literal and import checks.
link_check.py --prepare-current before and after verifies strict reusable
object receipts; the paired ordinary preview after LINKS 4,145 B.
find_declared_unmatched.py and git diff --check pass. Hooks supply the staged
identity, class, data, EH, variant and ledger checks. This is a legacy-preview
gain with self-strict objects, not a closed-strict measurement or runtime proof.
No recovered-byte, new identity, layout, pin or global claim is made.

The same-name sweep found FXListStoreParse, SelectionIDMap, Rva0002C7FD,
ArmyDefinitionManager and StlSweepW4Rva0060CBAC already link with current
sources: inherited improvements, not credited here. ArmorStoreParse is claimed
by another seat. DamageFX_hashtableResize and stlport_hash_map_int_resize still
have independent blockers; continue that investigation separately.

BFME1 donor review uses retained verified 37c3022de1 and the earlier
20261021-bfme1-freshness-link-review.md. Native STLport headers and existing
matched sibling specializations supply the mechanism; no donor ABI is copied.
Official master fetched as 42bba2ddbd. A full baseline byte gate waited on the
host compiler lock without starting compilation; that waiting process was
cancelled. The submodule pointer and success receipt remain unchanged, and
the pointer-update claim was released. A later seat must complete freshness
verification when the full-gate compiler slot is available.

Untracked paired logs and original source are in build/link-seat-20261022e/.
