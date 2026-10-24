# Reconcile the opaque twelve-byte deque payload

Native `0x00586204` (45 bytes) calls construction `0x002CA82C` (29 bytes)
and the growth auxiliary `0x00585B1E` (109 bytes). Construction copies three
words without reference counting. The auxiliary copies three scalar floats
into a temporary before reserving a map slot, allocating 120 bytes, constructing
the element and advancing the end iterator. The previously matched sibling
`stlport_deque_float3_push_back.cpp` supplies the same native operation.

The BFME1 donor at `6d943426` supplied the original STL operation lead; its
owning-string payload was an unsupported target layout inference. Other BFME2
consumers used three integers. The native copy/growth instructions support
three floats at offsets 0/4/8 and no owning subobject. The original application
class and field names remain unknown. The explicit copy constructor is a
compiler-shape inference. The retained generated type spelling is not a newly
recovered application identity.

The existing class-contract tool records the original conflicting views and
their unresolved names; it cannot infer this template payload from a member
ledger row. The fixed shared header follows the direct native helper evidence
instead of the contract's integer majority. The existing header adoption lane
proved all four consumers, registered the header and left no queued consumers.
The empty default constructor preserves the uninitialized transfer temporary.

The provider uses the verified sibling's compiler settings and allocation shim.
Its map reservation projects the existing BfmeE12 deque storage view: two
16-byte iterators followed by map pointer and size. That helper reads header
and pointer data, not payload data. This does not establish shared application
element identity. The transfer consumer declares the actual external push_back
provider instead of emitting another auxiliary under its old compiler context.
The synthetic anchor is removed in favor of explicit template instantiation.

The emitted constructor and auxiliary are complete byte-and-relocation twins
of existing owners, admitted as `gen-alias` rows. They add no unique recovered
bytes. Both old pins are deleted; no pin, tool or baseline is added.

## Verification and linkage

`body-proof.json` compares all 11 ordinary matched bodies in the five-unit
cohort strictly, clearing alias notes before resolving and comparing their
entire native bodies. All bytes and relocations match; nothing is unresolved.
Compiler EH/unwind rows are handled separately by the normal build gate.

The paired current-object `link_check.py` preview used the published follower
index at `eb0c43632a` (2026-10-24 10:04), with the same five explicit sources:

| Unit | Before | After |
| --- | ---: | ---: |
| Gen deque push_back | 0 | 45 |
| Gen deque transfer | 0 | 212 |
| Float3 auxiliary | 109 | 109 |
| Horde transfer | 409 | 409 |
| Horde melee attack positioning | 3196 | 3196 |
| Total | 3714 | 3971 |

The net gain is **257 existing matched nonpadding bytes**. It is a scoped
current-object linking prediction, not a new census or a closed-strict result.
The 138 aliased helper bytes and already-linking consumers are excluded.
