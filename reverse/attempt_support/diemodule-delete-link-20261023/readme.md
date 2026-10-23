# Superseded DieModule experiment and verified reference update

Publication reconciliation: upstream 4321ed9ff6 independently repaired the
DieModule providers before this batch published. Its existing canonical provider
is retained. This seat's alternative macro header, include edits and duplicate
row were removed from the outgoing commit. The 240 B below is historical local
evidence, not an additional gain over current origin/master. The retained change
is the verified BFME 1 reference pointer update and this evidence.

At BFME 2 800e4b6c94, using BFME 1 donor 74ea60ad41ef, the current paired
legacy preview was 0/240 matched bytes across SpecialPowerCompletionDie.cpp,
CreateObjectDie.cpp and FamilyDeletingDtors_0021C7e.cpp. The kept deleting
destructor was a 14-byte wrapper emitted by CreateObjectDie.cpp. The last
unit's separate 28-byte retail copy could not repair that selection and its
one-slot private DieModule table was itself a COMDAT loser.

Target evidence: native 45CEF4..45CF10 calls the complete destructor at
45CE54, tests deletion flag bit 0 and conditionally calls global operator
delete at 2FD60. The ZH MEMORY_POOL_GLUE_ABC macro instead defines an empty
ordinary delete operator. BfmeDieModule.h retains the donor class definition
and all other macro members, changing only that ordinary delete operation
for DieModule. BehaviorModule is included before the temporary macro override,
so no other abstract class receives the allocation change. The existing
class/function names remain inherited identities; this repair establishes
the target allocation behavior, not new application field names or layouts.

Both reference-derived units now emit the whole native 28-byte wrapper.
The row is moved into SpecialPowerCompletionDie.cpp through add_match's
verified replacement; the obsolete one-slot class stand-in is removed.
Before moving the row, the two repaired units link 212 B; after moving it,
the paired legacy preview links 240 B (185 + 55). All eight retained rows
pass the ordinary byte gate, strings/floats/import checks and strict reusable
compiler receipts through link_check --prepare-current. Neither unit has
EH-bearing rows. No new pin, alias, baseline, or ABI escape was added.
This is a legacy preview gain with self-strict compiler evidence; no
closed-strict, full-link, data-back or runtime gain is claimed.

Same-cause sweep: InstantDeathBehavior.cpp no longer has a selected deleting
wrapper blocker when evaluated with the repaired providers. Its separate
BehaviorModule and complete DieModule destructor conflicts remain, so it was
left unchanged. No additional census consumers of this deleting-wrapper
blocker were found.

BFME 1 freshness: advanced committed donor inputs from 138757e9 to official
master 74ea60ad41ef after the full BFME 2 gate passed all 98,105 function rows
and 2,140 data rows, plus strings, floats, imports, DIR32, pins, module
registry, source claims and no-op patch. Layout resolver checks passed 18/18;
resolved game, reference, toolchain, baseline, vendor directories and actual
headers were checked. The regenerated BFME 1 sweep records this revision;
ranked byte donors returned zero and the lift lane ran at limit 1000.
