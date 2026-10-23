# Seven fill callers use their real placement-copy owners

Seven existing 37-byte STLport fill loops called synthetic `_Construct<T,T>`
names pinned to distinct native 45-byte placement-copy bodies. Those bodies
already have genuine C++ owners from the October 20 placement-copy repairs.
The old caller units still emitted conflicting generic Construct definitions
and referred to undefined constructors of invented polymorphic element views.

Native evidence, independently checked for every member:

| Fill RVA | Actual placement-copy RVA | Existing interface |
| --- | --- | --- |
| 000BBC19 | 000BBA47 | TreeKey00242F5E pointer and reference |
| 000CF529 | 000CF4D6 | TreeKey00242F5E pointer and reference |
| 000D04BC | 000D0469 | TreeKey00242F5E pointer and reference |
| 001D9B62 | 001D9B0F | two pointer values |
| 0020572F | 0020596A | two pointer values |
| 0048C872 | 0048C81F | TreeKey00242F5E pointer and reference |
| 004C3AF2 | 004C3A9F | two pointer values |

Every native loop has stride eight and calls the listed complete owner. The
owners' actual constructor edges are CF475 or 466EA7. The existing owners and
their full EH graphs establish those operations; the loops' instruction shape
alone does not establish application class names or justify a template alias.
See the earlier placement-copy-family and placement-copy-stl-family handoffs.

Each caller now has a neutral eight-byte element view and a TU-local Construct
overload, declared before the reference template is parsed. It forwards to the
existing owner through its actual interface. Ob1 permits that forwarding call
to inline; the emitted 37-byte loop directly calls the native owner. No wrapper
entry is substituted for that call. The fake virtual members and unimplemented
copy constructors are removed. Existing mangled row names and extents remain.

The TreeKey and pair interpretations are inherited provider evidence; original
application identities of these seven element views remain unknown. No shared
header, canonical class, global, callee implementation or data layout changed.

A first explicit-template-specialization trial emitted an external Construct
adapter even after inlining, so it was rejected. The retained static overloads
have COFF storage class 3 and discardable COMDAT function sections. There is
exactly one public code definition per caller unit, its existing fill row.
No runtime relocation references the local forwarding copy; its only reference
is in discardable .debug$F information. The absent-from-retail annotations
declare those introduced, unused local emission copies, not unclaimed retail
bodies. All seven find_declared_unmatched checks pass.

Seven obsolete private-template pins are removed, with no new pin, alias,
object-symbol row or exception. No hatch register entry exists for these seven
pins, so no register or baseline file is edited. Code/shim searches find each
element name only in its own changed unit. Normal byte verification after pin
retirement proves the direct callee bindings without those pins.

Validation retained here:

* All seven complete 37-byte bodies and their actual single REL32 binding are
  exact. inputs.json records native bytes, raw emitted bytes, source/object
  hashes and the absence of runtime references to local glue.
* Strict reusable preparation verifies all 126 rows across the seven callers
  and two unchanged provider units. All 56 parent EH graphs are EXACT, no
  baselined or missing-object verdicts.
* On the same local retail-truth-4 index, all seven callers change from 0 to
  37 predicted linkable bytes. Both provider units stay linkable at 1,097 and
  1,763 bytes. The paired total is 2,860 -> 3,119, gain 259. This is a bounded
  current-object prediction, not a new census, closed-strict result or placed
  link. before-link.txt and paired-after.txt retain the actual diagnostics.
* Rescanning all seven affected units with place_bodies finds zero additional
  bodies or pins; placements.txt records that result.

C++ coverage is unchanged: these seven loops were already byte-matched C++.
The repair makes their real providers link and removes seven synthetic pins.

After retiring the seven pins, the full normal byte gate passed all 98,188
function rows and 2,175 data rows, plus literal/import/float, global consistency,
source ownership and no-op-patch checks. See full-byte-check.txt.
