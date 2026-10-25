# Adversarial review of the consolidation draft

This review challenges whether the draft could nominate the wrong original file,
lose rows, overstate reference evidence, or report a stale observation as usable.
It was performed after the first working scan; the findings below were addressed
and regression tested before the final scan. No production merge was attempted.

| Challenge | Improvement and regression coverage |
|---|---|
| Are all 173 original paths actually present, rather than copied from a claim? | Extract from the manifest-verified retail image, retain offsets, string RVAs and raw spellings, and test the exact 173 `.cpp` plus ten-header count against the local baseline. Also test root-level `Z:\Code\...` paths and UTF-16 strings. |
| Is `string_xrefs.tsv` really an instruction-xref table? | Reading `tools/ghidra/list_string_xrefs.java` established that it records function entries. Decode the owning body, then verify the literal operand at a real instruction boundary. Packets cite the instruction RVA. |
| Can a short folded row borrow another row's evidence? | Key verified references by both RVA and extent. A regression places the only path reference beyond a short twin's end and requires only the longer row to receive it. |
| Can stale or inferred TU names masquerade as original EA files? | Reuse the existing freshness and disputed-anchor predicates. Stale assignments retain hint strength. An unsupported N/K/C filename guess cannot nominate a new original home. |
| Can BFME 1's addresses or run-filled paths route BFME 2? | Join name/file evidence within BFME 1, then join by spelling as a hint. Never transfer addresses across games. Run-filled file records remain catalogue citations without routing authority. |
| Can many weak hints overrule a target reference? | Strong target evidence wins over donor hints while retaining alternatives. Conflicting target facts block routing. Conflicting hints remain ambiguous; no majority vote resolves them. |
| Can a mixed fragment be deleted or moved whole? | Every selected matched row must agree. Unknown rows remain in the packet. Attached funclets travel with their actual named parent, and do not independently invent a home. No apply or delete operation exists in this draft. |
| Can implementation-source inclusions or data definitions be overlooked? | Record source includers and data rows. Flag internal linkage, macros/pragmas, line/path sensitivity, quoted includes, unledgered markers, protected path registers and language-mode changes. Existing destinations outside the selected active ledger receive explicit blocked packets. |
| Does matching `// cl:` mean a merge is safe? | Compare raw compile lines and region settings, preserve override/register hazards, and require the ordinary compiler, ABI, byte, EH, data and link checks. Static checks never certify a merge. |
| Can case-only paths create a second file on another platform? | Preserve EA/donor case variants and flag file/directory spelling conflicts. Never silently lowercase source paths. |
| Can missing or changed inputs produce a successful empty scan? | Require the retail image, active ledger and baseline manifest. Verify image size/SHA-256. Fingerprint source/donor contents or inventories according to what the planner reads, then recheck before publication. A concurrent-edit test requires no snapshot to be published. |
| Can a truncated manifest skip validation? | Require the complete output set and recompute expected input coverage. Check outputs, decoder identity, BFME 1 checkout revision and superproject gitlink. New-source, changed-output and omitted-manifest-entry tests must fail freshness. |
| Are reports practical to review? | The first draft repeated per-file evidence in every destination group. Store it once in `files.jsonl`, with explicit packet keys from groups. Keep the full generated results under ignored `build/consolidation/` and the compact original retail catalogue in `reverse/consolidation/`. |
| Could the planner itself stage or alter the reconstruction? | Restrict outputs to dedicated draft directories. Reject unsafe paths, redirected output artifacts and escaped source paths. Test that source, ledger and a fixture git index retain their exact bytes. The naming picker dispatches without constructing its applying lane. |

Validation: **97 tests passed** across `test_source_layout.py`, `test_name_lane.py`
and `test_name_lane_donors.py`. The planner contributes 40 of those tests.
`tools/check_csv.py`, `tools/check_case_collisions.py` and `git diff --check`
also passed. These are tooling and ledger checks; no game-source byte or link
result is claimed because the draft changes no game source.
The final full scan and its subsequent snapshot freshness check passed. It
catalogued 3,888 paths, surveyed 23,366 active source files and produced 1,046
investigation groups. Instruction checks supported retail path references in
282 selected rows; 12,263 files retained no usable routing candidate. No group
was certified for merging. Every group packet key resolved to a file packet.

Publication integration: concurrent upstream work added the `tu_skeleton.py`
execution lane and `docs/consolidation.md`. The documentation preserves that
workflow and appends this opt-in evidence-planning draft. Its packets confer no
merge authority; execution continues through `tu_skeleton.py`, its claims and
the normal gates. The scan counts above describe the pre-publication snapshot;
regenerate the ignored reports after pulling the concurrent reconstruction work.

Reference provenance: the selected BFME 1 submodule checkout is
`f5140c1cff6a58e16276fd6de6788186286953d4`, already ahead of the superproject's
`0bf534ea7ccde110c456edb9cd2dd5dae823c953` gitlink before this work. Its checkout
and gitlink were preserved. The separate local BFME 1 checkout is
`b406ac3bb7e3ccf8ff7c62029f8a1249cbca2c27`; its placement, merge-cluster,
mergeability, EA queue and name-oracle tools have identical hashes to the
reviewed submodule versions. No reference freshness-success marker was written;
the direct GitHub transport check could not connect from this environment.

Remaining boundaries are explicit: donor spelling does not prove target identity;
ROTWK data vocabulary does not prove C++ structure; the existing TU map is stale;
and compile/declaration/include analysis here is conservative rather than a C++
semantic model. `report.md`, `groups.json` and `files.jsonl` keep those limitations
visible in the actual work queue. The draft does not weaken any existing gate,
grant naming authority, apply consolidations, stage files, commit or push.
