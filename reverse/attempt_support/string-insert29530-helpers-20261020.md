# 29530: sibling helper closure, stack slot still missing

Native29530..297C6 is662 bytes, ret12. Whole existing bank, the104-byte
2A140 caller, vendor _string.c count/character insert and the complete newly
landed284D0 source were reviewed. The operation is the same STLport narrow
string insertion; char follows the donor/traits interface, not a separate
target proof of signedness. The existing address/class view remains tentative.

The bank now uses the exact POD dispatch definitions and the existing
address-derived callee spellings of the landed sibling. No new pin or alias is
added, and no stronger identity is claimed for those shared helpers. It emits
662 bytes with all calls resolved:45 differing byte positions,617/662 positional
agreement=0.93202416918429. Its first difference is frame6C versus native70 at+5;
the this home and following compiler homes are four bytes high. This improves
the previous bank's unresolved helper calls, not the missing-slot codegen wall.

Eighteen normal explain_mismatch controls were run. Two copy-chain contexts
crossed with declared/non-inline-visible/noinline/late-noinline char fill give
662/frame6C. A real inline fill gives682/frame70: correct homes but two expanded
fill calls. Inline+noinline declarations, including after the caller definition,
return662/frame6C. Hash-pinned vc71-sp1 and vc71-ddk-4035 reproduce the682/662
split with the same header/flags; no alternate compiler is selected for Code.
Two whole-caller controls merge the actual BfmeThreeHundredSix104-byte wrapper
before the insertion definition, with its real declarations and matching
pointer fields. They reproduce the same662/frame6C versus682/frame70 split.

No inert padding, equal-arm expression, pragma, assembly, Code edit or ledger
row was introduced. Preserve the ordinary inline declaration in the bank;
noinline does not reserve retail's missing word. Earlier body/type/permutation
attempts remain applicable. A new explanation for the reserved fill-local home
is needed before repeating those shapes.

Inputs, all eighteen ordinary build logs and results are in
build/string-insert29530-helpers-oct20/. Replay driver copies are retained
beside this note; they read the bank/sibling and use only explain_mismatch.py.
Time about6 minutes, model gpt-6.1-sol. Body claim released after banking.
