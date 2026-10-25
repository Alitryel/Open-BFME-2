# INI bucket initializer and prime-search bindings, 2026-10-25

Control: BFME 2 `349db6dc10`, BFME 1 `0bf534ea7ccde110c456edb9cd2dd5dae823c953`.
The repair changes INI.cpp's existing inline/configuration contracts. Source
ownership, function identities, compiler flags, pins and debt registers are kept.

## Problem and repair

The constructor at `0x0002D281` calls bucket initialization at `0x00148DDF`.
INI's emitted helper was 64 bytes; retail's complete helper is 59 bytes.
The control identity scan reports `wrong/extent` at constructor offset +43.

Use the existing SelectionIDMap provider's inline vector wrappers: `end()` reads
the finish pointer, and `insert()` forwards to `_M_fill_insert`. INI then emits
the complete retail 59-byte helper under its existing specialization name.
Its constructor reference certifies as a retail fold, and the INI identity scan
has zero wrong bindings. The original nine derived alias references are retained.

The existing `_STLP_BFME_LOWER_BOUND_EXTERN` configuration was below `<hash_map>`.
Move it before the first relevant include so the hashtable reads it and uses
the shared 57-byte prime-search provider at `0x00568D2F`. This removes INI's
competing search copy. The provider is `stlport_lower_bound_uint.cpp`.

## Verification

- Ordinary byte gates: **203/203 rows across five sources**, including 39/39
  INI rows, 47 string literals plus three empty-string references, and nine
  named imports. All defined INI functions have matched rows.
- EH: **13/13 graphs EXACT** across the cohort.
- Converged data: five sources, ten addresses, zero second names or unjudged rows.
- Enforced data check: INI, its residual constructor, SelectionIDMap and the
  lower-bound provider have zero findings.
- Current ordinary source/header/command receipts pass for all five objects.

The actual shared initializer owner, `BfmeObject476Copy.cpp`, passes its 147-row
byte gate. Its three existing EH-label identity diagnostics and data-name finding
`?g_009FEFA4@@3VBfmeFixedStorage0004543D@@B` at `0x009FEFA4` remain recorded in
the evidence. That source is unchanged from the control revision. These provider
findings retain their separate repair prerequisites.

The commit hook also reports three existing divergent STL definitions in INI:
`_M_find<AsciiString>`, `_STLP_alloc_proxy` and `insert_unique<AsciiString>`.
[definition-control.json](definition-control.json) records identical control and
repaired body/relocation digests for all three. These retain their separate
identity-debt scope; zero wrong bindings describes INI's references.

## Bounded link diagnostic

The fetched index measures `ef9c691284` at 2026-10-25 18:23 UTC and predates
the INI consolidation. A plain preview includes absorbed donor definitions.
For the paired diagnostic, use the existing `link_check.forget` and `refresh`
functions in memory: remove objects absent from the current compile-source
inventory, and refresh INI, the residual INI_ctor.cpp and three helper providers.
Other provider facts retain their published state; the stored index is preserved.

With that identical ownership overlay, the control fails selected-copy
verification for `__lower_bound`; the repair passes all five units. INI's
clean authored scope changes **0 -> 2,989 nonpadding bytes**. The other cohort
units keep or improve their verdicts. This is a bounded diagnostic; global
current-ledger closure and the next census remain separate measurements.

## Evidence and reproduction

[control.json](control.json) and [before-refs.tsv](before-refs.tsv) identify the
original wrong binding. [paired-result.json](paired-result.json) records both
ownership overlays, provider findings, source/object hashes, current receipt
checks and the published index hash. [validation.json](validation.json) binds
the ordinary tool commands, exit codes and raw-log hashes.

The normal commands are `tools/build.py` for the five listed sources,
`tools/eh_verify.py`, `tools/data_check.py` and `tools/find_declared_unmatched.py`.
The provider data check records exit 1 for the existing finding above; the other
stored checks exit 0. The cohort paths are in paired-result.json.

For a paired replay, compile the control INI source at the recorded revision
through the normal build entry point in a consistent checkout. Save its object
as `build/ini-bucket-link-20261025/before-obj` and its control.json in that
directory. Copy [audit.py.txt](audit.py.txt) there as audit.py and run it from
the repository root with the repaired cohort built and the recorded index.
The script checks the helper's full retail verdict, the constructor reference,
ordinary receipt currency, preserved index bytes and the cohort's blocker sets.
