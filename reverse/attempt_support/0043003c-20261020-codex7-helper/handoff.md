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
