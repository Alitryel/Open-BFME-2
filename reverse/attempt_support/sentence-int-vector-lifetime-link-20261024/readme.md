# Native integer-vector destructor emission

The existing native deleting destructor at `156860` calls `23E3`. That is
the 11-byte base-vector destructor: store the base table `BBB5AC`, then
tail-call Clear at `F0CD4`. The default deferred DynamicVectorClass<int>
destructor in the sentence allocation unit instead emitted a 45-byte copy
that inlined Clear. Its parent Allocate_New_Surface was already an exact
551-byte match, including the inlined cleanup. Replacing that cleanup with
an external Clear declaration changes the parent to 531 bytes, so that is
not a valid source repair.

The source now defines the ordinary base destructor (`Clear()`) and empty
derived destructor under one scoped size-optimization block. The base body
remains available for forced inlining. At the restored parent compiler
settings, its inline cleanup remains the original native 551-byte body;
the two out-of-line destructors each emit the full native 11-byte body.
This is a measured compiler emission blocker. No assembly, synthetic anchor
or shared tool changes. The existing scoped allowance tool registers only
the two source pragmas; no byte, identity or EH debt allowance is added.
No fields or class relationships change.
The scalar representative does not establish the original renderer element
type, which remains donor provenance.

The derived destructor is recorded as a complete `gen-alias` twin of the
existing base owner. Both relocations have the same offsets, types and
referents: the base vtable and Clear. Its former callee pin is removed. The
alias adds no unique recovered bytes.

## Verification

`body-proof.json` clears alias notes and strictly compares the entire parent
and both destructors. All bytes and relocations match; the parent's complete
EH graph is EXACT. The normal build verifies all four source rows, including
the renumbered cleanup funclet and handler.

`link-proof.json` compares the saved original current object with the repaired
normal object against the same follower index at `2fbdec0868`. The baseline
uses its original pin and omits the newly added alias row; the repaired side
uses the real row and no pin. All three destructor-emitting units and the
base owner are read on both sides. The allocation unit goes from zero to
**561 existing matched nonpadding bytes**. Glyph and twiddler retain their
independent blockers; the base owner remains linked. No census or link runner
is started and no closed-strict result is claimed.

## Related glyph consumer: preserved prerequisite

Resolved by the follow-up in
`reverse/attempt_support/sentence-native-vector-table-link-20261024/`:
the three missing table operations now have real whole-body template twins,
all six native slots are proven, and the constructor/EH rows move to the glyph
provider. The paragraphs below preserve the original diagnosis and trial bank.

The same destructor block preserves the glyph parent's full 515 bytes and
emits both exact 11-byte destructors. It still does not link: its separately
emitted PendingSurfaceStruct constructor is not proven against the selected
provider's data graph. A 73-byte candidate and its EH graph compare EXACT,
but the native tables contain six slots whose complete bindings have not
been reconciled. Strict constructor bytes alone do not establish those tables.
Do not rehome its constructor or suppress the competing view on that basis.
`glyph-best.patch` preserves the useful source trial; production glyph source
is unchanged and no linking gain is credited there.

Other trials, all isolated and reverted:

| Trial | Allocation parent | Glyph parent | Destructor result |
| --- | ---: | ---: | --- |
| Clear declaration, early or late | 531/551 | shorter than 515 | native 11B |
| imported forced-inline derived destructor, with/without throw() | 523/551 | 479/515 | suppressed but parents differ |
| extern template class / destructor | 551/551 | class form 496/515; destructor form 515/515 | losing 45B retained |
| imported template class | 525/551 | 470/515 | parents differ |
| size state at EOF only | 551/551 | 515/515 | losing 45B retained |
| explicit sized derived destructor alone | 551/551 | 515/515 | 5B jump, not native 11B |
| forced-inline base at speed plus sized derived | 551/551 | 515/515 | derived 11B but base 45B |
| sized forced-inline base plus sized derived | 551/551 | 515/515 | both native 11B |
| plain base storage plus counters | 548/551 | 512/515 | loses the native derived construction phase |

The native constructor stores derived table `BD3C00`; destruction stores base
table `BBB5AC`. The plain base storage trial cannot replace this lifetime.
A declaration-only glyph record constructor makes the parent 482 bytes;
imported ordinary inline construction introduces an `__imp_` call and a
483-byte parent; forced inline construction changes register allocation even
at 515 bytes. A plain inline definition preserves 515 bytes and emits 73 bytes,
but does not resolve the data proof prerequisite. Constructor EH was tested
independently and is EXACT. Current BFME1 reference is `32774ab0`; compiler
flags and headers are the unchanged source-declared settings. Scratch trials
are under `build/link-sentence-owner-20261024/`.
