# Wide insert provider selection

At BFME2 39110db385, census d08db10acb (2026-10-21 18:42), the current
money_get string parser emits a non-retail wide _M_insert_aux before the
rowed provider at 0x12D10. The provider is 232 bytes and its sole legacy
blocker is that selected copy. Earlier repair 65408 suppressed the same
helper in stlport_wide_string.cpp; the subsequently recovered money parser
introduced another earlier copy. The BFME1 linking review at cea1e973 is
unchanged; this is the same supported STL provider-binding pattern.

Declare that specialization external in stlport_wide_money_get_string.cpp.
No new body, symbol pin, alias, shared header or identity claim. The parser
and all three EH rows retain their retail bytes, including both funclet
placements. The money parser retains its other independent link blockers.

Acceptance: build.sh passes all four rows; prepare-current passes the same
four rows with a strict reusable compiler receipt. Current-object legacy
link_check of parser and insert owner together changes 0 -> 232 bytes;
restoring the original parser reconfirms 0 -> 0. These are legacy link
results, not self-strict or closed-strict closure claims. The two consumers
of the existing malloc-allocation repair still link 618 -> 618 bytes.
Local evidence: build/link-seat-20261021e/wide-insert-{before,after,strict}.log.

The narrow-string and FX vector declaration-only probes reproduced their
existing MSVC C1001 blockers (narrow-append-link-20261020 and
fx-parameter-vector-link-20261020). Those files were restored, verified
69/69, and their claims released. No new hypothesis or improvement is
claimed for those probes; do not repeat them unchanged.
