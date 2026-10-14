# Direct scalar-delete dependency repair, 2026-10-14

Base BFME 2 revision: d9aa6e6b6a. Discovery index: cb660e4d97,
2026-10-13 04:02. Committed link_status measurement: 67e1365aa9,
2026-10-13 16:47. These are different inputs; current local previews below
are not a new census measurement.

## Supported donor repair and target evidence

Reviewed official BFME 1 master fea964f85433012ec0c95a44a8d88f77b4c29af5:
its direct global operator new/delete repair removes invented stand-ins and
unused pins. The scalar-delete repair is applicable to these five BFME 2
callers. Donor semantics motivate the direct spelling; target REL32s establish
the BFME 2 address independently. No donor layout or address was imported.
The verified submodule pointer remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85;
upstream pointer freshness verification remains outstanding as documented by
previous seats; this repair does not mark that check successful.

`target-calls.txt` records each native call displacement. All five target
RVA 0x0002FD60, the rowed global scalar delete in
Code/Libraries/Source/WWVegas/WWLib/mem_ops.cpp. Five invented declarations and
pins (bfmeFreeTWB/CDE/DMC/UD/VE) are removed. Existing aliases in other claimed
provider units are left for their owners. No new aliases or pins are added.

`object-comparison.txt` records exact before/after object-row bytes and
relocations: the five changed rows (257 bytes) have identical bytes and
identical relocation offsets/kinds, with only the called symbol replaced by
??3@YAXPAX@Z. The sixth, unchanged TWA row brings the affected unit coverage
to six rows / 316 retail bytes. There is no new authored C++ coverage.

## Acceptance and improvement

- ./build.sh on all five units: 6/6 rows and string/float/import gates pass.
- link_check.py --prepare-current on the five claimed units: strict reusable
  compiler receipts and ordinary gates pass (self byte evidence, not closed
  strict link evidence).
- pin_consistency.py --check: pass, no new/stale/baselined discrepancies.
- check_csv.py: pass, functions 88125, symbols 17114, data rows 396;
  symbol ledger shrank by five pins from 17119.
- Legacy link_check before and after: three of five consumers link, 155 bytes;
  two remain blocked, 161 bytes. No legacy linked-byte increase is claimed.
- The existing mem_ops provider links in the permitted local preview (80 bytes).
- No census, full link cycle, nightly, boot run or closed-strict measurement ran.

The verified improvement is five consumers referencing the real global delete
and five fewer invented pins, without byte or local-link regressions.

## Remaining blockers and rejected binding

BfmeConv1325.cpp still requires ?g_bfmeVftCTWA@@3PAPAXA. Its native TWA
DIR32 +0x24 stores VA 0x00CE30A8. Data ledger describes 12 bytes there:
00A65030 / 0043B810 / 0043B810. InlineDtorDeletingDtors2.cpp's current
Rva00665030 vtable emits only four bytes with a vector-deleting-destructor
relocation. Its 38 matched rows pass strict preparation, but that proves
neither the full table nor its other slots. A proposed address-based alias
passed the consumer byte gate but was reverted before landing. Supply a
complete target-supported class/table provider before reopening this repair.

BfmeThreeHundredFiftyFive.cpp still requires _bfmeVftUD, native DIR32 +0x5
VA 0x00BCEFAC. The data ledger associates that address with a 24-byte
VectorClass table. No table alias was attempted without whole-provider proof.
Both blockers are recorded through re_log.py. All five file claims are to be
released after the commit; the table-provider claim was already released.

## Final scope after concurrent upstream repair

Rebased onto ea402c81191d19ccdc93712fceb21019a43b2524. Upstream
147cfae2cb independently landed four of this batch's scalar-delete caller
repairs, plus the DMC array-delete repair and its provider cleanup. Conflicts
in BfmeConv1325 and BfmeConv730 were resolved by retaining upstream's sources.
The final commit changes only BfmeThreeHundredSixtyTwo.cpp: its 40-byte
?bfmeKillVE row calls the real scalar delete and the bfmeFreeVE pin is removed.
The original five-unit evidence above describes the session's starting base;
four repairs are already upstream and are not additional gains of this commit.

After rebase: the five-unit build gate passes 6/6 rows; the surviving VE unit
passes strict receipt preparation 1/1; pin consistency passes; the local legacy
preview still links three of five files / 155 bytes, with the same two table
blockers. See rebased-*.txt. No closed-strict gains or new authored C++ bytes
are claimed. Final incremental improvement: one real callee binding and one
fewer invented pin. The VE claim is released after the final commit.
