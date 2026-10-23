SiegeEngineContain constructor virtual contract
=============================================

At e1add84209, the constructor view declared TransportContain's destructor
nonvirtual and omitted SiegeEngineContain's destructor. The matched destructor
unit declares both virtual. Its deleting destructor at 0x0047C2D6 and primary
retail table 0x00C470F8 independently establish the destructor slot. Reusing
those declarations fixes the constructor's conflicting primary vtable without
changing its layout, constructor body or EH actions. The related HordeSiege
constructor already declares its virtual destructors; no sweep edit is needed.

Paired link_check.py current-object previews against the published d08db10acb
index: before, only the destructor unit links (292 B); after, both units link
(485 B), gaining 193 nonpadding matched bytes. ./build.sh verifies the four
constructor/EH rows. --prepare-current verifies all 12 rows in the constructor
and destructor units with strict reusable receipts. This is a self-strict
current-object preview, not closed-strict link-closure evidence. No census,
full link cycle, provider rename, symbol pin or ledger change was made.
