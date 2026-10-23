# BIG archive index recovery, 2026-10-20

Recovered `Win32BIGFileSystem::rva006045A2`, native RVA `0x006045A2`,
270 bytes through the `ret 16` immediately before `addArchiveFile` at
`0x006046B0`. The latter's existing 314-byte row remains exact.

## Identity and layout evidence

The native caller constructs a twelve-byte file/offset/size descriptor and
passes it to this helper. The helper looks up a folder, interns missing names,
constructs an empty inner map when necessary, then inserts or conditionally
overwrites a member descriptor. Its native field accesses and calls establish
the nested maps and three descriptor words. WorldBuilder's corresponding
`0x01650630` helper and named `0x016507D0` caller support the relationship;
the helper's address-derived name and descriptive record/field names do not
claim original target spellings. ZH's archive implementation was reviewed as
a semantic lead; its different archive model is not an exact donor.

Inputs: BFME 2 parent `f12f64bc17`; BFME 1 reference
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`. Compilation uses the source's
recorded `/O1 /arch:SSE /G7 /EHs /MD` settings and BFME 2's actual
`vendor/stlport` headers. No vendor headers or verifier code changed.

## Closing the earlier bank

The saved clean bank already used the natural map insertion expressions and
a declaration-only member-pair `_Construct` specialization. Fresh compilation
proved zero non-relocation differences over the whole 270-byte body; the
committed artificial padding wrapper and inline folder-insert helper were
therefore removed rather than tuned. Normal `add_match.py` verified the
complete resolved body and deleted the old bank.

Native node construction at `0x0029E11A` calls the 30-byte placement copy at
`0x0041360E` out of line. The real member-pair `_Construct` is instantiated in
the existing related `Rva00604289Construct.cpp` provider. It reproduces all
30 bytes with no relocations and folds with the already-owned copy there.
Keeping its real definition outside the indexing unit preserves the native
call boundary and temporary lifetimes, including the frame size `0x44` and
the first pair buffer at `ebp-0x50`. No layout padding, fake object, inline
assembly, dead operation, or synthetic callee body is needed.

`pin_consistency.py --symbol` was run before each new pin. All nine bindings
were then admitted through `pin_admission.py --add`, using full emitted bodies
and every owner row's relocations, with these tracked fold-proof sources:

| Binding | RVA | Proof unit |
| --- | --- | --- |
| member-pair `_Construct` | `0x0041360E` | `Rva00604289Construct.cpp` |
| folder/member `_M_find` (two names) | `0x00603A2D` | archive indexing unit |
| member-map default constructor | `0x00413727` | archive indexing unit |
| folder `make_pair` | `0x00604251` | archive indexing unit |
| folder pair const-key conversion | `0x0060426C` | archive indexing unit |
| folder `insert_unique` | `0x006044A0` | archive indexing unit |
| member tree destructor | `0x00603AA8` | archive indexing unit |
| member `insert_unique` | `0x00603E50` | archive indexing unit |

The official admission tool wrote the hatch grants. These folds add no retail
coverage; the new unique C++ coverage is the 270-byte parent alone. The native
12-byte descriptor was never replaced with the old four-byte placeholder.

## Linking and data

The first link preview exposed two nonretail `/O1` tree minimum/maximum copies
and the previously declaration-only archive signatures. The indexing unit now
selects the existing `_STLP_BFME_TREE_NODE_BASE_O2` header contract, already
used by its provider; the two complete recovered bodies remain exact.

Native VA `0x00DD5150` contains `f022bd00e822bd00`: pointers to the full
`BIGF\0` and `BIG4\0` strings at `0x00BD22F0` and `0x00BD22E8`.
`addArchiveFile` loads both entries. One mutable two-pointer array now owns
the eight-byte `.data` object, with a verified `data_rows.csv` row. There is
no competing global at this address and no shortened string literal.

## Final verification

- `check_csv.py`: OK, 97,407 function rows and 1,121 data rows.
- `bash ./build.sh` on both units: 7/7 function rows exact, the new data row
  byte-verified, source claims and string/import checks OK.
- `eh_verify.py` on both units: EXACT 2/2 parent EH graphs, no baseline debt.
- `pin_consistency.py --check`: OK, no new or stale inconsistencies.
- `find_declared_unmatched.py` on both units: all definitions matched.
- `place_bodies.py` on both units: fixpoint, zero additional bodies or pins.
- `link_check.py` on both units against published census `5366c4f808`:
  archive unit LINKS, 0 -> 584 bytes; provider LINKS, 92 -> 92 bytes.

Earlier investigation and native slot evidence remain in
`big-archive-6045a2-slots-20261020/handoff.md`. The new result supersedes that
handoff's two-slot-byte blocker and the old padded partial implementation.
