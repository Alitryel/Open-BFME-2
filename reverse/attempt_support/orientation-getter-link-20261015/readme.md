# Object orientation getter link repair — 2026-10-15

The two consumers in `sources.txt` emitted a surplus private-view
`Object::getOrientation` COMDAT that conflicted with the first census copy.
Read their existing orientation field directly instead. The heading query
uses friendship to preserve its private field access; no layout changes.
Neither repaired object defines or references this getter afterward.

## Evidence and scope

Measurement: census `28269d8e8d`, 2026-10-15 09:31; exact index hash and
pre-edit source revision are in `measurement.json`. Both pre-edit objects
and both final objects were current under strict dependency receipts.
The paired comparison refreshes both consumers together in separate copies
of the same index. The on-disk census and status were not modified.

Local **legacy** link preview: 3 findings become 1; the heading query
becomes link clean (155 existing authored bytes). W3DModelDraw loses its
getter conflict but still has unresolved
`?addEdgeToTrack@Rva00084206Track@@QAEXMM@Z` (725 authored bytes remain blocked).
This is no new authored C++ coverage and no measured self-strict or
closed-strict gain. No full link cycle or census was run.

`object-proof.json` records the two removed seven-byte getter COMDATs,
all 30 retained COMDAT byte-and-relocation digests (unchanged), unchanged
strong/undefined/weak symbol sets, and unchanged other link findings.
`target-reads.json` retains owner rows and retail instruction contexts:
heading-query RVA 0x0029B3D3 reads [eax+0x1c0] with fld; W3DModelDraw RVA
0x000B818E reads [eax+0x1c0] with movss. The former is the common return
for both source fallback paths. Full row bytes still match. These accesses
support the direct read; they do not establish a separate retail getter
identity or address. Existing row provenance remains in the ledger/source.

BFME 1 linking repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d was reviewed:
suppressing surplus conflicting COMDATs is applicable; its wrapper/pin/alias
details are not used. The verified BFME 1 pointer remains
a7c38d3b2597121f178ab5190b3062478823257d. Freshness fetch found upstream
eab55866b6a39aa54797b2d687f705c99e834b43, but another seat holds the
submodule file claim and comparative full-byte update verification remains
incomplete (prior baseline had 2982 stale units). No pointer or freshness
success stamp was changed.

## Acceptance

For both paths from `sources.txt`:

- `python3 tools/link_check.py --prepare-current ...`: two strict-current
  providers, normal byte verification passed; no census/status write.
- `./build.sh ...`: 2/2 rows exact, three float literals verified, no skipped
  or baselined references (`byte-after.txt`).
- `python3 tools/link_check.py ...`: paired legacy preview above; the
  unresolved track helper is the sole remaining finding (`link-after.txt`).
- `python3 tools/link_check.py --new-variants ...`: pass.
- EH verification: zero missing objects or nonexact EH rows; shadow data
  check: zero findings; enforced converged-data check: eight addresses,
  zero second names and zero unjudged rows.
- `find_declared_unmatched.py`, `class_gate.py`, `check_csv.py`, and
  `git diff --check`: pass. `place_bodies.py`: zero new bodies/pins.

`proof.py` is the exact comparison used. It reads the ignored scratch
`build/orientation-getter-link-20261015/`, whose before sources/objects were
saved before editing. Source revision, source/object hashes, retail hashes
and retained COMDAT digests permit checking the recorded inputs. The saved
binary objects are not committed. Preparation and before/after logs accompany
the proof results.
