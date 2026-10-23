The size-only Rva00153A27Element view made STLport emit a word-copy _Construct
at the existing folded pin 0x004F6B7B. Retail instead null-checks the destination
and calls the incrementing reference-handle copy Rva00468520::set at 0x004F62FE.
Both target bodies already have matched, named owners. This repairs the concrete
prerequisite recorded by the prior vector-copy attempts, without adding a pin,
identity, alias, row, or another address for the folded helper.

An explicit nothrow _Construct specialization performs the target's operation
through the existing Rva00468520 view. pin_admission.fold_proof_problems proves
its complete 18-byte body and every owner relocation at 0x004F6B7B. The original
three vector constructors remain byte-exact. The other two element helpers stay
declaration-only and bind to their established providers. The old POD explanation
was incorrect for this reference handle; the required property is nothrow copy.
Target bytes, relocations and existing owners establish this correction. No new
donor semantics or original class identity is inferred. BFME1 linking history
was reviewed at 37c3022de1ab944c7ffe536440d637dc8199091c.

Paired legacy previews use the same published e20daa4e78 index and three explicit
providers: 44 -> 251 nonpadding matched bytes, +207 in the vector-copy unit.
The original object is recompiled and measured alongside the final object, so
this is a source-change gain rather than merely a stale census difference.
The existing set and init providers remain linked. All three explicit sources
pass strict reusable receipt preparation and normal byte gates (5/5 rows).
find_declared_unmatched and new-COMDAT-variant admission pass. proof.json records
the paired findings, object and index hashes, and complete fold receipt.
This is self-strict byte preparation and a legacy preview gain; closed-strict
closure and a full link cycle were not measured.

The push_back and insert-overflow families also use this helper but retain
independent element/provider blockers. No linked-byte gain is claimed for them.
