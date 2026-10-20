# BFME 1 reference refresh: 0dc8a26a to 92f6bbe8

Paired verification used BFME 2 revision `9e42834dd0a7dcab4052951565b6687e02d65ab3` throughout. The previous committed pointer and the updated official upstream pointer both pass the full gate: 97,340/97,340 functions, 1,116 data rows, string/float/import references, DIR32 and pin consistency, module registry, source claims and no-op patch.

The complete EH result dictionaries are identical for all 11,798 rows: 11,761 exact, 35 bytes_differ and 2 retail_only. All 37 non-exact rows are pre-existing baseline entries; neither run has a missing object. Logs distinguish these baseline findings from update regressions.

The update contains nine donor C++ source changes and reference ledger/attempt records, with no header, toolchain, compiler flag or layout migration change. The updated full gate reused all 23,388 current BFME 2 objects. BFME 2 already contains the HLOD StringClass destructor repair. No BFME 2 production source or ledger row is changed here, and this refresh adds zero C++ exact bytes.

The BFME 1 byte scan, ranked and near queues, lifted-body listing, ZH compile/match/packet lanes and read-only placement trials for the nine changed donor units were refreshed. Placement output is lead evidence only; it establishes neither a donor identity nor a new recovery. ZH compile failures are discovery limitations, not failures of the paired BFME 2 gate; the ZH inputs did not change in this reference update. No candidate was claimed or imported from these scans.

`comparison.json` records exact revisions and changed paths. Before/after full-gate and EH logs, refreshed sweep summaries and changed-donor placement diagnostics accompany this record. Complete local discovery output remains in ignored `build/resume-oct20-*.log` files.
