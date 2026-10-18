# Sphere helper ownership

The native Add_Sphere body is already rowed at 0x0019BE00 (277 B).
Current hlod, collect and composite objects emitted a different COMDAT, which
prevented the retail owner from linking. Preserve the complete BFME 1 sphere
header from verified donor 64d369b90170b7e9ec917d646f020b11f13eb0d5, changing
only Add_Sphere to an out-of-line declaration. This keeps all other inline
visibility and the established target layout. No new identity or layout claim.

Same explicit four-source cohort and census c2c5ac8c27 before/after:
legacy preview 0/4 -> 1/4 units, 0 -> 277 linked matched bytes. Caller units
still have other blockers. This is not a closed-strict result.
Strict reusable receipts and ordinary byte verification: 188/188 rows,
including native EH graphs and renumbered funclets, plus string/float/import
references. No retail rows, pins, globals or baselines changed.
