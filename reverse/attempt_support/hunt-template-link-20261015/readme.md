AI hunt template-accessor emitter repair

AIHuntStateUpdate.cpp now marks its existing TeamPrototype::getTemplateInfo
definition imported forceinline. Its identity accessor still returns &m_info;
the caller already inlines it. This removes an unused three-byte standalone
COMDAT competing with other TeamPrototype views. No import reference, pin,
alias, header, compiler option, data owner or function row is added.

Target identity remains the existing 828-byte AIHuntState::update at
003464D1, vtable C118B0 slot 6, with the named getter/onExit relationships
documented in the source. Existing ZH semantics and target layout evidence
remain separate. No standalone retail getter identity is inferred here.

Measurement: source base 51280f14e2717534151f383dc521851e20ed6396;
downloaded index a2839ea429, 2026-10-15 13:35. measurement.json records its
hash. Strictly current original and repaired objects were substituted into
separate copies of that same index. One COMDAT conflict becomes zero; no
other finding changes. Paired current-object legacy preview: 0 -> 828
existing authored bytes, 0/1 -> 1/1 clean units. The historical census already
counts this file linked; ordinary link_check prints 828 -> 0 before and
828 -> 828 after. This is a repair of the current object's conflict, not an
increment in historical census totals. Census/status/history remain unchanged.

proof.json records source, object and receipt hashes. All 21 retained COMDAT
bodies, extents and relocation digests are identical. All other nondebug
sections, local/external relocation targets, bindings and linker directives
are unchanged. No retained relocation references the removed accessor.
peer-inventory.json records the index's five getter copies. Their unchanged
definitions and references are preserved by the section proof; they are not
freshly rebuilt or certified. TeamGetControllingPlayer retains independent
unresolved, STLport and layout conflicts; this is not a repair of that unit.

Acceptance:
- Bounded link_check.py --prepare-current before and after: strict reusable
  compiler receipts, complete 1/1 row exact and two float literals verified.
- Independent ./build.sh: 1/1 exact, two float literals, zero skipped/baselined
  references, no named imports. EH verify: no EH rows, no missing objects.
- Frozen-definition, class, new-variants and CSV checks pass.
- Converged-data enforcement: eight addresses, zero second names or unjudged
  rows. Shadow data: zero findings before and after.
- place_bodies.py: zero bodies/pins. Whitespace check passes.

Saved original/repaired source, objects, strict receipts, strict gate output
and executable proof remain in ignored build/hunt-template-link-20261015.
New authored C++ bytes: zero. Self-strict placement and closed-strict closure
are unmeasured. No census build/measure/history, full link cycle, nightly,
boot or scheduler operation was started.

Donor review: reused the previous seat's review of BFME 1 repair
66b19a8e95a4add525ef808fcea088e306798e2b and rechecked its verification message.
Its imported-forceinline emission mechanism applies; its Apt identities,
layouts, addresses and measured gain do not. No donor code is imported.
Official master fetched at 98f9c4fc7a457bb4c754231e0ed5b073c41db06e;
verified clean gitlink/checkout remains a7c38d3b2597121f178ab5190b3062478823257d.
Another seat's live file:reference/open-bfme-1 claim prevents advancing inputs.
Comparative full verification and affected donor refresh remain outstanding;
no freshness-success stamp was written.

Discovery: repair_queue.py link, link_rank.py help/top/near/kind/file and
current-object link_check. File and parent RVA claimed before editing. No
per-row data-back artifact or manufactured ranking used.
