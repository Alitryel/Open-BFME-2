HordeContain::changeToFormation linking attempt, 2026-10-20

At BFME 2 44d0196f61 with the verified BFME 1 a2c8039e61 inputs, the current
811-byte body and its 8-byte cleanup pass self-strict preparation. The published
b73720bed9 index rejects two emitted STL copies: list-iterator inequality
(retail owner RVA 0x6CFE40) and Object-pointer find (call target RVA 0x29B694).

Two careful trials failed the ordinary byte gate. First, dllimport+forceinline
inequality and a declaration-only find reduced the parent stack allocation
from 0x74 to 0x70 and changed distance's loop and local allocation. Second,
dllimport+ordinary-inline inequality with the original find body retained and
an extern-template instantiation produced the same parent mismatch. The second
trial is preserved as trial.patch. These are diagnostic
linking trials, not a replacement for the verified reconstruction.

Restored the original source. Further work needs independent control of helper
emission while preserving MSVC 7.1's original inlining/escape decisions; no
class/layout or function-identity change is supported by this evidence. Flags:
/O1 /G7 /arch:SSE /MD /EHsc. No new symbol pins or verifier changes were tried.
