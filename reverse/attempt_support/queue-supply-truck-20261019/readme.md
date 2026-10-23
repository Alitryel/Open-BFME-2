# AIPlayer::queueSupplyTruck handoff

The bank at `reverse/attempts/0x004f37b0.cpp` is a closer partial for `?queueSupplyTruck@AIPlayer@@IAEXXZ`, retail RVA `0x004F37B0`, extent 1537 bytes. The executable change restores the donor's desired-count read before the current-count read and removes the adjacent scheduling barrier, allowing the current count to fold into the memory comparison. `best.patch` is the complete source diff before re_log adds its bank header. No Code source, function-ledger row or symbol pin is changed.

## Measurements

These are fresh `tools/align_diff.py` compilations with `BFME_OBJSTORE=off`; each candidate has a distinct source path and the measurement wrapper removes its object and dependency receipt. Relocation and branch categories are excluded. Memory/register counts retain align_diff's own classification, including its limitations around unlinked data references. Positional differing bytes come from `build.compile_function`'s relocation-patched comparison, include absent tail bytes and do not determine eligibility. The before and final rows establish the accepted improvement without worsening either operand class.

| Source stem | Emitted bytes | Structural regions | Memory | Register | Positional differing bytes |
|---|---:|---:|---:|---:|---:|
| before | 1537 | 23 | 75 | 13 | 1009 |
| final | 1535 | 21 | 75 | 13 | 812 |
| h1-donor-order | 1537 | 23 | 75 | 13 | 1009 |
| h10-named-global | 1535 | 25 | 75 | 31 | 1153 |
| h10-named-phi | 1535 | 24 | 68 | 16 | 852 |
| h2-count-barrier | 1537 | 22 | 73 | 14 | 1009 |
| h3-manager | 1537 | 24 | 75 | 35 | 1136 |
| h4-loop | 1539 | 25 | 73 | 14 | 1185 |
| h5-order-and-barrier | 1535 | 21 | 75 | 13 | 812 |
| h6-priority | 1531 | 22 | 76 | 17 | 1033 |
| h7-loose-barrier | 1535 | 22 | 77 | 15 | 811 |
| h8-priority-read | 1529 | 20 | 76 | 17 | 780 |
| h9-command-base | 1547 | 26 | 74 | 14 | 1084 |
| h9-command-direct | 1535 | 21 | 75 | 13 | 812 |

The new score is the aligned retail-instruction agreement fraction, counting unmatched retail instructions and aligned memory/register mismatches as defects. It is a ranking estimate, not proof of semantic correctness or comparable to the farm's undocumented score method.

## Identity, boundaries and semantics

Native begins with its own EH prologue and ends in RET immediately before the next EH-prologued body. No declared ledger range overlaps it. `build/supply-4f37b0-20261019/retail.log` contains the full native listing and direct call destinations. Its receiver is in ECX and the final RET takes no stack arguments. The warehouse literal, three member-iterator calls, supply counts, dock checks, production sequence and queueUnits caller agree with the Zero Hour AIPlayer function. WorldBuilder's unnamed twin at VA `0x010F6160` is paired by strings at score 1.0 and names the original `GameLogic/AI/AIPlayer.cpp` path; this does not independently name the function. The real method identity is the donor inference corroborated by that full native control/call sequence and the existing named queueUnits caller, rather than a byte-match assertion.

The actual direct callees, Object offsets, AI virtual slots, hidden-return iterator size and command-interface adjustment were checked against native before shape trials. Native facts include the kind-byte accesses, rebuild-hole bit, seven-word filter mask, field offsets and command calls. The name and source comments come from the GeneralsMD donor. The bank's same-arm expressions do not drop operations; the priority helper adds a private volatile stack temporary, not a self-store to a game object. Removing that temporary or the remaining iterator barrier produces mixed improvements, so those alternatives are preserved as trials and are not represented as a closer bank. Every pre-existing comment line remains verbatim and in order. The missing applicable EA function description and player-filter comment were restored in their original positions.

## Ruled-out hypotheses and remaining mismatch

All six local verdicts were read, including the older 80-minute attempt omitted from the assignment's list. The only cited raw evidence directory, `build/resume-supply-visibility`, is absent in this checkout; `prior-paths.log` records that fact. No verdict cites a tracked support path. The WB identity and native listing were re-derived here.

Declaration order alone is byte-identical. Removing the count barrier alone trades fewer structural/memory differences for more register differences; combining those two changes is the accepted candidate. Simplifying the partition-manager PHI regresses receiver allocation and switches radius arithmetic to x87. Simplifying the build-list condition regresses loop structure and register use. Removing the other barrier or replacing the priority helper also trades defects between classes. Modeling the native +0x20 command-interface base, with compile-time checks of accessed offsets, is byte-identical to the best candidate when command calls use the inherited method directly; retaining the wrapper adds null adjustment code. Naming the kind filter within its existing lifetime, with either receiver form, also regresses. The prior Object-provider visibility hypothesis was not repeated. Full preregistered hypotheses and their refutation observations are in the scratch `hypotheses.md`.

Remaining mismatches are stack homes, live ranges, register assignment and scheduling: the candidate holds the build-list pointer in ESI rather than the native stack home, does not hoist the filter base-vtable pointer into ESI, keeps the partition manager in EDI, assigns the recount/loose-harvester Object pointers differently and retains the priority-byte temporary. It has a head-tested build-list back edge where native tests the saved next pointer at the bottom. All direct calls resolve. No evidence-backed new shape experiment remains from this run.

## Reproduction and inputs

Parent checkout: `af72028f8f334a7becdfa74206ce7acfe6391b75`. Donor checkout: `a18d9ed50607e9175de4d6568798d7d73119de09`. Compiler and include settings remain the bank's first cl directive, including O1, Ob1, G7, SSE, Oy-, GX and the existing BFME2 shims; no compiler profile, flag override or shared header was edited. Actual compiler arguments and input hashes are saved in the scratch provenance receipt. The source's first cl directive still controls the build.

Raw trial outputs, every trial source, the original bank, the selected source, inspection/measurement scripts and gate outputs are retained under `build/supply-4f37b0-20261019/`. `before.align.log` and `final.align.log` are the authoritative raw alignment outputs; their matching metrics JSON files contain differing-byte counts. `retail.log`, `wb.log`, `h5-detail.log` and `comment-integrity.log` preserve the native identity, debug twin, detailed alignment and comment checks. `re-log.log`, `check-csv.log` and `pin-consistency.log` hold the final tool outputs. No exact row was admitted, so add_match, build.sh and the exact-source declared-unmatched check do not apply to this partial. All changes remain uncommitted. No background task remains.
