# Vector placement-copy identity retirement

Inspected upstream revision: `1cd28a3a88`. The default picker served the
identity key for `stlport_vector_rva00287f76_overflow.cpp`, row 0x00287B4D.

The whole source already forwards its visible inline `_Construct` specialization
to the existing `Rva002861B0Copy` owner at 0x002861B0. The earlier repair and
its native call evidence are recorded in
[the placement-copy handoff](vector-copy-owner-link-20261020-seat8/readme.md).
That provider copies six bytes within an eight-byte element stride; the
address-derived element name remains provisional.

No source, symbol pin, function row or verifier was changed. The remaining
register key still described the former incorrect `_Construct` binding.

Current checks:

- `find_declared_unmatched.py` reports all defined functions matched.
- Normal `build.sh` passes both rows: overflow 0x00287B4D (184 bytes) and
  push_back 0x00287F76 (55 bytes), with all reference checks passing.
- `repair_queue.py retire identity` passes its current-object and provider
  checks, removes the one stale key, and reports zero keys still found for
  this source. The register was changed only by that tool.
- The committed census already records this unit as linking. Retirement
  claims one less identity-debt key and no additional matched or linked bytes.
