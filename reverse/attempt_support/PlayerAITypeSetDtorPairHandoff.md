# PlayerAITypeSet ctor/dtor pair — verified design handoff (2026-10-25)

Written by glm-5.3-flash-free seat after the ctor TU verified **4/4 byte-exact**
and got wiped by a concurrent seat replaying a stale checkout. Everything below
was independently re-proven against the retail image this session.

## Retail facts (read with tools/retail_body.read_bytes)

- `??_7PlayerAITypeSet@@6B@` at 0x007E77B0 (56B): slot 0 = 0x0022E1A0 (the own
  deleting dtor); slot 1 = 0x000B3FD0, 9/10 = 0x000B3FD0 (empty overrides);
  slot 8 = 0x001B5384 etc. This proves the **virtual-dtor U mangling** and the
  class token `PlayerAITypeSet` — the rename from `Rva0022E1BC`/`Rva0022E1A0`
  label rows is retail-proven, not a hint.
- `??1PlayerAITypeSet@@UAE@XZ` retail 53B @0x0022E1BC, prologue
  `b8 b7 f8 b6 00 e8 c2 af 3f 00` = handler addr + `__EH_prolog` call; NO
  `c7 06` entry vptr reinstall; destroys `vector<BfmeVectorRecord0002154F3>` at
  +0x0C via rowed 0x0021579C, then base `??1SubsystemInterface@@UAE@XZ`
  0x001B4E74 at +0x00; `c9 c3` tail.
- `??_GPlayerAITypeSet@@UAEPAXI@Z` retail 28B @0x0022E1A0: calls this dtor then
  rowed operator delete 0x0002FD60 (`56 8b f1 e8 14 00 00 00 … 59 8b c6 5e c2 04 00`).
- Sibling retail dtors in this family (RankInfoStore 0x00200280, W3DFontLibrary,
  Shell, ThreatFinderManager) DO carry the entry vptr store — the omission here
  is real and code-shaped, not a signature mistake.

## The codegen rule that solved it (probe-proven)

MSVC 7.1 emits the dead `c7 06` derived-vptr reinstall for an **explicitly
defined** empty dtor, and keeps the compact 53B body for the **implicit**
dtor (no user declaration anywhere). Precedent: WWDebug/DebugCmdInterfaceDebug
rows "explicit-empty gives 61B two-store while implicit gives 55B exact".

Emission mechanics discovered this session:

- A TU that merely *virtual-dispatches* (`delete p` → `call [eax]`) synthesizes
  NOTHING. An implicit pair appears in the TU that constructs the object or
  otherwise emits the vtable (vptr store in the ctor COMDAT forces the vtable
  COMDAT, and the implicit dtor pair comes with it).
- Therefore put the synthesis **in the ctor TU itself**: define the user ctor,
  declare NO dtor anywhere. The ctor TU then emits
  `??1PlayerAITypeSet@@UAE@XZ` (53B byte-exact) AND `??_GPlayerAITypeSet@@UAEPAXI@Z`
  (28B byte-exact) as COMDATs beside `??0`.
- `delete`-only anchors and construction anchors hit C2259 (the shim's
  `init/reset/update` are pure) — irrelevant in the ctor TU where nothing
  instantiates and the ctor is DEFINED in-place.
- The separate `Rva0022E1BCDtor.cpp` split TU is unnecessary. Also
  `FamilyDeletingDtors_Rva0022E1BC.cpp` (QAE packet) is non-retail for this
  class and gets deleted; its tombstones are in deleted_rows.csv.

## The verified ctor TU (collapsed; restore verbatim)

File: `Code/GameEngine/Source/Common/PlayerAITypeSetCtor.cpp`
Flags line: `// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii` plus `// stlport`.

```cpp
#include <vector>
#include "ascii_string.h"
struct PlayerAITypeEntry { AsciiString name; char unknown[12]; };
typedef bool Bool;
#include "subsystem_interface.h"

class PlayerAITypeSet : public SubsystemInterface
{
public:
	PlayerAITypeSet();
private:
	_STL::vector<PlayerAITypeEntry> m_types;
};

PlayerAITypeSet::PlayerAITypeSet()
: m_types()
{
}
```

Notes that must ride along in the file header: identity from byte-verified
GameEngine::init (24B allocation, ThePlayerAITypeSet 0x009FE31C,
initSubsystem<PlayerAITypeSet> 0x0022A302); donor note (BFME1
d6db6bfa PlayerAITypeSetFind entry view is donor-derived, 16-byte entry, base
grows +8 to +0xC); `/O1 /MD` no EH matches the RankInfoStore sibling because
enabling EH adds cleanup states absent from the 33B boundary; the fully-implicit
class synthesizes both dtor COMDATs here (DebugCmdInterfaceDebug probe
precedent), retired duplicate TU note, and `/D_STLP_USE_STATIC_LIB` keeps the
allocator proxy 0x0014F3C4 external/rowed.

## Resolution of the ??1 vector-dtor call (the one real blocker left)

The synthesized `??1` calls `??1?$vector@UPlayerAITypeEntry@@V?$allocator@
UPlayerAITypeEntry@@@_STL@@@_STL@@QAE@XZ`. Retail's body at 0x0021579C is
rowed under the **element-name `BfmeVectorRecord0002154F3`** (row
30868, home stlport_vector_record_2154f3_allocate_copy.cpp). Verified options:

- **Hand-typed pin worked for byte verification** (4/4 OK with pin
  `??1?$vector@UPlayerAITypeEntry@@…` @0x0021579C in reverse/symbols.csv) but
  the pre-commit hatch gate refuses hand pins; `tools/pin_admission.py --add`
  then refuses a pin onto an already-named address under one-address-one-identity,
  and the `fold-proof` escape fails while the calling TU *suppresses* the
  instantiation with an extern-template declaration (the proof file must
  compile the pinned name).
- **The sanctioned shape is the `_Vector_base` precedent** (rows 47383 + 47384
  at 0x00211E58: two rows, one per element spelling, `gen-alias; fold-proof=…`,
  verified字节/byte-and-relocation twins). BUT `tools/add_match.py --icf-owner`
  demands the alias symbol's whole body compiled **in its home TU** — "unverifiable:
  symbol not found in object" while `template <> vector<PlayerAITypeEntry,……>::~vector();`
  suppresses it.
- **Sleeping simplest alternative** (recommended when redoing): change the ctor
  TU member to the owner spelling `_STL::vector<BfmeVectorRecord0002154F3>`.
  Then BOTH call sites of the synthesized pair bind to *already-rowed* names —
  `??0?$_Vector_base@UBfmeVectorRecord0002154F3@@…` (row 47383) and
  `??1?$vector@UBfmeVectorRecord0002154F3@@…` (row 30868) — no pin, no alias.
  Cost: the old row 47384 (`…@UPlayerAITypeEntry@@…`, home = this TU) must be
  retired (tombstone in deleted_rows.csv: subsumed by the Record-keyed owner
  after the member spelling changed; the PlayerAITypeEntry spelling stays
  donor-derived). NOTE the donor evidence says the entry is 16B; the record
  element is 16B too, so layout/ABI is unchanged — but re-verify all rows of
  the TU since the ctor's vector_base call symbol changes name. If row 47383's
  notes' "24B base offset" or proxy rows disagree, fall back to:
- **Cleaned extern-template alternative**: keep the PlayerAITypeEntry spelling,
  drop the `template <> …::~vector();` declaration, and `add_match.py --icf-owner`
  the whole 63B instantiation as an alias row at 0x0021579C (no pin needed).
  Only attempt if its internal callees (allocator/`_M_clear` chain under the
  PlayerAITypeEntry spelling) all resolve — check a build FIRST; if any callee
  reports "add to reverse/symbols.csv", go back to the Record-keyed member.

## Ledger steps (all re-diffable)

1. functions.csv: rename row 34628 → `??1PlayerAITypeSet@@UAE@XZ,
   ,0x0022E1BC,53,Code/GameEngine/Source/Common/PlayerAITypeSetCtor.cpp` (keep
   the notes from this doc; NO commas in notes); rename row 34629 →
   `??_GPlayerAITypeSet@@UAEPAXI@Z,,0x0022E1A0,28,…PlayerAITypeSetCtor.cpp`.
2. deleted_rows.csv tombstones for the two old (name, rva) pairs — text saved in
   this repo history (they were written once; reconstruct from the notes
   above if needed).
3. tu_map.csv: 0x0022E1A0 and 0x0022E1BC homes → PlayerAITypeSetCtor.cpp.
4. `git rm` `FamilyDeletingDtors_Rva0022E1BC.cpp` and `Rva0022E1BCDtor.cpp`.
5. re_attempts.log `solved` entries exist in git history; re-run
   `tools/re_log.py record` for 0x0022E1BC and 0x0022E1A0 if the log was reset.

## Verification state reached before the wipe

`./build.sh Code/GameEngine/Source/Common/PlayerAITypeSetCtor.cpp` →
`Functions: OK 4/4` (??0 33B, vector_base 29B, ??_G 28B, ??1 53B) with the
hand-typed pin in place; `find_declared_unmatched` clean;
`pin_consistency --check` OK; `check_csv` OK after removing commas from row
34628's notes.
