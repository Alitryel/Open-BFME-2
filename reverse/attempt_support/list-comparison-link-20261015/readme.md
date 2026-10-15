# Local list comparisons: three consumer link repairs

Base bca2384dc4. Frozen fetched index: a2839ea429, 2026-10-15 13:35;
underlying census 5986a99448, 04:52. The committed status CSV was measured
separately at 4b7e7091c4 and served discovery only. proof.json records the
index hash, object hashes, source hashes and paired findings.

Rva00525ABFXfer.cpp, AIGroupMoveFormation.cpp and MilesAudioMultisound.cpp
each emitted an unused, incorrect 18-byte external copy of STLport's
list-base inequality operator. Select an internal typed overload, following
the existing NetPacket.cpp and W3DFXParticleSystem.cpp pattern. Native
comparison instructions stay inline and unchanged. No layout, compiler flag,
pin, ledger row, data name, import binding or shared header changes.

The canonical provider is stlport_list_int.cpp: its complete object is
unchanged, and its 22-byte comparator at 0x006CFE40 is retail, including
relocations. All four files were claimed before their bounded preparation;
the three edited files passed the frozen-definition check before editing.

## Evidence and acceptance

- The normal byte gate passes 12/12 rows in the three edited consumers.
  Bounded --prepare-current passes all four units, 16/16 rows, and establishes
  strict reusable receipts. Float, string and import reference gates pass.
  EH verification finds five complete EXACT graphs, zero nonexact rows,
  zero missing objects and zero baselined exceptions.
- proof.py compares saved original objects against current objects. All 194
  retained external COMDAT bodies, extents and relocation digests are identical.
  The only removed section in each consumer is the unreferenced 18-byte
  comparator. All other existing nondebug code/data and normalized relocations
  are identical, including directives and external bindings; the latter only
  lose the comparator definition.
- MSVC also emits five internal typed comparator copies, each 12 bytes, despite
  forceinline. These are explicitly accounted for, rather than described as
  unchanged sections. Each has static COFF storage and no references from any
  nondebug section. None participates in external COMDAT selection, introduces
  an import, or changes a retained call site. Trying forceinline after ordinary
  inline preserved the same result; both variants passed the native byte gate.
- Paired previews deep-copy the same frozen index and refresh only the same
  four explicit objects in both phases. Rva00525ABFXfer findings fall 4 -> 3;
  AIGroupMoveFormation 11 -> 10; MilesAudioMultisound 11 -> 10. Each difference
  is exactly the removed external comparator. The provider remains at 46
  independent findings. Ordinary link_check agrees: no unit links completely,
  existing LINKED bytes remain 0 -> 0, and authored coverage grows by zero.
- Class, declared-definition, data enforcement, converged-data, new-variant,
  CSV and whitespace checks pass. Placement resweep reports zero bodies and
  zero pins. No gate, baseline or whitelist changes.

These are legacy local link predictions with strict-current compiler inputs.
No self-strict executable-placement gain, closed-strict gain, new census
measurement or runtime result is claimed. Maintainer-only runners were not run.
proof.py replays the comparisons using ignored snapshots under
build/list-transfer-link-20261015 and the unchanged index; proof.json preserves
the results. It is evidence, not a portable acceptance gate.

Target identity and layout provenance remain as documented in each original
source: native/WB evidence for the transfer and multisound access views, and
ZH semantic guidance plus native/WB identity for formation movement. This
repair makes no new identity or layout claim. BFME 1 suppression repair
c1315665 was reviewed as general linking guidance; no donor layout or code
was imported. The actual overload pattern is already supported in BFME 2.

## Remaining work

The transfer unit still has list insertion and parent-specific COMDAT/selected
findings. Its regular byte gate passes; the frozen link identity verdict needs
separate investigation. Formation movement retains its Pathfinder dependency,
duplicate helpers and command/vector disagreements. Multisound retains audio
dependencies and vector/hash/list allocator conflicts. The comparator provider
has its own unrelated blockers. These findings are preserved verbatim in
proof.json; this repair does not assert any of them resolved.

sweep.json lists other consumers: MapCache's existing branch-codegen blocker
and two audio orphan-funclet false rejects were respected without retry. Four
additional consumers remain untrialled for a later bounded pass. An initial
AptMpGameSetupRefreshMapList claim was released after its unchanged current
object already passed local linking; the stale queue result was logged.

Official BFME 1 master was fetched at e08276073. The clean verified checkout
and gitlink remain a7c38d3b2597121f178ab5190b3062478823257d. Another worker
holds file:reference/open-bfme-1; the overdue comparative update is left with
that owner. No pointer advance or successful freshness stamp was made.

Model: gpt-6.1-sol.
