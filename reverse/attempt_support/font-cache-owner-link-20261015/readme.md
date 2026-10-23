# Font-cache global ownership repair, 2026-10-15

Three consumers now declare and reference BfmeFontCharsCache, the existing
byte-verified data_rows owner of the sixteen bytes at RVA 0x009E2084
(VA 0x00DE2084), instead of the undefined scalar g_Va00DE2084. Existing receiver
views, compiler flags, data definitions, function rows and pins are preserved.
The descriptive cache identity comes from the existing BFME2 recovery; the
original retail variable spelling is unknown. This repair does not assert a
new recovered identity or unify the private vector/destructor class views.

## Controlled link evidence

Base checkout 61f6ef8d7901bec2e2afea14e99469fa3a658b6e. Both preview phases use
copies of one frozen runner index, refreshed in memory with the three strictly
prepared consumer objects and the unchanged, strictly prepared cache provider.
context.json records its hash. Index update commit 19a2565407 (2026-10-15 09:33)
uses census 5986a99448 (04:52). The committed link-status queue measures
28269d8e8d and was used only for selection. No index or status was rewritten.

| Consumer | Existing authored bytes | Legacy link findings |
| --- | ---: | ---: |
| W3DFontLibraryDestructor.cpp | 106 | 3 -> 2 |
| Rva007ABEF3ArgCtorInits.cpp | 394 | 17 -> 16 |
| Rva007B6880Thunks.cpp | 9,068 | 74 -> 73 |

Each removes exactly the unresolved ?g_Va00DE2084@@3IA binding. The unchanged
191-byte W3DFontCharsCache provider has zero findings in both phases.
Legacy LINKED remains zero across the three consumers (9,568 existing authored
bytes, excluding 0xCC). New authored C++ bytes are zero. No self-strict,
closed-strict, census or executable-link gain is claimed. Strict receipts prove
the four objects current; they do not prove provider closure.

proof.py compares every nondebug COFF section and relocation, external binding
and linker directive before and after. Apart from the one declared owner-name
substitution, these are identical. MSVC local-label renumbering is compared by
actual target section and offset; the byte gate independently verifies the
renumbered font-destructor EH funclet. proof.json records object hashes and the
paired link findings. Saved originals, objects and receipts remain in ignored
build/font-cache-owner-link-20261015; scripts require these and the recorded
index. They are evidence, not gate replacements.

## Acceptance and diagnostic limits

- Strict preparation before and after: 937/937 matched rows across all four
  units, two byte-verified data rows, four strict reusable receipts. Explicit
  ./build.sh on the same four sources also passes 937/937. No literal/import
  checks are baselined or skipped.
- EH: one EH-bearing row EXACT, zero baseline or missing-object cases.
- New-variant admission, class, declared-definition and whitespace checks pass.
  Converged-data enforcement passes eight addresses, zero second names or
  unjudged rows. Placement resweep reports zero bodies and zero pins.
- Local link_check on the four current objects exits 1 for the remaining
  findings; proof.json establishes exactly the three removals, with all else
  identical. A --refresh invocation began unrelated global recompilation and
  was interrupted; it supplies no result. All four relevant objects were
  strictly prepared beforehand, so the bounded preview refreshes them directly.
- Shadow code-identity diagnostics remain four before and after.
- data_check --enforce is not passing: 49 total findings, twelve outside its
  baseline. diagnostic-proof.json establishes 46 -> 49 total findings, with
  exactly three additions: correct BfmeFontCharsCache references at 0x009E2084.
  The generated data_ledger still names the old undefined scalar there; the
  unchanged byte-verified provider already has the same wrong-name diagnostic.
  The eight other outside-baseline diagnostics are pre-existing in the large
  thunk unit. No checker, generated ledger or baseline was edited.
- check_csv passes: 91,230 function rows, 15,500 pins, 436 data rows.
  Normal commit and publication hooks remain required.

## Remaining blockers and donor review

FontLibraryDestructor still loses its primary vtable COMDAT and selects the
wrong W3DFontLibrary destructor definition. The initializer and thunk units
still have other unresolved globals and lifecycle helpers, plus their existing
COMDAT/selected-definition debt; full lists are preserved in proof.json.
A generated data-ledger refresh must reconcile the obsolete scalar entry with
the verified cache owner. These are separate repairs; no full link cycle or
other maintainer-only runner was started.

The pass checked repair_queue.py link and link_rank.py, then locally probed
ranked blockers before selecting this live binding error. BFME1 donor commits
63e68aaa567add9eb42a79913d23eece6a19ceee (typed owner rather than undefined
wrapper) and 121fc40f6a502481e19d1b9fa7964248edcefd97 (shared destructor
declaration) were reviewed. Their ownership/dependency repairs are applicable
as a method; the target data_rows record, relocations and paired object checks
prove this BFME2 adaptation. No donor layout or address was imported.

Official BFME1 master was fetched to 800b363f6af4a15f064628bff2fc74b15768709f.
The clean verified checkout/gitlink a7c38d3b2597121f178ab5190b3062478823257d
is retained: another worker holds its update claim and the prior full old/new
input comparison is blocked on dependency inputs/stalled old-input compilation.
No freshness success stamp or pointer advancement was made.
