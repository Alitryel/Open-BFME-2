# MultiByteToWideCharSingleLine link repair

Resume reverse/attempt_support/multibyte-link-blocker-20261022.md using the
member-template syntax established by the wide-string assignment repair.

Keep the wide C-string constructor visible: its empty-allocator non-escape
information is necessary for the native 195-byte parent. Declare only the
wide forward-iterator range initializer, specializing the outer string type
while retaining the iterator template parameter. This form compiles under
VC7.1, unlike the prior fully specialized range declaration that crashed
in _string.h:376. It emits no competing const-wchar range initializer and
resolves to the existing same-named STLport provider.

Normal build: 3/3 exact, including handler and 25-byte unwind code. The
renumbered local label is verified against the parent's EH graph; both
named imports verify. Placement resweep: zero bodies and pins.

Paired before/after previews use identical current stlport_money_put_wide.cpp
and index 491a8b3d87 (2026-10-23 03:12 UTC), restoring the original consumer
and rebuilding it for the before measurement. The consumer changes from
0 to 204 nonpadding linked bytes. Every provider blocker is unchanged,
including its unrelated locale IDs, constructor, destructor and do_put
issues; that provider still does not link. No claim of full link-cycle,
closed-strict or runtime validation. Source flags, rows, pins, aliases and
shared headers are unchanged.

Identity and behavior were already established by this function's existing
BFME1 donor and native row; this change preserves them. The new declaration
is a compiler visibility repair to the existing STLport template.

model=gpt-6-astra seat=s4
