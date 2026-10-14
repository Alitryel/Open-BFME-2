# FX-list unsigned max link repair

At BFME 2 base 24dd72505a, FXListStoreParse.cpp emits an incidental
external `_STL::max<unsigned int>` body that differs from the retail
17-byte provider at 0x00013740 in stlport_basic_ios_init.cpp. Use the
previously verified internal unsigned overload before the container headers.
STLport establishes its comparison and reference-return semantics; the
target object proves all uses were already inlined. No new identity or
layout is inferred.

The whole-object proof preserves all 112 retained COMDAT bodies, extents
and relocation digests. The only removed external binding is max; its
replacement is an unreferenced private eight-byte helper with no relocations.
All other nondebug sections and exact linker directives are unchanged after
normalizing local COFF indices. object-proof.json records source/object
hashes, the strict current compiler receipt and the unchanged index hash.
Original sources, objects, receipts and comparison scripts remain under
ignored build/fx-walls-max-link-20261014.

Strict bounded preparation passes all 23 rows of the two initially inspected
consumers before and after the trial. ManTheWallsSpecialPower.cpp already
has a declaration-only max specialization: it emits no offending max body,
so its trial edit was restored and its file claim released. Only the
FX-list parser changes. The final ordinary byte gate checks the parser and
the canonical provider together: 33/33 rows, one data row and two named
imports pass. EH verification is EXACT for the parser's one graph.
Declared-function, class, new-variant, converged-data and whitespace checks
pass. Placement resweep finds zero bodies and zero pins.

The runner index was measured at 147cfae2cb, 2026-10-14 07:27. The
committed link-status queue is discovery evidence only. link-proof.json
compares saved-before and current parser objects against two copies of that
same index, refreshing just the parser in memory in each. Findings improve
18 -> 17, with precisely the max finding removed and every other finding
unchanged. The parser's 889 owned bytes still have legacy local LINKED
0 -> 0. Remaining findings concern pointer-vector helpers and the NameKey
hash; the canonical provider also has independent unresolved/COMDAT/selected
findings. No index, census or link-status artifact changes.

Strict current receipts and byte verification do not prove self-strict LINK
closure. The bounded closed-strict current-ledger check refuses judgment
because 442 current objects are missing. No self-strict or closed-strict LINK
gain, fresh census placement or runtime result is claimed. Maintainer-only
link cycles, census build/measure/history, nightlies and boot runners were
not invoked.

Reviewed BFME 1 repair d3f9000fe08615a100e844adfff57fa4a39cd615 at the
retained verified revision a7c38d3b2597121f178ab5190b3062478823257d. Its
incidental-emitter suppression principle applies; its TileData code and
layout do not. BFME 2's preceding armies-page max repair supplies the
concrete overload pattern. Target bytes and relocations prove this repair
independently of donor linking results.

Official BFME 1 master was fetched at 58ab850fd1. The verified gitlink and
clean checkout remain a7c38d3b25. Comparative full verification of the
newer pointer is still blocked by the previously recorded large stale-object
gate; no freshness-success stamp is written. Unchanged blocked constructor
and return-view repairs were recorded and their file claims released;
another worker holds each required RVA. An interrupted read-only rehome
preview supplied leads only; its matched entry constructor remains deferred
because moving it does not resolve the owner's independent blockers.
