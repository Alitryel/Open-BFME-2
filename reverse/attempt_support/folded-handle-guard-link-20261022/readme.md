The existing folded handle and allocator guard pins now have retail COMDAT
providers in their existing home units. Paired legacy link previews with the
same published census index measure +2,995 nonpadding matched bytes:

- Rva008A2C80Constructor: +186 B; the counted-handle destructor is a 5 B jump
  at 0x000A9DF3 to the 30 B BfmeRefVGO destructor at 0x000A9822.
- Five GeneralAllocatorDebug units: +2,809 B (594 + 644 + 380 + 138 + 1,053);
  the guard destructor is the 21 B release at 0x000317C0.

Target identity evidence is the native cleanup destinations: 0x007A91A0 and
0x007A91B0 of the rowed constructor 0x006E5F10 reach the counted-handle thunk;
0x007A7D50 of Rva006C3840Cluster reaches the guard release. The guard's +0 held
pointer and volatile count at lock +0x18 are independently established by the
rowed Rva000317C0 method and memory_pool.cpp's release. The single-member
provider views are structural inferences, not recovered original class names.
No donor source was imported. BFME1 linking repairs were reviewed at
37c3022de1ab944c7ffe536440d637dc8199091c; its Rva008A2C80 donor supports the
handle relationship but retains BFME1's different payload offset.

Earlier allocator attempts ended in keep-rule false rejects: main paths need
the out-of-line Release call, while retail's kept cleanup copy inlines it.
Retail-truth-3 changes that prerequisite: wrong discarded copies are admitted
when the kept provider is retail. Consumer objects remain byte-identical. The
providers retain every prior COMDAT digest and size. Existing pin notes gain
whole-body fold proofs; no new name or address is added. pin_admission verifies
both providers against all owner rows and relocations, including the handle's
same-object callee. No selection exception or baseline was added.

The two proof reports include paired findings, index/input hashes and object
hashes. Strict reusable receipts and normal byte gates pass 7/7 handle rows
and 19/19 guard rows, covering eight units. The providers' original rows remain
exact. Pin consistency, pin admission, frozen-definition and CSV checks pass.
This is self-strict preparation plus a legacy preview gain. Closed-strict
closure and a full link cycle were not run. Bfme5ThirtyFour still needs its
Rva004A9DF3Element constructor provider, so none of its bytes are counted.
