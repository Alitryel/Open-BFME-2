# POD allocation/copy ownership repair

Measured against published census 5366c4f808 (2026-10-20 12:21), with current objects for every touched unit and the reserve consumer. This is a legacy per-unit preview; it does not measure placed self-strict or closed-strict credit.

Whole-class instantiation in the broad EH profile emitted 100-byte allocation/copy helpers ahead of dedicated 45-byte no-EH owners. No assignment members for the five retained element views are rowed in that profile. Declaration-only assignment specializations stop those competing helpers. Dedicated providers now explicitly instantiate their rowed members, preserving the mutable/const Pod44 twin; Pod104 and Pod340 construction binds to existing rowed owners rather than competing trivial copies.

| Unit | Before | After |
|---|---:|---:|
| pod24 allocation/copy | 0 | 45 |
| pod44 allocation/copy (one ICF range) | 0 | 45 |
| pod104 allocation/copy and copy worker | 0 | 83 |
| pod172 allocation/copy | 0 | 45 |
| pod340 allocation/copy | 0 | 45 |
| StlportReserveRva004DA039 | 0 | 126 |
| broad POD vector unit | 0 | 0 |
| Total | 0 | 389 |

`./build.sh` and `link_check.py --prepare-current` pass all 158 rows in the six changed providers, with strict reusable receipts. `find_declared_unmatched.py` passes. The broad unit retains independent blockers; this repair does not claim its 7,281 bytes. Existing width-only element identities are unchanged.

Rejected trials: explicit specialization of the member-template allocation helper causes MSVC 7.1 C1001 at `_vector.c:95`; declaration of its unused assignment owner avoids that error. Forcing Pod104 construction inline changes its rowed 38-byte loop into inline block copies; ordinary declaration preserves the loop and correct owner. Pod28 still conflates PB-copy addresses 0x5411C8 and 0x215F38; Pod32/128 still select wrong construction owners. Their source trials were restored and logged separately.

Donor inputs remain the previously reviewed BFME 1 revision 92f6bbe8e1dcdb46b5d27da0674313efc822b790. This repair uses current target row/relocation evidence and the repository's existing STLport sources; no donor rescan was repeated.
