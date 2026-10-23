# MeshClass::RecolorHouseColor: ownership-type controls

Target `?RecolorHouseColor@MeshClass@@UAEXABVRva0013101E@@PBD@Z`,
RVA `0x0014C470`, complete 2,291-byte `ret 8` body. The existing
`reverse/attempts/0x0014c470.cpp` remains the best bank and is unchanged.
Read the earlier
`reverse/attempt_support/0x0014c470_20261020_w2_wb_accessors.md` first.

Inputs: BFME2 `413ecd9e74b1c122e930f26a1f9d3099f4ad6d20`, committed
BFME1 `92f6bbe8e1dcdb46b5d27da0674313efc822b790`, MSVC 13.10.3077,
bank's `/O2 /G7 /arch:SSE /EHsc` flags. Each scratch translation unit lived
five directories below the repository root. Compiles used
`build.compiler_command` and private object paths, never `build/match`.

The baseline reproduces 2,291 bytes, all calls resolved, and 71 differing
bytes after normal relocation resolution (0.969009 positional equality).
The remaining differences are the previously documented stack slots.

## New controls and results

| Control | Bytes | Differing bytes |
| --- | ---: | ---: |
| Existing bank | 2,291 | 71 |
| Mesh holder's proven zeroing default constructor | 2,291 | 71 |
| Mesh holder's proven nontrivial copy constructor | 2,291 | 71 |
| Both constructors | 2,291 | 71 |
| Both plus provider's local-pointer destructor spelling | 2,291 | 87 |
| Implicit instead of explicit AsciiString lookup-key conversion | 2,291 | 71 |
| AsciiString derived from StringBase, natural base destructor | 2,291 | 71 |
| Same derived string with force-inlined base destructor | 2,291 | 71 |
| Annotation/index operation moved into a force-inlined helper | 2,291 | 71 |
| Lookup/key operation moved into a force-inlined helper | 2,291 | 71 |
| Both helpers | 2,291 | 71 |
| Diagnostic shared index/key union with placement construction | 2,320 | 1,174 masked |

The holder controls restore the special-member contracts in the exact
provider `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMeshHolderHold.cpp`:
default initializes the pointer to null; copy increments the pointee's
DWORD reference count at +4 when non-null. Those constructors are absent
from the bank's view. Restoring them does not affect this caller.

For the string controls, private scratch copies of the canonical headers
restored `AsciiString : public StringBase<char>`, with actual base
initialization in the default, text and copy constructors. The derived
destructor was empty and the base owned the single `releaseBuffer` call.
`str()` and `isEmpty()` retained the canonical one-pointer representation
and operations. Both natural and forced-inline base destruction emitted
the same complete parent body as the baseline. No production header changed.

The two helper controls moved the existing operations without changing them:
one force-inline helper performed the annotation lookup, local `int n`,
GetInt/range check and handle assignment; another performed the existing
reference-taking record lookup with its AsciiString temporary. Their
combination was also inert.

The union trial was diagnostic, not a candidate for landing. It explicitly
shared an aligned POD union between the index and placement-constructed
AsciiString, with an explicit destruction after the nonthrowing lookup.
Its substantial regression provides no evidence for replacing native
ownership with manual storage. It was not subjected to an EH acceptance gate.

## Independent target checks and conclusion

WorldBuilder `0x009CC5B0` confirms the ordinary local index initialized to -1,
GetInt followed by the 0..1 range check, and the key temporary's immediate
construction, reference-taking lookup, and destruction
(`0x009CCB73` through `0x009CCB9C`). The parameter getter at `0x009B35E0`
returns `this + 0xC`; the lookup at `0x009CD190` takes a reference.
The COM GetInt declaration is the ordinary `HRESULT __stdcall` interface
contract. These checks supply no missing extended lifetime.

This pass rules out missing holder constructors, the flattened string base
relationship, implicit conversion spelling, and inline-helper ownership
as explanations of the stack grouping. It does not establish that the
function is unmatchable. Resume when there is new compiler/lifetime or
source evidence; retain the earlier 0.969 bank rather than repeat these
controls or remove live computation to force its slots.
