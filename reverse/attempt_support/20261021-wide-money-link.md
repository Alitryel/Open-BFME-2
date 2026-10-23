# Wide money numeric parser link repair

At BFME 2 d08db10acb census (2026-10-21 18:42), paired current-object
checks of the wide numeric money parser, classic locale, wide money facet and
wide string insertion units move from 0/4, 0 bytes to 1/4, 301 bytes. This is a
legacy link_check gain; closed-strict closure has not been established.

Whole-class money_get instantiation emitted a vtable referencing the separate
string parser, whose selected definition is not retail. The narrow numeric
parser already uses explicit method instantiation. Applying that pattern to the
wide numeric overload removes this dependency without changing its 277-byte
body, 10-byte EH handler or folded 14-byte string destructor. The 30-byte facet
constructor is already emitted by stlport_classic_locale.cpp; add_match verified
that exact body there and rehomed its existing row. The locale remains blocked
by its existing provider and COMDAT problems. No authored C++ byte growth.

Checks: full pre-change byte gate 97929/97929; add_match locale 37/37; parser
3/3; prepare-current both units 40/40 with strict reusable receipts (this only
prepares providers, not LINK closure); check_csv; find_declared_unmatched both
units. Raw paired logs: build/link-seat-20261021d/wide-{before,after}.log.

Related unsuccessful trial: declaring the POD vector _Construct helper nothrow
kept all 3 rows exact but merely changed wrong_selected into unresolved, 0/207
bytes linked; source reverted and claim released. Its existing forceinline
trial already proves a 69-byte constructor versus retail 68, so do not retry
that unchanged hypothesis.
