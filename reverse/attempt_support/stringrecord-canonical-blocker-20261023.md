# String-record canonical-header blocker

Reviewed `stlport_vector_stringrecord_b9534_allocate_copy.cpp` at local
`4d5f3bd46023f540703780c6bdc1e0a9fd8e284b` and unchanged upstream
`7dd59793af`; BFME1 stays pinned at
`138757e9b74645fbcbb7724a7af2764e34931e11`.

Normal baseline build passes six rows / 260 bytes. No candidate source edit,
new compiler-shape trial, shared-header edit, or coverage gain is made.

The existing `reverse/header_queue.tsv` AsciiString entry already reports a
fill failure for this TU. Independent target inspection explains a semantic
obstacle, not just an inlining problem:

- Retail fill 0x0052506F is the complete 35-byte loop, copying six dwords per
  element with `rep movsd`. It makes no string assignment or ownership call.
- Its indexed direct caller is 0x00527378. The existing matched source
  `InGameHeroSelectInterfaceCtor.cpp` constructs sixteen 24-byte hero slots
  and casts their range and slot initializer result to the string-record
  spelling to reach this fill provider. Its local `Rva00524F35` slot view is
  five integers plus three bytes, not an identified string-owning record.
- Retail copy helper 0x000B448F likewise copies six raw dwords per element
  (50-byte complete body). Its wrapper 0x000B6782 is called by erase
  0x0008B4D2 and six-word vector assignment 0x000BC20D. The ledger also has
  an address-derived element instantiation at the same 0x000B448F address.
- In contrast, the actual record copy 0x000B9534 calls the established string
  copy at 0x000365F0, then copies the flag at +4 and words at +8/+C/+10/+14.
  The canonical-header Common record-copy TU already represents this path.
  The allocation helper 0x000BBCEF reaches uninitialized copy 0x000BBC3E,
  whose per-element construction calls 0x000BBA74, so that path retains
  independent evidence for this record family.

The current private AsciiString view has no user-defined copy assignment.
Consequently it emits raw pointer assignment in synthesized record assignment;
the canonical header's assignment instead invokes StringBase::set. Adding a
custom raw-memory assignment to a canonical string-owning record merely to
retain the generic fill/copy bytes would conceal this unresolved distinction.
The target proves raw-copy behavior, not that these helpers all operate on the
same ownership-bearing application type. A byte match is not type identity.

Next prerequisite: reconcile the generic 24-byte assignment/fill owners and
their consumers separately from the string-construction helpers, applying the
naming/fold rules with independently supported caller types. That may require
coordinated changes outside this WWLib TU (including the hero-slot consumer),
so no such change is made under the present disjoint scope. Prior destructor
provider findings in `stringrecord-destructor-link-20261014/readme.md` remain
valid and untouched. No new declaration/import suppression trial repeats the
already-refused destructor shapes.
