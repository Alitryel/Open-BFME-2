# Current-provider link lane reassessment

Inputs: BFME2 d2332d5a5c; clean BFME1 f5140c1cff6a58e16276fd6de6788186286953d4;
published legacy index 11b3872700, 2026-10-23 23:06, fetched successfully.
No C++, ledger ownership, pin, shared header, verifier or baseline changed.
No new linked bytes, self-strict closure or closed-strict gain is claimed.

Startup pull/rebase and check_csv passed. Reviewed the previous session's
request-set allocator blocker and ranked audit before selecting work. Refreshed
top-30, near-2, near-6, owner-gap and private-class blocker discovery. A joint
current-object link_check over 515 authored, existing sources with at most six
census blockers admitted 80 units and displayed 13,191 census-relative bytes.
Those are inherited improvements, not this session's work. Diagnostic copies
marked unreferenced were excluded from repair selection.

Follow-up cohorts explain why the most tempting remaining names are not
standalone repairs:

- CreateAHeroHero, Rva0040AA27, OwnedRecord840Copy, StlportOwnedRecordDeque and
  PeerThread: 2/5 link, 1,201 -> 1,201 B. Award and PeerResponse providers
  already link. Hero still has uint/bool tree lifetime conflicts when not
  including its complete provider cohort; the existing hero-owner handoff
  records that cohort's inherited success. The network consumers additionally
  need 2148-byte record lifetimes, queue construction/map initialization and
  competing string helpers. Merely rebinding the 840-byte record cannot link
  either consumer. No rename or alias was attempted.
- Allocate_New_Surface, PendingSurfaceStructResize, twiddler and
  vector_class_resize: 1/4 link, 368 -> 368 B. Surface allocation owns 561
  nonpadding bytes but has VectorClass<int>, DynamicVectorClass<int> and
  pending-surface cleanup conflicts, plus a wrong selected pending Add.
  PendingSurfaceStructResize also sees wrong selected ctor/assignment/Resize;
  twiddler has independent definition/persistence providers missing. Copying
  twiddler's visible base-destructor specialization alone cannot close this
  cohort. Source frozen-definition check passes. File claim acquired for
  inspection, then released without edits or build trials.
- DX8SkinClearVisibleList and wide money put still have the exact independent
  codegen/helper blockers recorded in flash-regions-link-20261023.md and
  wide-currency-fill-link-20261023.md. No failed variant was repeated.
- Shroud constructors' duplicate definitions do not remove the native derived
  predicate/table contract gap in link-seat-provider-recheck-20261024.md.
  BridgeBehavior and ExperienceTracker likewise retain the native virtual
  contract prerequisites in their existing handoffs; no table suppression.

Reference linking review: inspected BFME1 linking changes through 32774ab0,
including c7e241b5's GeometryInfo record-vector declaration. BFME2 already has
that declaration. The shape vector has distinct ownership/copy evidence, so
the record repair is not permission to substitute a shape provider. The
reference checkout was preserved; its file scope is foreign-claimed, and no
freshness-success stamp or pointer advancement was made.

Fallbacks: name_globals --dry-run found zero edits. repair_queue link repeats
the census leads above. rehome_rows --limit 12 cannot run without the absent
build/link_census/census.log; this is an artifact blocker, not an empty queue.
No data-back status artifact matching the census commit was available, so no
data-back ranking was manufactured. Full census/link-cycle/nightly/boot runners
were not started. High-byte private-class leaders require scope-wide ABI work
or are foreign-claimed. Prior blocked codegen variants were not rerun.

Scratch diagnostics (ignored, optional): build/seat-current-probe.log,
build/seat-owned-current.log, build/seat-surface-before.log and seat-rank*.json.
The counts and native/provider prerequisites above are the durable handoff.
progress.py origin/master reports +0 authored C++ and +0 census linked bytes.
