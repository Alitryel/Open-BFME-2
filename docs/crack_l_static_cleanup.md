# Compiler-local cleanup rows refused by check_csv

2026-10-13, seat crack-l, GPT-6-Astra. Parent: `0x0037FAC6`, 613 bytes,
`Code/GameEngine/Source/Common/System/ArmyPlacerPlaceObjects.cpp`.

The native parent passes callback VA `BB7D95` to atexit at `77FB2E`.
Using the canonical header's `BFME_ASCII_DTOR_DECL` emits `_$E2`, exactly 10 bytes: load the same static AsciiString at E022C4
into ECX and tail-jump to canonical destructor RVA 48BA39.

Native handler B7F244 points at FuncInfo D297D0, with maxState 2 and
unwind map D297C0. Its two entries are (-1, B7F22A), (-1, B7F237).
The compiler emits `$L1697` and `$L1698`: each is 13 bytes, loading the
same compiler-owned guard E022C8, clearing bit 0 or bit 1 with AND AL,
and writing it back. The complete parent EH graph verifies EXACT.

Rehoming the three existing rows from their manual address-named bodies
verified all 114 affected rows with `./build.sh`. The normal commit hook
then refused:

- `_$E2`: 007B7D95 versus unrelated 007B945A.
- `$L1697`: 0077F22A versus unrelated 0076CDEC.
- `$L1698`: 0077F237 versus unrelated 0076CDFA.

These are object-local COFF symbols in different translation units. The
checker keys names globally instead of by source/object. No new alias,
object-symbol token, baseline entry or pin was attempted. The repair was
reverted rather than changing the checker or manipulating label numbering.
Earlier `landed` log lines mean the local byte gate passed; later blocked
lines supersede them for publication. The assigned parent remains matched.

Reproduction artifacts in this worktree's ignored build/crack-l directory:
`static-cleanup-rejected.patch`, `cleanup-build.txt`, `cleanup-commit.txt`,
`army-place-eh.json`, and `data-ledger-refreshed.csv`. The partial data-index
refresh found 22,115 unbuilt source objects, so it was not committed.
