# Exact new-profile band deblocker

Recovered `_DeblockNonFilteredBandNewFilter_C`, retail RVA `0x001BF090`,
2107 bytes through `0x001BF8CB`, in
`Code/Libraries/Source/VP6/DeblockNonFilteredBandNewFilterC.cpp`.

Identity, ABI, field offsets, filtering behavior and clamp-table use come from
the approved clean-room spec `reverse/vp6_cleanroom/specs/001bf090.md` and
retail disassembly. The bounding-table and initialization specs `001bd590.md`
and `001b6520.md` informed the independent execution checks. No external VP6
decoder source was read. The small instance view records only the specified
offsets, not an inferred complete class layout.

The existing bank was close but retained different register allocation. Keeping
the tenth original sample alive through the horizontal smoothing and removing
an unused initial assignment to the rolling sum produced the complete retail
body with `/O2 /G6 /DNDEBUG /MD`. Every sum use is dominated by its actual
filter initialization. The result contains ordinary C++, with no assembly,
volatile scheduling devices, new pins, aliases or alternate globals.

Normal `add_match.py` and `build.sh` verification pass: one complete exact
body, four resolved clamp-table relocations, no masking, and all applicable
literal, float and import checks. Both resolved-body SHA256 hashes are
`460c3ea4afa30ec06a8fb40eb2cc567b827ba177875384fc35bdbcf15e08045f`.
The old bank is removed by `add_match.py`.

`oracle-results.json` records 4320 paired executions against retail, with no
pixel, accumulator or ABI differences. Cases cover three strides, zero through
three fragments, two starting indices, six pixel patterns, five quantizer
steps, three valid bounding tents, separate buffers and identical source and
destination pointers. Complete image and variance/context buffers, arguments,
callee-saved registers and the cdecl stack pointer are compared. Both filtering
branches execute in both passes; 97728 clamp reads agree.

`find_declared_unmatched.py` passes. `data_check.py --converged` finds no second
names or unjudged addresses. `place_bodies.py` reaches a fixpoint with no extra
placements. `link_check.py --new-variants` passes. The ordinary link preview
has no census entry for this new unit. Its only external datum uses the existing
canonical `g_bfmeClampTable` provider in `FilteringC.cpp`; that provider's four
matched bodies also pass their normal byte gate. An isolated native link of
both complete objects exposes that existing provider's separate unresolved
`g_bfmeFilterLimit` datum. This recovery does not add a substitute or claim a
complete-game linking result.

Reference pointer during verification:
`a18d9ed50607e9175de4d6568798d7d73119de09`.
Base before this source recovery: `be9092f65b`.
