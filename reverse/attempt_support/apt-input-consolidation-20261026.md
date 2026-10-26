# AptInput TU consolidation audit — 2026-10-26

The fifth mechanical shard allocation approved
`Code/Libraries/Source/Apt/AptInput.cpp`. A fresh scoped
`name_lane.py consolidate` report passed `--check`; the TU map passed the
queue's `--check-tu`. `tu_skeleton.py --plan` approved 21 rows from eight
donors, including one mixed source. The unchanged merge dry run accepted three
donors and 11 rows:

- `Code/GameEngine/Source/Common/BfmeMeshHitTest1290.cpp` (`0x006F9CB0`)
- `Code/Libraries/Source/Apt/Rva006F9EF0Cluster.cpp` (`0x006F9EF0`)
- `Code/Libraries/Source/Apt/AptAnimationPoolBILValidate.cpp` (`0x006FA020`)

Four other donors were rejected without source changes: the `0x006F9FC0`
cluster would lose its `-O2` override; `0x006FA7E0` has missing members and
`m60`; `0x006FB910` and `0x006FB120` fail on `AptCIH` declarations. The
accepted merge was applied by `tu_skeleton.py`; it carried protected register
keys through its prescribed transfer, with hatch totals kept. No gate baseline,
data, identity, or header debt key is claimed retired.

## Verification

- `./build.sh AptInput.cpp` passed all 11 matched rows, byte checks, literals,
  float/import checks and the verified funclet pin.
- `find_declared_unmatched.py Code/Libraries/Source/Apt/AptInput.cpp` found no
  unmatched definitions; `eh_verify.py` reported exact EH.
- Staged `code_identity_gate.py` reported zero new shadow findings;
  `tu_ownership.py --staged` passed; `data_check.py --converged` found zero
  second names or unjudged rows; CSV and case-collision checks passed.
- Header queue inspection found no AptInput/donor header adoption requirement;
  the `AptInputSuffixAdvance.cpp` MS-header item is separate and remains queued.
- Active path consumers were searched across tools, hooks, workflows, source,
  docs, config and reverse controls. No active consumer refers to the three
  absorbed donor paths. Remaining hits are historical status/evidence,
  generated reports, or provenance comments in the destination.
- The merge removes three source files net and preserves the 11 verified rows
  in the approved TU. The pre-push `link_batch_audit.py` remains responsible
  for selected providers, lost bytes and input freshness across the outgoing
  source batch; no link gain is claimed here.
