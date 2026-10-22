# Hash-map constructor link repair: blocked

Target: `Rva0016E400Ctor.cpp`, retail constructors 0x0016E400 and
0x00624D60 (72 bytes each), with four exception-handler rows. Tested at
69eb7204fa using the source flags and MSVC 7.1 from `./build.sh`.

The current-object legacy cohort (`AIStatCollector.cpp`,
`StlSweepW4Rva004E02B8.cpp`, `Rva0016E400Ctor.cpp`,
`Rva0016DEE0Cluster.cpp`) links 246 bytes before edits. The wrapper unit
emits a non-retail `hash_map<int,int>` default constructor; the verified
folded constructor provider is in `StlSweepW4Rva004E02B8.cpp`. Binding to it
could unblock the wrapper and AI collector, but byte identity is required.

Tested an explicit `hash_map<int,int>::hash_map()` specialization using the
vendor initializer `_M_ht(100, hasher(), key_equal(), allocator_type())`,
marked `__declspec(dllimport) __forceinline`. Both parent constructors gained
extra EH states and changed stack slots, failing two of six rows. Replacing
`__forceinline` with `inline` emitted an imported constructor call in each
parent (13 bytes versus retail 72), removed the local handlers, and failed
all six rows. Neither variant is a valid repair. No source change retained.

Remaining prerequisite: suppress the non-retail COMDAT without altering
retail parent inlining or EH state allocation. A declaration-only imported
constructor is insufficient, as demonstrated by the ordinary-inline trial.
The verified original source was restored and its six rows rechecked.
These trials do not establish a new target identity or class layout.
