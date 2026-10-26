# SpecialPower canonical-string prerequisite, 2026-10-26 (codex4)

Allocated family-A shard-1/2 target: `Code/GameEngine/Source/Common/RTS/SpecialPower.cpp`.
This is a prerequisite repair, not a merge or a new match. The supported RTS
planner was reviewed and refreshed after the source change. Current routing and
`tu_skeleton.py --merge ... --dry-run` authorize the trial, not the planner.

## Verified improvement

The constructor donor `Common/Rva003B1101Ctor.cpp` privately declared an
`AsciiString(int)` constructor. Composition with canonical AsciiString made its
four `(0)` initializers ambiguous. Include the canonical header directly with
its existing BFME_ASCII_DTOR_DECL switch, and default-construct those members.
The declaration-only destructor keeps retail's existing unwind calls.

`header_adopt_lane.py accept --class AsciiString Code/GameEngine/Source/Common/Rva003B1101Ctor.cpp`
passes and retires exactly one AsciiString header-queue entry. No shared header,
row, identity baseline or data key is changed. No recovered C++ bytes and no file
reduction are claimed for this repair.

Before trial: only the constructor donor, 12 rows, accepted. After trial:
constructor + `Rva003B1546Dtor.cpp` + `SpecialPowerStore.cpp`, 17 rows accepted.
The additional five rows are 227 bytes: destructor/deleting destructor/EH/unwind
at 003B1546/003B17F3/0078213C/00782129 (190 bytes), and the store constructor
003B11AD (37 bytes). This demonstrates an unblock; Luna has not landed this TU.
The donors remain separate for its normal merge lane.

## Acceptance and binding evidence

- `./build.sh Code/GameEngine/Source/Common/Rva003B1101Ctor.cpp`: all 12 rows exact;
  the header adoption command independently accepts the file.
- `find_declared_unmatched.py` on the constructor, store, find and parser: all
  definitions matched. `eh_verify.py` constructor: one EH row EXACT, zero missing.
- `allowed_symbols.py --source` constructor: 14 references, 12 owner, one EH,
  one existing alias, zero wrong bindings.
- `data_check.py` constructor: its one pre-existing 009FEFA4 wrong-name key
  survives, zero outside baseline. This header repair does not retire it.
- Official before objects were saved in `build/codex4-specialpower/`; scratch
  `header-proof.py` compares external code definitions, relocations, data,
  undefined closure, COMDAT selections and row data bindings. All agree except
  the intentional helper replacement: AsciiString(int), 11B ANY COMDAT digest
  431f5c99fd6f, becomes AsciiString(), 6B ANY digest 595907fb5146. The latter is
  identical to its officially built ledger owner's definition in
  `Code/Libraries/Source/WWVegas/WWLib/ascii_string.cpp`, RVA 00326BE6. That whole
  owner also builds successfully. There is no changed row call binding.
- The saved official objects for SpecialPowerStoreFind,
  SpecialPowerStoreParseSpecialPowerDefinition and SpecialPowerStore compare
  unchanged (code/data definitions, relocation digests, references, COMDATs and
  directives). Their original combined build passed 18/18 rows.
- Dry-run evidence: `build/codex4-specialpower-before.txt` and
  `build/codex4-specialpower-after-header.txt`. No composition was applied.

## Remaining prerequisites and scope

The template destructor still privately redeclares StringBase and now reports
that collision. Parser composition requires friend_getFinalOverride and
setNextOverride in SpecialPowerTemplate. Find and assignment trials still have
Overridable declaration ordering/layout and StringBase conflicts. Mixed donors
remain unsplit. The prior 2026-10-25 report accepted only the destructor; the
current before/after trials supersede that stale acceptance set.

SupplyCenterProductionExit was also probed without edits or claims:
`tu_skeleton.py --plan` currently routes five rows, and `--merge ... --dry-run`
accepts none (build/codex4-supplyexit-before.txt). Missing pool method, undefined
UpdateModule constructor base, conflicting module interfaces and STLport
allocator<char> redefinition remain. No speculative repair was applied.

The complete pending path audit remains the GameAudio donor move documented in
`consolidation-gameaudio-20261026-codex4.md`: no paths change in this repair and
no new active path consumer is introduced. Old historical census and evidence
references remain intentional. The audio merge's source/ledger/register checks
and scoped provider/consumer proof remain valid. The current fetched census at
47e030bafc is stale for this checkout; no linked-byte gain is asserted.

Keep constructor, destination, relevant consumer and evidence claims while the
batch is unpublished. Release speculative claims and release these after the
runner confirms publication. The abandoned transitive header file was removed
and its claim released; direct canonical inclusion satisfies the adoption lane.

## Separate data-identity cleanup

After the canonical-header commit, the same constructor now declares the real
`BitFlags<116> KINDOFMASK_NONE` global (forward-declared class template), casting
its address to the existing 28-byte fixed-storage view at the four copy sites.
No second global symbol or class definition was introduced. The current data
ledger records that mangled owner at 009FEFA4, defined by ThingIsAnyKindOf.cpp;
its name/placement and seven-zero-dword storage are existing target facts.
The ledger retains provisional status: this change does not promote its provenance.

`./build.sh` constructor still passes all 12 rows; `data_check.py` now reports
zero findings, and `repair_queue.py retire data` retired its one proven-fixed
key. `hatch_counters.py --update` removes exactly its one obsolete alternatename
(3953 -> 3952); all other entries survive. `allowed_symbols.py` still reports
zero wrong bindings; the frozen-file check passes. The provider
ThingIsAnyKindOf.cpp is built independently. This retires one data key and one
hatch, independently of the earlier header-queue entry. No code-identity key,
new matched bytes, file reduction or census gain is claimed for this cleanup.

Scratch `data-proof.py` compares the saved official pre-cleanup object with the
current official object. Defined symbol names, external data and COMDAT
selections agree. Undefined closure and every row's data-binding facts change
only the four intended references from the old name to KINDOFMASK_NONE at the
same retail address. The row byte verifier covers their resolved relocations;
the previous indirection to g_00DFEFA4StoragePrototype is gone. Other users and
their recorded duplicate-definition/wrong-name debt remain outside this scope.
No paths moved, so the existing full pending Audio path audit is unchanged.

The post-data-cleanup dry-run also accepts the same three donors and 17 rows
(`build/codex4-specialpower-after-data.txt`), confirming the demonstrated unblock
survives the data repair. The data-owner build succeeds; all helper code digests
also agree after normalizing only the intended old-to-real data symbol.

The pending path audit was rechecked before the data commit. `git diff
--name-status origin/master..HEAD` includes incoming changes because upstream
advanced. The true outgoing side from merge-base 66a8afdbdc contains only the
Audio move plus this fixed-path prerequisite/evidence. Searches across tools,
hooks, workflows, Code, docs, reverse and build.sh find the old Audio basenames
only in historical link_status.csv, evidence and preserved merge provenance;
there are no active old-path consumers. No regenerated TU map is included.
