Lobby GUI link repair, 2026-10-20

Parent fb3306104d; published census 5366c4f808 (2026-10-20 12:21).
GUIUtil's two mutable color declarations named different symbols from the
verified const definitions in LanGameOptionsMenu.cpp (data rows 9BA764/9BA768).
Match the owner declarations; loads and all 14 matched bodies remain exact.
The unit also emitted a nonretail recursive string-set cleanup. Declare the
specialization so it uses the existing complete 53-byte owner at 56CC3 in
stlport_rb_tree_hint_asciistring_set.cpp, including string destruction.

Paired current-object legacy preview: GUIUtil 0 -> 3,186 nonpadding bytes;
tree owner stays 1,247 and color owner stays 0. The color owner's unrelated
unresolved callees and COMDAT blockers remain. No closed-strict or full-link
gain is claimed. Strict preparation verifies 18/18 rows for consumer/color
owner before and 26/26 for consumer/tree owner after; normal byte, literal,
float and import gates pass. Declared-definition and diff checks pass.

Donor reviewed: BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790.
Its native GUIUtil TU supplies no corresponding color/cleanup adaptation.
STLport inputs/vendor/stlport/stl/_tree.c:643-651 establishes recursive
right-subtree destruction followed by value destruction and deallocation;
BFME2's existing byte-verified owner independently proves target identity.
No target class layout is inferred from the donor.

Cause sweep: only GUIUtil declares these two colors with mutable types.
The two other indexed units losing the same string-set cleanup are
AudioFileCacheThreadEntry and GameSpyInfoCtor; both have independent blockers
and require broader repairs before this declaration would link their units.
No new pin, alias, shared header, verifier or ledger row is introduced.
