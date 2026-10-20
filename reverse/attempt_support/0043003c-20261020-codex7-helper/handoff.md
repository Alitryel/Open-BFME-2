# SelectionTranslator free-helper prerequisite

Continue only parent0x0043003C; the retained score0.98 bank remains4054B,
184relocations,0structural changes and2operand differences (+C6B..+C6F).
Do not repeat the earlier comparison or constructor factorials.

New evidence resolves the apparent member/free ABI conflict at42F9DA.
WB SelectionTranslator calls12AA0A0 twice (at12A7E38 and12A9051), with
no ScriptActions receiver. Its61B helper reserves only the message-pointer
local and never saves ECX. WB ScriptActions::executeAction case506 calls
10194A0 at10254C7 after restoring its receiver. That separate66B function
saves ECX in its second local, but otherwise performs exactly the same
message0x3EC/Boolean true/UI slot110 sequence. Retail folds both into39B
at42F9DA. wb-free.txt and wb-member.txt preserve both bodies. The prior
receiver repair of the script member was correct; renaming it free would
have lost a distinct original function.

Added the free deselectAll beside the retained member in its existing TU.
The free name and purpose follow the SelectionXlat.cpp reference helper;
target WB proves the separate no-argument free ABI and its call relationships,
and retail proves the extra message emission absent from current donors.
This is a justified ICF row, not a new pin or address alias. Independent
whole-body fold proof against every owner is empty (helper-fold.json);
byte gate passes2/2 with all relocations resolved. link_check --new-variants,
find_declared_unmatched, check_csv and pin_consistency --check pass.

Fresh parent compilation still has exactly the original five raw comparison
bytes and passes extent/switch checks. Its two helper references now resolve;
only the hash_map<int,bool> default constructor remains unresolved. Its deeper
vector-base provider issue is documented in the prereqs/handoff.md.
BFME2 inputs ec2e83a034 plus the previously verified local prerequisite commits;
BFME1 checkout92f6bbe8e1dcdb46b5d27da0674313efc822b790. Freshness update
remains with the live codex5 shared lock; this seat did not certify it.

The typed bucket initializer is now independently admitted at148DDF/59B in
the existing SelectionIDMap.cpp unit. Its complete body and every relocation
pass fold proof against all owners (initializer-fold.json), and the unit's
9/9 rows plus new-variant and undeclared-definition checks pass together.
The end/insert wrappers use the established imported-inline idiom; reserve
and fill-insert are declaration-only canonical providers. No vector copy
is introduced. This is a zero-unique-byte prerequisite repair.

New constructor trials, beyond the old base-visibility factorial:
24 combinations hide the allocator-taking vector constructor (plain,
__declspec(nothrow), throw()) with four allocator-dtor visibility contracts
and /EHsc versus /GX. All keep the initializer59B exact but produce
65/69/73/77B callers. No64B variant. Another24 test the real STLport
_STLP_NO_TEMPLATE_CONVERSIONS and _STLP_NO_MEMBER_TEMPLATE_CLASSES
conversion paths with the same vector/dtor choices; same results. The new
argument lifetime/conversion path hypothesis is disproved. Reproduce using
ctor_visibility.py and ctor_conversion.py; outputs remain under build/.
All were isolated compiler_command trials, never shared-cache hand compiles.

The WB map metadata is misleading at this pair:12AA280 (ret16, four
arguments, inlined bucket construction) is the hashtable constructor, and
12AA320 (ret4, reserve then fill-insert then size zero) is its bucket
initializer. Automatic pairing calls the former hash_map and the latter
hashtable. Parent12A8207 calls the former with count100 plus three empty
function/allocator objects. Use the actual bodies and caller ABI, not the
automatically assigned metadata names, for further constructor analysis.

Six further controls keep the reference base-constructor body visible while
applying the established dllimport-inline suppression pattern directly to
_Vector_base: inline, forceinline and inline/noinline, each with ordinary
or forced-inline vector wrapping. All six trigger VC7.1 C1001 at msc1.cpp
line2701 on the explicit imported base-constructor specialization. This
pattern cannot supply the needed analysis/no-emission combination in this
compiler. ctor_base_import.py reproduces it; ctor-base-import-results.json
retains the diagnostic. This is a compiler failure, not a verifier false reject.

Session close preserves the unchanged best parent through re_log --stash
--score0.98. The parent and unresolved constructors42FFC0/43001D are released;
verified initializer/helper claims stay queued until publication. No more
parent comparison shape trials were repeated. Concrete next work is the
vector/base provider visibility prerequisite or a new evidence-backed source
shape for the two comparison operands.
