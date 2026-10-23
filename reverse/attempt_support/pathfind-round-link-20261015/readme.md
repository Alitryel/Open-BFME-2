PathfindLayer rounding helper linkage repair, 2026-10-15

PathfindLayerAllocateCells.cpp emitted public fast_float_floor and
fast_float_ceil copies whose CRT implementations differ from PartitionManager's
first copies. Give both helpers static linkage. Their inline implementations,
all emitted nondebug section bytes/flags, symbolic relocations, linker directives
and SafeSEH membership stay identical. Only the two external bindings disappear;
the helper bodies remain as local symbols. Neither has incoming nondebug
relocations, including section-directed references. All ten retained COMDATs
are unchanged. No pin, alias, compiler flag, shared header or baseline changes.

Source base and frozen runner index hash/measurement are in context.json:
legacy census ac77c85054, 2026-10-15 14:25 UTC. Both phases strictly prepare
only the two explicit, claimed sources in sources.txt. proof.py refreshes those
objects into two copies of the SAME in-memory index; it does not update the
index, census, status or history. The consumer's findings fall from three to one;
the unchanged provider's findings are identical. This removes two link findings,
with zero new authored bytes and zero linked-byte gain (0 of 674 existing consumer
bytes before and after). This is a local legacy prediction with self-strict
consumer/provider witnesses, not closed-strict or a full-game link result.
The helper witnesses have no established retail RVA; first-copy differences
are not proof of a new retail helper identity. Existing consumer identity/layout
evidence remains unchanged.

Acceptance:
- ./build.sh consumer: 1/1 matched, four float literals and four imports pass.
- link_check.py --prepare-current --paths-from sources.txt, both phases:
  9/9 matched across two sources, strict reusable receipts, literal/float/import
  gates pass. No extra providers compiled.
- proof.py: all section/relocation/binding invariants above pass, provider object
  byte-for-byte unchanged, paired findings 3 -> 1, data findings identical.
- link_check.py --paths-from sources.txt: exit 1, consumer only unresolved
  ??1PathfindCell@@QAE@XZ; provider retains its unrelated existing findings.
- eh_verify.py --sources-from sources.txt: 1/1 EXACT.
- data_check.py --enforce with both explicit source arguments: exit 0,
  two sources, zero findings. --converged: two sources, eight addresses,
  zero second names and zero unjudged rows.
- link_check.py --new-variants --paths-from sources.txt: exit 0.
- find_declared_unmatched.py and class_gate.py consumer: pass.
- place_bodies.py consumer: zero new bodies or pins.
- check_csv.py and git diff --check: pass.

Remaining dependency: the source/row's existing evidence gives 0x0052DD64 as
its array destruction callback. The current ledger owns that 17-byte body as
MixFileCreator::FileInfoStruct::~FileInfoStruct from a BFME1 byte donor; an earlier
sort attempt in re_attempts.log also reports conflicting FileInfoStruct layout.
Resolve the target identity and ownership before binding the missing destructor.
No alias, additional pin, or speculative owner rename was attempted. The blocker
is recorded separately with re_log.py. The math repair is complete independently.

Dependency sweep: family-census.json records legacy units involving either helper.
InGameUIMessages already localizes floor at this base; other units have independent
findings. No gains in those units are inferred. This repair preserves all helper
semantics; it does not globally replace differing implementations.

BFME1 review: c1315665a1 (DamageInfo) and 6ffd3f498c (AsciiString compare)
show suppression of competing per-unit helper emission. That principle applies;
no donor body, layout or address is transferred. The clean committed BFME1
checkout remains a7c38d3b2597121f178ab5190b3062478823257d. Official master fetched
as 7afa50f4cfe2205fab66de58312bc722dccf8cbe, while file:reference/open-bfme-1
was held by another worker for comparative full verification. No pointer or
freshness-success stamp changed here; freshness remains due. No maintainer-only
runner or full census/link/runtime validation was started.

Reproduce using the base/index in context.json: prepare the two sources, save
their objects under build/pathfind-round-link-20261015/before/, apply the edit,
and prepare the same sources again. Put context.json in that scratch directory
and run proof.py from the checkout. It writes proof.json there. Object caches
and source backup remain ignored; the tracked proof records this experiment.
