Constructor/filter linking deferrals, 2026-10-20, index e7a7769fe5

BezierProjectileBehaviorCtor and BattlePlanUpdateConstructor: baselines pass
3/3 rows total. Marking their out-of-line UpdateModule view novtable preserves
all rows but leaves the derived UpdateModule-subobject vtable mismatch and
undefined derived slot00. No linked gain, both sources restored. The dtor
units prove the views differ: BezierProjectileBehaviorDtor has two full
secondary interfaces (6 and 2 slots) and three named overrides; its constructor
has two one-slot placeholder interfaces and slot00. BattlePlan's dtor has a
different +20 base, and its primary view emits only the dtor while the ctor
appends slot00. Removing actual slots merely to match the first incomplete
copy would not establish retail vtable correctness. Needs a class contract
reconciling the ctor/dtor/interface views and retail tables first.

AITargetHeuristicBaseDefense: baseline strict3/3, legacy0/551B because its
implicit Rva00260F1BFilter dtor differs from PartitionFilterAllowSlots' first
copy (no retail address). A declaration-only virtual dtor changes the parent
bytes (1/3 fails); visible import-forceinline empty body preserves3/3 and
renumbers funclet label5202->5197, but leaves an actual unresolved imported
dtor reference and a differing deleting-dtor copy. Source restored; no gain.
Patch is diagnostic only. Further repair needs the real cleanup/provider,
not suppressing the EH reference. No pin/alias/ledger change attempted.

BFME1 review remains4483e88da1c2; target class evidence is the existing BFME2
constructor/dtor units and matched retail references. t=12min model=gpt-6.1-sol.
