# Foundation construction: checked containers and the final member transfer

No exact recovery. Keep `reverse/attempts/0x0045569d.cpp` unchanged. Its complete
1175-byte body remains closer than these alternatives to retail's 1174 bytes.
No production source, row, pin, compiler setting or verifier was changed.

Identity/boundaries are unchanged: FoundationAIUpdate's secondary interface
vtable at VA 0x00C1A690, slot 7, the rowed caller at RVA 0x00456134, and the named
WorldBuilder twin at VA 0x011715D0. Native RVA 0x0045569D ends with RET 0x18 at
0x00455B30, before the next function at 0x00455B33. The current home is
`Code/GameEngine/Source/GameLogic/Object/Update/FoundationAIUpdateSlots.cpp`;
its definitions passed find_declared_unmatched before this attempt. Prior
attempts and the October 19 semantic correction were read first.

The baseline has three structural regions. Retail keeps the interface receiver
in EDI after the Lua event and newMember in EBX; ours reloads the receiver into
EBX and uses EDI for newMember. The cost block also schedules the input-template
and player loads differently. This is a register/liveness mismatch, not evidence
for a different cost receiver or signed cost. The native negative test followed
by FADD 2^32 proves the unsigned-to-float conversion in the bank.

New target-grounded tests (119 compilations across the groups below):

* Actual STLport `std::bitset<218>` at ThingTemplate+0x108, with corrected
  following padding and the real `_Base_bitset<32>` upgrade container. Normal
  inline budgets give 1235/1280 bytes because map lookup becomes inline too.
  Keeping the already-rowed GameLogic lookup out of line gives 1177 bytes and
  four structural regions. All 32 combinations of checked and raw accesses at
  the five kind-test sites give 1175 or 1177 bytes; only the first test matters.
* Actual 591-bit model-condition storage, supported by the target BitFlags
  transfer/count/table routines, gives 1173 bytes under larger inline budgets,
  but five regions and additional LEAs/register mismatches. Header-only controls
  retain the baseline. set(false), reset, wrapper and Bool/unsigned tests do not
  resolve this. A shorter emitted body is not a successful match.
* Real ObjectModule/BehaviorModule hierarchy, const/nonconst getObject views,
  and a visible exact 43-byte Object::findModule provider do not fix allocation.
  Individual ID accessors, grouped copies and fluent setters are likewise inert.
* Cached Bool/Int results for the two module guards, equivalent separated cost
  guards, Module* carrier views with casts only at ID access, and earlier
  declarations of the two real live pointer locals remain 1175 or worsen to
  1182. No unused locals or artificial writes were retained.
* Ordinary compiler variants retain 1175; /Oa and /Oi change unrelated code.
  Moving the large EH body into a forceinline static member leaves an unresolved
  out-of-line helper, so that is rejected rather than pinned.

The tempting historical size-exact variant that omitted a guard is not proof:
native 0x00455A6C..0x00455AD8 skips cost when **either** module is null. Cost is
also skipped on rebuild, after copying the IDs. These guards must survive any
new source spelling. Direct native disassembly confirms the WB nesting here.

Useful replay sources are the adjacent `foundation-context-*.py.txt` files.
Copy the seed driver to build/foundation-bitset-oct20.py and run it first;
it freezes the bank from commit 50b6f372cc and normalizes only scratch include
paths plus the raw kind adapter's misleading name. Copy the other drivers to
their original build/ filenames shown in their names and run after the seed.
They use explain_mismatch, not the unsafe raw shared-cache compile entry point.
The diagnostic baseline alignment is preserved alongside this handoff.

Inputs: BFME2 50b6f372cc initially, pulled to 886b6b1a5a after independent
upstream landings; BFME1 verified pointer 92f6bbe8e1dcdb46b5d27da0674313efc822b790.
Default /O1 /G7 /arch:SSE /DNDEBUG /MD /GX, explicit static STLport only in
checked-container trials. Work began 2026-10-20 13:19 UTC; model=gpt-6.1-sol.
No exact-byte gate passed. The live claim is released after recording this
handoff; the production tree has no attempt to revert.
