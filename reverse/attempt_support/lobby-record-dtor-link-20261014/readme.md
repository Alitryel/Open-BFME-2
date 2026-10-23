# LAN sort-record destructor link repair, 2026-10-14

Base: `adfdf28d0a`. Runner index measurement: `147cfae2cb`,
2026-10-14 07:27 UTC. The index hash and strict-current source/object hashes
are recorded in `object-proof.json`. The committed link_status.csv has a
different measurement and was used only for discovery, not these gains.

The lobby TU emitted an unused one-byte `ret` destructor for
`Rva000795C1Record`. Its four WWLib sort consumers emit a 15-byte destructor
that null-checks the pointer at +4 and calls free. Their exception cleanup
funclets reference the owning destructor, so the empty lobby copy won the
legacy index's first-copy selection and blocked those consumers.

Mark the lobby's existing empty, non-owning temporary teardown imported and
force-inline. MSVC retains the verified caller code but emits neither the
empty COMDAT nor an import reference. The caller's special argument-transfer
view remains local; this does not establish an application class name or a
new canonical layout. The target-derived 16-byte layout and sort ownership
are existing recovery evidence, not inferred from donor identity.

This follows the BFME 1 incidental-emitter repair principle reviewed at
`d3f9000fe08615a100e844adfff57fa4a39cd615`; the exact compiler spelling also
exists in BFME 2's SidesListDataChunks.cpp. No donor source was imported and
the BFME 1 pointer was not changed.

## Verification

Before editing, prepare-current byte-verified all five explicit providers
with strict reusable receipts (26 matched rows). After editing:

- `./build.sh Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptLanLobbyRefreshGamesList.cpp`: 2/2 rows, strings, floats and imports pass.
- `python3 tools/link_check.py --prepare-current` on the changed lobby source:
  strict reusable receipt and ordinary byte gates pass.
- Whole-object comparison: all 23 retained nondebug sections match in bytes,
  symbol bindings and relocations after COFF-index normalization. `.sxdata`
  indices resolve to the same EH handler. All retained COMDAT digests match;
  the only removed code is the unreferenced one-byte destructor. No imports,
  undefined names, data-reference facts or data findings were added.
- Consumer objects/source hashes remain unchanged, and their strict receipts
  remain current. The real destructor and all five LinearInsert EH cleanup
  references remain intact.
- `python3 tools/data_check.py --converged` on the lobby source: zero second
  names, zero unjudged rows. `find_declared_unmatched.py`, `check_csv.py` and
  `git diff --check` pass.

The prescribed local `link_check.py` preview explicitly included the lobby,
LinearInsert, Sort, SiftHeap and PopHeap providers together. Its exit 1 is the
unchanged Sort vector-copy blocker below; four of five units now link cleanly.
Paired previews use the same runner index and current strict-receipt provider
objects in memory; neither census/index nor link_status.csv was rewritten.

| Unit | Findings before → after | Newly linkable nonpadding retail bytes |
| --- | --- | ---: |
| AptLanLobbyRefreshGamesList | 0 → 0 | 0 |
| Rva00580776LinearInsert | 1 → 0 | 471 |
| Rva00580E10SiftHeap | 1 → 0 | 194 |
| Rva00580C0EPopHeap | 1 → 0 | 96 |
| Rva005810B6Sort | 2 → 1 | 0 |

Total legacy preview gain: **761 bytes**, three existing authored units;
four destructor conflicts removed. The spans include 767 bytes before
excluding retail 0xCC padding. No new authored C++ bytes and no self-strict or
closed-strict LINKED gains are claimed. Full link/boot verification was not run.

Remaining Sort finding: selected definition of
`??0?$vector@IV?$allocator@I@_STL@@@_STL@@QAE@ABV01@@Z` is not retail's.
Repair its provider/consumer relationship separately; this change does not
suppress or rename that dependency.

Local ignored preparation, object backups, paired snapshots, comparison script
and command output are under `build/lobby-record-dtor-link-20261014/` and
`build/lobby-record-dtor-*.txt`, plus
`build/record-dtor-consumers-prepare.txt`.

An independent rehome probe at 0x004F6318 was declined and logged: its 29-byte
split owner already links while the proposed AutoResolve home retains 13
findings. No source/ledger rehome was made and those claims were released.

## Preparation recovery, 2026-10-14

Rebased the preserved commit `b242d22cf4` onto runner upstream
`4eda91266b`. Upstream `00008ddf5d` already contains the identical imported,
force-inline destructor repair and its own evidence. The conflict was only
its extra inline-ownership comment; both explanations are retained. The
recovered source differs from upstream only in comments. This commit preserves
this checkout's independent object proof and attempt records, with **zero
additional authored or linking gain** relative to upstream.

Applied preparation stash `e836ab42ce2bfefdfe45976e2810f0955576d38d` with
`--index`. It has no tracked delta. All 31 untracked files (20 assembly dumps,
one drift report and ten packet reports) were restored and hash-checked
against every saved blob. They remain untracked; none is a new source claim.
The stash and backup ref
`refs/runner/preparation/1792019544802556140` remain intact.

Recovery acceptance:

- Bounded `link_check.py --prepare-current` for the five sources passes all
  26 rows with strict reusable receipts and ordinary byte/reference gates.
- `./build.sh` for the reconciled lobby passes both rows and all references.
- `eh_verify.py` for all five sources: 21 EXACT, no baseline or missing object.
- Declared-definition, class, new-variant, enforced data, converged-data,
  ledger-integrity and whitespace checks pass.
- The index SHA256 still matches `object-proof.json`. The prescribed explicit
  five-source local link preview reproduces four clean units, 1085 -> 1846
  legacy linked bytes at measurement `147cfae2cb`; exit 1 is solely the
  previously documented Sort vector-copy selection blocker. This is not a
  new recovery gain or a self-strict/closed-strict result.
- `progress.py origin/master`: +0 authored, byte-matched and census-linked
  bytes, as expected for already-landed code with preserved evidence.

A recovery file-claim request failed to fetch origin claim refs (exit 2);
no lease was acquired. No new body or repair was started. The conflict index
is clear and there is no tracked unfinished work. Full link/boot checks and
the independent Sort repair remain outside this recovery.
