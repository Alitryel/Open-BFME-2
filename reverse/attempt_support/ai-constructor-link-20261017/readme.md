# AIUpdateInterface constructor linkage

Base: 456d5494, including the verified 984-byte AIUpdateInterface constructor
at 0x0026E9BD. BFME1 reference reviewed: 5bb8ca80. Its Transport/Siege ctor
units still use the same placeholder base names and offer no ready linking
repair; the BFME2 native calls and newly rowed provider establish the change.

Five caller units still referenced three unprovided constructor names:
Rva0026E9BDBase, TransportAIUpdateBase and SiegeAIUpdateBase. All pins and the
byte-verified call sites identify the same 0x0026E9BD body, whose class is now
proven AIUpdateInterface by its native/WB identity. Rename these private base
views and their initializers in Animal, AssaultTransport, DeployStyle,
Transport and Siege. No aliases or pins are added.

DeployStyle already had a second AIUpdateInterface view for command/turret
methods. Merge those declarations into the renamed base. Its declared virtual
member supplies the primary vptr in place of the old explicit pointer field;
novtable on the partial base and derived views prevents synthetic vtable
emission/stores. The five explicit native stores and all field offsets remain
byte-exact. Secondary-interface command calls retain their original +0x20
this adjustment.

The reference AIUpdate.cpp also defined an incompatible Zero Hour constructor
with exactly the real provider's name. Remove that obsolete body; its nine
independent ledger rows remain exact. The constructor now has one definition
in the tested units, from AIUpdateInterfaceCtor.cpp.

## Proof and limits

Normal byte gates: 13/13 rows across the new provider and five callers before
the edit; 12/12 caller rows after; all 9/9 reference-unit rows after removal.
All four EH-bearing rows are EXACT, with no baseline or missing object.
Strict new-COMDAT admission passes for all seven units; the caller placement
rescan reports no new body or pin.

MSVC 7.1 partial-link test uses the seven explicitly verified objects. It
suppresses only unrelated unresolved dependencies (/FORCE:UNRESOLVED), never
multiple definitions. Before: LNK2005 for the two real-name constructor
bodies and five unresolved calls under the placeholder names; no image.
After: no constructor diagnostic or duplicate-definition error; link exit 0
and a fresh map naming the 984-byte provider as sole constructor owner.
scoped-link.json preserves the actual diagnostics and selected map entry.
This is a scoped constructor-resolution proof, not a runnable game or a
whole-project LINKED-byte measurement.

The published census (2026-10-17 02:26 at fb06805bf5) predates the new provider.
The guarded --current-ledger preview was attempted; after preparing its five
missing upstream objects it still refused 10,574 providers lacking strict
compiler evidence. No check was weakened, index invented or census record
rewritten, and no global LINKED-byte gain is claimed. The complete original
objects, commands and logs remain in ignored build/local-macos/ai-constructor-link/.

Horde and SupplyTruck have further placeholder-base views with independent
cleanup/vtable obligations; this change does not assert their reconciliation.
