# AsciiString list erase provider repair

The census at c2c5ac8c27 selects GameSpyLoginPreferences.cpp's non-retail
list<AsciiString>::erase(iterator), pinned at RVA 0x000BC67A. The insert and
remove STL units already emit the retail byte-and-relocation copy. Declare
this specialization in preferences so its calls bind to that existing owner.
No new pin, alias, class view, provider body or authored coverage is added.

At the same HEAD and census, preparing all three sources strictly before
editing passed 62/62 rows. After editing, preferences passes 52/52 rows,
including its EH/funclet rows, plus all strings, floats and imports. The two
unchanged consumer objects retain their current receipts. Normal build,
class and frozen-source checks also pass. The enforced data audit reports
two pre-existing wrong-name findings for the local empty list and its guard
at RVAs A065E4/A065E8; restoring the original source and recompiling confirms
the same findings before and after. Data remains a shadow check in the hook.

The same current-object legacy link preview changes 0/3 to 2/3 units, and
0 to 308 linked bytes (insert 222, remove 86). This is a legacy preview gain;
strict receipts prove self bytes, not closed-strict linkage. Preferences
retains independent tree allocator, creation, erase and map blockers.

The verified BFME1 reference remains 64d369b90170. Its linking fixes were
reviewed earlier in this session; this local STLport provider conflict is
established from BFME2's own byte checks and census, not a donor layout claim.
