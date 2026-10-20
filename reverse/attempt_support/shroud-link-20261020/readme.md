Shroud search link handoff,2026-10-20

Original strict2/2,1181B parent plus10B handler. Frozen e7a7769fe5
legacy0/1191B: const vector<bool> operator[], const bititerator */+,
and allocator<unsigned>/allocator<BfmeE8> deallocate. Unreferenced
const-iterator += and allocator proxy diagnostics are not blockers.

Declaration-only const probes plus visible import-forceinline allocators
change parent frame8C->80 and replace inline probes with accessor calls.
Visible import-forceinline native probe bodies (leaf definitions must precede
vector accessor to avoid C2908) keep portions of inline probes but frame
8C->9C and introduce out-of-line const iterator += calls. Both parent byte
gates fail; handler stays exact. First allocator patch mistakenly uses
unqualified free, corrected to header's ::free in second patch. No gain.

Possible remaining explanation: original vector definitions are inside the
existing pragma optimize(s,on) window, while added definitions outside it
inherit O2. New specializations may require the original O1 definition
context, including iterator advance. Not tested after two byte failures;
no new pragma/escape hatch introduced. Original restored, claim released.
Vendor _bvector.h155..190,443..446 and bfmealloc/stl/_alloc.h374..377
provide native helper semantics, target1181B provides code shape. Donor
review4483e88da1c2; no identity/pin/verifier changes. t=7min gpt-6.1-sol.
