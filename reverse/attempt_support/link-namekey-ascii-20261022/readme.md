NameKeyGenerator::nameToLowercaseKey (0x00620500+187) used the BFME1
namekeygenerator private AsciiString header. Its default constructor emitted a
non-retail COMDAT, the only current link blocker. The canonical BFME2 string
header supplies the retail six-byte constructor and preserves the established
one-pointer ABI. Suppress the legacy header via its own include guard after
including the canonical one.

A local derived string supplies the legacy length-taking assignment, keeping
the original nullable strlen wrapper and call to StringBase<char>::set(text,len).
Using that operation directly changed register lifetimes and failed the main
body; preserving the inline wrapper restores all 187 bytes. No additional data
members or runtime operations are introduced. The stale LegacyBucket layout
remains unchanged. Target bytes and existing StringBase/AsciiString owners
establish storage and call relationships; the source's BFME1 provenance and
uncertain stale-header/original-identity explanation remain as previously recorded.
BFME1 linking repair history reviewed: 37c3022de1ab944c7ffe536440d637dc8199091c.

The same published e20daa4e78 index with the original and final objects gives
0 -> 187 nonpadding bytes in paired legacy previews. Both the default constructor
and original AsciiString assignment no longer lose. The published index has no
other unit blocked by this AsciiString constructor; only this TU uses the donor
namekeygenerator include path, so this cause has no additional sweep members.

Acceptance: ordinary byte gate 1/1; string and import verification pass;
find_declared_unmatched passes; new-COMDAT-variant admission passes. Strict
receipt preparation refuses both original and final dependency closures because
a macro or parent-traversing donor include has unknown search roots (the original
also reports an included header outside inventoried roots). This is a measured
legacy preview gain only: no self-strict or closed-strict gain is claimed.
No verifier changes, full census, link cycle or runtime checks were run.
proof.json records paired findings, object/source hashes and the index hash.
