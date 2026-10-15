# Two tree-iterator consumer repairs

ObjectCreationList and CreateAHero each emitted an unused 18-byte external
_STL::_Rb_tree_base_iterator::operator!= differing from the kept copy in the
frozen census. A TU-local typed comparison preserves the native inlined node
comparison and removes that external conflict. No shared headers, flags, ABI,
ledger, pins or data names change. The existing ObjectCreationList max overload
is retained; its declaration block keeps the original line count because an
unrowed DeliverPayloadNugget debug call embeds __LINE__ in its code.

## Evidence and acceptance

Base commit: 956cd5b8433678d7ae3b73bcae9aa60714554714. index-meta.json records
the unchanged index hash, measurement a2839ea429 (2026-10-15 13:35), and underlying
census 5986a99448. The committed status CSV at 4b7e7091c4 is discovery evidence
only. Published-index fetch kept the equally current local index and imported
22,914 objects. Both consumers and the first selected provider,
stlport_map_int_int.cpp, were file-claimed before preparation. Frozen-file checks
pass for both edited sources.

- Strict bounded preparation passes 23/23 ObjectCreationList, 33/33 CreateAHero
  and 19/19 provider rows. The explicit normal byte gate also passes 75/75:
  21 string literals, three empty strings, three floats and one import.
  Existing renamed funclets resolve through their parent EH graphs. Two
  CreateAHero folded constructors verify against retail owners and callees.
- EH verification: 12 EXACT graphs, zero nonexact, missing or baseline use.
- proof.py proves 1,357 retained external COMDAT bodies, sizes and relocation
  digests unchanged. All other retained nondebug section bytes, flags,
  directives, symbolic relocations, external definitions and data facts are
  unchanged. The three new typed helpers are static, 12 bytes each, have no
  relocations and no incoming nondebug relocations. Only the two unreferenced
  external comparator sections disappear.
- Paired previews refresh only the two explicit consumers and unchanged,
  strict-current provider into independent copies of the same frozen index.
  ObjectCreationList findings: 71 -> 70. CreateAHero: 39 -> 38. Each difference
  is exactly the removed comparator conflict. Provider findings stay at 12,
  and kept comparator copies are unchanged. No new variant finding appears;
  pre-existing variant findings stay 26 -> 26 and 0 -> 0 respectively.
- Ordinary prescribed link_check agrees that all three units retain independent
  blockers. Legacy predicted LINKED bytes: 0 -> 0. The consumers contain 4,928
  existing nonpadding bytes; new authored C++ bytes: 0. Strict-current receipts
  prove compiler-input currency, not a clean closure. No closed-strict or
  executable-placement gain is claimed.
- Class, declared-definition and enforced converged-data checks pass (eight
  converged addresses, zero second names or unjudged rows). Explicit enforced
  data checking still reports the pre-existing CreateAHero local static S1
  wrong-name at RVA 0x009FE484. Paired object/data proof establishes identical
  facts and findings before and after; normal shadow data checking passes.
- Ledger consistency passes. Diff whitespace checking passes with cr-at-eol
  because CreateAHero retains its existing CRLF encoding.
- Placement resweep: zero bodies and zero pins. No verifier, baseline or
  whitelist changes. Full link cycles, census runners, nightlies and boot
  runners were not started.

Raw before objects live in ignored build/tree-oclist-link-20261015/before.
proof.py replays from the root with those objects, current strict receipts and
the recorded unchanged index. To recreate snapshots, prepare the parent sources
at the base commit with the same verified BFME 1 inputs, save their objects,
then prepare the changed sources. JSON preserves the measured results; these
scripts are evidence rather than portable acceptance gates.

## Scope and provenance

This continues tree-comparison-link-20261015's proven local overload pattern.
BFME 1 donor commits c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 and
66b19a8e95a4add525ef808fcea088e306798e2b were reviewed for the principle of
suppressing conflicting incidental copies while preserving inlined behavior.
No donor layout or target identity is inferred from those commits. Existing
source identity/layout evidence remains unchanged. Target object evidence proves
the preserved behavior and emission-only effect in these two consumers.

MapCacheWriteCacheINI was claimed, baseline-prepared (1/1 exact), then released
without retrying its recorded tree-comparison branch-codegen blocker (log 58720,
58750). The audio orphan-funclet false rejects were also not retried. The large
W3DModelDraw consumer remains outside this bounded follow-up and unmodified.
Other remaining findings include unresolved audio/snapshot/Pathfinder services,
allocator/vector/tree helpers, constructors and wrong-selected providers;
link-after.txt contains their exact lists. These require independent evidence.

Official BFME 1 master was fetched at 21f8dfcc22798ba06acdaf3d2d06312f88d2d34f.
The verified clean checkout/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
A foreign live file:reference/open-bfme-1 claim owns the overdue comparative
verification. No pointer update or successful-freshness stamp was made.

Model: gpt-6.1-sol.
