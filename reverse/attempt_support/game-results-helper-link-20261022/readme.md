GameResults send helper ownership, 2026-10-22

After the allocator cleanup selection repair (e812f5e07f), sendGameResults has
one remaining blocker: it and createNewGameResultsInterface both provide a
strong explicit deque<GameResultsResponse> push-back specialization. The send
function has no reference to that queue helper. Remove its unused definition
and trailing optimization pragma; leave its earlier declaration and the interface
provider's definition. This fixes a strong duplicate, not an unreferenced
no-address COMDAT diagnostic.

The 197-byte parent and every relocation are unchanged. All retained COMDAT
bodies/relocations agree with the saved before object; 29 unused helper/dependency
copies disappear. Normal byte gate: 1/1, eight named imports verified. Paired
frozen-index preview including the repaired allocator provider: 0 -> 197 B,
with exactly one strong queue helper provider remaining. Both measured providers
have strict compiler receipts. No closed-strict closure or census gain claimed.

Same-cause sweep found only these two strong providers in the published census;
the interface copy remains available to its consumers. No new pins, aliases,
ledger rows or source markers. Removing the unused pragma also lowers hatch debt.
