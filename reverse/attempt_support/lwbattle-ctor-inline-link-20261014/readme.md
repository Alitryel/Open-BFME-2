# LivingWorldBattle constructor wrapper repair

At base `03fd36e223`, LivingWorldBattle.cpp emitted an 18-byte external
Rva004FA2E2 constructor wrapper despite inlining every use. The wrapper
forwards to the existing LivingWorldAutoResolveBattle constructor; it is not
retail's full constructor at 0x004FA3C9. Its competing name produced a COMDAT
and wrong-selected finding. Mark that existing forceinline wrapper dllimport
so MSVC retains the inline operation without emitting an external copy.

Native RetreatArmiesForPlayer at 0x003F6727 remains exactly 527 bytes, including
its constructor call and all relocations. This preserves the existing vector
storage view and introduces no target identity or layout claim. The other
source declaring this wrapper name, LivingWorldLogic.cpp, already has only a
declaration. There are no other definitions of this constructor signature.
No ledger row, pin, alias, global, header, compiler setting or baseline changes.

The paired legacy preview uses runner index measurement `147cfae2cb`,
2026-10-14 07:27, SHA256 in index-meta.json. Both sides replace the same two
objects: LivingWorldBattle and AutoResolve/LivingWorldAutoResolveBattle.
The committed link status has a different measurement and is discovery only.
The consumer goes from two findings to zero and 0 to **1,959 existing linkable
bytes**. The unchanged constructor provider retains all thirteen independent
findings (three duplicates, seven COMDAT conflicts, three selected bodies).
The combined local link command exits 1 because that provider remains blocked.
No census/index/status is updated. No closed-strict, actual-placement or
full-link gain is claimed; new authored C++ bytes are zero.

Acceptance:

- Strict-current preparation verifies the original consumer's 13 rows, then
  consumer plus provider 42/42 rows after. The unchanged provider object is
  used on both sides of the comparison. The ordinary ./build.sh gate also
  passes 42/42; five literals and two floats verified with zero skipped or
  baselined string/import checks. Strict reusable receipts are preserved.
- The object proof removes precisely the 18-byte wrapper, with zero incoming
  nondebug relocations. All 55 retained external COMDAT bodies, extents and
  relocation digests are equal. All other nondebug sections and normalized
  relocations match, including EH tables after local-label renumbering.
  Strong, undefined and weak external sets are equal; no import indirection
  is introduced. Object hashes and complete paired findings are recorded in
  object-proof.json. Scratch objects/receipts are in build/lwbattle-link-20261014;
  proof.py reproduces the assertions using those snapshots.
- EH verification: 10/10 EXACT, zero baseline or missing objects.
- Frozen definitions, class gate and new-variant admission pass. Enforced data
  checks report zero findings; converged checks judge eight addresses with
  zero second names or unjudged rows. Placement resweep finds zero bodies/pins.
- Ledger and whitespace checks pass; commit hooks run normally.

BFME 1 linking review: clean verified pointer a7c38d3b2597121f178ab5190b3062478823257d;
reviewed donor de59a7e9f891b3ed2d4221d151ca881f4b75a583 and its scoped byte/link
evidence. Reconciling incidental private COMDAT emission is applicable; its
Apt predicate spelling and layouts are inapplicable. No donor code is imported;
the local range-erase inline-only repair supplies the compiler technique and
independent BFME 2 byte/object evidence establishes this repair's validity.
Official master fetch resolves to 4b2a6f64aa83cd66e01cd83574cc64cc366a440e.
The verified gitlink/checkout are retained pending comparative full verification:
prior baseline attempts document compiler stalls and thousands of stale TUs
(terrain-small-link-20261014/readme.md). That unchanged prerequisite was not
repeated or marked successful during this bounded linking task.
No maintainer-only link cycle, census build/measure/history, nightly or boot
runner was started. Closed dependency and full placement checks remain outstanding.
