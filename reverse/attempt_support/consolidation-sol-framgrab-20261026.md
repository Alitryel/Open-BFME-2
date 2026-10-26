# FramGrab protected-access prerequisite, 2026-10-26

The codexb family-B shard-0 allocation includes
Code/Libraries/Source/WWVegas/WW3D2/FramGrab.cpp. Current --plan approves five
rows in three files, with no mixed or refused donor. File claims cover the
seed, Rva00958200BfmeThingTXACtor.cpp, Common/BfmeConv1867.cpp and this handoff.
The Common source is unchanged; its claim covers dependency verification.
The WW3D2 original-path planner and its alternatives were reviewed. Planner
evidence does not grant merge approval; the current in-memory plan does.

The prior mechanical handoff and fresh ordinary --merge --dry-run agree:
neither donor can join the seed because the composed FrameGrabClass omits the
friend declaration carried by each donor's verified private view. Both fail
C2248 at the existing protected Rva00958570_Flush_Buffered_Frames call.
Add those same two friend declarations to the seed. Preserve protected access,
the mangled member name, fields, virtual order, flags and every function body.
The existing BfmeThingTXA/BfmeOwnerYX spellings are donor declarations, not
new historical-name claims. No canonical class or shared header is changed.

Before and after ./build.sh on all three sources: 5/5 matched, eight literals
and twelve named imports verified. Frozen-file checks pass on all three;
existing absent-from-retail anchors are unchanged. Class and data checks pass;
data reports zero findings and zero outside baseline. The scoped identity
check reports five rows, zero problems and zero notes. Scoped link_check
--new-variants --staged-peers --shadow exits zero. The Microsoft-header scan
has zero failed scans and retains the pre-existing prototype debt. No header,
identity, data or hatch register is edited or retired.

The final ordinary composition trial accepts all three files and all five
rows, with no mixed, refused or rejected donor. This demonstrates two newly
compatible donors / three existing rows (1,060 retail bytes), not recovered
coverage or a confirmed Luna landing. Leave the actual merge to Luna.
No source files or rows move in this prerequisite.

All three standalone objects preserve their complete external code/data
definitions, bodies, relocations, section flags, COMDAT selections and
undefined-reference sets compared with pre-edit snapshots. The final composed
object build/tu_skeleton/1a6430d2e77fa671.obj preserves their entire provider
union with no missing, added, changed or multi-variant provider. Its sole
undefined-reference removal is the protected flush member, satisfied by the
identical provider now in the same object. No local relocation referent or
native EH graph is present. This checks the composed bindings as well as the
individual matched bodies; it does not claim an image census improvement.

Receipts: build/sol-framgrab-{before,after}-build-20261026.txt,
build/sol-framgrab-{before,after}-trial-20261026.txt,
build/sol-framgrab-before-20261026.json and
build/sol-framgrab-composition-proof-20261026.txt. The scratch proof uses the
supported allowed_symbols object reader, census COMDAT selections and
eh_verify APIs. Its initial parser included the trial's carried/trailer
metadata as source, so no cached object was found; locating the actual
// cl: source boundary fixes that evidence parser without changing a gate.
An initial identity wrapper asserted the returned tuple rather than its
problem list; the corrected wrapper checks problems and notes explicitly.

The earlier planner raced deletion of a temporary trial source and was
discarded. The final planner was regenerated only after the completed trial;
its currency check passes. No check refusal is bypassed.

The complete outgoing batch has only source edits and evidence/log files:
GameResults guard, NetCommandRef declarations, inherited recovery evidence,
and this seed friendship fix. No source is moved, renamed, deleted or added;
active tools, hooks, workflows, includes, build inputs and registries need no
path repointing. Historical EA paths remain intact. No committed TU-map,
ledger owner or protected-register change. File reduction: zero. Recovered
C++ body bytes: zero. Identity/data/header debt retired: zero.

Audited origin/master 47e030bafc against HEAD 8a4b6b7e80 plus the staged
prerequisite. The double-dot diff also shows incoming funclet/name/census
records; merge-base..HEAD confirms the outgoing changes listed above.
Incoming changes touch no dependency in this repair and no AGENTS.md.

Retain all four file claims above until the publisher confirms landing, then
release them. The inherited eight prerequisite scopes are recorded in their
handoffs and also remain held while pending. Publication status and exact
pending SHAs are recorded by the runner/session handoff. Existing batch-index
freshness limitations remain for the next census; no maintainer-only link,
nightly or smoke runner was invoked.
