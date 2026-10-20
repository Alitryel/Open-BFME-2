Byte-vector visible growth helper
=================================

Input: BFME2 8c52ecd989; BFME1 verified pointer 92f6bbe8e1dc.
Published census/index: 5366c4f808, 2026-10-20 12:21, retail-truth-2.

StlContainerRva000AFE9F.cpp had one non-retail COMDAT: unsigned-byte
vector::_M_insert_overflow. Its native 136-byte owner is already matched
at 0x000AFB2E in stlport_pod_vector_bodies.cpp. The target-backed owner
uses the unsigned-byte fill helper, a zero-allocation guard, trivial copies
and checked free. The element signedness remains the donor spelling,
not a new claim about an application type.

Earlier declaration-only/extern-template attempts lost visible callee effects:
the 179-byte fill_insert exchanged EBX/EDI and materialized the POD tag,
exceeding its extent. A local declaration reproduced that wall here.
The successful, different repair reuses the complete existing native growth
specialization as inline C++, retaining its visible effects and emitting a
retail-equivalent COMDAT. Both caller rows remain exact. No new identity,
pin, row, alias, global or compiler switch is needed. No reference decoder
source was read; this copies the existing BFME2 retail-verified implementation.
The donor linking review covered BFME1 d2e213690's analogous local visibility
repair; no BFME1 layout, code or address was imported for this change.

Paired current-object legacy link_check against the same published index:

  StlContainerRva000AFE9F.cpp: 0 -> 184 LINKED bytes, 1 -> 0 findings.

This is a legacy prediction, not a self-strict or closed-strict executable
placement result. Strict reusable receipts establish input currency and full
row bytes. No census, full link cycle, nightly or boot runner was started.

Acceptance:

* Strict bounded prepare-current before and after: 2/2 rows exact,
  no strings, float literals or named imports.
* Native provider ./build.sh: 151/151 rows exact, no literals or imports.
* EH: zero rows with EH data, no missing object.
* Frozen-source and class gates pass. Data shadow: zero findings;
  enforced converged-data check: ten addresses, zero second names.
* place_bodies: zero bodies, zero pins. The blocker index has no other
  consumer of this exact conflicting unsigned-byte helper.

Diagnostics: build/link-seat-bytevector-{before,before-gate,trial}.txt,
*-visible-{trial,after,gate}.txt, *-provider.txt, *-eh.txt and *-place.txt.
