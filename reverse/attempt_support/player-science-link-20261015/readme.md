PlayerAddScience unused COMDAT repair, 2026-10-15

At source base 9198fa5cc32e6b03689ed2b9b73dc5d05ff6c71b, the current
PlayerAddScience.cpp had two COMDAT blockers against the runner's legacy census
at ac77c85054 (2026-10-15 14:25). Suppress their unused external copies with
TU-local dllimport/forceinline specializations while keeping the original inline
semantics. This also stops emitting two empty allocator/proxy destructors.
No pin, alias, imported reference, shared-header or baseline change.

The proof compares strict-current before/after consumer objects and both
strict-current provider objects against the SAME in-memory census. Only these
three objects are refreshed; no census/status/index is written. Consumer
findings fall from two to zero: 0 -> 392 local legacy linked bytes, +0 authored
C++ bytes. This is not closed-strict or a full-game link claim. The strict source
receipts and byte checks establish the current consumer/providers' own bodies;
the rest of the index remains legacy evidence.

The original max<unsigned> copy is 16 bytes and differs from the 17-byte retail
provider at 0x00013740 in stlport_basic_ios_init.cpp. The ScienceType vector-base
destructor has no established retail RVA: BfmeObject476Copy.cpp supplies the
first-copy witness, with a different allocator relocation. No retail destructor
identity is inferred from this first-copy rule. Their identities/layouts in the
matched Player body are unchanged; no donor layout is transferred.

All four removed bodies have zero incoming nondebug relocations, including
section-directed references and EH data. All 32 retained COMDATs and every
other nondebug section, symbolic relocation, external binding and linker
directive are identical. Both provider objects are byte-for-byte unchanged.
The proof checks these properties and records object/index hashes in proof.json.

Acceptance (logs adjacent):
- ./build.sh consumer: 1/1 matched, literal/float/import checks passed.
- link_check.py --prepare-current --paths-from sources.txt, before and after:
  65/65 matched across the three explicitly owned sources, strict receipts;
  string/float/import gates passed.
- proof.py: all invariants above pass; provider findings identical before/after.
- link_check.py consumer: exit 0, LINKS 0 -> 392 bytes.
- link_check.py --paths-from sources.txt: exit 1 because both unchanged providers
  still have unrelated pre-existing findings. Consumer links cleanly.
- eh_verify.py --sources-from sources.txt: all 8 EH rows EXACT.
- data_check.py --enforce consumer: exit 0, zero findings.
- data_check.py --enforce all three: exit 1 for the existing wrong-name datum
  ?g_009FEFA4@@3VBfmeFixedStorage0004543D@@B in BfmeObject476Copy.cpp. Paired proof
  confirms the single finding is identical before/after; not repaired here.
- data_check.py --converged all three: no second name, no unjudged row.
- link_check.py --new-variants all three: exit 0.
- class_gate.py and find_declared_unmatched.py consumer: passed.
- place_bodies.py consumer: 0 new bodies, 0 pins.
- check_csv.py and git diff --check: passed.

Dependency sweep: family-near.json captures the six census units with at most
three blockers involving these same names (47 related authored units overall).
DrawableXfer already has the max suppression at this base. The other nearby
units retain independent blockers: missing checkIdleTeams (AITeamBuilder), two
vector insertion/allocation variants (Rva0059DD3FRecruit), missing rva001B4E21
(SubsystemInterfaceListRva001B505F), or missing registry data
(CreateAHeroRegistry). Do not infer linked-byte gains there from this repair.

BFME 1 review: upstream 66b19a8e95a4add525ef808fcea088e306798e2b applies the
same inline-emission technique to Apt allocation methods. Technique applicable;
its Apt code/layout is not a donor for Player. BFME 1 checkout remains the clean,
committed a7c38d3b2597121f178ab5190b3062478823257d. Freshness fetch found official
master 95eeb3bef370a7cd730b0ad5f228c317c8756e72, but the reference submodule is
claimed by another worker for the comparative full gate. No pointer or freshness
stamp changed here. Full link cycle/census/runtime validation remains outstanding
and was not started under this seat's authorization.

Reproduction: use the index hash and source base in context.json. Before editing,
prepare the three sources with --prepare-current and save their objects under
build/player-science-link-20261015/before/. Apply the source change, prepare the
same three sources again, and place context.json in that scratch directory.
Run this proof.py from the repository checkout; it writes proof.json into the
scratch directory. Objects/receipts remain ignored build artifacts. The tracked
proof output records the original experiment, not a portable compiled cache.
