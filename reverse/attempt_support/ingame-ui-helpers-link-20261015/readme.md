# Inline helper emission repair, 2026-10-15

Base BFME2: c278241c038c54c0b91c9747916da122d34de510. Frozen runner
index: ac77c85054, 2026-10-15 14:25; SHA256 in proof.json. The committed
link_status.csv and repair queue were discovery evidence, not a new census.

InGameUIMessages.cpp now suppresses the unused standalone fast_float_floor
copy with imported forceinline. Its eight localized font tests call the
same StringBase<char>::isEmpty predicate that the AsciiString header wrapper
already used. The visible predicate remains available to the optimizer;
retail's out-of-line isEmpty calls and register allocation are preserved.
The unused AsciiString and StringBase isNotEmpty forwarding copies disappear.
The latter was already a retail-exact copy; only the former was losing.

The compatible rounding-wrapper sweep applies imported forceinline to floor
and ceil in PathfindLayerAllocateCells.cpp too. Neither removed wrapper has
an incoming nondebug relocation, and no import reference is introduced.
All retail body boundaries, ABI, fields, native call targets, flags, headers,
pins, aliases, ledger rows and baselines are unchanged. These are emission
repairs, with no new target identity or layout claim. Existing ZH donor
semantics remain donor evidence; exact target bodies establish the preserved
behavior and bindings independently.

## Paired local evidence

proof.py binds each frozen before source and object to its version-2 receipt,
checks that command, dependencies and include-search inventory agree with the
strictly current after object, and verifies the frozen index digest. It
compares every retained nondebug section, flags, bytes, bindings and symbolic
relocations. These are identical except that the UI object's SafeSEH input
list swaps init/recreateControlBar order; its handler multiset is identical
(the linker sorts it by RVA). No retained relocation targets a removed helper.
Strong, undefined and weak name sets are unchanged. The unchanged 54-COMDAT
string_base_inline.cpp witness/provider is byte-for-byte identical.

Separate in-memory copies of the same index replace the same three object
positions for before and after. No on-disk index, status or history is written.

| Unit | Legacy findings before -> after | Remaining finding |
| --- | ---: | --- |
| InGameUIMessages.cpp | 3 -> 1 | wrong size-built wide getCharAt copy |
| PathfindLayerAllocateCells.cpp | 3 -> 1 | unresolved PathfindCell destructor |
| string_base_inline.cpp | 0 -> 0 | none |

Exactly four losing-COMDAT findings disappear. Every other finding is
identical. The source-byte measure is 5,080 existing authored UI bytes, 674
allocator bytes, and 3,011 provider bytes. Legacy linked bytes stay 3,011;
new authored C++ bytes and newly linked bytes are both zero. Strict reusable
receipts establish object freshness, not self-strict placement or closed-strict
closure. No self-strict, closed-strict or full executable-link gain is claimed.
Ordinary three-source link_check confirms the remaining findings and exits 1.

## Checks

- Bounded strict preparation and normal build gates: 101/101 rows across three
  units, including the allocator's complete 678-byte extent. Four strings,
  fourteen empty-string references, eighteen floats and thirty imports verify;
  none baselined or skipped.
- EH: 13 EXACT, zero nonexact, baseline or missing-object cases.
- Enforced data: allocator/provider clean; UI retains the same two pre-existing
  wrong-name diagnostics for subtitle guard 0x009FEEA8 and click 0x009FEE20.
  Nondebug-section and binding comparisons show these are unchanged.
  Converged-data enforcement: eight addresses, zero second names or unjudged rows.
- Declared definitions, class gate, no-new-variants, CSV and whitespace pass.
  Placement resweeps: zero new bodies or pins for either repaired unit.
- Source/file and affected RVA claims were acquired before edits. The unchanged
  getter provider was claimed for bounded preparation. No maintainer-only
  census, link cycle, nightly, boot, scheduler or publisher was started.

Snapshots and receipts live in ignored build/ingame-ui-helpers-link-20261015;
proof.py replays against those snapshots and the frozen index. proof.json
records hashes, full findings, removal digests and the index's helper families.
The other indexed floor copies in PartitionManager, Weapon and W3DModelDraw
no longer have this helper spelling in current source. Other AsciiString
copies use a different predicate body; the UI-specific visible StringBase
specialization does not support blindly applying its font-test change there.

## Remaining blockers and donor review

Two getCharAt trials were rejected by the normal byte gate: deleting the local
definition, then keeping it with extern template, both changed register
allocation and the compiler's static-helper convention in getLineWidth and
subtitle callers (three failures out of 48). Both were reverted. The original
getter definition remains unchanged. re_attempts.log records the wall so a
later seat can investigate codegen-preserving canonical emission rather than
repeat those trials. The allocator's destructor binding is separate work.

The verified clean BFME1 gitlink/checkout remains
 a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor repair
66b19a8e95a4add525ef808fcea088e306798e2b supports imported forceinline to
suppress surplus copies without introducing import references; no donor Apt
identity, layout or address was transferred. Official master was fetched to
95eeb3bef370a7cd730b0ad5f228c317c8756e72. Its overdue update is foreign-claimed;
comparative verification remains outstanding. Verified inputs and the old
success stamp are retained without claiming freshness.
