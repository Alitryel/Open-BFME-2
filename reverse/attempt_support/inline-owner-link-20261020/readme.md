Inline owner reconciliation, 2026-10-20

Two rowed owners emitted strong symbols although their consumers also needed
visible copies: BfmeStringRecord00204A30 copy construction in ScriptEngineDoXfer,
and the 0x0029FCB4 science-vector getter in ControlBarPopupDescription. Give the
record constructor inline ownership; give the getter the same noinline inline
declaration as its consumer. Their actual code bodies are unchanged. This
preserves optimizer visibility in consumers and allows the linker to select one
matching COMDAT. No new identity, layout, address, pin or alias is introduced.
The target identities and bytes remain the existing ledger's claims; record
application identity remains unresolved.

Paired preview against published e7a7769fe5 (2026-10-20 18:36):
StringRecordInlineCopyBFME2 0 -> 3,465 nonpadding bytes;
ControlBarRappellerCount 0 -> 4,725; total +8,190. Each had only its duplicate
blocker before and no blockers after. Both consumers lose that duplicate but
retain unrelated blockers, itemized in proof.json; no bytes from them counted.
All retained COMDAT digests, covering bytes and relocation referents, are
unchanged in all four objects. Both consumers' whole-object hashes are unchanged.

Self-strict receipts prepared for all four units before and for the two edited
owners after. The paired result is a legacy-index preview, not a closed-strict
closure, fresh census or executable placement measurement. Authored bytes +0.

Acceptance: normal build of edited owners 109/109 rows; strict before gate
188/188 across owners+consumers; strict after gate 109/109; strings, float and
import checks pass; link_check before/after, new-variants, class_gate,
find_declared_unmatched, data_check --converged and git diff --check pass.

BFME1 donor revision 4483e88da1c2 reviewed for existing-provider ownership
repairs (a411b334c,3313189ad,c54305633), as documented in the accompanying
special-ability-frame-global-link-20261020 evidence. Here both visible copies
are already BFME2 code and byte proofs; no donor layout or address imported.
t=12 model=gpt-6.1-sol.
