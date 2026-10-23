# Bind six assignment consumers to the rowed provider

At BFME2 e46d1b72b2, six units call native 0x0021C21B through a pinned
vector<int>::operator= name, whose kept definition is proven non-retail.
The matched 177-byte owner is vector<Rva0021C21BElement>::operator= in
StlSweepW5Rva0021C21B.cpp. Its four-byte non-POD-traited element identity
remains address-derived; this repair makes no claim about its application
payload. Existing caller rows prove the target, 12-byte vector storage,
receiver and reference argument ABI. Use that existing provider view at
assignment sites, keeping public signatures and storage unchanged. The
fill TU now explicitly specializes its one existing emitted instantiation.
No pins, aliases, provider definitions or compiler settings added.

Same-index paired legacy preview (b73720bed9, 2026-10-20 05:34):
PlayerScienceAssign 0->26; Rva0031804DAssign 0->81;
Rva003B1101Assign 0->215; Rva003F1AB9Setter 0->70;
stlport_copy_sciencevec 0->129; stlport_fill_sciencevec 0->29.
Total 0->550 bytes across six units. The 177-byte provider remains held
by independent allocator and _M_allocate_and_copy conflicts, unchanged.
This is a legacy prediction, neither self-strict nor closed-strict gain.

Byte gate: all eight caller rows exact; provider independently byte exact.
EH audit: no EH rows in these consumers. Declared-definition checks and
git diff --check pass. No new authored retail bytes. Previously observed
Hero map, audio and shell trials were restored and recorded separately.
