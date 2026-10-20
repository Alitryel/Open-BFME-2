# Vector placement-copy ownership

Inputs: BFME2 `54a521e457`, BFME1 verified pointer
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`, census/index
`5366c4f808` (2026-10-20 12:21, retail-truth-2). No census rebuild,
full link cycle, pin, header, ABI, or ledger change.

Two size-only STL element views emitted incorrect POD placement copies:

| Consumer | Row | Existing native provider | Paired LEGACY linked bytes |
| --- | --- | --- | --- |
| stlport_vector_rva00287f76_overflow.cpp | 00287B4D, 184 B | Rva002861B0Copy, 002861B0 | 0 -> 184 |
| stlport_vector_rva00336aec_overflow.cpp | 003361C6, 189 B | Rva00333295Construct, 00333295 | 0 -> 189 |

Native call displacements and the existing recovered provider bodies establish
the bindings. The first copies six bytes within an eight-byte stride; the
second constructs a 36-byte owning record through its existing copy ctor.
Neither address-derived element spelling establishes the application type.
Visible inline-only forwarding specializations preserve those native calls
while eliminating the incorrect competing POD copies. The extent/layout
claims remain those of the existing provider rows.

The BFME1 visible-body/unique-owner linking approach (donor repair
51b97cd796424d985cf533e1676f64915b8f1a75, reviewed at the verified pointer)
is applicable as compiler technique; the two bindings come from BFME2 evidence.

Checks: ordinary byte gates 2/2, self-strict prepare-current receipts 4/4
including both providers, find_declared_unmatched clean, check_csv clean.
Same unchanged index and current touched objects before/after: neither
consumer linked before; both link after, +373 nonpadding existing retail
bytes. This is a LEGACY local preview, not closed-strict or a full link result.
No authored C++ byte growth is claimed.

The same session tried two separate candidates and restored them completely:

* BfmePod36 fill_insert 000B0478: declaration-only Construct/overflow loses
  visible callee information, grows the caller frame 24h -> 28h and adds
  false-type initialization. Byte gate refused; no link gain.
* Gen_p12pod insertion 0016DBC0: its three indexed Construct definers share
  wrong digest cd8ab5d1af74. Removing all copies leaves the typed Construct
  unresolved (native16CC80 is owned by W3DRopeDraw::SegInfo); the map117B
  caller also changes zero-store scheduling. Needs provider/visibility
  reconciliation. No removal-only repair retained. Claims released.

Those blockers are recorded through re_log.py. The BFME1 upstream refresh
is owned by another live file claim; verified donor inputs were preserved.

Rebase reconciliation: upstream b70b5a39e9 independently landed both vector
bindings before this batch was published. Keep upstream's exact source and
count zero additional vector bytes for this seat after rebasing. This commit
retains the diagnostic handoff only. That upstream commit also resolves the
Gen_p12pod provider-copy prerequisite described above; the earlier restored
trial is historical evidence, not a reason to defer the now-repaired tree.
