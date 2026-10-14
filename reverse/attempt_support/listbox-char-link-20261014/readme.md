# List-box wide-character accessor link repair (2026-10-14)

At BFME 2 d05f427cf9eb078707ce2906fc4c4f4dbf1dc201, the list-box consumer emitted a size-optimized
`StringBase<unsigned short>::getCharAt` COMDAT that the census rejected as
not retail's body. The established WWLib provider supplies the matched 23-byte
accessor at RVA 0x00035760. Keep the consumer's existing expansion forced inline
and import-qualified, which removes its surplus external body.

## Target evidence and scope

Consumer: `Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBoxMultiInput.cpp`
(8 matched rows, 3,787 authored bytes). Provider:
`Code/Libraries/Source/WWVegas/WWLib/string_base_inline.cpp`
(52 matched rows, 3,011 authored bytes). The consumer's accessor use is expanded
inside `GadgetListBoxInput` at RVA 0x00325635. Its specialization already used
the one-pointer string view; this repair introduces no name, offset or layout claim.
The provider's /O2 accessor is unchanged. The consumer is /O1.

`object-proof.json` compares before/after current objects and their dependency
receipts. It records removal of exactly
`?getCharAt@?$StringBase@G@@QBEGH@Z` from the consumer, with all 11 retained
COMDAT names, bodies, retail verdicts and semantic relocations unchanged.
Strong definitions, undefined externals and weak bindings are unchanged. The
provider object is byte-for-byte unchanged (54 retained COMDATs). COFF symbol
indices and section numbers can shift when a section is removed; comparison
normalizes them to symbol facts and section content identity, not numeric IDs.

The claim was file-scoped to the consumer. No provider source was edited.

## Acceptance and measurement

The index is the runner-provided census at commit `147cfae2cb`, dated
2026-10-14 07:27; SHA-256 is in `index-meta.json`. The committed status CSV is
older and is not used to claim a new measured gain.

Before and after:

- `python3 tools/link_check.py --prepare-current <consumer> <provider>`:
  scoped byte gate 60/60, strict current object receipts (`prepare-*.txt`).
- `python3 tools/link_check.py <consumer> <provider>`: legacy index preview
  removes the consumer's wrong-COMDAT blocker; its unresolved
  `?g_00E01D48@@3IA` remains. Blockers 2 -> 1, clean files 1/2 -> 1/2,
  predicted linking bytes 3,011 -> 3,011 (`link-*.txt`).

Final checks:

- `./build.sh <consumer> <provider>`: 60/60 matched; 12 empty-string refs,
  17 named imports, no baselined or skipped refs (`byte-cohort.txt`).
- `python3 tools/eh_verify.py <consumer>`: one EXACT EH row, no missing or
  non-exact data (`eh-after.txt`).
- `python3 tools/data_check.py <consumer> <provider>`: zero findings;
  `--converged` checks 8 addresses with no second names or unjudged rows.
- `python3 tools/link_check.py --new-variants <consumer>`: passes admission.
- `python3 tools/class_gate.py <consumer>` and
  `python3 tools/find_declared_unmatched.py <consumer>`: pass.
- `python3 tools/place_bodies.py <consumer>`: no incidental bodies/pins.
- `git diff --check`: passes.

Strict receipts and byte acceptance are local evidence. The link prediction
above is legacy, not a closed-strict census result. No full link cycle or census
was run; no new authored bytes or linking-byte gain is claimed.

## Reference review and remaining blockers

BFME 1 verified pointer/clean checkout:
`23b143233b5a8664a3bdf8572df6d905c310a5a1`.
Official fetched master: `a7c38d3b2597121f178ab5190b3062478823257d`.
The three intervening commits affect the Apt string-transform unit and attempt
records, not this provider or consumer. Reviewed BFME 1 repair
`d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`: removing seven nonretail local
constructor COMDATs is an applicable repair principle; its alias scaffold and
constructor identity are inapplicable and were not imported. BFME 2's
`VersionUnicode.cpp` already uses the import/forceinline suppression idiom.
This is a local compiler-emission repair, not a donor transfer or inferred
identity recovery.

The overdue reference freshness comparison remains incomplete. The attempted
previous-input full `./build.sh` passed retail baseline identification and
archive extraction, then waited on the shared compiler lock before compilation.
It was interrupted (exit 130); it produced no full-verification verdict.
No new reference inputs were used, and neither the gitlink nor the successful
freshness stamp was advanced. A future seat must complete the old/new comparison
once the full-build lock is available.

Remaining consumer blocker `g_00E01D48` is still unowned in `data_ledger.csv`
(RVA 0x00A01D48). Giving it a speculative new data definition would not establish
retail identity or data-back correctness. A supported data-owner repair and a
future runner census are needed to establish linking-byte gains.
