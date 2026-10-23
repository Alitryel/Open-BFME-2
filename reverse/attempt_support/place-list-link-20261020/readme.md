Placement translator cleanup link deferral, 2026-10-20

At 22b2279158, PlaceEventTranslator's 1719-byte unit has three legacy blockers:
Drawable-list base ctor, node creator, and __node_alloc<true,0>::allocate.
Baseline strict preparation passes all three ledger rows. Retail providers
239BB0 and 239BD8 already exist and use the established 12-byte pool DBA5E0.

Two failed normal byte gates, then original source restored:
1. Declaration-only ctor and node-creator specializations: parent local stack
slots change, code grows, cleanup label/pin also fails (2/3 rows).
2. Visible noinline pool bodies copied from the already matching sibling
InGameUIGetAllSelectedLocalDrawables: parent stays 1701B, frame74, but starts
changing local slots at +25C (ebp-1C becomes -20). 1/3 rows fails; EH funclet
rows pass. Patch and first mismatch are retained. Do not publish this trial.

The canonical GameLogic-header ABI trials previously encountered the same
sensitive parent-local allocation; no header or ABI changed here. Further work
needs a caller-local lifetime/codegen repair preserving every row together with
the pool providers, rather than removing more helpers blindly. No linked bytes
gained. BFME1 review remains 4483e88da1c2; target provider evidence is BFME2's
existing rowed pool specializations. t=8min model=gpt-6.1-sol.
