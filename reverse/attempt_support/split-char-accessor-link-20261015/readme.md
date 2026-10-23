# Qualified-name splitter accessor: register-summary blocker

Source base 4b7e7091c4. Consumer GameLogic/Rva00194810Split_Rva0032abda.cpp is the 184-byte function at RVA 0x0032ABDA; provider WWLib/string_base_inline.cpp owns the public StringBase<char>::getCharAt at RVA 0x00035720 (23 bytes). Native REL32 operand +44 in the splitter reaches that provider. Existing private-spelling pin records the same address. No new identity, layout or pin is needed.

Before: strict bounded preparation of both files passes 53/53 rows, 12 empty-string references and 16 named imports. Local legacy link preview: provider LINKS (3011 bytes); splitter has wrong COMDAT and wrong-selected findings for its private 22-byte /O1 accessor. The caller was compiled with knowledge of that definition and reuses its buffer pointer after the const call.

Rejected trial 1 made getCharAt public and declaration-only to call the canonical provider. It removed the wrong helper but made the call opaque, so the compiler stopped caching the buffer pointer: registers and later reads changed, failing the splitter byte gate. Rejected trial 2 explicitly kept a per-iteration header snapshot and reused it after the call; the compiler changed register assignment and branch order, also failing the byte gate. These are ordinary mismatches, not false rejects.

Two careful builds exhausted this seat's attempt allowance. Original source restored; file claims for consumer/provider released. No pragma, alias, pin, baseline, ledger, shared-header or Code change retained. No verified gain or new C++ bytes claimed. Scratch original sources/objects/receipts, both rejected build outputs and the second source trial remain under build/split-char-accessor-link-20261015. Do not repeat declaration-only or explicit-snapshot trials without new compiler-summary evidence. The earlier pair-producer repair remains intact.

Measurement index: 19a2565407 dated 2026-10-15 09:33, underlying census 5986a99448 dated 2026-10-15 04:52; SHA256 a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3. This is a legacy local preview with self-strict preparation of the explicit cohort; no closed-strict/full-link claim.
