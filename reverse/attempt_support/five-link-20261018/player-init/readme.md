Player initializer linkage repair

The old donor Player.cpp still emitted an unrowed Player::initFromDict that competed with the independently verified native 2762-byte implementation. Retire only that obsolete body. Rehome the existing 20-byte Dict copy constructor to its naturally emitted exact native-initializer copy; preserve the three existing getter/setter bodies whose last donor call sites disappear. No new symbol pins or aliases.

Retail call operand at initializer+0xA40 targets RVA3F4DA9, the already matched five-byte LivingWorldBattle query wrapper. Use that wrapper name instead of bypassing it via the underlying 160-byte method. The normal byte gate had accepted the routed call, but stock census truth requires this physical target. This correction makes the initializer selected copy retail true.

Normal before/after gates preserve 25/25 rows across the two player sources; final provider/consumer gate also includes the battle-query provider (27/27). Four parent EH graphs are EXACT. Stock published-index controls replace only explicit objects and forget only the deleted unowned PlayerList TU. Before: two strong initializer providers. After: one native provider. With the preceding getter and cache repairs, the consolidated 1266-byte PlayerList unit now LINKS. The initializer itself still has independent unresolved keys/team copier and COMDAT blockers; this is not a full-game link claim.

Donor provenance remains in the original native source; the BFME1 reference reviewed is a0e8f345a9b22b4b42088e402962287d7015e3c2. Scoped evidence is proof.json.
