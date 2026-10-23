# N-patch side hash constructor reconciliation

The renderer's private SideIndexInfo default constructor left all three fields
uninitialized, unlike the byte-matched constructor in meshmdl_sidehash.cpp at
0x00171AD0 (15 B). Use that owner's zero initialization. The Entry constructor
at 0x00171E50 (16 B) and Re_Hash at 0x00172600 (476 B) then also match their
retail copies. No other SideIndexInfo definitions or indexed losing consumers
exist in Code/. This repairs a target-proven constructor difference rather than
changing hash-table layout or suppressing a helper.

Acceptance: ./build.sh on MeshModelInitNPatch.cpp passes 1/1, preserving the
663 B parent at 0x00172F90. link_check.py before/after changes from three losing
COMDATs to LINKS, +663 B in the legacy preview against published census 5366c4f808
(2026-10-20 12:21). paired.json substitutes only this unit's before/after objects
against that same index and records exactly three changed COMDATs, no removed
or added ones. --prepare-current verifies a reusable self-strict receipt. No
closed-strict gain is measured or claimed.

Donor reviewed: Open-BFME-1 checkout 92f6bbe8e1dcdb46b5d27da0674313efc822b790;
no matching NPatch/SideIndex/sidehash linking repair in its available history.
The zero initialization follows BFME 2's matched owner, not donor byte identity.
