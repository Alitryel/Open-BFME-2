# WWLib helper selection repairs, 2026-10-20

Paired legacy link previews gain **819 existing nonpadding matched bytes**;
new authored C++ bytes: **0**. Index: `b73720bed9`, 2026-10-20 05:34,
`retail-truth-2`. Before/after object replacements were evaluated against the
same published index, in memory, without a census or index/status publication.

| Repair | Newly linking unit | Bytes |
| --- | --- | ---: |
| Retire unrecovered StringClass MixFileCreator helpers | MixFileCreatorFileInfoStructAssign.cpp | 349 |
| Keep StringClass construction and Set_Shader inline, suppress external copies | MaterialPassInstallMaterials.cpp | 271 |
| Rowed ModuleData push_back plus native delimiter literal | Rva0028900AParse.cpp | 199 |

The attached paired JSON records object hashes, blockers and current strict
receipts. These are legacy LINK preview gains, with self-strict byte receipts
for each object; **closed-strict gains were not measured**. No full link cycle,
census, nightly or boot runner was invoked.

## MixFileCreator

`mixfile.cpp` emitted a competing implicit FileInfoStruct assignment based on
the donor's StringClass record. The rowed assignment at RVA `0x002174DF` uses
AsciiString, as its existing source/byte proof establishes. Remove the
unrecovered creator/makemix section that instantiates the wrong record, retaining
the `_SimpleFileFactory` datum. The complete donor implementation remains at
BFME 1 revision `a2c8039e61ad4dfb20c095d8eafe048248d31f25`,
`game/Libraries/Source/WWVegas/WWLib/mixfile.cpp`.

All retained COMDAT bodies are unchanged, no COMDAT is added, and before/after
data-check facts agree. Both units' 28 matched rows pass. The assignment owner
loses its sole selected-definition blocker and links its existing 349 bytes.
`mixfile.cpp` itself remains unlinked: other StringClass/FileFactory/vector
copies and Windows imports still block it. Four references from its unrecovered
helpers now lack creator definitions. The index reference graph has no other
external incoming references to those removed creator functions; no formerly
linked unit relies on them. This repair does not claim the mixfile unit's bytes.

## Material installation

The unit's inline StringClass constructor and forceinline shader setter emit
nonretail external copies. Importing those inline definitions preserves their
inlined operations and suppresses their external copies, also eliminating the
unused StringClass destructor copy. All retained nondebug sections, bytes,
flags, definitions, relocation referents and data-check facts agree exactly.
Both rows pass, including the parent and EH handler. The unit's existing
271 bytes now link. Three unreferenced helper diagnostics remain nonblockers
under `retail-truth-2` and were left alone.

Other units with the same helper names have additional independent blockers
(LineGroup, PointGroup, sortingrenderer, box/sphere and decal units); suppressing
these two names alone would not link them.

## SplitUpgrades

Declare the existing vector<const ModuleData*>::push_back specialization so the
call binds to the rowed body at `0x004DFCB0`, without emitting another copy.
Replace the unresolved address-named delimiter with the exact native literal:
RVA `0x007BE7A4`, bytes `20 0a 0d 09 00` (space, LF, CR, tab, NUL). These bytes
are target evidence; the upgrade-parser identity and loop are unchanged.

The complete 199-byte body, literal references and named strtok import pass.
All retained COMDATs except the verified parent's changed string relocation
are identical; removed placement-new/Construct copies were only dependencies
of the removed external push_back copy. The only new COMDAT is the delimiter.
The current object has no link blockers.

## Acceptance and handoff

- `./build.sh` passed for each changed unit; all 31 rows across the three
  changed sources and the assignment owner also received strict reusable
  receipts through `link_check.py --prepare-current`.
- `find_declared_unmatched.py` passes for every changed source.
- `git diff --check` passes. No pins, aliases, protected lists or tools changed.
- `name_globals.py --dry-run`: zero eligible rewrites.
- `rehome_rows.py --limit 12`: zero movable units after examining its 92-pair
  candidate cohort; one claimed source was skipped.
- DX8 Vector4 suppression cannot link its owner while five earlier nonretail
  Set_Transform providers remain; a required provider is held by another seat.
  Recorded through re_log.py and released all associated claims.

Session diagnostics and original objects are ignored under
`build/link-seat-20261020b/`. The attached paired JSON is the durable evidence.

## BFME 1 freshness

Advanced the previously verified pointer `a2c8039e61ad4dfb20c095d8eafe048248d31f25`
to official master `0dc8a26a9c6041c73dc564754cd059dc54faa72a`, preserving the
clean donor checkout. The old-input full gate and updated-input full gate at
BFME 2 HEAD `6dea4f6a1f` both passed all 97,317 functions and 1,116 data rows;
no pre-existing failures or update regressions were observed. The local repairs
also passed their scoped gates and strict receipts independently.

The upstream source delta is limited to Rva0058D820Palantir.cpp,
DebugExceptionhandler_LogRegisters.cpp (own the EDI label), and
memorypool_allocator.cpp. No headers, toolchain or flags changed. BFME 2's
ledger imports none of those donor TUs; its separate LogRegisters copy is
unchanged. This linking cohort has no affected donor compile trial cache, and
no BFME 1 sweep cache was present to retain at a stale revision. Earlier donor
linking repairs had already been reviewed in this seat; these new deltas do not
supply an applicable repair for the current helper-selection blockers.

The existing resolver selects `game/`, `inputs/reference/`, `inputs/toolchains/`
and `targets/game/reverse/`. Checked that the resolved directories exist, plus
WWLib/mixfile.h and the ZH GameEngine/Include/Common/STLTypedefs.h. The prior
layout migration remains valid; no silent substitute header was introduced.
The ignored freshness stamp was written only after the updated full gate passed.

`freshness-baseline.log` SHA-256: `9d16236289a07a0867bfbdf9c2a90c2978173e4156509ad9cf7b74913f4a343e`.

`freshness-updated.log` SHA-256: `6cd756fb0f868d7f1148acf96307af87cece5eb3dc94ebad7050e8509d10eff9`.
