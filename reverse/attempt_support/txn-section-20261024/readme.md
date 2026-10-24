# Native transaction initializer placement, 2026-10-24

model=gpt-6 lane=R budget=30m. Inputs: BFME2 b8259655173099477cad3079217fd7ef5e50cd71 plus the separately verified PointGroup repair and its completed receipt; BFME1 donor 32774ab03393709a7f14331ba8d98d281a55ffd9.

The authoritative ab0e4d81feec3933cca88fc1bfd3af6a74c7866a receipt proves all 62 existing 22-byte transaction initializer bodies closed-strict but unplaced solely because their compiled .text group differs from retail .text$yc. before-link-status.json preserves all 63 code rows, including the already placed 25-byte ICF constructor at 0065D070. Prior identity, ABI, data-owner and ICF evidence was reviewed in ../transaction-registry-link-20261021/readme.md and the constructor attempt log. No new identity is inferred here.

A donor review at 32774 found no code_seg repair in its game C++ units to inherit. Native BFME2 section evidence supplies this local repair: two balanced code_seg pragmas surround only the 62 existing explicit initializer definitions. The shared constructor stays in .text; globals, record layout, bodies, flags, symbols, headers and ledgers are unchanged. All 62 RVAs plus the source-file scope were confirmed claimed on origin before editing.

Control and modified normal builds both pass 63/63 code rows, 69 data rows and 62 string refs. find_declared_unmatched accepts the existing honest no-op default-constructor annotation. The official unmodified link-cycle unit planner finds all 62 functions orderable in native .text$yc, with zero placement refusals (placement-plan.json). These checks are prerequisites, not earned credit. An actual immutable shifted-base link measurement will decide whether 1,364 previously unplaced retail bytes can be credited.
