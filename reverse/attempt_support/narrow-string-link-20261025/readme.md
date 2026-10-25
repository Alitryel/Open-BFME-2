# Narrow-string link repair, 2026-10-25

Inputs: BFME 2 82cff43d14, published retail-truth-4 index ce1b975697,
BFME 1 0bf534ea7ccde110c456edb9cd2dd5dae823c953, existing TU flags
/EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC plus normal build profile.

`stlport_narrow_string.cpp` still previews 0/396 B linked: its whole-class
instantiation emits non-retail `_M_compare` and `insert<char*>` copies.
After row rehoming, eight rows remain. Replacing the whole-class instantiation
with explicit rbegin, rend, append<char*>, swap<char*> and reverse-iterator !=
instantiations preserves six rows but no longer emits char_traits<char>::assign
or compare. No mismatched bodies were landed.

A second trial restored the whole-class instantiation and added declaration-only
specializations for `_M_compare(const char*, const char*, const char*, const char*)`
and `insert<char*>(char*, char*, char*, const forward_iterator_tag&)`.
MSVC 7.1 fails with C1001 at vendor/stlport/stl/_string.h:801 (Utc P2/main.c:148).
This confirms the previously recorded 82315 obstruction; do not repeat it.
Prior 82316 kept ForwardIterator in declarations but lost compare emission and
changed a now-rehomed initializer wrapper. A future selective-emission attempt
needs a principled way to retain the specialized non-template char_traits
members and must preserve the wide _String_base allocator constructor fold proof.

Independent target identities also need care: the comparator pin 24FC0 belongs
to the rowed range comparator in BfmeTwoHundredEightyThree.cpp, whereas insert's
1EC1B4 owner is a 172-byte-record vector, not a char string insertion. A pin is
not proof of a valid string helper provider. Source was restored completely;
no byte gain, no closure gain, no compiler/cache bypass.
