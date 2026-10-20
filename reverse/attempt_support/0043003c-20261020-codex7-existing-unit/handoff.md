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


## Default-map constructor completed

The typed default hash_map constructor also belongs in W5. Keeping the typed
table constructor visible there produces exactly31B at43001D, whose complete
all-owner fold proof passes (map-constructor-fold-final.json). The typed table
constructor remains exactly64B with its final proof in constructor-fold-final.json.
Both have no unresolved bytes or relocations; all5 rows in W5 pass together.
The typed table destructor is declaration-only here: SelectionIDMapDestructor.cpp
owns its independently verified /GX57B provider. Without that declaration the
map instantiation emits a wrong /EHsc destructor, so that trial was rejected.
The final link preview returns to the four pre-existing provider conflicts and
the stale-census initializer issue, with no additional destructor conflict
(map-w5-link-final.txt). link_check --new-variants and undeclared-definition
checks pass. No complete LINKED receipt is claimed.

The alternate W4 placement, declaring the typed table constructor before
instantiating only hash_map<int,bool>::hash_map(), produces39B instead of31B.
Adding __declspec(nothrow) or throw() to that declaration still produces39B.
Those three visibility/contract trials are disproved for this wrapper; the W4
production file is restored. map-contract-results.json records those controls
and the successful W5 visible-body trial. This is separate from the previous
base/vector constructor contract factorials; none of those were repeated.

Fresh read-only isolated compilation of the unchanged parent bank has4054B,
184 relocations, zero structural regions and two operand differences (five
raw bytes C6B..C6F). Extent and jump-table checks return no problems. Most
usefully, compile_function now has unresolved=[] and concrete=4054: all native
callee bindings are available. See parent-raw-diff.json, parent-extent.json and
parent-resolved.json. No source variant was tried, and the parent bank and
claim owned by yasinschroeder-claudeb3 were left untouched. The remaining
comparison is saved/requested group operand selection, as documented earlier.

These two substantive constructor bindings are separate verified commits.
Their95 retail bytes were already covered by opaque owners, so authored
unique-byte credit is zero. Publishing is delegated to the mandated runner
batch mechanism; retained verified claims settle only when origin holds the
rows. No blocked or abandoned claim remains from this session.
