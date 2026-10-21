# Mesh deformation: grouped sums and nested products

Target: `?get_deformed_vertices@MeshModelClass@@QAEXPAVVector3@@PBVHTreeClass@@@Z`,
native 0016B680..0016BF3D, 2237 bytes, RET8. Trial base is BFME2
ce558e28475 with the committed BFME1 37c3022de1ab944c7ffe536440d637dc8199091c.
The starting body is the retained `cross-base.cpp.txt` in
`../mesh-cross-context-20261021/`. Its source and provenance were read alongside
the whole meshgeometry owner, the exact paired overload, and the w7/w9/w10/w11
and r62 records. The reference ranked/near queues and ZH packets were refreshed
and empty. This pass continues the supported mesh target rather than repeating
the old inert-local scans.

## Hypothesis and coverage

The paired 0016BF40 recovery and `docs/recipes.md` establish that nested FP
parentheses change MSVC 7.1 IL and operand ordering. The prior pass's real
cross-product intermediate changed the numbering of this candidate. The new
tests use that improved input, not the older unsigned-count body.

`replay.py.txt` generates two finite diagnostic suites:

- Group: control plus every contiguous interval of the eight blend-row terms,
  wrapped once or twice, on row Y, row Z, both Y/Z, or all X/Y/Z: 289 trials.
- Nest: control plus every 0/1/2 nesting-depth combination on the six products,
  applying the same pattern to rows Y and Z: 729 trials. Translation terms
  remain unchanged. Independent patterns for Y versus Z are not covered.

These are compiler diagnostics; grouping changes FP association and must pass
the full byte gate before being accepted. They establish no new original-source
or class-layout facts. No dummy functions, inert locals, volatile operations,
pins, shared headers or production changes are introduced.

## Result and replay

All 1,018 trials completed with no compile errors or unresolved references.
None is exact or improves the starting full-body comparison. The unchanged
control is the best result. This closes the two specified searches; it does
not exhaust independent nesting patterns on the two rows or all source shapes.

See verification.json and trials.tsv for completed counts and exact metrics.
The starting control is 2237 bytes, no unresolved references, M0/B8/S8,
74 positional differing bytes, and 2150 identical aligned-instruction bytes.
Regions are M before +58C, B before +6C0, and S thereafter. Structural differences
are counted separately. Aligned scores ignore jump displacement bytes, so they
are diagnostics only; `exact` compares the complete resolved byte strings and
checks the emitted COFF extent. The original partial bank remains intact.

Copy replay.py.txt to build/resume-eh-local/turn66-mesh-group.py, then run it
with Python, once without arguments and once with --nest. It invokes the normal
tools/explain_mismatch.py compiler path and reads the resulting COFF object.
No manual build.compile_source call is made by the driver. Inputs and results
remain under ignored build/resume-eh-local/turn66-mesh-group/.
The control dependency receipt records all 21 actual header hashes and the
compiler command fingerprint. Flags are unchanged: /arch:SSE /G7 /DNDEBUG /MD
with the bank's real WWMath, WWLib and WWDebug providers. All 21 header hashes
were rechecked against the checkout during the run.

Model: gpt-6.1-sol. This evidence is not recovered C++ progress.
