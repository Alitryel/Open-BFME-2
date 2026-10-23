# Float math and light constructor link repair

Base commit: 469fe60d26 (full hash in proof.json). Measurement: local census
ac77c85054, 2026-10-15 14:25; index hash in index-meta.json. The published
index/objects were fetched; census/status/history were not regenerated or edited.

The repair queue and current link previews served the light-direction unit and
giant-bird death unit. Their last blockers were incidental sin(float)/cos(float)
COMDATs, plus Matrix3D(bool) in the light unit. A same-cause census sweep found
CylinderEmissionVolumeModuleSample with only the same trig blockers. All four
file scopes, including the unchanged AptMathCallbacksBFME2 provider, were claimed.

## Supported changes and proof

Apply the existing FloatUpdateUpdate math-header policy: scope inline to static
inline only while including MSVC math.h, then restore the macro. Twelve 17-byte
wrappers become local functions, retaining their complete bytes and relocations.
They cease competing for external sin/cos/sinf/cosf names. The light unit's
75-byte non-retail Matrix3D(bool) outline is suppressed by imported forceinline
on its existing definition; the matched initialization stays inlined. No new
import is introduced. No shared header, flags, layout, identity, pin or ledger
range changes. Existing source evidence supplies the target relationships;
this repair establishes emission/selection facts rather than new identities.

proof.py compares self-strict before/after snapshots in ignored
build/light-bird-math-link-20261015/before. It verifies all other nondebug
sections, flags, bytes, symbolic relocations, external/weak bindings and data
references unchanged, and no incoming nondebug relocations to these thirteen
external copies. Wrapper bodies are compared separately across their change
of linkage. All retained COMDAT digests/sizes are identical, with no new variants.
The unchanged provider is included in the same proof and byte gates. Existing
first kept providers remain unchanged; removed sinf/cosf copies were identical
twins, and every surviving kept copy remains the same. Matrix3D's surviving
copies retain their census classifications (some are unknown, not newly proven).

## Acceptance and measured scope

Before/after bounded preparations provide strict reusable self receipts.
Final prepare-current and ./build.sh: 24/24 rows across four sources, one string,
16 float literals, zero named imports. Data enforcement: zero findings;
converged check: eight addresses, zero second names or unjudged rows. Class gate,
find_declared_unmatched, check_csv and diff whitespace checks pass. EH verification
sees zero EH rows and no missing objects; full retained sections are also compared.
Placement rescans of all three changed units find zero bodies and zero pins.

Same-index paired legacy local preview, in memory only:

| Unit | Before blockers | After blockers | Existing nonpadding bytes unlocked |
| --- | ---: | ---: | ---: |
| Rva0009D55BProductLight | 3 | 0 | 642 |
| GiantBirdSlowDeathBehavior | 2 | 0 | 355 |
| CylinderEmissionVolumeModuleSample | 2 | 0 | 212 |
| AptMathCallbacksBFME2 (unchanged provider) | 0 | 0 | 0 |

Combined legacy local LINKED: 1332 -> 2541, gain 1209 existing bytes. New authored
C++ bytes: zero. Self-strict byte verification is current; closed-strict gain and
actual executable placement remain unmeasured. No maintainer-only runner ran.
Normal commit/push hooks still apply.

## Reference review and handoff

Reviewed BFME1 c1315665a1b22beb7e6d9279548fe5b1c26ed1f9: imported forceinline
suppresses surplus DamageInfo constructors while preserving callers; this
emission technique applies to the light constructor, without borrowing its ABI.
Reviewed d3f9000fe08615a100e844adfff57fa4a39cd615: TileData surplus-constructor
ownership is relevant as a principle; its layout/body is inapplicable. BFME2's
existing float-math-local-link-20261013 evidence directly supports the header
policy. No donor function body or donor address was imported.

Verified BFME1 inputs remain a7c38d3b2597121f178ab5190b3062478823257d. Official
upstream fetched to 8fd286029cee70cd91c8d0c2a860ce73d9f07df2; freshness success
stamp is absent. Updating/comparing old and new inputs remains foreign-claimed
(file:reference/open-bfme-1, codex-b0d3-01a11af6-root at the final claim check).
The verified pointer is preserved, without marking the overdue update successful.

Remaining same-cause current previews: Pathfinder has 13 unresolved names,
13 duplicate definitions and seven selected-provider conflicts in addition to
trig wrappers; HordeContainIface11CSlots has numerous unresolved/COMDAT/provider
conflicts. Their broad repairs were left untouched. Earlier queue probes also
confirm existing BfmeStringRecord EH cleanup, PrereqUnitRec overflow and
OpenContain vtable blockers; documented failed shapes were not retried.
