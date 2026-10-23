# FXShaderGeometry::Init — exact recovery, 23 October 2026

Retail `0x0018C84E..0x0018D16B`, 2,333 bytes, RET4. The production home is
`Code/Libraries/Source/WWVegas/WW3D2/FXShaderGeometry.cpp`. The incoming bank at
`c2113da648` was 2,333 bytes with nine differing bytes in seven instructions in
the two-bone remap block; EH and all parent calls were already exact.

## Evidence and fix

WorldBuilder `0xA39110`, its source assertions and calls establish the method
identity and inline accessor structure. Target accesses establish the partial
object layouts, effect slots and bone stream offsets. STLport 4.5.3 is the
semantic source for vector/iterator operations. The address-derived helper and
application element names remain structural views, not recovered original
container/type identities. Earlier target/WB findings are in
`../fxinit-wbinline-20261020/readme.md` and the subsequent banks.

Replacing the reduced signed-short vector with the real STLport implementation
was insufficient alone. The winning combination also makes the complete native
resize provider visible: resize `18C7E5`, fill-insert `18C600`, overflow `18C41E`
and the unsigned-short erase path. Their original source was
`Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0018C41E.cpp` at `c2113da648`.
This preserves the existing two-bone statement and in-arm position/normal copies,
and changes MSVC 7.1's interprocedural allocation context to retail's registers.
No inert local, artificial call, asm or optimization override is used.

A 64-case visibility matrix varied ordinary/diagnostic packing, provider
placement, resize/fill noinline attributes, overflow visibility and erase
visibility. Thirty-two variants compiled; sixteen were exact. Late explicit
overflow specializations accounted for the other thirty-two compile failures.
With real overflow instantiation, making unsigned-short erase opaque restored
the nine-byte mismatch. A 36-case ablation of fill visibility, copy specialization,
resize inline/noinline and erase instantiation placement had eighteen exact
results, precisely those retaining the full fill-insert body. Neither resize's
inline attribute nor the extra explicit erase instantiation mattered.

The real iterator operation resolves a preparation defect in the bank: its
non-template `__distance` overload had a different name from the existing
provider. Iterator comparison/increment now let STLport instantiate its actual
`__distance<Rva005E59FCKeyIterator>`, retaining all 169 bytes and relocations of
assign `18C73C`. MSVC rejected dependent-return explicit specializations; making
assign opaque changed the parent to 2,339 bytes. Natural instantiation is exact.
The three emitted unpinned cursor/accessor definitions are honestly marked
present-unmatched; no independent retail address is claimed for them.

## Verification and integration

The production object reproduces Init, its native helper `18C131`, and all eight
rehomed helper bodies (18C41E, 18C600, 18C7E5, 18C3C9, 18C705, 18C73C, 18C088,
18C732) with complete bytes, exact extents and resolved relocations. The former
three helper units are retired to avoid duplicate strong definitions.

The parent EH graph is EXACT, binding cleanup locations through its actual
unwind map at `90D65C` and FuncInfo `90D69C`. Three previously open 10-byte
cleanups at `768841`, `76884B`, `768868`, and the 10-byte handler at `768872`, are
rowed from the same production object. Existing generated cleanup rows remain.
Parent and handler admission passed `add_match_batch.py`; helpers passed
`add_match.py --replace-existing`. Source flags remain `/O1 /G7 /arch:SSE /MD
/DNDEBUG /EHsc`, with STLport and the established BFME allocator shim.

Private experiment sources, output and the two visibility matrices remain in
ignored `build/fxinit-coalesce23/`. Production source is the reproducible winning
candidate. The speculative owning/cache-life families written in that scratch
script were never run and are not negative evidence.

The link preview exposed a previously unbound `vector<short>` destructor. Its
complete 14 bytes and free30830 relocation match the native `768860` cleanup's
tail destination `7FAB3`, already owned by the folded storage destructor family.
`pin_admission.py --add` admitted the template with this unit as `fold-proof`,
including every owner/gen-alias relocation. `pin_consistency.py --check` passes.
This lets link checking recognize that both the existing `_free` copy and this
unit's C++-linkage free copy are retail's body. The one new admitted hatch record
is retained; unrelated automatic stale-baseline normalization was reverted.

The supported local `link_check.py --update-index` refreshed provider definitions
and dropped retired ledger units; the subsequent scoped preview reports LINKS,
with this file's LINKED bytes 305 -> 3,319 and no blocking duplicates/unresolved
names/COMDATs. No link.exe or maintainer-only runner was started. This is a
preview against the published census refreshed locally, not a new census.
The stricter `--refresh --current-ledger` check could not run to completion:
11,042 unrelated cached objects lack its strict compiler receipts. That existing
repository-wide evidence gap is separate from the passing scoped link preview.
`check_csv`, `find_declared_unmatched`, `eh_verify`, pin admission/consistency,
and the normal source byte/string/float gates pass. `place_bodies` reports zero
additional bodies and zero pins.
