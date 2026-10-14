Delayed experience queue global ownership repair
================================================

At source commit a4afd6c162, both DelayedExperienceLevelGrantXfer.cpp and
DelayedExperienceLevelGrantUpdate.cpp define TheExperienceLevelSystem.
The data ledger assigns that exact ExperienceLevelSystem pointer name at
RVA 0x009FECC4 to the transfer unit; its source records GameEngine::init's
registration at VA 0x00DFECC4. Keep that owner and declare the update unit's
copy extern. The update body does not reference this global, so the unused
declaration emits neither a definition nor an undefined reference.

The named xfer (0x00420F3F, 325 bytes) and update (0x00420EB3, 91 bytes)
retain their original identity, layout, source provenance and compiler flags.
This is an ownership repair, with zero new authored C++ bytes.

Measurement and acceptance
--------------------------

Discovery status is committed at de7bb30890 (2026-10-14 15:43). The actual
paired local preview uses runner index 147cfae2cb (2026-10-14 07:27), SHA256
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Both current units were substituted together into that same index before
and after; no index, status, history or baseline was rewritten. No per-row
data-back ranking was used.

- Before: both units refuse with only the duplicate global; 0/2 LINKS.
- After: both units LINKS; 2/2, 0 -> 416 existing retail bytes in the legacy
  local preview (325 transfer + 91 update).
- Strict prepare-current receipts and the whole-unit build.sh gate pass
  before/after: 2/2 rows, complete literal/import checks, no skips.
- All 20 transfer and 10 update COMDATs retain their complete raw bytes,
  sizes and relocations by offset/type/referent. The owner object is identical.
  The update object removes only the global external definition and its
  four-byte uninitialized .bss section; all other external bindings and the
  .drectve section remain identical. COFF symbol indices shift accordingly.
- New-COMDAT admission, frozen-file, class, CSV, whitespace and data checks
  pass. Data shadow has zero findings; converged-data enforcement checks
  eight addresses with zero second names. Affected-unit placement was swept.

Strict receipt currency and byte identity are verified. The 416-byte gain
is a legacy link preview, not a self-strict placement, closed-strict closure,
fresh census or data-back gain. Those broader measurements remain outstanding;
no maintainer-only runner was started.

Donor review and handoff
------------------------

The current verified BFME 1 gitlink/checkout is
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed upstream repair
0835ab92bef30e3303e729a0ce09cf591368d0cd (declare the exact owned global type,
cast at use sites) supports keeping one real data owner. No donor source,
layout, alias or pin is imported; the target ledger and paired byte/object
evidence establish this repair. The unchanged earlier shared-library review
is in concat-link-20261012/README.md.

Official upstream was fetched at fc5aa8096. The pre-existing overdue
freshness update remains blocked on its comparative full verification with
thousands of stale donor-dependent objects; prior interrupted compile
evidence is in build/bfme1-freshness-blocker.txt and the unicode-comparator
repair record. Verified inputs and the success stamp are preserved, with no
pointer advancement claimed. setDisabledUntil still lacks a matched provider;
the ranked getDrawModules repair is already upstream; the remaining camera
Matrix4 constructor emitter needs a separate supported repair. None of those
unchanged blocked conversions was retried.

Measurement, paired logs and compact object proof are stored beside this file.
Before/after sources, objects and the exploratory comparison script are kept
in build/experience-level-global-link-20261014/.
