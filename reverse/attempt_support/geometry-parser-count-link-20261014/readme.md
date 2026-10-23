# Geometry parser count link repair

Source base: ac03bb88ef7434374b15081f94173b465f5b2c29.
Actual paired measurement index: 147cfae2cb, 2026-10-14 07:27;
SHA256 690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Committed link_status.csv at 67e1365aa9 is discovery evidence only. No census,
status, history, receipt or per-row data-back artifact was updated.

GeometryParseActiveAndOffset.cpp inlines vector<GeometryShape>::size but
also emits its 25-byte COMDAT (digest 0b7a2f26297a). The index keeps the
12-byte same-name body from StlportVectorInsertOverflowFamily.cpp (digest
af999157e466). Both divide by 0x24: this is a compiler-shape conflict, not
an established layout disagreement. The current byte-verified provider
reproduces its indexed digest. Neither standalone count has a retail address.
The original consumer is a later, losing copy; its removal cannot change the
selected generic provider. Other indexed copies already agree with that keeper.

Use an implementation-local vector subclass with no additional fields to
spell the inherited-pointer count as shapeCount. The existing element type,
allocator, representation and signed pointer subtraction/unsigned result are
preserved. The parser member uses this derived range; inherited back() remains
unchanged. This is an implementation helper, not a new retail identity or class
layout claim. No alias, pin, shared header, compiler flag or global was added.

Target evidence: the whole native parseGeometryActive body at
0x006BD590..0x006BD5CD (61 bytes) and parseGeometryOffset body at
0x006BD610..0x006BD650 (64 bytes) still byte-match, including relocations and
full extents. The parser's count uses stride 0x24. The existing ledger preserves
BFME 1 donor provenance and callee/fold discrimination; the original source
records BFME 1 FieldParse table evidence for the donor identity. This repair
adds no independent target naming assertion and imports no donor code.

Acceptance:

- link_check --prepare-current: consumer before and after 2/2 exact; final
  consumer/provider pair 62/62 exact with strict reusable compiler receipts.
  Ordinary ./build.sh consumer: 2/2 exact, zero string/float/import refs skipped
  or baselined. No failed byte builds.
- Object proof: every nondebug section, directive, extent and relocation,
  plus strong/undefined/weak bindings, is identical after normalizing only
  the helper name. All four retained COMDATs agree; the renamed helper is an
  exact 25-byte twin, including its complete relocation facts (none).
- Paired same-index local legacy preview substitutes saved before/current
  after consumer objects together with the same strict-current provider:
  one losing COMDAT -> zero findings, LINKED 0 -> 125 existing bytes.
  Provider findings are unchanged (35 U, 1 D, 10 L, 12 S). The new helper has
  no other indexed provider. Consumer CLI independently reports LINKS.
- Frozen definitions, class gate, new-variants admission, whitespace, CSV,
  converged data (eight addresses, zero second names), shadow data (zero
  findings), and EH (zero EH rows, zero missing objects) pass.
- Affected consumer placement resweep: zero bodies and zero pins.

Self-strict compiler currency is proven. LINKED gain is legacy local preview
only: closed-strict dependency closure, actual link.exe placement and fresh
census gains remain unmeasured. Authored C++ growth is zero. The selected
provider retains broader unresolved, duplicate and COMDAT debt. No maintainer
verification runner, census build/measure/history, nightly or boot was started.
Reproducible proof scripts, original source/object/receipts and the unchanged
measurement index remain under build/geometry-parser-count-link-20261014.

Reference review: committed verified BFME 1 pointer
23b143233b5a8664a3bdf8572df6d905c310a5a1. Reviewed donor repair
de59a7e9f891b3ed2d4221d151ca881f4b75a583: reconcile surplus inline emissions
while preserving byte-exact parents. Applicable as a repair principle; its
Apt expressions and layouts are inapplicable here. Fetched official master
(a7c38d3b2) for the required freshness comparison. Another worker holds
file:reference/open-bfme-1, so its comparative full-gate pointer update remains
with that owner; verified inputs were preserved and no success stamp was written.

Lane probes: repair_queue link; link_rank top/near and sole L/S candidates.
Previously repaired getDrawModules, locomotor goal, quick-match count and
Horde radius conflicts were skipped after their recorded evidence was read.
name_globals --dry-run retained zero changes. rehome_rows --limit 12 was
stopped during its read-only scan after independent positive leads appeared;
it did not exhaust the lane or apply changes. No blocked task was retried.
