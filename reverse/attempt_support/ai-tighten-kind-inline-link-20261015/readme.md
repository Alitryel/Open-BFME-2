# AIGroup kind-mask outline repair

`AIGroupTightenToPosition.cpp` emitted wrong standalone copies of
`Object::isKindOf` (40 bytes, digest `d08f3bed52e8`) and
`ThingTemplate::isKindOf` (41 bytes, `659973b635dc`). Keep the existing
private inline implementations and mark them `dllimport` as well as
`__forceinline`. VC7.1 then suppresses these unused outlines and their
4-byte `Object::getTemplate` dependency. No import or external binding is
added. This is an emission repair; the existing target identity, layouts,
semantics and donor uncertainty remain as documented in the source.

BFME 1 pointer `a7c38d3b` and linking repair `66b19a8e95` were reviewed.
That Apt allocation repair supports the compiler mechanism, not BFME 2
identity or layout. No donor body, header or layout is imported. Official
master was fetched at `95eeb3be`; freshness remains pending under another
worker's live submodule claim. The verified pointer and timestamp remain
unchanged.

## Acceptance

- Strict reusable preparation and ordinary byte gate pass all 3/3 consumer
  rows. EH before/after is EXACT 1/1. Enforced data and converged-data checks
  pass, as do class and declared-definition checks. Placement finds no new
  body or pin. No flags, pins, aliases, markers or protected baselines change.
- The paired current-object preview uses unchanged index `a2839ea429`
  (2026-10-15 13:35; original census `5986a99448`). Findings fall from four
  to one: two wrong COMDATs and the selected wrong ThingTemplate helper
  disappear. The unresolved iterator insertion signature is unchanged.
- All 18 retained COMDATs and all retained nondebug section bytes, flags,
  definitions, symbolic relocations, external/weak bindings and data facts
  are equal. No retained relocation addresses a removed helper; admitted
  variant sets remain empty. Remaining copies keep the same loss decisions
  and kept body facts. The unused getter loses one of 118 identical copies;
  the other 117 remain. Exact hashes and paired findings are in the JSON.
- Providers and consumer were checked together. Provider strict preparation
  passes 35/35 rows: Object.cpp, ThingTemplateRva000456AC.cpp and
  Rva0054BBB5.cpp. The first two link in the legacy local preview. The iterator
  provider still has its own vtable COMDAT and selected deque-provider
  conflicts. These are self-strict receipts, not closed-strict closure.
- New authored C++ bytes and legacy linked-byte gain are both zero. No full
  census, link.exe run, whole-game result or closed-strict gain is claimed.

## Handoff

The consumer still references
`?insert@SimpleObjectIterator@@QAEXPAVObject@@M@Z`; the matched body at
0x0054BBB5 uses the int-parameter decorated name. Reconcile that ABI/name and
its provider's remaining conflicts as separate evidence-backed work.

The same-name family was inspected. AutoHeal and privateGuardObject/Position
use inherited Thing views (rather than this Object view) and, for the guards,
different compiler flags. They require their own object and caller evidence;
this repair does not establish their acceptance. No unchanged failed getter
trial was repeated.

Session triage also confirmed that ScriptEngineRva00205D5D.cpp and
ProductionPrerequisiteIsSatisfied_ProductionPrerequisite_isSatisfied.cpp
already have clean current local previews after strict preparation. No repair
or gain is claimed for those stale census findings. A premature RankInfo
triage assertion was explicitly retracted with a `void` log entry: its getter,
placement-new, allocator-import and address blockers remain, with no source
trial made. Those file claims were released. Before snapshots and the one-off
proof script stay in ignored scratch; reproduce.json identifies them.
