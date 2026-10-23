# HLOD class ownership prerequisite

At BFME2 `54a521e4` with pinned BFME1
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`, fresh actual objects verify all
162 rows across `hlod.cpp`, `HLodModelArrayDeletingDtor.cpp`, and
`Rva0017FFCABase.cpp`. The same published index `5366c4f808` holds all 14,856
nonpadding bytes out of the link: 14,709 + 30 + 117 respectively.

The previous `hlod-destructor-link-20261020/README.md` applies. This pass
tested different class and first-header compiler contexts, not another fake
inline-destructor or post-header size anchor.

## Native ownership evidence

The 67-byte ModelArray constructor at RVA `0x0019F500` constructs the real
DynamicVector base, initializes the four-float tail at offsets 0x18–0x24,
and installs vtable VA `0x00BD69C8`. That table contains these six native
function pointers:

```
0059EF10 0059E6A0 0059E9F0 0056FED0 0059E980 0059E9C0
```

Its first slot is the array/vector deleting destructor at RVA `0x0019EF10`,
not the standalone scalar wrapper at `0x0019F4E0`. The latter remains a real
30-byte wrapper calling the genuine complete destructor; this evidence does
not establish that it is absent from retail.

The 45-byte complete destructor at `0x0019E580` installs base vtable VA
`0x00BD6720`. Its six slots are:

```
0059EB20 0059E6A0 0059E700 00554A30 0059BDC0 0059E9C0
```

BFME1's actual `game/Libraries/Source/WWVegas/WW3D2/hlod.h` supplies the
40-byte ModelArray class with a DynamicVector<ModelNode> base and four floats;
ModelNode is 20 bytes (render object pointer, bone index, Vector3 offset).
The current scalar fixture's eight-byte private class and one-slot table
cannot represent that construction contract.

## Fresh controls

- Placing size optimization around the **first** `hlod.h` include makes the
  HLodDef scalar deleting wrapper exactly 28 bytes at `0x0017FEA5`.
  It preserves 154/156 home rows but changes the ModelArray constructor and
  complete destructor. It is not a valid repair by itself.
- Using the genuine donor header with the existing ModelNode Resize provider
  declaration and an unused static automatic-local anchor emits no ModelArray
  scalar wrapper. Retaining the original external `famgenDelete` also does not
  cause that wrapper to be emitted.
- An external automatic-local diagnostic emits the exact scalar wrapper but
  adds a synthetic emitted anchor and a scalar vtable variant. It was rejected
  as a production solution.
- A corrected local view with the actual DynamicVector base, 20-byte node,
  four-float tail, constructor declaration and empty noinline derived
  destructor emits the exact 45-byte complete destructor but no scalar wrapper.
  The original external `famgenDelete` was retained unchanged in this control.
  Thus replacing the fake field write with real base cleanup alone does not
  satisfy the existing scalar row.

An earlier isolated header-only scratch compile entered a Wine exception loop
(sampled in `ntdll`'s `segv_handler`/`setup_raise_exception`) and was terminated.
That run supplies no compiler-shape result; the controls above used ordinary
`build.sh` against the claimed tracked paths.

The remaining prerequisite is coherent constructor/destructor ownership and
a shared class definition, with scalar and array wrapper identities kept
distinct. A shared-header change requires the full gate; the current batch
cannot verify that while the independent W3DDisplayDraw SDK issue is pending.
All production source edits were restored, claims released, and no new
recovered or linkable bytes are credited.
