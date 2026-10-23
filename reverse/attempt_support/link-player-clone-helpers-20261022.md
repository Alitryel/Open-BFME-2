# Player clone relation-map helper trial

Base 25074ab48a; census e20daa4e78, BFME1 donor 37c3022de1ab.
PlayerCloneFrom.cpp has five matched rows (613 nonpadding bytes), legacy
preview 0 linked. Its int/Relationship hashtable begin differs from the rowed
68-byte provider at427195 in RelationMapXfer.cpp. Iterator skip-to-next has no
retail address and differs from the first kept copy in that same provider.
Current strict reusable preparation passed5/5 before editing.

Trial1: declaration-only explicit specializations of both helpers. Four EH
rows pass but cloneFrom changes604->609 bytes: iterator loop now keeps zero
in EDI and reloads the node from the stack instead of keeping the node in EDI.
This is a callee visibility/register-summary change, not a template name fix.

Trial2: dllimport/forceinline specializations using the existing STLport bodies
(_hashtable.h begin and _hashtable.c skip). Parent shape returns to retail,
but its hash_map<int,Relationship>::begin call is unresolved: the wrapper now
contains an imported hashtable begin call instead of the target provider body.
The byte gate therefore still refuses1/5. No link gain claimed.

Final diagnostic patch saved alongside this note. Production restored. Do not
repeat these declarations/imports unchanged; reconcile actual iterator helper
providers and preserve the caller summary plus direct begin binding. No pins,
ledger or baseline changes. Target identities/layout carried from existing
row evidence; helper facts established from current objects and census. t=7min.
