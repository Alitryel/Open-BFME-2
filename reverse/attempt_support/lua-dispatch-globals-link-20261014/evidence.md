Lua script dispatcher global binding repair
===========================================

The action and condition dispatchers declared TheScriptActions and
TheScriptConditions using private interface-view pointer types. Their
canonical strong definitions in ScriptEngine_init.cpp instead use
ScriptActions* and ScriptConditions*. MSVC consequently emitted distinct
unresolved data symbols. Declare the canonical globals, then cast at each
existing virtual call to its unchanged local interface view.

The owned data ledger independently assigns the canonical symbols to RVAs
0x00A02D98 and 0x00A02E04. Retail ExecuteAction at 0x0033436F loads VA
0x00E02D98 at operand RVA 0x003344CF and calls vtable slot +0x38.
EvaluateCondition at 0x00334212 loads VA 0x00E02E04 at operand RVA
0x0033432E and uses the same established slot. These addresses and call
operations are target evidence. Interface method/class names and the Lua
algorithm come from the existing matched donor-derived source; this repair
establishes no new class layout, original global name or code identity.

Donor review: BFME1 commit 0835ab92bef30e3303e729a0ce09cf591368d0cd
binds two Apt local views through their owned global's declaration. Its
binding principle applies; its names, types and addresses do not. BFME1's
Lua sources own interface-typed globals, so copying those declarations into
BFME2 is inapplicable. No donor code or layout is imported.

Base BFME2 commit: 4255d25adc3bc27d0c42ce16fd5807ddf12f93fd.
Index: 147cfae2cb, 2026-10-14 07:27; SHA256
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
The committed link-status snapshot serves discovery only. The same index
and three-unit cohort are used before and after. No missing per-row data-
back artifact is used, and no census/status/history is changed.

Before: strict preparation verifies all four executable rows across the
three units. Legacy preview has two unresolved consumers and one clean
provider: 416 -> 416 linked bytes. Data shadow audit independently reports
exactly the two corresponding wrong-name bindings. Dispatcher EH is exact
for both rows. Provider init's EH bytes_differ is existing baselined debt.

After: ./build.sh over both consumers and ScriptEngine_init.cpp passes
4/4 matched rows, all literal/import references, and strict preparation
again verifies all three units. Local link_check.py on the identical index
reports all three units clean: 416 -> 1170 bytes, a gain of 754 existing
authored bytes excluding 0xCC padding. No new authored C++ bytes are claimed.
Consumer data audit drops from two wrong-name findings to zero. The cohort
retains one existing baselined provider finding (_st_DebugDLL); converged
data audit has zero second names and zero unjudged bindings. Dispatcher EH
remains EXACT for both rows, with only the unchanged provider's baselined
EH difference remaining.

All COFF section bytes, extents, relocation offsets and relocation kinds
are preserved. The sole external relocation change in each consumer is its
owned global's mangled name. Compiler-local $T/$L labels renumber because
the added declarations consume compiler symbol IDs; their section/value
identity is unchanged. The provider's whole object SHA256 is unchanged.
Object comparison evidence is in object-proof.json. Frozen-file and class
gates pass, check_csv.py passes (88286 functions, 17019 pins, 425 data), and
git diff --check passes. place_bodies.py reports zero bodies and zero pins.

Explicit checks:
  python3 tools/link_check.py --prepare-current <the three cohort paths>
  ./build.sh <the three cohort paths>
  python3 tools/link_check.py <the three cohort paths>
The supplied units have current strict receipts; unrelated stale units are
not refreshed and no full census or link cycle is run. Companion logs
record byte, data, EH, placement and before/after link results.
BFME1 freshness remains due. The clean checkout and committed pointer stay
at 23b143233b5a8664a3bdf8572df6d905c310a5a1. Official upstream master was
fetched at a7c38d3b2597121f178ab5190b3062478823257d (three commits ahead;
only an Apt source and two attempt records changed). The existing migrated
layout resolves all six directories, the consumer headers were inspected,
and lift_lane.py exists at the retained pointer.

Comparative full byte verification was not completed. The previous-input
serial baseline rebuilt roughly 4975 of 8291 stale TUs before a clean
interrupt; a subsequent BUILD_POOL=8 retry had 3316 stale TUs and waited
for another full build's shared compiler lock, then was cleanly interrupted.
Neither run produced a full function verdict. No upstream-input run was
started, no pointer was advanced, and bfme1-last-check.txt remains stale.
The baseline interrupt/lock logs are included to identify this blocker;
there is no claim of a full gate pass or regression assessment. Resume the
freshness comparison when the shared compiler scope is available.

The checks are self-strict compiler receipts and a local legacy link
preview. No closed-strict closure, real link.exe/data-back placement or
new census gain is claimed. A full link measurement remains maintainer work.
