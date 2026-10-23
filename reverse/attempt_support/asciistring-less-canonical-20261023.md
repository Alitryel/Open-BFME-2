# Canonical AsciiString comparator provider

Scope: `Code/Libraries/Source/WWVegas/WWLib/AsciiStringLess.cpp`, existing
23-byte row 0x0005598C. Inputs retain BFME1 pin
`138757e9b74645fbcbb7724a7af2764e34931e11`; source flags and shared headers
are unchanged. The upstream file was unchanged when reviewed this session.

The existing header-adoption queue records error C2084: the earlier attempt
included the canonical header while also defining its free operator< locally.
The new hypothesis removes the duplicate operator, private StringBase, and
private inherited AsciiString view together. The existing emission anchor
now emits the canonical header's own free comparison operator. Its source
does not need the old `|| false` expression to reproduce this body under the
header's existing compiler context. No new pragma, alias, marker, pin, or
compiler override is introduced.

The target's complete 23-byte leaf pushes the right-hand string, loads the
left-hand string into ECX, calls the established StringBase<char>::compare
at 0x000069D6, then uses xor/test/setl/mov to return the less-than Boolean.
This establishes the comparison behavior and one-pointer thiscall ABI; the
existing ledger and canonical class already carry the AsciiString identity.
No new application type identity or donor layout is inferred from placement.

Verification:

- Normal `./build.sh` passes 1/1 before and after the edit, with all 23 bytes
  and the compare relocation verified against retail. Literal/import checks
  pass; there are no referenced literals/imports in this leaf.
- Independent read-only COFF comparison finds the same code-definition set,
  identical full 23-byte operator bytes, and the unchanged five-byte emission
  anchor. The only changed code relocation is the comparison spelling:
  StringBase<char>::compare becomes AsciiString::compare. The unchanged
  canonical header's existing alternatename binds it back to the same worker;
  the normal byte gate verifies the target 0x000069D6.
- Frozen-source checking reports all definitions already matched or carrying
  the existing emission-anchor annotation. `git diff --check` passes.
- No link gain is claimed: this worktree has no current census index. There
  are no new code providers, but that is not a measured scoped link result.

This reconciles two private class views and removes one duplicate operator
definition. It preserves 23 existing bytes: zero newly recovered bytes,
zero direct source-hatch-count reduction, and zero measured link gain.
The old queue diagnostic is superseded by this successful narrow adoption;
the shared queue itself is not edited in this source-only repair.
