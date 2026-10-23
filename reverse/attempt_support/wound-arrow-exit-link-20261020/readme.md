WoundArrowUpdate base-exit binding, 2026-10-20

Current paired legacy preview against e7a7769fe5: 5211 -> 5558 nonpadding
bytes linked (+347). The already repaired SpecialAbilityUpdate provider stays
linked at 5211; it is not counted again. Closed-strict closure unmeasured.

The private nonvirtual onExit declaration in the WoundArrowUpdate base view
produced an undefined private spelling. The real rowed owner at 0x004502CE is
protected virtual, slot 13 (+0x34), as documented by its source and native
vtable evidence. Replace the slot-13 placeholder with that declaration.
Qualify the derived update's call with SpecialAbilityUpdate:: so it retains
retail's direct call. Object size and other virtual slots remain unchanged.
No new pin, alias, or external datum. Existing donor provenance is retained.

Normal byte gate: exact 347-byte update, including its compiler float literal.
prepare-current: both explicit providers strict-current, 21/21 exact rows.
EH graphs checked separately. Declaration gate passes. Two other census
consumers (SpecialAbilityUpdateDtor and VslotSmallBodiesAJ) have additional
unresolved names in their current objects; editing just their exit spelling
would link nothing, so they remain untouched. Four older exit wrappers already
use the rowed virtual spelling and need no repair.

Related unsuccessful probe this session: declaration-only Geometry bounds
setters alter updateMeshVolume byte shape; original restored. Rehoming those
exact emitted helpers could free the allocation owner, but the two helper
RVAs are claimed by another worker. The attempt log records this prerequisite.
