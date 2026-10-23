# Smoke-glow scalar data ownership repair

Base commit `c3c14cc35e2a09838b32a4f2456757befb432db0`. The restored
census index measures `cb660e4d97`, dated 2026-10-13 04:02. The committed
link-status snapshot at `67e1365aa9` serves discovery only. No per-row
data-back artifact, census rebuild or status rewrite is used.

ScreenFilterRva007DCA80PostRender.cpp now defines its three previously
undefined scalar globals. The existing canonical provisional symbol names
and the unchanged camera-transform consumer are retained. Add three data
rows totaling nine bytes. There is no new function row, pin, alias, class,
header, compiler setting or hatch occurrence. Original global identifiers
remain unknown.

Target evidence establishes each scalar independently:

- VA `0x00DB457C` holds `0000803f` (1.0f). Native DIVSS at VA `0x004F9FED`
  divides the glow scale by this four-byte scalar. The camera builder's
  MOVSS at VA `0x0048A6E8` reads the same float into its established context.
- VA `0x00DEC0DC` holds four loader-zero bytes. Native postRender MOVSS
  loads/stores at VAs `0x004FA00D`, `0x004FA050`, `0x004FA05D` and FLD
  at `0x004FA065` establish the four-byte pulse phase. The existing exact
  body advances it by 0.6 and wraps at 13.
- VA `0x00DB5B08` holds byte 1. Native CMP byte at `0x004FA4A0` selects
  the existing additive/modulating blend arms. The bool definition claims
  only this one-byte operand, without claiming its neighboring padding.

The data gate proves compiler sizeof 4/4/1, allocation extents and retail
initializers. Before/after proofs record all seven native DIR32 operands
and the current objects' SHA256 values; every binding and source hatch
count remains identical. The new definitions are strong external owners.

Donor review used verified BFME 1 pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85` and dependency repair
`0835ab92bef30e3303e729a0ce09cf591368d0cd` (Apt string-pool externs
bound to an existing owner). Its exact respelling repair is inapplicable:
these three BFME 2 scalars had no provider. The ownership principle applies;
all addresses, initializers and access widths here come from BFME 2 retail.
No donor code, data address or type layout is imported. Official master was
fetched at `d003077f0b7ce97622adb7a53f1fe76653433c5c`; the overdue
comparative full verification/update remains outstanding. The verified
submodule checkout/pointer is retained and no success stamp is written.

Acceptance logs accompany this record:

- Before and after, bounded `link_check.py --prepare-current` on the owner
  and camera consumer passes both complete executable rows with strict
  reusable self receipts. After also verifies all three new data rows.
- Normal `./build.sh` on the owner passes its complete 1,712-byte body,
  all three data rows, twelve float literals and one named import, with
  no baselined or skipped references. The two-source preparation also
  passes the unchanged 1,148-byte camera body and all sixteen float literals.
- `data_rows.py --verify` independently passes the three scalar rows.
  Data shadow audit reports zero findings. Enforced converged-data check
  reports zero second names and zero unjudged rows across both consumers.
- Local legacy link preview changes the owner from three unresolved
  bindings to `LINKS`: **0 -> 1,711 unique existing authored C++ bytes**.
  The camera consumer loses its shared-float unresolved binding but remains
  blocked. The two-unit cohort changes from 0/2 to 1/2 locally linkable.
  This is four fewer unresolved consumer bindings, nine newly owned data
  bytes and zero newly authored executable C++ bytes.
- CSV, declared-definition, pin-consistency, case-collision and whitespace
  checks pass. Protected baselines and the converged list are unchanged.

These are self-strict compiler receipts and a local legacy link preview.
No closed-strict gain, actual link.exe/data-back placement or refreshed
census measurement is claimed. Full link cycles, nightlies and boot checks
remain maintainer work.

Remaining camera blockers are float `g_Va00DE2020`, state helper
`Rva00102F83Owner::rva00102F83`, and differing Vector4 assignment,
Matrix3D assignment and vector-construction COMDAT bodies. Their existing
deferrals remain valid; this repair does not reopen those reconstructions.
