# Preparation recovery, 2026-10-18

Recovered the retained commits 6ddf0b5863 and cfd04099f5 from preparation
backup refs/runner/preparation/1792336890292190708. Neither rebase was aborted
and no commit was skipped. The stash 83707d0a935fce08c2fb84a76b293b721e53e323
has no tracked delta: all ten saved untracked dumps and sweep artifacts were
restored byte-for-byte. The stash and backup ref remain intact.

During recovery upstream independently landed all three linking outcomes:

- 2defa89ff5 keeps unsigned vector stores inline, already covering 185 B.
- f2f9f1e333 binds Rva0056A3FF's push_back to its retail owner, covering 171 B
  without the saved attempt's now-redundant growth declaration.
- bc019a9f4e switches Rva00359290Dtor.cpp from /EHsc to /EHs, covering 165 B.

Both vector conflicts keep the upstream implementation. The empty-map source
change is removed in the recovery follow-up: with current /EHs flags, paired
ordinary link_check results both predict the same 165 B linked (published
census c2c5ac8c27, 2026-10-18 11:36). The upstream-only source passes all four
byte rows; the saved-declaration source passed the outgoing gate too. Current
legacy incremental gain over these upstream repairs is therefore **0 B**.
The historical proof.json files retain their original baseline and claims;
they are evidence of the saved attempts, not current coverage measurements.
No closed-strict gain or new census measurement is claimed.

Before the second upstream sync, both original paired proof scripts passed
again with strict-current receipts; all retained sections and reachable kept
providers were unchanged. The later outgoing hook passed 24/24 byte rows,
six exact EH graphs and converged data checks, but the dry-run push itself
was rejected because master moved. A fresh final dry run is required after
this bookkeeping commit and sync.

Ignored detailed logs and the removed declaration's source backup are under
build/recovery-*. No new tasks were drawn during preparation recovery.
