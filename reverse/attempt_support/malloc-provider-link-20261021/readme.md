# Rowed malloc allocator selection

Two earlier COMDAT copies of `_STL::__malloc_alloc<0>::allocate` displaced the
retail provider in `STLMallocAlloc0Allocate.cpp` (RVA 0x25090). Add declaration-only
specializations in the wide money parser and sphere-merge units, preserving
all their existing code rows while referring to the rowed provider. Both copies
must be removed: leaving either selects a known non-retail body.

Paired current-object `link_check.py` against census 17918792f6
(2026-10-21 09:22) changes `stlport_vector_pair.cpp` from zero to 570 linked
bytes. The two edited units retain their other existing blockers; these edits
are verified prerequisites for this named consumer. `./build.sh` passes 5/5
rows, including the parser's EH handler and both renumbered cleanup labels.
`find_declared_unmatched.py` passes both sources. `--prepare-current` passes
strict reusable receipt/byte verification for both edited providers and the
pair-vector consumer (16/16 code rows). The link result is the per-unit legacy
prediction against frozen peers, not a closed-strict closure claim.

The canonical allocator itself also becomes selectable (48 B); the final
paired-source check reports 618 linked bytes across these two consumers. No
full census or link cycle was run.
