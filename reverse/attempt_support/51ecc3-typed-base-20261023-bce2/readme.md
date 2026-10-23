# Typed vector copy at 0x0051ECC3

Inputs: BFME 2 base 0f2f7c97da7; BFME 1 verified pointer
138757e9b74645fbcbb7724a7af2764e34931e11; published link index
456ce161c5 (2026-10-23 06:28, retail-truth-4). Work by GPT-6.

Target evidence: the 71-byte constructor counts 20-byte elements, obtains an
allocator at 0x21983A, calls a 60-byte count base at 0x4FF36C, and copies through
0x39BA22. That worker constructs each element through 0x39B893. The latter is
the existing address-named Snapshot-derived record, not the unrelated raw
SaveMapPreview view previously used here. The caller at 0x51F87B copies this
12-byte vector member at offset 0x14. These are target layout/call facts; no
application name is inferred from the byte match.

The STLport vector/count-base/allocator relationship supplies the structural
interpretation. Its allocator shim is the established BFME allocator. The
actual typed vector constructor reproduces all 71 bytes and all relocations.
The four typed dependencies independently match their existing complete ICF
owners: allocator 28B at 0x395960, getter 7B at 0x21983A, proxy constructor 11B
at 0x14F3C4, count base 60B at 0x4FF36C. They add no unique covered bytes.

The placeholder parent needs a reviewable retraction before its typed replacement.
The attempted retraction was correctly refused by the normal commit gate: the
paired caller still resolves the old constructor name. That caller and its
default-constructor sibling are claimed by davidrazidlo-claude (checked
2026-10-23 16:34 BST), so neither was edited. The old source and all ledger rows
were restored; no partial retraction or new helper row is committed here.
The typed source is banked as evidence only. The paired caller must use the typed
constructor too. A preliminary placeholder-preserving reconstruction matched
all five rows and linked, but retained a downcast from a vector base to a full
vector. It is not the final implementation. A real vector removes that cast.
An inline wrapper around that vector emitted 18 bytes; forced inlining emitted
72 with an extra local stack slot. Direct explicit instantiation of the typed
vector emits exactly 71. The empty CopyTag adapter is an implementation detail
to preserve default-initialization semantics, not a recovered retail identity.

## Shared-provider experiment, not installed

The original failure was a kept SaveMapPreview count-base body of 61 bytes.
Removing Ob2 alone, adding malloc alone, or combining them retained 61 bytes.
The sibling's O1/SSE/G7/malloc/bfmealloc settings emitted the correct 60 bytes
and preserved all five owned SaveMapPreviewCopy rows. However, normal shared
COMDAT admission caught changed cleanup implementations. Declaring cleanup
providers instead passed that check but removed the allocator deallocate
provider needed by Rva0052CD81Finish. Both source and flag-override changes
were restored. This was a real dependency failure, not a false verifier reject.

The saved provider patch and diagnostic source are evidence only. Do not apply
them without resolving the deallocation provider and checking both affected
consumers. The narrower typed-vector repair avoids that shared-provider change.

Resume with typed-vector.cpp.txt. Its explicit instantiation is exactly 71B;
the helper comparison in helper-results.json precedes ledger admission, so the
count-base result still lists its then-unmapped allocator. All four helpers
subsequently passed add_match's whole-file gate in a temporary source, and the
placeholder-preserving typed parent passed 5/5 rows plus link admission. Those
temporary rows were removed when banking. Claim the caller before editing it.
The field's application identity remains unknown. Do not add an old-name pin to
evade the required consumer correction.
