# Make IMEManager's intended Windows shim explicit

The only source change appends `/Ireference/shims/sweep` after the three
existing explicit include roots on IMEManager.cpp's `// cl:` line. Source
bodies, typedefs, declarations, optimization flags, shared headers, tools,
ledgers and baselines are unchanged. Base source is from `930dcce626`; the
preceding allocator commit does not touch this unit. BFME1 remains pinned at
`4483e88da1c2f3b9a273f779baac7458bd8bb891`.

The source explicitly expects the sweep windows.h: it renames that shim's
HKL and GetKeyboardLayout declarations, then supplies its own strict HKL
handle and IME declarations. A real PlatformSDK include changes this
contract. The existing driver retries missing includes with the sweep path,
but the intended header should already be available to the initial command.
This source-local flag makes that dependency explicit without relying on a
failed first compile.

The original profile was not compiled again here, and no current original
object was available. The environment's observed missing-header/Wine exception
loop belongs to GameEngine.cpp, not an observed IMEManager failure. The driver
fallback may work on other hosts; no historical explicit flag is inferred.
`commands.json` labels the original command as reconstructed and not executed.
There is no before/after object equivalence or linking-gain claim.

## Verification

- Normal gate: all 47 existing rows, 3,875 bytes exact; six native string
  literals and 11 named imports verified.
- Five EH graphs EXACT. The normal parent-EH resolver validates six funclets
  whose compiler-local labels shifted; their retail identities are unchanged.
- Strict provider preparation passed. All 78 actual opened dependencies were
  rehashed. The only opened windows.h is `reference/shims/sweep/windows.h`.
- Current full object is link-clean against authenticated index
  `3f413ed3ff`, refreshing this exact object. Its external definition-name set
  matches the older census entry. This is a current verdict and historical
  name-set check, not a paired current-before comparison.
- Focused placement scan: zero bodies, zero pins. New coverage and whole-unit
  link gain are both zero.

`proof.json` contains all fully resolved native row hashes, current-object and
receipt hashes, opened dependencies, named definitions, the link verdict and
index hash. The frozen object, receipt and source are retained in the writer's
`build/batch4-ime-profile/after`. `prerequisite.json` records the independently
reviewed source/header contract. Normal gate, EH and strict preparation output
are included. `manifest.json` hashes the source and evidence.

Agent attribution: `Codex(runtime-model-not-exposed)`.
