# Armies-page and formation-parser unsigned max repair

At BFME 2 base c59ee28af2, two current consumers still emit an incidental
external `_STL::max<unsigned int>` body that differs from retail. Add an
internal unsigned overload before the container headers. It preserves the
comparison and reference-return semantics; all uses were already inlined.
This is the same locally verified pattern as the preceding vector-growth
repair. No flags, shared headers, class layouts, ledger rows, pins, aliases,
globals, baselines or external providers change.

## Evidence and acceptance

Target evidence is the existing byte-verified parents and complete associative
EH graphs. STLport supplies the comparison semantics. No new identity or
layout is inferred. Whole-object comparisons prove all 196 retained COMDAT
bodies, extents and relocation digests unchanged (41 armies-page, 155 parser).
The only removed external binding is max. Each object gains an unreferenced
private eight-byte comparison helper instead; it has no relocations and no
nondebug callers. All other nondebug sections and exact linker directives
are unchanged after normalizing local COFF section/symbol indices. Source,
object and unchanged index hashes are recorded in object-proof.json.

Bounded strict receipt preparation passes all 12 touched rows before/after.
The ordinary byte gate including the canonical provider
Code/Libraries/Source/WWVegas/WWLib/stlport_basic_ios_init.cpp passes 33/33,
two literals, one empty-string reference and two named imports. EH verification
is EXACT for all three applicable graphs, no baseline. Declared-function,
class, new-variant, CSV and whitespace checks pass. Shadow data check has zero
findings; enforced converged-data check sees eight addresses, zero second
names and zero unjudged rows. Placement resweep finds zero bodies or pins.

## Local improvement and remaining blockers

The unchanged runner index was measured at 147cfae2cb, 2026-10-14 07:27.
The older committed repair queue is discovery evidence only. Saved-before
objects retain their canonical object filenames in ignored scratch; both
before and after refresh exactly these two providers in memory against the
same index. link-proof.json proves each loses only its max finding.

| Consumer | Legacy local findings before -> after | Remaining finding |
| --- | ---: | --- |
| StrategicInGameUIRegionDetailsArmiesPage.cpp | 2 -> 1 | unresolved Rva005E1E9BElement destructor |
| FormationAssistantParseFormation.cpp | 2 -> 1 | nonretail nested-deque _M_push_back_aux_v |

This is a verified two-finding repair with zero new authored C++ bytes and
legacy local LINKED 0 -> 0. Both remaining findings are unchanged independent
blockers. Strict current compiler receipts and byte verification do not prove
self-strict LINK closure. The bounded closed-strict check refuses judgment:
408 current-ledger objects are missing. No self-strict or closed-strict LINK
gain, fresh census placement or runtime result is claimed. Maintainer-only
full link cycles, census build/measure/history, nightlies and boot runners
were not invoked.

## Donor review and reference state

Reviewed BFME 1 repair d3f9000fe08615a100e844adfff57fa4a39cd615
at retained verified revision 23b143233b5a8664a3bdf8572df6d905c310a5a1.
Its incidental-emitter suppression is applicable; TileData code and layout
are inapplicable here. BFME 2's preceding vector-growth repair supplies the
concrete local max pattern. Exact retained target bytes and relocations prove
this application, independently of donor linking results.

Official master was fetched at a7c38d3b2597121f178ab5190b3062478823257d.
The clean verified gitlink/checkout is retained. Comparative full verification
of the newer pointer is outstanding, as already recorded by the preceding
session. No freshness-success stamp is written.

Original sources, before/after objects, receipts, comparison scripts and
snapshots remain under ignored build/armies-page-max-link-20261014. The
fallback name_globals dry run found zero edits. An optional rehome preview
found one lead before being stopped after this dependency was selected;
no rehome or census changes were made.
