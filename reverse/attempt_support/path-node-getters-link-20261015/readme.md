# Ground-path getter emission link repair

Base BFME2: `a1f9a8a5e81bd12e88b8eedfa7287982e5d5135b`. Frozen runner index:
`ac77c85054`, 2026-10-15 14:25; its SHA256 is recorded in proof.json.
Committed link_status.csv is discovery evidence, not a new measurement.

PathRva00363FA4.cpp now uses imported forceinline for its existing getNext and
getLayer expressions. This suppresses a surplus three-byte getNext COMDAT and
replaces the prior bfme_get_layer workaround with the original getter spelling,
removing its unused four-byte COMDAT too. No import reference, flag, header,
pin, alias, baseline entry, field, ledger row or native extent changes.

The existing 522-byte optimizer at 0x00363FA4 remains whole and byte-exact.
Its established target boundary, RET4 ABI, member accesses and calls are
unchanged. ZH Path::optimizeGroundPath semantics carried through the existing
BFME1 donor remain donor evidence; no new target identity is inferred here.
The optimizer's private PathNode next pointer is at +0; the indexed first
copy in AIGroupMoveFormation reads +8. Neither standalone getter has a retail
address. This repair preserves both enclosing native bodies and uses the
index's first-copy rule; it does not assert a common layout or reconcile all
private PathNode views. No retained relocation calls either removed helper.

## Paired evidence

Both sources have strict reusable receipts before and after. proof.py compares
all retained nondebug sections, flags, bytes, external bindings and symbolic
relocations, including local targets. They are identical. Strong, undefined
and weak name sets are unchanged. Six optimizer COMDATs remain; only the two
unused getter sections disappear. The 80-COMDAT AIGroupMoveFormation witness
object is byte-for-byte unchanged.

The same two objects replace the same positions in separate in-memory copies
of the frozen index. The optimizer loses its sole finding, 1 -> 0; its local
legacy preview changes from 0 to 522 existing linked bytes. The witness's nine
findings stay identical: unresolved adjustDestination, three duplicate
definitions and five losing COMDATs. Ordinary two-source link_check confirms
the result and exits 1 because that unchanged witness remains blocked.
An independent one-source check passes for the repaired optimizer.

The index has two getNext copies and one bfme_get_layer copy. This is its only
losing getNext consumer; the supported family is drained. No extra unverified
consumer or fabricated per-row data-back ranking is used. New authored C++
coverage is zero. Self-strict placement, closed-strict closure and full-game
linkage are unmeasured; no census/status/history was rewritten.

## Acceptance and reproduction

- Bounded --prepare-current: 3/3 rows across optimizer and witness, strict
  reusable receipts. Normal ./build.sh: optimizer 1/1, one compiler float,
  zero skipped/baselined string or import references.
- EH: one EXACT witness row, no nonexact, baselined or missing-object rows.
- Enforced data: zero findings. Converged-data enforcement: eight addresses,
  zero second names and zero unjudged rows.
- Class gate, declared-definition check, no-new-variants, CSV and whitespace
  checks pass. Optimizer placement rescan: zero bodies and zero pins.

proof.py uses the ignored sources.txt, before objects/receipts, source backups
and index-meta.json in build/path-node-getters-link-20261015. It verifies
strict current objects and the frozen index digest before comparing findings;
it never writes the index. proof.json records full paired findings and hashes.

## Donor review and remaining boundaries

Verified clean BFME1 gitlink/checkout remains
`a7c38d3b2597121f178ab5190b3062478823257d`. Reviewed repair
`66b19a8e95a4add525ef808fcea088e306798e2b`: imported forceinline suppresses
surplus copies without adding import relocations. This mechanism applies;
no Apt identity, layout or source body is transferred. The unchanged donor
revision was already reviewed by this seat; no unchanged broad scan was
repeated. Official master was fetched at
`95eeb3bef370a7cd730b0ad5f228c317c8756e72`. The overdue update remains
foreign-claimed, with comparative full verification outstanding. Verified
inputs and the old success stamp are retained without claiming freshness.

The file and optimizer RVA were claimed before editing; the unchanged witness
file was claimed before strict preparation. Discovery used repair_queue.py link,
link_rank.py help/near/kind/file evidence and a current-object link check.
No maintainer-only census, full link cycle, nightly, boot, scheduler or shadow
publisher was started. Broader linkage and class reconciliation remain separate
work; the witness's unchanged blockers are preserved in proof.json.
