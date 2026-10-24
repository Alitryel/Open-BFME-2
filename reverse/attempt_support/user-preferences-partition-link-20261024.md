# UserPreferences independent string-map ownership

BFME2 input bdcf20a6ce; frozen published census a9f880ad06, retail-truth-4.
BFME1 verified input 32774ab03393 remains fresh. Its independent
IgnorePreferences_getIgnores.cpp already separates the same reference loop;
this change retains BFME2's existing ABI, offsets, compiler settings and bodies.

The ordinary UserPreferences methods and IgnorePreferences constructor/dtor
operate on map<AsciiString,AsciiString>. Only getIgnores instantiates the
int-keyed map family. Move its definition and 12 template/EH rows unchanged
into UserPreferencesDeferredIgnores.cpp. Keep all 44 independent rows in
UserPreferences.cpp. No identities, pins, literals, or data values change.

Paired scoped current-object link_check.py UserPreferences.cpp changes from
0 to 2,288 linked authored bytes against the same census index. This is a
legacy preview, not a closed-strict result or new census measurement. The new
deferred unit has no census position and earns no gain. All 57 rows byte-match,
all 19 EH graphs are EXACT, and both units pass frozen-definition checks and
strict reusable receipt preparation through the normal byte gate.

Remaining blocker: reverse/attempt_support/map_int_asciistring_fake_family.md
and re_attempts.log's earlier 0x003B224D entry describe the conflicting 24-byte
value family using int/AsciiString names, plus the pair destructor variation.
The ownership change does not resolve those identities. Do not repeat the
previous insertion/copy guesses; reconcile the family under the naming rules.
