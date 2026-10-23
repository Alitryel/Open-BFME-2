# UnitRevivalTracker helper binding, 2026-10-23

BFME2 input 4502082e35; published retail-truth-4 index b711de3634
(2026-10-23 14:28). gpt-6.1-sol. Source settings unchanged: /O1 /EHsc /MD,
static STLport, no exceptions, moduledata/bfmealloc shims.
No source, ledger, identity, pin or linked-byte improvement retained.

Current xfer 37F39E..37F4C0 is 290 bytes and previews 0/290 linked:
its vector<UnitRevivalEntry>::erase copy differs from retail and needs
an unprovided UnitRevivalEntry assignment. Native REL32 at37F435 targets
2E2690; the real row owner is vector<Rva002E2690Element>::erase in
StlportVectorEraseRangeFamily.cpp. Native push_back at37F468 targets2E2D10,
whose standalone owner uses Rva002E2D10Record. These are target call/stride
facts; the opaque tags do not prove application payload identities.

Two failed byte builds:
1. Directly call both rowed vector owners through layout-compatible vector
   views, using only forward declarations and declaration specializations.
2. Retain the original UnitRevivalEntry push_back and change only clear to
   a direct call of the rowed range erase. erase-view.patch preserves this
   smaller diagnostic; it is not a matching candidate.

Both emit 290-byte parents and pass both EH-related byte rows, but swap
EBX/EDI roles throughout the parent. Retail starts its saved-register region
53 56 8B D9 57 8B 7D 08; trial starts53 8B 5D 08 8B 03 56 57 8B F9.
At erase, retail loads finish from[ESI+4]; trial loads[EDI+8], where EDI
holds the outer object and ESI its vector. Call offsets and targets remain
at their native locations. Restoring only push_back does not resolve this:
range-erase body visibility/access information is the remaining compiler
hypothesis, rather than push_back identity alone. Neither trial is exact,
so no repaired link gain is claimed and the source is restored.

The paired baseline includes both standalone providers: only push_back
links58B; the broad range-erase family itself retains many independent
unresolved copy/destruction providers. Binding the caller alone would not
prove closed-strict closure. Read those providers together before another
trial. All three original rows are reverified after restoration.

Reference review reuses the unchanged BFME1 linking survey at verified
96c88c73 and official masterf5140c1c; no donor body or layout was imported.
Its provider-binding repair principle motivated the trial, while all ABI,
call and stride observations above come from BFME2. Broader rank/class,
globals and rehome probes found inherited gains or existing prerequisites.
No census or maintainer-only verification runner was started.
