# Vector assignment provider sweep

Three callers now declare their already-rowed STLport vector assignment
specializations instead of emitting alternate helpers. Each retail caller
already calls the named out-of-line provider; no element identity or layout
is inferred from the link preview.

| Caller | Target RVA | Legacy before | Legacy after |
| --- | --- | ---: | ---: |
| WeaponTemplateAssignRva002CD67C.cpp | 0x002CD67C | 0 | 1167 |
| Rva0030B92COpAssign.cpp | 0x0030B92C | 0 | 63 |
| Rva001DA379Copy.cpp | 0x001DA379 | 0 | 357 |

The shared `vector<BfmePod8>` assignment provider is rowed at 0x001D9BEE
in `stlport_pod_vector_malloc_bodies.cpp`. The third caller also uses the
existing `Rva001DA05ERecord` and `BfmeStringTailRecord156` vector assignments
at 0x001DA05E (`StlSweepR3Rva001DA05E.cpp`) and 0x001D9D75
(`StlportVectorAssignFamily.cpp`). Their declarations remove the callers'
competing assignment, allocation, copy and destruction helpers.

Acceptance:

- Paired `tools/link_check.py` previews against census 144ed0ccab
  (2026-10-20 15:34): three callers change from 0 to 1587 linked bytes.
- `./build.sh` passes all three caller rows, string/float/import checks,
  and source claims. `find_declared_unmatched.py` passes all three files.
- `link_check.py --prepare-current` verifies the weapon caller separately,
  then the other two callers and all three assignment providers (24 rows),
  producing strict reusable receipts.
- A combined six-unit legacy preview retains the +1587 gain. Two providers
  have separate existing link blockers; no closed-strict gain is claimed.

The 63-byte AreaPolygon caller belongs to this same-cause sweep. No new
authored C++ byte coverage, aliases, pins, or ledger rows are claimed.
