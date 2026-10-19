# Module-key registry lifetime and class repair

Retail `4ABDC3` (25 bytes), `4ABE53` (18 bytes), and `4ABDDC` (119 bytes)
belong to one registry. Both lifetime bodies store vtable VA `C549F0`; its
first word points to `4ABDDC`, followed by zero padding and the distinct
LargeGroupAudioUpdateModuleData table at `C549F8`. Consequently key collection
is virtual and destruction is nonvirtual. The earlier constructor's virtual
destructor and string-set view were unsupported. The existing pinned neutral
destructor name is retained for the unified class.

The target constructor calls the full **25-byte** empty pointer-set
constructor at `D3A71`; its 42-byte tree constructor, 36-byte allocation base,
and 11-byte proxy reproduce the existing owners, including every relocation.
The allocator requests a 20-byte node: a 16-byte tree header plus a pointer.
The target walk reads that pointer at node+16 and merges the pointed object's
key-map member at +8. The independently matched registration method `4ABEAE`
inserts module pointers into the same global's set at +4. These establish the
pointer registry and member offsets independently of byte coincidence.
Original class, typedef, comparator spelling, and complete entry layout remain
unknown. The canonical 20-byte class records the consumed aligned layout;
byte +16 remains opaque and byte +17 is cleared during construction and set
during destruction.

The typed STLport destructor emits the complete native tree lifetime at
`4ABCFE` (56 bytes), its genuine base-header destructor at `7FAB3` (14 bytes),
and the set destructor thunk at `4ABDBE` (5 bytes). Clear `4ABC5C` (41 bytes)
and recursive erase `4ABAD6` (45 bytes) live with the existing indexed STL
lifetime provider. Normal `add_match --icf-owner` admissions prove the folded
names against whole existing owners; no pin, object-symbol alias, baseline,
gate, or generated source was added or changed.

The key-map local formerly used a derived five-byte destructor wrapper. Its
normal exit inlined that wrapper, but its EH action tried to call the wrapper
at the retail **58-byte** destructor address. Use the existing 12-byte
`Rva003ED94FDtor` view directly: its folded constructor is `1F81BF`, and its
whole destructor is `3ED94F`. The 108-byte sibling and 119-byte method remain
exact. Both real cleanup actions (8 and 25 bytes) now resolve to their actual
full callees. The latter includes its shared RET; the following named handler
proves its 25-byte extent. All three complete parent EH graphs and every real
cleanup target are checked in `proof.json`.

Keep `/GX` for the registry tree: `/EHsc` removes a retail state reset from its
56-byte destructor. The original nonallocating placement operation is retained
for the global initializer; this compiler's standard void* placement-delete
pair adds an extra EH cleanup. The constructor, destructor, initializer, and
shutdown callback are co-located, and obsolete private class views are removed.

`class_contract.py` derived the corrected class contract. The header generator
cannot supply its required out-of-line special members and opaque aggregate
return declaration (C2600, zero passing generated variants). The supported
existing-header adoption mode accepted the complete evidence-backed header;
both consumers pass `header_adopt_lane accept`. No class remains queued. The
general header-queue formatting rewrite was discarded.

The semantic lead remains BFME1's clean
`LargeGroupAudioUpdateModuleDataCollectRegisteredKeyMap.cpp`, reviewed at the
verified submodule `cf0a80c228583af789772b794ab27abcab2debbf`; the earlier
transfer recorded donor `ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f`. Donor purpose
guides the walk; target instructions, callbacks, and vtable independently
establish the BFME2 layout, dispatch, and lifetime. No VP6 source was read.

Validation: 987 bodies and 20 data rows across the six changed sources, plus
170 bodies in the existing constructor/destructor providers; strict current
receipts; frozen-file checks; 20 complete rows and three complete EH graphs in
the focused proof; zero further `place_bodies` leads. Unique strict C++ gains
18 bytes, and game C++ gains 23 bytes including the former generated thunk.

The current provider/consumer `link_check` preview places the registry unit's
80 bytes and the key-collection unit's 247 bytes; across all eight checked
sources it predicts LINKED **5,549 -> 5,829 (+280)**. Existing unrelated
blockers remain in the broad thunk, map-instantiation, and key-registration
files. The enforced new-variant gate passes. This is a preview against the
published `8eecc93d07` index, not a new census or a measured global LINKED gain.
The pre-existing unsigned global storage declaration is retained; correcting
its full allocation/type is separate data convergence work.

The prerequisite commit retracts the old identities and their dependent
initializer so renaming is reviewable and its own hooks pass. Publish it with
the complete recovery; it is not a standalone final state.
