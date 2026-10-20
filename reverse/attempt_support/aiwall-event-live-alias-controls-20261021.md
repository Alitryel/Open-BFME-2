# Live-expression controls: AIWall and scripted event update

No production source, body, signature, layout, pin or gate was changed.
Both existing stronger banks remain untouched. All trials used separate
scratch files and normal explain_mismatch compilation, never hand cache writes.

AIWall helper004EACF5,197B: the latest joint canonical-coordinate bank reproduces
the four entry encoding-byte differences; the actual class-key mangling is
PBVCoord2D, matching the canonical header. Six fully used coordinate-difference
forms were tested: aggregate return by pointer/reference, output by
pointer/reference, and sharing the returned difference with endpoint-distance
evaluation. None improves;26..187 differing patched bytes, no unresolved symbols.
Some forms also change the private register convention. No padding, dead
locals, barriers, volatility or compiler settings were introduced. The earlier
r54 colour-cost investigation remains a separate uncompleted lead. Local
sources/results: build/aiwall-causal-oct21/ and live-math-results.json.

Scripted event updater000BD6C2,894B: retain the correct single loop increment
and test only live aliases of the node/payload inside the particle arm:
local node pointer, const node pointer, const payload reference, inlined
node-reference getter, and an aggregate node view used to read the value.
The single-increment baseline and all node forms compile to903B, reproducing
the known wrong register roles and unshared cleanup. Payload reference896B is
less accurate overall. No result improves the existing898B arm-advance bank.
Raw symbol sizes come from explain_mismatch, not the197/894B patched row
windows. All relocations resolve. Local sources/results:
build/scripted-event-alias-oct21/ and results.json.

The894B retail extent remains unchanged; larger trial bodies are mismatches,
not justification for covering retail padding. Existing strong ctor/visible
erase prerequisites and prior iterator controls remain in the earlier handoffs.
Do not repeat these live-alias or math-helper families without new evidence.
