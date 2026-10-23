# MetaImpact float CRT link repair

At BFME2 32f7ffbd1f, the frozen published census index is 2b4d1fb42a
(2026-10-21 06:00). Ordinary current-object link_check before the change
reports 0/1879 real bytes linked, with exactly two losing copies:
?cos@@YAMM@Z and ?sin@@YAMM@Z. The existing parent's float overloads
already call the CRT float routines; spell those calls cosf/sinf directly.
No class, layout, compiler flag, global, reference address or identity changes.

Acceptance: ./build.sh passes all four rows (434, 751, 10 and 687 bytes),
two string literals, fourteen float literals, zero skipped references, and
the existing data row. --prepare-current independently supplies a strict
reusable receipt and repeats those gates. eh_verify: one EXACT EH graph,
zero discrepancies. Enforced converged data: ten addresses, zero second
names or unjudged rows. Declared definitions and whitespace checks pass.
Current-object link_check now LINKS, 0 -> 1879 B on the same index. This is
self-strict byte verification and a legacy census prediction; no
closed-strict closure, actual link placement or new authored bytes claimed.

Sweep: the same index names two additional sin/cos consumers, pathfinder.cpp
and HordeContainIface11CSlots.cpp. Both retain many independent blockers
(31/21); no unmeasured edits were made to them. Previous unrelated portal
and strafe wrapper repairs were read; their scheduling failures do not
recur in this whole-unit byte gate.

BFME1 verified checkout 68c5ce2789e974f36b6c742d57437d157bc159e9 was reviewed,
including its PersistentStorageThread.cpp and STL tree destructor source;
those transfer leads are respectively foreign-claimed and unrelated to this
local math emitter fix. The previously recorded emitter ownership repair
principle (d2e213690, geometry-sqrt-link-20261013/readme.md) applies; no donor
source, layout or address was imported. Official master was fetched at
5987fd1b859e86801d093256eadc6fb63d87785f. It differs in 146 paths under
game/inputs/tools/lift_lane.py; a verified pointer update still requires the
full comparative old/new byte baseline and affected donor-cache refresh.
That update was not completed in this bounded linking pass. The clean
verified pointer is retained and no successful freshness stamp is written.

No census build/measure/history, link cycle, nightly or boot runner started.
