# Behavior wrapper ownership repair (2026-10-18)

CastleBehavior and StancesBehavior deleting wrappers already compile in their real destructor units. Focused `rehome_rows.all_exact` checks establish their whole retail bytes and relocations there; `add_match --replace-existing` independently verifies both new row owners. Their audited owner identity and call evidence is preserved in the ledger. Remove the two old synthetic constructor scaffolds and their partial vtables.

Before and after previews use the same three current objects and ledger rows. `before.log` also includes two unchanged static-sort units, which already link with current objects and were left alone. The behavior units improve from 338 to 450 linked bytes (+112 B): the old wrapper unit now links its remaining 56 B, and both destructor owners acquire their 28 B wrapper rows. No authored C++ coverage grows.

`prepare.log`: 15/15 normal byte checks and strict reusable receipts for all three explicit providers. This is a legacy link prediction with self-strict provider evidence, not a closed-strict census or full link result. No census/index/status changes were made.

The related AttackNugget wrapper was not moved: its existing constructor provider still has an unresolved NuggetBase destructor and wrong selected constructor, so the paired current preview stays at zero. The blocker was recorded and its claims released.
