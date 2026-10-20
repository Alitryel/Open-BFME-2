# Script cleanup receiver binding

At BFME2 44d0196f61, three consumers declared retail 0x003B693A on
ScriptList, but the matched 59-byte provider owns the member as
Rva003B693AHolder::rva003B693A (Rva003B693AClear.cpp). Bind the calls to
that existing receiver view, preserving the receiver address and ABI.
No pin, layout, vtable, or provider body changes.

Target evidence: Player::rva002AD25B calls 0x003B693A on its stack
ScriptList; SidesList::discardOverriddenScriptsAndTeams calls it on the
SidesInfo script pointer. Existing caller rows establish the call sites;
the provider row establishes the target. The address-based receiver name
is retained rather than asserting a recovered ScriptList method identity.

Paired link_check against the same published index (b73720bed9,
2026-10-20 05:34): PlayerSkirmishTeamCopy 0 -> 656 linked bytes;
provider remains 59. Total of this pair 59 -> 715. The two SidesList
units lose this unresolved name but retain independent blockers; no gain
is claimed for them. This is a legacy index prediction, not a full
closed-strict link cycle or a self-strict measurement.

Acceptance: ./build.sh on all three consumers: 94/94 exact rows;
eh_verify.py: 14/14 EXACT; find_declared_unmatched.py: all definitions
matched; git diff --check clean. MSVC settings are unchanged (source
// cl: flags). No authored C++ byte growth; 656 bytes newly link.

BFME1 linking review: official master 0dc8a26a9 was reviewed from the
verified a2c8039e pointer. Recent StringBase/GadgetRadioSetText cleanup
repair 8c49200d6 explicitly inherited BFME2 GadgetRadioButton.cpp's
binding, so it supplies no independent BFME2 gain. This repair uses the
existing BFME2 rowed provider directly, not a BFME1 layout assumption.
