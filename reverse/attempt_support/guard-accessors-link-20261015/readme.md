AI guard-target accessor emitter repair

AIGuardInnerTargetRva00369FDF.cpp marks its existing TeamPrototype::getTemplateInfo
and Object::getTeam definitions imported forceinline. The matched caller already
inlines both definitions. This removes unused standalone COMDAT copies competing
with other class views without adding import references, pins, aliases, headers,
compiler options, data owners or function rows.

Target identity and layout remain the existing source's evidence: guard-machine
caller 0036A979, WorldBuilder F356C0, and retail boundary 00369FDF..0036A3E9;
the ZH AIGuard implementation supplies the semantic guide. The private target
views return the embedded TeamTemplateInfo and Object's team at +0x304. This
change does not infer a standalone retail identity for either accessor.

Measurement base: bb03cf2a35af242d14be1b119f8d776de799b352. Downloaded index:
a2839ea429, 2026-10-15 13:35; underlying census 5986a99448, 04:52.
measurement.json records the unchanged index hash. Strictly current original
and repaired objects were substituted into separate copies of that same index.
Two COMDAT findings become zero. The unresolved filter method
?allow@Rva00260E01Filter@@UAE_NPAVObject@@@Z remains, with no other finding
changed. Paired current-object legacy preview: 0 -> 0 linked bytes and 0/1
clean units. The unit has 1,031 existing unique authored bytes in this metric.
This is a verified conflict repair, with no linked-byte or closure gain claimed.
Census/status/history remain unchanged.

proof.json records source, object and strict receipt hashes. All 47 retained
COMDAT bodies, extents and relocation digests are identical. All other nondebug
sections, local/external relocation targets, bindings and linker directives
are unchanged. The only external definitions removed are the two accessors;
no retained relocation references them. peer-inventory.json records the index's
five template-accessor copies and seventeen Object::getTeam copies, and the
absent filter provider. Their definitions and references are untouched; peers
were not freshly rebuilt or certified. The remaining independent conflicts in
those peers are not claimed repaired.

Acceptance:
- link_check.py --prepare-current before and after: strict reusable receipts,
  2/2 rows exact, one float literal verified, no skipped/baselined references.
- Independent ./build.sh: 2/2 exact, one float literal, zero named imports.
- eh_verify.py: one EH row EXACT, zero missing objects; eh-after.json retained.
- Frozen-definition, class, CSV, new-variants and whitespace checks pass.
- Shadow data: zero findings before and after. Converged-data enforcement:
  eight addresses, zero second names and zero unjudged rows.
- place_bodies.py: zero bodies and zero pins.

Saved original/repaired source, objects, strict receipts, gate output and
executable comparison remain in ignored build/guard-accessors-link-20261015.
New authored C++ bytes: zero. Self-strict placement and closed-strict closure
are unmeasured. No census build/measure/history, full link cycle, nightly,
boot or scheduler operation was started.

Donor review: reused the preceding seat's review of BFME 1 repair
66b19a8e95a4add525ef808fcea088e306798e2b and rechecked its verification message.
The imported-forceinline emission mechanism applies; Apt identities, layouts,
addresses and measured gains do not transfer. No donor source is imported.
Official master fetched at a5a369864461df0da0a435313edc3252a761de4a;
verified clean gitlink/checkout remains a7c38d3b2597121f178ab5190b3062478823257d.
Another seat's live file:reference/open-bfme-1 claim prevents advancing inputs.
Comparative full verification and affected donor refresh remain outstanding;
no freshness-success stamp was written.

Discovery: repair_queue.py link, link_rank.py help/top/near/kind and bounded
current-object link_check probes. The analogous hunt, idle, attack-on-exit,
enemy-search and selected script units already pass local link checks, so no
duplicate repair was attempted. The split string accessor's recorded REL32
blocker remains deferred. File, parent and EH RVAs were claimed before editing.
No unavailable per-row data-back artifact was used to invent a ranking.
