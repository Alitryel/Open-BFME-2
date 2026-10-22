MaterialCollectorClass::Collect_Materials retained a private out-of-line
RefCountPtr<TextureClass> copy constructor, the sole current link blocker.
Use the existing imported force-inline constructor pattern from
MeshMatDescTextureHandles and the verified floor texture-copy repair. The
inline pointer copy and WORD refcount increment at +4 are unchanged; the
out-of-line name already binds to retail's 21-byte AssetReference copy at
424BB. No identity, layout, pin, row, compiler flag or ownership claim changes.
Existing BFME1/ZH provenance remains in the source; donor linking history was
reviewed at BFME1 37c3022de1ab944c7ffe536440d637dc8199091c.

Same published e20daa4e78 index, original and final current objects:
legacy link preview 0 -> 1489 nonpadding bytes. Only the unused private copy
constructor COMDAT disappears; every retained COMDAT digest and extent is
unchanged. The index lists no other unit blocked by this same constructor,
so there are no additional sweep members. Existing unreferenced diagnostics
remain diagnostics under retail-truth-3.

Acceptance: ordinary byte gate 8/8; strict reusable byte receipts before and
after; exception graph EXACT 1/1; frozen-definition and new-variant checks
pass. The two natural cleanup labels renumber, and the byte/EH gate resolves
them through the unchanged parent graph. No new authored C++ coverage and no
closed-strict placement gain are claimed. No census or full link cycle ran.
Paired findings and source/object/index hashes are preserved in proof.json.
