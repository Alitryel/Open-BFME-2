# InGameUI tree comparison ownership

At base a2839ea429, InGameUISuperweapons and InGameUIXfer emit unused external
STLport tree-base inequality copies incompatible with the selected copy. Both
already use local typed list comparisons. Add the corresponding existing BFME2
local tree comparison immediately after the map include. The comparison still
tests the two iterator node pointers; no layout, ABI, target identity, header,
compiler flag, pin, ledger row or data binding changes.

## Controlled result

The frozen runner index measures 825b86983f at 2026-10-15 12:37, with underlying
census 5986a99448 at 04:52. context.json records its SHA-256 and full source
revision. The committed status queue (28269d8e8d) is discovery evidence only;
no per-row data-back artifact was available or used. Published-index fetch
returned 404; the existing runner index was preserved and used unchanged.

Genuine original objects and dependency receipts were saved under
build/superweapon-tree-link-20261015 before each edit. Original scoped strict
preparation verified 14/14 superweapon rows and 9/9 save-game rows. Final strict
preparation verifies all 23/23, with two literals plus one empty-string reference,
no skipped or baselined references, and no float/import references. Both normal
per-source byte gates pass. All five EH graphs are EXACT, without baseline use.

| Consumer | Paired local findings | Identical retained COMDATs |
| --- | --- | --- |
| InGameUISuperweapons | 28 -> 27 | 211 |
| InGameUIXfer | 14 -> 13 | 198 |

The paired proof refreshes exactly these two objects into independent in-memory
copies of the same frozen index. Each consumer loses exactly the finding for
??9_Rb_tree_base_iterator@_STL@@QBE_NABU01@@Z; all other findings agree. Legacy
local LINKED stays 0 -> 0; new authored C++ bytes are zero. Strict reusable
receipts establish current scoped objects, not self-strict placement or a
closed-strict gain. No census, index or link status file was rewritten.

object-proof.json proves identical retained COMDAT bodies, extents and
relocation digests. Each 18-byte unused external comparison disappears. The
superweapon unit adds one and the save-game unit adds two 12-byte private typed
comparisons; every new helper and the removed helper have zero nondebug caller
relocations. Every other normalized nondebug section, relocation, external
binding and linker directive is unchanged. EH label renumbering is handled by
the ordinary parent EH proof; pins remain unchanged.

Data facts and zero data findings are identical before and after. Enforced data,
converged-data (eight addresses, no second names or unjudged rows), class,
declared-definition, new-variant admission, ledger and whitespace checks pass.
The two-source placement sweep returns zero bodies and zero pins.

The prescribed local link check still exits 1 for the remaining 40 findings,
fully listed in local-link-final.txt. Superweapon bookkeeping retains vector,
hash, pair-copy, tree-access and selected RadiusDecalTemplate provider conflicts;
save-game transfer retains ObjectID vector, pair-copy and iterator-increment
conflicts. Maintainer-only whole-link/boot verification remains outstanding.

## Lane and donor review

Started with repair_queue link and link_rank help/rankings. Rechecked stale
ranked candidates against current objects and credited none of their existing
repairs. Horde configuration, SkirmishAI and the BFME1 submodule are held by
other workers and were not edited. This is a bounded same-cause dependency
repair; no full census, whole-tree refresh, link cycle or boot runner was run.

Reviewed official BFME1 repair 66b19a8e95a4add525ef808fcea088e306798e2b,
suppressing incidental Apt allocation copies while preserving matched callers.
Its ownership principle applies, but its implementation and target addresses
are not imported. This change uses BFME2's established typed-iterator pattern
and independent target-object evidence. BFME1 verified gitlink and checkout
remain a7c38d3b2597121f178ab5190b3062478823257d; fetched official master is
8426edbe18b7fe0b14d0782e2c7425ab50f326c9. The overdue update remains under
another worker's live file claim with prior comparative-baseline blockers;
verified inputs and the old freshness stamp were preserved, with no false
success stamp.

Two independent destructor emission trials were restored and recorded blocked
in re_attempts.log: INIStatsRecordTextures introduces an imported EH destructor;
Rva002214A6Dtor either introduces an imported pair cleanup or changes retained
cleanup relocations. Their claims were released. Scratch originals and trial
evidence remain in build/ini-textures-link-20261015 and
build/nocase-pair-dtor-link-20261015. These are not credited repairs.
