# Mesh load context lifetime selection repair

Base checkout: 12beb51735b4ddf7bee5083516327b937087f0aa. Local census index:
147cfae2cb, 2026-10-14 07:27. Its hash and exact before/after findings are in
object-proof.json. The committed queue at 67e1365aa9 is discovery evidence
only. Census, index and status are unchanged.

meshmdlio.cpp emitted the old donor lifetime methods: constructor 373 bytes,
destructor 598 bytes. The census judged both non-retail and selected them ahead
of MeshLoadContextCtor.cpp's verified 405-byte constructor at 0x0018B5F0 and
599-byte destructor at 0x0018B180. Both units had duplicate-definition findings;
MeshModelLoadW3D.cpp's only findings were these two selected lifetime methods.

Remove the donor definitions and retain their existing declarations. They were
already out-of-line calls in the emitted donor loader; no matched call, layout,
ABI, identity or algorithm is changed. The exact BFME 2 lifetime methods remain
in their existing provider. This does not reconcile the remaining private class
views or claim that the unrowed donor loader is target code.

Removing the constructor also stops emission of two existing matched helpers
in meshmdlio.cpp. Rehome their rows with add_match.py --replace-existing to the
already-emitted identical bodies in MeshLoadContextCtor.cpp:

- ShaderClass DynamicVector constructor, 0x0016FEA0, 46 bytes.
- ShaderClass DynamicVector scalar deleting destructor, 0x0016FFB0, 30 bytes.

Their raw bytes and relocation digests are identical in the two baseline
objects, and both rows pass their normal target byte verification after moving.
No new row, pin, alias, marker, global, shared header or baseline is introduced.

Target identity comes from the existing verified lifetime/helper rows and the
matched Load_W3D calls, not from donor similarity. Reference review used clean,
verified BFME 1 gitlink 23b143233b5a8664a3bdf8572df6d905c310a5a1. Donor repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d removes non-retail local constructors
in favor of existing providers; that cause applies here. Reviewed fea964f8
allocation repairs are already represented in BFME 2; 92a8d854 data-owner
repair is not needed for this change. No donor code was imported. Official
master fetched as a7c38d3b2597121f178ab5190b3062478823257d; the reference file
claim belongs to another worker. Preserve the verified gitlink pending that
worker's comparative verification. No successful freshness stamp was written.

Acceptance:

- Bounded link_check.py --prepare-current before: 54/54 rows across the two
  providers, strict reusable receipts. After: 55/55 rows across both providers
  and the unchanged loader, with one literal verified and no baseline/skipped
  string, float or import checks. Each rehomed row also passed add_match's gate.
- meshmdlio.cpp removes 99 COMDATs and adds none. All 169 retained raw bodies,
  sizes and byte/relocation digests are identical. All 128 provider COMDATs are
  identical. COFF indices/sections and eleven local branch label names renumber;
  referent storage, offsets, values and contents are unchanged. Scratch proof
  script, original objects and strict receipt backups are under
  build/meshcontext-link-20261014.
- Same-index, three-source legacy preview using the historical strict baseline
  provider objects and unchanged current loader: meshmdlio findings 38 -> 30;
  lifetime provider 15 -> 10; loader 2 -> 0. MeshModelLoadW3D.cpp now LINKS:
  875 existing bytes. Local CLI report is link-after.txt; object-proof.json
  contains the complete same-cohort before and after comparison. Historical
  objects are preserved witnesses, not presented as current source objects.
- check_csv, frozen-definition check, class gate, new-variants admission,
  whitespace check and data checks pass. Converged data: eight addresses,
  no second names or unjudged rows. Shadow data: zero findings.
- TU ownership shadow reports two A2 findings: the helper rows are classified
  with matinfo.cpp as their approved C-tier home. Their old meshmdlio owner
  already differed from that home; this repair chooses the existing exact
  lifetime provider. No ownership baseline or TU map was changed. Canonical
  ownership reconciliation remains separate work.
- EH verification: 3/3 EXACT, zero baseline or missing objects (eh-after.txt);
  affected-source placement resweep:
  zero new bodies and zero pins in the placement resweep.

New authored C++ bytes: zero. Self-strict currency is proven for the current
three-source cohort. This is a local legacy selection improvement; closed-strict
dependency closure, actual link placement and a fresh census were not measured.
No census build/measure/history, full link cycle, nightly, boot or publisher
verification runner was started.

Remaining provider blockers are independent ShaderClass/refcount copies,
RefCountPtr teardown and SimpleVec Resize; meshmdlio also retains Reset and
stricmp imports and other mesh helpers. Further class/layout repair is separate
work. Earlier in this session, narrow-string append declaration suppression hit
MSVC 7.1 C1001 twice at _string.h:573 / P2/main.c:148. Those source edits were
restored, the blocked verdict recorded with re_log.py and all three claims
released; the compiler-shape blocker must change before retrying that attempt.
