Script condition access link repair
===================================

ScriptEngine.cpp previously emitted an unused four-byte
`Script::getOrCondition` COMDAT reading +0x30. It conflicted with the
+0x24 copy in Scripts.cpp. The evaluator now directly reads its existing
`m_condition` field, so that surplus getter is no longer emitted.

Target evidence: retail evaluateConditions at 0x00209748 (201 bytes) reads
`mov edi,[eax+0x30]` (`8b7830`) at 0x002097AD. Its compiled body already
inlined this access and had no getter relocation. Neither standalone getter
has a proven retail address; this repair does not establish the provider's
+0x24 view as target truth. The field name comes from the existing source;
the target offset and behavior are independently established by retail.

Donor review: official BFME 1 master and the verified committed pointer are
23b143233b5a8664a3bdf8572df6d905c310a5a1. Donor repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d removes surplus BfmeStrVKI
constructor emitters. That general mechanism applies here; its alias/pin
method does not. No donor code, class layout or identity was imported.
Geometry rehome b955ec4852b51ec7190f1a4542a9f2864abda988 is inapplicable.

Baseline source revision: 4e2e97737575deca9dc8ef78a69db3a051cf6b43.
Census index: 147cfae2cb, 2026-10-14 07:27; SHA256
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
The saved before object and current after object were each substituted into
that same index together with the current Scripts.cpp object. Consumer
findings fell from one COMDAT conflict to zero: legacy linked preview
0 -> 1,328 existing authored bytes. Provider findings are exactly unchanged
(6 unresolved, 9 duplicate, 13 COMDAT, 12 selected-definition blockers).
No census, self-strict placement or closed-strict gain is claimed.

Verification:
- Bounded link_check --prepare-current: consumer before/after 17/17;
  provider 8/8; strict current compiler receipts for both after objects.
- ./build.sh consumer provider: 25/25 exact, string reference verified,
  no baseline additions or skipped references.
- eh_verify: both consumer EH rows EXACT, zero baselined/notexact/missing.
- Object comparison: all 46 retained COMDAT raw bytes, extents and relocation
  digests unchanged; all ordinary sections unchanged after normalizing local
  COFF indices/compiler labels. Strong/undefined/weak names and hatch counts
  unchanged. Exactly the unused 4-byte getter was removed.
- Frozen-file, class gate and converged-data checks passed (8 data addresses,
  no second names). No shared header, ledger pin or verifier change.

The provider's unrelated parser/xfer duplicates, conflicting class views and
missing dependencies remain. Broader class reconciliation and a maintainer's
full link measurement are separate work. New authored C++ bytes: zero.

Logs and object-proof.json retain the before/after evidence. A read-only
place_bodies rescan is recorded separately; placements alone are not identity
or recovery evidence.
