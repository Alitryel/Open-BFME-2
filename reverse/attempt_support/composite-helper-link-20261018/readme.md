# Composite bounds and string helper emission

Base 7ee55052d7; same paired index c2c5ac8c27, 2026-10-18 11:36 as the
preceding SphereClass provider repair. proof.json records its frozen hash.

After that repair, composite.cpp retained non-retail out-of-line copies of
AABoxClass::Init(MinMaxAABoxClass) and StringClass::Is_Empty. Their visible
inline semantics are required by existing matched callers. Reuse the existing
bfme_part_emt_inline StringClass view. Add AABoxClassLink.h from the verified
BFME1 64d369b90170b7e9ec917d646f020b11f13eb0d5 game WWMath/aabox.h,
changing only the initializer's declaration and definition to the established
dllimport/forceinline spelling, provenance comment and trailing whitespace.
This preserves inlining while omitting the competing external definition.
No imported call remains, and no pin, alias, global, layout or row changes.
The rowed AABox owner at 0x00068F68 and string owner at 0x00130FEA retain
existing target identity evidence; donor layout assertions are not upgraded.

Acceptance and measurement:

* Before/after link_check --prepare-current and ./build.sh: 25/25 rows,
  strict reusable receipts, two empty strings and one float literal, no
  baselined/skipped references or named imports.
* Exact normalized object comparison removes only those two COMDATs. Every
  retained nondebug section's full bytes, flags, definitions and symbolic
  relocations match; every retained COMDAT's extent/digest matches.
* Paired current-provider prediction measures the previous repair's hlod,
  collect and SphereClass owner as unchanged witnesses in both states.
  Composite LINKED 0 -> 1930 nonpadding bytes; combined witnesses 277 ->
  2207 B. Its remaining findings fall to zero; no witness regresses. The
  AABox kept provider is unchanged and StringClass's selected provider
  changes from wrong to the retail body. Ordinary four-unit link_check
  agrees (2/4 clean, expected exit 1 for independent witness blockers).
  This is a legacy local prediction using self-strict current objects,
  not closed-strict evidence or a new census/executable measurement.
* Enforced data, converged data, class and frozen-source checks pass.
  Placement resweep finds zero bodies/pins. Hooks verify header dependents.

The first trial reused bfme_hlod_aabox's external initializer declaration.
It changed the 742-byte bounds routine because retail inlines this helper
there. That trial was replaced with the selective inline-emission view;
no failed reconstruction remains. The earlier whole-class import refusal
in re_attempts.log is not retried.

The same-helper scan found aabtreecull, part_buf and collect with additional
independent findings; no link gain in them is claimed. BFME1 review/freshness
state is unchanged from sphere-provider-link-20261018: verified pointer kept,
official upstream fetched at 8619c4c5, outstanding Rva005E394EPrimaryBase
relocation identity blocker. No maintainer-only runner or census write.
