# Wide istream locale-copy alignment (2026-10-18)

The sole current blocker of stlport_wide_istream.cpp was ios_base::getloc: its 32-byte copy called locale's copy constructor, whereas the complete retail 41-byte body inlines the copy and invokes _Locale_impl slot 1. getloc-before.log shows both whole bodies and the exact difference. The existing rowed stlport_locale.cpp and matched narrow num_get<bool> unit already supply this inline copy implementation. The wide-stream TU now sees the same implementation before its ios_base definition. The local implementation view mirrors the locale owner's virtual slots and pointer/count prefix; it allocates no implementation object and makes no new whole-class size claim.

Current paired previews replace wide_istream and locale providers together, before and after: 0 -> 232 linked bytes. The wide unit links; the locale owner still has its unrelated classic-handle global and default-constructor COMDAT blockers. The other index emitters of getloc all retain at least four independent blockers; merely aligning their copy would not make their units link. Their larger string/facet repairs are separate work.

All 7 wide-stream rows retain exact bytes, including the 28-byte unwind funclet (its compiler label was renumbered and is verified from the parent EH graph). prepare.log verifies 15/15 rows across both explicit providers and creates strict reusable receipts. No new markers, aliases, pins, pragma settings or helper anchors were added. No authored C++ coverage grows.

This is a legacy link prediction with self-strict provider evidence, not a closed-strict census or full link result. No census/index/status changes were made.
