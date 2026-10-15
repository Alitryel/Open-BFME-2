# Timer-list helper ownership repair

Source base: 4b1a58a31d, after rebasing the previous seat's pending EVA repair.
Concurrent upstream commit a2839ea429 landed the identical ownership repair
during this seat. Rebase preserves upstream's source and row unchanged; this
commit contributes independent verification evidence and its attempt record.
The 588-byte historical prediction below is corroboration, with zero additional
repair gain relative to current origin/master. Rebase conflicts were comments
only, and the upstream implementation was byte-verified again after resolution.
Paired measurement uses runner index 825b86983f, dated 2026-10-15 12:37
(original census 5986a99448). The index hash, source/object hashes, strict
receipt hashes and complete before/after findings are in proof.json.
The committed link_status.csv is queue evidence, not this measurement.

The 28-byte address-derived Rva00357DF8::rva00357DF8 helper had a standalone
strong definition in ScriptEngineRva00357DF8.cpp and an identical existing
inline/noinline definition in Rva00358076AudioComplete.cpp. Both units failed
on that sole duplicate. The consumer must retain visibility of the real helper
for MSVC's register-preservation analysis in its two 280-byte callers.
Rehome the existing row with add_match --replace-existing to that consumer;
delete the redundant standalone file. No algorithm, layout, compiler flags,
shared header, pin, alias or verification rule changes.

Target evidence remains the existing 0x00357DF8..0x00357E14 retail body,
which inserts the record at list begin via the rowed 0x0036E30E list insert.
Both old copies have the same 28-byte body-and-relocation digest a4e23668e4d9
and retail-truth verdict. The class/method names remain address-derived.
The shared BfmeSpecialPowerTimer8 header retains the distinction between donor
semantic names and independently supported target layout; this repair imports
no donor code and establishes no new identity or layout claim.

Acceptance:

- Bounded strict preparation before: 3/3 rows across both claimed files.
  add_match and strict preparation after: 3/3 in the surviving owner, current
  reusable dependency receipt. All literal/import reference checks pass.
- The asserting scratch proof at build/timer-list-home-link-20261015/proof.py
  normalizes every retained non-debug COFF section, section-local referents,
  relocations, data, directives and EH symbol-index references. They are all
  unchanged. All COMDAT facts, strong/undefined/weak bindings and verdicts
  are unchanged. Every one of the deleted owner's 13 external COMDAT copies
  survives identically in the consumer, including the rowed helper.
- Refresh the current consumer in an in-memory copy of the same runner index;
  retire the deleted object with link_check.forget, the exact operation used
  by --update-index for sources no longer in the ledger. Both before objects
  had only the helper duplicate; the surviving owner now has no finding.
  Run link_check.main against an isolated scratch serialization of that
  index: LINKS, 0 -> 588 existing retail bytes. The shared index is unchanged.
  A raw check against its unretired stale owner would still report that old
  duplicate, so the retirement is explicit rather than silently omitted.
- This is self-strict currency for the surviving owner with a legacy local
  prediction against external providers. No closed-strict closure, fresh
  census gain, link.exe placement or data-back gain is claimed. Matched and
  authored bytes grow by zero; the previous 28+560 bytes now share one unit.
- EH: 2/2 EXACT, no missing objects or baseline findings. Frozen declarations,
  canonical classes, converged data (eight addresses), shadow data, whitespace
  and CSV checks pass. Affected placement sweep: zero bodies and zero pins.
  Normal commit hooks run the byte and admission checks again.
  The independent full object proof also passes against upstream's surviving
  implementation after rebasing, with the same unchanged non-debug contents.

Selection: repair_queue.py link, link_rank help/top/near and D/S rankings.
Previous triage at reverse/re_attempts.log deferred this repair only because
another worker held the consumer file; that claim has expired. Both files and
the helper RVA were claimed before editing. Previously repaired debug hash,
constructor and tree-insert queue entries were not repeated, nor were still
blocked GameInfo compiler-shape trials. No matching per-row data-back artifact
was available or used to rank this duplicate-definition repair.

BFME1 review: verified clean gitlink/checkout a7c38d3b2597121f178ab5190b3062478823257d
is preserved. Reviewed upstream de59a7e9 (consistent COMDAT expressions) and
4966496c (surplus inline emission), including their byte/link verification
records. The ownership/emission principles apply; target Apt/AsciiString
algorithms, layouts and addresses are inapplicable. Official master fetched
to e22c4572edf087614ded84f3191b47a1127c5b22. The freshness pointer update remains
blocked by another worker's live reference/open-bfme-1 claim and outstanding
old/new full-byte comparison already documented by the previous seat. No
pointer edit or successful freshness stamp is made.

No census build/measure/history, full link cycle, nightly, boot or shadow
publisher was started. Broader link placement remains for authorized runners.
