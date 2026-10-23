# EnableRegion link repair

Input BFME 2 27dd681fd2 plus this seat's deque repair; published census
456ce161c5 (2026-10-23 06:28). BFME 1 input remains the verified committed
96c88c73a5 pointer; its parser supplies the semantic guide only.

Target evidence: native ParseEnableRegion 4E1579 passes table VA C61A50
and calls append thunk 566527. Reading all 32 table bytes gives Region,
parseAsciiString 2F11E, null userData, offset 4, then sixteen zero bytes.
The existing data-ledger spelling owns that address. Define that table
and call the existing rowed Rva00566527::rva00566527 owner with its
reference ABI. FXList is the existing callable view, not a new assertion
that the parser's polymorphic string record has that original identity.

Paired current-object legacy preview with unchanged Rva00566527Thunk.cpp:
parser 0 -> 129 B, provider remains 16 B; total 16 -> 145 B (+129 B).
No new authored function bytes or closed-strict/full executable result is
claimed. Normal build verifies both existing function rows and the full
32-byte data row, including string and code relocations. EH graph is EXACT;
strict reusable receipt preparation, frozen-file check, check_csv, and
enforced data_check pass (zero findings).

The sibling FlashRegionsEvent parser has the same class of missing table
and append spelling, but another worker holds its file claim; it was left
unchanged and this seat released the two temporarily acquired RVA claims.
