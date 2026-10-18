GUI static storage ownership, 2026-10-18

At BFME2 97e92bae01, unchanged census c2c5ac8c27 (retail-truth-2).
Paired current explicit objects: GUI startup/cleanup unit 0 -> 388, consumer
Rva005E91A9Dtor 0 -> 246, five-getter family 0 -> 140 nonpadding bytes.
Combined legacy link preview gains 774 B; authored C++ growth is zero.
The additional explicit ButtonNameInits provider remains blocked before/after
and contributes no claimed gain. No closed-strict or actual link.exe claim.

Target facts: VA E0675C, E068EC, E06900 and E06918 are each 20 zero bytes.
Their rowed GUI initializers pass these exact addresses to constructor 5E16DA,
using four distinct complete label strings, and register exact rowed cleanup
callbacks reaching destructor 5E16FD. Constructor/destructor evidence supports
20-byte storage with a vptr and four opaque words; application class unknown.
The existing typed extern names, rather than competing getter-view names, own
the storage. Inert storage uses those exact decorated identifiers under C
linkage, avoiding an extra compiler-generated dynamic initializer. The rowed
explicit startup functions begin object lifetime, as in retail. All twelve
GUI rows, four exception records and complete literals remain byte-exact.

The five getters retain their established GetResult ABI view only as a cast
at each call; target immediates independently prove each address. E06620 uses
its existing data-row owner g_Va00E06620; it is not redefined or given a second
owner. Its existing 4-byte row is unchanged and is not claimed as a complete
20-byte object recovery. The other four use the GUI owners above.

Acceptance: explicit self-strict reusable receipts 24/24 code rows across
three units, data 4/4 (80 native zero bytes), EH EXACT 4/4, frozen-source and
CSV checks pass, converged-data check reports zero second names. Related
GUI holder units already claimed by another seat were left for that owner.
