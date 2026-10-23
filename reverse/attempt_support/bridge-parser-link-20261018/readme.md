Bridge parser link repair, 2026-10-18

Paired legacy link_check on the two callback units, their current BridgeBehavior.cpp peer and the existing BridgeBehaviorListValueCopy.cpp provider: 84 -> 444 linked bytes (+360). The peer remains blocked; the gain is exactly FX 190 and OCL 170. The published index is c2c5ac8c27; passing current peers prevents claiming the older duplicate parseOCL removal as a new gain. No closed-strict gain is claimed.

Target evidence already recorded with the callbacks and list rows establishes the common 12-byte pointer/delay/AsciiString payload (offsets 0/4/8) and native copy chain 4570DD -> 456E70 -> CF475. Each callback now routes its inline _Construct specialization to the existing neutral BridgeBehaviorListValue12 helper, rather than leaving a second semantic name unresolved. The neutral application class identity remains unknown; BFME1 semantic names and addresses remain donor provenance, not new target identity claims. No new pin or linker alias is added.

OCL also uses the same explicit TimeAndLocationInfo constructor/destructor and constructor optimization context already verified in FX, producing the rowed 10-byte constructor at 154300. The former implicit constructor lost to retail.

Acceptance: all 4 existing rows byte-match, both explicit providers have strict reusable receipts (self-strict only, closure not checked); EH 2 EXACT; converged data 2 sources, 9 addresses, zero second names or unjudged rows; enforced data check zero findings; find_declared_unmatched passes both sources; check_csv passes. Baselines unchanged.
