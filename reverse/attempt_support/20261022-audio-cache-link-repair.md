# Audio-cache constructor visibility

Base e0e25654b5; published census 08160bc2c9 (2026-10-22 17:08).
AudioFileCacheThreadEntry.cpp initially previews 0/360 linked bytes because
its hash-map constructor instantiation emits a non-retail hashtable constructor
and next-size helper. A declaration-only specialization binds the existing
rowed wrapper at A7E7A instead. All ten byte rows, seven funclet-label
renumberings, literals and imports pass. The scoped legacy preview becomes
360/360 linked bytes. This is not a closed-strict gain.

The wrapper owner StlSweepW4Rva000A7E7A.cpp still has its separate provider
blockers: gratuitous whole-class instantiation references element equality,
and its hashtable constructor differs from retail. A7E7A's native 31-byte body
calls the existing 64-byte A7DF1 constructor, rowed in StlSweepW5Rva000A7DF1.cpp
under an address-derived eight-byte mapped carrier. Native passes three empty
temporaries at the same ebp-1 address. No payload identity follows from this.

An explicit wrapper specialization containing that existing hashtable type
and a declaration-only base constructor compiled, but emitted zero initialization
(`xor eax,eax; stosb`), three different temporary addresses and a relocation
at offset 29 (outside the 31-byte row). The provider was fully restored;
no extent, pin, alias or payload identity was changed. A future trial must
explain the original dependent-template temporary initialization before retrying.

The same session restored a systimer WWINLINE=dllimport trial: it imported
Get's function-static storage and prevented Reset inlining (1/4 rows failed).
CreateAHeroHeroBlingList's paired existing provider already links 496 bytes;
its direct canonical map::find trial hit MSVC C1001 at _tree.h:481. Both are
recorded in re_attempts.log; neither contributes a link gain.
