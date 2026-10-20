# SelectionTranslator constructor bindings in their existing units

Resume only the unfinished SelectionTranslator 0x0043003C prerequisites.
The parent is now claimed by another seat and was neither edited nor rebanked.
This seat claimed 0x0042FFC0 and 0x0043001D. Its previous score-0.98 parent
bank and the constructor-contracts handoff remain unchanged.

New hypothesis: the existing constructor unit already owns the required code
generation environment. Add the typed instantiation there, with its initializer
declared only, now that SelectionIDMap.cpp owns that exact initializer. This
avoids adding the optimized vector/base provider variants to a new unit.
The previous visibility/allocator/compiler factorials need not be repeated.

The typed hashtable<int,bool> constructor is exactly64B at42FFC0. Independent
fold_proof_problems returns no problems against every owner, with all bytes
and relocations resolved (constructor-fold.json). add_match --icf-owner admits
it alongside the existing opaque owner, and the unit passes4/4 byte rows.
The int/bool choice is structural inference from the parent key load and
Boolean value store; template algorithm/layout are STLport4.5.3 donor facts.
No pin, alias row, padding or replacement algorithm was introduced.

link_check --new-variants passes. Ordinary link_check before and after shows
the same four pre-existing allocator/proxy/base/vector provider conflicts,
with LINKED0->0; see link-before.txt and link-after.txt. The old census also
reports the newly bound initializer as unresolved, although its byte-verified
provider is already in SelectionIDMap.cpp. A joint provider/consumer preview
refuses because that new source is absent from the published census
(link-pair.txt); no full-link receipt is claimed. This is a verified
caller-binding improvement, not a claim that the unit now links. The existing
provider debt still needs a separate evidence-backed compiler/header repair.

Inputs: BFME2 e0e58cd834; BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790;
stock VC7.1 through Wine, original W5 O1/G7/EHsc settings. BFME1 freshness
update remains under codex5 shared lock; no freshness certification made here.
No maintainer-only runner was started.
