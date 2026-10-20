# String/unsigned reference-model copy owner

The native hashtable new-node at `0x0060D089` calls `0x0060CFFF` at
`0x0060D0A0`. Its existing 37-byte allocation, next-pointer initialization,
copy and return sequence independently establishes that edge and the
two-pointer cdecl ABI. The 45-byte destination has its own complete native
EH graph: handler `0x007A6CCE`, FuncInfo `0x009604AC`, and cleanup
`0x007A6CC0` (14 bytes).

The pre-existing owner unit supplies the semantic reference: STLport placement
copy of a const narrow-string key and a trivial dword. It calls the already
rowed copy constructor at `0x00389DD6`. This preserves the reference model;
the original application mapped type and helper spelling are unknown. The
standard template spelling already belongs to the tree copy at `0x0038A5A4`.

Define `StringUnsignedPairCopyAtRva0060CFFF` as real placement-copy C++, remove
the borrowed object-symbol identity and redundant template pin, and specialize
the hashtable new-node with the same reference allocation/store/copy/return
operations, calling the real owner directly. No new pin, alias, private layout,
assembly, compiler barrier or padding is introduced.

Normal isolated compilation reproduces the entire 45-byte owner. `eh_verify`
reports `EXACT` for the complete parent graph and maps its actual compiler
cleanup to the native 14-byte body. The natural compiler frame handler is
the complete 10-byte FuncInfo load and jump to the existing C++ frame handler;
it is new C++ coverage. Existing parent and cleanup bytes are repair only.
The caller trial is exactly the native 37-byte sequence, with only the new
owner relocation unresolved until the ledger acquires its real definition.

Final acceptance uses the normal owner/caller byte and EH gates, strict current
dependency receipts and the normal commit/push hooks. Raw isolated trial logs
and inputs remain under ignored `build/deque-string-copy-owner-oct21/`.
