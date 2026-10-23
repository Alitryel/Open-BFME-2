# ScoredKill cleanup identity: +223 B in the legacy preview

BFME2 base b8feb98731 with prior unpublished STL ownership repair; published
index 5366c4f808, retail-truth-2. Paired objects refresh the same four provider
slots against that frozen index. Parser 0x414F85 plus its EH handler changes
from 0 to 223 linked bytes. Constructor stays 124 B linked; deleting destructor
stays 28 B linked. The 85 B destructor unit remains blocked by its pre-existing
BfmeAssignRecord44 vector/_Destroy copies. No closed-strict, census, link.exe
placement or authored-C++ gain is claimed. All four current objects have
self-strict reusable receipts; all seven function rows byte-verify, including
three EH handlers. One datum and string/import/float gates pass.

Target evidence, independent of donor names: the parser constructs its 48 B
stack temporary with 0x4148C0, and its cleanup calls 0x414932. Those existing
constructor/destructor implementations manage the same offsets (name +4,
member +0x14, vector +0x1C). The constructor and data ledger bind the object's
four-slot table to Rva004147CF at 0x83A09C. The old destructor-only opaque name
Rva00414932 represented this same lifetime under another class. Retain the
constructor's neutral name rather than assert a recovered original class name.
Rename its destructor, EH handler and deleting-destructor rows coherently;
no pin, alias or extra address is introduced.

The parser's artificial inheritance/inline cleanup is replaced by a direct
virtual-destructor declaration. The constructor declares that destructor,
preventing a competing implicit definition. The deleting-destructor emitter
inherits the existing Snapshot declaration so its table has the same four
slots as the constructor (one-slot emitter would regress its 28 linked bytes).
The real destructor retains novtable and exactly its original executable body.
The constructor's BfmeE16 and destructor's BfmeAssignRecord44 element views
remain unreconciled; this repair makes no claim to fix those separate blockers.

Prior attempt log 65322 and this session's import-forceinline trial establish
that suppressing inline cleanup alone leaves an unresolved EH import. Unifying
the actual provider identity addresses that cause without an import workaround.
Donor review reused verified BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790 and
its b0af542b7 ownership repair as a method lead only. Layout, slots, addresses
and lifetime identity above are BFME2 evidence; no donor body was transferred.

Checks: scoped build 7/7; link_check on all four providers before/after;
link_check --prepare-current on all four; check_csv; frozen-source checks.
paired.json records current/before source and object hashes, index hash,
blockers and receipts. No shared header, verifier or maintainer-only runner
was changed or started.
