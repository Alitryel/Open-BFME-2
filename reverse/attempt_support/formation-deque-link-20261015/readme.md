# Formation parser nested-deque provider repair

Base: 1d591774d73933770546db9f1fa2af9def9ec598. Paired local index:
19a2565407, 2026-10-15 09:33; underlying census 5986a99448, 04:52.
The index hash and before/after object hashes are in object-proof.json.
Committed link_status.csv belongs to a different measurement and was used
only for discovery.

FormationAssistantParseFormation.cpp emitted a 119-byte
OuterDeque::_M_push_back_aux_v COMDAT under /EHsc. Retail's existing
123-byte owner, StlportNestedWordDequeAuxV.cpp, uses /EHs and retains
the final EH state store. Declare that specialization in the consumer,
following its existing declaration-only destructor convention. Both units
already agree on the nested deque's forty-byte element and four-byte keys.
No type, layout, flags, shared header, pin or ledger ownership changed.
Original application identities remain uncertain as in the existing recovery.

Acceptance:

- Before and after, bounded strict preparation of consumer and provider
  passes 5/5 byte rows, two literals and one empty-string reference, with
  zero skipped/baselined references and zero named imports. Receipts are
  strict-current. EH verification of saved before objects and current after
  objects passes 2/2 EXACT on each side, with no baseline or missing object.
- Object comparison preserves all 155 unchanged consumer nondebug sections,
  including their bytes, extents, symbols and normalized relocations.
  It removes the surplus helper, its now-unused map-growth dependencies
  and its associative exception data. SXDATA drops exactly that removed
  helper's handler registration; all remaining registrations are retained.
  The provider's complete nondebug section multiset is unchanged.
- Paired in-memory replacement refreshes the same two objects against the
  same index on both sides: consumer findings 1 -> 0, provider stays clean.
  Legacy nonpadding LINKED increases 130 -> 560 (+430 consumer bytes).
  Ordinary link_check agrees: both units link cleanly, consumer 0 -> 430
  and provider 130 -> 130. Same-symbol index inspection finds no other
  losing copy; the separate triple-deque specialization already agrees.
- Frozen-definition, class, new-COMDAT-variant, enforced data, converged-data
  and whitespace checks pass. Data checks find zero issues across two units
  and eight protected addresses. Placement resweep: zero bodies or pins.
- The commit hook reports three shadow code-identity divergences for the
  inner deque's _Destroy, __destroy and destructor. Their emitted sections
  are unchanged in the paired object comparison; this repair does not
  resolve that separate identity debt or establish closed-strict closure.

This is self-strict evidence for the two explicit objects, with a paired
legacy local preview. External-provider currency remains that of the index;
no closed-strict gain, new census, full link result or executable placement
is claimed. No index, status or census history was changed. Saved sources,
objects, receipts and comparison scripts are under
build/formation-deque-link-20261015/. No authored C++ byte growth is claimed.

Reference review: clean BFME1 checkout and committed gitlink remain
a7c38d3b2597121f178ab5190b3062478823257d. Official master fetched at
066fa2a946913ed52ab609b7f723f19ef9bf0521. Reviewed donor repairs
6b9800e65dc6 (private inline comparison), d003077f0b7c (declare the real
provider instead of a competing forwarder), and 4966496c5ae4 (suppress
surplus inline COMDATs). Their ownership principle supports this repair;
no donor layout or code is imported. Freshness update remains blocked by
another worker's live reference-submodule claim and the outstanding old/new
full-gate comparison documented in ../unicode-comparator-link-20261014/readme.md.
No pointer update or successful-freshness stamp is claimed.

Independent attempted repair: W3DModelDrawSubObjectVisibility.cpp's
BfmeStringRecord000B9534 destructor remains blocked. An imported forceinline
destructor suppressed its losing COMDAT while preserving the 506-byte parent,
but converted retail's eight-byte EH cleanup to a nine-byte indirect-import
cleanup at 0x00761C85. EH verification correctly refused it. The original
source was restored and its ordinary byte gate passed; the claim was released.
The failure is recorded in re_attempts.log and subobject-eh-refusal.json.
Do not repeat declaration-only or imported cleanup without new EH evidence.
