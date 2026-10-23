# Inline wrapper link repair

Base tree: 00963d9140. Discovery used repair_queue.py link, link_rank.py,
its ranked JSON and current-object checks. Same paired local census index:
147cfae2cb, 2026-10-14 07:27, SHA256 recorded in object-proof.json.
Committed link_status.csv is older (67e1365aa9) and used only for discovery.
No index, status, history, baseline, pin or per-row data-back artifact changed.

Three consumers inline their tree-node comparisons but emit an unused,
18-byte iterator-base comparison differing from the first indexed copy.
Use the existing TU-local typed comparison pattern from Rva00441E4DFaction.cpp
and ScriptEngineNamedBindings.cpp. Each object loses exactly that wrapper;
all retained raw bytes, extents and relocation digests remain identical.

TerrainResourceClaimFeedback.cpp also inlines a local PlayerList +0x10
accessor whose surplus generic getLocalPlayer copy conflicts with the first
indexed copy. Rename only this implementation helper to claimantLocalPlayer.
Its full four-byte body (8b4110c3), relocation facts and inlined caller remain
identical. This introduces no retail identity or layout claim. The generic
indexed keeper remains untouched. The local rename has no other providers
or consumers in the index.

| Consumer | Existing authored bytes | Findings before | Findings after |
| --- | ---: | ---: | ---: |
| Common/GapBodiesGE01.cpp | 451 | 2 | 1 |
| GameClient/GUI/TerrainResourceClaimFeedback.cpp | 532 | 2 | 0 |
| GameClient/GUI/GUICallbacks/Apt/AptSaveLoadPromptAddFriend.cpp | 372 | 2 | 1 |

Paired legacy local preview: 0/3 to 1/3 clean, LINKED 0 -> 532 existing
bytes. This is not a closed-strict placement, link.exe result or fresh census
gain. Strict reusable compiler receipts are proven for the three owned
consumers; the complete provider closure remains unmeasured. New authored
C++ bytes: zero. Four local COMDAT findings are removed.

## Acceptance

- Bounded link_check.py --prepare-current before and after: 18/18 rows pass,
  strict reusable compiler receipts; no expansion to other sources.
- Final ./build.sh: 18/18, three strings and two float references verified,
  no unverified or baselined literal/import references.
- Full-object comparison: every retained COMDAT is unchanged; renamed helper
  raw bytes/extent/relocations identical; ordinary nondebug sections including
  symbolic EH targets, external bindings and hatch counts identical.
  Paired findings and unchanged keeper digests are in object-proof.json.
- EH verifier: 2 EXACT, none nonexact or missing. Class, frozen-definition,
  new-variants admission, CSV and whitespace checks pass.
- Enforced converged-data check: all 3 sources, 8 addresses, no second names
  or unjudged rows. Shadow data check retains the pre-existing
  TheProjectedShadowManager wrong-name finding at RVA 0x009EC2D4; read-only
  before-object analysis proves every data binding and finding unchanged
  (data-proof.json). This is a remaining blocker for any closed-strict claim.
- Affected-unit place_bodies.py resweep: 0 bodies, 0 pins.

Remaining independent local legacy blockers: GapBodiesGE01.cpp references
unresolved ControlBar::findCommandSet; AptSaveLoadPromptAddFriend.cpp retains
its non-retail less<int> COMDAT. Neither was retried or concealed.
Scratch source/object backups and the paired proof script remain under
build/rb-node-link-20261014. No full link cycle, census build/measure/history,
nightly or boot runner was started.

## Reference review

Verified BFME 1 pointer: 23b143233b5a8664a3bdf8572df6d905c310a5a1.
Reviewed de59a7e9f891b3ed2d4221d151ca881f4b75a583, whose scoped gate preserved
all callers while reconciling surplus inline Apt predicates. That linking
principle applies; donor layouts and identities are inapplicable to these
consumers. This change uses existing BFME 2 patterns and imports no donor code.

Official master fetch reports a7c38d3b2597121f178ab5190b3062478823257d, ahead
of the verified pointer. Another worker holds file:reference/open-bfme-1;
the clean checkout and committed verified inputs were preserved. The pointer
update and old/new full-gate comparison remain with its owner; this session
wrote no freshness-success stamp.
