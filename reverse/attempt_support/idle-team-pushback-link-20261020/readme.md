# AITeamBuilder Object-pointer push_back link blocker

Base 44f33aef2a, BFME1 01b84526fc8a43c9dea1cfe6abd0a6859b34eee5,
published index 5366c4f808. Baseline strict gate passes both rows, 402-byte
checkIdleTeams and 10-byte cleanup; whole-unit preview 0/407 nonpadding bytes.
Sole blocker is vector<Object*>::push_back; its rowed provider is 0x001F211B.

A declaration-only specialization changes the caller's instructions; trial1
contains the exact diff. Keeping the vendor push_back body as dllimport and
forceinline must occur after this unit's explicit _M_insert_overflow definition;
otherwise MSVC rejects its later specialization as already instantiated.
With correct ordering the caller still changes: the final command relocation
is at offset400 and needs404 bytes, beyond retail's402-byte extent. This is
not evidence that retail's proven extent should grow. No pin, extent change
or import thunk was added. The preserved candidate is diagnostic only.

Both visibility strategies fail caller-byte preservation. A further repair
needs evidence for inliner/register shape while retaining the custom overflow
body. Original source restored and reverified before releasing claims. No
linked-byte gain or closed-strict result is claimed.
