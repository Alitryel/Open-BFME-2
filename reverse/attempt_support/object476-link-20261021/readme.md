# Aggregate vector helper ownership

Inputs: BFME2 7c06faa3fc, verified BFME1 pointer 68c5ce2789, published link
index 2b4d1fb42a (2026-10-21 06:00). Existing /O1 /SSE2 /MD /EHsc flags
and dependencies retained. No identity, layout or pin changes attempted.

Baseline: all 135 rows byte-exact. Current-object legacy link preview holds
out 2,491 real bytes on vector<void*>(allocator), its allocator-only base
constructor, and the empty allocator-proxy destructor. This is not a
closed-strict placement measurement.

An imported forceinline vector/base constructor and empty proxy destructor
remove the three competing copies but inline base initialization into the
64-byte hashtable constructor at 1FE312: 134/135 rows pass. A declaration-only
base constructor restores the native call to 25100, but adds EH states and
one stack slot: native starts `51 56 8b f1 8d 45 0b ...`; candidate starts
`51 51 56 8b f1 89 75 ec 83 65 fc 00 8d 45 f3 ...`. The final candidate
is preserved in candidate.cpp.txt; production source was fully restored.
An initial declaration-order compile error was fixed by declaring the base
destructor before the constructor specialization.

Stopped at this seat's failed-build limit. Untried: whether the declared base
constructor needs a proven nothrow specification to reproduce native lifetime
states. Establish that from the complete native 25100 provider before another
trial; do not merely suppress EH. Scratch gate logs are
build/seat-object476-{before-byte,trial1-byte,trial2-byte,trial3-byte}.txt and
the same-index baseline is build/seat-object476-before-link.txt.

No donor code imported. Existing provenance separates target layout/lifetime
evidence from the ZH PlayerTemplate semantic lead. Claim released.
