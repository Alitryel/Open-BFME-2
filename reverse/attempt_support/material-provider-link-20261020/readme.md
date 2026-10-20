Materials provider declaration repair, 2026-10-20

BfmeConv1137InstallMaterials declared StringClass::Get_String as returning char *,
although its existing verified 00610B00 provider returns void. Correct that
local declaration. The unchanged constructor now calls the provider under its
actual symbol and agrees with the retail constructor owner at 00065F34.
The same unit still used g_00DFE1E4 after Rva0027070C renamed the definition to
TheCloudEffectManager. Use the provider's name and existing Rva0027070CGlobal
pointer type at all twelve accesses. The field views and casts remain as before.
No new datum, layout, pin or alias. Source evidence and retail byte gates, not
the stale data-ledger spelling, establish the current provider identity.

Paired legacy preview on published e7a7769fe5, 2026-10-20 18:36:
materials 0 -> 10,934 nonpadding matched bytes. Providers remain 74 + 39 + 389
bytes clean, no credit taken. All retained COMDAT instruction bytes are
unchanged. Only two COMDAT relocation digests change: the constructor's one
Get_String reference and Install_Materials' twelve cloud-global references.
All three provider whole objects are unchanged. See proof.json and measurement.

Normal after byte gate 2/2 rows. Strict reusable before/after preparations
7/7 across all four units; five empty string references, 31 compiler floats,
zero named imports. New-variants, class gate, declared definitions, enforced
converged-data check (10 addresses, zero second names) and diff check pass.
Self-strict receipts plus legacy-index preview only; no closed-strict closure,
new census or executable result claimed. Authored C++ bytes +0.

The blocking names are unique to this unit; source sweep finds no remaining
char *Get_String(int,bool) or g_00DFE1E4 consumer. seglinerenderer's separate
constructor conflict has other causes and is not covered. Donor review stays
at BFME1 4483e88da1c2, as recorded in special-ability-frame-global-link-20261020;
this repair uses BFME2's byte-proven providers without importing donor layouts.
t=7 model=gpt-6.1-sol.
