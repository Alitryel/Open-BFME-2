BuffNugget constructor literal/link repair

Base checkout: ee54d2de73250053617a6dec0fcf967e917cbeba. Discovery used
repair_queue.py link and link_rank.py --kind A. The committed link_status.csv
measurement is 28269d8e8d (2026-10-15 09:31); the available local index instead
is 19a2565407 (09:33), derived from census 5986a99448. Paired evidence uses
only the latter, with its exact SHA256 recorded in object-proof.json. No
index, status/history, ledger, pins, baseline, headers or compiler flags changed.

The sole affected consumer is BuffNuggetFXNuggetCtor.cpp (333 matched bytes).
Its 295-byte constructor read color defaults through three hard-coded image
addresses. Retail data independently supplies float32 bits cdcc4c3e at
VA 0x00BC4DD8 (0.2f), cdcccc3e at 0x00BCAE8C (0.4f), and 0000803f at
0x00BBB8D8 (1.0f). Replace the casts with these C++ literals. Identity, class
layout and purpose remain those already established by the original donor
and target FieldParse evidence; this repair adds no identity/layout inference.

Acceptance:

- Before editing, --prepare-current byte-verified all three rows and supplied
  a strict reusable object receipt. The local preview reported only three
  hard-coded-address findings and 0 linked bytes. Source/object/receipt
  snapshots are preserved under build/buff-color-link-20261015/before.
- ./build.sh passes 3/3 rows (295-byte constructor, 28-byte deleting destructor,
  10-byte EH handler), the string reference, four compiler float references,
  and import checks. --prepare-current repeats those checks with a strict
  reusable receipt. No literal or import references are skipped.
- Constructor COFF bytes differ only at offsets 219, 235 and 251: three absolute
  address operands become DIR32 references to the matching __real literals.
  The other 15 existing COMDAT bodies are identical. A normalized complete
  object comparison, excluding the separately checked constructor and two new
  literal sections, preserves all remaining nondebug sections and symbolic
  relocations. Compiler-local EH labels are compared by target section/offset
  and payload because their generated numbers change. EH verification is EXACT.
- New literal sections have the exact target bits. All indexed copies of
  their compiler symbols agree: 30 copies of 0.2f, 18 of 0.4f, and 873 of 1.0f.
  There is no new harmful COMDAT variant or changed existing provider body.
- Paired previews refresh only this explicit object in memory against the
  identical index. All findings disappear: LEGACY linked bytes 0 -> 333,
  authored C++ byte growth zero. Ordinary link_check.py also reports LINKS.
  This is a self-strict byte check plus a LEGACY local link prediction, not
  measured closed-strict closure or link.exe placement/runtime verification.
- Frozen-definition, class, converged-data, EH, CSV and whitespace checks pass.
  place_bodies.py reports zero additional bodies and zero pins. No matching
  volatile-const float-address pattern remains in GameClient; the broader
  GameEngine source search found no additional exact-pattern consumer.

Reference review used the clean, unchanged verified BFME1 pointer
 a7c38d3b2597121f178ab5190b3062478823257d. Donor repair
69c0b4b3155793989b2dae71584f37262a9f7d16 replaces a hard-coded lighting
constant with a compiler literal while preserving its target body; that
technique is applicable here, with BFME2 data and bytes proving these values.
Other reviewed donor repairs 4966496c5ae401ec877a044e1ae6dd04f9d9f65c and
6b9800e65dc6f0e7e4660ac55f27b44094f9e590 concern surplus wrapper/COMDAT
emission and were not needed for this repair. Official BFME1 master fetched
read-only at e27a65cb6bd7b2b3cc8ee320ef7ef8a3797b1d0e. Another worker holds
the submodule file claim, and the earlier comparative-full-gate freshness
blocker (thousands of stale units/compiler stalls) remains documented by the
previous session. The verified pointer was retained; no success stamp written.

Other triage: current AIIdleStateUpdate, AIAttackApproachTargetStateOnExit,
Rva000C4069PristineQuery, Rva003FE05E and Rva005E1928HelpUpdate already pass
their local link previews despite stale census listings. The Apt counted-key
destructor still differs from PlaybackBufferResize's first indexed copy;
no unsupported ownership rewrite or previously deferred reconstruction was
attempted. Top missing-function work remains for the appropriate conversion
seats. name_globals.py --dry-run found no applicable rewrite in the three
explicit address-blocked files examined. No maintainer-only runner started.

proof.py reproduces the operand/data, complete remaining-object invariants,
and same-index paired preview from preserved build/ snapshots. Checked outputs
are committed here. Release the file claim after committing the repair.
