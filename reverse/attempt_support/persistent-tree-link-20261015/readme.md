# Persistent-storage tree comparison repair

Base BFME2 revision: `d90fb9036fc3e84e737d9744a86eb72f76cc7d82`.
PersistentStorageThread.cpp's unused external STLport tree-base inequality
differs from the selected library copy. A TU-local typed node comparison,
following W3DShroudInterpolate and the existing tree-consumer repairs, keeps
the same inlined pointer test without that external definition. No header,
compiler flags, layout, ABI, pin, data binding or ledger row changes.

## Controlled result

The unchanged runner index is `19a2565407` (09:33), based on census
`5986a99448` (04:52). The status queue measures `28269d8e8d` (09:31).
context.json records its SHA-256 and the source revision. No data-back
ranking artifact or full link cycle is used; index/status are not rewritten.

Original and changed objects both have strict reusable receipts and pass
211/211 byte rows. link-proof.json independently refreshes only the original
or changed consumer in copies of the same index: findings **15 -> 14**,
with exactly the tree-base comparison conflict removed and every other
finding unchanged. This affects 21,777 existing unique authored bytes;
legacy local LINKED stays **0 -> 0**. No new authored bytes, self-strict
placement or closed-strict gain is claimed.

object-proof.json verifies all 356 retained COMDAT bodies, extents and
relocation digests are identical. The only nondebug section changes replace
one unreferenced 18-byte external comparison with five unreferenced 12-byte
static typed comparisons. All other normalized sections, relocations,
directives and external bindings are identical. Local label destinations and
.sxdata indices are compared by their actual targets. The removed helper has
no nondebug caller relocation; provider definitions remain untouched.

## Acceptance and remaining debt

- Before/after `link_check.py --prepare-current`, and `./build.sh`:
  211/211 exact; 52 strings plus 13 empty references, 23 floats, 14 imports pass.
- `eh_verify.py`: 46/46 EXACT, no baselined or missing-object rows.
- Prescribed local `link_check.py`: expected exit 1, remaining 14 findings;
  paired original/current preview proves the improvement above.
- `link_check.py --new-variants`, `class_gate.py`,
  `find_declared_unmatched.py`, and both enforced data checks pass.
- Paired data facts/findings identical (zero findings); identity shadow has
  the same nine pre-existing findings, zero new findings.
- `place_bodies.py`: zero bodies/pins. `check_csv.py` passes.

Remaining blockers are two unresolved globals (E02548/E0254C), integer-tree
iterator/pair/allocator COMDATs, string constructor/selection conflicts and
the selected Xfer destructor. No unchanged blocked repair was retried. Proof
scripts reproduce from the original scratch object saved in
build/persistent-tree-link-20261015 and the current strictly compiled object.

The link queue also served an already repaired CrowdResponse parser:
strict 1/1 and local LINKS 163 bytes, no edit or new gain. Its claim was
released. EVA's consumer was foreign claimed and left unchanged.

## Donor review and freshness

Reuse the dedicated donor scan documented in link-inline-emitters-20261014
and tree-consumer-cohort-link-20261015. Reviewed BFME1 `de59a7e9f891b3ed2d4221d151ca881f4b75a583`
for consistent incidental helper ownership. Its Apt body/layout do not apply;
the typed iterator implementation and direct object proof establish this
BFME2 repair. Also inspected recent donor repair `4d506dbb57690a913403c09a0ab83b2a22e80f83`:
its GameSpy AsciiComparator binding concerns different string-tree helpers
and is inapplicable to this node-pointer comparison. No donor code imported.

The clean verified donor remains `a7c38d3b2597121f178ab5190b3062478823257d`.
Official master was fetched; context.json records the observed revision.
The reference scope remains foreign claimed and its previously recorded
old/new dependency-verification blocker unresolved. No pointer advance,
freshness-success stamp, whole census, link cycle, nightly or boot run.
