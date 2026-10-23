# Deferred vector range ownership, 2026-10-23

Inputs: BFME2 9671102148, published census b711de3634 (retail-truth-4),
verified BFME1 pointer 96c88c73 unchanged. Prior donor linking repairs and
reverse/attempt_support/link-vector-dtor-isolation-20261022.md were reviewed.
This repair follows native call targets rather than asserting donor identities.

The deferred destructor unit initially linked 0/606 nonpadding bytes. Three
undefined range operations now bind to their existing rowed native targets:

- vector<RvaPair00257544> at 257544 calls 32C0CA, the 25B two-argument
  Rva0032C0CADestroyPairs worker (8-byte AsciiString-keyed pairs).
- vector<Rva005F8620Element> at 5F85E1 calls 5F85C8, the 25B two-argument
  Rva005F85C8Destroy worker (8-byte stride, element destructor 5F8447).
- vector<Rva002BBB96Element> at 2BBB18 calls 2BB6A5, the 25B worker rowed as
  __destroy_aux<BfmeAssignRecord52*>. The complete native worker reads first
  and last only, advances by 52, and calls 2B707E. Its native caller pushes
  and pops exactly two arguments. The provider spelling has an unused tag;
  no tag is passed by this native path. This is independent caller and whole
  callee ABI evidence, not an inference from loop-byte similarity alone.

No application class identity is equated by these operation bindings. No pins,
new data, extent changes, or verifier/baseline changes are introduced.

The two remaining destructors (3B904B, 5EB28A, and their EH handlers) move to
StlportVectorDtorDeferredOwners.cpp. Their _Destroy names have existing selected
non-retail definitions, so fallback aliases cannot replace them. An imported
forceinline forwarding specialization changed argument loads from direct
memory pushes to register loads/pushes and failed the byte gate. It was removed.
Geometry's neutral wrapper additionally had no admitted name resolution. Do not
repeat either wrapper trial. Native target 3B8E13 is already rowed; 5EAA83 is
rowed as __destroy_aux<BfmeVectorRecord002AF478*>. Actual provider reconciliation
or another byte-exact call mechanism is required. The preserved original
specializations still byte-match; there is no nonmatching C++ left in Code/.

Acceptance: ordinary byte/ref gates 13/13 across both units; frozen-definition
check passes. Scoped strict reusable receipt preparation covers the two touched
units. Legacy paired current previews give the remaining family 0 -> 461 B;
32C0CA and 5F85C8 provider units stay linked at 25 and 53 B. The 2BB6A5 provider
stlport_asciistring_record_bodies.cpp remains 0/2021 B with unrelated bad copies
and an unresolved construct helper. This is a legacy gain, not closed-strict.
The new isolation unit is outside the published census and its link placement
is unmeasured; no gain is claimed for it. No full census/link cycle was run.

Diagnostic logs (local): build/link-seat-probe12.txt,
link-seat-deferred-direct-gate.txt, link-seat-deferred-split-gate.txt,
link-seat-deferred-split-measure.txt, link-seat-deferred-split-strict.txt.
