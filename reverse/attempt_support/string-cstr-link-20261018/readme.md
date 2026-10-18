# C-string helper linking trial, 2026-10-18

Baseline e3c94fc435; published retail-truth-2 index c2c5ac8c27. No source,
header, pin or verifier changes retained. No authored or linked byte gain.
All link results here are legacy previews; no closed-strict gain measured.

## Rva006889F0Load.cpp

The existing body is 171 bytes and its EH handler is 10 bytes; the link preview
accounts for 180 bytes in this unit.
Current-object preview before and after the reverted trial reports 0/180 linked:
StringBase<char>::set(const char *) and AsciiString::operator=(const char *)
emit non-retail COMDATs. find_declared_unmatched passes.

The unit requires the visible nullable-strlen setter for evaluation order.
Trial one added dllimport to its forceinline setter and replaced name=path
with name.set(path). The ordinary set declaration leaves an external call,
removing the inline strlen and shortening the parent; byte gate refused it.
Trial two enabled the existing BFME_ASCII_KEEP_CHAR_SET_BODY header mode.
The length returns to 171, but receiver computation moves after strlen and
ESI/EDI/ECX/EDX allocation differs. Byte gate still refuses it. Further trials
need evidence for preserving original assignment IPA while binding both helpers.
Complete original source restored; normal byte gate passes 2/2, string/float/
import checks pass. Both file and parent RVA claims released.

## Current queue reassessment

- link_rank --top 30, --near 2 and class_views --blockers still prioritize
  previously documented missing bodies and wider ABI/provider reconciliation.
  Reviewed current evidence before excluding deferred trials; do not reopen
  SimpleScene, Gate module-data or ClosestPoint operator work without addressing
  their recorded blockers (pin fold admission, full vtable, and x87/SSE shape).
- Current link_check previews covered 730 non-generated units with at most two
  census losing/selected/duplicate blockers: 92 currently link, 26,846 bytes.
  Those are already-landed repairs, not session gains. Pairing current vector
  destructor-family providers also clears both damage-scalar units (850 bytes).
- name_globals --dry-run: zero rewrites kept. repair_queue link agrees with the
  missing-body/provider blockers. The bounded rehome dry-run reproduced the
  already-deferred exact 29-byte entry constructor: split links 29/29, while
  its 2,441-byte home retains five unrelated destroy/range findings. Moving it
  would lose working coverage. Stopped the broader scan; no rows moved.
- BFME1 linking donor commits reviewed at official 8619c4c56 (local verified
  pointer 64d369b901 remains clean). Declaration-only destructors and canonical
  helpers are useful leads, but no unblocked current transfer was established.
  Pointer freshness remains blocked by the documented PrimaryBase DIR32
  inconsistency in ../bfme1-freshness-20261018/readme.md; no success stamp written.
- No matching data-back measurement artifact; no ranking manufactured. No census
  build/measure/history, link cycle, nightly or boot runner started.

The existing link-blockers-seat-20261018 handoff remains applicable. Next useful
work requires native cleanup providers, full class/lifetime reconciliation or
the separately recorded verifier fixes; do not repeat imported-inline trials.
