Current paired-provider legacy link_check: MeshClassRender.cpp 0 -> 1,427
matched bytes; MeshModelClassGetSortFlagsPass.cpp remains independently blocked.
The pair increases from 0 to 1,427 B. Census c2c5ac8c27. Self-strict reusable
receipt only; no closed-strict or authored C++ coverage gain claimed.

Native Render 14BB90..14BFF6 inlines both alpha-test shader lookups. There are
no calls to model getter 5434D0 or descriptor getter 543370 in the native body.
The existing model descriptor at +94 and descriptor shader at +98 are retained.
Removing its redundant model forwarding definition and directly querying the
same descriptor preserves all native bytes and removes the dependency on the
conflicting selected model accessor. Descriptor and all layout evidence remain
as documented in the original source and ledger. No shared headers, pins,
aliases or baselines changed.

Acceptance: 10/10 code rows exact, including independently verified renumbered
funclets; strict reusable receipt; 2/2 EH records EXACT; frozen-definition check
passes; data enforcement zero findings; converged data zero second names and
zero unjudged rows. The unreferenced RenderingMethod handle-copy diagnostic
is retained, as retail-truth-2 does not consider it a blocker.
