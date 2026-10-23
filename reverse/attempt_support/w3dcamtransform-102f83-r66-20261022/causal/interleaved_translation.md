# Interleaved output translation: closed control

One semantic reconstruction probe of the same 4299-byte camera target. No donor
API identity is claimed. The local helper takes a Vector3 by value and the real
input context pointer, updates p.X then copies out.X immediately, updates p.Y then
copies out.Y immediately, and preserves Z through out.Z=p.Z. Both initial and
live translations use it; pitch and all other source expressions are unchanged.

WB 7E44C5..7E44F2 and 7E519D..7E51D6 establish sequential direct component
updates through input+4C/+50. They do not establish a returned-vector or
copy-in/out translation API. This probe tests the compiler mechanism only.

Ordinary result: 4291 bytes, fitness 0.8685425778, 57 relocations. The best input
value_reference is 4286 bytes / 0.9311709691. Normalized changed instructions
increase from 179 to 298. Tracing is read-only and exit 0; traced complete bytes
and relocations equal the ordinary object. `proof.json` contains command, hashes,
complete extent verification, scoped IR and actual SubsumePseudos writes.

| Principal long-lived component | References | Signed cost | Final allocation |
|---|---:|---:|---|
| sourcePos.X | 12 | +1 | xmm3 |
| sourcePos.Y | 10 | -7 | memory |
| sourcePos.Z | 17 | +11 | xmm4 |
| targetPos.X | 14 | +10 | xmm0 |
| targetPos.Y | 14 | +10 | xmm1 |
| targetPos.Z | 15 | +19 | xmm2 |

The intended aggregate ownership does not survive. At relative lines 50 and 56,
all four target translation copies again have a class-3 scalar source and
class-2 target field destination. SubsumePseudos accepts them in direction 1 and
rewrites the load/ADDSS chain to the target field descriptor. The desired
10-reference/-6 target ranges become 14-reference/+10 ranges. A source-level
by-value parameter plus three real component copies is therefore insufficient
to preserve value_reference's anonymous arithmetic owner.

The context pointer restores native EBX+50 addressing, but no immediate stores:
ordinary +50C and +523 use [ebx+50], then all four XY stores cluster at
+536/+53B/+540/+545. Native first translation stores X at +515 before loading Y
at +51A, then writes Y at +52C. The probe closes this interleaved copy-in/out
route; do not repeat it as an alias or store-order fix.

Reproduce ordinary compile with `python build/camera-causal-20261021/interleaved_translation.py`,
read-only trace with `python build/camera-causal-20261021/trace_interleaved_translation.py`,
and compact proof with this directory's `summarize.py`. Legacy compiler launch
requires the usual authorized native execution. All outputs are isolated here.
