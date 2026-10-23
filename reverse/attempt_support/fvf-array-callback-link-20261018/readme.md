FVF material/texture migration callback repair, 2026-10-18

Paired legacy link_check with current fxshadernamespacesas.cpp and Rva001447B0Dtor.cpp providers: 11,816 -> 13,726 matched bytes link (+1,910 B). The latter provider already frees its own 165 B before this change, so those bytes are excluded. Census c2c5ac8c27. Self-strict receipts cover this unit's 4/4 rows; closure is not checked and no closed-strict gain is claimed.

The native vector-constructor call independently identifies the null-initializing four-byte texture-handle callback at 326BE6. The existing size-optimized fxshadernamespacesas.cpp emits that same complete six-byte callback. The migration unit's generic /O2 instantiation emitted nine bytes. An explicit TextureClass specialization under size-on/speed-off optimization now emits exactly 8BC1832000C3 without relocations. Applying the pragma to the generic template definition did not change its eventual instantiation; that trial was discarded. No new identity, pin, linker alias or table owner is claimed.

All 4 existing rows pass the byte gate, including the renumbered funclet proven by parent EH. EH: 2 EXACT. Enforced data check: zero findings; converged check: 9 addresses, zero second names or unjudged rows. find_declared_unmatched and check_csv pass. Optimization pragmas are counted by the existing shadow hatch check; no baseline is changed.
