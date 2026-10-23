# ModelCondition comparator providers, 2026-10-18

The rowed comparator at 0x0033AD13 examines 104 bits of the four-word ModelCondition key. Its established byte-verified source is SparseMatchFinderModelConditionCompare117.cpp. The previous STLModelConditionBitFlagsFind.cpp view compared a single word and emitted a non-retail COMDAT; W3DModelDrawO1Inlines.cpp also emitted a non-retail comparator from its reference headers.

Give the find unit the four-word layout and the established comparator body, keeping noinline visibility so its two matched callers retain their retail register allocation. The emitted comparator independently equals all 73 retail bytes, with no relocations. Declare the W3D member specialization without defining it so that unit calls the rowed provider. No pins, aliases, source flags or shared headers change.

Paired current previews use the same six units and the published c2c5ac8c27 index. Before: 0/6 units link, 0 bytes. After: the comparator (73 B) and lower-bound (76 B) units link, totaling +149 B. Both edited providers and the insertion units retain independent blockers shown in after.txt. This is a legacy link preview with self-strict provider evidence, not a closed-strict census result. Authored C++ coverage does not grow.

All 15 matched rows in the two edited units pass the byte gate and both receive strict reusable provider receipts. The associated EH graph is EXACT (1/1). Data checks and code identity checks have no findings; restoring the original sources and rebuilding also showed no pre-existing identity findings. Declarations pass. An initial opaque comparator declaration changed _M_find scheduling and was discarded; the visible native body preserves every row. No census/index/status or verifier baseline is changed.
