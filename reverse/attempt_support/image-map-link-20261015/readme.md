Image-map instantiation link repair

The insertion unit explicitly instantiated every member of map<unsigned,
Image*>. That emitted an unused _Rb_tree_base constructor with a different
COMDAT body from the first indexed copy. Instantiate only the recovered
hint-insert wrapper, as the existing stlport_map_int_ptr_insert_hint.cpp
sibling does. Its dependency chain and ImageSubscriptMap::operator[] still
emit every one of this unit's six matched functions.

Base checkout: 243d8affab. The local measurement is 28269d8e8d, 2026-10-15
09:31 UTC; exact index SHA256 is in object-proof.json. The paired proof uses
the same unchanged index, replacing the explicit current unit and the same
three peers in memory on both sides. One constructor COMDAT finding becomes
zero. LEGACY local linked bytes improve 0 -> 681 (682 bytes of row extent).
ImageCollectionFindImage.cpp, ImageCollectionDtor.cpp and
stlport_string_pair_cleanup.cpp remain locally clean on both sides.

All 33 retained COMDAT bodies have identical bytes, extents and relocations.
The full-object proof also compares every retained nondebug section, flags,
bytes and symbolic relocations, with local referents normalized by content.
It excludes only 95 removed COMDATs, their associative exception sections,
one unused static iterator comparison, and their SafeSEH index entries.
No retained relocation references any removed body. All 23 removed shared
COMDAT families retain the same first selected digest and no remaining copy
acquires a losing verdict. The 72 removed sole-provider names have no
undefined consumers in any object-store variant. That scan includes 22,482
objects whose hashes match the measurement, including 49 other Image users;
516 census objects are unavailable at their measured digest. This is bounded
local evidence, not a full link or a claim about the missing objects.

Acceptance:
- ./build.sh on the insertion source: 6/6 rows pass, including all reference
  checks. --prepare-current passes those six and all twelve peer rows with
  strict reusable receipts. Ordinary four-source local preview is clean.
- EH verification: no EH-bearing matched rows; zero missing objects or debt.
- Data enforcement, converged-data enforcement (eight addresses), frozen-file,
  class, CSV, new-COMDAT-variant and whitespace checks pass.
- place_bodies.py finds zero bodies and zero pins.
- The reproducible comparison script and baseline source/object/receipt
  snapshots remain under ignored build/image-map-link-20261015.

No flags, headers, pins, ledger rows, globals, baselines, census measurements
or verifier rules change. New authored C++ coverage is zero. Receipts are
self-strict; no closed-strict, full-link placement or runtime gain is claimed.
No maintainer-only runner was started.

Donor review: preserve the verified BFME 1 pointer
 a7c38d3b2597121f178ab5190b3062478823257d. The dedicated review already
recorded in link-inline-emitters-20261014 and region-iterator-link-20261015
covers donor d3f9000fe08615a100e844adfff57fa4a39cd615's incidental-emitter
repair technique. Here the actual adaptation comes from the matched BFME 2
STLport sibling; no donor layout or source is imported. Official master was
fetched read-only at 27dbaa68. Another worker holds the reference-file claim,
so the overdue verified pointer update remains their work; no success stamp
or pointer change is made.

Independent triage: the damage-neighbor parser still has an EH-referenced
Rva004BA1B2 destructor colliding with the differently typed ManTheWalls
record. It needs supported identity/constructor-fold reconciliation. The
blocker was recorded through re_log.py without a source edit and its claim
was released. The broad name_globals.py dry run produced zero edits. Many
higher-ranked items already have source repairs newer than the census;
foreign claims also reserve candidate files.
