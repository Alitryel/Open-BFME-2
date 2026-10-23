# Lua events dispatcher provider binding

`ProcessEventsElement` at RVA 0x003371F4 (195 bytes) called the donor-address
placeholder `rva002E9590ParseScriptedEvent(BfmeLexEAN*)`, although the real
121-byte provider at 0x00336BE4 is already recovered as
`ProcessScriptedEvent(XmlNameSlotList*)`. Bind the declaration and direct call
to that provider, using the parser view already used by this dispatcher's
`finish` and `ProcessInternalEvent` calls. This does not establish the original
name of the parser class, change its layout, or add an alias or pin.

Native identity: at 0x00337264 the dispatcher pushes ESI (the unchanged parser
loaded from its first argument at 0x003371F6), copies EBX to ECX (engine saved
at 0x003371FA), and directly calls 0x00336BE4 at 0x00337267. The provider loads
that argument into EDI at 0x00336BEB, saves engine ECX at 0x00336BEE, calls
count/tag/name/finish on the unchanged parser, and ends with RET 4 at
0x00336C5A. There is no hidden result or receiver adjustment. The source
comments now distinguish BFME2 callee RVAs from donor RVAs.

This reopens prior attempt 77300 after its missing ObjectStatus prerequisite
landed: 0x00336EB0 (482 bytes), its EH handler, and the separate
`lua-predicate-link-20261020` repair are upstream work, not credited here.
The source remains the existing BFME1 donor port (original donor revision
6d943426); this repair uses the established BFME2 provider and native ABI.
Inputs for this verification are base 930dcce626 and BFME1 pin 4483e88da1c2.

Validation: frozen current before/after objects and compiler receipts for the
dispatcher plus ScriptedEvent, ObjectStatus, ModelCondition, and InternalEvent
providers. Normal build passes 11/11 rows; both EH graphs are EXACT. Frozen
replay is 11/11 before and after. The dispatcher's full raw 195 bytes are
identical, and its only relocation change is the intended REL32 name at
body offset 0x74. All four provider sources, objects and receipts are
identical between snapshots. Affected-unit placement finds 0 bodies/0 pins.
`proof.json` records hashes and row-level results.

Link accounting is deliberately limited. Against authenticated published
index 3f413ed3ff (2026-10-20 18:52), with the same current objects on both
sides, dispatcher unresolved references drop from two to one: the obsolete
scripted-event name is gone. The remaining ObjectStatus name has the exact
current provider, but that source is absent from this index's object universe;
ordinary refresh correctly does not add it. Its standalone object facts are
not a supported whole-universe closure check. No index was hand-extended.
The eligible four-source total is unchanged at 1,173 linked nonpadding bytes;
the out-of-index ObjectStatus unit is excluded. Claimed new recovery and
whole-unit linked gain are both zero. A future complete current-ledger check
can decide the dispatcher's 195-byte closure without attributing upstream
provider work to this change.

The old placeholder pin is retained; this patch changes only the caller and
this evidence/log. No flags, headers, layouts, metadata rows, or providers
change. t=20min model=Codex(runtime-model-not-exposed).
