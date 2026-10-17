# Synthetic RE-metadata fixture

Repository-owned test data for `tools/re_metadata.py` (`tools/tests/test_re_metadata.py`).
Nothing here is game code or game data.

| Path | What it is |
|---|---|
| `src/fixture.c` | The source: cdecl/stdcall/thiscall functions, a varargs, an aggregate-by-value and a 64-bit-return function (the deferred cases), the `FxPoint`/`FxBox` structures, the `FxKind` enum and the `fx_u32` typedef |
| `fixture.exe` | The committed 2 KB PE32 built from it (SHA-256 in `build.json`) |
| `build.json` | The exact build recipe and the clang version that produced `fixture.exe` |
| `class_contracts/` | `FxPoint` and `FxBox` in `tools/class_contract.py`'s contract format, so the canonical-type adapter is exercised |
| `evidence/reverse/` | A synthetic ledger: `exports.csv` (true: `fx_frag` is exported), `functions.csv` (`ilt-verified=` rows, plus `fx_mid`, a matched row **without** ILT evidence for the forged-tier tests), `reloc_names.csv` (`identity=real` rows, plus a generated one) |
| `package/` | The metadata package the round trip replays |
| `ghidra/fixture_edit.java` | Test-only Ghidra script that simulates analyst edits (renames, labels, comments, unmanaged types) |

## Build recipe

```sh
clang --target=i686-pc-windows-msvc -O1 -ffreestanding -fno-builtin -fno-stack-protector \
      -fno-asynchronous-unwind-tables -c src/fixture.c -o fixture.obj
lld-link /nologo /entry:fx_start /subsystem:console /nodefaultlib /base:0x10000000 /fixed \
      /Brepro /debug:none /export:fx_frag /out:fixture.exe fixture.obj
```

`test_fixture_executable_rebuilds_from_source` repeats this when clang and lld-link
exist and compares hashes; another clang version may emit other bytes, in which case
the committed `fixture.exe` stays the reference (the package is bound to its hash).

## Intentional construction

clang does not split functions, so the fragmented bodies are hand-written assembly:

* `fx_frag` (0x11c7): a hot part in `.text$m` and a cold part in `.text$z`, with
  `fx_mid` placed between them; a conditional jump reaches the cold part, and
  auto-analysis finds both ranges `[0x11c7, 0x11d7)` and `[0x11e9, 0x11ef)`.
* `fx_hidden` (0x11d7): its tail `[0x11ef, 0x11f3)` is reached only by `push; ret`,
  which analysis does not follow, so the curated two-range body replaces the
  one-range analysis baseline (and the tail is disassembled by the replay).
* `fx_orphan` (0x11f3): never referenced, so the replay creates the function.

The package excludes the three deferred signatures explicitly (`manifest.exclusions`).
If the fixture source or binary changes, regenerate the package digests with
`python3 tools/ghidra_refdb.py metadata-validate --metadata <pkg> --update-digest`
after updating the hashes the records cite, and re-record the recipe with
`metadata-recipe`.
