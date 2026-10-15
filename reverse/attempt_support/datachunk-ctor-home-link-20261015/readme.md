# DataChunk mapping-constructor ownership repair

Source base: 4b7e7091c4dd659f6f123ec7f25cb75a1a178344. Local index:
19a2565407, 2026-10-15 09:33, census 5986a99448, 2026-10-15 04:52.
SHA256 a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3.
Committed link status is discovery evidence; the paired previews use this
actual index. No index, census status/history, pin, baseline, shared header
or compiler setting is changed.

DataChunk.cpp already defines the native 13-byte Rva0030714F mapping
constructor at 0x00307126. AsciiStringFoldDeleters.cpp separately defines
the same constructor as a strong symbol and owns its row. Their competing
definitions are DataChunk's sole local link blocker. Move that existing row
to DataChunk with add_match --replace-existing, which independently verifies
the constructor there, and remove only the redundant out-of-line definition.
The split unit retains the class declaration and destructor.

Identity and layout evidence are unchanged: the native constructor stores
vtable 0x00C07EAC, whose deleting destructor is already rowed at 0x00307133,
and clears the AsciiString at +8 while leaving +4 untouched. DataChunk's
existing mapping view and read path provide the home. The original semantic
class name and full layout remain unresolved; neither byte equivalence nor
this ownership repair adds a new identity claim. The BFME 1 default-constructor
pattern in the original evidence remains donor evidence only.

Acceptance:

- Strict bounded preparation before and after verifies all 30 rows across
  the two explicitly claimed units, two literals, one empty-string reference
  and zero baselined/skipped strings. Both after objects have strict reusable
  dependency receipts. add_match also verifies DataChunk's nine rows.
- DataChunk's complete object is byte-identical. Normalizing COFF section
  references and excluding debug sections, the other object loses exactly
  the 13-byte constructor section. Its remaining 40 sections, extents, bytes,
  relocations, bindings and directives are unchanged. object-proof.json
  records hashes and assertions from the scratch proof script.
- Paired previews refresh the same index with both saved before objects,
  then both strict-current after objects. DataChunk loses its sole duplicate
  finding; the split unit loses the same duplicate and retains exactly its
  two unresolved destructor names. The standalone CLI agrees: 0/2 -> 1/2
  clean, 0 -> 270 existing linked bytes. The before DataChunk source accounted
  257 bytes; the existing 13-byte row moves into it, without increasing total
  authored C++ or matched bytes.
- This is self-strict currency for the explicit cohort and a legacy local
  link prediction against unchanged external providers. It is not a
  closed-strict gain, link.exe placement result or a new census measurement.
- EH verifier: zero EH-bearing rows, zero missing objects. Frozen-definition,
  canonical-class, new-variant, converged-data (eight addresses) and shadow
  data checks pass. CSV and whitespace checks pass. The affected placement
  sweep is recorded separately; no incidental body or pin is landed.

Remaining independent dependencies in AsciiStringFoldDeleters.cpp are
??1Rva0025558E@@UAE@XZ and ??1Rva0025559B@@UAE@XZ. The actual local index
does not supply them. No new body, alias or speculative owner was introduced.

The automatic rehome discovery command cannot run because this runner's
index has no build/link_census/census.log. The candidate was instead found
from the ranked duplicate queue, inspected in both units and verified with
the same add_match ownership operation. No census rebuild was started.

Reference link repairs reviewed at verified gitlink/checkout
a7c38d3b2597121f178ab5190b3062478823257d: 92a8d854 (canonical data owner),
4966496c (surplus AsciiString COMDAT) and 94f453a5 (STLport copy). Their
ownership/emission principles are applicable leads; their layouts and bytes
were not imported. Official master was fetched, but freshness verification
remains blocked by the existing reference-file claim and outstanding large
old/new full-gate comparison documented in
../unicode-comparator-link-20261014/readme.md. Preserve the verified pointer;
no success stamp was written.

Other checked work: repair_queue link; link_rank help/top/near and U/D/L/A
queries; explicit current-provider probes for ranked neighbours. Several
already link with current providers and were not claimed as new gains.
The flag-owner data-check false reject and the splitter accessor's two
failed compiler-shape trials are recorded in this session's sibling evidence
directories and re_attempts.log; both sources were restored and all their
claims released. Neither unchanged blocked attempt was retried.

No full link cycle, census build/measure/history, nightly, boot runner or
shadow publisher was started. Scratch before sources/objects/receipts and
the asserting proof script remain in build/datachunk-ctor-home-link-20261015.
