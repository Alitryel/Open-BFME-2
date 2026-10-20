# Campaign record cleanup linkage

The native vector overflow at 1ED476 (183B) calls clear1ED3A2 (30B),
which calls the already rowed Destroy loop1ED34A (25B). That loop steps
36 bytes and calls destructor1ED0DE (92B). The copy/construct/fill helpers
and parser1ED580 establish one36-byte campaign record, currently split
between Rva001ED03C and Rva001ED0DE address-named ABI views. Payload and
original class identity beyond the existing parser evidence remain unknown.

The vector TU previously instantiated cleanup through an undefined
Rva001ED03C destructor. Specialize only its clear path to use the existing
Rva001ED0DE destruction range, then free the existing storage. This preserves
the whole30-byte cleanup under its existing fold pin and calls the native
rowed destruction helper. No new pin, data alias, ledger row or header edit.

Paired current-object legacy prediction improves25 ->263 linked bytes
(+238B). Both183B/55B rows pass the byte gate. Strict self preparation
verifies6/6 rows across the consumer, destruction loop, destructor and
original clear provider. The six-unit family sweep is6/6 link clean, with
only the growth TU gaining bytes (762 ->1000 combined). Frozen definitions,
class gate, data shadow and new variants pass. No closed-strict gain or full
link-cycle/census measurement is claimed. Existing fold proof is retained.
BFME1 revision reviewed this session:92f6bbe8e1dcdb46b5d27da0674313efc822b790;
no donor source is imported by this target-evidence cleanup reconciliation.
