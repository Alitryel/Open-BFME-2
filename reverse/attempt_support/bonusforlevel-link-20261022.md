BonusForLevel parser link repair, 2026-10-22
=========================================

Inputs: BFME2 f01c130123; retained verified BFME1 37c3022de1. Published
census ae3b3e68e2, retail-truth-4. No full link cycle or census run.

Rva00417FF0Finish.cpp failed only on undefined g_00C3A6C8 and g_00CFE2FC.
Target evidence: VA 00C3A6C8 contains the complete diagnostic "Two BonusForLevel
entries with duplicate MinLevel of %d" followed by NUL. VA 00CFE2FC is the
existing compiler-owned __TI1?AVINIException@@ ThrowInfo, independently
recorded in data_ledger.csv. Existing AIKindOfFromName.cpp and other parsers
use its real C-linkage compiler name. No donor behavior or layout change.

Use the complete string literal and the real ThrowInfo declaration, removing
two unresolved address-named extern declarations. No new data definition,
alias, pin, ledger row, baseline change, or authored C++ byte growth.

Before and after: link_check.py --prepare-current passes 2/2 matched rows
with strict reusable receipts. ./build.sh after passes 2/2, one string
literal, and float/import checks. Same-index current-object link_check.py
changes from two unresolved names, 0/132 B linked, to LINKS, 132/132 B.
This is a legacy link preview using self-strict objects; no closed-strict or
runtime gain is claimed. Scratch receipts/logs: build/link-seat-20261022e/
bonus-{before,after}-{strict,link}.log and bonus-after-byte.log.

Other session handoffs in this batch record restored, unlanded string-hash
and MultiByteToWideCharSingleLine source trials. They contribute zero gain.
