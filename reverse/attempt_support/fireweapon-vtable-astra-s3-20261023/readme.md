# FireWeaponWhenDeadBehavior vtable collision, 2026-10-23

Read-only prerequisite audit at BFME2 ee6f67b8a4, pinned BFME1
138757e9b74645fbcbb7724a7af2764e34931e11. Constructor203B at482D80 and
destructor39B at482E96 are already matched. No source edits or gains.

The old blocked note identifies one-slot versus four-slot copies of
??_7FireWeaponWhenDeadBehavior@@6BUpdateModule@@@ but conflates their native
roles. They are **different subobjects at different retail addresses**:

* The constructor's relocation at+69 writes the symbol to receiver+0x10;
  retail stores VA00C496E8. Its COFF table is4 bytes with
  UpdateModuleInterface::update at slot0.
* The destructor's relocation at+2 writes the same symbol to receiver+0;
  retail stores VA00C497B4. Its COFF table is16 bytes, holding the deleting
  destructor, loadPostProcess, s02 and xfer.

See evidence.json, obtained independently from the current ordinary compiler
objects and native immediates. The constructor's primary table is separately
named ObjectModule. The current data inventory identifies native8496E8 as16B
and8497B4 as52B; raw slots at primary8497B4 include the pool-key getter482E51
at index4 and established UpdateModule getUpdatePhase22C4CB at index12.
Thus copying the peer's four-slot view into the constructor would change the
meaning of its +0x10 table, not repair the class.

The BFME1 FireWeaponWhenDeadBehavior.cpp and UpdateModule.h were reviewed
read-only at the revision above. The donor FireWeapon class uses
BehaviorModule rather than BFME2's UpdateModule; its source does not resolve
this BFME2 five-subobject naming collision. UpdateModule's distinct update
interface supports keeping primary and secondary identities separate.

Current-object paired legacy preview at published index491a8b3d87:
constructor0/203B (COMDAT collision above), destructor provider311/311B.
Single-unit preview misleadingly reports the old unresolved destructor
because the cached census predates its rename; paired current objects resolve
that dependency and expose the actual collision. Neither result is a full or
closed-strict game link.

A coordinated class/view repair must preserve each native subobject identity
and the appropriate full virtual layouts in constructor and destructor
providers. The destructor rows482E96/482EBD are held by another worker, so
this seat does not change that provider or introduce a local workaround.
Constructor claims released after recording the evidence.
