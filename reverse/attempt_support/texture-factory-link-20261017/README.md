# Missing texture factory vtable

Base: 0c18c898. BFME1 reference 5bb8ca80 was reviewed for factory and vtable
ownership patterns. Its partial factory views do not supply BFME2's table;
this repair uses BFME2 retail entries and already landed code providers.
The previous BFME2 direct-vtable repairs are an ownership guide only.

The rowed filename constructor132D43 installs VA BD2690. Its formerly
unprovided g_00BD2690 declaration was the texture-loading unit's sole live
linker blocker after refreshing stale census providers. Define the complete
18-entry read-only table in that existing consumer, under the existing canonical
g_00BD2690 name. Slot1 points to the independently named
MissingFactory::PreLoad at131CA5. Comparison with sibling Factory7D25D8
and RecolorFactoryDecal7D2630 confirms the 18-slot family. The rowed Camera
constructor134AB0 independently installs the next secondary table BD26D8
at134AEE and its primary table BD26E0 at134AE8, proving the boundary.
No Camera entry or guessed padding belongs to this 72-byte array.

Each pointer names an existing COFF code owner. Opaque declaration prototypes
are used only to take addresses; no call uses them and no new callable ABI or
original method identity is asserted. Shared empty slots use existing folded
code owners. targets.json records all 15 unique names and their ledger sources;
table-proof.json records the exact slot order. The original class-name and
method-name uncertainty is retained where existing owners are provisional.

Verification: all 233 rows across 16 consumer/provider units remain exact;
the array's compiler sizeof72 and every relocated pointer byte-verify. All
three EH parents are EXACT with zero baseline/missing objects. Strict new
COMDAT admission passes, and source placement finds no additional bodies or
pins. There are no new/removed COMDATs; all 15 retained digests are identical.
The constructor's raw text and symbolic relocations are unchanged.
Only the table adds a strong definition. No pin, alias, flags, header, baseline
or verifier changes. The pre-existing address-global identifier is retained to agree with the
global ledger; shadow data audit reports no new wrong-name finding.

Paired comparison against the same refreshed published index (2026-10-17
02:26 at fb06805bf5) removes the sole unresolved name in TextureAssetGet.cpp.
The unit becomes locally link-clean, covering 987 already-matched nonpadding
bytes. No finding count increases across the 16-unit cohort. Some provider
units retain independent blockers, including providers newer than this index;
this is a scoped prediction, not closed transitive linkage or a runnable game.
No census/status/history is rewritten and no full link runner is invoked.

Full original source/object, exact build and EH logs, paired comparison script
and the unchanged published index remain in ignored build/local-macos/texture-factory-link/.
