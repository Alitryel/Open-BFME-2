# SidesList post-load link repair

At BFME2 88983ceb42, the current-object legacy preview of SidesListCtor.cpp
plus its existing SubsystemNameGetters2.cpp provider is 268 -> 268 authored
nonpadding bytes: the constructor unit's 999 bytes remain excluded solely
by undefined SidesList::LoadPostProcess. The getter provider must be included
in both previews because the published census predates that provider.

Native constructor 32EE24 installs the secondary Snapshot table C0DA88.
Its four entries are 32ED59, B3FD0, 32ED53, and 329AEA. Slot 1 thus supplies
the canonical Snapshot zero-argument post-load hook through the shared empty
RET, rather than a missing substantive method. Define that existing method
and row its complete one-byte, relocation-free ICF twin. No pin or new datum
is needed. The target table establishes the binding; no donor identity is
inferred from byte equality. BFME1 checkout 138757e9b remains the verified
reference pointer; review of upstream linking changes at 38cba658a found no
additional donor repair needed for this target-specific missing definition.

After: the same two-source legacy preview is 268 -> 1,267 bytes, +999 B,
2/2 units link. This is not an actual-link or closed-strict measurement.
Strict reusable byte preparation passes 43/43 rows, all string/import/float
checks pass with zero skipped references, and all four EH graphs are EXACT.
The added row has zero unique retail bytes. Existing function bodies and
layout are preserved; compiler-local EH labels are resolved by their exact
parent graphs. Scratch results: build/link-seat-sides-{add,after,strict,eh}.txt.

The same-cause queue sweep found remaining post-load blockers entangled with
different class contracts, other undefined substantive methods, or competing
vtable providers. They do not justify copying this empty method blindly.
