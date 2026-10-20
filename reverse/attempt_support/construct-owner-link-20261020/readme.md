# Constructor helper link repairs

At BFME2 9ff5576d09, using published retail-truth-2 index 5366c4f808
(2026-10-20 12:21). Current-object paired previews establish **+555 legacy
linked matched bytes**, not a closed-strict link-cycle result. Strict reusable
receipts verify the touched sources and both vector providers; no global
census/status files were regenerated.

| Unit suffix | Own bytes before | Own bytes after |
| --- | ---: | ---: |
| stlport_vector_rva00287f76_overflow | 0 | 184 |
| stlport_vector_rva00336aec_overflow | 0 | 189 |
| RvaTreeMInsertGenP12pod0016DBC0 | 0 | 182 |
| RvaMapIndexGenP12pod00928690 | 0 | 0 |
| RvaTreeInsertUniqueGenP12pod009282C0 | 0 | 0 |

The first vector's opaque eight-byte slot has a native six-byte copy, already
rowed as Rva002861B0Copy at 002861B0/25. The second's 36-byte slot has a
nontrivial copy wrapper Rva00333295Construct at 00333295/18. Target REL32s
and existing pins establish these destinations independently of payload type.
Imported-inline STL construction specializations delegate to those real
owners without emitting incorrect implicit copies. Providers and consumers
are checked together (43 unchanged provider bytes plus 373 newly linked).
These opaque stride types are not claimed to be original game identities.

The tree's pinned helper at 0016CC80/35 null-checks and copies four words
individually. The first three belong to its established three-int key and the
fourth is the mapped int. An explicit memberwise key copy reproduces the
complete helper. Its emitted copy and both competing providers must agree;
changing only the 182-byte unit still leaves wrong_selected. Therefore the
same key constructor in MapIndex and hinted InsertUnique is a verified
prerequisite for linking the 182-byte unit. Their own remaining blockers are
hinted-insert duplicate/wrong helpers, tree allocation shape and the pair-key
hash clear. No linkage gain is claimed for those two providers.

All eight touched ledger bodies pass build.sh (2 vector, 1 tree, 5 in tree
providers); byte extents and references remain exact. Both rowed vector
providers also pass strict current-object preparation. find_declared_unmatched
passes all five changed units. No new rows, pins, aliases, baselines or verifier
edits. The unchanged code coverage is expected for this linking lane.

Current donor pointer 92f6bbe8e1 was reviewed by the existing verified reference
handoff; the imported-inline owner-binding approach follows the established
BFME1/BFME2 helper repairs. Slot semantics above are target facts; retained
opaque type labels are structural views, not donor identity claims.
