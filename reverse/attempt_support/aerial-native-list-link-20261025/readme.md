# AerialPathfinder native-list reconciliation, 2026-10-25

Inspected at `27b23d675b`; BFME 1 pointer `0bf534ea7ccde110c456edb9cd2dd5dae823c953`.
No production source or function-ledger change was made. This is a resumable
private candidate, not a completed repair or a linking gain.

The current constructor at 0022C987 (75 bytes) fails ordinary preview on an
invented base destructor, `BFME2NativeNetwork::baseConstruct`, an imported
node allocator and a competing `_List_base<BfmePod8>` destructor. The paired
destructor at 0022C9F6 already uses the registered `SubsystemInterface`.

Private trials:

- Adopting that existing canonical base preserves every constructor byte and
  its exact EH graph while resolving both invented base dependencies.
- The existing bfmealloc/bfmelist settings remove the imported allocator;
  the constructor remains 75 bytes and its EH graph stays EXACT.
- The final list destructor conflict is an actual identity conflation:
  the global `BfmePod8` destructor pin is 002FECBC (a different container),
  while this constructor/destructor family's native cleanup is 004EC395.
  Do not alter that shared pin or merely suppress the competing copy.
- The target's existing `AerialPathfinder_getNoFlyZoneHeight.cpp`, 00375AF7,
  independently establishes the same list at +10 and the polygon/height
  payload at node+8/+C. Its existing `Rva00375AF7Entry` view is adopted in
  the banked constructor and destructor. The original element name and
  original volatile qualifiers remain unknown. BFME 1's corresponding
  query supplies a semantic lead only; target offsets are independently read.
- The complete constructor (75), destructor (59) and deleting wrapper (28)
  retain their raw bytes; both private parent EH graphs are EXACT. Relocation
  names intentionally change to the canonical base and native-entry helpers.
  The new helper emissions have whole extents 11 (proxy at 0014F3C4),
  39 (clear at 0023DAA5), 41 (constructor at 0035C9A6) and 23 (destructor
  at 004EC395). Their prospective folded bindings still need normal admission
  and full byte/relocation gates; private size/raw-byte results are not that gate.

Concrete prerequisite: remote reservations for 0014F3C4 and 004EC395 were
held by other workers. No work on those bodies or admission was attempted.
Other scope reservations were released for independent work. Recheck claims
before resuming; do not bypass them or add pins/aliases to old spellings.

Resume with the two banked source candidates. Admit the four helper names
through `add_match.py --icf-owner`, in dependency order proxy, clear,
destructor, constructor. Because each invocation verifies the entire unit,
first instantiate the new helpers alongside the unchanged old constructor,
then adopt the final constructor after its dependencies are declared. Keep
that intermediate state uncommitted. Verify the current provider/consumers
together and compare current-input before/after previews. The destructor's
exact parent graph also identifies cleanup `$L4178` at 0076F8AF; inspect its
current scaffold row before any separate supported funclet repoint.
