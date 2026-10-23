# Horde movement geometry accessor link repair

Checkout base: 7781f0b03c. Local runner census index: 147cfae2cb,
2026-10-14 07:27; SHA256 is recorded in object-proof.json. The committed
link_status.csv queue measures 67e1365aa9 and is discovery evidence only.
No census, status, history or per-row data-back artifact was changed.

HordeContainMovementPosition.cpp defines a local GeometryInfo view whose
radius is at +0x24. Its inline getMajorRadius helper emitted d94124c3,
conflicting with the index's first same-name copy: PartitionManager.cpp's
d94110c3 (+0x10), digest 57aa571c12a2, with no relocations. The generic
accessor has no retail address. These copies cannot represent one shared
out-of-line accessor. The movement body independently verifies its +0x24
loads against native 0x0046B05B..0x0046B850 (2037 bytes, RET12).

Rename this implementation helper to movementMajorRadius and update its six
inline uses. This assigns no new retail identity, layout, pin or global.
The existing local view, external getMaxHeightAbovePosition declaration,
method body semantics, compiler flags and ledger rows remain unchanged.
The helper's four-byte COMDAT still emits under its distinct implementation
name; its entire bytes and relocation facts are unchanged. The earlier log
note incorrectly described the index's first offset as +0x08; the following
correction and first-view.txt establish +0x10.

Acceptance:

- Bounded link_check.py --prepare-current before and after establishes strict
  reusable compiler receipts and ordinary byte verification, 1/1 exact.
- Final ./build.sh: 1/1 exact, 18 compiler float references, zero skipped or
  baselined string/import references.
- All 26 retained COMDATs have identical raw bytes, extents, digests and
  relocation facts. The renamed helper has identical body and relocation
  facts; external undefined names, strong definitions, weak bindings and
  ordinary nondebug sections stay equal. Full snapshots, source/object
  backups and the proof script remain under build/horde-radius-link-20261014.
- Same-index ordinary legacy preview changes the consumer from one losing
  COMDAT finding to clean: LINKED 0 -> 2025 existing bytes. The original
  copy was not selected; its removal changes no existing selected provider.
  The renamed helper has no other index consumers or providers. The first
  generic copy remains untouched and agrees with its census digest.
- Frozen definitions, class gate, new-variants admission, converged-data
  check (eight addresses, no second names), shadow data, CSV and whitespace
  checks pass. EH verifier has no applicable rows or missing objects.
- Affected-unit placement resweep: zero bodies and zero pins. The census
  has no other near-clean losing getMajorRadius consumer to which this
  particular local-view fix applies.

New authored C++ bytes: zero. The LINKED gain is a local legacy preview;
self-strict object currency is proven. Closed-strict dependency closure,
actual link.exe placement and a fresh census gain remain unmeasured. No full
link cycle, census build/measure/history, nightly or boot runner was started.

Reference review: clean verified BFME 1 gitlink
23b143233b5a8664a3bdf8572df6d905c310a5a1. Reviewed BFME 1 linking repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d and geometry reconciliation
b955ec4852b51ec7190f1a4542a9f2864abda988: conflicting private helper emission
is applicable as a cause; their aliases, pins and donor-specific layouts
are inapplicable here. This repair imports no donor code. Target byte
identity/layout evidence remains the existing movement body's verification.

BFME 1 freshness: official master fetched to
a7c38d3b2 (upstream ahead of the verified gitlink). Another worker holds
file:reference/open-bfme-1, so its clean checkout and pointer were preserved.
Comparative old/new full byte verification remains with that claim owner;
no freshness success stamp was written.

Two unsuccessful local alternatives were discarded: __forceinline preserves
the unwanted emission; direct field access removes it but changes native SSE
scheduling. The final helper rename preserves the entire matched body.
