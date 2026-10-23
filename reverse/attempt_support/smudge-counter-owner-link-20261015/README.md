# Smudge counter ownership and render-call repair, 2026-10-15

W3DFXParticleSystem.cpp now owns the four-byte zero-initialized
`g_bfmeVal991` counter shared with BfmeConv991.cpp. The latter calls the existing
verified `W3DSmudgeManager::render(RenderInfoClass&)` provider instead of its old
donor placeholder `BfmeB991::bfmeSet991(int)`. The obsolete pin is removed.
The public donor-shaped wrapper signature is retained; its integer argument
carries the RenderInfoClass address. This change adds no function or alias.

## Target and donor evidence

native.json records instructions within the proven boundaries of the main
particle pass (RVA 0x0004CF9A, 1251 bytes) and wrapper (0x0004CB32, 45 bytes).
The former zeroes EBX at VA 0x0044CFB1, stores it to VA 0x00DE1CF0 at
0x0044CFC7, and increments that same dword at 0x0044D29E in the smudge loop.
The wrapper reads it at 0x0044CB55. Four retail zero bytes and the compiled
sizeof/allocation independently verify the data row's extent. The data-ledger
span of eight bytes is an inter-address estimate, not an eight-byte claim.
The existing donor identifier is retained; its original target spelling remains
unknown. The particle unit owns the render-time reset and increment.

The wrapper's direct call at VA 0x0044CB40 targets RVA 0x000A6E08. That whole
2447-byte body is already rowed as W3DSmudgeManager::render in
W3DSmudgeManagerRender.cpp, from BFME1 donor d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c
and independently verified target behavior. Its RenderInfoClass reference uses
the same one-stack-word x86 thiscall ABI as the old integer placeholder. The
explicit pointer/reference cast preserves that argument and the existing global
view; no second data name or new layout claim is introduced.

Before selecting this repair, BFME1 linking commits
53d32d6b4b377317a3397971629ca3ad20b870e9 (Apt constructor COMDAT suppression)
and 63e68aaa567add9eb42a79913d23eece6a19ceee (verified character-search call-owner
binding with a typed return adaptation) were reviewed. The latter supplies a
repair method; BFME2's own call bytes, provider body and gate prove this use.
No BFME1 address or unverified target identity is imported.

## Controlled local measurement

Base commit 92034602a0abdb8afd702cc374a76b89d4339d64. context.json records the
unchanged runner index SHA256, update commit 19a2565407 (2026-10-15 09:33) and
underlying census 5986a99448 (04:52). Both proof phases refresh copies of that
same frozen index in memory with only the three strictly current owned objects.
The committed queue at 28269d8e8d served selection only. No index, census or
link-status artifact was rewritten.

| Unit | Unresolved findings before -> after | Legacy LINKED bytes before -> after |
| --- | ---: | ---: |
| W3DFXParticleSystem.cpp | 1 -> 0 | 0 -> 1710 |
| BfmeConv991.cpp | 2 -> 0 | 0 -> 45 |
| W3DSmudgeManagerRender.cpp | 0 -> 0 | 2515 -> 2515 |

Exactly three missing bindings disappear. Total local-preview LINKED bytes rise
2515 -> 4270 (+1755); authored C++ bytes grow by zero. No self-strict,
closed-strict, full-census or executable-link gain is claimed. Strict receipts
establish current objects, not transitive provider closure.

proof.py verifies all nondebug sections, relocations, external bindings and
linker directives. The particle object adds only a four-byte zero .bss owner;
all 35 COMDAT bodies and their normalized relocation identities are unchanged.
The wrapper's one COMDAT retains every byte with only the direct-call symbol
mapped to the verified owner. The provider's entire object and its 33 COMDATs
are identical. No new COMDAT variant is admitted. Original sources, objects,
receipts and after snapshots remain in ignored
build/smudge-counter-owner-link-20261015; replay requires those snapshots and
the recorded frozen index. These are evidence scripts, not alternative gates.

## Acceptance and handoff

- Strict preparation and explicit build.sh: 10/10 matched function rows across
  all three sources; one sizeof4 data row exact. Three pre-existing renumbered
  funclet labels resolve through the provider's verified parent EH graph.
- Two strings, one empty reference, nine floating literals and zero imports
  verified; zero baselined or skipped literal cases.
- EH: three EXACT, no baseline or missing-object cases.
- data_check --enforce: three sources, zero findings. Converged enforcement:
  eight protected addresses, zero second names or unjudged rows.
- New-variant admission, class and declared-definition checks pass. Placement
  resweep of the two changed units returns zero bodies and zero pins.
- data_ledger.py generated a scratch ledger; only its exact 0x009E1CF0 row was
  selected. ledger-generation.json records hashes and its warning about 128
  unrelated missing objects; all affected units are strictly current.
- No remaining local link finding in these three units. Project-wide closure
  and maintainer-only full verification remain unmeasured. No full link cycle,
  census, nightly or boot runner was started.

The initial rank contained stale entries: AIIdleStateUpdate and
AIAttackApproachTargetStateOnExit already link with current objects; their
exploratory edits were restored and claims released. Other unchanged probes
still need the banked ScoreRowSort comparator and water-tracks update helper;
those reconstructions were not retried. Fresh reference-dependent work remains
subject to the existing BFME1 pointer-update claim and recorded old/new input
verification blockers (missing/stale dependency inputs and stalled old-input
MSVC compilation). The clean verified a7c38d3b2597121f178ab5190b3062478823257d
checkout/gitlink and freshness stamp were preserved. The observed fetched
BFME1 origin/master is 4a7ac95953977c61221d14307247b381b224c168; no unverified
pointer advance is included.
