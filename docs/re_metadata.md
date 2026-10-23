# Curated RE metadata: Git overlay, private Ghidra replay

A small, reviewable package of accepted reverse-engineering facts (function names,
bodies, signatures, canonical types, managed comments) lives in Git and is replayed
into a **private** Ghidra project rebuilt from the executable and a recorded recipe.
The SQLite refdb (`docs/agent_tools.md`) stays the fast, derived read index.

This is infrastructure. It recovers no bytes, proves no codegen and earns no
recovery credit: a renamed function or a replayed layout is not a matched row.

Code: `tools/re_metadata.py` (called only through `tools/ghidra_refdb.py`),
`tools/ghidra/export_metadata.java` (observation and baseline; also the projection
library), `tools/ghidra/apply_metadata.java` (validated transactional replay).
Tests: `tools/tests/test_re_metadata.py`. Synthetic fixture:
`tools/tests/fixtures/re_metadata/`. BFME2 pilot package: `reverse/re_metadata/bfme2/`.

## Authority

| Fact | Authority | What the overlay does |
|---|---|---|
| Recovered status, owned extent, byte verification | `reverse/functions.csv` and the gates | cites rows; never writes the ledger |
| Original symbol identity | export / ILT / real-relocation evidence (`ghidra_refdb.admits`) | re-checks the cited row at plan **and** apply time |
| Canonical class layout | `reverse/class_contracts/` (`tools/class_contract.py`) | references a contract by path and SHA-256; drift is a conflict |
| Ghidra observation | an explicit record with provenance | exported as a *proposal* (`review: proposed`); never auto-accepted |
| Donor lead / hypothesis | the donor revision or analysis note | context only; not replayed |

Three separate axes on every replayable field (`provenance`): **origin**
(`target` / `donor` / `analysis`), **status** (`observation` / `hypothesis` /
`supported`) and **review** (`proposed` / `accepted` / `rejected`). Acceptance makes a
field *eligible*; field-specific evidence decides whether it is applied:

* **name**: `identity_tier` (`export`, `ilt`, `reloc`) plus `evidence_refs` to the
  rows that prove it. The tier string is a claim: the row is re-read, its digest
  compared and `ghidra_refdb.admits()` applied. Any other admissible name for the
  same entry is an alias conflict. The existing overwrite rule holds: only `ilt` may
  replace a name that is neither a placeholder nor `DEFAULT`, managed names included.
  `tools/ghidra/apply_metadata.java` repeats all of this from the evidence files
  itself, so a forged plan with correctly recomputed digests is still refused.
* **body**: `status: supported` and at least one verified `evidence_ref`; a cited
  `reverse/functions.csv` row must be `matched` and its extent must equal the body.
  Bodies taken from the ledger carry `"seeded": true`: they restate the ledger and
  are not independent boundary evidence.
* **signature**, **comment**: verified `evidence_refs` (signature: at least one).
* **type**: the contract (or a novel layout record) is the evidence.

`evidence_refs` entries are `{path, record_key, sha256}`. A path that is one of the
three ledger CSVs binds one row (`record_key` = `<rva column>=<value>;name=<name>`,
`sha256` = digest of the row as a `csv.DictReader` dict); any other path binds the
whole file.

## Package layout and records

```text
<package>/manifest.json               target, recipe, inputs, capabilities, exclusions, digest
<package>/functions/<entry_rva>.json   one record per function entry
<package>/types/<portable key>.json    contract reference or novel enum/typedef/struct layout
<package>/comments/<rva>-<kind>-<segment>.json
<package>/recipe/analysis_options.json effective analyzer options recorded from a real import
```

Addresses are RVAs relative to `target.image_base`, fixed-width lowercase
(`0x00003571`). Body ranges are half-open `[start, end_exclusive)`, sorted, disjoint
and **non-adjacent** (Ghidra merges adjacent ranges), and the entry lies inside one.
A function's stable key is executable SHA-256 + address space + entry RVA; a package
names exactly one target executable, so BFME1, BFME2 and RotWK never share address
identity.

*Manifest:* `schema` (`re-metadata/1`), `package_id`, `target`
(`executable_sha256`, `image_base`, `address_space`, `pointer_size`, `language_id`,
`compiler_spec_id`), `recipe` (`ghidra_version`, `ghidra_revision`, `java_version`,
`import_args`, `analysis.mode`, `analysis.effective_options`, `pre_scripts`),
`inputs` (`{path, sha256, role}` for every file the facts depend on), `capabilities`,
optional `contract_roots`, `evidence_root`, `exclusions` (`{record, field, reason}`),
and `metadata_sha256`.

*Function:* `entry_rva`; optional `name` (`raw` evidence spelling, `namespace`,
`ghidra_name`), `body` (`ranges`, `seeded`), `signature` (`convention`, `variadic`,
`storage_mode`, `return {type, storage}`, ordered `params [{name, type, storage}]`,
`auto_params [{role, storage}]`), each with its own `provenance`.

*Type references:* `{"prim": "i32"}` (`void bool8 char8 wchar16 i8 u8 i16 u16 i32
u32 i64 u64 f32 f64`), `{"ptr": ref}`, `{"array": ref, "count": n}`,
`{"named": "Qualified::Key"}`. Storage: `[{"reg": "ECX", "size": 4}]` or
`[{"stack": 4, "size": 4}]`; `[]` for a void return.

*Type:* `key` (qualified C++ name; Ghidra path `/ReMetadata/<ns>/.../<name>`, never
collapsed to the last component), `representation` (`struct`, `enum`, `typedef`),
then either `contract {path, sha256}` (the path must be
`class_contract.contract_path(key)` under a contract root) or `layout`. Enums declare
`size` and `signed` explicitly; `abi_unknown` lists what the source does not
establish (alignment, typically).

*Comment:* `address_rva`, `comment_kind` (`plate pre post eol repeatable`),
`segment_id`, `text` or `deleted: true` (a tombstone), `provenance`. The tool owns
only its delimited segment:

```text
[re-metadata:<segment_id>]
<text>
[/re-metadata:<segment_id>]
```

Analyst text around it is preserved byte for byte; absence from the package deletes
nothing.

### Canonical serialization and digests

Every digest is SHA-256 over canonical JSON: sorted keys, `,`/`:` separators, UTF-8,
Python's escaping (`ensure_ascii=False`), integers only (floats are refused), array
order preserved. `metadata_sha256` covers the manifest (without that field) and every
record, so it binds the recipe and the input hashes too. Files on disk are written
sorted and indented; they are not themselves the digest input. After a reviewed
edit, run `metadata-validate --update-digest`.

## Supported capability profile (v1)

Pinned environment: Ghidra 12.1.2 PUBLIC (`c0f584bf…`) with Temurin JDK 21.0.12.1;
`tools/ghidra/README.md` gives the install locations.

| Artifact | Replayed | Explicitly unsupported (reported, never coerced) |
|---|---|---|
| Names | raw spelling + demangled namespace path, `IMPORTED` source | aliases, collisions, ownership transfer |
| Bodies | exact intervals; a missing function is created; undefined bytes inside the body are disassembled | split/merge, overlap with another function, defined data inside |
| Comments | managed segments of the five listing kinds | blanket comment export |
| Types | explicit-layout non-bitfield structs (packing off), enums (width + values; signedness kept in the description), typedefs, pointers, arrays, pointer cycles | unions, bitfields, bases/vtables, unresolved contract queue items, by-value cycles, unresolved field types |
| Signatures | `__cdecl`, `__stdcall`, `__thiscall` with scalar/pointer parameters and scalar/pointer/void returns, dynamic storage; storage of return, every explicit parameter and the automatic `this` is verified after the write | varargs, custom/split/register-pair storage (e.g. 64-bit returns), aggregate parameters or returns, hidden return buffers, other conventions, ambiguous automatic parameters |

The `this` parameter's *type* is reported (`auto_param_types`) but not managed: in a
plain namespace Ghidra types it `void *`, in a demangler-created class it points to
that class's own structure. Function-pointer prototypes, stack/locals, decompiler
state, xrefs, bookmarks/equates, RTTI and memory edits are deferred.

## Commands

All verbs print one JSON object on stdout (diagnostics on stderr). Supply
`--ghidra`/`--java` or the usual `GHIDRA_INSTALL_DIR`/`JAVA_HOME`/`build/toolchains`.
Keep `TMPDIR` on the work disk: `refdb export` copies the project to a temp dir.

```sh
python3 tools/ghidra_refdb.py metadata-validate --metadata PKG [--executable EXE] [--update-digest]
python3 tools/ghidra_refdb.py metadata-recipe   --metadata PKG --executable EXE --scratch EMPTY_DIR
python3 tools/ghidra_refdb.py metadata-export   --project P.gpr --program NAME --scope SCOPE.json --out-dir DIR [--metadata PKG]
python3 tools/ghidra_refdb.py metadata-plan     --metadata PKG --project P.gpr --program NAME --out PLAN.json
python3 tools/ghidra_refdb.py metadata-apply    --metadata PKG --project P.gpr --program NAME --plan PLAN.json --receipt R.json
python3 tools/ghidra_refdb.py metadata-compare  --metadata PKG --actual OBSERVATION.json|DIR [--out REPORT.json]
python3 tools/ghidra_refdb.py metadata-rebuild  --metadata PKG --executable EXE --project NEW.gpr --program NAME --receipt R.json
```

Differences from the specification's proposed interface: `metadata-recipe` is new
(it records the effective analyzer options and tool versions from an actual import,
which the rebuild then enforces); `metadata-export` takes `--metadata` optionally
(the scope may carry the target hash); `--evidence-root` overrides the manifest's;
`--refdb-out` and `--max-cpu` are added to `metadata-rebuild`; `metadata-apply` has a
hidden test hook `--fail-after N` that injects a failure after N writes.

A scope file (`metadata-export`) lists `target.executable_sha256`, `functions`
(entry RVAs), `types` (qualified keys) and `comments` (`{address_rva, kind}`).

| Exit | `status` | Meaning |
|---|---|---|
| 0 | `ok`, `noop`, `pass`, `ready` | completed and validated (`noop`: nothing to change) |
| 2 | `invalid` | malformed package/plan/arguments, failed validation |
| 3 | `blocked` | conflicts, stale plan, wrong target, lock held |
| 4 | `unsupported` | an unsupported artifact is in scope (`metadata-export`: `partial`) |
| 5 | `environment` | Ghidra/JDK/recipe environment differs or is missing |
| 6 | `execution` | Ghidra failed, the transaction rolled back, or the save was not reported |
| 7 | `mismatch` | a rebuild or comparison found a difference |

## Plan, apply and the protected state

`metadata-plan` observes the program read-only (`-readOnly -noanalysis`) and writes a
deterministic plan: bindings (`metadata_sha256`, `recipe_sha256`, `inputs`,
`evidence`, `tools` = hashes of the four tool files, `target`, `baseline_sha256`,
`state_sha256`, `observation_sha256`), `scope`, ordered `operations` (`set_type` →
`create_function` → `set_function_body` → `set_function_name` →
`set_function_signature` → `set_comment_segment`), `noops`, `conflicts`,
`unsupported`, `excluded`, `context`, `status` and `plan_sha256`. Every operation has
`expected` (the exact current value the write protects), `desired`, `provenance` and
an `operation_id` = digest of those.

Replacement policy per field: a name follows the tier rule above; a body may replace
only the program's recorded **auto-analysis baseline** or an unchanged managed body;
a signature may replace the baseline, an unchanged managed signature, or (in a
program with no baseline) a `DEFAULT`/`ANALYSIS` signature; a type is created when
absent, left alone when equal, updated only when it is an unchanged managed type
whose by-value consumers are all in the plan, and any suffixed duplicate
(`.conflict`) is a conflict; a comment segment is replaced only while it still equals
its managed digest. Everything else is a conflict. There is no `--force`.

`metadata-apply` refuses a plan whose bindings changed (it names the changed input)
or whose status is not `ready`/`noop`, takes an exclusive lock beside the `.gpr`,
then runs `apply_metadata.java`, which independently checks the plan digest,
operation ids, target, baseline/state digests, every expected value and the name
evidence, applies everything in **one nested transaction**, verifies every written
value (signature storage included) and aborts the whole batch on any mismatch or
exception. (analyzeHeadless commits a script's transaction even when the script
throws, so the rollback relies on aborting the nested transaction; the tests prove
it by reopening the project in a fresh process.) The save is reported separately
(`save: succeeded|failed`, from analyzeHeadless's report).

### Baseline and managed state (inside the program)

Two JSON records in the program options category `RE Metadata`:

* `baseline`: written once, by `export_metadata.java baseline`, **only in the import
  session of a never-saved program** (the script refuses otherwise), binding the
  executable, metadata and recipe digests and the analyzer-options digest, with each
  scoped function's untouched body/name/signature digests. A project that was ever
  saved cannot acquire one: rebuild privately instead.
* `state`: per managed field (`function:<rva>:name|body|signature`,
  `type:<path>`, `comment:<rva>:<kind>:<segment>`) the digest of the written value,
  the plan digest, the full provenance and its digest, and `original`: the value the
  first managed write replaced (immutable thereafter).

Source mapping: managed names and signatures must read back as `IMPORTED`; a field
already equal before any replay (e.g. a body analysis found itself) compares as
`unmanaged-equal`. `metadata-compare` checks values, the managed digest and the
provenance digest, and the source mapping; Ghidra database ids never enter a
comparison.

### Rebuild and its receipt

`metadata-rebuild` validates the package against the executable and the environment
against the recipe, creates a project at an unused path, imports with the recorded
language/compiler spec, runs auto-analysis and records the baseline in the same
process, checks the effective analyzer options against `recipe/analysis_options.json`,
plans and applies, reopens in a fresh process and compares, plans and applies again
(must be a 0-change `noop` with equal before/after digests), exports an ordinary
refdb from the rebuilt project and runs `fn`/`callers`/`type` queries, checking exact
containment for every body interval, its gaps and its end-exclusive address.

The receipt lists every step as `passed`, `failed`, `blocked` or `not_run`, plus the
package, recipe, input and tool digests, the environment, plan/apply results,
`before_sha256`/`after_sha256` curated-state digests, exclusions, the Ghidra launch
count, timings and log paths. Host paths and timestamps live under `operational`
and are not part of any semantic comparison.

### Recovering from a conflict

Read the conflict, inspect the program, and decide which side is right. Either fix
the package (with evidence) and re-plan, exclude the field explicitly in
`manifest.exclusions` with a reason, or rebuild a fresh private project. A stale plan
is never retried: plan again against the current state.

## refdb schema version 2

`export_refdb.java` now writes `function_ranges.tsv`, and `ghidra_refdb.py load`
builds a version-2 snapshot with table `function_ranges(func_rva, start_rva,
end_rva_exclusive)` checked against each function's size, range count and maximum
address. A TSV directory without that file still loads as version 1, byte-identical
to before. Readers detect the version from `meta.schema_version` and refuse a
version they do not know or a version-2 file missing its table.

`fn DB RVA` rows now carry `containment`: `exact` (version 2; the row also lists its
`body` intervals; gap and end-exclusive addresses are never contained), `entry`,
`bounds-candidate` (version 1 only: entry ≤ RVA ≤ max address, which a gap also
satisfies; not containment evidence) or `name`. All other verbs are unchanged.

## Name sync (compatibility change)

`sync-plan DB [--out plan.tsv]` still lists renames read-only. With `--project`,
`--program` and `--out plan.json` it writes an evidence-bound name package
(`plan.package/`) and a validated metadata plan against that project's actual state;
`sync-apply --plan plan.json` replays it through `apply_metadata.java`. An unbound TSV
is refused with the regeneration command, and `tools/ghidra/apply_names.java` (which
applied unvalidated TSV lines and appended a provenance line on every run) is
removed.

## Acceptance tests

`TMPDIR=<work disk>/tmp python3 -m pytest tools/tests/test_re_metadata.py tools/tests/test_ghidra_refdb.py --basetemp=<work disk>/pytest`

| Id | Test(s) |
|---|---|
| A01 | `test_a15_a05_a01_fresh_rebuilds_round_trip_and_agree` (byte-identical re-export) |
| A02 | `test_a02_wrong_target_is_rejected_before_any_operation`, `test_a02_a17_java_refuses_wrong_target_and_malformed_plans` |
| A03 | `test_a03_plan_bindings_name_what_changed`, `test_a03_validation_names_a_changed_contract` |
| A04 | `test_a04_name_changed_after_planning_is_a_stale_plan`, `test_name_evidence_reuses_the_existing_tier_rules` |
| A05, A15 | `test_a15_a05_a01_fresh_rebuilds_round_trip_and_agree` |
| A06 | `test_a06_injected_failure_rolls_back_the_whole_batch` |
| A07 | `test_a07_managed_segments_beside_analyst_text`, `test_managed_segments_preserve_unmanaged_text` |
| A08, A09 | `test_a08_exact_ranges_never_contain_gaps_or_end_addresses`, `test_a09_version_1_snapshots_stay_readable_and_say_so`, rebuild `refdb_export_queries` |
| A10, A11 | `test_a10_a11_fixture_types_resolve_with_dependencies`, `test_a11_enum_width_and_signedness_are_enforced`, the rebuild comparison |
| A12 | the rebuild comparison (positive), `test_a12_wrong_expected_storage_rolls_back` |
| A13 | `test_a13_*` |
| A14 | `test_a14_collisions_and_overlaps_block_the_plan`, `test_a14_unknown_schema_and_malformed_interval_are_invalid`, `test_plan_conflicts_follow_field_policy` |
| A16 | BFME2 pilot (`reverse/re_metadata/bfme2/`, run below) |
| A17 | `test_a17_forged_ilt_plan_is_refused_by_the_java_path`, `test_a02_a17_java_refuses_wrong_target_and_malformed_plans`, `test_java_and_python_agree_on_shared_rules` |
| A18 | `tools/tests/test_ghidra_refdb.py`, `test_evidence_names_unchanged_by_the_admits_refactor`, `test_refdb_version_detection_and_consistency` |

Ghidra-backed tests skip with an explicit "NOT run" reason when Ghidra/JDK are absent;
a skip is not a pass.

## BFME2 pilot

```sh
python3 tools/ghidra_refdb.py metadata-rebuild --metadata reverse/re_metadata/bfme2 \
    --executable baselines/bfme2/workshop-vanilla-1.06/files/game.dat \
    --project <work disk>/bfme2_pilot/bfme2.gpr --program game.dat \
    --receipt <work disk>/bfme2_pilot/receipt.json --max-cpu 8
```

Scope: 18 exported `Coord3D`/`Region3D`/`ICoord3D` methods (names from the PE export
table; bodies from byte-verified ledger extents, tagged `seeded`; signatures from the
MSVC mangling of each exported name, with parameter names from the canonical header
or matched source), the `Coord3D`, `Region3D` and `ICoord3D` contracts, and two plate
comments carrying the `Coord3D` contract's own `decided_by` evidence. One signature
(`Coord3D::sub(const Coord3DBase *)`) is excluded: `Coord3DBase` has no contract. The
recipe is plain auto-analysis (no ledger seeding), so the rebuild needs only the
executable, the pinned tools and this package.

Result (2026-10-17, Ghidra 12.1.2, 5 Ghidra launches, 372 s of which 349 s is the
import and auto-analysis): every rebuild step passed; 58 of 58 replayed fields compare
equal after a fresh-process reopen and the second apply changed nothing. Plain
auto-analysis already agreed with the package on all 18 names (through the demangler),
all 18 ledger body extents and 12 of the 17 replayable signatures, storage included;
the replay changed the 5 signatures that carry parameters (types and names), created
the 3 contract types and wrote the 2 comments. That agreement is a pilot observation
about these simple exported methods, not a measure of the rest of the binary.
