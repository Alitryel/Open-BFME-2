# Local state-machine idle helper link repair

Base checkout: e335827a57. The runner-provided census index measures
147cfae2cb, 2026-10-14 07:27. Its unchanged SHA256 and before/after object
and source hashes are in object-proof.json. The discovery queue's committed
link_status.csv measures 67e1365aa9; it is not the preview measurement.
No census index, status, history, baseline, pin or ledger row changed.

GiantBirdNormalFlightStates.cpp and AIStatesDerivedOnExit.cpp each emit an
inline StateMachine::isInIdleState using state pointer +0x04 and State slot 8.
Its complete 17-byte object body is
8379040074088b49048b01ff6020b001c3, with no relocations. The first indexed
copy, AIUpdate.cpp, instead uses state pointer +0x20 and slot 5:
8379200074088b49208b01ff6014b001c3. The index has no retail address for this
generic helper; first-view.json records the keeper specimen and digest.
These distinct code-generation views cannot safely share an out-of-line name.

Rename the flight and attack implementation helpers to flightMachineIdle and
attackMachineIdle, updating their three and six inline uses respectively.
The existing present-unmatched annotation follows the latter rename; hatch
total counts do not grow. The keyed shadow hook reports the renamed label
as +1 unadmitted and the old label as down to zero; no register/baseline
was changed or exemption added. This does not establish hatch admission
under future enforcement. The names identify local implementations, not new retail
identities or a canonical StateMachine layout. The target access/slot evidence
is the existing native callers' full byte gates. No donor layout is imported.

Same-index legacy paired previews remove exactly two losing-COMDAT findings:
flight consumer 2 -> 1, derived-state consumer 13 -> 12. Every other finding
and the original selected keeper remain unchanged. Neither consumer becomes
clean: LINKED stays 0 -> 0, and new authored C++ bytes are zero. This is a
verified conflict reduction, not a placement gain. Both owned objects have
strict reusable compiler receipts before and after (self-strict object
currency). Closed-strict provider closure, self-strict executable placement,
actual link.exe placement and a fresh census are unmeasured.

Acceptance:

- Bounded link_check.py --prepare-current before and after: 19/19 exact rows
  across two explicit owned sources, strict reusable receipts, no expansion.
- Ordinary ./build.sh: 19/19 exact; 23 string literals and one empty-string
  reference, 14 compiler float references; no baselined or skipped references.
- Complete object comparison preserves all 106 retained COMDATs' raw bytes,
  extents, digests and relocation facts. Each renamed helper's full body and
  relocation facts are identical. All nondebug symbolic relocations, external
  undefined/strong/weak bindings, ordinary sections and hatch counts stay
  equal. New helper names occur nowhere in the original index.
- Prescribed local link_check.py completed; exit 1 reflects the independent
  remaining findings. Paired previews establish exactly the two removals.
- Frozen-definition, class, new-variant, converged-data, CSV and whitespace
  checks pass. EH: no applicable rows, no missing objects. Converged-data:
  two sources, eight addresses, no second names or unjudged rows. One existing
  shadow-data finding remains baselined; all data bindings are unchanged.
- Affected-source place_bodies.py resweep: zero bodies and zero pins.

Remaining findings are fully listed in paired-link-after.txt. Both consumers
still touch a getNextMoodTarget provider selected against retail. The derived
state unit also lacks seven indexed providers and has independent region,
waypoint, locomotor-set and team COMDAT conflicts. No unchanged blocker was
retried, renamed or hidden. These are candidates for independent repairs,
not evidence that all work in this lane is exhausted. The indexed same-cause
idle-helper sweep has no further losing consumer beyond these two.

Reference review: verified BFME1 gitlink/checkout
23b143233b5a8664a3bdf8572df6d905c310a5a1, unchanged; freshness success stamp
2026-10-14 08:17 remains under 24 hours. Reused the donor review from
../local-player-link-20261014/readme.md, and inspected repairs d2e21369067f
and b955ec4852b5: surplus private emission/provider reconciliation applies as
a repair principle; donor-specific aliases, pins and layouts are inapplicable.
No unchanged donor sweep or source transfer was repeated.

Normal commit hooks pass the 19-row byte gate. Code-identity shadow reports
three findings (one unowned binding and two divergent definitions); the
full-object invariants establish their definitions and symbolic bindings
unchanged. Shadow data retains one baselined finding. These were not repaired
or waived.

Both file claims protected the repair. Reproducible full-object proof script,
source/object/dependency backups and strict cached objects remain under
build/idle-state-link-20261014. No maintainer-only full link cycle, census
build/measure/history, nightly, boot or scheduler runner was started.
