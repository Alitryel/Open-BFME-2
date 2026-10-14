# Remove incidental vector clear link blockers

At source commit f356629e3068ba7b392adf9beb56d53a2ad2d840, the three consumers below each had one current local link blocker: their unused `vector<void*>::clear` COMDAT differed from the first copy in link order. The unchanged census was measured at 147cfae2cb, 2026-10-14 07:27; its SHA256 is recorded in object-proof.json. No per-row data-back artifact or closed-strict measurement was used.

| Consumer | Existing parent RVA | Parent bytes | Local LINKED before → after |
| --- | --- | ---: | ---: |
| Common/Rva00240E18Reset.cpp | 0x00240E18 | 164 | 0 → 164 |
| Common/Rva00214A8AClear.cpp | 0x00214A8A | 61 | 0 → 61 |
| GameLogic/Object/WeaponXfer.cpp | 0x002CDD47 | 579 | 0 → 579 |

The result is **804 existing authored bytes enabled in the legacy local preview**, with no new recovered coverage. Weapon also owns the existing 25-byte unwind row at 0x00777166: all four rows (829 bytes) pass the normal byte gate. The preview's authored-parent accounting excludes that funclet.

## Supported change and object proof

The included vendor/stlport/stl/_vector.h implements `clear()` as `erase(begin(), end())`. Each consumer already uses dllimport+forceinline specializations for begin/end to avoid incidental per-unit COMDATs. Apply that established pattern to clear, keeping its STLport operation and every call site intact. MSVC emits no imported clear reference: all external undefined bindings remain unchanged. Existing erase providers and call relocations remain intact.

Before and after objects were saved under ignored build/vector-clear-link-20261014. The proof compares every retained COMDAT's full bytes, relocation digest and size; non-debug section bodies and relocation targets; and external definition/reference bindings. All retained bodies, sections and bindings are identical. Reset and Weapon lose only the unused clear definition. The 61-byte cleanup additionally loses four unused STLport copy/destroy helpers exclusive to that discarded wrapper. No definition, reference, datum, pin, alias or alternative-name directive is added. Debug/symbol labels are allowed to renumber; Weapon's parent EH verification independently binds the existing unwind row to the renumbered label.

Target facts and identity remain those already recorded in the ledger and source. This repair changes no inferred class layout, original-name claim or retail boundary. In particular, the address-derived reset class remains unidentified.

## Acceptance

- `./build.sh` on the three explicit units: four of four rows exact, literal/import checks pass.
- `link_check.py --prepare-current` on the same units: three current strict reusable compile receipts and four of four rows exact. These are self-strict compile/byte receipts, not closed-strict LINK evidence.
- `link_check.py` on all three current objects: three of three link cleanly against the same index, 0 → 804 existing authored bytes. Before logs cover all three units separately.
- `eh_verify.py WeaponXfer.cpp`: one EH parent EXACT, no baselined or missing-object rows.
- `link_check.py --new-variants`, `class_gate.py`, `find_declared_unmatched.py`: pass for all three units.
- `data_check.py --converged`: three sources, eight addresses, no second names or unjudged rows.
- `place_bodies.py` on the repaired units: zero bodies and zero pins; no incidental recovery claimed.
- `check_csv.py`: 88270 function rows, 17019 symbols, 425 data rows valid; `git diff --check` passes.

The census/index/status files remain unchanged. No full link cycle, nightly, boot run, or census build/measurement/history was started. A new runner census and any closed-strict/runtime verification remain outstanding.

## Scope sweep and donor review

The index contains 50 copies of this clear name and lists 43 authored consumers blocked on it. `cohort.json` records their blocker counts; the full blocker names remain in the ignored local cohort snapshot. These three are the entire sole-blocker cohort. The remaining 40 units retain distinct unresolved names, competing providers, data/address debt or other COMDAT blockers; no broader linking gain is claimed. Removing an unused copy in these later consumers does not change the earliest selected provider or the bytes used by other consumers.

The dedicated donor pass reviewed BFME 1 at the committed, verified revision 23b143233b5a8664a3bdf8572df6d905c310a5a1. Donor d2e21369067f2f2c762c1c7ec2792c75f1ecf53d removes seven incidental string-constructor wrappers; de59a7e9f891b3ed2d4221d151ca881f4b75a583 harmonizes Apt predicate copies. Their incidental-COMDAT diagnosis is applicable, but their types/layouts/bodies are unrelated and were not imported. This local STLport specialization is supported by the included header and the target objects themselves.

Official master was fetched and is newer (a7c38d3b2597121f178ab5190b3062478823257d). Another live seat owns file:reference/open-bfme-1, so the verified pointer was retained, with no success-stamp update. Its comparative full verification remains that seat's work. The committed pointer's prior full verification is documented in BFME 2 commit 9b6bf3e581.
