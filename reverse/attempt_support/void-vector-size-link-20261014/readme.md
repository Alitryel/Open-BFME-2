# Pointer-vector accessor link repair

Three consumers emitted optimized standalone STLport `vector<void*>`
accessors that disagree with independently rowed retail bodies in
`stlport_vector_voidptr.cpp`. File-local `dllimport`/`__forceinline`
specializations retain the standard pointer-range calculations while preventing
these consumers from emitting competing definitions. No new import reference
is emitted. Compiler flags, row names, donor provenance and function bodies
remain unchanged.

The retail `size()` provider is the 25-byte body at 0x00023BC0, compiled with
the existing `/Od /Ob1` settings. Both provider and consumers pass their normal
row byte gates and have current self-strict reusable receipts. Target identity
and extents remain those of the existing ledger; the STLport declarations
establish accessor semantics. No new identity or layout is inferred.

## Measurement

Base checkout: 4b653c38d0 (full revision in object-proof.json).
Index: 147cfae2cb, 2026-10-14 07:27; its SHA-256 is recorded in the proof and
remained unchanged. Committed link_status.csv belongs to another measurement
and is not used as gain evidence. Both before/after previews refresh the same
four-object cohort in memory against this index.

| Consumer | Before | After | Existing bytes passing local preview |
| --- | --- | --- | --- |
| LivingWorldPlayerRegionMembership.cpp | One size COMDAT finding | Clean | 0 -> 74 |
| Rva009D7350BktNumKey_Rva0060c9a7.cpp | One size COMDAT finding | Clean | 0 -> 58 |
| LivingWorldRegionManagerCompleteBattle.cpp | Ten COMDAT findings | Six findings | 0 -> 0 |

Six conflicting definitions disappear across the consumers. Every retained
COMDAT's complete bytes, extent, digest and relocation bindings remain exact.
Ordinary nondebug sections, directives and external bindings also remain
identical, apart from removed definitions. SafeSEH `.sxdata` entries contain
COFF symbol indices: those numbers move, but resolve to the same unchanged
handler and are normalized by symbol identity in the comparison.

The standalone provider's object is unchanged and retains its eight independent
local findings: vector assignment duplicate/wrong-selected, const subscript,
allocator constructor, erase, `_M_set`, assignment and `_M_allocate_and_copy`.
The region consumer retains exactly its six existing `vector<const ModuleData*>`
findings: allocator/proxy deallocation, `_M_clear`, `_M_allocate_and_copy`,
`_M_insert_overflow` and `reserve`. These need separate supported repairs.
LivingWorldUpgradeListHelpers.cpp shares the size symptom but is claimed by
another contributor and was not edited.

This is a **legacy local preview gain of 132 existing matched bytes**, with
current **self-strict receipts** for all four objects. New authored retail
bytes: **0**. Closed-strict closure, actual link-cycle gains and a new census
measurement have not been established.

## Acceptance

- Bounded `link_check.py --prepare-current`: all four receipts current.
- `./build.sh` across consumers and provider: 27/27 rows pass; string, float
  and named-import checks pass.
- COFF comparison and same-index before/after proof: pass.
- Paired local `link_check.py`: two consumers clean; unchanged provider and
  remaining region findings give the expected exit 1.
- `link_check.py --new-variants`, `class_gate.py`,
  `find_declared_unmatched.py`: pass.
- `data_check.py --converged`: no second names or unjudged rows; shadow data
  check has zero findings.
- `eh_verify.py`: no matched EH data; `place_bodies.py`: no bodies or pins.
- `check_csv.py` and `git diff --check`: pass.

Saved original objects/sources and the comparison script remain in ignored
build/void-vector-size-link-20261014. Committed object-proof.json records the
removed and retained bodies, bindings, receipts and exact preview findings.

## Reference review and outstanding verification

Retained BFME 1 pointer: a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed donor repair de59a7e9f891b3ed2d4221d151ca881f4b75a583: separating
incidental helper copies from retail ownership applies here. No BFME 1 code,
types or layout were imported; existing BFME 2 providers and caller byte gates
are the acceptance evidence.

The prior session's BFME 1 freshness update remains blocked: fetched master
58ab850fd1f734e310048b2e19c1ecb7ba112a3f required a full old/new gate that
stalled refreshing thousands of dependencies. That unchanged blocker was not
retried. The retained pointer and successful-check stamp were not advanced.
No full census, link cycle, nightly or boot runner was started.
