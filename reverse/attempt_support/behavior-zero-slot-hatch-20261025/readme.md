# Compile the existing zero-result interface slot directly

The SpecialPowerModule destructor unit used an alternate-name directive to
bind its existing BehaviorModuleInterface::behaviorAnchor declaration to the
shared ControlBarInput body. Retail's BehaviorModule interface table at VA
0x00BEE9C0 starts with VA 0x004D43D0: the complete three-byte `xor eax,eax; ret`
body. The native destructor restores that table at its +0x0C subobject.
These are target facts. The method's existing structural label and its
original return type remain unrecovered; the C++ view exposes only the observed
zero machine-word result and does not assert a pointer's pointee or a name.

Define that slot with real C++ returning zero and remove the old linker alias.
The constructor and companion unit declare the same interface result, so
their emitted copies remain consistent. The compiler emits the entire
three-byte body with no relocations. Normal add_match --icf-owner admission
records its true gen-alias twin of the existing ControlBarInput owner, without
a pin, duplicate real owner or new unique-byte claim. The callback owner stays
unchanged. Only one of the inspected files contained this exact alias; other
similarly named declarations and real bodies were not rewritten blindly.

Fresh private compiles preserve all eight pre-existing owned bodies. The
184-byte destructor and 28-byte deleting destructor retain every relocation.
The EH handler's bytes stay unchanged while its local FuncInfo spelling moves
from $T1556 to $T1560. Official verified_funclet_locations, after the complete
parent EH graph passes EXACT, binds old $L1496 and new $L1500 to the same
native cleanup at 0x0078CE14. Its eight bytes and relocation are identical.
The containing associative section is 18 bytes: cleanup8 followed by handler10;
the next symbol and the exact graph prove the boundary. The entire section's
raw bytes also remain identical. The existing funclet row's compiler label is
refreshed, with its parent/address/extent unchanged and no new object-symbol
alias row. No generated source or parent was inferred from adjacency.

Production acceptance: all 9 rows pass the normal whole-file gate across the
three units; all 3 EH graphs are EXACT, without baseline or missing object.
All three units pass strict reusable-receipt preparation and frozen-file
checks. Code identity reports zero new findings. The shrink-only hatch tool
retired the one alternate-name key; unrelated register normalization was
reversed with context-checked patches, preserving other grants and counts.
The enforced staged register credits exactly one removed hatch.

Against provider index 51fde01dff (2026-10-25 13:53 UTC, historical census
d2636bb381 at 09:42), the current three-object preview preserves the constructor
and companion's 624 linked bytes. The native destructor unit retains its
original three vtable conflicts, without an added conflict from the new slot.
This is one escape-hatch debt retirement, zero new C++ coverage, and no new
linking headline or closed-strict/executable-placement claim.

Inputs remain at verified BFME1 0bf534ea7ccde110c456edb9cd2dd5dae823c953;
the local repair was developed after BFME2 17d211067f. Existing source compiler
settings and field layouts are unchanged. No link cycle, census, nightly,
boot/smoke test or shadow publisher was started.

## Remaining native class/data prerequisite

The indexed Zero Hour-shaped BehaviorModule copies have 14 primary and 34
secondary slots. Retail's primary table at 0x00BEEA7C instead has 12 code
pointers followed by its class-name text, with destructor/load/name/xfer at
slots 0/1/2/3. The secondary table at 0x00BEE9C0 has a run of 47 code pointers
before that independently installed primary table; no interior .text reference
was found at 0x00BEEA70/74/78. This bounds the observed run, without settling
every slot's C++ signature or the original allocation. The class-contract tool
finds 319 views and still queues slot46 between slot46(int) and the
FoundationAIUpdate-specific rva00455B42(int). Resolve the native interface
identity/signatures before adopting a header; do not choose a name merely to
silence the queue. Snapshot already has a registered canonical header with
the native slot order; do not introduce another private Snapshot copy.

SpecialPowerModule's primary table at 0x00C4E868 has 14 code pointers before
the following string. Its secondary at 0x00C5E080 has 25 consecutive code
pointers before the independently installed next table at 0x00C5E0E4. Current
constructor/destructor interface copies contain only 16 slots and disagree
on three entries. Matching those incomplete copies alone would not establish
retail's full table. The native primary slots12/13 already have rowed methods
at 0x00493805 and 0x00493EA7. BehaviorModule's native slot3 reaches the row at
0x004C9C7D, whose current nonvirtual signature also needs coordinated ABI
reconciliation when adopting the class. No second name or pin was added.

The BFME1 native Module header and ZH Behavior header were reviewed as leads;
their declarations do not supply this complete BFME2 contract. Preserve the
native constructor/destructor table bindings and complete data ownership
while reconciling those classes. The broader LINK-004 family remains open.
# Rebase validation

Rebased onto `8983e1f1f1`, which includes the upstream correction making
`SpecialPowerModule::~SpecialPowerModule` protected (`MAE`, not `UAE`).
The union merge reintroduced the old cleanup row beside the updated row.
Reconciled that single owner to the current protected parent and its exact
graph-proven `$L1500` label. Repeated verification passes all nine body rows,
all three EH graphs EXACT and all three strict current receipts. The earlier
private comparisons below describe the pre-rebase parent spelling; the current
receipts and rebased logs establish the final source state.
