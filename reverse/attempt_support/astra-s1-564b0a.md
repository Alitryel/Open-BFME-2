# 00564B0A receiver accessor

Owner astra-s1; model gpt-6-astra. Native complete eight-byte extent is
ADD ECX,0C; JMP 0047A6A9. No incoming direct E8/E9 or absolute-address
reference was found. The source therefore retains an address-derived owner
and method; no original semantic class name is asserted.

The callee has an existing rowed self() view:
?self@Rva005045DBTree@@QAEAAV1@XZ in BfmeRectVNI_ctor.cpp, RVA0047A6A9.
Its identity is independently anchored by native565402..565413: borrow the
record's +0C receiver through47A6A9, pass the result to assignment5045DB.
WB12CAB90 independently returns its receiver with no stores or calls, and
WB143ADFF supplies the same role. This existing proof distinguishes it from
an arbitrary empty math constructor sharing the same three-byte ICF body.

The nearby matched00564B12 already forwards assignment on a +0C member to
Rva005045DBTree::assign. The new source uses the same landed receiver type
with a separate neutral owner and calls its existing self method.
The eight bytes and REL32 are exact in isolated compilation.

This is not reconstructed as a constructor: an ordinary owner constructor
with a member at +0C compiles15B (save whole receiver, call member ctor,
restore whole receiver). Placement-new initialization compiles11B with a
null check. Neither reproduces the native accessor's returned adjusted
receiver. No compiler thunk or constructor ownership is invented.

Read-only helper research additionally identifies the method family with
WB ControlPointBlock::DoXfer and finds two plausible owner layouts: the
24-byte campaign-act tree record and the28-byte delayed spline-camera event.
No reference to this particular outline selects one, so those remain
structural leads only. BFME1 pinned138757e9 supplies no definition for this
outline. The production source does not apply those unproven names.

Normal add_match admission passed all 89/89 source rows including the
eight-byte accessor and its callee relocation. Source claims and string,
float and import reference gates passed. No new pin, alias or assembly
was added.
