# ProjectileStreamDraw consolidation prerequisite, 2026-10-25

The device Luna handoff reports the seed failing C2061 for `Snapshot` in
BfmeXfer.h before any donor can be tested. A fresh normal dry run reproduces
that failure under every merged flag set (build/sol-projectile-before.txt).
Current --plan approves 14 rows and retains mixed/protected donor boundaries;
the stale committed TU map is rebuilt in memory, not staged.

W3DProjectileStreamDraw.cpp now includes its existing directory-local
BfmeDrawXferPrefix.h. That header keeps the exact same Xfer operand forward
declarations together with BfmeXfer.h when the composer hoists includes.
Thing, ModuleData and Object declarations remain beside this seed's bodies.
The prefix and shared header are unchanged, as are both authored bodies.
`./build.sh W3DProjectileStreamDraw.cpp` preserves both rows (130-byte shroud
setter and 44-byte xfer), with literal, float, import and declared-unmatched
checks passing. Receipt: build/sol-projectile-prefix-build.txt.

The normal after-trial result and remaining prerequisites follow below.

## Publication audit and claim handoff

The previously published prerequisite batch ends at 89f6c529a5; it includes
Bib allocation, both polygon ctors, the Smudge ctor and release-resource
repairs. Their file claims were released after publication, and
`claims.py release --landed` found zero remaining landed RVA claims.

This final outgoing source change is in place: no source moves, includes
change target, or paths disappear. Active tools, hooks, workflows, includes,
build inputs and registries need no path repoint. The existing prefix already
serves Supply and Laser. No protected register names this seed, and no debt,
row owner, hatch count or historical EA path is changed. Actual source files
removed 0, recovered C++ bytes 0, identity keys retired 0 in this session.

If the final commit is held for the runner's publication, keep these claims
until its landing is confirmed, then release them and run release --landed:

- file:Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DProjectileStreamDraw.cpp
- file:reverse/attempt_support/consolidation-sol-projectile-20261025.md

Other normal merge receipts left for Luna this session:

- LadderDefs: all five whole files accepted, 60 rows
  (build/sol-ladder-find-after.txt); mixed list/destructor files remain.
- dx8polygonrenderer: seed and both constructors accepted, nine rows
  (build/sol-dx8polygon-copy-header-after.txt).
- W3DBibBuffer: seed and allocation accepted, 15 rows
  (build/sol-bib-allocate-after.txt); ctor C1001 and dtor bytes remain.
- W3DSmudge: seed, ctor and release-resource accepted, ten rows
  (build/sol-smudge-release-after.txt); reacquire bytes, copyRect C1001 and
  mixed render/probe/math split requirements remain.
- profile/profile.cpp: unchanged normal trial accepts the seed and two donors,
  27 rows (build/sol-profile-highlevel-before.txt). Leave that compatible merge
  to Luna; this read-only trial produced no source change.

The NetCommandWrapperList pool prefix now survives include hoisting, but the
native getReadyCommands donor still fails C2248 against the pooled node view.
Its earlier attempt and separate handoff retain the evidence. Broad native
reference/node layout reconciliation remains; no repeated body attempt was
retained. Existing shadow identity findings remain registered or reported;
no smaller-file or identity-retirement claim is made by these prerequisites.

## Normal after-trial acceptance

The after trial accepts the seed and W3DProjectileStreamDrawModuleDataDtor.cpp,
two files and six rows, versus no accepted files before the prefix repair.
Receipt: build/sol-projectile-prefix-after.txt. The constructor donor now
reaches C2504 (`DrawModule` base undefined); the destructor donor reaches
C2143 (missing `;` before `*`). Neither donor was edited. Mixed deleting-dtor,
name-getter and RenderObj sources retain their split boundaries, and all
three protected donors remain refused. Leave the compatible subset for Luna.
