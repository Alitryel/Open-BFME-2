# Integer-count map constructor ownership

Inputs BFME2 1b42f8c583; BFME1 verified pointer37c3022de1ab; published index08160bc2c9 (2026-10-22 17:08). No new identity, pin or layout claim.

AIStatCollector.cpp (362B) loses its int-count hashtable destructor and selects the wrong default hash_map<int,int> constructor emitted by Rva0016E400Ctor.cpp (164B). Including current StlSweepW4Rva004E02B8.cpp and Rva0016DEE0Cluster.cpp removes the destructor conflict but leaves the map constructor wrong-selected. The default-map pin4E02B8 has a fold-proof naming StlSweepW4Rva004E02B8.cpp; that current source also declares the specialization before explicitly instantiating it. A working independently emitted constructor provider is a prerequisite; the pin alone does not supply one.

Two trials, both restored:

* AI hashtable destructor declaration passes its10/10 rows. Imported forceinline hash_map default constructor, with the primary `_M_ht(100,hasher(),key_equal(),allocator_type())` initializer, changes both72B wrapper constructors: extra EH-state stores and second wrapper frame growth. Combined gate14/16 exact, failed2.
* `extern template hash_map<int,int>::hash_map()` retaining the primary declaration suppresses its inline body too. Wrapper becomes12B out-of-line call; both handlers and cleanup rows disappear. Combined gate10/16 exact, failed6.

Do not repeat either suppression without restoring the native inline/EH behavior. Useful diagnostics remain local build/link-seat-ai-{before,providers,trial1,trial2,after2}.txt. Original sources restored; no gain or failed reconstruction retained. No full link runner was used.
