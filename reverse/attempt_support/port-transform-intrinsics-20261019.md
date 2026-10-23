# BuildAssistant port transform: intrinsic/profile follow-up

Target 00392802..00392AD7, 725B, WB F9B980. The existing bank reproduces
725B in the current BuildAssistant.cpp with visible native Coord3D length
and normalize bodies. Its first difference remains +CE: nine SSE scheduling
instructions in the centroid normalization. Its volatile casts are diagnostic
and were not promoted into production.

Inputs: BFME2 5dc0a19ac8, BFME1 a18d9ed50607e9175de4d6568798d7d73119de09.
The full current owner has no undeclared definitions. Existing source flags
and the bank transplant reproduce the previous baseline.

New hypothesis: scalar SSE intrinsics could express the native calculation
without the bank's volatile casts. `_mm_load_ss`, `_mm_div_ss`, `_mm_mul_ss`
and `_mm_store_ss` preserve scalar arithmetic, but MSVC introduces 16-byte
stack realignment. An __m128 reciprocal emits 890B; a scalar reciprocal with
only expression temporaries emits 873B. Both differ at +4. This does not
provide a usable source shape; unaligned scalar memory accesses do not
prevent the compiler from realigning the frame for its vector temporaries.

New authenticated compiler inputs 13.10.4035 and 13.10.6030 each reproduce
the unchanged 725B bank and +CE residue. Removing volatile casts under either
profile gives 712B and a difference at +A3. No improvement was banked and
no Code, data or pin edits were made. The better existing bank remains intact.
Resume with a new supported source/compiler hypothesis, not these trials.
