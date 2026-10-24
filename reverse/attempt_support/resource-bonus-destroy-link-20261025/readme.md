# Use the resource-bonus record's actual range cleanup

The existing parser constructs a 24-byte bonus record through 413F8B, parses
through 414081, appends through 414258 and destroys its local through 22CD2A.
Its vector's emitted clear worker at 414148 instead referenced an undefined
_Destroy specialization. The existing real typed 25-byte range cleanup at
22D941 already destroys those same records through the same 59-byte destructor.

Expose a TU-local forced-inline _Destroy overload before the vector template
is parsed. It passes the two existing range endpoints to Rva0022D941Destroy
using the record view that the parser already uses for stack destruction.
Remove the obsolete declaration-only specialization. No new pin, alias,
owner row, header, compiler flag or name is introduced. The actual underlying
application record type remains unknown; its shared 24-byte lifetime follows
the target constructor/parser/vector/destructor chain, not name similarity.

The native 30-byte clear worker independently calls 22D941, then the real
17-byte game allocator free at 30830. Both native destinations are decoded
and its entire body is reconstructed exactly with those two real owners.
The latter is the _free row in GameMemoryFree.cpp, not the different CRT
import thunk candidate. The new overload has a discardable static COMDAT
copy and no runtime references; the only reference is removed debug metadata.
External defined names remain unchanged.

Reference STLport 4.5.3 supplies vector destruction structure. BFME1 pointer
0bf534ea7ccde110c456edb9cd2dd5dae823c953 is already verified and current.
Prior attempt 83538 repaired the same typed range in the push-back collector.
Prior 82700 refused moving the overflow here because its clear binding was
wrong. This repairs that binding directly and changes no ownership.

All four ordinary owned bodies and every relocation are identical between
fresh original and production objects. The ten-byte EH stub has identical
raw bytes and a renumbered compiler FuncInfo relocation; the full parent
exception graph is EXACT. Normal gates pass all 6 consumer/provider rows
and the diagnostic string. The frozen-file check and strict current consumer
receipt pass. A new placement scan serves no bodies or pins.

Paired previews hold the provider at 25 linked bytes and change the parser
unit from zero to 260. This is 260 existing bytes predicted linkable and
zero new C++ recovery, not a new census or executable smoke test.
