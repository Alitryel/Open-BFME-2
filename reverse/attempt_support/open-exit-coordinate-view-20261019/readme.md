# OpenContain exit: coordinate-view follow-up

Native OpenContain::exitObjectViaDoor is 0x0046525F..0x004656DF, 1152 bytes,
RET8. WorldBuilder 0x01196CE0 independently names the method and shows the land
branch's copy/subtract/normalize/copy/scale/add coordinate operations. The clean
BFME 1 OpenContain implementation supplies the earlier semantic donor but has
no land branch; it cannot resolve the remaining BFME 2 arithmetic scheduling.

Read every prior attempt at this RVA, the complete newer 0.985 bank, its complete
home OpenContainExitObjectInAHurry.cpp, the WB decompilation, the Siege exit
handoff, and the relevant canonical coordinate headers and matched math-owner
definitions. The previous dead throw and barrier are already absent from this
bank. Visible vector-copy/command bodies naturally produce native frame 0x50
and keep the matched 659-byte sibling exact according to the bank's handoff.

Normal explain_mismatch reproduces the newer bank as 1154 bytes, all calls
resolved. The two substantive defects remain: native FLD [ebp-44] precedes the
goal-view pointer load at 0x004654FB; after normalization native preloads only
delta.z before the block copy, then multiplies x/y directly from memory. The
bank preloads all three and multiplies registers, adding two bytes. Earlier
jump displacements and later shifted bytes follow from that size difference.
region-diff.txt retains the focused diagnostic. Raw COFF extents are measured
independently of the 1152-byte verification prefix.

Test fifteen additional ordinary C++/compiler variants in four groups:

1. Visible existing Coord3D::scale body, before/after target copy, including
   the real canonical Coord3DBase view; and visible Coord3D::set for the goal
   copy. Four scale/base copies stay 1154 bytes with 282 prefix differences;
   goal set worsens them to 321.
2. Opt into the supported Coord3DCtorView (with/without its real empty user
   destructor), and its header-inline operators in WB order. These genuine
   lifetime variants remain 1154 bytes with 281/282 prefix differences.
3. Use the word-copy representation of matched Coord3DBase::operator= or an
   intrinsic memcpy, before/after scaling. All four remain 1154 bytes, 281
   differing prefix bytes. Hiding the float fields behind the established raw
   assignment does not defer the x/y loads.
4. Ordinary VC7.1 G5 and G6 processor scheduling instead of G7. Both retain
   1154 bytes and the same remaining wall (281 prefix differences).

No variant improves the bank. No artificial destructor operation, dead throw,
volatile access, barrier, private canonical class, assembly, new pin or production
flag change is introduced. No Code, header or ledger file is edited, and the
stronger existing bank is preserved unchanged. The reservation is released.
No recovered-byte gain is claimed for this follow-up.

Input: 146949d8fb30b15c9968fd47787f4965a1da5e2c; verified BFME 1 dependency
6b9d92bf92debd03e4357462bab41f701651e67c. Source flags are those in the bank:
O1/G7/SSE, MD, EHs and its existing allocator/string includes; the two scheduling
trials change only G7. Model: gpt-6.1-sol, about ten minutes.

results.json preserves measurements. Copy replay.py.txt into build/NAME/trials.py
and run it with no argument, ctor, raw-copy and processor. It obtains its
immutable seed from the input revision if seed.cpp is absent. Full raw logs
remain under build/open-exit-resume-oct19; the tracked focused diff is sufficient
to distinguish the two original defects from displaced later instructions.
