# ShipSlowDeathBehavior Matrix3D link repair

Base checkout: d9a91fce3147d49b286d8fca2cde0eb370ed030d. Local census index:
cb660e4d97, 2026-10-13 04:02; SHA256 recorded in base.json. Committed
link_status.csv measures 67e1365aa9 and is a newer discovery lead, not this
comparison's baseline. Neither measurement nor index was modified.

The consumer now includes the existing BFME matrix3d_copy_link.h instead of
matrix3d.h. Compiler flags, declarations, layouts, method bodies, ledger and
pins are unchanged. This applies the supported emitter suppression used by
ToppleUpdate.cpp and StructureToppleUpdateCrushing.cpp; no shared header edit.
The native FloatUpdate.cpp Matrix3D copy owner at RVA 0x0006645C, size 98,
was checked alongside the consumer and remained untouched.

Reference evidence: BFME 1 verified gitlink cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
supplies the existing Row-copy semantics. Reviewed donor repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d suppresses redundant constructor
COMDAT emission; only that general technique applies here. Its identities and
pins are not imported. Target identity, MI receiver offsets and row extents
remain the established BFME 2 evidence of the two matched consumer rows.

Acceptance:

- Ordinary ./build.sh consumer gate: 2/2 exact rows; strings, floats and imports
  verified without baselines or skipped references.
- Before and after bounded link_check.py --prepare-current over this consumer
  and FloatUpdate.cpp: 4/4 exact rows and strict reusable object receipts.
- Consumer loses only Matrix3D copy constructor, Vector4 default constructor,
  and Vector4 assignment COMDATs. All 13 retained COMDATs preserve complete raw
  bytes, sizes, and relocation offsets, kinds and referent names/content.
  No COMDATs are added; external undefined names and nondebug ordinary sections
  stay equal. FloatUpdate's entire object is unchanged, including all 631
  COMDATs. .sxdata indices are normalized to handler names for comparison.
- Frozen definitions, class gate, converged-data gate (8 addresses, no second
  names or unjudged rows), shadow data check, CSV and diff checks passed.
- Consumer EH check: no EH rows, no missing objects. Affected-unit placement
  resweep: 0 bodies, 0 pins.

Same-index legacy link preview: consumer selected-definition findings decrease
from two to one. Matrix3D copy selection no longer affects this consumer;
beginSlowDeath@SlowDeathBehavior still selects a nonretail provider. The consumer
has 676 counted existing bytes (680 ledger bytes). FloatUpdate retains its eight
independent findings. Both previews exit 1 because these known blockers remain.
Linked bytes stay 0 -> 0; new authored C++ bytes are zero. This is one verified
link-blocker removal, not a clean-link result. Self-strict input currency is
proven; no closed-strict, full-link or fresh census improvement is claimed.

Commands and output are retained alongside this file. Additional acceptance
commands: find_declared_unmatched.py, class_gate.py, data_check.py --converged,
data_check.py, check_csv.py, eh_verify.py --json, place_bodies.py, git diff --check.
No full census, link cycle, nightly or boot runner was started.

BFME 1 freshness: official upstream was fetched to
23b143233b5a8664a3bdf8572df6d905c310a5a1. The existing reference-file claim belongs
to another worker; the clean verified gitlink and checkout were preserved.
Comparative full old/new byte verification remains outstanding after prior
compiler-lock/stale-cache blockers. No freshness success stamp was written.
