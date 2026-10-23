# Video vector destroy ownership repair

Base: BFME2 `7e32ef28cefb71e864fe9b1cf2ee5b89b280d271`, BFME1
`4483e88da1c2f3b9a273f779baac7458bd8bb891`. Frozen published legacy census:
`3f413ed3ff`, 2026-10-20 18:52. No census or status files rewritten.

The nine-byte `_Destroy<Rva001D28F0Element>` at 0x689740 was emitted by
DestroyInstances.cpp using an empty, declaration-only class view. It also
emitted a 28-byte scalar deleting destructor: its operator-delete cleanup was
`pop ecx`, whereas the retail 30-byte body at 0x6896D0 uses `add esp,4`.
Although both vector units emitted the retail copy, the earlier destroy unit's
copy won selection. Changing its /O1 /G7 to /O2 /G7 or /O2 /G6 preserved all
59 rowed wrappers but did not repair selection; those flag changes were reverted.

Rehome the existing wrapper beside the real 119-byte element destructor, keeping
that destructor out of line so the wrapper stays the native nine-byte tail jump.
This removes the competing empty view and retains the existing target identity,
layout, and destructor semantics. No new body, pin, alias, or class identity is
claimed. The wrapper and full destructor/EH bodies verify under the local STLport
allocator profile. The remaining vector view and helper-type reconciliation is
separate work.

Same-index, explicitly paired before/after predictions (nonpadding bytes):

| Unit | Before | After |
| --- | ---: | ---: |
| DestroyInstances.cpp | 0 | 0 |
| Rva00689DB0Finish.cpp | 0 | 113 |
| Rva001D25F0VectorInsertOverflow.cpp | 0 | 0 |
| Rva001D28F0ElementDtor.cpp | 129 | 138 |
| Total | 129 | 251 |

Gain: **122 bytes**, comprising the 113-byte vector-destructor unit and the
existing nine-byte wrapper moved into a linking unit. Authored C++ coverage is
unchanged. These are legacy-index predictions with self-strict compiled changed
providers, not a measured closed-strict closure or a full link result.

Acceptance: 64/64 rows across the two changed units, including three existing
unwind mappings and the destructor EH handler, pass the normal byte gate and
string/float/import checks. `link_check --prepare-current` verifies both changed
providers with strict reusable receipts. Saved before/after, byte and strict
logs accompany this note. New-variant and declared-unmatched checks pass.

Remaining: DestroyInstances still needs AudioEventRTS destruction and its
RvaSmartPtr12 helper reconciliation. The overflow unit retains unresolved
element constructors/assignment and non-retail copy/copy-backward helpers.
Neither is claimed to link. Read-only provider inspection found the same scalar
deleting name only in these three original units, so this cause is exhausted.
