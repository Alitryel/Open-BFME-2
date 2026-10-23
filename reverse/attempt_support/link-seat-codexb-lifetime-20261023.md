# Opaque vector lifetime binding repairs, 2026-10-23

Inputs: BFME2 f15fab177f; published census b711de3634, 2026-10-23
14:28, retail-truth-4; verified BFME1 reference
96c88c73a5cd1a58fc2f8db691beea50acd996db. This is a BFME2 operation-binding
repair, not a donor identity transfer. Prior donor/linking handoffs were reviewed
at the unchanged reference revision.

Five current-object legacy previews were 0/450 nonpadding matched bytes before
the edits and LINKS 450/450 after them. The census baseline also has zero linked
bytes for these units. Normal byte gates pass 1/1 for each unit. No authored
C++ recovery, published-census update, or closed-strict gain is claimed.

| Unit suffix | RVA | Bytes | Construction provider | Cleanup provider |
| --- | --- | ---: | --- | --- |
| StlVectorRva0021582C | 21582C | 105 | 21559C | range 215783 |
| StlVectorRva0039C028 | 39C028 | 116 | 39B8C6 (copy ctor 39B893) | range 22C8E3 |
| StlVectorRva0048D628 | 48D628 | 55 | 48C81F | range 48CE25 |
| StlVectorRva0052D801 | 52D801 | 58 | 52D6BE | range 52C24E |
| StlVectorRva005C84F1 | 5C84F1 | 116 | 5C83CD | destructor 5C8FBD |

## Target evidence and scope

These are existing address-derived opaque element views. Their original game
class identities remain unknown. Direct calls and pointer strides read from
retail game.dat establish operation relationships independently of similar
bytes or donor names:

- 21582C calls allocate/copy 215614 -> uninitialized_copy 2155C9 -> placement
  copy 21559C; clear 21580E calls range destroy 215783. Both loops step 0x10.
- 39C028 calls allocate/copy 51ED51 -> uninitialized_copy 39BA22, which inlines
  the placement null check and calls copy ctor 39B893, stepping 0x14. The rowed
  39B8C6 wrapper performs the same placement copy for its out-of-line spelling.
  Clear 565A42 calls 22C8E3 -> 52BF9B. The last loop advances 0x14 and invokes
  each record's virtual deleting destructor with zero flag.
- 48D628 and overflow 48D48F call placement copy 48C81F. Overflow calls clear
  C060A -> range destroy 48CE25, with stride 8.
- 52D801 and overflow 52D742 call placement copy 52D6BE. Clear 52CAAB calls
  52C24E -> tagged destroy 52BCE7, whose loop advances 0xB8 and invokes the
  virtual deleting destructor with zero flag.
- 5C84F1 calls allocate/copy 5C8445 -> uninitialized_copy 5C83FA -> placement
  copy 5C83CD. Clear 5C84D3 calls range destroy 5C847B -> destructor 5C8FBD.
  Both native loops step 0x48; the destructor takes ECX and no stack argument.

Construction bindings preserve two-pointer cdecl ABI. Four units declare their
range _Destroy specialization and bind its two-pointer cdecl spelling to the
existing native range owner. This also avoids treating the polymorphic records
as if they had a known directly callable destructor. The fifth binds the
nonvirtual destructor already established by its target cleanup loop. No new
symbol pins, data globals, identities, or ledger rows are introduced.

## Validation

- ./build.sh for each of the five source suffixes: all five matched bodies
  exact; string/float/import reference checks pass.
- link_check.py before/after on the five current objects: 0 -> 450 B legacy.
- link_check.py --prepare-current on all five: scoped byte verification and
  reusable strict receipts; receipt preparation does not prove link closure.
- find_declared_unmatched.py: all definitions already matched.

Scratch transcripts are build/link-seat-reserve-before.txt,
link-seat-reserve-other-before.txt, link-seat-lifetime-after.txt and the five
per-unit build logs. The table and call chains above preserve the useful facts
without depending on those ignored scratch files.

## Other checked work and remaining prerequisites

Ranked sole/name/near blockers, class_views --blockers, repair_queue link,
current-object previews and the existing BFME1 linking handoffs were checked.
Many leading census blockers already link on current master (Hashable family,
FireLogicSystemObjects, GSConfig, W3DGhostObjectScene, SimpleScene, army copy,
partitionmanager and several allocator/constructor units); no inherited gain
was credited. name_globals.py --dry-run proposed no rewrites. rehome_rows is
blocked by missing census.log; no matching data-back artifact was available.
Current-ledger closure remains unavailable due to missing provider objects;
no census, full link cycle, nightly or boot runner was started.

The string-replace pair remains blocked: removing its nonretail local helpers
changes the verified 511-byte parent's frame from 0x9C to 0x54 and spill shape.
The 848-byte insert stays exact. Both original sources were restored and each
passes its 2/2 byte gates. The failed change is recorded in re_attempts.log;
retry needs a way to preserve compiler analysis context while selecting the
native helpers. Existing full-class/vtable and ABI prerequisites in the prior
link-seat handoffs remain unresolved and were not retried unchanged.
