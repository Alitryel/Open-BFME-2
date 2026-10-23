# SpecialPower lookup accessor emission repair

BFME2 source base: `8f2b844a0683f72bc60df9fdabdc7d4b33b82e26`. Frozen runner census index: `ac77c85054`, 2026-10-15 14:25 UTC, SHA256 `a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`. The published-index fetch retained this same local index. No index, census status or history was rewritten.

`SpecialPowerStoreFind.cpp` emitted an unused nine-byte external copy of `SpecialPowerTemplate::getID() const`, digest `1ae4b752f2bd`. Its only reference was from `.debug$F`. The first indexed copy, in `INIParseSpecialAbilities.cpp`, is digest `14f7f5722e26`. Neither helper has a retail address: this is an upstream first-copy finding, not independent proof of either helper's target identity.

The two existing views have different purposes: the lookup view follows the final override before reading +0x14, while the INI view reads +0x14 after its caller already resolved the final override. Adding `__declspec(dllimport) __forceinline` to the lookup accessor preserves that complete visible expression while suppressing its unused standalone copy. No common identity, layout, address or ABI is asserted beyond the existing recovered source. No pin, alias, shared header, compiler setting or allowance is added. The source file was claimed before editing.

## Paired preservation and link evidence

Both sources have self-strict reusable receipts before and after. The unchanged INI witness is byte-for-byte identical. The consumer removes only the nine-byte accessor COMDAT and its external definition. All 11 retained COMDATs and all retained nondebug sections preserve bytes, sizes, flags, symbolic relocations, external bindings and directives. Local relocation targets are compared by section contents and offset, normalizing compiler label numbers. No nondebug relocation references the removed function or section, and no imported call is added.

`proof.json` records source/object/receipt hashes and the complete before/after findings. The ignored `build/specialpower-id-link-20261015/proof.py` compares saved strict before objects against strict after objects, refreshes only these two objects into separate in-memory copies of the same frozen index, and checks data findings as well. The witness's selected vector push_back blocker remains unchanged.

Local legacy prediction: the lookup unit changes from one COMDAT finding to zero and LINKS 0 -> 184 existing nonpadding retail bytes. The consumer-only prescribed CLI exits 0. The paired CLI exits 1 solely because the unchanged INI witness retains its vector-provider selection finding. Authored C++ growth is zero. Closed-strict closure and full-link gains were not measured; committed link status is unchanged.

## Acceptance and scope sweep

- Bounded strict preparation: 4/4 matched rows across consumer and witness before and after.
- Explicit edited-source byte gate: 3/3 matched, with string/float/import checks.
- EH: one EXACT, no nonexact or missing object.
- Enforced data check: zero findings across both sources; converged data: eight addresses, zero second names or unjudged rows.
- Declared-definition and class gates, no-new-variants, ledger validation and whitespace checks pass.
- Placement resweep: zero additional bodies or pins.

The frozen index has only these two accessor copies. Removing the losing copy drains this supported emission pattern in the index. The remaining INI vector-provider issue is independent and untouched. No maintainer-only runner was started.

## Donor review and remaining freshness dependency

Clean committed BFME1 checkout: `a7c38d3b2597121f178ab5190b3062478823257d`. Reviewed repairs `53d32d6b4b377317a3397971629ca3ad20b870e9` (Apt constructors) and `c1315665a1b22beb7e6d9279548fe5b1c26ed1f9` (DamageInfo constructors). Their unused-COMDAT suppression mechanism applies locally; their types, layouts and identities are not imported. BFME2 byte gates and complete object preservation establish the result independently.

Initial fetch found official BFME1 master at `df3816cb` while another live worker, `codex-6bc6-20261008`, holds `file:reference/open-bfme-1`. The retained verified inputs are preserved. No freshness-success stamp or pointer advancement is claimed; comparative update verification remains with that worker.

Reproduction: at the recorded source base, strictly prepare these two sources and save their source/object/receipt files using the original object basenames; apply this patch, strictly prepare again, and compare all nondebug object facts and local link results against the same frozen index. Before objects and receipts remain ignored under `build/specialpower-id-link-20261015/before/`.
