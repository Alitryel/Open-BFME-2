# Forward-range string insertion owner binding

`BfmeConv1486.cpp` formerly called `BfmeStrV44::bfmeImplV44`, pinned to
RVA 0x00028820. That whole 740-byte insertion has since been recovered as
`Rva008314E0String::insertRange`. The grow branch passes three byte pointers
and an address of the empty range tag; its call now names that owner directly.
No new pin, alias, function body or layout assertion is introduced.

The retail caller is [0x0002A730, 0x0002A84D), 285 bytes (282 excluding CC).
Its machine bytes and relocations are identical after normalizing only this
callee name. The existing assembly wrapper is retained; this is a link repair,
not a C++ conversion. The new declaration follows the recovered owner's tag
reference ABI, with no datum at the tag address consumed by the callee.

Paired **legacy-index preview: +282 B**. The same frozen census index
(3f413ed3ff, 2026-10-20 18:52) and current verified insertion provider are used
for both sides. The original caller has its sole unresolved placeholder;
the repaired caller has no unresolved, duplicate, COMDAT, address or selected
blockers. The index itself is unchanged. The receipt records hashes and exact
call relocation offsets.

`link_check.py --prepare-current` verifies strict reusable receipts for both
caller versions and the native insertion provider; all three matched rows
across the final caller/provider cohort pass the ordinary byte/reference gates.
Self-strict evidence is current. **Closed-strict gain is unmeasured**: the
insertion provider retains the generic-copy dependency debt documented in
`string-copy-providers-20261020/readme.md`. No full link runner was started.

Donor provenance remains as recorded by the existing BFME1 wrapper and the
insertion recovery at `string28820-recovery-20261020/readme.md`. No donor code
is imported. The unchanged BFME1 linking-repair review at pointer 4483e88da1
and prior link-seat handoffs was reused; the applicable repair here is the
BFME2-ledger owner binding, proved against native bytes.
