# Array delete dependency repair

BFME2 base: `81f74027847f3a700d1e40dd4fd59d9c33176e70`.
Four consumer units now call the existing global array-delete provider directly.
The unused bfmeFreeRC declaration is removed from BfmeConv908. All six remaining
mem_ops alternatename directives, their six symbols.csv pins and their six keyed
hatch-baseline entries are removed; the two address-keyed pin counters shrink
by the six removed pins. bfmeFreeArrayTXA and bfmeFreeTXA already have
no source users; the other four names are replaced throughout their consumer
units, including the two existing present-unmatched BfmeConv943 siblings.
No definitions, rows, extents, flags, headers or class identities are added.

Target evidence: native-calls.json records every affected matched REL32 operand.
BfmeConv909 (00016B60/36), BfmeConv1393 (00197F30/73),
BfmeThreeHundredFiftyThree (0061ED80/17) and BfmeConv943 (001A7F20/70)
all reach RVA 0002FD80, the existing 21-byte `??_V@YAXPAX@Z` provider in
WWLib/mem_ops.cpp. This establishes the binding independently of the removed
pins. The opaque receivers, layouts and donor provenance remain unchanged.

Acceptance:

- Normal byte gate: 11/11 matched rows across six sources; no baselined or
  skipped string/import references. Before and after bounded preparation also
  passes 11/11 with strict reusable compiler receipts for all six units.
- object-proof.json compares all non-debug, non-directive sections, their
  flags, sizes, raw bytes, relocation offsets/types/canonical referents,
  external definitions and canonical undefined references. Uninitialized BSS
  compares as zero storage. All equal after exactly the six alias substitutions.
  This includes complete emitted sibling bodies beyond the matched rows.
  The provider's directives change only by the six removals.
- Data shadow: zero findings. Enforced converged-data: eight addresses,
  zero second names or unjudged rows. EH: no applicable tables, nonexact
  rows or missing objects. Class, case-collision, declared-definition,
  CSV, pin-consistency and whitespace checks pass. Placement rescan: zero
  bodies, zero pins. Existing present-unmatched markers are retained.
- The available index measures cb660e4d97, 2026-10-13 04:02 UTC; its hash
  appears in object-proof.json. The committed queue at 67e1365aa9 is discovery
  only. Both previews refresh the same six current objects together in memory.
  Four units link before and after, totaling **219 -> 219 legacy linked bytes**.
  BfmeConv1393 remains blocked on g_bfmeVftBVJS. BfmeConv943 retains its four
  pre-existing unresolved F/G sibling vtables; expected preview exit is 1.
- Verified improvement: **six fewer aliases and six fewer pins**, with no
  new authored bytes. Strict receipts establish byte/current-object evidence,
  not self-strict placed linkage or closed-strict closure. No closure gain is
  claimed. Census/status/history are unchanged; no full link cycle, census
  build, nightly or smoke runner was started.

Donor review: official BFME1 master fetched and compared at
23b143233b5a8664a3bdf8572df6d905c310a5a1. Reviewed new linking repair
fea964f85433012ec0c95a44a8d88f77b4c29af5: replace invented allocation/free
stand-ins with direct global operators, remove unused pins. Applicable repair
principle; no donor bytes, layout, ABI or addresses were imported. Target
operands and the unchanged complete objects establish the local adaptation.
The clean verified checkout/gitlink remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
The overdue comparative full-byte freshness update remains held by the live
foreign file:reference/open-bfme-1 claim (yasinschroeder-claude2), with the
previous shared-compiler/stale-dependency verification still outstanding.
No pointer or success timestamp was changed.

Discovery: repair_queue.py link; link_rank.py help/top/near, address and
selected-definition rankings; current source and historical evidence.
Already-repaired ranked dependencies and the recorded SRCCOPY false reject
were not retried. The staged hatch check reports only pre-existing shadow growth;
this repair adds none and lowers its eight affected keys by twelve counts.
All six files and eleven retail row addresses were claimed
before editing. Scratch audit script and before-source/object snapshots are
preserved at build/array-delete-link-20261014.
