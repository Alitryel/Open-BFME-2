# SlowDeath parser linkage, 2026-10-22

Inputs: BFME 2 9cd1f9be16; BFME 1 37c3022de1ab944c7ffe536440d637dc8199091c;
existing source flags /GX /MD /DNDEBUG, STLport malloc, no exceptions.
The current published census 08160bc2c9 with explicit current parser and
WeaponTemplateSetHeadRva0045D859 objects reports only two missing names in the
807-byte parser unit: TheSlowDeathPhaseNames and the by-value rva0045D859.
The callee already links 46 B under its explicit output-pointer declaration.

Retail phase table is VA DC9598, .data, 20 bytes:
BEE8D8 INITIAL; C42014 MIDPOINT; BEE8C8 FINAL; C42008 HIT_GROUND; zero.
BFME 1 SlowDeathBehavior.cpp at the recorded pointer agrees on these strings;
addresses/order/extent above were read independently from BFME 2 retail.
No data row landed because the combined repair could not byte-match.

Trial 1: declare the callee using its rowed explicit output argument, and use
an inline constructor from Rva000B6253 to initialize the guarded static directly.
This accidentally creates a user conversion at the later C-style reference cast
for rva000B3ED3: a second complement call and 0x50 frame appear. Rejected.
Trial 2: give that constructor a second tag argument so it cannot convert the
later reference. No extra complement call remains, but parent now saves EBX,
loads the allowed mask into EDI later, and changes registers/byte count.
See assembly.diff and trial.patch. 9/10 rows pass; parseDeathFlags 243 B fails.
The inline explicit-output wrapper loses the original by-value call's compiler
alias/return summary. Do not raise the row extent: retail is already bounded.

Both trials restored completely. A table-only definition yields zero linked
bytes, so it was not retained. A future ABI reconciliation must preserve the
original caller codegen while binding to the real callee; no alias or new pin
was added. Existing declaration-by-value pin remains unchanged. No independent
consumer of that spelling was found by a Code-wide search.
