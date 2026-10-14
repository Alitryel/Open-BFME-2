# Logic frame-rate data verification

BFME 2 base `d8b5fc23ccc3066f1229bf65af6576ac5556a0d1`.
Local census index measurement `cb660e4d97`, 2026-10-13 04:02.
The committed link-status snapshot serves discovery only. No per-row data-back
artifact was available or used; census/index/status files are unchanged.

Add the missing four-byte verified data row for the existing sole definition
`BfmeLogicFramesPerSecond` in ColdGlobalDwordGetters.cpp. This source and its
consumers are unchanged. The canonical rename and consumer reconciliation
already landed in `de3584dbb23faa4d03ecb8a0e2db3f584a948a93`; their link gain
is not attributed to this row. The descriptive identifier is not claimed to
be an original debug symbol.

## Target and donor evidence

The existing data_ledger owner is `?BfmeLogicFramesPerSecond@@3HA` at RVA
`0x009BA4E4` (VA `0x00DBA4E4`). Retail getter `Rva004B879DGet` reads this
address. The existing canonical timing consumers establish its shared role.
The retail .data initializer is exactly `05 00 00 00`, not the later runtime
frame-rate value. The data gate independently proves compiler sizeof four,
allocation extent and all four initializer bytes, with no relocations.
There is no overlapping data row and no new symbol pin or second definition.

Reviewed BFME 1 repair `92a8d854746f059994f8ab370c133f3ba71eec24`:
consumers should bind an existing data_rows owner rather than invent a datum.
This is applicable as an ownership principle; its debug-cell identity,
layout and address are not BFME 2 evidence and none is imported. BFME 2 had
already reconciled the frame-rate consumers; this change makes their existing
owner independently byte-verifiable as data.

BFME 1 remains at the clean verified pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. The official freshness fetch
found newer upstream `30c4ca7346c098cc8755f7fd685a11f2d01f67fb`.
Comparative full old/new verification and pointer publication are outstanding;
no freshness success stamp is written and no newer donor inputs are imported.

## Acceptance and limits

- `data_rows.py --verify ColdGlobalDwordGetters.cpp`: the new row byte-verifies;
  matched retail data ownership increases by four bytes.
- Normal source gate: 38/38 matched function rows, one verified data row,
  zero string/float/import refs or verification skips.
- `link_check.py --prepare-current ColdGlobalDwordGetters.cpp`: accepts the
  explicit owner with a strict reusable compiler receipt and normal gates.
  This proves self currency, not closed-strict link closure.
- Enforced converged-data check: one source, eight protected addresses,
  zero second names and zero unjudged rows. CSV integrity, frozen-file,
  case-collision and diff checks pass.
- Before/after local legacy preview checks the owner and the cinematic-text
  consumer together. The owner contributes 511 bytes and the consumer 430.
  Their current combined linked bytes remain 941. The printed 511 -> 941
  compares with the old census, not this change. No incremental legacy or
  closed-strict linked-byte gain is claimed; authored C++ growth is zero.

The local repair queue and unresolved/COMDAT/address ranks were inspected.
Three ranked hardcoded-global leads yielded no name_globals dry-run edits.
The rehome preview again served the previously recorded neutral/loss candidate
at 0x004F6318; it is not retried without new evidence. The exploratory rehome
scan was stopped after that unchanged lead; no queue-exhaustion claim is made.
Broader class/COMDAT/provider debt, closed-strict closure and real link.exe
placement remain unmeasured. No maintainer-only census build, full link cycle,
nightly, boot or scheduler operation was started.
