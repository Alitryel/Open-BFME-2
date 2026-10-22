# Wide num_get helper ownership, 2026-10-22

Current source before repair: link_check reports 0/563 legacy linked bytes.
Its unrowed unsigned-int do_get overload instantiates two competing integer
scanner helpers. The census keeps the same do_get body in stlport_classic_locale
(e43b40bd1dc1), whose scanner dependency is already first in link order.

Declare that unowned overload without defining it here. Explicitly instantiate
four rowed iterator operations it formerly caused to emit: _M_bumpc, operator*,
operator++, and operator!=. The remaining owned iterator and num_get bodies
continue to emit through this unit's existing instantiations.

Acceptance: build.sh 13/13 exact, literal/import references pass,
find_declared_unmatched passes, link_check --prepare-current passes with strict
reusable receipts. Ordinary link_check then reports LINKS 0 -> 563 legacy
bytes. No self-strict/closed-strict link-cycle result is claimed. Census index
08160bc2c9, BFME1 verified pointer 37c3022de1ab944c7ffe536440d637dc8199091c.

Publication reconciliation: upstream d8e35779cb independently resolved this
unsigned-int scanner dependency with helper declarations and the same iterator
instantiations, together with additional scanner-provider repairs, before this batch rebased. Keep upstream's
source in full. This commit preserves the independent experiment and blocker
handoffs; its 563-byte result is historical evidence and contributes no
additional gain over the updated origin/master.
