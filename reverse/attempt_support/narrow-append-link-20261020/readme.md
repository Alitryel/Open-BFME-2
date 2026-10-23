Narrow char-range append linking handoff, 2026-10-20

Index e7a7769fe5: canonical private PBD append at1B3E0 is254B retail.
Earlier narrow_string and float_format objects emit wrong selected copies.
Prior20261014 declaration-only and extern member-template attempts hit
MSVC7.1 C1001 during whole-class instantiation; that blocker remains.

New isolated owner trials: import-forceinline proxy allocate plus direct
private-member instantiation preserve1/1 and suppress proxy/wrapper copies.
Explicit specialization (patch attached) also preserves all254B and3 imports,
but becomes a NODUPLICATES definition: current preview still0/254B, now with
duplicate plus wrong-selected append. It cannot override the earlier copy.
No source change retained; no gain, pin, alias or verifier change.

A possible next hypothesis is making earlier string units emit this proven
body instead of declaration-only specialization, or reducing whole-class
instantiation. Not tested:179B0 is held by another worker, so the first
provider cannot be edited in this seat. Do not retry unchanged declaration
trials. Uninitialized-copy majority diagnostic is unreferenced, not debt
to suppress. BFME1 donor review4483e88da1c2; target254B gate establishes
code shape, not a new identity. t=12min model=gpt-6.1-sol.
