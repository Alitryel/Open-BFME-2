# Rampage module-data vtable dependency repair

BFME2 source base: c340be4361d1cb7050019ed587d8ff9a8a9be085.
The consumer is RampageBehaviorModuleDataCtor.cpp; its unchanged provider is
RampageBehaviorModuleDataDtor.cpp in the same Behavior directory.

Replace the constructor's hard-coded vtable VA 0x00C40EF8 with a direct
reference to the existing ??_7RampageBehaviorModuleData@@6B@ symbol. The
112-byte constructor at RVA 0x00458C0F now has a zero-addend DIR32 relocation
at body offset 36. Its other bytes and relocations are unchanged. The
destructor object is unchanged and defines the real vtable. Its first slot
references MSVC's vector deleting destructor weak external, whose compiler
default is the matched scalar deleting destructor at RVA 0x00458C7F; the
retail table's first word independently contains VA 0x00858C7F.

Object proof compares every non-debug/non-directive section after replacing
that one immediate with the relocation. Compiler-local names are compared by
section, offset, storage and type; .sxdata symbol indices are compared by
their referenced symbol. These metadata ordinals change when the extern is
added. No other section bytes or relocation targets change. No new identity,
layout, function, pin, shared header, compiler flag or data row is claimed.

Acceptance:

- Before/after bounded link_check.py --prepare-current verifies 5/5 matched
  rows across consumer and provider with strict reusable compiler receipts.
  Independent ./build.sh passes 5/5 with no skipped string/float/import refs.
- EH verification is EXACT 2, with no baseline, non-exact or missing objects.
  Data checking has zero findings; converged data checking has zero second
  names and zero unjudged rows. Class and declared-definition checks pass.
  check_csv.py passes. place_bodies.py finds zero additional bodies or pins.
- The supplied local index is measured at cb660e4d97, 2026-10-13 04:02 UTC,
  SHA256 4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e.
  Its metadata and source base are attached. The newer committed status at
  67e1365aa9 is used only for discovery, never for before/after arithmetic.
- Same-index legacy local preview: constructor hard-coded-address blocker
  1 -> 0, LINKS, own linked bytes 0 -> 112. Provider remains LINKS, 84 -> 84.
  Cohort linked bytes 84 -> 196: **112 existing bytes gained in the legacy
  local preview**. Newly authored matched C++ bytes grow by zero.
- Strict receipts establish current byte verification of these two objects.
  They do not establish self-strict LINK closure or closed-strict gains.
  No full link cycle, census build/measure/history or other maintainer-only
  runner was started. Index, committed status and history are unchanged.

Donor review: retained verified BFME1 pointer/clean checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85; official master was fetched to
0e5755b95fa20855639253131c03ef436bb8d076. Reviewed its
game/Libraries/Source/WWVegas/WW3D2/MaterialInfoDtor.cpp, which directly binds
an existing decorated vtable with __identifier. That technique applies here;
BFME2's address and provider evidence above are independent. No donor body
or layout is imported. The prior unfinished same-revision old/new full-byte
freshness comparison remains blocked on stale-TU preparation/shared compiler
availability; this narrow repair preserves verified inputs and does not write
a freshness success stamp or advance the pointer.

Discovery used repair_queue.py link and link_rank.py --top 15 --near 8,
followed by the address-only ranking and this file's one-blocker report.
The queue remains populated. The prior blocked voice-response reconstruction
was not retried. This concrete repair is complete; broader fresh link
measurement and the overdue verified BFME1 pointer update remain outstanding.
