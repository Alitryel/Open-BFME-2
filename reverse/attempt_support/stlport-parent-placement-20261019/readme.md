Existing STLport cleanup parent placements

The existing 14-byte compiler actions at769680 and783AE4 named the canonical
_Construct template rows atA7849 and796E8 as their parents. Their own original
notes identified the actual native parent placements at1D9B0F and3F1A5F.
Those placements already have same-source logical alias rows. A newly repeated
raw compiler label made the existing exact-parent scope check expose the stale
metadata during reference publication.

Point parent= to those existing same-source placement rows. Fresh isolated native
compilation proves each complete45-byte parent, its complete exact EH graph and
the corresponding complete14-byte action, including its placement-delete REL32.
The next compiler EH-handler symbol in the same COFF section proves each action's
extent. proof.json records the original rows, source/object hashes, compiler
command, native bytes, bindings and complete parent locations.

The normal whole-file gate passes60/60 bodies. Complete scoped EH verification
passes34/34 graphs with zero baseline exceptions or missing objects. Ledger and
definition checks pass. No source, extent, pin, alias, baseline or verifier edit
is part of this repair; there is zero additional C++ coverage. The earlier
76A02C repair is independent and remains unchanged.

A narrow audit checked all985 collision-guarded raw compiler labels. After the
first two corrections it found one more stale parent:776A09 in the sibling
stlport_construct_stl_types2.cpp. That row now points to the existing2BF35B
placement instead of the canonical21789E template. types2-proof.json contains
the same fresh45B parent, complete EH graph and14B action/extent proof.
The final combined normal gate passes71/71 bodies and41/41 complete EH graphs.
