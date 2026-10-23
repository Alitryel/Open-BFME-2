# Full module-registry storage

The recovered constructor and destructor operate on the registry at native
VA `E03CE0`: virtual pointer at +0, 12-byte pointer set at +4, and a flag at
+17. Its canonical class consumes an aligned 20 bytes. The next independently
named datum is RainOfFireUpdate's pool-name key at `E03CF4`; all 20 initial
registry bytes are zero. The old definition in the broad shutdown-thunk file
reserved only four bytes, although the initializer constructed the full object
there.

`BfmeLargeGroupAudioRegistry` is a behavior-derived name, not a recovered
original spelling. One aligned 20-byte raw-storage object now lives with its
explicit initialization and destruction. A compile-time size check keeps the
allocation equal to the canonical class. The storage union has no runtime
constructor, so it adds no initializer or shutdown callback. The existing
22-byte initializer and 10-byte callback retain the native lifetime sequence.

The LargeGroupAudio module constructor, copy constructor, destructor, registry
initializer and registry shutdown callback all reference that one symbol through
the shared storage header. Unused old declarations and the four-byte definition
are removed. A real data row verifies the complete 20-byte range and the
converged-address list protects the sole name. No old global spelling remains
in `Code/`. No second datum or symbol pin is introduced.

Validation: 966/966 bodies across seven changed sources; 21 data rows;
strict current receipts; all ten converged addresses pass with zero second
names and zero unjudged rows. `proof.json` checks the sole definition, data size
and complete initial contents, and every relocation to it in all five native
readers/writers. Those complete bodies remain byte-exact. The datum's size
comes from native layout and its next independent neighbor; the original name
remains unknown.

The current eleven-provider link preview places the registry's 80 bytes,
module copy's 102 bytes, module destructor unit's 100 bytes, and module
constructor's 111 bytes. The complete scoped preview is 5,549 -> 6,142 bytes
against published index `8eecc93d07`; it also includes the preceding registry
class recovery and current provider refreshes, so it is not an incremental
storage-only gain or a new census. Unrelated broad thunk/map/registration debt
remains. This repair adds 20 verified data bytes and zero new C++ code bytes.
