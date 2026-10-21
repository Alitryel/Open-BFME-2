# Chat-history push helper binding

At HEAD f780aee32f, the 55-byte `vector<BfmeStringRecord005DDD40>::push_back`
row at 0x00381C4B has a REL32 operand at +19 reaching the distinct native
placement-copy entry 0x003814A6. The old generic instantiation instead names
`_Construct<BfmeStringRecord005DDD40>`, whose ledger owner is 0x005DDD78.
The additive legacy pin admits 0x003814A6 to the byte gate but does not establish
that name's link identity. The two native copies have separate EH scope data.

The explicit specialization preserves STLport 4.5.3's push algorithm and calls
the already rowed `Rva003814A6Construct` owner. All 85 external COMDAT sections
are retained; 84 have identical bytes and relocation digests. Push remains
55 bytes, byte-for-byte identical; exactly the REL32 referent at +19 changes.
No new pin, alias, definition identity, layout claim or exception hatch is added.
The address-derived record name and existing application-identity uncertainty
are retained. Donor linking evidence reviewed this session is recorded in
`reverse/attempt_support/20261021-bfme1-freshness-link-review.md` (BFME1 cea1e973).
This repair is driven by BFME2 native calls, not donor address equivalence.

Same frozen index d08db10acb (2026-10-21 18:42): the untouched chat caller
`Rva00381C82AddChatText.cpp` goes from its sole wrong-selected push blocker,
0/107 bytes, to LINKS 107/107. The provider remains 0/660 with independent
insert-overflow/fill-insert conflicts. This is +107 legacy preview bytes;
self-strict/closed-strict link closure is unmeasured. Both baseline and final
provider/caller pass `--prepare-current`, 16/16 byte rows and strict reusable
compile receipts. Native EH verification is EXACT for all three scoped parents; CSV and declared-definition checks pass. No full link cycle or census was run.

## Remaining overflow prerequisite

The row at 0x00381B7B ends at 0x00381C2D (178 bytes). Its native calls are:
allocator 0x523D6C; range-copy 0x3814D3 (+0x3F and +0x8A);
placement-copy 0x3814A6 (+0x54); range-fill 0x3814F9 (+0x6C);
clear 0x381B52 (+0x97). The generic 178-byte body instead names the other
record's range-copy/fill/Construct owners at 0x5DDDCA/0x5DDDA5/0x5DDD78.

`overflow-trial.patch` preserves the two failed diagnostic trials' final source:
STLport algorithm with explicit calls to the existing address-derived range
owners and placement-copy owner. Native bounds were not changed. Both normal
builds reject this larger emitted body: clear's REL32 moved from +0x97 to
+0xAF, past the native row. The second retained generic initialization order
and inline qualification; neither resolved the register allocation change.
The build driver printed the extent diagnostic despite status 0, so neither
trial is counted verified. Callee summaries/visibility remain a prerequisite;
no repetition of these two spellings is warranted. All overflow edits restored.

A separate fill-insert declaration-only trial preserves all 19 scoped rows
but adds zero linked bytes: its existing provider itself retains wrong-selected
and overflow conflicts. That declaration was also restored. No new strict
closure is claimed for either provider.

Raw local checks are under ignored `build/link-seat-20261021e/chat-*`;
this note and patch retain the evidence required to resume. Compilers and flags
are the existing TU profile (/MD, STLport, bfmealloc, no STL exceptions).
