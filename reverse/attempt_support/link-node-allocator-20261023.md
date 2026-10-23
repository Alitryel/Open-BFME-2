# Hashtable node allocator linkage, 2026-10-23

At BFME2 0959c3ad9b, BFME1 f36a4db066aa, published retail-truth-4
census 0fa62a2841, current-object legacy preview excludes the 192-byte
StlSweepR3Rva001FDC0F.cpp only for the opaque record copy constructor.
No source change or linked-byte improvement is retained.

The existing _M_new_node pin names RVA 00056E53. Its real row is the
37-byte stdcall Rva00056E53New in stlport_hashtable_hint_00058ead.cpp:
12-byte allocation, next pointer zero, rowed _Construct of an eight-byte
AsciiString/payload pair. Existing member-view pin rva00056E53 on
Rva000427195 records that ECX is ignored. Prior attempt-log entries at
001FDC0F independently identified this node-copy call pattern. The original
one-byte opaque record does not establish the actual value's identity.

Trials under original /O1 /EHsc flags:

* Declaration-only specialization of _M_new_node passes the full 192-byte
  scoped gate. Legacy link preview then requires that missing member name
  instead of the record copy constructor. A pin does not supply a provider.
* Force-inline specialization calling the rowed stdcall function directly
  produces 186 bytes: ECX receiver loads disappear and registers change.
  Both native call sites load ECX from the saved receiver before calling.
* MSVC 7.1 rejects a free __thiscall function-pointer typedef (C4234);
  that route is unavailable on this compiler.

The source was restored and both file/RVA claims released. A supported
provider ABI/name reconciliation must preserve the caller's member-call
summary. Do not add a dummy record constructor, unproven alias or second
owner for RVA 00056E53. No strict or closed-strict gain was measured.

Session handoff
---------------

The dedicated link lane was checked with `link_rank.py --top 30 --near 2`,
`class_views.py --blockers`, and current-object `link_check.py` previews of
ranked near units. Many apparent gains were already present at the current
master revision; none are credited to this session. The remaining inspected
items need supported provider identities/ABIs or shared class/vtable contracts.
Tribute-row 0050FC54 still needs the 0050FC54 and 0050FF55 virtual destructors;
Drawable 00278440 still has the documented volatile cleanup/COMDAT conflict.
Prior evidence was reviewed rather than repeating unchanged blocked trials.
FontLibrary's constructor already links, while its W3D consumers need a shared
class/vtable repair across the competing providers. No source edits remain.

`name_globals.py --dry-run` offered no edits in the inspected address-getter
units or AssistedTargetingUpdate. `repair_queue.py link --limit 8` was checked;
its leading repairs remain covered by existing evidence or already-landed
fixes. `rehome_rows.py --limit 8` could not run because the published index
does not include build/link_census/census.log; a full census was not started.
This missing artifact is a lane limitation, not proof of an empty queue.

The verified BFME1 pointer remains f36a4db066aa. Official master fetch found
138757e9b746, but codex8 owns the fresh shared BFME1 update lock, so this seat
did not change the donor pointer or interfere with that verification. Reviewed
BFME1 freshness and earlier link-repair handoffs before the local trials.

Final checks: restored allocator `./build.sh` passes 1/1, 192 bytes;
`tools/check_csv.py` passes. All file and RVA claims from this session released.
No self-strict or closed-strict improvement, nor new legacy linked bytes.
Model: gpt-6.1-sol .
