ScoreKeeper vtable owners and tree cleanup
=========================================

Input BFME2 2431c48671, rebased on 626aa9f32f. BFME1 verified pointer
92f6bbe8e1dc. Published census 5366c4f808 (2026-10-20 12:21), retail-truth-2.

Target identity: the rowed ScoreKeeper constructor/destructor write C1AD98.
Its four native slots are 39C5E1 (named deleting destructor), 39B78D,
39C3A6 and 39C7B8 (named DoXfer). Slot 2 returns the literal ScoreKeeper;
slot 1 stores byte 1 at this+110. Snapshot's canonical retail slot contract
establishes post-load/name/xfer order. Existing ScoreKeeper views already
use public capitalized LoadPostProcess/GetSnapshotName overrides. Rename
the two opaque owners accordingly and move their unchanged native bodies
into the destructor's existing class view. Do not infer a flag purpose from
the byte store. No second name or pin is added at either address.

BFME1's ScoreKeeper_loadPostProcess.cpp at the verified revision was
reviewed: it has a protected lowercase empty body. Only the slot purpose
is corroborated by that donor; BFME2 behavior, offset and signatures above
come from target bytes, vtable and existing target declarations.

After fixing both missing vtable names, the constructor retains a different
_Rb_tree destructor for its existing Rva0039CAE1Allocator. Only two units
emit this exact specialization: the constructor and destructor. The kept
56-byte destructor differs from the constructor's 52-byte /EHsc copy by an
EH-state update before free. Declare the constructor's specialization only,
so its unwind calls use the kept destructor provider. Constructor normal
bytes and its complete native EH graph remain exact. Allocator identity
remains opaque; its previously established 24-byte header family is unchanged.

Paired current-object legacy prediction against the same census:

  ScoreKeeperDtor.cpp             0 -> 255 B
  ScoreKeeperCtorBFME2.cpp        0 -> 237 B
  DispByteOneSetters.cpp        455 -> 447 B
  SubsystemNameGetters4.cpp     245 -> 239 B
  Total                        700 -> 1178 B  (+478 B)

Both generic units retain their link status. The 14 moved bytes were
already linked and are deducted from the net improvement. No new C++ byte
coverage is claimed. Findings: destructor 2 -> 0, constructor 3 -> 0.
These are legacy predictions, not self-strict or closed-strict executable
placement evidence. No census/full link cycle/nightly/boot runner was used.

Acceptance: strict bounded before receipts verify 105/105 rows in four
units. Final six-unit receipts also refresh the rebased byte-vector and
buddy-thread repairs: 110/110 rows, 41 string literals, zero empty-string
refs, floats or imports, two complete STLport folds verified. ScoreKeeper
EH EXACT 2; zero nonexact, baselined or missing objects. Frozen/class gates
pass; shadow data zero findings and converged check ten addresses with zero
second names. check_csv passes. Placement resweep of both ScoreKeeper
units finds no extra bodies or pins.

Ignored diagnostics: build/link-seat-score-{before,before-gate,trial,
ctor-trial,after,final-link,final-gate,eh,data,place}.txt.
