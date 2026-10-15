# Formation restart ownership and vtable binding repair

Base: 82bf70e431 (upstream b04d5190ba plus two preserved verified commits).
Runner index: 825b86983f, 2026-10-15 12:37; underlying census 5986a99448,
2026-10-15 04:52. Its unchanged SHA256, strict receipt/object hashes and paired
findings are in proof.json. Committed link_status.csv is discovery evidence.
No per-row data-back ranking or measurement artifact was used.

FormationTranslatorRva00431C9D.cpp already compiled the complete 104-byte
WaitForSecondButtonDownStateHandler::Restart as well as its 445-byte caller.
Rva00431C35.cpp supplied a redundant exclusive definition. Rehome the existing
row with add_match --replace-existing and remove the redundant file. The home
must retain the helper definition for its caller's compiler analysis; no
algorithm or layout is changed.

The home referenced two undefined address-named vtables. Replace those names
with the existing compiler symbols ??_7Rva004318FC@@6B@ and
??_7Rva004319C2@@6B@ emitted by RvaSmallVtableCtors.cpp, as already used by
other matched callers in this family. The constructors at 0x004318FC and
0x004319C2 install VA 0x00C3C97C and 0x00C3C9A0 respectively. The helper and
caller reach exactly those same tables. The four retail DIR32 witnesses are
recorded in proof.json. Class owners remain address-derived and unrecovered;
this establishes no new source identity, vtable slot recovery or data-back
placement. No donor code, header, compiler flag, pin, alias or gate change.
Original WorldBuilder identity evidence and the standalone source's layout
comments were already present verbatim in the surviving source and remain.

Acceptance and scope:

- Before: strict preparation passes both rows across two files. Each file
  has the helper duplicate; the home additionally has two unresolved vtable
  names and one helper COMDAT comparison finding.
- After: add_match and the byte gate pass 2/2 rows in the home. Bounded strict
  preparation of the home plus unchanged vtable provider passes 187/187 rows,
  all float/literal/import checks, and issues current reusable self receipts.
- The asserting scratch proof at
  build/formation-restart-home-link-20261015/proof.py normalizes all non-debug
  COFF sections, data, directives, EH symbol indices and relocations. Every
  byte and binding is unchanged except the two intended vtable relocation
  names. The deleted owner's only external copy is retained with the identical
  104-byte body-and-relocation digest b647b9948621 in the home.
- The paired local check refreshes the explicit home and unchanged provider
  in an isolated copy of the same index. It retires the removed object with
  canonical link_check.forget, as --update-index does for vanished ledger
  owners. All home findings disappear. The provider's four unrelated unresolved
  findings are unchanged. Invoking the prescribed local link_check CLI on the
  isolated preview reports LINKS: 0 -> 549 existing retail bytes. The shared
  index and census/status artifacts are unchanged.
- This is strict self verification and a legacy local link prediction.
  Closed-strict closure, fresh census gain, link.exe placement and data-back
  gains are unmeasured. Authored and matched byte growth is zero.
- Frozen declarations, canonical classes, new-variant admission, CSV and
  whitespace checks pass. EH: zero rows, no missing objects or failures.
  Placement resweep: zero additional bodies and pins. Converged data: eight
  addresses, zero second names or unjudged rows. Shadow data checking retains
  the pre-existing MessageStreamSubsystem versus TheMessageStream name finding
  at RVA 0x00A00950; the stricter diagnostic --enforce therefore still fails
  on this unchanged binding. No baseline is changed and no data-back claim is
  made. Resolving the provider's two independent singleton definitions requires
  a separate coordinated repair.
- A source sweep finds no further live g_00C3C97C/g_00C3C9A0 references outside
  this repaired unit; other occurrences are provenance comments. Other
  WaitForSecondButtonDownStateHandler units define distinct member bodies.

Selection: repair_queue.py link, current link_rank help/workflow and rankings,
then rehome_rows.candidates and its all_exact check after the high-ranking
current units were already link-clean or still deferred. Both files and the
helper RVA were claimed before mutation. No still-blocked GameInfo or
Render2D compiler-shape attempt was repeated.

BFME1 review: verified gitlink/clean checkout a7c38d3b2597121f178ab5190b3062478823257d
is preserved; official master fetched to 6974867b784ad2e651a2e167853246afcb18e3b5.
Reviewed de59a7e9 (consistent inline definitions) and 4966496c (suppress surplus
COMDAT emission). The ownership principle applies; target algorithms/layouts
are independently established above, with no import. Freshness pointer work
remains held by another worker's live reference/open-bfme-1 file claim and the
outstanding old/new full-byte comparison. No successful check stamp was written.

No census build/measure/history, full link cycle, nightly, boot or publisher
verification runner was started. Broader placement is left to authorized runners.
