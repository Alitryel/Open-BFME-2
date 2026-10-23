BitFlags<117> inverse-intersection provider selection

Base checkout: 0cc24017ed72eff057f963830ca5e68471184d36.
Discovery: repair_queue.py link and link_rank.py --top 35 / --near 12,
followed by current-object inspection because several ranked blockers were
already repaired. The committed status measures 28269d8e8d; this paired
result instead uses the local index measuring 19a2565407 (2026-10-15 09:33),
based on census 5986a99448. Fetch retained that newer local index. Its exact
hash, source/object hashes, counts and removed findings are in object-proof.json.
No census, status or index data was changed.

Both W3DModelDraw.cpp and W3DModelDrawO1Inlines.cpp instantiated the ZH
inline BitFlags<117>::countInverseIntersection body, producing two different
non-retail COMDATs. The existing BFME2 provider owns the verified 89-byte
inverse counter at 0x0033AE53 and its 87-byte intersection sibling at
0x0033ADFC. Existing rowed ModelConditionInfo findBestInfoSlow calls and
the four-word SWAR bodies establish identity and layout independently of
this edit. The provider's own local link failure was solely selection of
a competing inverse counter.

Declare the inverse specialization next to the existing declaration-only
intersection specialization in both consumers. These calls now use the
existing provider. Shorten the accompanying comments to preserve original
line numbers: changing __LINE__ otherwise changes four random-call debug
arguments in the unmatched adjustAnimation body. No ABI, layout, flags,
global, pin, ledger row, baseline or provider source changes.

Acceptance:

- Before/after link_check.py --prepare-current on both consumers, the counter
  provider and SparseMatchFinderModelConditionBestInfoSlow117.cpp: 25/25 rows
  byte-exact, strict reusable receipts; string, float and import checks pass
  with zero skipped/unverified references. Final ./build.sh on the two edited
  sources passes 22/22 rows. EH before/after: one graph, EXACT in both cases.
- Two divergent inverse COMDATs disappear. Indexed selection changes from
  a wrong body to the single retail provider: three copies/three digests
  become one copy/one digest. No replacement COMDAT is introduced.
- All retained nondebug sections of both consumers are identical, including
  instruction bytes, data, directives, extents and symbolic relocations;
  1,427 and 695 retained COMDAT bodies respectively have unchanged digests.
  Only the inverse counter and its now-unused bitset helper sections vanish.
  Both read-only context objects remain byte-identical.
- Separate in-memory refreshes of the before and after objects against the
  same index add zero findings. Model-draw COMDAT/selected counts improve
  93/43 -> 92/42 and 54/28 -> 46/26. The provider loses its sole selected
  blocker. The standalone slow-match consumer loses the inverse blocker,
  retaining its separate findBestInfoSlow selection conflict.
- The ordinary four-unit local preview agrees: provider LINKS 0 -> 176
  existing nonpadding bytes, aggregate 0 -> 176; the other three units
  remain blocked. This is a LEGACY local prediction with self-strict byte
  acceptance. New authored C++ bytes are zero. No closed-strict, executable
  placement or runtime improvement is claimed. No maintainer-only runner ran.
- New-COMDAT-variant admission, class, declared-definition, enforced-data,
  converged-data, CSV and whitespace checks pass. Data checks report zero
  findings and zero second names. Placement resweep finds no bodies or pins.

Remaining consumers require independent repairs: the main W3DModelDraw unit
still has 15 unresolved, 92 COMDAT and 42 selected-definition findings;
O1Inlines retains 46 COMDAT and 26 selected-definition findings. The standalone
slow-match provider still selects a non-retail findBestInfoSlow elsewhere.
These are not a reason to repeat this resolved inverse-counter repair.

Dedicated reference review: verified donor pointer remains
 a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor reconciliations
4966496c5ae401ec877a044e1ae6dd04f9d9f65c (AsciiString inline/provider) and
de59a7e9f891b3ed2d4221d151ca881f4b75a583 (Apt inline unification).
The existing-provider principle applies; their identities and layouts do
not supply BFME2 evidence here. No donor source or dependency is imported.
Official upstream fetch found a9e3b4b524bac0c2f17bd328badb0784deb0a788.
Another worker holds file:reference/open-bfme-1; comparative full verification
and pointer update remain outstanding. No freshness success stamp was written.

Before objects, source snapshots, dependency receipts, detailed findings and
paired proof script remain under ignored build/bitflags-inverse-link-20261015.
