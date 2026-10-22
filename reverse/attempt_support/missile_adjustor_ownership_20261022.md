# MissileUpdate callback adjustor: resolved ownership and vtables

The new body at `0x004A7691..0x004A7699` is the compiler-generated
this-minus-four adjustor for MissileUpdate's two projectile interfaces.
The native 200-byte constructor at `0x004A75B9` and 84-byte destructor at
`0x004A76DE` establish five vptrs. The two relevant interfaces are at +0x20
and +0x24. Neither begins with a destructor; the old private views did.

The repaired flat interface declarations retain the existing five vtable
symbols and root object layout. Their complete six-entry prefixes resolve
to these native RVAs, in order:

| Interface | Native table VA | Resolved RVAs |
|---|---|---|
| +0x20 | 0x00C53548 | 4A7551, 4A768A, 49CB8A, 4A78B8, 5CB9FF, 47A69C |
| +0x24 | 0x00C53530 | 45B4C0, 4A7691, 47A699, 47A699, 47A699, 47A699 |

MSVC uses the +0x20 introducing interface for the implementation. Native
root fields +0x94/+0xCD/+0x90 therefore appear at receiver+0x74/+0xAD/+0x70;
the owner at root+8 appears at receiver-0x18. Both interfaces declare the
shared one-word callback; the MissileUpdate false override naturally emits
SUB ECX,4 then JMP 0x005CB9FF for the +0x24 entry. No assembly is used.

Ten exact same-range companion rows bind the actual populated methods.
They preserve the original matched providers and add no unique bytes or pins.
Every companion passed strict byte and relocation resolution; gen-alias
fallback masking was not needed. The four ordinal zero-argument callbacks
remain address-derived; their original names and semantic roles are unknown.

Independent COFF audits compared all code, both complete 24-byte table
prefixes and every relocation against native. The other three pre-existing
table objects are byte-and-relocation unchanged. No exports, global anchors,
extra constructors or unresolved gap methods were introduced. Those three
unchanged tables remain partial baseline views; this is not a complete
reconstruction of all MissileUpdate virtual methods.

Production verification: 16/16 matched rows; EH EXACT 1; no undeclared
definitions; placement sweep found no other bodies or pins. Link preview is
clean and grows from 174 to 182 unique bytes in this file. Compiler settings
are the existing path-specific /O1 /arch:SSE /G7 with /MD /EHsc.

The earlier attempt log's constructor citation 0x004A764E was a recording
error; the verified constructor is 0x004A75B9. All final ledger notes use
the corrected address. This supersedes the earlier diagnostic-only compound
view in `missile_adjacent_layout_20261022.patch` and the section-6 blocker in
`parallel_recovery_20261022.md`.
