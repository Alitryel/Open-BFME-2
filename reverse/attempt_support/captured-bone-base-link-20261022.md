# Captured-bone storage constructor link repair

Inputs: BFME2 parent 59f7442fa9, published census/index 08160bc2c9
(2026-10-22 17:08). No index, census status, ledger row, pin or tool changed.

## Target evidence and binding

The complete 175-byte copy constructor at RVA 0x166110 calls 0x162800.
The existing BfmePod36 size-constructor pin names that address and passes
pin_consistency.py --symbol. The address already has a verified 86-byte
STLport _Vector_base<Rva00162800Record> constructor in
StlVectorRva00162800.cpp. Its source and target arithmetic establish a
36-byte element and the same three-pointer storage layout; the allocator
is the stateless STLport allocator. This is a storage-constructor ABI
binding, not a claim that the two opaque element names are original names.
The captured-bone element layout is independently established by the
HTreeClass/Capture_Bone/Control_Bone witnesses in the existing copy row.

stlport_pod_vector_o2_bodies.cpp emitted a competing BfmePod36 constructor
which the index proves wrong at 0x162800. Declare that specialization only
and bind its existing spelling to the rowed constructor with /alternatename.
The captured-bone caller and all three rows of the provider stay byte-exact.
No function body or placeholder is added. Unreferenced COMDAT differences
remain untouched. The published index names exactly these two units as
blocked by this constructor; both now link. The real constructor owner
continues to link.

The semantic source is the existing pristine STLport 4.5.3 constructor.
The previously reviewed BFME1 pointer 37c3022de1ab944c7ffe536440d637dc8199091c
has no corresponding named split-out constructor/provider file to inherit.
No external reference input changed. The BFME1 HTree source remains a
hierarchy lead, not evidence of BFME2 element identity or bytes.

## Acceptance and measurement

Paired legacy link_check.py on the same three current objects and frozen
index, before and after:

| Unit | Before | After |
| --- | ---: | ---: |
| StlportCapturedBoneVectorCopy.cpp | 0 | 175 |
| stlport_pod_vector_o2_bodies.cpp | 0 | 122 |
| StlVectorRva00162800.cpp | 86 | 86 |
| Total | 86 | 383 |

Measured improvement: **297 linked bytes**, 1/3 to 3/3 units clean.
This is a legacy preview gain, not a closed-strict or published-census gain.
--prepare-current verifies all 5/5 rows with strict reusable receipts and
leaves index/status unchanged. Normal source gate 3/3, literal/import/float
checks, find_declared_unmatched, data_check (0 shadow findings), converged
data check (0 second names), and git diff --check pass. No new pin.

Local diagnostic logs and original source are retained under
build/eh-seat-20261022/pod36-*; these are reproducible diagnostics, not
required inputs. Remaining private BfmePod36 copy/insert differences are
independent causes; the prior B0478 visibility/frame blocker is not retried.
