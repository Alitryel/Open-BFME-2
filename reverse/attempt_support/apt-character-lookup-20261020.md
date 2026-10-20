# Character lookup: owned contracts and bounded source controls

Target `Rva006EFBC0ObjectMemberLookup`, independently named by WB1784910 as
`AptCharacterInst::objectMemberLookup`. Read the complete 603-line bank, all
RVA-specific log entries, the earlier Astra evidence JSON and complete native/
WB disassemblies before trials. Input revision: BFME2
`f49f5687dcd0233c1a9c9423e5254f7bc1a22715`, BFME1
`b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b`, stock VC7.1, bank O2/NDEBUG/MD/EHsc.

## Boundary and measurement correction

The executable native body is 5501 bytes, ending at exclusive6F113D. Three
alignment bytes precede dispatch tables at6F1140: 84 bytes,16 bytes,204 bytes
and127 bytes, ending at exclusive6F12EF. Full code/alignment/table extent is
5935 bytes. The CC at6F12EF is padding before the separately owned22-byte
sized-delete helper at6F12F0. Earlier5936-byte comparisons included that CC.

`align_diff.py` searches for four consecutive CC bytes near its size hint.
Here it skips the one-byte pad and next helper and reports5958. Its old full
instruction counts also decode dispatch-table bytes as instructions. Do not
treat those counts as an exact function comparison. The retained scratch
metrics find the first table from contiguous DIR32 code-label relocations and
compare only executable code plus alignment, excluding relocation-backed
operands from the defect counts. Native code/alignment ends at+5504.

## Contract repair retained in the bank

Replace nine provisional callback declarations/addresses with the current
verified owners: GetBounds6EC730, LocalToGlobal6ECCB0, AttachMovie6ED580,
CreateTextField6ED810, SwapDepths6EDBD0, CreateEmptyMovieClip6EDFF0,
ApplyTextFormat6EF570, TextFormat6EF6D0 and TextFormat6EF920. Their complete
current rows establish the pointer-returning cdecl context/count ABI. These
are existing owner spellings and physical bindings; historical misnomers such
as Rva006EDF20SwapDepths are not new semantic claims about that callback.

Use the rowed int-returning rva006E02B0 and isCharacterInst contracts with
retail's low-byte tests. Use the real Rva006DBB30SarDwordField getter and
BfmeAptValue checked-cast/isCIH/isUndefined owners instead of old private alias
spellings. The inline checked-cast adapter forwards directly to the already
verified57-byte provider; no new pin or forwarding row is added.

The primary bank still emits5915 bytes. Machine shape is unchanged, but its
one unresolved REL32 is gone and callback ownership is explicit. Under the
same legacy diagnostic fitness, baseline is0.7892895857 and the retained
canonical-cast body is0.7895675820. This is binding/readiness progress, not a
new exact match. Main register and float cross-jump differences remain.

## Controls and useful alternative

There were34 caller compilations: owner/ABI controls, complete barrier removal,
inline character accessor, fourteen direct numeric-return cases, direct float
expressions, real checked-cast visibility, G6/G7 sibling settings, the true
static method identity, typed instance pointer, the existing float provider's
class view/body, real predicate inlining, debug-break intrinsic, common virtual
prefix view and GC-root setter visibility. An early Ob1-before-O2 control is
not relied upon; an explicit trailing Ob1 control was also run.

The visible providers independently remain exact: checked cast57 bytes,
predicate75, GC-root setter73 and float factory263. None repairs the parent.
These facts do not prove the copied class views' complete ABI or vtable data.
The ordinary/inline predicate reproduces the manually expanded shape; forcing
both calls inline gives5931 bytes and does not fix the register roles.

Removing all three inherited compiler barriers and the redundant scroll
conditional gives6331 bytes. Direct numeric returns/expressions give6287/6223,
with more genuine structural differences. G6 is unchanged; G7 regresses.
The source without the redundant conditional and with intrinsic debug breaks
is a useful5891-byte alternative: code-only structural regions40->37, memory
defects120->51, register defects102->76. Raw-code diagnostic fitness improves
0.59598->0.67606, while the old mixed code/table patched metric drops to0.78116.
Keep it alongside the stronger primary bank rather than silently replacing
the score/metric. It still has three inherited barriers and is diagnostic.
The primary bank also retains its inherited barriers/conditional: neither
candidate is ready to land as production C++.

The read-only AptValue contract sample reports sizeof4 by majority with no
retail field witness, and queues virtual slots2/3 (ForceDelete versus unnamed
slots; GetNativeHashVirtual versus unnamed slot3). Native base/CIH/float
vtable prefixes and existing constructor views do not justify adopting a
complete header from that sample. No header or class registry was written.
Resolve these contracts from independent evidence before a scope-wide change.

Both the typed-unit placement rescan and the already owned post-table helper
yield no additional recovery. No Code, ledger, pin, verifier or baseline edit
is made by this investigation. About25 minutes, gpt-6.1-sol.

Replay the retained `.py.txt` driver from build/ with phases `contracts`,
`returns`, `cast`, `flags`, `identity`, `float`, `predicate`, `shared` in order.
It freezes its seed/provider source at the input revision above. The metrics
driver operates on their normally compiled objects. Summary comparisons, the
unresolved contract output and the useful alternative are retained here;
all trial sources/full diagnostics remain in build/apt-character-contracts-oct20/.
