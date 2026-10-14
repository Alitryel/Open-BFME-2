Bind rowed network consumers to NetCommandList::reset

At base 5caf9b321eda8a1a1849372281aba932ade95b85, ConnectionManager_reset.cpp
and FrameData.cpp reference an undefined NetCommandList::init name pinned to
0x0058B283. NetCommandList.cpp already provides the real reset definition there.
Use reset directly for the three allocation-branch calls; preserve both the
branch's reset and the following unconditional reset. Remove the unused init
declaration from the private view. The other consumer and the init pin remain.

Target evidence: the rowed ConnectionManager::reset REL32 operands at 0x004D0723
and 0x004D0767 and FrameData::init at 0x005DA535 each target 0x0058B283.
The existing 67-byte provider there passes the full byte gate. These facts
establish the target binding independently of the donor name.

Donor review: open-bfme-1 a7c38d3b2597121f178ab5190b3062478823257d,
game/GameEngine/Source/GameNetwork/NetCommandList.cpp, implements init as reset().
This supports purpose only; no donor layout or extra wrapper is imported.
The earlier linking repair fea964f85433012ec0c95a44a8d88f77b4c29af5 was also
reviewed; its global allocation repairs are already inherited here.

Acceptance:
- ./build.sh on all four cohort units: 55/55 matched; no skipped string,
  float or import literal checks. Final --prepare-current repeats the normal
  gate with strict reusable receipts for four explicit providers. This bounds
  refresh to this cohort; --refresh would compile every stale ledger object.
- EH: 7 EXACT, zero baseline exceptions or missing objects.
- Pin consistency, declared-function, class and data checks pass; converged
  data check covers eight addresses with no second names or unjudged rows.
- Final variant admission passes for the two modified consumers and provider.
- Placement rescan: zero bodies and zero pins.
- object-proof.json compares every non-debug COFF section and relocation before
  and after, normalizing only init -> reset external names and local label
  ordinals. Bytes, extents, flags and other destinations are unchanged; the
  larger consumer is restored. Strong/weak definitions and hatch counts hold.

Paired link preview uses the same index throughout: measurement 147cfae2cb,
2026-10-14 07:27, SHA256 in index.json, with only the four explicit current
objects substituted in memory. Two unresolved consumer edges disappear:
ConnectionManager_reset 1 -> 0 and FrameData 2 -> 1. The provider's findings and
all other findings are identical. This is a legacy-index preview; strict byte
receipts establish current compilation, not strict placement or closure.
There is no new authored C++, no linked-byte gain and no closed-strict gain
claimed. Neither census nor committed link status is rewritten. The committed
status comes from a different measurement (de7bb30890, 15:43 UTC); it is not
used as the baseline for these before/after figures.

Remaining blockers: FrameData and NetCommandList still need addMessage;
ConnectionManager_reset has the existing duplicate reset and selected
Transport/reset definitions; ConnectionManager.cpp has 72 unresolved names,
six duplicate names, 33 losing COMDATs and 18 selected-definition findings.
The paired reports enumerate them. Full link/boot runners were not started.

Deferred consumer: the initial five-call trial also changed the two init calls
in the larger ConnectionManager.cpp. New-variant admission refused its existing
nonmatching reset COMDAT after the relocation names changed. full-cohort-proof
shows all section bytes and other destinations unchanged and three unresolved
edges removed. admission-refused.txt records the check; blocked-consumer.diff
preserves the exact trial. This was logged as false-reject and that file was
restored, without changing the checker. Final admission passes without that
blocked consumer. Its source/pin remain for a future tooling or class repair.
