# Asset refresh constructor ownership, 2026-10-22

Current paired legacy baseline is 0/3252 linked bytes. Only remaining blockers:
Rb_tree_base<Rva001408C0Target*>::allocator constructor and Rb_tree's comparator+
allocator constructor. Both differ from the kept GameLogicInit copies and have
no proven retail addresses. They are referenced by a kept local constructor.

Trial 1 declares both specialized constructors: parent 6227E0 changes, replacing
inline allocation with a call and perturbing stack temporaries. Trial 2 preserves
stock bodies with dllimport forceinline: C2908 because the new early bodies
instantiate allocation before the existing late allocator specializations.
Trial 3 (attached) declares imported constructors early and defines them after
those allocator specializations: parent frame C4 versus retail BC, plus an
unresolved alloc-proxy constructor. Thus source-order matters; do not repeat
these three exact forms. A future attempt could reorder the allocator and proxy
constructor visibility, but must preserve the parent register/escape summary.

Original source restored. build.sh must pass 2/2 again. No +0 code repair kept,
no verifier changes. MSVC7.1 existing /O2 /G6 /arch:SSE /MD /EHsc flags;
BFME1 verified pointer 37c3022de1ab944c7ffe536440d637dc8199091c.
