# EAString provider binding and duplicate assignment repair

BFME2 base: `370848c49c` (the preserved opacity-call repair rebased onto
`ec6ad492f1`). No matched row or native boundary changes.

The 35-byte wrapper at 0x006D5580 still referenced the BFME1-derived
`Rva0089EFE0::rva0089E2B0` declaration. The direct call at 0x006D559A targets
0x006D47F0, now recovered as `EAStringC::rva006D47F0` in EAStringCConcat.cpp.
Declare that existing provider in the EAStringC view and forward the unchanged
receiver and two C strings to it; remove the obsolete old-name pin. The
wrapper's original class/member identities remain unknown. Target bytes prove
the destination and thiscall/RET8 ABI; the existing provider supplies its
current C++ spelling. No new field/layout/identity is inferred from matching.

The newly recovered provider also emitted an external 85-byte assignment copy
alongside the canonical strong definition in EAStringCRefCount.cpp. Its bytes
AND relocations equal the canonical assignment, but the two external definitions
produce duplicate/selected findings. This is an ownership conflict, not evidence
that the assignment's instructions differ from retail. Mark its local visible
assignment dllimport/forceinline to retain the native inlined behavior without
emitting that redundant external body. No import relocation is introduced.
All retained provider sections, including EH and assertions, stay identical.

## Paired local evidence

Frozen index receipt: `a2839ea429`, 2026-10-15 13:35; underlying census
`5986a99448`, 04:52. SHA256:
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`.
Committed link-status discovery measurement: `4b7e7091c4`.

proof.py refreshes the saved-before/current caller and provider plus the same
strict-current canonical assignment unit into separate in-memory copies of
that index. The three-unit preview improves **0/3 to 3/3 clean** and **0 to
5,009 existing retail bytes** (caller 910, provider 1,780, canonical unit 2,319).
The default link_check output instead compares against older per-file index
status, 3,419 to 5,009; use the paired result for this repair's before/after.

The wrapper retains its complete 35 instruction bytes and changes exactly one
REL32 name at offset 27. Its eleven retained COMDATs and all normalized
nondebug sections are identical modulo that spelling. The provider retains
22 COMDATs with identical byte/relocation digests; the sole omitted section is
the external assignment, independently checked against its canonical twin.
No added variants or changed data findings. proof.json records exact findings
and object/index hashes. Before objects and original sources remain in ignored
build/eastring-provider-link-20261015/before/.

sweep.py reads current assignment-declaring consumers without compiling or
editing them. Of 35 candidates, 23 have strict reusable receipts and census
positions; 12 missing/stale/outside-index units are skipped. With the same
before/after replacements, the bounded preview improves **0/23 to 20/23 clean**,
**0 to 18,962 local linked bytes**, with no added finding. sweep.json preserves
all paired findings, skipped paths and current-object hashes. EAStringCConcat
was the only additional external assignment emitter found; other candidates
need no similar edit. Three unrelated blockers remain in the current preview:

- AptActionInterpreterGetVariable: missing findChild and rva006E02B0 names.
- AptCIHRender: missing rva006F7720Sub.
- AptValueVector: duplicate/selected subscript operator.

These are bounded receipt-current previews against a legacy index, not new
self-strict or closed-strict census measurements. New authored C++ bytes: **0**.
No full census, link cycle, nightly, boot or scheduler runner was invoked.

## Acceptance

- Normal byte gates: caller 7/7, provider 10/10; bounded strict preparation of
  caller, provider and canonical unit **50/50**, with reusable current receipts.
- Literal verification: 56 nonempty plus one empty reference; no unverified or
  skipped literals, floats or imports.
- Local three-source link_check and no-new-variants: pass.
- EH: **8 EXACT**, no missing objects or baseline entries.
- Data enforcement: zero findings; converged enforcement: eight addresses,
  zero second names and zero unjudged rows. Paired data findings unchanged.
- Pin consistency, ledger, class gate, declared-definition and whitespace
  checks pass. Affected-unit placement resweep: zero bodies, zero pins.

## Reference review and preserved boundaries

Reviewed BFME1 `d003077f0b7ce97622adb7a53f1fe76653433c5c` for direct binding to
an existing provider, and `66b19a8e95a4add525ef808fcea088e306798e2b` for the
inline-import external-copy suppression technique. The latter repairs two Apt
allocation copies while preserving the enclosing bodies. These are principles
adapted to independently verified BFME2 calls and emission, not imported BFME1
layouts or addresses. The DamageInfo constructor repair c1315665 was also
reviewed; its already-reconciled BFME2 units were not retried unchanged.

The clean donor checkout/gitlink stays at
`a7c38d3b2597121f178ab5190b3062478823257d`; official master fetched as
`e082760734795655f086939df77b393f4b728375`. A foreign reference-scope claim and
incomplete controlled old/new-input verification still block the freshness
update. Neither the checkout nor its stale success stamp was advanced.

repair_queue.py link, link_rank.py and current-object checks supplied discovery.
Many ranked blockers are already repaired in current sources; no unchanged
stream-motion, Apt mask-stack or garrison reconstruction was retried.
