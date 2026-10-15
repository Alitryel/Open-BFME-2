Particle handle destructor link repair

Base checkout: 97992c26abd9a961490197975d2c5a6b94a385a4.
Discovery: repair_queue.py link, then link_rank.py --kind L --near 1.
The local index measures 19a2565407 (2026-10-15 09:33), based on census
5986a99448. Its exact hash and before/after findings are in object-proof.json.
The committed status instead measures 28269d8e8d; it is discovery evidence,
not the basis for this paired result. Fetch kept the newer local index.

ParticleBaseConstructor.cpp was the only indexed emitter of a divergent
RvaSmartPtr12 destructor. Its 11-byte body had the correct null test but
tail-called the guarded BfmeParticleSystemHandle destructor at 2115C5.
The other fifteen indexed copies tail-call the non-null unlink at 4CBC0.
The existing destructor row in FXParticleSystem/Rva0055F840Ctor.cpp proves
the complete 11-byte body and relocation; ParticleSystemHandle_dtor.cpp
owns the 55-byte unlink. The BfmeParticleSystemHandle pin also explicitly
distinguishes the guarded destructor from that unlink. Calling the guarded
spelling from another guard tests the pointer twice and makes the emitted
COMDAT fail retail selection.

Declare and use the existing unlink directly under the existing null test.
Remove the now-unused BfmeParticleSystemHandle declaration. No flags, layout,
global, pin, ledger row, baseline or census data changes. The two provider
files were claimed and prepared read-only; their source remains unchanged.

Acceptance:

- Before/after link_check.py --prepare-current on the consumer, unlink owner
  and destructor owner: 13/13 matched rows, strict reusable current receipts;
  string, float and import reference checks pass without skipped references.
- ./build.sh on the consumer: 3/3 exact, including its two generated unwind
  rows. EH verification before and after: one parent graph, EXACT.
- Object comparison: all retained nondebug sections, instructions, extents,
  flags and symbolic relocations are identical after substituting only the
  destructor's old callee name with the existing unlink name. The helper's
  bytes remain 8339007405e900000000c3; its sole relocation now matches the
  rowed destructor owner. The other five emitted COMDAT bodies are unchanged.
- Separate in-memory refreshes of the strict-current before and after
  objects against the same index: consumer COMDAT findings 1 -> 0;
  legacy linked bytes 0 -> 260. Both current providers link in both cases,
  with identical findings. The selected helper provider does not change;
  sixteen indexed copies converge from two digests to one.
- The ordinary three-file local preview agrees: 3/3 link, aggregate existing
  linked bytes 490 -> 750. New-COMDAT-variant admission passes.
- Enforced data and converged-data checks: zero findings, zero second names.
  Class, declared-definition, CSV and whitespace checks pass. The affected
  placement resweep finds zero bodies and zero pins.

This is self-strict byte acceptance and a LEGACY local link prediction.
New authored C++ bytes are zero. No closed-strict gain, executable placement
or runtime result is claimed. No maintainer-only runner was started.
Before objects, dependency receipts, source snapshot and the section/paired
proof script remain under ignored build/particle-base-unlink-link-20261015.

Reference review: retain verified BFME1 a7c38d3b2597121f178ab5190b3062478823257d.
The dedicated-pass reviews of donor inline/provider reconciliations
4966496c5ae401ec877a044e1ae6dd04f9d9f65c and
de59a7e9 are reused; the real-provider principle applies, while removing
this referenced destructor would be inappropriate. The donor data-owner
repair 92a8d854746f059994f8ab370c133f3ba71eec24 was also inspected this
session; it does not supply this handle's identity, layout or call contract.
Those facts come from the existing BFME2 rows and retail relocations above.
No donor source or dependency is imported. Official master fetch finds
f76203cb023f923b97cd8687679ea29ef121d875; another worker holds
file:reference/open-bfme-1 and the comparative full-verification/pointer
update remains outstanding. No freshness success stamp is written.

Other triage: current WWDebug singleton/console, pristine-bone, AI getter,
hero-pointer, reinforcement and river-parser units already have their old
queue blockers repaired. Damage-neighbor parsing still conflates a 44-byte
string-vector record with ManTheWalls' 16-byte object-vector record under
Rva004BA1B2. Its blocker was recorded without editing or inventing a fold
pin; a safe repair needs a distinct record identity and constructor-fold
proof. Other claimed files were left to their owners.
