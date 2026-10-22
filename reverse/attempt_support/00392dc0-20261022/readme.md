# BuildAssistant 0x00392DC0: exact recovery

Recovered the entire 1116-byte range 0x00392DC0..0x0039321C as C++ in
`Code/GameEngine/Source/Common/System/BuildAssistant.cpp`. The address-derived
method name remains: the WorldBuilder callgraph twin is a structural lead,
not proof of a real method name. Input BFME2 revision:
`4b2a1bb738f2a1315955f77c245a365c7b01779c`; BFME1 reference:
`37c3022de1ab944c7ffe536440d637dc8199091c`. Model: gpt-6.1-sol.

## Evidence and provenance

The earlier 20261019 and 20261020 handoffs establish the retail boundary,
thiscall ABI with six stack words, target offsets and virtual calls, and the
WorldBuilder twin at VA 0x00F96810. This session started from the retained bank
and read that history before experiments. The bank measured 1111 bytes and
18 normalized instruction differences. No donor implementation was imported.
The nested producer call and inline template accessors follow the twin's
source-shape evidence. Target bytes, existing callee rows and the final gate
establish their BFME2 relationships and layouts independently.

The home tile view now exposes its existing array at +8 and object ID at +0x14
(the complete record is 24 bytes). Existing callers retain their field names
through unions. Existing Object accessors supply template, ID, dead-state and
body access; the two object writes retain the bank's target-proven +0x280 and
+0x324 layout. Existing Object::setBuilder at 0x28AFE7 replaces the stale bank
callee spelling. The real converged GameLogic and PartitionManager globals
are used. There are no new pins or alternate symbols for their addresses.

## Winning interaction

The final body combines these choices; independent one-change trials missed
how their live ranges interact:

1. Inline STLport's real list<int>::insert while declaring its node factory
   and list-base destructor out of line. The hidden insert-result temporary
   then shares the unsigned-price stack slot and the frame is retail's 0x70.
2. Keep the producer call nested in the behavior call and inline the real
   Thing::getTemplate accessor at the refresh condition.
3. Read the index through a volatile unsigned alias only for the refresh
   template getter. The conversion is the same 32-bit value; the additional
   observable read makes the compiler select the native stack-home use.
   The increment, multiplier and price getter use the ordinary index.
4. Declare a signed index before an explicit nonempty-count guard, then run
   `for (; i < tiles.count; i = i + 1)` inside that guard.
5. Bind the price template as `const ThingTemplate *const &tile` to the getter
   result. Combined with the loop guard and signed index, this fixes both the
   index/vtable register allocation and the later lookup-result copy order.

The winning factorial entry was `edgeform-0-5-11`: loop form 5, mask 11
(normal increment, signed index, const-reference price template). A reduced
probe, a real-home-prefix probe, and the complete home TU all reproduced all
1116 relocated bytes with no unresolved calls. The EH graph was EXACT in both
probes and is rechecked on the final home object. The original home compiler
flags suffice; the bank's extra /G7, /DNDEBUG and /I. were removed again.

## Other hypotheses tested this session

The scratch family drivers and unique source/object outputs were isolated in
`build/buildassistant-oct22/`; none used build.compile_source or altered the
shared match object for a scratch trial. Eight compiler processes ran in
parallel. Searches stopped when the exact variant appeared.

- Control flow: index entry/guard/latch families, ordinary and volatile index
  uses at each read, positive build-success guards, expression ordering and
  increment forms. The guard/sign/reference combination above closed it.
- Lifetime and declaration scope: aliases, temporary and local permutations,
  producer-result shapes, loop-scoped and function-scoped declarations. They
  improved intermediate register webs but did not independently close them.
- Types and layout: Object accessors versus views, signed/unsigned index
  types, iterator/value aliases and the existing native class prefixes. The
  winning body uses the home accessors rather than importing duplicate classes.
- Callee visibility: opaque/visible insert and node creation, getter wrappers,
  virtual-call contracts, throw specifications and same-unit class context.
  Making insert visible was necessary to reproduce the frame/price home.
- Compiler settings: retained the proven /O1, /EHs, /MD and /arch:SSE home
  profile; the bank's redundant flags do not affect the final match.

Narrow index types and compiler-internal allocation diagnostics were scratch
experiments only. They were not accepted as semantic repairs and contribute
nothing to the landed body. No assembly, emitted bytes, optimizer pragma,
semantic restriction, or artificial extra runtime branch is used.

## Acceptance

- Normal `add_match.py` and `./build.sh` pass all 48 home-TU function rows,
  the data row, two string literals and 42 float literals.
- `find_declared_unmatched.py` reports all definitions already matched.
- `place_bodies.py` reports zero additional bodies and zero pins.
- `link_check.py` reports the complete home TU LINKS, 11615 linked bytes
  versus 10490 in the published census (the new body is 1116 bytes).
- Ledger, EH and final staged-hook results are checked before committing.
