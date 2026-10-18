# GenericObjectCreationNugget constructor linking

Measurement uses the published c2c5ac8c27 census index (2026-10-18 11:36),
with the current constructor and destructor owner supplied together to
`python3 tools/link_check.py`. Before: destructor owner 252 B links,
constructor 488 B does not. After: both link, 740 B total, +488 B.
This is legacy LINKED preview, not a self-strict/closed-strict or runtime claim.

Target evidence: rowed constructor 1F0E32 copies the empty AsciiString at
VA DE0878, whose existing canonical declaration is AsciiString::TheEmptyString.
The old unrelated global declaration had no provider. Rowed base destructor
1F0409 is the empty virtual destructor that restores its vptr. The rowed
29-byte deleting wrapper 1F010B expands that restoration inline. Giving the
constructor view that established empty body emits the correct wrapper;
marking the owner's identical destructor inline makes both copies COMDAT
instead of colliding with a strong definition. No pin, alias or new layout.

The retained BFME1 donor c1315665's method-copy suppression repair was reviewed
as a lead, but no dllimport suppression is needed here. A novtable trial kept
the parent exact but emitted a non-retail implicit base constructor; discarded.
The final change retains the retail base vtable and destructor behavior.

Acceptance: build.sh passes 8/8 function rows across both units;
link_check --prepare-current issues strict reusable compile receipts for both
(no strict link closure inferred); eh_verify reports EXACT 2, no baseline;
find_declared_unmatched, class_gate and git diff --check pass.

Cause sweep: census blockers mention the same deleting destructor only in
ObjectCreationNuggetParse.cpp besides this constructor. That unit has six
additional blockers and is not changed for an unmeasured zero-byte repair.
The Requirements_Create and PositionCreate callers need unrowed 2618-byte
reallyCreate 1F1634 (existing blocked attempt 65133); no retry without its
missing dependencies. This repair adds no authored C++ function bytes.

Post-commit shadow identity diagnostic: the pre-existing global AnimSet vector
base constructor spelling binds 211E58 and is classified wrong. This repair
does not alter that template call or its target; the byte gate independently
verifies the two emitted folded constructors and resolved retail owners.
The diagnostic is retained as a limitation, with no baseline modification.
