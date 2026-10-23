# Record-copy unit link isolation, 2026-10-23

The published census at b711de3634 (2026-10-23 14:28) assigns 201 unique
matched bytes to `Code/GameEngine/Source/Common/Rva0041573FCopy.cpp`.
Before this repair, `python3 tools/link_check.py` reports zero linked bytes:
the appended Rva0022A809Subsystem constructor introduces an unresolved virtual
destructor and a non-retail hashtable constructor, including a wrong selected
provider. These dependencies do not belong to the independent record-copy rows.

Move that constructor at 0x00415704 (59 bytes) and its compiler-emitted EH row
at 0x00786192 (10 bytes) to `Rva00415704Ctor.cpp`. Preserve its original compiler
flags, STL include order, declaration-only specializations and class definition.
The remaining copy and destruction bodies are unchanged. This is source
isolation, with no new identity, pin, recovered body or authored-C++ byte gain.

Verification:

- `./build.sh` on both units: all seven rows exact.
- `python3 tools/link_check.py --prepare-current` on both: seven self-strict
  receipts; no closed-strict gain claimed.
- `python3 tools/eh_verify.py` on both: both EH rows exact.
- `python3 tools/find_declared_unmatched.py` on both and `check_csv.py`: pass.
- `python3 tools/link_check.py Rva0041573FCopy.cpp` (full Code path): legacy
  linked bytes increase from 0 to 142, with all remaining rows link clean.
- `python3 tools/link_check.py --new-variants --staged`: no new variants.

The commit's shadow identity check reports a divergent `_M_next_size` for
`hashtable<pair<const int, Rva00415643Element> >`: the census-ordered kept
copy is in StlSweepW4Rva00415643.obj (62 bytes), versus 48 bytes in the new
constructor object. `dup_defs.analyse` gives the kept copy verdict `none`,
with no owner or retail address. The link variant check above accepts it;
do not suppress this unaddressed helper merely to silence the shadow report.

The new constructor unit has no position in this published census and is not
previewable by link_check. Its link result is unknown; no gain is attributed to
it. Its original unresolved `??1Rva0022A809Subsystem@@UAE@XZ` and non-retail
`hashtable<pair<const int, Rva00415643Element> >` constructor still require
class/container reconciliation. Preserve this rowed implementation for that
work rather than suppressing its vtable or changing its layout. A future census
must measure the new unit. This session did not run a census or full link cycle.
