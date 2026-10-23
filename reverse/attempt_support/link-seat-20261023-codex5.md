# Link repair pass, 2026-10-23

Base: aa465f8345, published census 456ce161c5 (2026-10-23 06:28), rules
retail-truth-4. No authored link gain or C++ coverage gain. All Code trials
were restored; all claims released. Results below are bounded legacy previews,
not closed-strict closure. The byte gates were scoped to the trial units.

## Byte vector / BooleanVector split

`Code/Libraries/Source/WWVegas/WWLib/vector.cpp` has two ledger rows but
unrowed BooleanVector definitions referencing Get_Bit and Set_Bit. A trial
kept the includes and `template class VectorClass<unsigned char>;` in that
file and moved its BooleanVector definitions, unchanged, into
`vector_boolean.cpp`. Both byte rows passed; legacy prediction changed from
0 to 71 linked bytes. The new file had zero matched rows and failed source
admission (`find_declared_unmatched`), so the split was rejected in full.
No whitelist or admission rule was changed. A verified BooleanVector body
could make a legitimate split possible. A new byte-vector home would need
current-ledger measurement rather than pretending it is in this census.

Logs: `build/link-seat-vector-{before,byte,after}.log`. Original backup:
`build/link-seat-vector-original.cpp.txt`. No improved reconstruction to bank.

## MapCache pair cleanup

`MapCacheClearUnseenMaps_Rva0030469e.cpp`: seven rows, 322 authored bytes,
held by the implicit `pair<const AsciiString,MapMetaData>` destructor versus
the first MapUtil copy. The opaque payload remains 256 bytes; this pass made
no new layout or identity inference.

Two declarations immediately after MapMetaData were tried independently:

```cpp
namespace _STL {
template <> pair<const AsciiString, MapMetaData>::~pair();
}
```

This leaves the conflicting implicit destructor emitted (7/7 byte rows pass).

```cpp
namespace _STL {
template <> __declspec(dllimport) __forceinline
pair<const AsciiString, MapMetaData>::~pair() {}
}
```

Implicit member cleanup preserves 7/7 byte rows, including both EH funclets,
but generates an unresolved imported destructor and a non-retail erase-one
copy. Rejected and restored. Do not suppress this conflict without reconciling
the pair/string cleanup with its provider.

Logs: `build/link-seat-map-{before,byte,after,byte2,after2}.log`. Original:
`build/link-seat-map-original.cpp.txt`. Neither candidate improves the link.

## CahClass cleanup is a container identity problem

Current paired prediction for `Rva005B5420Dtor.cpp`,
`StlSweepR3Rva0040A603.cpp`, and `Rva0021FFEEDtor.cpp` is 485 -> 485 B.
The first two hold 109 and 56 B on the pinned tree clear helper at 40A59B.
The independently recovered 52-byte native function at that address, in
`Rva0040A1ACHeroPtrAlgos.cpp`, clears an owned CreateAHeroData pointer vector
using for_each and range erase. This is target evidence contradicting the
tree-clear pin. A declaration-only specialization would keep a wrong
provider. Reconcile the container identity/layout first; no source trial.
Log: `build/link-seat-cah-clear-before.log`.

## Refreshed leads and verification infrastructure

Reference donor review and current provider checks were performed before
new trials. Current Snapshot alias cohort: all 17 units already link;
309 B of difference from the published index is inherited, not this pass.
Current PingThread pair also links already (410 B inherited). Existing
particle, Apt, string, preference and class reconciliation records were
consulted rather than repeating their unchanged failed trials. Several
providers are newer than the census; always include them in a paired preview.

`name_globals.py` dry run found zero rewrites. `rehome_rows.py --limit 5`
could not serve work without `build/link_census/census.log`. No compatible
data-back artifact was available; no rankings were invented from missing data.

The full retained-input freshness baseline was launched once with valid
published caches, but waited 17 minutes on
`/home/agent/.cache/open-bfme-build.lock` (Python PID 7515,
`locks_lock_inode_wait`, no children). This seat terminated only its own
waiting process (exit 143). Scoped gates remained usable. Full verification
was not completed, so the reference pointer and success stamp were not
advanced. Log: `build/link-seat-freshness-baseline-current.log`.

Retained clean/committed BFME1 inputs:
96c88c73a5cd1a58fc2f8db691beea50acd996db. Official master fetched:
f5140c1cff6a58e16276fd6de6788186286953d4. Resume the verified freshness
comparison when the shared compiler is available; preserve the retained
inputs until both baseline and update regressions have been checked. Do not
rebuild the census in this model seat.
