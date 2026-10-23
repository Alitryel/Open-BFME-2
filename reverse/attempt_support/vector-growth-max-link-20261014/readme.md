# Unsigned vector-growth provider repair

At BFME 2 base de7bb30890621a5de4b072a6c5535277721167e5, GameLogicLoadPostProcess.cpp
and HordeContainModuleDataParse.cpp each have one local link blocker: their
incidental external `_STL::max<unsigned int>` COMDAT differs from retail.
Declare a TU-local unsigned overload before including vector, preserving the
original comparison and reference-return semantics. Vector growth calls were
already inlined. No flags, layouts, shared headers, ledger rows, pins, aliases,
globals or baselines change.

## Evidence and acceptance

- Existing target rows identify the units and anchor their functions. The
  ordinary byte gate passes all eight rows, eighteen literals and three named
  imports. Every retained COMDAT's whole bytes, size and relocation digest
  match its before object. All other nondebug sections and linker directives
  remain identical after normalizing internal COFF section/symbol indices.
- Each object loses only its external max template, whose sixteen bytes are
  `8b4424048b108b4c24083b110f42c1c3`. MSVC emits an eight-byte private static
  helper instead, `8b113b100f43c1c3`, with no relocations. Neither the old
  external body nor the new local helper has a nondebug call relocation in
  these units. There are no new external bindings; the only removed external
  binding is max. Existing external providers are not edited.
- Bounded `link_check.py --prepare-current` verifies both objects with strict
  reusable receipts. The /I. unit watches the checkout's file listing; final
  receipts were refreshed after creating every evidence filename. This proves
  current compilation, not self-strict LINK closure.
- Class, declared-function, new-variant, CSV and whitespace checks pass.
  EH check reports zero applicable rows and zero nonexact/baseline/missing
  objects. Shadow data check has zero findings; enforced converged-data check
  sees eight protected addresses and zero second names or unjudged rows.
  Placement resweep finds zero additional bodies or pins.
- object-proof.json records source/object hashes, unchanged index hash, complete
  retained COMDAT names and the full indexed forty-two-consumer max blocker
  cohort. Original sources, objects, receipts and the comparison script remain
  under ignored build/vector-growth-max-link-20261014.

## Local result and limits

The unchanged runner index was measured at 147cfae2cb, 2026-10-14 07:27.
The older committed repair queue at 67e1365aa9 is discovery evidence only.
Both before/after previews use this same index and the same explicit two units.

| Consumer | Blockers before -> after | Existing legacy local LINKED bytes before -> after |
| --- | ---: | ---: |
| GameLogicLoadPostProcess.cpp | 1 -> 0 | 0 -> 340 |
| HordeContainModuleDataParse.cpp | 1 -> 0 | 0 -> 765 |

This enables 1,105 existing bytes in the legacy local preview and adds zero
C++ coverage. Other indexed consumers need separate current checks and repairs;
no cohort-wide improvement is claimed. The bounded local closed-strict check
`link_check.py --refresh --current-ledger --paths-from ...` refuses judgment
because 395 current-ledger objects are missing (closed-after.txt). No self-strict
or closed-strict LINK gain, fresh census placement or runtime result is claimed.
No census build/measure/history, full link cycle, nightly or boot runner ran.

## Donor review and reference state

Reviewed BFME 1 TileData repair d3f9000fe08615a100e844adfff57fa4a39cd615
from verified donor revision 23b143233b5a8664a3bdf8572df6d905c310a5a1.
Its principle of suppressing an incidental competing emitter applies; its
TileData implementation and layout are not transferred. BFME 2's existing
StrategicHUDRegionDetailsArmiesMovieClip.cpp repair independently supplies this local max pattern.
Exact retained bytes and unchanged relocation targets establish its application
here, rather than the donor's linking result.

Official BFME 1 master was fetched at a7c38d3b2597121f178ab5190b3062478823257d.
The verified 23b1432 gitlink/checkout is retained; comparative full verification
of the newer pointer remains outstanding. No freshness-success stamp is written.
