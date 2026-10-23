# List range provider reconciliation (2026-10-21)

Inputs: BFME2 parent 0cd9cb481d; published census e20daa4e78,
2026-10-21 21:42. BFME1 linking changes reviewed earlier at a80da2e3;
this repair uses BFME2 retail evidence and the already established
`stlport_list_b757d_insert.cpp` range-erase forwarding pattern.

## Target evidence and change

- The 115-byte list assignments at 000BDBFA and 002FFC74 call range
  erase 002FECD3 at 000BDC4B and 002FFCC5. That is the existing rowed
  `list<AsciiString>::erase(iterator, iterator)` worker. Forward through
  its declaration rather than generating opaque-record destruction.
- The native insert chains independently establish element extents:
  000BD24A -> 000BC804 -> 000BC180 -> 000BB6CC allocates 0x28 bytes;
  002FED6F -> 002FED07 -> 002FEC97 -> 002FE8AA allocates 0x10 bytes.
  Eight bytes are node links, leaving 32 and 8 data bytes respectively.
  Replace the old one-byte placeholders with these observed extents.
- The first copy worker is already named by the existing source bridge,
  `_Construct<BfmeStringRecord000B75AE>` at 000B9478. The second create
  worker calls the rowed two-pointer cdecl copy owner
  `Rva002FE87DConstruct`; forward placement construction to it.
- `AIConstructor_Unresolved.cpp` formerly instantiated the 002FFC74
  assignment with a trivial eight-byte record, causing the kept definition
  to be wrong. Declare the independently rowed assignment specialization
  instead. Its caller and all other rowed bodies stay exact.

The record application identities and scalar meanings remain unknown.
The existing provider spellings are inherited reference/structural evidence;
retail calls, allocation sizes and bytes establish the relationships above.
No new pin, alias, ledger row or naming claim is added.

## Verification

- Before: neither 115-byte unit links. AIConstructor_Unresolved is also
  blocked, including wrong-selected list assignment.
- After: `link_check.py` on all three sources reports **0 -> 230 B**,
  two of three units link. This is a **legacy preview** against e20daa4e78.
  The AI consumer loses its wrong-selected blocker but retains nine
  unresolved names; no bytes are credited for that source.
- `./build.sh` and `link_check.py --prepare-current`: 28/28 rows exact,
  string/float/import gates pass; strict reusable source receipts produced.
- `eh_verify.py AIConstructor_Unresolved.cpp`: EXACT 4/4.
- `find_declared_unmatched.py` passes for all three sources.
- Additionally extracted all four emitted insert dependencies per list:
  create_node 34 B, insert 37 B, dispatch 48 B, range insert 30 B. Each
  whole body is masked-byte equal to the native address listed above;
  every REL32 edge follows that native chain, ending at allocator 000307F0
  and copy 000B9478 or 002FE87D. No allocation-sized private copy remains.
- Closed-strict/link-cycle closure is unmeasured. No maintainer-only runner
  was started. The current-ledger universe still has missing objects.

A discarded member-template range-insert forwarding trial hit MSVC 7.1
C1001 in P2/main.c line 148. The final code uses ordinary STLport
instantiation with target-proven sizes instead. A forward-declared
AsciiString alone also failed because list nodes require its complete type;
the final range-erase bridge uses the canonical existing header.

## Preparation recovery, 2026-10-22

Replayed the checkout's ten preserved commits onto 0df867e973. Upstream
f0c3e87577 already supplies the CrushDie callback repair; retained its source
and kept the saved verification evidence. Upstream c55aebdc6a also supplies
the 000BDBFA range-erase bridge. Git combined that bridge with this attempt's
equivalent specialization without a text conflict; the required dry-run push
gate caught MSVC C2995. Removed only the duplicated bridge and its unnecessary
AsciiString include, retaining upstream's bridge and the native 32-byte record
extent. The 115-byte assignment passes build.sh with all literal/import checks.

The preparation record names no stash; the worktree had no saved untracked or
unstaged edits beyond the rebase conflict. Backup ref
refs/runner/preparation/1792628884160129801 remains intact. No commits skipped.
The recovered source set's legacy link_check preview reports 8/10 units clean,
0 -> 2,203 bytes against published e20daa4e78. This includes upstream's list
repair and is not an incremental gain over current master. AIConstructor and
stlport_pod_hash_bodies retain the previously documented unrelated blockers.
Closed-strict closure and a new measured census remain unverified.
