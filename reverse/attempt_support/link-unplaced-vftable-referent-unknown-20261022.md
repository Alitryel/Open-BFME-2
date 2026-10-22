# link_census: copies referencing an unplaced vftable stayed unknown (2026-10-22)

**Symptom.** A constructor whose body matches retail stored its class's
vftable (`??_7...`), which has no ledger address because data_rows cannot row
vftables yet (see the 0x00BC650C wall in `re_attempts.log`). The census
judged every such copy `unknown`, never `retail`. Retail-truth-3's exemption
then never applied to the name's wrong copies. In this census, 160 names with
wrong copies had no proven-retail copy, and vftables were the most common
missing referent (`build/scratch/gap_refs.py`).

**Fix.** `_comdat_sections` gives each referent that the object defines in a
COMDAT section its definition (body, relocations, digest). That covers:
- static mangled symbols;
- a weak external such as a vftable slot's `??_E`, through its default `??_G`.

When no ledger row places the referent, `RetailTruth._judge` judges that
definition at the address retail's relocation lands on, recursively:
- a cycle back to the same definition at the same address holds;
- depth is capped at 6;
- inner results are not cached.

The rule only proves: a mismatch leaves the site `unknown`. It shows what a
fold-proof row at that address would show. The keep rule still decides the
referent's own copies by link-order equality, so a kept copy that differs
still loses under its own name. The verdict fingerprint includes the
definition's digest. Regression test:
`test_unplaced_referent_is_judged_by_its_own_definition_where_retail_points`.

**Measured.** Example: `??0?$basic_streambuf@D...@IAE@XZ` (0x13320) is proven
through `??_7` at 0x7BBC30, `??_G` at 0x13360, `~basic_streambuf` and
`operator delete`. Of the 160 names, 114 flip to retail. Across the 294 units
holding their copies, `link_check` (all re-judged) links 150 against 148
without the change (+850 B). Most of those units have other blockers; the
next census shows the full effect.
