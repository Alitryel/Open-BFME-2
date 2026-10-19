# Weapon private firing: typed bonus boundary and compiler checks

Complete 2494-line Weapon.cpp owning unit, both saved banks, both caller handoffs and helper return-value evidence reviewed. The owner remains unchanged and its frozen-file check passes. Prior ordinary provider-visibility and bonus-scope experiments were not repeated. Current whole-owner placement search yielded zero bodies and zero pins.

Native 0x002CE30A..0x002CE6C5 is 955 bytes, RET 36. Its six-float bonus starts at EBP-0x24; both later target-coordinate branches use EBP-0x18. The saved caller emits 955 bytes but allocates EBP-0x30 for bonus: eight frame/bonus operand differences, zero structural differences and six relocation-only memory lines. The existing eight-byte blocker is reproduced.

Fresh hypothesis: opaque integer conversions of bonus addresses may hide their use/lifetime from the compiler. Tested firing boundary as const WeaponBonus reference, both firing and special boundary as references, and both as pointers. All preserve 955 bytes and the identical 0/6/8 alignment counts. These are diagnostic declaration changes, not established replacement identities or admitted bindings.

The existing opt-in Coord3DDerivedView header with inline default/copy/destruction reproduces the bank without a private canonical class. Authenticated DDK 13.10.4035 and SP1 13.10.6030 profiles preserve the same caller differences. No shortened bonus, union, expired object, volatile operation, assembly, invented standard-convention helper pin or production reconstruction was introduced. Native six-float reset and the independently verified 86-byte computeBonus owner rule out reducing the bonus extent merely to fit the frame.

Both stronger banks are preserved unchanged. The 199-byte helper was not independently re-admitted; its existing exact result with the real caller remains prior evidence. No full-unit integration, new recovery or successful landing is claimed. Scripts and raw logs retain reproducible tests. Model gpt-6; about 9 minutes.
