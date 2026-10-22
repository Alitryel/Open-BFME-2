# Fstream default-protection constructors: +528 B linked

At HEAD 681beffaaa, published index 08160bc2c9 (2026-10-22 17:08),
FstreamDefaultProtectionNameCtors.cpp's current object failed the legacy
preview on its nonretail basic_ios<char>::init and selected imbue copies.
A declaration-only specialization of init before the constructors uses the
rowed 178-byte owner at 0x000162F0 (stlport_basic_ios_init.cpp). This is the
same binding used by stlport_narrow_fstream.cpp, rather than a new identity
or source reconstruction. The calls' existing retail relocations prove the
provider relationship. No donor inputs or compiler flags change.

Measured the original and repaired current objects against the same index:
0 -> 528 nonpadding bytes, all five matched rows unchanged. A second
baseline with the current stlport_narrow_ios_imbue.cpp provider also fails;
the repaired unit links both alone and with that provider. The initializer
copy's removal eliminates this unit's dependency on the losing imbue copy.
The other imbue provider's own string-assignment blocker remains unrelated.

Acceptance: build.sh 5/5, literal/float/import checks, frozen-file check,
link_check --prepare-current strict reusable source receipt, and
link_check --new-variants. This is a legacy current-object preview gain
with self-strict byte evidence, not a closed-strict census measurement.
The sole other nonretail init emitter is narrow_ostringstream_dtor; it has
many independent blockers, so no speculative suppression was landed there.
