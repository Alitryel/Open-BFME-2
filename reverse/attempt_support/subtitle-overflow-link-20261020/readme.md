# Subtitle overflow provider selection blocker

At c0e160a2a8/a6b17059eb, published census 5366c4f808 (retail-truth-2),
`stlport_vector_int.cpp` emits a wrong stock-allocator SubtitleEntry pointer
vector overflow before the rowed alloc-only provider in
`stlport_vector_int_insert_overflow.cpp`. Paired current baseline: neither
253-byte caller unit nor 217-byte provider links. SubtitleManagerAccessors
additionally has StringBase/UnicodeString constructor copies.

Both declaration-only specialization and extern-template declaration suppress
body visibility needed by the rowed 50-byte push_back: cl7.1 now reserves a
stack byte (`push ecx`) and initializes the empty __true_type argument,
where native has no local frame/store. Both fail that same one of seven rows.
Original caller restored after two builds; no change or gain retained.
Baseline strict preparation passed 8/8 across caller/provider, with five import
references. A compiler-safe body-visible suppression or allocator/provider
reconciliation is required; changing allocation semantics just to remove the
COMDAT is not justified. No pins or baselines changed.
