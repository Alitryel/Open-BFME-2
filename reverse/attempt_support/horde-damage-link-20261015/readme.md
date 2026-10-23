Horde damage callback link repair

Base checkout and exact index hash/metadata are in object-proof.json. Discovery
used repair_queue.py link and link_rank.py. The available local index measures
19a2565407 (2026-10-15 09:33), derived from census 5986a99448; committed
link_status.csv instead measures 28269d8e8d (09:31). Paired checks use only the
same local index, replacing this explicit object in memory. No census, status,
history, ledger, pins, baseline, shared headers or compiler flags changed.

The affected consumer is HordeTransportContainDamageCallback.cpp, one 539-byte
row at RVA 0x004BB176 (538 scored bytes after padding). Before editing,
--prepare-current supplied a strict reusable receipt and passed the ordinary
byte/reference gates. Its local link preview reported only the non-retail
17-byte _Construct<int,int> COMDAT. That helper has no incoming nondebug
relocation. The callback's integer placement construction is already inlined.

Use a file-static placement-construction overload, following the existing
XferListInt.cpp/Rva00460216XferList.cpp pattern. Its private compiler-generated
9-byte copy has no incoming nondebug relocation and introduces no external
definition. It is not a newly recovered retail body. All other nondebug
sections retain their bytes, flags, external leaders and symbolic relocations,
including the complete matched callback. All 35 retained COMDAT bodies agree
with their pre-edit copies. The shared helper's selected provider remains
stlport_deque_int.obj, digest 1f973cbdcb23, independently retail-proven; its
indexed family loses this one wrong copy (15 -> 14). Other consumers continue
to resolve the same provider.

Acceptance:

- ./build.sh and --prepare-current pass 1/1 rows, one compiler float reference,
  and all applicable string/import checks, with a strict current receipt.
- The bounded whole-object proof checks both unreferenced helpers separately
  and preserves all other nondebug bytes and symbolic relocations. Same-index
  findings change from one wrong COMDAT to none; LEGACY linked bytes 0 -> 538.
  --new-variants passes with no new harmful external COMDAT variant.
- Frozen-definition, class, converged-data, CSV and whitespace checks pass.
  place_bodies.py finds zero additional bodies and zero pins.
- This is self-strict byte verification plus a LEGACY local link prediction.
  No closed-strict gain, link.exe placement, or runtime result is claimed.
  Authored matched C++ growth is zero. No maintainer-only runner was started.

Donor review: verified BFME1 pointer remains a7c38d3b2597121f178ab5190b3062478823257d.
Official origin/master was fetched read-only at 75ff0c1485a68eafb10344670711edbee8679b62.
Donor repairs 4966496c5ae401ec877a044e1ae6dd04f9d9f65c and
6b9800e65dc6f0e7e4660ac55f27b44094f9e590 establish the surplus external
inline-wrapper pattern. That technique applies, with BFME2 bytes/relocations
proving this repair. No identity, layout, donor source or header is imported.
Another worker owns the submodule claim; the documented comparative-full-gate
freshness blocker also remains. Keep verified inputs; no freshness success
stamp was written.

Other queue triage: waypoint lookups, map-list refresh, GapBodiesSeat1B,
AnimationSoundClientBehavior and GeometryUpgrade already pass current local
previews despite census listings. Rva0042CB81's selected wrong constructor
comes from the peer-held W3DDisplayGatherAnimationDebuggingInfo.cpp; leave it
to that owner. RebuildHoleExposeDie/FireWeaponUpdateBehaviorDtor still require
secondary vtable providers. AptRowListCallbacks/DumbProjectileBehavior have
multiple unresolved/COMDAT dependencies and prior deferrals. No unsupported
identity or provider rewrite was attempted.

WeaponTemplateTargetPositions.cpp has a separate lexical address false reject:
0xBC614E is the scalar RNG upper bound 12345678, not a data pointer. Its local
preview reports only that value. Recorded with re_log.py for a tooling seat;
neither the correct source nor the check was changed to bypass it.

proof.py reproduces the bounded comparison and paired preview using preserved
source/object/receipt snapshots in build/horde-damage-link-20261015/before.
Checked output and the portable result JSON are committed here.
