Horde merge pooled-list linking repair, 2026-10-20

Bind the HordeContain merge unit to the established Object-pointer pooled
node factory, using the same visible noinline specialization as Player.cpp
and GameLogicDestroyObject.cpp. Native 0x001EB9AC..0x001EB9C8 establishes the
12-byte node, value at +8 and pool DB8FEC; no new identity or layout asserted.
Keep comparisons local, and retain the existing native inline erase while
suppressing its competing out-of-line copy. The inline erase behavior is
unchanged; paired inventory has no import-pointer reference.

Before/after normal full-row gates and strict preparation pass 1/1 (1415B),
EH graph EXACT. Paired frozen-index legacy preview e7a7769fe5 improves from
0 to 1412 nonpadding linked bytes. Both phases replace the object using its
census basename in the same unchanged index. All five blocker fields empty
afterwards. Ten redundant COMDATs disappear, only the node-factory digest
changes, every other retained COMDAT byte/relocation digest stays identical.
See proof.json and local-snapshot reproduction proof.py. Self-strict receipt
verified; closed-strict closure and executable gain unmeasured. C++ growth +0.

A declaration-only factory trial changed the parent register allocation and
failed. Typed comparisons plus imported forceinline erase passed; keeping the
existing pooled specialization visible then also passed and removed the last
blocker. Other factory users were inspected: LinearCampaignAddCarryover and
MoveToFormationGroupOrder retain unrelated vector/hash-table blockers, so no
zero-gain source changes were kept there.

BFME1 linking review unchanged at 4483e88da1c2, donor a411b334c/3313189ad/
c54305633 ownership leads reused; target implementation taken from existing
BFME2 byte-verified pool providers. t=12min model=gpt-6.1-sol.
