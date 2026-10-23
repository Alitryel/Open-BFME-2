# Sequential script constructor ownership

BFME2 7a2d918535; frozen census 03035cf02c (2026-10-20 22:09).
ScriptEngineDoXfer's inline Rva0020479E constructor is the first COMDAT
selected in the index. It differs from retail and prevents ScriptEngine.cpp
(1,338 B), TeamUpdateGenericScripts (531 B), ScriptActions_sequentialScript
(476 B) and ScriptEngineExecuteSequentialScript (357 B) from linking.
The existing 43-byte owner is Common/Rva0020479ECtor.cpp. The DoXfer unit
itself retains many independent blockers, so no gain is claimed for it.

One trial: keep the body visible using dllimport forceinline, as in the
verified particle ownership repair. The normal byte gate refuses before
comparing parent rows because the outline suppression renumbers its funclets:

$L19707 does not hold this funclet and 4 bodies in the parent's group match it
equally ($L19697, $L19696, $L19695, $L19694). Byte evidence cannot tell them
apart, so the gate will not pick one — the row needs a body it can name on
its own.

This is a false-reject lead, not proof of the whole source's byte identity.
Do not work around the naming gate; tooling needs to reproduce it and use
an authenticated parent EH graph if that disambiguates these identical
cleanups. Trial restored and claims released. No rule or ledger change.
The one-line candidate patch is retained to reproduce it. Inputs unchanged
from the existing donor pointer 68c5ce2789; flags are source's recorded
/O1 /EHs /arch:SSE /G7 and STLport settings.
