# Object creation helper ownership, 2026-10-21

Input BFME2 6e4198f56d, BFME1 verified pointer 68c5ce27, published census
2b4d1fb42a (2026-10-21 06:00). Current baseline: all seven ledger rows exact,
but legacy preview links 0/2618 B for duplicate/losing ThingTemplate build
limit getter, losing Player default-team getter and iterator-base inequality.

Both local field getters already expand in the matched parent. Make them
import-forceinline, as the established BuildAssistant getMaxSimultaneousOfType
view does, so they cannot emit competing out-of-line definitions. The actual
ThingTemplate.cpp implementation includes restriction logic; this view is
valid for the proved native field reads, not a replacement for that body.
Player::getDefaultTeam is rowed at 0x46F7E4. No type/layout/pin changes.

The horde loop compares a const iterator with a mutable end iterator. Add the
established exact-type inequality overload with independent left/right traits,
comparing node pointers. The initial same-traits overload preserved all seven
rows and removed the getter blockers but left the base inequality copy; the
cross-traits version removes the last blocker and still preserves every byte.

Acceptance: build7/7 exact; all three literals and two float references
verified, zero unverified/skipped references. Five compiler label renumberings
are independently proven against native parent EH actions. Parent EH EXACT.
--prepare-current produces the strict reusable receipt. Declared-definition,
class gate, enforced converged-data (10 addresses, zero second names or
unjudged rows), check_csv and whitespace checks pass. Legacy current-object
same-index preview LINKS, 0 -> 2618 B. Self-strict byte verification and legacy
prediction only; no closed-strict or actual placement gain claimed.

Cause sweep: census blockers contain no other getDefaultTeam consumer. The
only other getMaxSimultaneousOfType unit is the full ThingTemplate.cpp (47
independent blockers). No iterator-base inequality consumer has fewer than
three blockers. Thus no extra edits with unmeasured benefit are included.
Existing isKindOf/getName copy diagnostics are unreferenced and not blockers
under retail-truth-2; they remain unchanged. No donor source imported.
Scratch: build/seat-really-{before-byte,before-link,trial1-byte,trial1-link,
trial2-byte,trial2-link,final-strict,eh}.txt.
