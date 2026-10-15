# Client iterator ownership repair, 2026-10-15

At BFME2 base bb1313274d3bcfac789dbb34553ac33e74c99d49, keep typed
list-iterator inequality local in GameClientXfer.cpp and
Drawable/PickAndPlayUnitVoiceResponse.cpp. This uses PlayerTemplate.cpp's
existing recipe and STLport's same node-pointer comparison. No game function,
ABI, field layout, compiler setting, ledger row or external provider changes.

## Measured improvement

Genuine before/after objects are compared against separately refreshed copies
of the same runner index: update 19a2565407, census 5986a99448. context.json
records its hash and source revision. The committed status queue separately
reports measurement 28269d8e8d; it was used for selection, not paired proof.
Neither index nor census/status was rewritten.

Local legacy findings fall 14 -> 13 in GameClientXfer and 10 -> 9 in voice
response. One rejected _List_iterator_base::operator!= copy disappears from
each consumer. Together these consumers contain 9,860 existing authored bytes
as counted by link_check (0xCC excluded). Legacy LINKED remains 0 -> 0;
new authored matched bytes are zero. No self-strict placement, closed-strict
gain, census gain or full executable link is claimed.

object-proof.json proves all 232 retained COMDATs have identical bytes and
relocation digests. Each object replaces one unreferenced 18-byte external
comparison with two unreferenced 12-byte static typed comparisons. All other
normalized nondebug sections, relocations, external bindings and directives
are identical. No call relocations target the removed or added comparisons.
The compiler's actual game code and data bindings are preserved.

## Checks and limits

- Strict preparation before and after: 20/20 matched rows; reusable receipts.
- Explicit ./build.sh on both consumers: 20/20 matched; 33 literals, two float
  literals and all reference checks pass, with zero baselined/skipped strings.
- EH verification: all five EH-bearing rows EXACT; no missing/inexact rows.
  Parent EH evidence resolves automatically renumbered cleanup labels.
- Paired local link proof: precisely one COMDAT finding removed per consumer,
  no other result changes. Ordinary local link check exits 1 for the remaining
  findings, as expected. New-COMDAT-variant admission passes.
- Data enforce: zero findings. Converged-data admission: eight addresses,
  zero second names or unjudged rows. Class, declared-definition and whitespace
  checks pass. place_bodies serves zero additional bodies or pins.
  Session-start check_csv passes (91,218 rows).
- The unmodified identity shadow gate retains all 16 original findings and
  reports three extra voice-cleanup bindings through stale literal $L labels.
  identity-proof.json records these exactly; no shadow finding is suppressed
  or baseline changed. This is a diagnostic limitation, not a new binding:
  object-proof proves all nondebug sections/relocations unchanged and the
  ordinary gate resolves these funclets through the exact parent EH graph.

Proof scripts run from the repository root using saved original binaries and
source snapshots under build/client-iterator-link-20261015. Scratch binaries
are not committed. Only bounded strict preparation and local checks ran;
no maintainer-only verification runner was started.

## Remaining work and reference review

GameClient still has duplicate xfer/audio-setter definitions; drawable and
unsigned-vector helpers; max; record construction/overflow and selected
xferNoName providers. Voice response still needs BfmeTmpCF lifecycle and
TheExperienceLevelSystem providers, duplicate NameKeyGenerator helpers and
Rva004D977D ownership, and the Rva00395561 destructor provider reconciled.

MapCacheWriteCacheINI was separately claimed and tried twice. List+tree local
comparisons and then list-only both fail its byte gate despite its baseline
passing. Both edits were reverted, the evidence was recorded via re_log.py,
and its file claim released. No unchanged blocked attempt is repeated.

Selection started with repair_queue.py link, link_rank.py and current-object
probes. ModuleFactoryInit, AptMpGameSetupRefreshMapList, Rva000E473F and
RTS3DSceneFlushOccludedObjectsIntoStencil already link in the local preview;
no repair is claimed for them. The published object store was fetched while
the newer runner index was retained.

Reuse the prior supported helper-ownership donor review and inspect BFME1
repair de59a7e9f891b3ed2d4221d151ca881f4b75a583: consumer helper consistency is
applicable; donor implementations, layouts and addresses are not imported.
Official master fetched to eab55866b6a39aa54797b2d687f705c99e834b43. Clean
verified checkout/gitlink a7c38d3b2597121f178ab5190b3062478823257d is retained:
another worker owns its update, and the prior full old/new input comparison
remains blocked on dependency inputs/stalled old-input MSVC compilation.
No pointer advancement, unchanged full retry or freshness success stamp.
