# LightClass constructor and assignment ownership repair

At BFME 2 ad9c2e49d69c9383a14a2447ef40797ae5cdafdc, light.cpp still
emits obsolete ZH LightClass constructor and assignment definitions beside
verified BFME 2 owners in LightClassCopyCtor.cpp. The 270-byte constructor
(digest a48d1b61fabf) differs from retail's 311-byte owner at 0x00130AC0
(digest 4ac95986822d). The two 305-byte assignment bodies also differ:
obsolete 781dd2bb4824 versus retail owner d23d16447f00 at 0x00130D40.
The ZH view has the old 0x94 RenderObj layout; the recovered owner's
0xC4 layout, vtable and access offsets are established in its existing source.
This repair adds no identity or layout claims and imports no donor bodies.

Remove only those two obsolete definitions and their present-unmatched
markers. Their declarations and the verified owner bodies remain. Losing the
constructor also stops emitting old vtables and virtuals. Two existing matched
14-byte accessors were among them: Set_Native_Screen_Size at 0x000EFB4C
and the existing Set_ObjectScale gen-alias at 0x005AD93A. Rehome these two
rows to collect.cpp, whose unchanged object emits both complete byte-exact
bodies. add_match --replace-existing verifies each row; alias notes and
its object-symbol token are preserved. There is no new alias, pin, anchor,
header change, compiler setting or baseline exception.

## Checks and bounded measurement

Discovery used repair_queue.py link and link_rank.py at the existing census.
The obsolete source, recovered owner and two otherwise-clean consumers were
claimed, checked and compared together. collect.cpp and both accessor RVAs
were claimed before rehoming; both sources pass the frozen-definition check.
This is a five-unit cohort, not an exhaustive link-closure measurement.

The index measurement is 825b86983f, 2026-10-15 12:37, based on census
5986a99448 at 04:52. context.json preserves its metadata and SHA256.
proof.py refreshes the same five current objects in memory on each side of
the unchanged index. It never updates the census, index, link status or history.

- Self-strict preparation and an independent ordinary build.sh pass 26/26
  matched rows across all five sources, eight float literals and one named
  import, with zero string baselines or skipped references.
- The light object drops 119 COMDATs. Every retained COMDAT is unchanged:
  42 in light.cpp and 316 across the four other objects. No new COMDAT
  variants are emitted. Every retained nondebug section has the same raw
  bytes, flags, definitions and symbolic relocations. The only other section
  removals are two obsolete destructor EH sections and its SafeSEH entry;
  every retained SafeSEH entry is unchanged. The proof checks these deletions.
- EH is exact for all three applicable matched rows, none missing/baselined.
  collect.cpp has a pre-existing renamed funclet label ($L22536 -> $L22377)
  that the ordinary gate resolves independently; it is unchanged here.
- All matched-row data-reference facts are identical before and after.
  The two edited row/source homes pass data_check --enforce with zero findings.
  The five-source cohort retains an existing, outside-baseline wrong-name
  finding in W3DTerrainVisualLoad.cpp: g_00DFE7A8 at 0x009FE7A8. This means
  the cohort-wide enforced data check fails; the repair does not add or hide it.
  Converged data checks all eight addresses with zero second names/unjudged rows.
- Class gate, frozen definitions, CSV and diff checks pass. Placement resweep
  of light.cpp finds zero new bodies or pins. Present-unmatched debt falls by
  two; the existing object-symbol alias moves between files without growth
  in total aliases. Normal hooks remain required.

The paired legacy preview removes 57 findings: 49 in light.cpp, six in the
recovered owner and one in each consumer. Removing the old vtable helper
also exposes one first-copy COMDAT loser in collect.cpp for the obsolete
one-argument Set_Collision_Type overload, for a net reduction of 56 findings.
This newly visible legacy first-copy finding has no retail address; it is
reported rather than presented as a target-proven regression or gain.
No new unresolved or selected-wrong finding appears in the cohort.

W3DDynamicLightConstructor.cpp (178 nonpadding bytes) and
W3DTerrainVisualLoad.cpp (978) change from one selected-wrong constructor
each to zero legacy link findings: a predicted gain of 1,156 existing bytes.
The ordinary link_check CLI independently reports two of five clean and
0 -> 1,156 bytes. It exits 1 for the other units' remaining debt. This is a
legacy link prediction with self-strict object witnesses; authored C++ growth
is zero, and closed-strict gain, actual executable placement and runtime
behavior are not measured. No full link cycle, census, nightly or boot runner
was invoked.

## Deferred evidence and remaining blockers

The first accessor rehome trial used dynamesh.cpp. Strict preparation passed
its six rows, but add_match's ordinary gate then obtained a 38-byte
Add_Vertex_Material helper instead of its 85-byte retail body at 0x00189670.
The tool reverted the ledger move. No dynamesh source change was made, its
file claim was released, and re_log records the failure for follow-up rather
than bypassing the byte gate. The initial object is preserved under ignored
build/light-ctor-owner-link-20261015/before. No cache-correctness diagnosis
is claimed from this observation alone. collect.cpp passes both preparations
and ordinary row checks and avoids that independent blocker.

light.cpp retains three unresolved Persist/SaveLoad names, ten COMDAT losers
and selected-wrong Get_Flag/Get_Intensity dependencies. The recovered owner
retains selected-wrong RenderObj destructor and Set_Force_Visible dependencies.
collect.cpp retains eight unresolved, 55 COMDAT losers and seven
selected-wrong names. proof.json lists all remaining findings and before/after
objects, including the new legacy first-copy diagnostic above.

The BFME 1 verified checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched at
4cdfd6e37afae409885e0bb78f2cecb7c269c207. Another worker holds the reference
file claim, and the prior comparative full-byte freshness verification remains
unresolved; no advancement or successful freshness stamp was made. Donor
repair 262d3e9507d68409d7cf86e730f4c75eefa58ccd was reviewed for its supported
pattern: remove a stale ZH definition beside a verified owner, then check
providers and consumers together. No donor layout, source or flags were imported.

Scratch originals and objects remain under ignored
build/light-ctor-owner-link-20261015/before; the committed proof uses these
and the unchanged local index to reproduce its paired checks.

Model: gpt-6.1-sol.
