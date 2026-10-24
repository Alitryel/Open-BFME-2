# Complete the native sentence vector table

The native PendingSurfaceStruct constructor `156A10` installs `BD3C00`.
Its complete six-slot table supplies independent relationships between the
existing deleting destructor, equality, resize, clear and two ID operations:

| Slot | Native RVA | Existing owner |
| --- | --- | --- |
| 0 | 156860 | DynamicVectorClass<int> deleting destructor |
| 1 | 22B3 | VectorClass<int> equality |
| 2 | 155460 | DynamicVectorClass<int> Resize |
| 3 | 16FED0 | DynamicVectorClass<float> Clear, 42 bytes |
| 4 | 1969C0 | DynamicVectorClass<FontCharsBuffer*> value ID, 40 bytes |
| 5 | 154BE0 | VectorClass<float> pointer ID, 24 bytes |

The last three operations are complete four-byte template twins. The native
table, 28-byte record constructor and its callers support their relationship;
the whole bodies and every relocation prove the particular instantiations.
The original renderer element type remains unknown. `int` is the existing
four-byte scalar view, not a newly established original application type.

The donor vector.h implements derived Clear by clearing the active count and
calling the qualified base Clear. Its pointer ID calls the qualified base ID.
Existing per-TU declarations hid those base bodies, emitting a short call
instead of native's expanded operation. The new shared header expands those
same EA operations, preserving their exact tests, deletion, field updates and
unsigned pointer-index calculation. It uses the existing class declaration;
no private class or layout is introduced. Native-size base/derived destructor
definitions from the preceding repair also move into this header.

All three census definers of these operations adopt the same implementation:
the allocation consumer, glyph consumer and twiddler. Each emits the native
42/24/40-byte bodies. The normal source flags remain unchanged. No pin or
verifier code is added. Three whole-body `gen-alias` rows bind the real emitted
operations; they add no unique recovered bytes.

## Constructor ownership and debt repair

The previously blocked glyph constructor now has a complete data proof.
`body-table-proof.json` resolves all 24 table bytes to the six native pointers
and verifies the entire body at every slot. Its vector-deleting weak name
resolves to the compiler's actual scalar deleting destructor. The constructor's
full 73-byte body and EH graph are exact, and the independent RetailTruth
recursive constructor verdict is `retail`, rather than `unknown`.

The constructor and its existing eight-byte cleanup and ten-byte handler move
to the glyph unit through the normal add_match gates. No name or RVA changes.
The cleanup's new compiler label is taken from the exact parent EH placement,
not inferred from adjacency. The old PendingSurfaceStructCtor.cpp is removed:
it carried private VectorClassDummy/DynamicVectorDummy views, six unresolved
virtuals and a synthetic constructor anchor. Its three present-unmatched
markers disappear. The same two already-admitted destructor pragmas move from
the allocation source to one shared header; there is no further pragma growth.

## Verification and net gain

The normal gate and `body-table-proof.json` verify all **19 existing/alias
cohort rows**, including compiler cleanups and handlers. Ordinary bodies are
compared with alias notes cleared. The three slot methods in each provider
also underwent isolated whole-body comparisons before admission. Constructor
and parent EH data are exact.

`link-proof.json` recompiles the four original source snapshots freshly into
isolated outputs, with the same original compiler commands and source include
search directories. It compares those with the normal repaired objects under
the same follower index at `2fbdec0868`. The baseline ledger omits the three
new aliases and retains the old constructor ownership. On the repaired side,
the existing `forget` operation removes the obsolete unit that the ledger no
longer compiles, preserving every other measured object position.

| Source | Before | After |
| --- | ---: | ---: |
| Allocation | 561 | 561 |
| Glyph, including rehomed constructor | 0 | 608 |
| Twiddler | 0 | 0 |
| Obsolete constructor unit | 0 | retired |
| Total | 561 | 1169 |

This follow-up adds **608 existing matched nonpadding bytes**. Together with
the preceding allocation destructor repair's 561 bytes, the unpublished batch
adds **1169**. The 83 constructor/handler bytes were previously unlinked, so
their transfer is included once. Cleanup funclets, alias bytes and pre-existing
linked bytes are excluded by the normal progress calculation. Twiddler's
independent factory/save-load dependencies remain; no gain is claimed there.
This is paired scoped linking evidence, not a new census or closed-strict claim.

The broader `--refresh --current-ledger` preflight refused a whole-program
result because 7079 other objects lack current compiler evidence. The three
owned providers were prepared through the existing strict-receipt tool;
`current-receipts.json` independently confirms each is current. No global
link result is inferred from the focused result.
