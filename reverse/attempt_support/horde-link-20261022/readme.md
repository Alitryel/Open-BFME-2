# Horde model link repair, 2026-10-22

Inputs: BFME2 b68575f39f, BFME1 37c3022de1ab944c7ffe536440d637dc8199091c; original TU flags unchanged. Native parent 0x0007A847, 2586 B. Published census 08160bc2c9: own 2579 unique B, legacy 0 -> 0, sole blocker narrow basic_string<char>(const char*,allocator) nonretail COMDAT.

Two trials: declaration-only constructor; imported forceinline vendor constructor body (_String_base allocator initializer, _M_range_initialize through traits_type::length). Both change parent stack slots (e.g. retail saved module data ebp-10 becomes ebp-14), and renumber cleanup labels. $L11452 disappears; $L11453 has four indistinguishable group matches. Visible constructor does not restore original codegen. Both byte gates failed; no link gain claimed.

Restored original source and released claims. Attached last trial is diagnostic only. A future repair needs to preserve original optimizer decisions or repair the selected constructor provider, rather than repeat either suppression. No shared-header changes tested.
