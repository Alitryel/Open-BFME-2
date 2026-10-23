Partition provider binding, 2026-10-18

The sort unit's extra __unguarded_partition instantiation differed from the
separately rowed owner at RVA 21C6CB. Declaring that specialization makes sort
call the owner without emitting its competing partition, swap, and iter_swap
COMDATs. The owner's C++ and object remain unchanged. These descriptive types
retain the existing ledger identity; no original target class name is inferred.

Paired replacements of the same two objects against census c2c5ac8c27 predict
847 -> 964 nonpadding matched bytes linked: the partition's 107-byte body and
10-byte unwind handler newly link, while sort's 847 bytes continue to link.
This is a legacy prediction; no closed-strict link-cycle gain is asserted.
Both objects have strict reusable receipts covering all 15 matched rows.

proof.py checks retained nondebug code/data bytes, flags, definitions, symbolic
relocations and normalized SafeSEH entries against the saved baseline objects.
The only added linker directive is MSVC's compiler-generated fallback from the
template specialization to a non-template name. The proof checks that exact
delta and the real template definition in the unchanged provider; the fallback
is unused when that definition is present. All other directives are identical.
No source-level /alternatename or new pin is introduced. Baseline objects live
locally under build/seat8-partition/before; proof.json records their hashes and
the fixed index hash for reproducibility.

Checks: ./build.sh on both units (15/15); link_check.py --prepare-current on both
units before and after; paired proof.py; check_csv.py; normal commit hooks.
No full link, census, nightly, or boot runner was started.
