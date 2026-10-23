# String-record fill-insert provider binding

Inputs: BFME2 parent 70a2bd89d5; census 456ce161c5 (2026-10-23 06:28);
BFME1 reference 96c88c73a5cd1a58fc2f8db691beea50acd996db.

The 260-byte fill-insert row at 0x005DE651 calls overflow 0x005DE4BA at
REL32 +0xF0. Its old BfmeStringRecord overflow name belongs to the separate
0x00381B7B row. An additive historical pin lets the byte gate select either
address, but the link census correctly binds the name to its ledger owner.
Call the existing 0x005DE4BA provider by its actual address-derived name.
The allocate/copy unit must also stop emitting its non-retail 266-byte
fill-insert copy; its declaration now consumes the dedicated 260-byte owner.

The existing provider uses Rva005DE4BAElement, a structural eight-byte view
containing two list handles. Reproduce that declaration exactly so the compiler
can retain the generic overflow body and its unused tag-argument summary.
This does not establish lists as the target application's record identity.
The cast preserves the three-pointer vector ABI and eight-byte record ABI;
native calls and complete bytes establish the relationship, not type spelling.
The exposing derived view adds no members or virtual methods. No pin, alias,
ledger row, baseline or compiler setting is added or changed.

The reference STLport algorithm remains the guide. BFME1's current vendored
_vector.h has the same overflow algorithm; these BFME2 structural owner names
are not a donor naming claim or an inherited donor linking repair.

## Acceptance

- Before: allocate/copy 0/660 B; fill-insert 0/270 B. Independently checked
  existing overflow provider already links 178/178 B with these same inputs.
- After: paired current preview of all three units is 178 -> 448 B, +270 B.
  Fill-insert links; the existing overflow provider still links. Allocate/copy
  retains its independent chat-history overflow conflict.
- This is legacy scoped preview evidence, not closed-strict LINK closure.
- build.sh: 17/17 rows exact across both changed units; the funclet's changed
  compiler label is independently resolved by the unchanged native EH graph.
- link_check --prepare-current: 17/17 exact, two strict reusable receipts;
  this establishes self-strict preparation, not closed-strict link evidence.
- eh_verify: three EXACT graphs, no debt. check_csv passes; both sources pass
  find_declared_unmatched.

## Trials and remaining prerequisite

A declaration-only 0x005DE4BA specialization changes the caller's stack and
register allocation and initializes an empty tag temporary. It fails the byte
gate. Keeping the existing provider's full generic definition visible restores
the native 260-byte caller and passes all rows. Only these two trials were run.

The separate 0x00381B7B growth repair was not repeated: prior evidence in
reverse/attempt_support/20261021-chat-history-link/readme.md already banks two
failed explicit-helper spellings. It still needs a different, evidence-backed
callee-visibility/register-allocation repair. Its native helper addresses remain
0x3814D3/0x3814A6/0x3814F9, unlike the generic record helpers.
