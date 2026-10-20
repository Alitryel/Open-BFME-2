Float-key tree identity and cleanup repair

Parent de33871f25. Same-unit legacy preview 0 -> 608 nonpadding bytes after
removing a false 166-byte claim and binding the remaining native cleanup.
No new C++ recovery bytes are claimed; the coverage correction is -166 bytes.

The 33C176 insert_unique row had the float-key Rva00568FE4 tree name. Its
own comparator is the verified 71-byte SSE float/word comparator at 56866A.
Native calls at 33C176+28 and +6C instead reach 33AD5C, a 73-byte bit-test
loop independently owned by SparseMatchFinderWeaponCompare17.cpp. These
are different algorithms, not ICF twins. comparator-proof.txt records both
complete bodies. Its 33C0E1 insertion worker also calls that bit comparator,
not the floating comparator used by the 568FE4 insertion worker. The old
pins redirected the two helper names despite their already-owned native
bodies. The row passed ordinary relocation resolution but failed retail truth
in the census. It is a false claim, not a false verifier rejection.

Retract the 166-byte row and its three pins; remove the unrowed hinted
insert_unique instantiation that emitted the false value-insert copy.
Preserve all ten independently anchored float-key family rows. The destructor
then differs from the earlier LargeGroupAudioSoundKeyPair.cpp provider only
in its allocator-free relocation name. Use that provider's established C++
throwing game-free declaration through the headers. All 56 bytes of the
destructor and its EH graph stay exact, and its kept copy now agrees.
No new alias, pin, data address, compiler override or hatch is introduced.

Donor review: BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790, STLport
inputs/vendor/stlport/stl/_tree.h/_tree.c, confirms generic tree insertion
and destruction structure only. It cannot establish a target key/comparator
identity. The target comparator bytes and existing named row establish the
identity conflict; the existing BFME2 provider establishes the cleanup route.

Acceptance: strict self 11/11 before (including the misleading pin-resolved
row), 10/10 after; normal byte/literal/import checks pass. EH1 EXACT,
declared definitions clean, converged data 0 second names, check_csv and
pin_consistency clean. Same published census 5366c4f808 (2026-10-20 12:21),
same-unit legacy preview 0 -> 608 bytes, LINKS. No closed-strict gain claim.

Follow-up: stlport_rb_tree_0033c646_insert.cpp explicitly documents using
float keys as a code-shape view while binding to the bit comparator. Its
449-byte hinted insertion and 149-byte worker need actual map/key identity
reconciliation; it is a separate two-row unit and was not edited here.
Do not rebuild it as another floating tree or manufacture new fold pins.
