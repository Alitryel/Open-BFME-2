# vector<BfmeE16>::_M_insert_overflow link chain (2026-10-19)

Goal: link LivingWorldAIBuilderScores.cpp (2,093 B), blocked only by its
BfmeE16 overflow copy (retail body 0x005B3970, stlport_vector_e16_noexc.cpp,
186 B, no-EH frame, allocate via allocator<BfmeE16>::allocate(n, 0)).

What works (not committed): an explicit inline specialization in retail form
(STLport __false_type body without _STLP_TRY, storage taken through
static_cast<allocator<BfmeE16>&>(_M_end_of_storage).allocate(len), helpers
__uninitialized_copy/__uninitialized_fill_n called normally). In
LivingWorldAIBuilderScores.cpp, stlport_vector_e16_o1.cpp and
Draw/W3DRopeDraw.cpp the unit stays 9/9 / 28/28 byte-matched and the copy
becomes retail's (W3DRopeDraw needs the include after its decl-only block,
outside namespace _STL).

Blocker: the link keeps the first copy in link order, which is
stlport_vector_e16_fill_insert_000b0395.cpp. That unit is /Ob0, so size(),
max, _M_clear and _M_set stay out-of-line calls and the body is 172-174 B,
never retail's 186 B. A decl-only binding there was tried earlier and changed
_M_fill_insert (0x000B0395). Until that unit can drop its overflow copy
without disturbing _M_fill_insert (e.g. moving _M_fill_insert to a unit
where the overflow is not instantiated, or a census rule change), the
retail-form header does not make LivingWorldAIBuilderScores link.

Also outstanding in the chain: stlport_vector_e16_o1.cpp has independent
non-retail copies (__uninitialized_copy x2, __uninitialized_fill_n,
_M_allocate_and_copy, operator=); Draw/W3DRopeDraw.cpp has a duplicate
buildSegments and an unproven _M_clear copy.