# Wide currency padding helper ownership, 2026-10-23

Parent 26517f55f4; published retail-truth-4 index b711de3634 (2026-10-23
14:28). BFME1 verified checkout remains 96c88c73a5cd1a58fc2f8db691beea50acd996db.

The current formatter `stlport_wide_money_put_string.cpp` emitted a non-retail
explicit `fill_n<ostreambuf_iterator<wchar_t>, unsigned, wchar_t>` specialization.
The indexed retail provider is `stlport_money_put_wide.cpp`, whose owned 103-byte
body is at 0x00019B80. This is the only competing pair for this name in the index.
The wrong copy was still selected even after the upstream provider-scope repair
(record 82396). The narrow currency formatter already uses an ordinary inline
padding helper to preserve these inlined loops without emitting that specialization.

Apply the same source-local pattern to the wide formatter: retain the loop and
its inline-depth setting, call a static forceinline helper, and leave the
existing declaration-only template binding in place. No row, pin, ABI, type,
string, compiler flag or dependency changes. This helper's name describes this
implementation only; no new target identity is asserted.

Same current-object cohort, same published index, legacy preview:

| Unit | Before | After |
| --- | ---: | ---: |
| stlport_money_put_wide.cpp | 0 | 133 |
| stlport_wide_money_put_string.cpp | 0 | 0 |

Gain: **133 counted linked bytes**, no new authored or unique retail bytes.
The formatter still has independent string-base destructor, wchar range
constructor and mutable narrow range-initializer findings. No full census or
closed-strict closure gain is claimed.

Acceptance: scoped normal byte gate 10/10 formatter rows; strict reusable
provider preparation 13/13 across both units; exact parent EH graph maps the
renumbered labels; find_declared_unmatched, new COMDAT variants and check_csv
pass. Hook acceptance additionally checks the EH and data constraints.
Diagnostics: build/link-seat-wide-fill-{gate,after,strict,variants}.log;
paired baseline is the first two units in build/link-seat-duplicates-before.log.
