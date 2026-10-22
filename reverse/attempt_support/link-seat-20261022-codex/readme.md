# Link-repair handoff, 2026-10-22

Inputs: BFME2 f8580668b5; published census 08160bc2c9 (2026-10-22 17:08);
BFME1 retained committed 42bba2ddbd5cb895d99293583891d3b7315fa49e.
Compiler: MSVC 7.1 under Wine, existing per-unit flags. Model: gpt-6.1-sol.
No measured linked-byte gain is claimed. All experimental Code/header/ledger
changes were reverted; the patch is diagnostic evidence only.

## DefectorSpecialPowerModuleData constructor, RVA 0x004C2A6A, 26 bytes

Target evidence: rowed native constructor calls SpecialPowerModuleData at
0x004930A0, installs folded vtable 0x00C5E7A8, and zeros FatCursorRadius at
+0x7C. The independent FatCursorRadius parse entry at 0x00C5C764 also uses
+0x7C. The donor declaration-only SpecialPowerModuleData view ends at +0x74.
The identities and eight-byte extent difference are supported; the meaning
of the missing eight bytes is unknown.

Best candidate: defector-layout-rehome.patch adds a TU-scoped copy of the
BFME1 declaration-only shim with eight unidentified tail bytes, repoints the
constructor row into DefectorSpecialPower.cpp, and deletes the now-redundant
flat constructor unit. No other class declarations or bodies are changed.
The home unit passes 5/5 rows (125 B), and strict explicit-provider preparation
passes all 8 rows in the home and two consumer units. A direct constructor
comparison also reproduces all 26 bytes and relocations. Donor semantics are
retained; the target-only tail is a structural inference from field offsets.

Measured before: Defector home 99 B, flat ctor 26 B, FriendNew 84 B do not
link; ModuleDataFriendNewFactories84 already links 168 B. Default legacy
preview retains the deleted flat object's strong constructor, so the rehome
still reports a duplicate and no gain. --refresh --current-ledger excludes
retired objects, but refuses 11,984 objects lacking current compiler evidence.
One initially missing GUI provider was compiled read-only and passes 11/11;
the subsequent compiler-evidence prerequisite remains. Do not run a full
census/whole-tree refresh from this seat to resolve it. The self-strict
receipts establish bytes only, not a closed-strict link result.

A separate trial retained the flat row owner and made the donor constructor
inline. This removes the unwanted strong definition, but also drops both
rowed module-data destructor bodies: 2/4 rows fail as missing symbols. Reverted.
Earlier attempts that simply deleted the donor constructor have the same
failure. Resume the best patch when a receipt-current provider universe is
available, or reconcile explicit destructor emission as real class work.
The transient add_match landed log entry is superseded by the blocked record;
no constructor rehome was committed.

## Render2DClass::Render, RVA 0x0011A040, 7476 bytes

Legacy preview still rejects non-retail Set_DX8_Render_State and Set_Shader
COMDAT copies. Two trials annotated their existing declarations/definitions:
(1) __declspec(dllimport) __forceinline throughout;
(2) declaration __declspec(dllimport) void, definition __declspec(dllimport)
WWINLINE. Both fail 35/41 rows: parent StringClass terminator load/store order
changes, and 34 cleanup funclet labels shift. This is a codegen dependency,
not an accepted helper-suppression repair. Original source restored and passes
41/41 rows plus the existing data checks. No gain. Do not repeat these two
attribute spellings without evidence addressing the parent/funclet changes.

## Queue review

link_rank --top 30 / --near 2, class_views --blockers, repair_queue.py link,
and current link_check previews were reviewed. Many census leaders already
link in the current tree; historical census-to-current differences are not
this session's gains. name_globals.py --dry-run found zero authored changes.
rehome_rows.py --limit 20 tested its dry-run candidates and found three exact
moves; LivingWorld entry ctor and its destination already link. The other
pairs also already link (four units, 1,962 B before any edit). Remaining top failures
require class contracts, missing recovered callees, or compiler-shape work;
see existing per-RVA attempt records before retrying.

BFME1 upstream was fetched, but its submodule path is claimed by another seat;
the verified committed pointer was retained and no freshness success was
recorded. No maintainer-only verification runner was started.
