# GeometryInfo contact selector: control-flow and coordinate-copy evidence

Target `GeometryInfo::getBestContactPoint`, RVA `0x006BEF80`, has a complete
1082-byte extent ending after `RET 0x18` at `0x006BF3B7`. The inventory's 1079
omits that return. WB `0x006F91B0`, its Geometry.cpp diagnostic string and the
native six-argument caller establish the identity independently of matching.
The picker served a stale Pathfinder name; that proposed identity was rejected.

The full bank and current `GeometryInfoCollidesWith.cpp` owner were read. ZH
Geometry.cpp supplies the distance-helper pattern and shape enums, not the
BFME2 contact-list behavior. Native accesses establish contact stride 16 at
+0x38/+0x3C, shape stride 36 at +0x2C/+0x30, and positions +0x44/+0x50.

The new bank retains the whole owner. Native-supported changes are ordinary
Coord3D assignment instead of a scalar copy helper, nested caller/search-success
conditions with one final false return, separate label-call arms, an else-if
final height clamp, and a POD local for the selected nearest contact. The
preferred-position path calls the height getter a second time on clamping, as
native does; the old bank cached it. The interpolation path retains the cached
height and copy-constructed locals established by previous work.

With identical current inputs the old bank emits 1023 bytes; the new bank emits
1080. The diagnostic SequenceMatcher ratio rises from 0.647981 to 0.738205;
this is not exactness, not an instruction-aligned score, and not comparable to
scores recorded by earlier seats. `compile_function` patches DIR32 slots from
same-offset target data for diagnostics, even while code differs; those slots
must not be interpreted as resolved data identities or meaningful operands.
All REL32 calls resolve. The existing CollidesWith sibling still verifies all
821 bytes exactly from the bank.

Remaining: frame 0x18 versus native 0x1C (first difference +7), native best-index
stack slot versus compiler register allocation, logging/caller argument homes,
and some interpolation/distance x87 scheduling. Native first reads seed into
EDI and caller into ECX; the bank holds caller and preference in saved registers.
The origin at VA 0x00E0C140 still needs a real data owner; the probe at E0C150
uses the existing g_Va00E0C150 owner. No production source, global, pin or ledger
row was changed, and no +C++ exact progress is claimed for this bank.

Ruled out in this pass: free/member copy helper forceinline/dllimport annotations;
return-by-reference copy; distance helper, square template, reversed sum or
coordinate temporary; alternate empty ctor and local lifetimes; positive
label/collision nesting; and visible/hidden CollidesWith plus a visible verified
height-getter implementation. These are unchanged or worse than the bank.
RTM, SP1 and DDK4035 agree on the 1081-byte intermediate; /G5 and /Ob1 agree too.
/G7 regresses; /Op creates a different size-exact but much worse body. A
size-exact body is not proof. Do not repeat these families without new evidence.

Inputs: BFME2 d8961f14c218725a3dc0890fe1dcc313d533d469, verified BFME1
f52d3a5cb41976aafa760e8db12c4bfdb2be91e8. Flags remain /O2 /Ob2 /G6 /DNDEBUG
/MD /EHs-c- with the bank's existing ASCII and Lib include paths. Copy the bank
to a unique build/ path, then run tools/explain_mismatch.py with the exact
decorated symbol, --rva 0x006BEF80 --size 1082 and --source that path.
The included old source, baseline/final diagnostics, sibling check and trial
results preserve the comparison; the trial driver records all tested shapes.
