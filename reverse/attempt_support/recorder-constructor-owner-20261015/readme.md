# Recorder constructor owner binding

Base: 96ac53a1b0993d919d87987ddb112724717f3c16.

RecorderClass::appendNextCommand at 0x0037B7F6 now allocates the existing
0x24-byte Rva0030F47A view and invokes its matched constructor at 0x0030F47A.
The former GameMessage constructor spelling resolved to MessageStream.cpp's
nonmatching donor definition. The same owner/view is already used by
NetGameCommandMsg::constructGameMessage in Rva004D68C6Create.cpp. Retail's
allocation, call argument, and constructor accesses support this binding;
the address-derived owner retains its existing identity uncertainty.

Only Recorder.cpp changes. No new body, pin, alias, data name, compiler flag,
header, or ledger row is introduced.

## Verification

- Strict preparation of Recorder and Rva0030F47ACtor: 17/17 matched rows,
  one data row, 41 string literals, 15 empty references and 29 named imports.
- EH: six exact rows, none baselined or missing.
- Converged data: eight addresses, no second names or unjudged rows.
- Enforced data: two existing wrong-name findings, TheSkirmishGameInfo at
  0x00A02EF0 and g_Rva00A02D86 at 0x00A02D86. A before/after comparison of
  data_check.object_facts on the saved and current objects proves every data
  binding and defined data name unchanged, with no unreadable rows.
- New-variant admission, class gate, declared definitions and CSV check pass.
- Placement rescan: zero bodies and zero pins.

The published index is 2026-10-15 17:25 at a18a88030a, SHA256
8e47978c9983d4368203d2032651f8f62b576fc1203db31acf27351f84dbc95c.
Both local preview phases refresh the same four strictly current sources:
Recorder.cpp, Rva0030F47ACtor.cpp, VectorDeletingDtorsV07.cpp and System/Xfer.cpp.
Refreshing those unchanged Xfer providers removes the stale census Xfer
selection finding before the edit. This repair removes only the remaining
GameMessage constructor finding. Recorder's local prediction is 0 -> 5,939
nonpadding linked bytes; authored-byte growth is zero. The two Xfer provider
units retain unrelated findings. This is not whole-program closure or a new
census. The saved index and committed status tables are unchanged.

Snapshots and paired data/link results are in ignored
build/recorder-owner-20261015. The adjacent JSON files retain the measurements.

BFME1 donor repair d003077f0b7ce97622adb7a53f1fe76653433c5c was reviewed:
binding an existing matched provider applies here, without importing its
addresses, layouts or source. Official BFME1 master was fetched at ba629d9d;
the clean checkout/gitlink remains f76203cb023f923b97cd8687679ea29ef121d875.
No new reference inputs were used or freshness success recorded; advancing
the donor still requires the separate comparative full verification.
