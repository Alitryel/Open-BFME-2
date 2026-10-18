# Fixed-storage vector assignment link repairs

Paired current-object legacy link preview at unchanged BFME 2 HEAD 8c9e451583 and census c2c5ac8c27 (2026-10-18 11:36): **+531 existing C++ bytes linked**, 1,208 -> 1,739 across the two changed consumers and four unchanged providers. The census-relative total also includes 417 bytes of pre-existing improvement in StlportObject872Vector.cpp; those bytes are present before and after and are explicitly excluded from this repair's gain.

| Changed unit | Before | After |
|---|---:|---:|
| StlportObject260Assign.cpp | 0 | 260 |
| StlportObject872Assign.cpp | 0 | 271 |

The same four providers are included in both runs: StlportObject260Vector.cpp (418), StlportObject872Vector.cpp (417), Object260Copy.cpp (93), and Object872Copy.cpp (280). To establish the baseline, both consumer files were temporarily restored from HEAD, checked synchronously, and then restored to the edited contents. The before run exits 1 for the two expected blocked consumers; after exits 0 with all six units linking. These are legacy predictions, not closed-strict or full-link results.

## Evidence and repairs

These are already-established neutral target views; their original application names remain unknown. The existing copy chains independently establish the layouts: 260-byte object copy at 0x2CF495 calls the fixed-storage copies at +4/+0x84; 872-byte object copy at 0x2CF380 calls the header and fixed-storage 28/76-byte member copies and copies its tail fields. No new identity, pin, alias or header is introduced.

Both assignment units used exception-enabled STLport helpers while their rowed vector providers use _STLP_NO_EXCEPTIONS. Matching that setting makes their referenced _M_allocate_and_copy and __uninitialized_copy bodies agree with the kept retail copies without changing the native assignment rows. The 260-byte unit also declares its existing rowed _Construct specialization (0x2CF8E8), as its vector provider already does. Attempting declarations of the member-template allocate/copy helpers instead triggered an MSVC 7.1 internal error and was discarded.

The 872-byte unit's broad class instantiation additionally emitted unrelated default-construction users and a competing push_back. It now instantiates its rowed assignment and clear operations explicitly. The rowed __copy_ptrs helper remains emitted. The active non-retail malloc allocator deallocate copy is replaced by the same inline free specialization pattern already used in the 260-byte sibling: retail's assignment contains the inline null test and free call. A declaration-only deallocate trial outlined _M_clear and changed the assignment bytes, so was rejected. The final inline wrapper preserves the complete 232-byte assignment and both other rows. Unreferenced diagnostic copies are not counted as blockers under retail-truth-2.

## Acceptance and limits

Normal byte/reference gates pass all five rows. Strict reusable receipts are prepared for both edited consumers; that checks their own bodies, not provider closure. No literals, imports or EH frames require additional rows; eh_verify reports no non-exact rows. Frozen-source checks pass. No verifier/baseline/reference/shared-header changes are made. Provider bytes and relationship claims are inherited from the existing matched rows, with no new target type name asserted.

The BFME 1 reference stays at its last verified 64d369b90170b7e9ec917d646f020b11f13eb0d5 pointer; another live seat holds its update claim. No maintainer-only verification runner was invoked.
