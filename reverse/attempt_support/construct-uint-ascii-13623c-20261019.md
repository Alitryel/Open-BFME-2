# Unsigned/string map construction at 0x0013623C

The old `dup_0013623C` row borrowed `_Construct<TreeKey00242F5E>` from
0x000A7876. Identical copy bytes were insufficient to identify its application
type or admit its unclaimed EH handler. The native caller chain establishes a
genuine STLport value type without creating a replacement application class:

`136A21 -> 136777 -> 136642 -> 1364F7 -> 1364AC -> 13623C -> CF475`.

Target facts: the 132-byte subscript at 0x00136A21 compares unsigned keys
(`JAE`). On a miss it creates an empty narrow string, constructs the two-field
value through 0x00523DB7, inserts it with a hint, destroys the temporaries, and
returns the mapped string at node+0x14. Its 34-byte node creator at 0x001364AC
allocates 24 bytes and constructs the eight-byte value at node+0x10. The
29-byte copy at 0x000CF475 copies the first dword and calls the already verified
StringBase<char> copy at 0x000365F0 for the string at value+4. The same tree's
hint/duplicate workers compare only the unsigned first dword. Existing sources
`Rva00136A21MapSubscript.cpp` and `Rva00136642HintInsert.cpp` independently
preserve those signedness and mapped-string facts.

Reference contract: local STLport `_map.h:158` defines precisely this
lower_bound/default-value/hinted-insert/return-second algorithm. Its line 52
defines `value_type` as `pair<const key_type, mapped_type>`. The genuine
instantiation is therefore `pair<const unsigned int, AsciiString>`, using the
project's canonical narrow-string header. The original application map/global
name is still unknown. Cached WorldBuilder bodies at 0x009B4B30 (subscript)
and 0x009B4A30 (lookup) corroborate value+4 and string access, without naming
the original map. This is a container/type inference from complete native
behavior plus the established STLport contract, not a name inferred from a
matching folded copy alone.

Whole-source trial: the existing `stlport_construct_game_structs.cpp` gained
the canonical ASCII include and a genuine pair `_Construct` instantiation.
Only the obsolete `dup_0013623C` alternatename was removed. All 36 existing
rows remain exact, with identical resolved byte hashes and unchanged EH
verdicts. Effective flags remain `/O1 /arch:SSE /G7 /Ob2 /EHsc /MD
/D_CRTIMP= /D_STLP_USE_STATIC_LIB`, with the canonical ASCII include directory
added. No naked body, inline assembly, synthetic caller, invented record,
compiler-label perturbation, or optimization pragma was introduced.

The whole object emits the real pair copy (29 bytes), `_Construct` (45 bytes),
cleanup (14 bytes), and handler (10 bytes). Complete strict relocation proofs
give: pair-copy -> 0x000CF475, parent -> 0x0013623C, cleanup -> 0x00765A4A,
handler -> 0x00765A58. The native EH graph is EXACT with no placement conflicts:
FuncInfo 0x00909F18 binds the cleanup and handler independently of their byte
patterns. Compiler-local cleanup ordinals are read from the current object.
The real pair-copy name has no other ledger or pin address; its full 29-byte
body has the same relocation at +19 to StringBase copy 0x000365F0 as the
existing CF475 owner. Its binding is admitted through the normal fold-proof
pin mechanism; there is no second ledger row at CF475. The original TreeKey
parent at 0x000A7876 and handler at 0x00760AB8 retain their source and ownership.

The sole direct construction caller, `Rva001364ACCreateNode.cpp`, now calls
the genuine external template declaration instead of the old void placeholder
through a function-pointer cast. Its opaque existing parameter spelling and
allocator provider remain; its complete 34-byte body, both calls and lack of EH
data are unchanged. Unused container headers were replaced by declarations,
keeping the real template definition in its owning constructor source. No
compatibility alias or placeholder pin is introduced.

The ordinary legacy C++ row's owner is corrected using terminator-preserving
`ledger_io.rewrite`, requiring exactly one old name/RVA key and changing only
its name and factual notes. This is an identity correction of the same
45-byte body, followed by normal `add_match --replace-existing` and whole-source
verification. It does not relabel the old row as generated scaffolding or
change the generated-conversion admission policy.

Input provenance: BFME1 remains at verified cf0a80c228583af789772b794ab27abcab2debbf.
The original source SHA256 is
702548d995ae23a5ef88b538b2a59926dbd614f441db6834bf77aaa5fe5541b1.
Detailed ignored caller, compiler-input, whole-row and strict-EH receipts are
under `build/identity-13623c/`, particularly
`construct-whole-tu-existing-rows.json` and `construct-whole-tu-proof.json`.

Production verification: both affected sources pass all 38 rows, the declaration
gate is clean, and all 23 EH graphs are EXACT. Pin consistency is clean. The
required placement rescan reports zero additional bodies or pins. The scoped
link preview links both sources: constructor-source bytes rise from 1,054 to
1,064, while the node creator remains 34 bytes; the new handler adds 10 linked
bytes. No extra current-provider witness or census run was needed.

The hatch-baseline change retains only the official CF475 fold-pin registration
(3 to 4 with its admission hash). Unrelated automatic tightenings were restored.
The obsolete constructor alias is removed from source; its baseline allowance
is left unchanged. The registration requires a Verifier-Change commit trailer.
