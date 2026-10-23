# Vector destructor dependency isolation

BFME 2 starting revision: 17afe9c099. BFME 1 donor revision reviewed:
37c3022de1ab944c7ffe536440d637dc8199091c. The earlier donor ownership review
in `link-seat-20261021/readme.md` supplies the declaration-only specialization
lead; the target's existing matched rows and relocations establish the calls.

`StlportVectorDtorFamily.cpp` initially has 2,081 nonpadding matched bytes and
does not link. Its size-only element views emit incorrect range helpers and
references to seven element destructors without providers. Declaration-only
`_Destroy` specializations preserve every matched vector destructor and avoid
those unintended helper definitions. Three such bindings remain in the family
for Rva00413B16Element, Rva002E2690Element and Rva000C828CElement.

Nine independent dependencies are isolated in `StlportVectorDtorDeferred.cpp`:

* OpaqueRefElement4: competing vector destructor in MilesAudioManager.
* BfmeAssignRecord172 and BfmeAssignRecord44: competing vector destructors in
  stlport_asciistring_record_bodies.cpp.
* BfmeAssignRecord104: competing range helper; retail owner is the differently
  named Rva003B8E13DestroyRange.
* RvaPair00257544 and Rva005F8620Element: no compiled provider under the pinned
  helper spelling; retail owners are Rva0032C0CADestroyPairs and
  Rva005F85C8Destroy respectively.
* Rva002BBB96Element, GeometryShape and Rva001DEF38Element: competing range
  helpers, with retail bodies owned under other element/template names.

These are still byte-matched code, not newly recovered bodies. All nine range
helpers are declaration-only in the isolated unit: a size-only view must not
emit a replacement implementation. The existing row names, retail addresses,
extents and compiler settings are unchanged; 13 ledger rows move, including
four compiler EH handlers. The isolated unit is absent from the published
census and has no claimed LINKED gain.

Acceptance:

* `link_check.py StlportVectorDtorFamily.cpp` before: does not link, 0 bytes.
* Same bounded legacy preview after: LINKS, 1,475 nonpadding bytes.
* `link_check.py --prepare-current` on both explicit sources: strict reusable
  receipts and normal byte gates, all 44/44 original rows match.
* `find_declared_unmatched.py` on both files: all definitions declared.
* `check_csv.py`: passes after staging the new source.
* `link_check.py --new-variants` on both sources: passes.

This is a 1,475-byte legacy preview improvement with self-strict byte receipts.
No closed-strict, full-link, census or runtime result is claimed. The remaining
deferred ownership repairs require provider/consumer checks together; do not
infer a third ignored tag argument from a shared loop's bytes alone.
