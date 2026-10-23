# Integer-construction COMDAT repair, 2026-10-15

Base tree: `2c2e88cdea636c9defee459006e04ca40c7c53a9`. Model: `gpt-6.1-sol`.

Five consumers emitted the same surplus 17-byte `_STL::_Construct<int,int>`
COMDAT (digest `ad8cdf2bb9fa`), differing from the canonical retail body at
`0x00620140` in `Code/Libraries/Source/WWVegas/WWLib/stlport_deque_int.cpp`.
Imported forceinline specializations preserve the vendor integer-construction
operation and prevent those out-of-line copies from being emitted. Four units
also stop emitting an unused five-byte placement-new helper.

Target evidence is the canonical provider's matched ledger row, verified retail
bytes and the paired object/link checks. No new identity or layout is inferred.
`object-proof.json` records source/object hashes, retained bodies and removed
helpers for every consumer. All retained COMDAT bytes, extents, digests,
normalized complete relocations, ordinary sections, external bindings and hatch
counts are identical before/after. The canonical provider object is unchanged.

## Local acceptance

The index is SHA-256 `a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3`,
measurement commit `19a2565407` at 2026-10-15 09:33;
underlying census `5986a99448` at
2026-10-15 04:52. Paired before/after checks replace only these
owned consumer objects and the verified provider in memory; the on-disk index,
census/status and baselines are untouched. The selected canonical helper remains
unchanged. No full census, link cycle, nightly or smoke runner was started.

Bounded `link_check.py --prepare-current` prepared strict reusable compiler
receipts for all six sources, with normal byte verification 43/43. The explicit
`./build.sh` run also passes 43/43, four strings, seven float constants and all
imports, with zero skipped references. EH verification is 7/7 EXACT. Frozen-file,
class, new-variant, data/enforce and converged-global checks pass. Placement rescan
finds zero new bodies or pins. Restored MilesAudioCache separately passes 10/10.

These strict receipts establish object input currency. No self-strict placement
or closed-strict gain is claimed. Paired **legacy** checks remove exactly one
incorrect `_Construct<int,int>` blocker per consumer. The horde damage callback
becomes locally link-clean: **0 -> 538 existing retail bytes** (ledger extent
539 includes padding excluded by the link metric). The canonical provider stays
link-clean at 960 bytes. Combined explicit check: 960 -> 1,498 bytes, two of six
units clean. Zero new authored C++ bytes.

Remaining consumers and unrelated blockers are preserved verbatim in
`paired-link-after.txt`: InGameUIFloatingAnimation needs Anim2D::GetSnapshotName;
ChatWindowsLan needs its constructor/list-population providers plus tree/less
COMDAT repairs; SpecialAbilityUpdateRva0044FEB6 retains list allocator/node
COMDAT conflicts; Rva00474483ConfigureSlots retains map/vector conflicts and
rva004693D9. The combined link command exits 1 for these pre-existing blockers;
the paired proof confirms every blocker other than this helper is unchanged.

## Reference review and deferred sweep member

Reviewed BFME 1 donor checkout `a7c38d3b2597121f178ab5190b3062478823257d`
and repairs `d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`
(surplus constructor suppression) and
`4966496c5ae401ec877a044e1ae6dd04f9d9f65c` (inline forwarding suppression).
The emission-repair approach applies, supported independently by the target
objects; those donor source/layout changes are inapplicable to these consumers.
No donor code, headers or layouts were imported. The official reference fetch
found a newer tip; the reference-pointer freshness update is separately claimed
by `codex-6bc6-20261008`. This seat preserves the committed pointer and old success
stamp rather than advancing unverified inputs. Freshness verification remains due.

A sixth consumer, MilesAudioCache, failed the ordinary byte gate because
`uw_00760c03` names local `$L6948`, renumbered to `$L6939` after the otherwise
identical repair. All retained object code, full relocations, ordinary sections
and bindings remain identical; EH is 2/2 EXACT. See `audio-false-reject.json`.
The false rejection is logged, its source restored and its claim released; no
verifier, pin or ledger workaround was attempted. The only other indexed emitter,
Rva00396E4ARemove.cpp, is held by another worker and was not edited.
