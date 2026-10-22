# Matrix3 consumer link repair

At BFME 2 3c0234e976, published census ae3b3e68e2 (2026-10-22
11:05 UTC), both current consumers failed their link preview:

- colmathsphere.cpp: 0/251 nonpadding bytes linked; unresolved
  `Matrix3D::Set(const Matrix3x3&, const Vector3&)`.
- coltest.cpp: 0/25 bytes linked; unresolved
  `Matrix3x3::operator=(const Matrix3D&)`.

BFME 2's existing providers name the rotation class Matrix3. The same
Matrix3x3-to-Matrix3 donor mapping is established in camera.cpp; this changes
consumer declarations, without renaming or adding a ledger owner. The current
BFME 1 donor inputs are 37c3022de1ab944c7ffe536440d637dc8199091c.

The previous sphere trial (re_attempts entry 81579) already proved that mapping
but exposed a 39-byte donor rotation constructor competing with retail's
26-byte constructor. The sphere/box test now default-constructs its empty
matrix rows then calls the same Set directly. This retains the donor's
initialization and transform semantics while removing that emitted constructor.
No header, pin, alias or optimization setting was added.

Acceptance:

- ./build.sh on each consumer: sphere 2/2 and coltest 1/1 rows exact; string,
  float and import checks green.
- link_check.py --prepare-current on both: 3/3 byte rows, strict reusable
  receipts prepared for both sources.
- Same-index paired current link_check.py: both LINKS, 0 -> 276 nonpadding
  matched bytes. This is a legacy index preview with self-strict source
  receipts, not a closed-strict gain. Unreferenced math-copy diagnostics remain.
- link_check.py --new-variants --staged-peers on the pair: exit 0.
- find_declared_unmatched.py on the pair: accepted (coltest's existing
  whitelist reports ten unclaimed definitions).
- Closed-strict --current-ledger --refresh refused: 3,469 current-ledger
  objects are missing, beginning with ascii_string and particle-info units.
  No census rebuild or full link cycle was run.

Scratch before/after and receipt logs are under ignored
build/link-seat-20261022e/{triage-current,coltest-before,math-after,math-strict,
math-variants,colmath-closed}.txt.
