# Payload constructor provider repair

BFME2 base: `33692378c6`. Move the existing 26-byte constructor row at
0x002BEF29 from Rva002C00E0ObjCtor.cpp to Rva005CBB0AWrap.cpp, which already
emits the same constructor while inlining it into the rowed wrapper 0x002C00E0.
Delete the redundant source. The existing neutral identity, 12-byte layout and
vtable BFE4F4 are retained; no pin, alias or ABI change is introduced. Both files
and the constructor RVA were claimed before editing.

The complete constructor bytes and relocations match retail. All three external
definitions removed with the split object (constructor, vtable and deleting
destructor) have identical masked bytes, sizes and normalized relocation digests
in the home object. That entire retained object is unchanged, including its
data and relocations. Both before objects and the retained after object have
strict reusable compilation receipts.

## Paired local prediction

Index: `ac77c85054`, 2026-10-15 14:25 UTC, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
Each phase refreshes the two explicit objects into an independent copy of the
same frozen index. After deletion, `link_check.forget` removes the retired
object's facts, as in the normal index update path. No index or committed census
status is rewritten.

| Unit | Before | After | Legacy predicted linked bytes |
| --- | --- | --- | --- |
| Rva002C00E0ObjCtor.cpp | constructor duplicate | removed | 0 -> removed |
| Rva005CBB0AWrap.cpp | constructor duplicate | clean | 0 -> 154 |

The home unit's sole duplicate disappears; all other findings are unchanged.
This predicts **154 existing bytes** can link, with **zero new authored bytes**.
Strict object currency is proved individually; no self-strict or closed-strict
placement gain is measured. Ordinary preview retains the deleted file's stale
census entry, so the paired proof explicitly forgets it.

## Acceptance and reproduction

- Before bounded strict preparation: 5/5 rows across two units. After preparation
  and `add_match --replace-existing` / ordinary byte gate: 5/5 in the home unit.
- EH EXACT 2, no baseline allowances or missing objects.
- Enforced data: zero findings. Converged data: eight addresses, zero second
  names or unjudged rows. The deleted data definition has an identical survivor.
- New COMDAT variant check, class gate, declared-definition check and CSV
  integrity pass. Home placement rescan: zero additional bodies or pins.

`capture.py` was run at the base after explicit strict preparation; its snapshots
are in ignored `build/payload-ctor-home-link-20261015/{0,1}`. After the repair,
run `python3 reverse/attempt_support/payload-ctor-home-link-20261015/proof.py`
from the root. `proof.json` records the paired results and receipt/object hashes.
No full link cycle, census, nightly or boot runner was started. Generic
`link_check --refresh` unexpectedly expanded to 7285 stale units (6981 restored
from the object store); it was interrupted at compilation rather than finishing
that unrelated refresh. The explicit strict preparation and paired local proof
provide this repair's evidence.

## Donor review and remaining boundaries

BFME1 repairs `de59a7e9f8` and `d003077f0b` supply the ownership principle of
reusing an existing exact provider. Target bytes establish this constructor and
its layout; no donor C++ or identity is imported. Latest donor `579a8169e6`
font-cache repair was also reviewed: BFME2's deferred large glyph-storage body
is a different blocker, so its member-call spelling was not copied.

Official BFME1 master was fetched at `579a8169e623846f80a90ada4266f72153fbfc60`.
The clean verified checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`. The previous old-input full baseline
is unfinished (attempt 53899: 2982 stale units, interrupted after 21 minutes with
2806 left at `e4dfd1e4d7`). This repair neither advances that pointer nor marks
freshness successful. GPU virtual-contract and string-cleanup conflicts remain
deferred; no unchanged blocked reconstruction was retried.
