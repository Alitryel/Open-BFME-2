# Scripted model event update 0xBD6C2 recovered

The complete 894-byte body now matches retail. It retains a single destroy-loop
increment, the WorldBuilder twin's control flow, and the actual event iterator
increment. The incoming 898-byte bank had correct registers but duplicated the
node advance before handle destruction. The ordinary single-increment control
was 903 bytes with node/nugget registers exchanged and a separate cleanup tail.

## New hypothesis and search

Earlier handoffs ruled out iterator wrappers, live aliases, variable scopes,
callee visibility, flags, symbol-number scans and permutations. This run tests
equivalent control paths that merge after affecting allocation, the recipe that
closed 0x4404AC, 0x655B90 and 0x507D84 earlier this session. It does not repeat
those old controls.

The factorial search used seven edit bits, three branch forms, and three
side-effect-free node predicates: 1,143 variants plus two controls, eight
isolated compiler workers, 48 seconds, no compile failures, 80 exact outputs.
Nested substitutions sometimes suppress an enclosing substitution; counts are
compiled trials, not a claim of 1,145 distinct source or object shapes.

The selected one-bit variant is `paths-008-0-1`: replace just the existing
`system->destroy()` statement with two identical arms under `n==n->next`.
Both branches call destroy once. The predicate and duplicate call disappear;
the whole 894-byte result, including every relocation, equals retail.

Read-only Wine debugger observations at c2's priority builder show the destroy
node's priority increasing from 9 to 15. Its symbol ID is 30 in both runs.
The create node stays at priority 30. No compiler executable or intermediate
representation was patched. The improved node priority explains the recovered
EDI node / EBX nugget and the event-iterator reload before the shared list tail.

## Integration and provenance

Target BD6C2..BDA40 and WB945CC0 independently bind the frame-driven event/FX
and particle walks to W3DScriptedModelDraw. The original method name remains
unknown. ZH handleWeaponFireFX supports the emission relationship; the BFME1
scripted source has no recovered counterpart. No new identity is inferred from
bytes alone.

The known strong B6D26 initializer prerequisite is retained: move the existing
646-byte C48DB parser, constructor and its proven EH rows into the updater's
home. The original parser unit retains its two existing entry wrappers. Shared
20-byte event-base / 24-byte record declarations preserve both callers. Keep
the actual FX companion's volatile first owner test, external event destructor,
and visible select-any STLport erase. All existing bodies remain exact.

The exact parent EH graph binds handler7617DB / FuncInfo904D1C and six 8-byte
cleanups at 7617AB/B3/BB/C3/CB/D3. All are rowed from this object; the six old
generator claims yield. Two emitted 5-byte destructor tails are genuine folded
copies of existing owners: the event list at 200667 and particle string record
at 48BA39. Each has a checked whole-body/relocation ICF row, no new pin.
Initial cleanup admission correctly reported these missing callee identities;
adding the proven folded definitions resolves them without changing code.

## Checks and reproduction

Normal build: 21/21 rows across both units; six string literals verified.
EH: all three parent graphs EXACT. Frozen-definition and pin checks pass.
Link preview: both units LINKS, 1068 -> 1977 bytes against census08160bc2c9.
Placement rescan: zero extra bodies or pins. No maintainer-only runner used.

Copy `control.cpp.txt`, `driver.py.txt`, and `search.py.txt` into the scratch
`build/bd6c2-mergeweights/` paths named in the scripts, removing `.txt`, and run
search.py. The driver uses compiler_command with distinct source/object paths,
never the shared compile_source cache. `integrate.py.txt` records integration
against the pre-landing homes; `inputs.json` records revisions and flags.
`results-summary.json` records grouped scores and minimal winners; the compact
priority record and EH placements preserve the useful diagnostics.
