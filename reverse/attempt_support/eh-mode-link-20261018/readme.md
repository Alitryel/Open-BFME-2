# Exception-mode helper link repair, 2026-10-18

Same-index current-object legacy preview: **+613 existing C++ bytes linked**, no authored C++ growth.
The index is the published 2026-10-18 11:36 census at c2c5ac8c27; these are explicit current-object predictions, not a closed-strict or full-link result.

| Unit | Before | After | Gain |
|---|---:|---:|---:|
| UpgradeCenterFindUpgradeByKey.cpp | 0 | 375 | 375 |
| Rva00359290Dtor.cpp | 0 | 165 | 165 |
| Rva002B8817Filter.cpp | 0 | 73 | 73 |
| LivingWorldRegionAwardDispute.cpp (unchanged provider) | 427 | 427 | 0 |

Before measurements are in upgrade-before.txt, sweep-before.txt and filter-before.txt; after.txt checks all four together. The sweep log also records independently blocked siblings, not gains from this repair.

## Established cause

The three consumers compiled with /EHsc. Their referenced STL helper copies omit a four-byte exception-state store, `83 4d fc ff`, present with /EHs. UpgradeCenter and the filter emit a 236-byte vector<Rva004DFCB0Element>::_M_insert_overflow, while the kept fxshaderasset.cpp /O1 /EHs copy is 240 bytes. Rva00359290 emits a 52-byte AsciiString/NamedTimerInfo tree destructor against the rowed 56-byte retail body. Comparing complete helper bytes and relocation names isolates this EH-state difference. Changing only /EHsc to /EHs makes those referenced copies agree while preserving every rowed native body, including handlers and unwind actions.

The filter additionally called 0x004FBED6 under the obsolete Rva004FBED6Call spelling. The existing provider identifies it as RegionAwardDispute::GetResolvableBy: its independent WorldBuilder source/name evidence and retail call graph are recorded in LivingWorldRegionAwardDispute.cpp. The consumer now declares that exact method and its int return, comparing the same 32-bit filter word. The filter's own class and remaining member meanings stay address-derived/unknown; no new layout or target identity is inferred from a placement. No alias, pin, vtable or global owner is added.

## Acceptance

All three changed sources pass normal source/body/data/string/float/import gates with strict reusable compiler receipts: 12/12 code rows, 2/2 data rows. One existing UpgradeCenter unwind label renumbers; the normal verifier resolves it through the unchanged parent's EH graph. See verified.txt and eh.txt. The provider retains 427 linked bytes in the paired prediction. No census was rebuilt, no status/baseline was rewritten, and no runtime/full-link or closed-strict improvement is claimed.

BFME 1 donor freshness was checked against official master. The verified gitlink remains 64d369b90170b7e9ec917d646f020b11f13eb0d5, while upstream is newer; another seat holds the reference update claim. This local compiler-mode and existing row-name repair does not import new donor inputs.
